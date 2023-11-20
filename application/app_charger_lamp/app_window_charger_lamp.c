#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "app_window_charger_lamp.h"
#include "app_ota/app_window_ota.h"
#include "app_charger/app_window_charger.h"
#include "data_gensor_direction.h"
#include "bsp_lcd/lcd.h"
#include "app_window_charger_lamp_layout.h"
#include "app_main/app_window_main_watchface_update.h"
#include "get_data.h"

#define CHARGER_LAMP_TIMEOUT 500

#if CHARGER_LAMP_SUPPORT

static const picture_info_struct* g_charger_lamp_left_time_list[] =
{
	&pic_charger_lamp_left_time_0_info,
	&pic_charger_lamp_left_time_1_info,
	&pic_charger_lamp_left_time_2_info,
	&pic_charger_lamp_left_time_3_info,
	&pic_charger_lamp_left_time_4_info,
	&pic_charger_lamp_left_time_5_info,
	&pic_charger_lamp_left_time_6_info,
	&pic_charger_lamp_left_time_7_info,
	&pic_charger_lamp_left_time_8_info,
	&pic_charger_lamp_left_time_9_info,
};

static const picture_info_struct* g_charger_lamp_left_date_list[] =
{
	&pic_charger_lamp_left_date_0_info,
	&pic_charger_lamp_left_date_1_info,
	&pic_charger_lamp_left_date_2_info,
	&pic_charger_lamp_left_date_3_info,
	&pic_charger_lamp_left_date_4_info,
	&pic_charger_lamp_left_date_5_info,
	&pic_charger_lamp_left_date_6_info,
	&pic_charger_lamp_left_date_7_info,
	&pic_charger_lamp_left_date_8_info,
	&pic_charger_lamp_left_date_9_info,
};

static const picture_info_struct* g_charger_lamp_left_week_list[] =
{
	&pic_charger_lamp_left_week_7_info,
	&pic_charger_lamp_left_week_1_info,
	&pic_charger_lamp_left_week_2_info,
	&pic_charger_lamp_left_week_3_info,
	&pic_charger_lamp_left_week_4_info,
	&pic_charger_lamp_left_week_5_info,
	&pic_charger_lamp_left_week_6_info,
};

static const picture_info_struct* g_charger_lamp_left_week_list_c[] =
{
	&pic_charger_lamp_left_week_7_c_info,
	&pic_charger_lamp_left_week_1_c_info,
	&pic_charger_lamp_left_week_2_c_info,
	&pic_charger_lamp_left_week_3_c_info,
	&pic_charger_lamp_left_week_4_c_info,
	&pic_charger_lamp_left_week_5_c_info,
	&pic_charger_lamp_left_week_6_c_info,
};

static unsigned char app_window_charger_lamp_timer_count = 0;
//static unsigned char app_window_charger_lamp_brightness = 0;



