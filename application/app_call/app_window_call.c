
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"

#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "data_manager_message.h"

#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#include "data_manager_contact.h"
#endif

#include "srv_call.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_base.h"

#include "application_config_main_window.h"

#include "app_window_call.h"
#include "app_window_call_layout.h"
#include "app_window_call_ui.h"

/*-----------------------------主流程--------------------------------------*/
static void app_window_call_init(void *buf)
{
}

static void app_window_call_load(void *buf)
{
    app_call_info_function();
}

static void app_window_call_entry(void *buf)
{
    if (srv_call_get_info(0) == NULL)
    {
        application_send_event(EVENT_GO_BACK, NULL);
        return;
    }
    g_call_comming_flag = 1; // set call comming.

    send_motor_msg(MOTOR_MSG_CALLING);
    application_open_act_timer(APPLICATION_TIMER_ACT, 60 * 1000);
    application_open_act_timer(APPLICATION_TIMER_ACT_1, 1 * 1000); // the call cancel timer,1S.
}

static void app_window_call_exit()
{
    g_call_comming_flag = 0; // clear call comming.
    close_motor_msg();

    application_close_act_timer(APPLICATION_TIMER_ACT);
    application_close_act_timer(APPLICATION_TIMER_ACT_1);
}

static void app_window_call_destroy(void)
{
}

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_call_ble_status(void *buf)
{
    application_go_back();
}

static void app_window_call_timer_handler(void *buf)
{
    unsigned int timer_index = *((unsigned int *)buf);

    if (timer_index == APPLICATION_TIMER_ACT)
    {
        application_go_back();
    }
    else if (timer_index == APPLICATION_TIMER_ACT_1)
    {
        /* if call has cancel, so delete window, maybe call has cancel,
        ** but the call incoming event has active, so it must delete this event.
        */
        if (0 == get_call_flag())
        {
            application_go_back();
        }
    }
    if (srv_call_get_info(0) == NULL)
    {
        application_send_event(EVENT_GO_BACK, NULL);
        return;
    }
}

static void app_window_call_cmd_event_handler(void *buf)
{
    if (0 == get_call_flag())
    {
        application_go_back();
    }
}

static void app_window_call_key_handler(void *buf)
{

    application_go_back();
}

static void app_window_call_hangup_click_handler(gui_click_struct *click)
{
    call_control_handler(CALL_CMD_HANGUP_CALL);
    application_go_back();
}

static void app_window_call_reply_click_handler(gui_click_struct *click)
{

    application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_call_reply, NULL);
}

/*-----------------------------系统配置--------------------------------------*/
static const gui_touch_event_struct app_window_call_touch_events[] =
    {
        {
            .id = CALL_HANGUP,
            .click = app_window_call_hangup_click_handler,
        },

        {
            .id = CALL_REPLY,
            .click = app_window_call_reply_click_handler,
            .offset_top = 20,
        },
};

static const app_window_event_struct app_window_call_events[] =
    {
        {
            .id = EVENT_BLE_CONNECT_STATUS,
            .handler = app_window_call_ble_status,
        },
        {
            .id = EVENT_ACT,
            .handler = app_window_call_timer_handler,
        },
        {
            .id = EVENT_CALL_CMD,
            .handler = app_window_call_cmd_event_handler,
        },
        {
            .id = EVENT_KEY1_SHORT,
            .handler = app_window_call_key_handler,
        },
        {
            .id = EVENT_BL_TIMEOUT,
            .handler = NULL,
        },
        {
            .id = EVENT_MESSAGE,
            .handler = NULL,
        },
        {
            .id = EVENT_APP_SPORT,
            .handler = NULL,
        },
};

const gui_window_struct app_window_call =
    {
        .screen = &app_call_screen,

        .init = app_window_call_init,
        .load = app_window_call_load,
        .entry = app_window_call_entry,
        .exit = app_window_call_exit,
        .destroy = app_window_call_destroy,

        .touch_event_num = countof(app_window_call_touch_events),
        .touch_events = app_window_call_touch_events,

        .event_num = countof(app_window_call_events),
        .events = app_window_call_events,
};
