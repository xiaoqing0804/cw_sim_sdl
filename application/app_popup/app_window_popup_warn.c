
#include "app_window_popup_warn.h"
#include "app_window_popup_warn_ui.h"
#include "app_window_popup_warn_layout.h"
#include "gui_surface_box_label.h"

/*-----------------------------定义--------------------------------------*/
static gui_popup_warn_struct g_gui_popup_warn;

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_popup_warn_click_handle(gui_click_struct *event)
{
    application_go_back();
}

/*-----------------------------系统事件--------------------------------------*/
static void app_window_popup_warn_init(void *buf)
{
    memcpy(&g_gui_popup_warn, buf, sizeof(gui_popup_warn_struct));
}

static void app_window_popup_warn_load()
{
    app_window_popup_warn_ui_show(&g_gui_popup_warn);
}

static void app_window_popup_warn_entry()
{
}

static void app_window_popup_warn_exit()
{
}

static void app_window_popup_warn_destroy()
{
}

/*-----------------------------配置--------------------------------------*/

static const gui_window_config_struct gui_popup_warn_config =
    {
        .entry_back_to_destory = 1,
};

static const app_window_event_struct gui_popup_warn_events[] =
    {
        {
            .id = EVENT_BL_TIMEOUT,
            .handler = NULL,
        },
};

static const gui_touch_event_struct gui_touch_popup_warn[] =
    {
        {
            .id = POPUP_WARN_LAYOUT_ID_BACK,
            .click = app_window_popup_warn_click_handle,
        },
};

const gui_window_struct app_window_popup_warn =
    {
        .screen = &gui_screen_popup_warn,
        .config = &gui_popup_warn_config,

        .init = app_window_popup_warn_init,
        .load = app_window_popup_warn_load,
        .entry = app_window_popup_warn_entry,
        .exit = app_window_popup_warn_exit,
        .destroy = app_window_popup_warn_destroy,

        .touch_event_num = countof(gui_touch_popup_warn),
        .touch_events = gui_touch_popup_warn,

        .event_num = countof(gui_popup_warn_events),
        .events = gui_popup_warn_events,
};
