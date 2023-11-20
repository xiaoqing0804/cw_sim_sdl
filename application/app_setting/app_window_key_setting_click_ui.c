#include "app_window_key_setting_click_ui.h"
#include "app_window_key_setting_click_layout.h"
#include "app_window_key_setting_click_type.h"
#include "app_window_key_setting_click.h"
#include "application_config_app_info.h"
#include "gui_surface_layout_listview.h"
#include "config_key_define.h"

static void app_window_key_setting_click_ui_scale(gui_box_struct *box)
{
	gui_node_struct *node = gui_surface_box_find_node(box, KEY_SETTING_CLICK_LAYOUT_ID_ICON);
	if (node != NULL)
	{
		node->scale = 62 / 98.0f;
	}
}

static void app_window_key_setting_click_ui_select(gui_box_struct *box, app_info_struct *app_info)
{
	gui_node_struct *node = gui_surface_box_find_node(box, KEY_SETTING_CLICK_LAYOUT_ID_CHECKED);
	if (node != NULL)
	{
		node->visible = app_window_key_setting_click_type_is_selected(app_info->id);
	}
}

static void app_window_key_setting_click_ui_init_box(gui_box_struct *box, app_info_struct *app_info)
{
	if (box->child == NULL)
	{
		box->id = app_info->id;
		box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
		box->widget = &gui_widget_key_setting_click;
		box->x = gui_widget_key_setting_click.x;
		box->y = gui_widget_key_setting_click.y;
		box->width = gui_widget_key_setting_click.width;
		box->height = gui_widget_key_setting_click.height;
		box->visible = gui_widget_key_setting_click.visible;

		gui_key_setting_click_item_icon.data = app_info->icons[0];
		gui_key_setting_click_item_title.value.string_id = app_info->name;
	}
}

void app_window_key_setting_click_ui_list_refresh()
{
	gui_surface_struct *surface = gui_surface_get_surface(&app_screen_key_setting_click);
	if (surface != NULL)
	{
		gui_surface_layout_listview_dynamic_init(surface);

		app_info_struct *app_info;
		gui_box_struct *box;
		for (short i = 0; i < config_key_define_get_count(); i++)
		{
			app_info = config_key_define_get_info(i);
			if ((app_info != NULL) && (app_info->icons != NULL))
			{
				box = gui_surface_layout_listview_dynamic_get_box(surface, app_info->id);
				if (box != NULL)
				{
					app_window_key_setting_click_ui_init_box(box, app_info);
					gui_surface_layout_listview_dynamic_add_item(surface, box);

					app_window_key_setting_click_ui_select(box, app_info);
					app_window_key_setting_click_ui_scale(box);
				}
			}
		}
		gui_surface_layout_listview_dynamic_finish(surface);
	}
}

void app_window_key_setting_click_ui_show(unsigned short string_id)
{
	application_titlebar_create(&app_screen_key_setting_click, string_id);

	gui_surface_struct *surface = gui_surface_get_surface(&app_screen_key_setting_click);
	gui_surface_layout_listview_dynamic_create(surface, app_window_key_setting_click_ui_list_refresh);
}