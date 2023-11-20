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

#include "system_util_math_geometry.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_base.h"

#include "application_config_main_window.h"

#include "app_call/app_window_call.h"

#include "app_window_call_dial_layout.h"
#include "app_window_call_dial_ui.h"
#include "app_window_call_dial.h"

static unsigned char m_call_dial_flag = 0;

/*-----------------------------主流程--------------------------------------*/
static void app_window_call_dial_init(void *buf)
{
    memset(AU_call_num, 0, sizeof(AU_call_num));

#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_STATUS, NULL, 0);
#endif
}

static void app_window_call_dial_load(void *buf)
{
    app_input_number_estimate();
}

static void app_window_call_dial_entry(void *buf)
{
}

static void app_window_call_dial_exit()
{
}

static void app_window_call_dial_destroy(void)
{
}

/*-----------------------------响应事件--------------------------------------*/

static void app_window_call_dial_pad_click_handler(gui_click_struct *click)
{
    app_window_call_dial_pad_click_handler_function(click->x, click->y);
}

static void app_window_ble_status(void *buf)
{
#if defined(__EXT_BT_AUDIO__)
    app_window_ble_status_function_invoking();
    gui_surface_commit();
#endif
}

/*-----------------------------系统配置--------------------------------------*/
static const gui_touch_event_struct app_window_call_dial_touch_events[] =
    {
        {.id = CALL_DIAL_PAD_ID,     .click = app_window_call_dial_pad_click_handler,     .offset_top = 27,     .offset_left = 30    },
        {.id = CALL_DIAL_DEL_ID,     .click = app_window_call_dial_del_click_handler}
};

static const app_window_event_struct app_window_call_dial_events[] =
    {
        {.id = EVENT_BTAUD_STATUS, .handler = app_window_ble_status},
};

const gui_window_struct app_window_call_dial =
    {
        .screen = &app_call_dial_screen,

        .init = app_window_call_dial_init,
        .load = app_window_call_dial_load,
        .entry = app_window_call_dial_entry,
        .exit = app_window_call_dial_exit,
        .destroy = app_window_call_dial_destroy,

        .touch_event_num = countof(app_window_call_dial_touch_events),
        .touch_events = app_window_call_dial_touch_events,

        .event_num = countof(app_window_call_dial_events),
        .events = app_window_call_dial_events,
};
