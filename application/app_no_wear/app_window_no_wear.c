#include "app_window_no_wear.h"
#include "app_window_no_wear_ui.h"
#include "app_window_no_wear_layout.h"

/*-----------------------------本地逻辑处理--------------------------------------*/

static void app_window_no_wear_retry()
{
    application_go_back();
}

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_no_wear_acttimer_handler(void *buf)
{
    if (APPLICATION_TIMER_ACT == *((unsigned int *)buf))
    {
        app_window_no_wear_ui_show_ani();
        gui_surface_commit();
    }
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_no_wear_init(void *buf)
{
}

static void app_window_no_wear_load(void *buf)
{
    app_window_no_wear_ui_show();
}

static void app_window_no_wear_entry(void *buf)
{
    application_open_act_timer(APPLICATION_TIMER_ACT, 100);
}

static void app_window_no_wear_exit()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_no_wear_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_no_wear_static_events[] =
    {
        {
            .id = EVENT_ACT,
            .handler = app_window_no_wear_acttimer_handler,
        },
};

static const gui_touch_event_struct app_window_no_wear_touch_events[] =
    {
        {
            .id = NO_WEAR_LAYOUT_RETRY_ID,
            .click = app_window_no_wear_retry,
        },
};

const gui_window_struct app_window_no_wear =
    {
        .screen = &app_no_wear_screen,

        .init = app_window_no_wear_init,
        .load = app_window_no_wear_load,
        .entry = app_window_no_wear_entry,
        .exit = app_window_no_wear_exit,
        .destroy = app_window_no_wear_destroy,

        .touch_event_num = countof(app_window_no_wear_touch_events),
        .touch_events = app_window_no_wear_touch_events,

        .event_num = countof(app_window_no_wear_static_events),
        .events = app_window_no_wear_static_events,
};
