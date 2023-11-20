#include "app_window_o2.h"
#include "app_window_o2_ui.h"
#include "app_window_o2_layout.h"
#include "bsp_includes.h"
#include "application_config_app_info.h"
#include "app_window_widget_delete.h"
#include "gui_surface_box_image_number.h"
#include "app_window_no_wear.h"

/*-----------------------------定义--------------------------------------*/

static unsigned char g_o2_tick_count = O2_MEASURE_TICK_TOTAL;
static unsigned char g_o2_status = O2_STATUS_START;
static unsigned char g_o2_number = 0;

/*-----------------------------本地逻辑处理--------------------------------------*/

/// @brief 重新初始化“开始”数据
static void app_window_o2_reset_start()
{
    g_o2_tick_count = O2_MEASURE_TICK_TOTAL;
    g_o2_status = O2_STATUS_START;
    app_window_o2_ui_switch(g_o2_status);
    app_window_o2_ui_show_time(g_o2_tick_count);
    gui_surface_commit();
}

/// @brief 重新开始
static void app_window_o2_retry()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
    app_window_o2_reset_start();
    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_o2_acttimer_handler(void *buf)
{
    if (APPLICATION_TIMER_ACT == *((unsigned int *)buf))
    {
        if (g_o2_status == O2_STATUS_START)
        {
            g_o2_tick_count--;

            if (g_o2_tick_count == 0) // 时间到，显示血氧
            {
                g_o2_tick_count = O2_MEASURE_TICK_TOTAL; // 需要多查询一段时间血氧
                g_o2_status = O2_STATUS_RESULT;
                app_window_o2_ui_switch(g_o2_status);
                app_window_o2_ui_show_data(g_o2_number);
            }
            else if (g_o2_tick_count == O2_MEASURE_TICK_TO_START) // 几秒后自动测量血氧
            {
                O2_set_real_mode(true);
                send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
                app_window_o2_ui_show_time(g_o2_tick_count);
            }
            else
            {
                app_window_o2_ui_show_time(g_o2_tick_count);
            }
        }
        else if (g_o2_status == O2_STATUS_RESULT)
        {
            g_o2_tick_count--;
            if (g_o2_tick_count == 0) // 时间到，关闭血氧
            {
                send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
                O2_set_real_mode(false);
                application_close_act_timer(APPLICATION_TIMER_ACT);
            }
            app_window_o2_ui_show_data(g_o2_number);
        }

        gui_surface_commit();
    }
}

static void app_window_o2_measure_handler(void *buf)
{
    g_o2_number = last_hr_result.O2;
}

static void app_window_o2_hrtouch_handler(void *buf)
{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_no_wear, NULL);
}

static void app_window_o2_touch(gui_click_struct *envent)
{
    app_window_o2_retry();
}

static void app_window_O2_cmd_event_O2(void *buf)
{
    SYS_DEBUG("app_window_O2_cmd_event_O2 =%d, g_phone_type=%d", g_app_heart_cmd_flag, g_phone_type);
    if (1 == g_app_heart_cmd_flag)
    {
        app_window_o2_retry();
    }
}

static void app_window_o2_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    gui_surface_struct *surface = gui_surface_get_surface(&app_o2_screen);

    if (rolkey->rotate == ROTATE_TYPE_FORWARD)
    {
        gui_surface_layout_scrollview_switch_to_direction(surface, DIRECTION_TYPE_DOWN);
    }
    else if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
    {
        gui_surface_layout_scrollview_switch_to_direction(surface, DIRECTION_TYPE_UP);
    }
    gui_surface_commit();
}

static void app_window_o2_long_touch_handler(gui_click_struct *event)
{
    SYS_DEBUG("window_o2_touch longpress");
    if (is_exist_widget_app(APP_INFO_ID_O2))
    {
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_O2);
    }
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_o2_init(void *buf)
{
}

static void app_window_o2_load(void *buf)
{
    g_o2_number = 98;
    g_o2_tick_count = O2_MEASURE_TICK_TOTAL;
    g_o2_status = O2_STATUS_START;
    app_window_o2_ui_show(g_o2_status);
    app_window_o2_ui_show_time(g_o2_tick_count);
}

static void app_window_o2_entry(void *buf)
{
    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}

static void app_window_o2_exit()
{
    O2_set_real_mode(false);
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_o2_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_o2_static_events[] =
    {
        {
            .id = EVENT_ACT,
            .handler = app_window_o2_acttimer_handler,
        },

        {
            .id = EVENT_REAL_HEART,
            .handler = app_window_o2_measure_handler,
        },
        {
            .id = EVENT_O2_CMD,
            .handler = app_window_O2_cmd_event_O2,
        },
        {
            .id = EVENT_HEART_TOUCH,
            .handler = app_window_o2_hrtouch_handler,
        },
        {
            .id = EVENT_ROLKEY,
            .handler = app_window_o2_rolkey_handler,
        },
        {
            .id = EVENT_BL_TIMEOUT,
        },
        {
            .id = EVENT_GO_HOME,
        },
};

static const gui_touch_event_struct app_window_o2_touch_events[] =
    {
        {
            .id = O2_LAYOUT_ID_RESULT_RETRY,
            .click = app_window_o2_touch,
        },
        {
            .id = 0xFFFF, // fullscreen.
            .long_touch = app_window_o2_long_touch_handler,
        },

};

const gui_window_struct app_window_o2 =
    {
        .screen = &app_o2_screen,

        .init = app_window_o2_init,
        .load = app_window_o2_load,
        .entry = app_window_o2_entry,
        .exit = app_window_o2_exit,
        .destroy = app_window_o2_destroy,

        .touch_event_num = countof(app_window_o2_touch_events),
        .touch_events = app_window_o2_touch_events,

        .event_num = countof(app_window_o2_static_events),
        .events = app_window_o2_static_events,
};
