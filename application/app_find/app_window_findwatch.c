#include "app_window_findwatch.h"
#include "app_window_findwatch_layout.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"

#include "bsp_includes.h"


#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "application_config_main_window.h"




#define UI_PI		3.14159265358979f


#if defined(__EXT_BT_AUDIO__)
#define FIND_AUD_IDLE     0
#define FIND_AUD_MUSIC    1
#define FIND_AUD_MIC      2
static unsigned int  g_find_phone_music;     // 0: idle; 1: music play test;  2: mic-spk loop test;
#endif

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_findwatch_init(void *buf)
{
}

static void app_window_findwatch_load(void *buf)
{
}

static void app_window_findwatch_entry(void *buf)
{
	send_motor_msg(MOTOR_MSG_ONOFF);
	application_open_act_timer(APPLICATION_TIMER_ACT, 10*1000);
	#if defined(__EXT_BT_AUDIO__)
    	g_find_phone_music = FIND_AUD_MUSIC;
		ext_btaud_test_speaker_music(1);
    	application_open_act_timer(APPLICATION_TIMER_ACT_1, 5000);
	#endif
}

static void app_window_findwatch_exit()
{
	close_motor_msg();
    application_close_act_timer(APPLICATION_TIMER_ACT);
	application_close_act_timer(APPLICATION_TIMER_ACT_1);
	#if defined(__EXT_BT_AUDIO__)
    	application_close_act_timer(APPLICATION_TIMER_ACT);

    	if (g_find_phone_music == FIND_AUD_MUSIC) {
        	ext_btaud_test_speaker_music(0);
    	}
    	else if (g_find_phone_music == FIND_AUD_MIC) {
        	ext_btaud_test_speaker_mic(0);
    	}
    	g_find_phone_music = FIND_AUD_IDLE;
	#endif
}

static void app_window_findwatch_destroy(void)
{
}

static void app_window_findwatch_ble_status(void* buf)
{
    application_go_back();
}

static void app_window_findwatch_timer_handler(void* buf)
{
  	if (APPLICATION_TIMER_ACT == *((unsigned int*)buf))
	{
		application_go_back();
	}
	else if(APPLICATION_TIMER_ACT_1 == *((unsigned int*)buf))
	{
		if (g_find_phone_music == FIND_AUD_MUSIC)
		{
			ext_btaud_test_speaker_music(1);
		}

	}
}

/*-----------------------------����--------------------------------------*/

static const app_window_event_struct app_window_findwatch_events[] =
{
    {
        .id = EVENT_BLE_CONNECT_STATUS,
        .handler = app_window_findwatch_ble_status,
    },
    {
        .id = EVENT_ACT,
        .handler = app_window_findwatch_timer_handler,
    },
    {
        .id = EVENT_BL_TIMEOUT,
        .handler = NULL,
    },
};


const gui_window_struct app_window_findwatch =
{
	.screen = &app_find_screen,

	.init = app_window_findwatch_init,
	.load = app_window_findwatch_load,
	.entry = app_window_findwatch_entry,
	.exit = app_window_findwatch_exit,
	.destroy = app_window_findwatch_destroy,

	.event_num = countof(app_window_findwatch_events),
	.events = app_window_findwatch_events,
};