static void app_window_charger_lamp_show_left()
{
	time_struct time;
    sys_time_get(&time);
	unsigned char charger_hour = time.hour;

	if (0 == g_timeSync.format.bit.hour) // 12h format.
	{
		if (charger_hour > 12)
		{
			charger_hour -= 12;
		}
		else if (charger_hour == 0)
		{
			charger_hour = 12;
		}
	}
	gui_box_struct* box_bat = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_BAT);
	if(box_bat != NULL)
	{
		box_bat->visible = 1;
		gui_surface_box_change_x(box_bat,LCD_SCALE_WIDTH*210);
		gui_surface_box_change_y(box_bat,LCD_SCALE_HEIGHT*285);
	}


	gui_box_struct* box_time_1 = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_TIME_1);
	if(box_time_1 != NULL)
	{
		gui_surface_box_change_x(box_time_1,LCD_SCALE_WIDTH*80);
		gui_surface_box_change_y(box_time_1,LCD_SCALE_HEIGHT*17);
		gui_surface_box_image_change(box_time_1,g_charger_lamp_left_time_list[charger_hour / 10]);
	}
	gui_box_struct* box_time_2 = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_TIME_2);
	if(box_time_2 != NULL)
	{
		gui_surface_box_change_x(box_time_2,LCD_SCALE_WIDTH*80);
		gui_surface_box_change_y(box_time_2,LCD_SCALE_HEIGHT*94);
		gui_surface_box_image_change(box_time_2,g_charger_lamp_left_time_list[charger_hour % 10]);
	}
	gui_box_struct* box_time_dot = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_TIME_DOT);
	if(box_time_dot != NULL)
	{
		gui_surface_box_change_visible(box_time_dot,app_window_charger_lamp_timer_count);
		gui_surface_box_change_x(box_time_dot,LCD_SCALE_WIDTH*80);
		gui_surface_box_change_y(box_time_dot,LCD_SCALE_HEIGHT*177);
		gui_surface_box_image_change(box_time_dot,&pic_charger_lamp_left_time_dot_info);
	}

	gui_box_struct* box_time_3 = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_TIME_3);
	if(box_time_3 != NULL)
	{
		gui_surface_box_change_x(box_time_3,LCD_SCALE_WIDTH*80);
		gui_surface_box_change_y(box_time_3,LCD_SCALE_HEIGHT*218);
		gui_surface_box_image_change(box_time_3,g_charger_lamp_left_time_list[time.min / 10]);
	}

	gui_box_struct* box_time_4 = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_TIME_4);
	if(box_time_4 != NULL)
	{
		gui_surface_box_change_x(box_time_4,LCD_SCALE_WIDTH*80);
		gui_surface_box_change_y(box_time_4,LCD_SCALE_HEIGHT*295);
		gui_surface_box_image_change(box_time_4,g_charger_lamp_left_time_list[time.min % 10]);
	}


	// gui_box_struct* box_date_1 = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_DATE_1);
	// if(box_date_1 != NULL)
	// {
	// 	gui_surface_box_change_x(box_date_1,23);
	// 	gui_surface_box_change_y(box_date_1,122);
	// 	gui_surface_box_image_change(box_date_1,g_charger_lamp_left_date_list[time.mon / 10]);
	// }

	// gui_box_struct* box_date_2 = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_DATE_2);
	// if(box_date_2 != NULL)
	// {
	// 	gui_surface_box_change_x(box_date_2,23);
	// 	gui_surface_box_change_y(box_date_2,141);
	// 	gui_surface_box_image_change(box_date_2,g_charger_lamp_left_date_list[time.mon % 10]);
	// }

	// gui_box_struct* box_date_dot = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_DATE_DOT);
	// if(box_date_dot != NULL)
	// {
	// 	gui_surface_box_change_x(box_date_dot,23);
	// 	gui_surface_box_change_y(box_date_dot,160);
	// 	gui_surface_box_image_change(box_date_dot,&pic_charger_lamp_left_date_dot_info);
	// }

	gui_box_struct* box_date_3 = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_DATE_3);
	if(box_date_3 != NULL)
	{
		gui_surface_box_change_x(box_date_3,17);
		gui_surface_box_change_y(box_date_3,LCD_SCALE_HEIGHT*254);
		gui_surface_box_image_change(box_date_3,g_charger_lamp_left_date_list[time.day / 10]);
	}

	gui_box_struct* box_date_4 = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_DATE_4);
	if(box_date_4 != NULL)
	{
		gui_surface_box_change_x(box_date_4,17);
		gui_surface_box_change_y(box_date_4,LCD_SCALE_HEIGHT*272);
		gui_surface_box_image_change(box_date_4,g_charger_lamp_left_date_list[time.day % 10]);
	}


	gui_box_struct* box_week = gui_surface_get_box(&gui_screen_charger_lamp, CHARGER_LAMP_ID_WEEK);
	if(box_week != NULL)
	{	
		gui_surface_box_change_x(box_week,LCD_SCALE_WIDTH*25);
		gui_surface_box_change_y(box_week,LCD_SCALE_HEIGHT*290);
		if(LANGUAGE_TYPE_CHINESE == g_language.num){
			gui_surface_box_image_change(box_week,g_charger_lamp_left_week_list_c[time.wed]);
		}
		else{
			gui_surface_box_image_change(box_week,g_charger_lamp_left_week_list[time.wed]);
		}
	}

}

static void app_window_charger_lamp_show()
{
	GUI_DEBUG("app_window_charger_lamp_show");
	static unsigned char gsensor_direction_type = (unsigned char)DIRECTION_TYPE_LEFT;

	DIRECTION_TYPE direction_type = data_gsensor_direction_get_type();
	if(direction_type != DIRECTION_TYPE_LEFT)
		direction_type = gsensor_direction_type;

	if(direction_type == DIRECTION_TYPE_LEFT)
	{
		GUI_DEBUG("app_window_charger_lamp_show DIRECTION_TYPE_LEFT");
		app_window_charger_lamp_show_left();
	}
	gui_surface_commit();

	gsensor_direction_type = direction_type;
}

