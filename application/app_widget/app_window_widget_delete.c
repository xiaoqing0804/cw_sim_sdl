#include "app_window_widget_delete.h"
#include "app_window_widget_delete_ui.h"
#include "app_window_widget_delete_layout.h"
#include "config_widget_list.h"
#include "data_widget_list.h"

#include "gui_event_core_id.h"
#include "application_config_app_info.h"

/*-----------------------------定义及声明--------------------------------------*/
static unsigned short g_widget_entry_app_id = 0;

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_widget_delete_on_click(gui_click_layout_struct *event)
{
    short icon_index = event->index;
    short icon_num = get_widget_app_count();
    short add_num = config_widget_list_get_count();
    SYS_DEBUG("icon_index = %d, %d, %d", icon_index, icon_num, add_num);

    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_widget_delete);
    if (event->x < g_widget_delete_layout_x_right) // 点击在删除的区域内
    {
        if (event->x > g_widget_delete_layout_x_left) // 点击在删除的区域内
        {
            if (icon_index < icon_num) // 删除
            {
                unsigned int app_id = get_widget_app_id(icon_index);
                app_info_struct *app_info = get_app_info_by_id((APP_INFO_ID)app_id);
                if (app_info != NULL && remove_widget_app(app_info->id))
                {
                    application_list_clean_window(app_info->window);
                }
            }
            else // 增加
            {
                short index = abs(icon_index - icon_num);
                app_info_struct *app_info = config_widget_list_get_info(index);
                if (app_info != NULL)
                {
                    add_widget_app(app_info->id);
                }
            }
        }
    }
    else // 点击在可以上下移动区域内
    {
        if (icon_index < icon_num && icon_index != 0)
        {
            widget_top_app(icon_index);
        }
    }
    application_widget_update();
    gui_surface_layout_listview_updata_arrange(surface);
    gui_surface_commit();
}

static void app_window_list_widget_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_widget_delete);

    if (rolkey->rotate == ROTATE_TYPE_FORWARD)
    {
        gui_surface_layout_listview_switch_to_item(surface, DIRECTION_TYPE_DOWN);
    }
    else if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
    {
        gui_surface_layout_listview_switch_to_item(surface, DIRECTION_TYPE_UP);
    }

    gui_surface_commit();
}

static void app_window_list_widget_goback_handler(void *buf)
{
    if ((g_widget_entry_app_id != 0) && !is_exist_widget_app(g_widget_entry_app_id))
    {
        // 进入widget-add前的窗口已经被从widget列表移除了， 返回时先销毁那个窗口..
        app_info_struct *app_info = get_app_info_by_id((APP_INFO_ID)g_widget_entry_app_id);
        if (app_info != NULL && app_info->window)
        {
            gui_window_history_remove_window(app_info->window);
        }
    }
    application_go_back();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_widget_delete_init(void *buf)
{
    g_widget_entry_app_id = (unsigned int)buf;
    init_widget_app_count();
}

static void app_window_widget_delete_load(void *buf)
{
    app_window_widget_delete_ui_show_list();
}

static void app_window_widget_delete_entry(void *buf)
{
}

static void app_window_widget_delete_exit()
{
}

static void app_window_widget_delete_destroy()
{
    g_widget_entry_app_id = 0;
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_moreinfo_events[] =
    {
        {
            .id = EVENT_ROLKEY,
            .handler = app_window_list_widget_rolkey_handler,
        },
        {
            .id = GUI_EVENT_GESTURE_BACK,
            .handler = app_window_list_widget_goback_handler,
        },
        {
            .id = EVENT_GO_BACK,
            .handler = app_window_list_widget_goback_handler,
        },
};

const gui_window_struct app_window_widget_delete =
    {
        .screen = &gui_screen_widget_delete,

        .init = app_window_widget_delete_init,
        .load = app_window_widget_delete_load,
        .entry = app_window_widget_delete_entry,
        .exit = app_window_widget_delete_exit,
        .destroy = app_window_widget_delete_destroy,

        .click_on_layout_item = app_window_widget_delete_on_click,

        .event_num = countof(app_window_moreinfo_events),
        .events = app_window_moreinfo_events,
};
