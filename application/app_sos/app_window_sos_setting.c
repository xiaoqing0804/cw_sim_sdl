#include "app_window_sos_setting.h"
#include "app_window_sos_setting_ui.h"
#include "app_window_sos_setting_layout.h"
#include "data_sos.h"

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_sos_setting_event_touch(gui_click_struct *event)
{
    data_sos_switch_status();
    app_window_sos_setting_ui_show_status();
    gui_surface_commit();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_sos_setting_init(void *buf)
{
}

static void app_window_sos_setting_load(void *buf)
{
    app_window_sos_setting_ui_show();
}

static void app_window_sos_setting_entry(void *buf)
{
}

static void app_window_sos_setting_exit()
{
}

static void app_window_sos_setting_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_sos_setting_touch_events[] =
    {
        {
            .id = SOS_SETTING_LAYOUT_ID_OPEN,
            .click = app_window_sos_setting_event_touch,
        },
};

const gui_window_struct app_window_sos_setting =
    {
        .screen = &gui_screen_sos_setting,

        .init = app_window_sos_setting_init,
        .load = app_window_sos_setting_load,
        .entry = app_window_sos_setting_entry,
        .exit = app_window_sos_setting_exit,
        .destroy = app_window_sos_setting_destroy,

        .touch_event_num = countof(app_window_sos_setting_touch_events),
        .touch_events = app_window_sos_setting_touch_events,
};
