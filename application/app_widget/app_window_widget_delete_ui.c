#include "app_window_widget_delete_ui.h"
#include "app_window_widget_delete_layout.h"
#include "application_config_app_info.h"
#include "gui_surface_box_layout_item.h"
#include "config_widget_list.h"
#include "data_widget_list.h"
#include "gui_surface_layout_listview.h"
#include "application_titlebar.h"

static void app_window_widget_delete_visible_delete(gui_box_struct *box, unsigned char can_up)
{
    /*判断是否是删除小组件*/
    gui_surface_box_layout_item_change_visible(box, WIDGET_ITEM_DEL_ICON, 1);
    gui_surface_box_layout_item_change_visible(box, WIDGET_ITEM_ADD_ICON, 0);
    gui_surface_box_layout_item_change_visible(box, WIDGET_ITEM_MUP_ICON, can_up);
}

static void app_window_widget_delete_visible_add(gui_box_struct *box)
{
    /*判断是否是添加小组件*/
    gui_surface_box_layout_item_change_visible(box, WIDGET_ITEM_DEL_ICON, 0);
    gui_surface_box_layout_item_change_visible(box, WIDGET_ITEM_ADD_ICON, 1);
    gui_surface_box_layout_item_change_visible(box, WIDGET_ITEM_MUP_ICON, 0);
}

static void app_window_widget_delete_init_box(gui_box_struct *box, short box_id, app_info_struct *app_info)
{
    box->id = box_id;
    box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
    box->widget = &gui_widget_delete_info;
    box->x = 0;
    box->y = 0;
    box->width = LCD_SIZE_WIDTH;
    box->height = WND_WIDGET_DELETE_LIST_ITEM_H;
    box->visible = 1;

    gui_widget_delete_app_icon.data = app_info->icon_widget;
    gui_widget_delete_app_name.value.string_id = app_info->name;
}

static void app_window_widget_delete_refresh()
{
    // geg box_number
    short icon_num = get_widget_app_count();        // 已加入widget的数目
    short add_num = config_widget_list_get_count(); // 没有加入 widget 的数目
    SYS_DEBUG("gui: widget_delete, icon_num=%d, add_num=%d", icon_num, add_num);

    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_widget_delete);
    if (surface != NULL)
    {
        gui_surface_layout_listview_dynamic_init(surface);

        gui_box_struct *box = NULL;
        short box_id = 0;

        app_info_struct *app_info;
        unsigned int app_id;

        for (short icon_idx = 0; icon_idx < icon_num + add_num; icon_idx++)
        {
            app_id = (icon_idx < icon_num) ? get_widget_app_id(icon_idx)
                                           : config_widget_list_get_appid(icon_idx - icon_num);
            app_info = get_app_info_by_id((APP_INFO_ID)app_id);
            if (app_info != NULL)
            {
                box_id = 10 + app_info->id;
                box = gui_surface_layout_listview_dynamic_get_box(surface, box_id);
                if (box != NULL)
                {
                    app_window_widget_delete_init_box(box, box_id, app_info);
                    gui_surface_layout_listview_dynamic_add_item(surface, box);

                    // 已经在列表的，显示删除图标
                    if (icon_idx < icon_num)
                        app_window_widget_delete_visible_delete(box, icon_idx > 0);
                    else
                        app_window_widget_delete_visible_add(box);
                }
            }
        }
    }
    gui_surface_layout_listview_dynamic_finish(surface);
}

void app_window_widget_delete_ui_show_list()
{
    application_titlebar_create(&gui_screen_widget_delete, STRING_CUSTOM);

    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_widget_delete);
    gui_surface_layout_listview_dynamic_create(surface, app_window_widget_delete_refresh);
}