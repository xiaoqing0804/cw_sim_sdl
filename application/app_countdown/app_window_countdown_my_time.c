
#include "debug_info.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "application_titlebar.h"

#include "app_window_countdown.h"
#include "app_window_countdown_time.h"
#include "app_window_countdown_layout.h"
#include "app_window_countdown_my_time.h"
#include "app_window_countdown_my_time_layout.h"
#include "app_window_countdown_ui.h"

 short countdown_my_time_hour = 0;
 short countdown_my_time_min = 0;
 short countdown_my_time_second = 0;


/*-----------------------------主流程--------------------------------------*/

static void app_window_countdown_my_time_init(void *buf)
{

}

static void app_window_countdown_my_time_load(void *buf)
{
	app_window_countdown_my_time_update(1, 1, 1);
}


static void app_window_countdown_my_time_entry(void *buf)
{

}


static void app_window_countdown_my_time_exit()
{
}
/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_countdown_my_time_destroy()
{
	countdown_my_time_hour = 0;
	countdown_my_time_min = 0;
	countdown_my_time_second = 0;
}


static unsigned char app_window_countdown_my_time_touch_handler(gui_touch_struct *event)
{
    static unsigned char touch = 0;
     touch=app_window_countdown_my_time_touch_handler_function(event->type,event->x,event->y,event->direction);
    return touch;
}


static void app_window_countdown_my_time_touch_event_click_statr(gui_click_struct *envent)
{

	countdown_time_data = countdown_my_time_hour*60*60 + countdown_my_time_min*60 + countdown_my_time_second;
	if(countdown_time_data > 0)
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_countdown_time, NULL);
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_countdown_my_time_touch_events[] =
{
    {
        .id = 0xFFFF,
        .touch = app_window_countdown_my_time_touch_handler,
    },

	{
		.id = COUNTDOWN_MY_TIME_ID_STATR,
		.click = app_window_countdown_my_time_touch_event_click_statr,
		.offset_bottom = 60,

	},

};



const gui_window_struct app_window_countdown_my_time =
{
	.screen = &gui_screen_countdown_my_time,
	.init = app_window_countdown_my_time_init,
	.load = app_window_countdown_my_time_load,
	.entry = app_window_countdown_my_time_entry,
	.exit = app_window_countdown_my_time_exit,
	.destroy = app_window_countdown_my_time_destroy,

	.touch_event_num = countof(app_window_countdown_my_time_touch_events),
	.touch_events = app_window_countdown_my_time_touch_events,
};

