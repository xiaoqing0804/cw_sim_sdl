
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "font_convert.h"

#include "app_task_main.h"
#include "data_manager_flash.h"

#include "gui_event_core_id.h"

#include "app_window_message_delete_all.h"
#include "app_window_message_list.h"

#include "app_window_message_info.h"
#include "app_window_message_info_ui.h"
#include "app_window_message_info_layout.h"


/*-----------------------------系统事件--------------------------------------*/
static void app_window_message_info_init(void *buf)
{
    unsigned int index = (unsigned int)buf;
    g_curr_msg_index = index;
    g_timer_exit = (((index & 0x80000000) == 0) ? 0 : 1);
    SYS_DEBUG("app_window_message_info_init %d", g_timer_exit);
}

static void app_window_message_info_load(void *buf)
{
    app_window_message_info_update();
	application_titlebar_create(&gui_message_info_screen,STRING_MESSAGE);
    gui_surface_commit();
}

static void app_window_message_info_entry(void *buf)
{
    if (g_timer_exit == 1)
    {
        application_open_act_timer(APPLICATION_TIMER_ACT, 3000);
    }
}

static void app_window_message_info_exit()
{
}

static void app_window_message_info_destroy()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

/*-----------------------------响应事件--------------------------------------*/
static void app_window_message_info_event_handler(void *buf)
{
    g_curr_msg_index = 0;
    application_open_act_timer(APPLICATION_TIMER_ACT, 3000);
    app_window_message_info_load(NULL);
}


static void app_window_message_goback_click(gui_click_struct *event)
{
    application_go_back();
}

static void app_window_message_info_back_handler(void *buf)
{
    application_go_back();
}

static const gui_touch_event_struct app_window_message_info_touch_events[] =
{
    {.id = APP_MESSAGE_INFO_GOBACK,            .click = app_window_message_goback_click        },
};

static void app_window_message_info_act_handler(void *buf)
{
	application_go_back();
}

static const app_window_event_struct app_window_message_info_event_map[] =
    {
        {
            .id = EVENT_MESSAGE,
            .handler = app_window_message_info_event_handler,
        },

        {
            .id = GUI_EVENT_GESTURE_BACK,
            .handler = app_window_message_info_back_handler,
        },
        {
            .id = EVENT_ACT, // 控件ID.
            .handler = app_window_message_info_act_handler,
        },
};

/*-----------------------------配置--------------------------------------*/
const gui_window_struct app_window_message_info =
    {
        .screen = &gui_message_info_screen,
        .init = app_window_message_info_init,
        .load = app_window_message_info_load,
        .entry = app_window_message_info_entry,
        .exit = app_window_message_info_exit,
        .destroy = app_window_message_info_destroy,

        .touch_event_num = countof(app_window_message_info_touch_events),
        .touch_events = app_window_message_info_touch_events,

        .event_num = countof(app_window_message_info_event_map),
        .events = app_window_message_info_event_map,
};
