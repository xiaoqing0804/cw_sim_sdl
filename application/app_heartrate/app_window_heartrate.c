#include "app_window_heartrate.h"
#include "app_window_heartrate_ui.h"
#include "app_window_heartrate_layout.h"

#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "application_titlebar.h"

#include "app_window_widget_delete.h"
#include "gui_window_swipe.h"
#include "app_window_no_wear.h"

/*-----------------------------定义--------------------------------------*/
static unsigned char g_heartrate_status = HEARTRATE_STATUS_START;
static unsigned char g_heartrate_tick_count = 0;

/*-----------------------------本地逻辑处理--------------------------------------*/

unsigned char app_window_heartrate_get_status()
{
    return g_heartrate_status;
}

static void app_window_heartrate_retry()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
    application_close_act_timer(APPLICATION_TIMER_ACT_1);

    g_heartrate_tick_count = HEARTRATE_MEASURE_TICK_TO_START - 1;
    g_heartrate_status = HEARTRATE_STATUS_START;
    app_window_heartrate_ui_show_result();

    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
    application_open_act_timer(APPLICATION_TIMER_ACT_1, HEARTRATE_MEASURE_ANI_INTERVAL);
}

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_heartrate_acttimer_handler(void *buf)
{
    gui_box_struct *box;
    if (APPLICATION_TIMER_ACT == *((unsigned int *)buf))
    {
        if (g_heartrate_status == HEARTRATE_STATUS_START)
        {
            if (++g_heartrate_tick_count > HEARTRATE_MEASURE_TICK_TIMEOUT)
                g_heartrate_tick_count = HEARTRATE_MEASURE_TICK_TIMEOUT;

            if (g_heartrate_tick_count >= HEARTRATE_MEASURE_TICK_TO_START)
            {
                if (g_heartrate_tick_count == HEARTRATE_MEASURE_TICK_TO_START)
                {
                    hr_set_real_mode(true);
                    send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
                    application_open_act_timer(APPLICATION_TIMER_ACT_1, HEARTRATE_MEASURE_ANI_INTERVAL); // 动画的定时器
                }
                app_window_heartrate_ui_show_result();
            }
            gui_surface_commit();
        }
        else if (g_heartrate_status == HEARTRATE_STATUS_RESULT)
        {
            if (++g_heartrate_tick_count > HEARTRATE_MEASURE_TICK_TIMEOUT)
                g_heartrate_tick_count = HEARTRATE_MEASURE_TICK_TIMEOUT;

            if (g_heartrate_tick_count == HEARTRATE_MEASURE_TICK_RESULT)
            {
                heart_item_struct heart_info = {0};
                unsigned int sec = sys_sec_get();
                int_to_char(sec, heart_info.time, sizeof(heart_info.time));
                heart_info.heart_nums = last_hr_result.hr;
                block_save_sensor_item(DATA_TYPE_REAL_HEART, (unsigned char *)&heart_info);

                hr_set_real_mode(false);
                send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
                hr_control_handler(HR_CONTROL_TYPE_HR, 0);
                application_close_act_timer(APPLICATION_TIMER_ACT);
                application_close_act_timer(APPLICATION_TIMER_ACT_1);
            }

            app_window_heartrate_ui_show_result();
            gui_surface_commit();
        }
    }
    else if (APPLICATION_TIMER_ACT_1 == *((unsigned int *)buf))
    {
        app_window_heartrate_ui_show_ani();
        gui_surface_commit();
    }
}

static void app_window_heartrate_measure_handler(void *buf)
{
    if (g_heartrate_status == HEARTRATE_STATUS_START)
    {
        g_heartrate_tick_count = 0;
        g_heartrate_status = HEARTRATE_STATUS_RESULT;
        app_window_heartrate_ui_show_result();
    }
}

static void app_window_heartrate_hrtouch_handler(void *buf)
{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_no_wear, NULL);
}

static void app_window_heartrate_long_touch_handler(gui_click_struct *event)
{
    SYS_DEBUG("window_heartrate_touch longpress");
    if (is_exist_widget_app(APP_INFO_ID_HR))
    {
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_HR);
    }
}

static void app_window_hr_cmd_event_hr(void *buf)
{
    if (0 == g_app_heart_cmd_flag)
        application_go_back();
    else
        app_window_heartrate_retry();
}

static void app_window_heartrate_click_handler(void *buf)
{
    if (g_heartrate_status == HEARTRATE_STATUS_RESULT)
    {
        app_window_heartrate_retry();
    }
}

static void app_window_heartrate_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    gui_surface_struct *surface = gui_surface_get_surface(&app_heartrate_screen);

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

/*-----------------------------主流程--------------------------------------*/

static void app_window_heartrate_init(void *buf)
{
}

static void app_window_heartrate_load(void *buf)
{
    g_heartrate_tick_count = 0;
    g_heartrate_status = HEARTRATE_STATUS_START;
    app_window_heartrate_ui_show();
}

static void app_window_heartrate_entry(void *buf)
{
    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}

static void app_window_heartrate_exit()
{
    hr_set_real_mode(false);
    application_close_act_timer(APPLICATION_TIMER_ACT);
    application_close_act_timer(APPLICATION_TIMER_ACT_1);
}

static void app_window_heartrate_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_heartrate_static_events[] =
    {
        {
            .id = EVENT_ACT,
            .handler = app_window_heartrate_acttimer_handler,
        },

        {
            .id = EVENT_REAL_HEART,
            .handler = app_window_heartrate_measure_handler,
        },

        {
            .id = EVENT_HEART_TOUCH,
            .handler = app_window_heartrate_hrtouch_handler,
        },
        {
            .id = EVENT_ROLKEY,
            .handler = app_window_heartrate_rolkey_handler,
        },

        {
            .id = EVENT_HR_CMD,
            .handler = app_window_hr_cmd_event_hr,
        },
        {
            .id = EVENT_BL_TIMEOUT,
        },
        {
            .id = EVENT_GO_HOME,
        },
};

static const gui_touch_event_struct app_window_heartrate_touch_events[] =
    {
        {
            .id = 0xFFFF, // fullscreen.
            .click = app_window_heartrate_click_handler,
            .long_touch = app_window_heartrate_long_touch_handler,
        },
};

const gui_window_struct app_window_heartrate =
    {
        .screen = &app_heartrate_screen,

        .init = app_window_heartrate_init,
        .load = app_window_heartrate_load,
        .entry = app_window_heartrate_entry,
        .exit = app_window_heartrate_exit,
        .destroy = app_window_heartrate_destroy,

        .touch_event_num = countof(app_window_heartrate_touch_events),
        .touch_events = app_window_heartrate_touch_events,

        .event_num = countof(app_window_heartrate_static_events),
        .events = app_window_heartrate_static_events,
};
