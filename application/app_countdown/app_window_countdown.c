#include "app_window_countdown.h"
#include "app_window_countdown_layout.h"
#include "app_window_countdown_time.h"
#include "app_window_countdown_my_time.h"

#include "debug_info.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "gui_window.h"

unsigned int countdown_time_data = 0;
/*-----------------------------主流程--------------------------------------*/

static void app_window_countdown_init(void *buf)
{

}

static void app_window_countdown_load(void *buf)
{

}


static void app_window_countdown_entry(void *buf)
{

}


static void app_window_countdown_exit()
{

}

static void app_window_countdown_destroy()
{

}



/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_menu_list_touch_event_click_1min(gui_click_struct *event)
{
	countdown_time_data = 1*60;
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_countdown_time, NULL);
}

static void app_window_menu_list_touch_event_click_3min(gui_click_struct *event)
{
	countdown_time_data = 3*60;
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_countdown_time, NULL);
}

static void app_window_menu_list_touch_event_click_5min(gui_click_struct *event)
{
	countdown_time_data = 5*60;
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_countdown_time, NULL);
}

static void app_window_menu_list_touch_event_click_10min(gui_click_struct *event)
{
	countdown_time_data = 10*60;
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_countdown_time, NULL);
}

static void app_window_menu_list_touch_event_click_mymin(gui_click_struct *event)
{
	countdown_time_data = 0;
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_countdown_my_time, NULL);
}


/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_countdown_touch_events[] =
{
	{
		.id = COUNTDOWN_ID_1MIN,	
		.click = app_window_menu_list_touch_event_click_1min,
	},
	{
		.id = COUNTDOWN_ID_3MIN,	
		.click = app_window_menu_list_touch_event_click_3min,
	},
	{
		.id = COUNTDOWN_ID_5MIN,	
		.click = app_window_menu_list_touch_event_click_5min,
	},
	{
		.id = COUNTDOWN_ID_10MIN,	
		.click = app_window_menu_list_touch_event_click_10min,
	},
	{
		.id = COUNTDOWN_ID_CUSTOM,	
		.click = app_window_menu_list_touch_event_click_mymin,
	},

};



const gui_window_struct app_window_countdown =
{
	.screen = &gui_screen_countdown,
	.init = app_window_countdown_init,
	.load = app_window_countdown_load,
	.entry = app_window_countdown_entry,
	.exit = app_window_countdown_exit,
	.destroy = app_window_countdown_destroy,

	.touch_event_num = countof(app_window_countdown_touch_events),
	.touch_events = app_window_countdown_touch_events,
};

