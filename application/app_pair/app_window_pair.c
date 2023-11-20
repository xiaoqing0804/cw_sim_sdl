#include "app_window_pair.h"
#include "app_window_pair_ui.h"
#include "app_window_pair_layout.h"
#include "bsp_includes.h"

/*-----------------------------响应事件--------------------------------------*/
static void app_window_pair_static_event_act(void *buf)
{
	unsigned int time_id = *((unsigned int *)buf);
	if (time_id == APPLICATION_TIMER_ACT)
	{
		application_go_back();
	}
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_pair_init(void *buf)
{
	send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
}

static void app_window_pair_load(void *buf)
{
}

static void app_window_pair_entry(void *buf)
{
	application_open_act_timer(APPLICATION_TIMER_ACT, 2500);
}

static void app_window_pair_exit()
{
}

static void app_window_pair_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/
static const app_window_event_struct app_window_pair_static_events[] =
	{
		{
			.id = EVENT_ACT,
			.handler = app_window_pair_static_event_act,
		},
};

const gui_window_struct app_window_pair =
	{
		.screen = &gui_screen_pair,

		.init = app_window_pair_init,
		.load = app_window_pair_load,
		.entry = app_window_pair_entry,
		.exit = app_window_pair_exit,
		.destroy = app_window_pair_destroy,

		.event_num = countof(app_window_pair_static_events),
		.events = app_window_pair_static_events,

};
