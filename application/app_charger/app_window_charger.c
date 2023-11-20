#include "app_charger/app_window_charger.h"
#include "app_charger/app_window_charger_ui.h"
#include "app_charger/app_window_charger_layout.h"

#include "app_config.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "gui_surface_control_base.h"
#include "app_ota/app_window_ota.h"

#include "app_main/app_window_main_watchface_update.h"

/*----------------------------------事件及触屏---------------------------------------------*/
static void app_window_charger_charger_handler(void* buf)
{
	//SYS_DEBUG("app_window_charger_charger_handler");

    app_battery_info_struct* batt_info = (app_battery_info_struct*)buf;
    if (batt_info->charger == 0) {
        application_go_back();
        return;
    }
     app_window_charger_load_ui_show();

}

static void app_window_charger_on_resumed(void* buf)
{

}

static void app_window_ota_handler(void* buf)
{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_ota, NULL);
    app_window_charger_load_ui_show();
}

static void app_window_update_watchface_handler(void* buf)

{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_main_watchface_update, NULL);
}


/*-----------------------------系统流程--------------------------------------*/

static void app_window_charger_init(void *buf)
{
}

static void app_window_charger_load()
{
   app_window_charger_load_ui_show();
}
static void app_window_charger_entry()
{

    app_battery_info_struct* batt_info = application_get_battery_info();
    if (batt_info->charger) {
    #if defined(TCFG_APP_PC_EN)&&TCFG_APP_PC_EN
        application_open_act_timer(APPLICATION_TIMER_ACT, 3000);
    #endif
    }
    else {
        application_send_event(EVENT_GO_BACK, NULL);
    }
}


static void app_window_charger_exit()
{
}

static void app_window_charger_destroy()
{
}


/*-----------------------------触屏事件--------------------------------------*/
static const app_window_event_struct app_window_charger_static_events[] =
{
	{
		.id = EVENT_BATTERY_CHARGER,
		.handler = app_window_charger_charger_handler,
	},
	{
        .id = EVENT_OTA,
        .handler = app_window_ota_handler,
    },
    {
        .id = EVENT_UPDATE_WATCHFACE,
        .handler = app_window_update_watchface_handler,
    },
    {
        .id = EVENT_GUI_RESUMED,
        .handler = app_window_charger_on_resumed,
    },
#if defined(TCFG_APP_PC_EN)&&TCFG_APP_PC_EN
    {.id = EVENT_ACT,           .handler = app_window_charger_on_timer},
    {.id = EVENT_USB_OFFLINE,   .handler = app_window_mass_usb_offline},
#endif
    {
        .id = EVENT_ALL,
        .handler = NULL,
    }


};

static const gui_window_config_struct app_window_charger_config =
{
	.forbid_gesture_back = 1,
	.forbid_key_back = 1,
	.enable_touch = 1,
};



const gui_window_struct app_window_charger =
{
	.screen = &gui_charger_screen,
	.config = &app_window_charger_config,


	.init = app_window_charger_init,
	.load = app_window_charger_load,
	.entry = app_window_charger_entry,
	.exit = app_window_charger_exit,
	.destroy = app_window_charger_destroy,

    .event_num = countof(app_window_charger_static_events),
    .events = app_window_charger_static_events,

#if defined(TCFG_APP_PC_EN)&&TCFG_APP_PC_EN
    .touch_event_num = countof(app_window_charger_touch_events),
    .touch_events = app_window_charger_touch_events,
#endif
};