static void app_window_charger_lamp_timer_handler(void* buf)
{
	GUI_DEBUG("app_window_charger_lamp_timer_handler app_window_charger_lamp_timer_count=%d",app_window_charger_lamp_timer_count);
	unsigned int timer_index = *((unsigned int *)buf);
    if(APPLICATION_TIMER_ACT == timer_index)
	{
		app_window_charger_lamp_timer_count = !app_window_charger_lamp_timer_count;
		GUI_DEBUG("app_window_charger_lamp_timer_handler1 app_window_charger_lamp_timer_count=%d",app_window_charger_lamp_timer_count);
		app_window_charger_lamp_show();
    }

	gui_surface_commit();
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_charger_lamp_init(void *buf)
{

}

static void app_window_charger_lamp_load()
{
	//app_window_charger_lamp_brightness = oled_backlight_get();
	//g_brightness = 20;
	oled_backlight_set_adpvalue(20);
	oled_backlight_set();

    app_window_charger_lamp_show();
}


static void app_window_charger_lamp_entry()
{
    app_battery_info_struct* batt_info = application_get_battery_info();
    if (batt_info->charger) {
        application_open_act_timer(APPLICATION_TIMER_ACT, CHARGER_LAMP_TIMEOUT);
    }
    else {
        //application_go_back();
        application_send_event(EVENT_GO_BACK, NULL);
    }
}


static void app_window_charger_lamp_exit()
{
	application_close_act_timer(APPLICATION_TIMER_ACT);

	//g_brightness = app_window_charger_lamp_brightness;
	oled_backlight_set_adpvalue(100);
	oled_backlight_set();
}

static void app_window_charger_lamp_destroy()
{
	
}


static void app_window_charger_lamp_charger_handler(void* buf)
{
	//SYS_DEBUG("app_window_charger_charger_handler");
    app_battery_info_struct* batt_info = (app_battery_info_struct*)buf;
    if (batt_info->charger == 0) {
        application_go_back();
        return;
    }
}


static void app_window_charger_lamp_ota_handler(void* buf)
{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_ota, NULL);
}

static void app_window_charger_lamp_gsensor_direction_handler(void* buf)
{
	GUI_DEBUG("app_window_gsensor_direction_handler");
	if((data_gsensor_direction_get_type() == DIRECTION_TYPE_NONE) || (data_gsensor_direction_get_type() == DIRECTION_TYPE_LEFT))
	{
		GUI_DEBUG("app_window_gsensor_direction_handler DIRECTION_TYPE_NONE");
		application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_charger, NULL);
	}
	else
	{
		app_window_charger_lamp_show();
	}
}
static void app_window_charger_lamp_key1_short(void* buf)
{
    application_suspend_req(1);
}

static void app_window_watchface_update_handler(void* buf)
{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_main_watchface_update, NULL);
}

static void app_window_charger_lamp_finddevice_handler(void* buf)
{
	#ifdef __EXT_BT_AUDIO__
	//ext_btaud_test_speaker_music(1);
	#endif
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_charger_lamp_static_events[] =
{
	{
		.id = EVENT_BATTERY_CHARGER,
		.handler = app_window_charger_lamp_charger_handler,
	},

	{
        .id = EVENT_OTA,
        .handler = app_window_charger_lamp_ota_handler,
    },
    {
        .id =EVENT_UPDATE_WATCHFACE,
        .handler = app_window_watchface_update_handler,
    },

    {
		.id = EVENT_GSENSOR_DIRECTION,
		.handler = app_window_charger_lamp_gsensor_direction_handler,
	},
	{
        .id = EVENT_ACT,
        .handler = app_window_charger_lamp_timer_handler,
    },
	{
         .id = EVENT_FIND_DEVICE,
         .handler = app_window_charger_lamp_finddevice_handler,
    },
    {
        .id = EVENT_KEY1_SHORT,
        .handler = app_window_charger_lamp_key1_short,
    },
    {
        .id = EVENT_ALL,
        .handler = NULL,
    }
};

static const gui_window_config_struct app_window_charger_lamp_config =
{
	.forbid_gesture_back = 1,
	.forbid_key_back = 1,
};

const gui_window_struct app_window_charger_lamp =
{
	.screen = &gui_screen_charger_lamp,
	.config = &app_window_charger_lamp_config,

	.init = app_window_charger_lamp_init,
	.load = app_window_charger_lamp_load,
	.entry = app_window_charger_lamp_entry,
	.exit = app_window_charger_lamp_exit,
	.destroy = app_window_charger_lamp_destroy,

    .event_num = countof(app_window_charger_lamp_static_events),
    .events = app_window_charger_lamp_static_events,
};

#endif


