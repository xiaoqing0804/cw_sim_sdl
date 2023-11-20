#include "string.h"
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

#include "app_call/app_window_call.h"
#include "app_window_call_comming_layout.h"
#include "app_window_call_comming_ui.h"
#include "app_window_call_comming.h"

static unsigned char m_act_1_flag = 0;

/*-----------------------------主流程--------------------------------------*/
static void app_window_call_comming_init(void *buf)
{
}

static void app_window_call_comming_load()
{
    app_window_call_number();
}

static void app_window_call_comming_entry()
{
    srv_call_info *call = srv_call_get_info(0);
    if (call == NULL)
    {
        application_send_event(EVENT_GO_BACK, NULL);
        return;
    }

    m_act_1_flag = 0;
    application_open_act_timer(APPLICATION_TIMER_ACT, 200); // the call act.
    send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
}

static void app_window_call_comming_exit()
{
    m_act_1_flag = 0;

    close_motor_msg();
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_call_comming_destroy(void)
{
}

static void app_window_call_comming_handler(void *buf)
{
    app_window_call_number();
    gui_surface_commit();
}

static void app_window_call_handler(void *buf)
{
    app_window_call_number();
    gui_surface_commit();

    if (srv_call_get_lines_count() == 0)
    {
        application_go_back();
    }

#if defined(__EXT_BT_AUDIO__)
    if (ext_btaud_status_get()->call_status == 3)
    {
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_call_outgoing, NULL);
    }
#endif
}

static void app_window_call_comming_timer_act(void *buf)
{
    app_window_call_number();
    gui_surface_commit();

    if (srv_call_get_lines_count() == 0)
    {
        application_go_back();
    }

    if (m_act_1_flag++ > 245)
        m_act_1_flag = 245;

#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_STATUS, NULL, 0);
#endif
}

static void app_window_call_comming_timer_handler(void *buf)
{

#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_STATUS, NULL, 0);
    if (ext_btaud_status_get()->call_status == 3)
    {
        // accepted
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_call_outgoing, NULL);
    }
#endif
}

static void app_window_call_comming_key_handler(void *buf)
{
#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_CALL_OFF, NULL, 0);
#endif
    application_go_back();
}

static void app_window_call_comming_reject_click_handler(gui_click_struct *click)
{
    m_act_1_flag = 20;

#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_CALL_OFF, NULL, 0);
#endif
    application_go_back();
}

static void app_window_call_comming_accept_click_handler(gui_click_struct *click)
{
#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_CALL_ANSWER, NULL, 0);
#endif

    application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_call_outgoing, NULL);
}

static void app_window_call_comming_reply_click_handler(gui_click_struct *click)
{
    m_act_1_flag = 20;

    if (!g_phone_type)
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_call_reply, NULL);
    else
        application_go_back();
}

/*-----------------------------系统配置--------------------------------------*/
static const gui_touch_event_struct app_window_call_comming_touch_events[] =
    {
        {
            .id = CALL_ING_REJECT,
            .click = app_window_call_comming_reject_click_handler,
            .offset_top = 30,
            .offset_left = 30,
        },
        {
            .id = CALL_ING_ACCEPT,
            .click = app_window_call_comming_accept_click_handler,
            .offset_top = 30,
            .offset_left = 30,
        },
        {
            .id = CALL_ING_REPLY,
            .click = app_window_call_comming_reply_click_handler,
            .offset_top = 30,
        },
};

static const app_window_event_struct app_window_call_comming_events[] =
    {
        {.id = EVENT_BTAUD_STATUS, .handler = app_window_call_comming_handler},
        {.id = EVENT_BTAUD_CALL, .handler = app_window_call_comming_timer_handler},
        {.id = EVENT_CALL, .handler = app_window_call_handler},
        {.id = EVENT_ACT, .handler = app_window_call_comming_timer_act},
        {.id = EVENT_KEY1_SHORT, .handler = app_window_call_comming_key_handler},
        {.id = EVENT_CALL_CMD, .handler = NULL},
        {.id = EVENT_BL_TIMEOUT, .handler = NULL},
        {.id = EVENT_MESSAGE, .handler = NULL},
};

const gui_window_struct app_window_call_comming =
    {
        .screen = &app_call_comming_screen,

        .init = app_window_call_comming_init,
        .load = app_window_call_comming_load,
        .entry = app_window_call_comming_entry,
        .exit = app_window_call_comming_exit,
        .destroy = app_window_call_comming_destroy,

        .touch_event_num = countof(app_window_call_comming_touch_events),
        .touch_events = app_window_call_comming_touch_events,

        .event_num = countof(app_window_call_comming_events),
        .events = app_window_call_comming_events,
};
