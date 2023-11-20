#include "app_window_findphone.h"
#include "app_window_findphone_ui.h"
#include "app_window_findphone_layout.h"

#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "bt_module.h"			// iPhone14查找手机死机问题

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"


#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_animation.h"
#include "application_config_main_window.h"



#define UI_PI		3.14159265358979f


/*-----------------------------ϵͳ�¼�--------------------------------------*/
static unsigned char g_timer_counter;
static unsigned char btaud_status = 0;

static void app_window_findphone_init(void *buf)
{
    g_timer_counter = 0;
}

static void app_window_findphone_load(void *buf)
{
  app_window_findphone_ui_show();
}

static void app_window_findphone_entry(void *buf)
{

    if (0 == get_ble_appconnect()) {
    }
    else {
        application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
    }
}

static void app_window_findphone_exit()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
    if(get_ble_appconnect() > 0)
    {
        find_phone(0);
    #if defined(__EXT_BT_AUDIO__)
        if ((btaud_status) && (ext_btaud_onoff_get()>0))
        {
            if (!bt_mod_get_a2dp_state()) {
                bt_mod_a2dp_open_and_close();    // ext_btaud_onoff_set(1);
            }
        }
        btaud_status = 0;
    #endif

    }
}

static void app_window_findphone_destroy(void)
{

}

static void app_window_findphone_ble_status(void* buf)
{
    app_window_findphone_ui_show();
    if (0 == get_ble_appconnect()) {
        application_close_act_timer(APPLICATION_TIMER_ACT);
    }
    else {
        application_open_act_timer(APPLICATION_TIMER_ACT, 200);
    }
}

static void app_window_findphone_timer_handler(void* buf)
{
    if (0 == get_ble_appconnect()) {
        application_close_act_timer(APPLICATION_TIMER_ACT);
    }
    else {
        if (g_timer_counter == 0) {
        #if defined(__EXT_BT_AUDIO__)
            if ((ext_btaud_onoff_get() > 0) && bt_mod_get_a2dp_state())
            {
                btaud_status = 1;
                bt_mod_a2dp_open_and_close();    // ext_btaud_onoff_set(0);
            }
        #endif
        }
        else if (g_timer_counter == 1) {
            find_phone(1);
        }

        g_timer_counter ++;
        app_window_findphone_ui_show();
        application_open_act_timer(APPLICATION_TIMER_ACT, 200);
    }
}

/*-----------------------------����--------------------------------------*/

static const app_window_event_struct app_window_findphone_events[] =
{
    {
        .id = EVENT_BLE_CONNECT_STATUS,
        .handler = app_window_findphone_ble_status,
    },
    {
        .id = EVENT_ACT,
        .handler = app_window_findphone_timer_handler,
    },
    {
        .id = EVENT_BL_TIMEOUT,
        .handler = NULL,
    },
};


const gui_window_struct app_window_findphone =
{
	.screen = &app_findphone_screen,

	.init = app_window_findphone_init,
	.load = app_window_findphone_load,
	.entry = app_window_findphone_entry,
	.exit = app_window_findphone_exit,
	.destroy = app_window_findphone_destroy,

	.event_num = countof(app_window_findphone_events),
	.events = app_window_findphone_events,
};



