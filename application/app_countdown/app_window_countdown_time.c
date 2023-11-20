#include "debug_info.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#include "application_titlebar.h"

#include "app_window_countdown.h"
#include "app_window_countdown_time.h"
#include "app_window_countdown_layout.h"
#include "app_window_countdown_time_layout.h"

#include "srv_time_counter.h"

#include "app_window_countdown_time_out.h"

unsigned char countdown_flag = 0;
unsigned int countdown_save = 0;

/*-----------------------------主流程--------------------------------------*/

static void app_window_countdown_time_init(void *buf)
{
	countdown_save = countdown_time_data;
	countdown_flag = 1;
}

static void app_window_countdown_time_load(void *buf)
{
	app_window_countdown_time_initial_entry();

}

static void app_window_countdown_time_entry(void *buf)
{
    application_open_act_timer(APPLICATION_TIMER_ACT,1000);
}

static void app_window_countdown_time_exit()
{
	application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_countdown_time_destroy()
{

}

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_countdown_time_static_event_counter(void *buf)
{
	 app_window_countdown_time_static_event_counter_function();
}


static void app_window_countdown_time_touch_event_click_strat(gui_click_struct *event)
{
    app_window_countdown_time_touch_event_click_strat_function();
}


static void app_window_countdown_time_touch_event_click_clear(gui_click_struct *event)
{

	// application_close_act_timer(APPLICATION_TIMER_ACT);
	// gui_window_go_back();
	application_open_act_timer(APPLICATION_TIMER_ACT,1000);
  	countdown_save = countdown_time_data;
    app_window_countdown_time_load(NULL);
	gui_surface_commit();
}




/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_countdown_time_touch_events[] =
{
	{
		.id = COUNTDOWN_TIME_ID_CLEAR,
		.click = app_window_countdown_time_touch_event_click_clear,
	},
    {
		.id = COUNTDOWN_TIME_ID_START,
		.click = app_window_countdown_time_touch_event_click_strat,
	},

};

static const app_window_event_struct app_window_countdown_time_static_events[] =
{
    {
		.id = EVENT_ACT,
		.handler = app_window_countdown_time_static_event_counter,
	},
	{
        .id = EVENT_BL_TIMEOUT,
        .handler = NULL	,
    }
};

static const gui_window_config_struct app_window_countdown_config =
    {
        .disable_go_home = 1,
};

const gui_window_struct app_window_countdown_time =
{
	.screen = &gui_screen_countdown_time,
    .config = &app_window_countdown_config,

	.init = app_window_countdown_time_init,
	.load = app_window_countdown_time_load,
	.entry = app_window_countdown_time_entry,
	.exit = app_window_countdown_time_exit,
	.destroy = app_window_countdown_time_destroy,

	.touch_event_num = countof(app_window_countdown_time_touch_events),
	.touch_events = app_window_countdown_time_touch_events,

	.event_num = countof(app_window_countdown_time_static_events),
	.events = app_window_countdown_time_static_events,
};

