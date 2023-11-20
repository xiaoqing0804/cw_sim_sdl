#include "app_window_usb.h"
#include "app_window_usb_ui.h"
#include "app_window_usb_layout.h"

extern void app_usb_start_req(void); // start usb mode
extern void app_usb_stop_req(void);  // stop usb mode

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_usb_click(gui_click_struct *event)
{
    application_goto_main();
}

static void app_window_usb_usb_offline(void *buf)
{
    application_goto_main();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_usb_init(void *buf)
{
}

static void app_window_usb_load(void *buf)
{
}

static void app_window_usb_entry(void *buf)
{
    app_usb_start_req();
}

static void app_window_usb_exit()
{
    app_usb_stop_req();
}

static void app_window_usb_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/
static const gui_window_config_struct g_usb_config =
    {
        .forbid_gesture_back = 1,
        .forbid_key_back = 1,
        .entry_back_to_destory = 1,
};

static const gui_touch_event_struct g_usb_touch[] =
    {
        {
            .id = 10,
            .click = app_window_usb_click,
            .offset_left = 10,
            .offset_top = 10,
            .offset_right = 10,
            .offset_bottom = 10,
        },
};

static const app_window_event_struct g_usb_events[] =
    {
        {
            .id = EVENT_USB_OFFLINE,
            .handler = app_window_usb_usb_offline,
        },
        {
            .id = EVENT_BL_TIMEOUT,
        },
        {
            .id = EVENT_ALL,
        },
};

const gui_window_struct app_window_usb =
    {
        .screen = &gui_screen_usb,

        .init = app_window_usb_init,
        .load = app_window_usb_load,
        .entry = app_window_usb_entry,
        .exit = app_window_usb_exit,
        .destroy = app_window_usb_destroy,

        .event_num = countof(g_usb_events),
        .events = g_usb_events,
};
