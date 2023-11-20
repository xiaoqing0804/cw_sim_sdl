
#include "debug_info.h"
#include "sys_timer.h"
#include "picture.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_receive_package.h"

#include "data_common.h"

#include "app_window_sport_data_exit.h"
#include "app_window_sport_data.h"
#include "app_window_appSport.h"
#include "app_window_appSport_layout.h"
#include "get_data.h"
#include "gui_surface_box_label.h"

static unsigned int app_sport_time_base = 0;
static unsigned int app_sport_time_start = 0;
static unsigned int app_sport_updata_time = 0;
static unsigned char m_sport_status = 0;
static unsigned char m_last_heart = 0;


static unsigned int app_sport_time_get(void)
{
	unsigned int time;

	if(0 == app_sport_time_start)
	{
		app_sport_time_start = HAL_GetTickMS();
		time = app_sport_time_base;
	}
	else{
		time = app_sport_time_base + (HAL_GetTickMS()-app_sport_time_start)/1000;
	}

	return time;
}


static void app_sport_cmd_handler(void)
{
	char_to_int(g_app_sport.time, &app_sport_time_base, 4);
	app_sport_time_start = 0;

	if((APP_SPORT_STATUS_START == g_app_sport.status)||
		(APP_SPORT_STATUS_CONTINUE == g_app_sport.status))
	{
		hr_set_sport_mode(1);
	}
	else if((APP_SPORT_STATUS_STOP == g_app_sport.status)||
		(APP_SPORT_STATUS_STOP_FORCE == g_app_sport.status)||
		(APP_SPORT_STATUS_PAUSE == g_app_sport.status))
	{
		hr_set_sport_mode(0);
	}
}

static void device_sport_cmd_handler(APP_SPORT_STATUS_TYPE status)
{
	if((APP_SPORT_STATUS_START == status)||(APP_SPORT_STATUS_CONTINUE == status))
	{
		app_sport_time_base = app_sport_time_get();
		app_sport_time_start = HAL_GetTickMS();
		hr_set_sport_mode(1);
	}
	else if(APP_SPORT_STATUS_PAUSE == status)
	{
		app_sport_time_base = app_sport_time_get();
		app_sport_time_start = 0;
		hr_set_sport_mode(0);
	}
	else if((APP_SPORT_STATUS_STOP == status)||(APP_SPORT_STATUS_STOP_FORCE == status))
	{
		hr_set_sport_mode(0);
	}

	g_app_sport_sync = g_app_sport;
	if(APP_SPORT_STATUS_SYNC == status)
	{
		/* if app sport status don't start , so don't sync request data. */
		if((APP_SPORT_STATUS_START == g_app_sport.status)||
			(APP_SPORT_STATUS_CONTINUE == g_app_sport.status))
		{
			/* if queue has data send, so don't repeat send it. */
			if(0 == check_data_type_queue_status(DATA_TYPE_APP_SPORT))
			{
				g_app_sport_sync.status = status;
				push_data_type_to_queue(DATA_TYPE_APP_SPORT);
			}
		}
	}
	else{
		g_app_sport.status = status;
		g_app_sport_sync.status = status;
		push_data_type_to_queue(DATA_TYPE_APP_SPORT);

		/* if ble has connect, so motor open, if ble disconnect, motor don't open. */
		if(get_ble_connect_flag() > 0)
		{
			/* motor event when sport status change. */
			send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
		}
	}
}

static void app_sport_updata_data(void)
{
	if(HAL_GetTickMS() >= (app_sport_updata_time+5000))
	{
		app_sport_updata_time = HAL_GetTickMS();
		device_sport_cmd_handler(APP_SPORT_STATUS_SYNC);
	}
}


void appsport_event_handler(void)
{
	/*(SPORT_STATUS_STOP == m_window_sport_status)&&*/
    if(
        ((APP_SPORT_STATUS_STOP != g_app_sport.status)&&
        (APP_SPORT_STATUS_STOP_FORCE != g_app_sport.status)))
    {
        /* handler app sport cmd. */
        app_sport_cmd_handler();

        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_appsport, NULL);
    }
}



