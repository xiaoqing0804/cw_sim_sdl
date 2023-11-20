
#include "app_window_ota.h"
#include "app_window_ota_ui.h"
#include "app_window_ota_layout.h"

#include "picture.h"
#include "language.h"
#include "debug_info.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "ota.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image_number.h"

#include "application_config_main_window.h"


static unsigned int m_ota_sec = 0;

static void app_window_ota_timer_handler(void* buf)
{
	static unsigned int save_pos = 0;
	unsigned int timer_index = *((unsigned int *)buf);
	unsigned int pos = 0, size = 0;

    ota_get_status(&size, &pos);

	if(timer_index == APPLICATION_TIMER_ACT)
	{
	    app_window_ota_ui_show(NULL);
	}
	else if(timer_index == APPLICATION_TIMER_ACT_1)
	{
		if(save_pos == pos)
		{
			//if font updata, so don't exit.
			if((pos < size)&&(0 == ota_font_updata_check()))
			{
			    application_go_back();
			}
		}
		else{
			save_pos = pos;
		}
	}
}

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_ota_init(void *buf)
{
	m_ota_sec = HAL_GetTickMS();
}

static void app_window_ota_load(void *buf)
{
    app_window_ota_ui_show();
}

static void app_window_ota_entry(void *buf)
{
    SYS_DEBUG("app_window_ota_entry()");
	application_open_act_timer(APPLICATION_TIMER_ACT, 1*1000);
	application_open_act_timer(APPLICATION_TIMER_ACT_1, 5*1000);
}

static void app_window_ota_exit()
{
    SYS_DEBUG("app_window_ota_exit()");
}

static void app_window_ota_destroy()
{
}

static void app_window_ota_ble_status(void* buf)
{
    SYS_DEBUG("app_window_main_ota_ble_status()");

	unsigned int pos = 0, size = 0;

    ota_get_status(&size, &pos);

	//if font updata, so don't exit.
	if((pos < size)&&(0 == ota_font_updata_check()))
	{
        application_go_back();
	}
}



static const app_window_event_struct app_window_ota_events[] =
{
    {
        .id = EVENT_BLE_CONNECT_STATUS,
        .handler = app_window_ota_ble_status,

    },
    {
        .id = EVENT_ACT,
        .handler = app_window_ota_timer_handler,
    },
    {
        .id = EVENT_GUI_RESUMED,
    },
    {
        .id = EVENT_BL_TIMEOUT,
    },
    {
        .id = EVENT_OTA,
    },
    {
        .id = EVENT_GO_HOME,
    },
    {
        .id = EVENT_KEY1_SHORT,
    },
    {
        .id = EVENT_BATTERY_CHARGER,
    },
    {
        .id = EVENT_ALL,
        .handler = NULL,
    }
};

static const gui_window_config_struct app_window_ota_config =
{
	.forbid_gesture_back = 1,
    .forbid_key_back     = 1,
};



const gui_window_struct app_window_ota =
{
	.screen = &app_ota_screen_layout,
    .config = &app_window_ota_config,

	.init = app_window_ota_init,
	.load = app_window_ota_load,
	.entry = app_window_ota_entry,
	.exit = app_window_ota_exit,
	.destroy = app_window_ota_destroy,

	.event_num = countof(app_window_ota_events),
	.events = app_window_ota_events,
};

