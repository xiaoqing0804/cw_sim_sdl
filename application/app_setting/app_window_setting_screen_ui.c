#include "app_window_setting_screen_ui.h"
#include "app_window_setting_screen_layout.h"

#include "gui_surface_box_layout_item.h"
#include "application_config_app_info.h"
#include "app_window_widget_delete.h"
#include "data_wrist_lift.h"
#include "data_brightness.h"

void app_window_setting_screen_ui_show_wrist()
{
	gui_box_struct *wrist = gui_surface_get_box(&gui_screen_setting_screen, APP_INFO_ID_WRIST);
	if (data_wrist_lift_status_is_on())
	{
		gui_surface_box_layout_item_change_image(wrist, APP_SETTING_SCREEN_LAYOUT_ID_OPEN, &pic_setting_list_status_open_info);
	}
	else
	{
		gui_surface_box_layout_item_change_image(wrist, APP_SETTING_SCREEN_LAYOUT_ID_OPEN, &pic_setting_list_status_close_info);
	}
}

void app_window_setting_screen_ui_show_brightness()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_setting_screen, APP_INFO_ID_BRIGHTNESS);
	gui_node_struct *node = gui_surface_box_find_node(box, APP_SETTING_SCREEN_LAYOUT_ID_BRIGHTNESS);
	node->clip_width = node->width * data_brightness_get_value() / 100;
}

void app_window_setting_screen_ui_show()
{
	application_titlebar_create(&gui_screen_setting_screen, STRING_SCREEN_SET);
	app_window_setting_screen_ui_show_brightness();
	app_window_setting_screen_ui_show_wrist();
}

unsigned char app_window_setting_screen_ui_is_touch_on_wrist_button(short x, short y)
{
	return (x > 300);
}

unsigned char app_window_setting_screen_ui_is_touch_on_brightness_low(short x, short y)
{
	return (x < 88);
}

unsigned char app_window_setting_screen_ui_is_touch_on_brightness_high(short x, short y)
{
	return (x > 350);
}