/*-----------------------------ϵͳ�¼�--------------------------------------*/
static void app_window_appsport_update(void)
{
    gui_box_struct* box;
    unsigned int    index = 0;

    if (APP_SPORT_STATUS_PAUSE == g_app_sport.status) {
        while(1) {
            box = gui_surface_get_box_by_index(&gui_screen_appsport, index);
            if (box == NULL) {
                break;
            }
            if (box->id < APPSPORT_DATA_LAYOUT_ID_PAUSE_BASE) {
                gui_surface_box_change_visible(box, 0);
            }
            else {
                gui_surface_box_change_visible(box, 1);
            }
            index ++;
        }
    }
    else {
        while(1) {
            box = gui_surface_get_box_by_index(&gui_screen_appsport, index);
            if (box == NULL) {
                break;
            }
            if (box->id < APPSPORT_DATA_LAYOUT_ID_PAUSE_BASE) {
                gui_surface_box_change_visible(box, 1);
            }
            else {
                gui_surface_box_change_visible(box, 0);
            }
            index ++;
        }
    }
}



static void app_window_appsport_update_data(void)
{
	static unsigned int sys_sec = 0, distance = 0, heart = 0;
	char temp[40];
    gui_box_struct* box;

    app_sport_updata_data();

    sys_sec = app_sport_time_get();
    char_to_int(g_app_sport.distance, &distance, 4);
    heart = get_hr_result()->hr;

    /// time
    box = gui_surface_get_box(&gui_screen_appsport, APPSPORT_DATA_LAYOUT_ID_TIME);
    if (box != NULL) {
    	snprintf(temp, sizeof(temp),"%02d:%02d:%02d", sys_sec/3600, (sys_sec/60)%60, sys_sec%60);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }

    box = gui_surface_get_box(&gui_screen_appsport, APPSPORT_DATA_LAYOUT_ID_KM_TEXT);
    if (box != NULL) {
        /* display distance. */
        if(g_unit_setting.select.bit.distance)
        {
            //1mile = 1609.3m , mile
            snprintf(temp, sizeof(temp), "%d.%d", distance*10/16093, (distance*10*10)/16093%10);
			//ICOM.....
        }
        else{ //km
            snprintf(temp, sizeof(temp), "%d.%d", distance/1000, (distance/100)%10);
        }
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }

    box = gui_surface_get_box(&gui_screen_appsport, APPSPORT_DATA_LAYOUT_ID_BPM_TEXT);
    if (box != NULL) {
        if(heart > 0)
        {
            m_last_heart = heart;
        }
        if(m_last_heart > 0)
        {
            snprintf(temp, sizeof(temp),"%03d", m_last_heart);
        }
        else{
            snprintf(temp, sizeof(temp),"--");
        }
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
}

static void app_window_appsport_init(void *buf)
{
}

static void app_window_appsport_load(void *buf)
{
    app_window_appsport_update_data();
    app_window_appsport_update();
}


static void app_window_appsport_entry(void *buf)
{
	m_sport_status = g_app_sport.status;
	m_last_heart = 0;
	application_open_act_timer(APPLICATION_TIMER_ACT, 500);
	/* if app sport start, so motor open, if ble reconnect, so motor don't open. */
	if(app_sport_time_get() < 3)
	{
		send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
	}

	if((APP_SPORT_STATUS_START == g_app_sport.status)||
		(APP_SPORT_STATUS_CONTINUE == g_app_sport.status))
	{
		hr_set_sport_mode(1);
	}
}


static void app_window_appsport_exit()
{
	if((APP_SPORT_STATUS_STOP == g_app_sport.status)||
		(APP_SPORT_STATUS_STOP_FORCE == g_app_sport.status))
	{
	}
	app_sport_updata_time = 0;
	hr_set_sport_mode(0);
}

static void app_window_appsport_destroy()
{

}



/*-----------------------------��Ӧ�¼�--------------------------------------*/
/*-----------------------------��Ӧ�¼�--------------------------------------*/
static void gui_screen_appsport_continue_click(gui_click_struct* click)
{
    if (APP_SPORT_STATUS_PAUSE == g_app_sport.status) {
        device_sport_cmd_handler(APP_SPORT_STATUS_CONTINUE);
        app_window_appsport_update();
        app_window_appsport_update_data();
        gui_surface_commit();
    }
}

static void gui_screen_appsport_finish_click(gui_click_struct* click)
{
    if (APP_SPORT_STATUS_PAUSE == g_app_sport.status) {
        device_sport_cmd_handler(APP_SPORT_STATUS_STOP_FORCE);
        application_go_back();
    }
}

static void app_sport_window_act(void *buf)
{
	if((APP_SPORT_STATUS_STOP == g_app_sport.status)||
		(APP_SPORT_STATUS_STOP_FORCE == g_app_sport.status)||
		(0 == get_ble_appconnect()))
	{
		device_sport_cmd_handler(APP_SPORT_STATUS_STOP_FORCE);
		application_go_back();
        return;
	}
	application_open_act_timer(APPLICATION_TIMER_ACT, 500);

	app_window_appsport_update_data();
    gui_surface_commit();
}

static void app_sport_window_key_short(void *buf)
{
	SYS_DEBUG("app sport key short\r\n");

	if(APP_SPORT_STATUS_PAUSE != g_app_sport.status)
	{
		device_sport_cmd_handler(APP_SPORT_STATUS_PAUSE);
	}
	else{
		device_sport_cmd_handler(APP_SPORT_STATUS_CONTINUE);
        app_window_appsport_update_data();
	}
	app_window_appsport_update();
    gui_surface_commit();
}

static void app_sport_window_app_sport_cmd(void *buf)
{
	/* if status change, so open lcd. */
	if(g_app_sport.status != m_sport_status)
	{
		m_sport_status = g_app_sport.status;
		send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
	}
	app_sport_cmd_handler();
	if((APP_SPORT_STATUS_STOP == g_app_sport.status)||(APP_SPORT_STATUS_STOP_FORCE == g_app_sport.status))
	{
		application_go_back();
	}
	else{
        app_window_appsport_update_data();
		app_window_appsport_update();
        gui_surface_commit();
	}
}

static void app_sport_window_ble_connect_status(void *buf)
{
	device_sport_cmd_handler(APP_SPORT_STATUS_STOP_FORCE);
	application_go_back();
}



static const gui_touch_event_struct gui_screen_appsport_touch_events[] =
{
    {
    	.id = APPSPORT_DATA_LAYOUT_ID_PAUSE_CONTINUE_PIC,
     	.offset_top = 20,
     	.click = gui_screen_appsport_continue_click
    },

    {
    	.id = APPSPORT_DATA_LAYOUT_ID_PAUSE_EXIT_PIC,
		.offset_top = 20,
		.click = gui_screen_appsport_finish_click

	},
};



static const app_window_event_struct gui_screen_appsport_static_events[] =
{
	{.id = EVENT_ACT,	.handler = app_sport_window_act	},
	{.id = EVENT_BL_TIMEOUT, .handler = NULL},
	{.id = EVENT_KEY1_SHORT,.handler = app_sport_window_key_short},
    {.id = EVENT_APP_SPORT, .handler = app_sport_window_app_sport_cmd},
    {.id = EVENT_BLE_CONNECT_STATUS, .handler = app_sport_window_ble_connect_status},
    {
		.id = EVENT_KEY2_SHORT, //控件ID.
		.handler = app_sport_window_key_short,
	},
	{
		.id = EVENT_KEY1_LONG, //控件ID.
		.handler = app_sport_window_key_short,
	},
};

static const gui_window_config_struct app_window_appsport_config =
{
	.forbid_gesture_back = 1,
};



/*-----------------------------����--------------------------------------*/

const gui_window_struct app_window_appsport =
{
	.screen = &gui_screen_appsport,
	.config = &app_window_appsport_config,

	.init = app_window_appsport_init,
	.load = app_window_appsport_load,
	.entry = app_window_appsport_entry,
	.exit = app_window_appsport_exit,
	.destroy = app_window_appsport_destroy,

    .touch_event_num = countof(gui_screen_appsport_touch_events),
    .touch_events = gui_screen_appsport_touch_events,

    .event_num = countof(gui_screen_appsport_static_events),
    .events = gui_screen_appsport_static_events,
};



