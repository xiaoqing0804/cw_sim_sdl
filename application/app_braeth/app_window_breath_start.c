#include "app_window_breath_start.h"
#include "app_window_breath_start_ui.h"
#include "app_window_breath_start_layout.h"
#include "app_window_breath.h"
#include "app_window_breath_time.h"
#include "app_window_breath_hz.h"
#include "app_window_breath_hz_layout.h"
#include "app_window_breath_animate.h"
#include "data_breathe.h"

#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"
#include "application_titlebar.h"

/*-----------------------------定义--------------------------------------*/

#define BREATH_START_INTERVAL (50)

/// @brief 总时间
static short g_breath_start_times_count = 0;

/// @brief 倒计时剩余时间
static unsigned char g_breath_start_status = 3;

/*-----------------------------本地逻辑--------------------------------------*/

static float app_window_breath_start_get_step()
{
	float step = 2.0f;
	if (data_breathe_get_curr_speed_type() == BREATHE_SPEED_TYPE_QUICK) // 快速
		step = 90.0f / (BREATH_TIME_ONCE_QUICK / BREATH_START_INTERVAL);
	else if (data_breathe_get_curr_speed_type() == BREATHE_SPEED_TYPE_NORMAL)
		step = 90.0f / (BREATH_TIME_ONCE_NORMAL / BREATH_START_INTERVAL);
	else
		step = 90.0f / (BREATH_TIME_ONCE_SLOW / BREATH_START_INTERVAL);
	return step;
}

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_breath_start_timer(void *buf)
{
	application_close_act_timer(APPLICATION_TIMER_ACT);

	if (g_breath_start_status > 0) // 倒计时
	{
		g_breath_start_status--;
		app_window_breath_start_ui_show_countdown(g_breath_start_status);

		if (g_breath_start_status == 0)
		{
			app_window_breath_animate_auto_start();
			application_open_act_timer(APPLICATION_TIMER_ACT, BREATH_START_INTERVAL);
		}
		else
		{
			application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
		}
	}
	else // 已经开始
	{
		if (--g_breath_start_times_count > 0)
		{
			app_window_breath_start_ui_show_status();

			float step = app_window_breath_start_get_step();
			app_window_breath_animate_step(step);
			if (app_window_breath_animate_is_back())
				close_motor_msg();
			else
				send_motor_msg(MOTOR_MSG_BREATH);

			application_open_act_timer(APPLICATION_TIMER_ACT, BREATH_START_INTERVAL);
		}
		else
		{
			close_motor_msg();
			gui_window_go_back();
		}
	}
	gui_surface_commit();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_breath_start_init(void *buf)
{
}

static void app_window_breath_start_load(void *buf)
{
	g_breath_start_status = 3;
	g_breath_start_times_count = data_breathe_get_curr_total_time() * 1000 / BREATH_START_INTERVAL;
	app_window_breath_start_ui_show();
}

static void app_window_breath_start_entry(void *buf)
{
	g_breath_start_status = 3;
	g_breath_start_times_count = data_breathe_get_curr_total_time() * 1000 / BREATH_START_INTERVAL;
	app_window_breath_start_ui_show();
	application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}

static void app_window_breath_start_exit()
{
	close_motor_msg();
	app_window_breath_animate_auto_stop();
}

static void app_window_breath_start_destroy()
{
}

/*-----------------------------系统设置--------------------------------------*/

static const app_window_event_struct app_window_breath_start_events_handler[] =
	{
		{
			.id = EVENT_ACT,
			.handler = app_window_breath_start_timer,
		},
		{
			.id = EVENT_BL_TIMEOUT,
			.handler = NULL,
		},
};

const gui_window_struct app_window_breath_start =
	{
		.screen = &gui_screen_breath_start,

		.init = app_window_breath_start_init,
		.load = app_window_breath_start_load,
		.entry = app_window_breath_start_entry,
		.exit = app_window_breath_start_exit,
		.destroy = app_window_breath_start_destroy,

		.event_num = countof(app_window_breath_start_events_handler),
		.events = app_window_breath_start_events_handler,
};
