
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "app_task_main.h"

#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "data_manager_sensor.h"
#include "data_receive_package.h"

#include "application_titlebar.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"
#include "application.h"

#include "app_window_bp.h"
#include "app_window_bp_measur.h"
#include "app_window_bp_layout.h"

#include "app_widget/app_window_widget_delete.h"
#include "app_weather/app_window_wear.h"
#include "get_data.h"

unsigned char bp_meas_spb_value = 0;
unsigned char bp_meas_dpb_value = 0;

// 0: idle;  1: starting; 2: measuring; 3: no wear
static unsigned char bp_info_status = 0;
static unsigned char bp_tick_count;
static unsigned char bp_touch = 0;

static void app_bp_start_measure(void)
{
    if (bp_info_status == 0)
    {
        bp_info_status = 1;
        bp_meas_spb_value = get_hr_result()->bp_sbp;
        bp_meas_dpb_value = get_hr_result()->bp_dbp;
        bp_tick_count = 0;
        bp_touch = 0;
        bp_set_real_mode(true);
        SYS_DEBUG("motor1");
        send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
        application_open_act_timer(APPLICATION_TIMER_ACT, 500);
        application_close_act_timer(APPLICATION_TIMER_ACT_1);

        ui_bp_value_ready_updata();
    }
}

static void app_bp_stop_measure(void)
{
    if (bp_info_status != 0)
    {
        bp_info_status = 0;
        bp_touch = 1;
        /* stop hr real mode. */
        bp_set_real_mode(false);
        SYS_DEBUG("motor2");
        send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
        hr_control_handler(HR_CONTROL_TYPE_HR, 0);
        application_close_act_timer(APPLICATION_TIMER_ACT);

        ui_bp_value_start_updata(bp_meas_spb_value,bp_meas_dpb_value);
    }
}

static void app_window_bp_init(void *buf)
{
    bp_info_status = 0;
}
static void app_window_bp_load(void *buf)
{

    ui_bp_value_start_updata(bp_meas_spb_value,bp_meas_dpb_value);

}

static void app_window_bp_entry(void *buf)
{
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_bp);
    gui_surface_layout_scrollview_switch_to_y(surface, 0);
    bp_touch = 1;
    application_open_act_timer(APPLICATION_TIMER_ACT, 3000);

}


static void app_window_bp_exit()
{
    bp_set_real_mode(false);
    if (bp_info_status != 0)
    {
        bp_info_status = 0;
        bp_touch = 1;
    }
    SYS_DEBUG("motor2");
    hr_control_handler(HR_CONTROL_TYPE_HR, 0);
    application_close_act_timer(APPLICATION_TIMER_ACT);
    gui_surface_control_animation_stop(&gui_screen_bp, BP_BOX_ANI_IMAGE_ID);

}

static void app_window_bp_destroy()
{
}

static void app_window_BP_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_bp);

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

/*-----------------------------配置--------------------------------------*/
 static void app_window_BP_long_touch_handler(gui_click_struct *event)
{
    /*
     SYS_DEBUG("window_breath_set_touch longpress");
     if (is_exist_widget_app(APP_INFO_ID_BLOOD))
     {
         application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_BLOOD);
     }
     */
 }

static void app_window_bp_acttimer_handler(void *buf)
{
    gui_box_struct *box_sbp;
    gui_box_struct *box_dbp;
    SYS_DEBUG("hr act");
    if (APPLICATION_TIMER_ACT == *((unsigned int *)buf))
    {
        if (bp_info_status == 0)
        {
            // 3s auto start
            app_bp_start_measure();
            gui_surface_commit();
        }
        else if (bp_info_status == 1)
        {
            // start: blink ---
            ui_bp_value_ready_updata();
        }
        else if (bp_info_status == 2)
        {
            // measure
            bp_tick_count++;
            box_sbp = gui_surface_get_box(&gui_screen_bp, BP_SBP_CHART);
            if (box_sbp != NULL)
                gui_surface_control_chart_reload(box_sbp);
            box_dbp = gui_surface_get_box(&gui_screen_bp, BP_DBP_CHART);
            if (box_dbp != NULL)
                gui_surface_control_chart_reload(box_dbp);
            if (bp_tick_count >= 20)
            {
                BP_item_struct bp_info = {0};
                unsigned int sec = sys_sec_get();
                int_to_char(sec, bp_info.time, sizeof(bp_info.time));
                bp_info.bp_dbp = bp_meas_dpb_value;
                bp_info.bp_sbp = bp_meas_spb_value;
                block_save_sensor_item(DATA_TYPE_REAL_BP, (unsigned char *)&bp_info);

                // measure compeleted!!!!
                app_bp_stop_measure();
                application_open_act_timer(APPLICATION_TIMER_ACT_1, 10000); // 3s exit
            }
            gui_surface_commit();
        }
        else if (bp_info_status == 3)
        {
            // not wear
            application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_wear, NULL);
            bp_tick_count++;
            if (bp_tick_count >= 30)
            {
                app_bp_stop_measure();
                application_open_act_timer(APPLICATION_TIMER_ACT_1, 10000); // 3s exit
            }
            gui_surface_commit();
        }
    }
    else if (APPLICATION_TIMER_ACT_1 == *((unsigned int *)buf))
    {
        application_close_act_timer(APPLICATION_TIMER_ACT_1);
        application_goto_main();
    }
}

