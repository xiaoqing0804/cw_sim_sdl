
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"

#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#include "data_manager_contact.h"
#endif

#include "srv_call.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_base.h"

#include "application_config_main_window.h"
#include "application_titlebar.h"

#include "app_call/app_window_call.h"

#include "app_window_call_reply_layout.h"
#include "app_window_call_reply.h"

/*-----------------------------主流程--------------------------------------*/
static void app_window_call_reply_init(void *buf)
{
}

static void app_window_call_reply_load(void *buf)
{
	application_titlebar_create(&app_call_reply_screen, STRING_TELEPHONE);
}

static void app_window_call_reply_entry(void *buf)
{
}

static void app_window_call_reply_exit()
{
}

static void app_window_call_reply_destroy(void)
{
}

/*-----------------------------响应事件--------------------------------------*/

static void app_window_call_reply_push_click_handler(gui_click_struct *click)
{
    if (click->id == REPLY_TYPE_ID_1)
        g_sms_reply_index = 1;
    else if (click->id == REPLY_TYPE_ID_2)
        g_sms_reply_index = 2;
    else if (click->id == REPLY_TYPE_ID_3)
        g_sms_reply_index = 3;
    else if (click->id == REPLY_TYPE_ID_4)
        g_sms_reply_index = 4;
    else if (click->id == REPLY_TYPE_ID_5)
        g_sms_reply_index = 5;

    SYS_DEBUG("g_sms_reply_index =%d", g_sms_reply_index);
    push_data_type_to_queue(DATA_TYPE_SMS_REPLY);
    call_control_handler(CALL_CMD_HANGUP_CALL);

#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_CALL_OFF, NULL, 0);
#endif

    application_goto_main();
}

static const gui_touch_event_struct app_window_call_reply_touch_events[] =
    {
        {
            .id = REPLY_TYPE_ID_1,
            .click = app_window_call_reply_push_click_handler,
        },
        {
            .id = REPLY_TYPE_ID_2,
            .click = app_window_call_reply_push_click_handler,
        },
        {
            .id = REPLY_TYPE_ID_3,
            .click = app_window_call_reply_push_click_handler,
        },
        {
            .id = REPLY_TYPE_ID_4,
            .click = app_window_call_reply_push_click_handler,
        },
        {
            .id = REPLY_TYPE_ID_5,
            .click = app_window_call_reply_push_click_handler,
        },
};

/*-----------------------------系统配置--------------------------------------*/
static const app_window_event_struct app_window_call_comming_events[] =
    {

        {
            .id = EVENT_BTAUD_STATUS,
        },
        {
            .id = EVENT_BTAUD_CALL,
        },
};

const gui_window_struct app_window_call_reply =
    {
        .screen = &app_call_reply_screen,

        .init = app_window_call_reply_init,
        .load = app_window_call_reply_load,
        .entry = app_window_call_reply_entry,
        .exit = app_window_call_reply_exit,
        .destroy = app_window_call_reply_destroy,

        .touch_event_num = countof(app_window_call_reply_touch_events),
        .touch_events = app_window_call_reply_touch_events,

        .event_num = countof(app_window_call_comming_events),
        .events = app_window_call_comming_events,
};
