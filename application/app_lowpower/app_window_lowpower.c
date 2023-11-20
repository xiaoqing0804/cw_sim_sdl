#include "app_window_lowpower.h"
#include "app_window_lowpower_ui.h"
#include "app_window_lowpower_layout.h"
#include "app_window_charger.h"
#include "app_window_lowpower.h"
#include "ota_updata.h"

#include "picture.h"
#include "language.h"
#include "data_common.h"
#include "application.h"
#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

/*-----------------------------本地逻辑处理--------------------------------------*/

static unsigned char app_window_lowpower_is_in_ota(app_battery_info_struct *batt_info)
{
    if (batt_info->charger && (SYS_MODE_NORMAL_TYPE == get_system_mode()))
    {
        if (!ota_check())
        {
            application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_charger, NULL);
        }
        return 1;
    }
    return 0;
}

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_lowpower_charger_handler(void *buf)
{
    app_battery_info_struct *batt_info = application_get_battery_info();
    if (app_window_lowpower_is_in_ota(batt_info))
        return;
    app_window_lowpower_show_image(batt_info);
    app_window_lowpower_show_text(batt_info);
    gui_surface_commit();
}

static void app_window_lowpower_act_handler(void *buf)
{
    if (SYS_MODE_NORMAL_TYPE == get_system_mode())
    {
        application_close_act_timer(APPLICATION_TIMER_ACT);
        gui_window_go_back();
    }
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_lowpower_init(void *buf)
{
}

static void app_window_lowpower_load(void *buf)
{
    app_battery_info_struct *batt_info = application_get_battery_info();
    app_window_lowpower_show_text(batt_info);
}

static void app_window_lowpower_entry(void *buf)
{
}

static void app_window_lowpower_exit()
{
}

static void app_window_lowpower_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_lowpower_static_events[] =
    {
        {
            .id = EVENT_BATTERY_CHARGER,
            .handler = app_window_lowpower_charger_handler,
        },
        {
            .id = EVENT_ACT,
            .handler = app_window_lowpower_act_handler,
        },
};

static const gui_window_config_struct app_window_low_power_config =
    {
        .disable_go_home = 1,
};

const gui_window_struct app_window_lowpower =
    {
        .screen = &gui_screen_lowpower,
        .config = &app_window_low_power_config,

        .init = app_window_lowpower_init,
        .load = app_window_lowpower_load,
        .entry = app_window_lowpower_entry,
        .exit = app_window_lowpower_exit,
        .destroy = app_window_lowpower_destroy,

        .event_num = countof(app_window_lowpower_static_events),
        .events = app_window_lowpower_static_events,
};
