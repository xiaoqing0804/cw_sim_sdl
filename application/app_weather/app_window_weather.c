#include "app_window_weather.h"
#include "app_window_weather_layout.h"
#include "app_window_weather_ui.h"
#include "data_weather.h"
#include "data_datetime.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "gui_window.h"

#include "data_common.h"
#include "debug_info.h"

#include "application_titlebar.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#include "app_widget/app_window_widget_delete.h"

/*-----------------------------本地逻辑处理--------------------------------------*/

static void app_window_weather_show()
{
    unsigned int day_index;
    weather_info_item_struct *weather_info = data_weather_get_now_weather_info(&day_index);
    if (weather_info == NULL) // no weather
    {
        app_window_weather_ui_show_empty_page();
    }
    else
    {
        app_window_weather_ui_show_data_page();
        app_window_weather_ui_update_data(weather_info, day_index);
    }
}

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_weather_update_handler(void *buf)
{
    app_window_weather_show();
    gui_surface_commit();
}

static void app_window_weather_long_touch_handler(gui_click_struct *event)
{
    if (is_exist_widget_app(APP_INFO_ID_WEATHER))
    {
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_WEATHER);
    }
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_weather_init(void *buf)
{
}

static void app_window_weather_load(void *buf)
{
    app_window_weather_show();
}

static void app_window_weather_entry(void *buf)
{
}

static void app_window_weather_exit()
{
}

static void app_window_weather_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_weather_touch_events =
    {
        .id = 0xFFFF, // fullscreen.
        .long_touch = app_window_weather_long_touch_handler,
};

static const app_window_event_struct app_window_weather_static_events[] =
    {
        {
            .id = EVENT_UPDATE_WEATHER,
            .handler = app_window_weather_update_handler,
        },
        {
            .id = EVENT_UPDATE_SYS_TIME,
            .handler = app_window_weather_update_handler,
        },
        {
            .id = EVENT_UPDATE_UNIT_SETTING,
            .handler = app_window_weather_update_handler,
        },
};

const gui_window_struct app_window_weather =
    {
        .screen = &gui_screen_weather,

        .init = app_window_weather_init,
        .load = app_window_weather_load,
        .entry = app_window_weather_entry,
        .exit = app_window_weather_exit,
        .destroy = app_window_weather_destroy,

        .touch_event_num = 1,
        .touch_events = &app_window_weather_touch_events,

        .event_num = countof(app_window_weather_static_events),
        .events = app_window_weather_static_events,
};