static void app_window_bp_value_handler(void *buf)
{
    gui_box_struct *box;
    char temp[40];

    SYS_DEBUG("hr: measure handler bp_info_status = %d mmmmmmmmmmmmmmmmmmmmmmmm", bp_info_status);

    if (bp_info_status != 2)
    {
        bp_info_status = 2;
        bp_tick_count = 0; // reset tick, count up to 20, then measure completed.
    }

    gui_surface_control_animation_stop(&gui_screen_bp, BP_BOX_ANI_IMAGE_ID);

    bp_meas_spb_value = get_hr_result()->bp_sbp;
    bp_meas_dpb_value = get_hr_result()->bp_dbp;

    ui_bp_value_messung_updata(bp_meas_spb_value,bp_meas_dpb_value);

    box = gui_surface_get_box(&gui_screen_bp, BP_SBP_CHART);
    if (box != NULL)
        gui_surface_control_chart_reload(box);
    box = gui_surface_get_box(&gui_screen_bp, BP_DBP_CHART);
    if (box != NULL)
        gui_surface_control_chart_reload(box);
    gui_surface_commit();
}

static void app_window_bp_touch_handler(void *buf)
{
    SYS_DEBUG("hr: touch handler bp_info_status = %d tttttttttttttttttttttttttt", bp_info_status);
    if (bp_info_status != 3)
    {
        bp_info_status = 3;
        bp_tick_count = 0; // reset tick, count up to 20, then measure completed.
        gui_surface_commit();
    }

    // pop no wear window.
}

static void app_window_BP_cmd_event_BP(void *buf)
{
    SYS_DEBUG("app_window_O2_cmd_event_O2 =%d, g_phone_type=%d", g_app_heart_cmd_flag, g_phone_type);
    if (0 == g_app_heart_cmd_flag)
    {
        application_go_back();
    }
    else
    {
        app_bp_start_measure();
    }
}

static const app_window_event_struct app_window_bp_static_events[] =
    {
        {.id = EVENT_ROLKEY, .handler = app_window_BP_rolkey_handler},

        {.id = EVENT_ACT, .handler = app_window_bp_acttimer_handler},
        {.id = EVENT_REAL_HEART, .handler = app_window_bp_value_handler},
        {.id = EVENT_HEART_TOUCH, .handler = app_window_bp_touch_handler},
        {.id = EVENT_BL_TIMEOUT},
        {.id = EVENT_GO_HOME},
        {
            .id = EVENT_BP_CMD,
            .handler = app_window_BP_cmd_event_BP,
        },
};

static void app_window_bp_touch(gui_click_struct *envent)
{
    if (bp_touch == 1)
    {
        bp_info_status = 0;
        bp_tick_count = 0;
        bp_touch = 0;
        application_open_act_timer(APPLICATION_TIMER_ACT, 1);
        application_close_act_timer(APPLICATION_TIMER_ACT_1);
    }
};

static const gui_touch_event_struct app_window_bp_touch_events[] =
    {
        {
            .id = BP_BG_ID,
            .click = app_window_bp_touch,
        },

        {
            .id = BP_BOX_ANI_RESET_ID,
            .click = app_window_bp_touch,
        },

        {
            .id = 0xFFFF, // fullscreen.
            .long_touch = app_window_BP_long_touch_handler,
        },
};

const gui_window_struct app_window_bp =
    {
        .screen = &gui_screen_bp,

        .init = app_window_bp_init,
        .load = app_window_bp_load,
        .entry = app_window_bp_entry,
        .exit = app_window_bp_exit,
        .destroy = app_window_bp_destroy,

        .touch_event_num = countof(app_window_bp_touch_events),
        .touch_events = app_window_bp_touch_events,

        .event_num = countof(app_window_bp_static_events),
        .events = app_window_bp_static_events,

};
