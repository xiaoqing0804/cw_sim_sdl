#include "app_window_breath_time.h"
#include "app_window_breath_time_ui.h"
#include "app_window_breath_time_layout.h"
#include "app_window_breath_start.h"
#include "app_window_breath_hz.h"
#include "app_window_breath.h"
#include "data_breathe.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "application_titlebar.h"

/*-----------------------------定义--------------------------------------*/
static unsigned char m_save_time = 0;

/*-----------------------------本地逻辑--------------------------------------*/
static void app_window_breath_time_move_down()
{
	m_save_time += 60;
	if (m_save_time > 180)
		m_save_time = 60;
	app_window_breath_time_ui_update_list(m_save_time);
	gui_surface_commit();
}

static void app_window_breath_time_move_up()
{
	if (m_save_time <= 60)
		m_save_time = 180;
	else
		m_save_time -= 60;
	app_window_breath_time_ui_update_list(m_save_time);
	gui_surface_commit();
}

/*-----------------------------事件及触屏--------------------------------------*/

static unsigned char app_window_breath_time_countdown_hander(gui_touch_struct *envent)
{
	if (envent->type == TOUCH_EVENT_TYPE_DOWN)
	{
		return 1;
	}
	else if (envent->type == TOUCH_EVENT_TYPE_MOVE)
	{
		if (gui_run_time_lock())
			return 1;

		if (envent->direction == DIRECTION_TYPE_DOWN)
		{
			app_window_breath_time_move_down();
		}
		else if (envent->direction == DIRECTION_TYPE_UP)
		{
			app_window_breath_time_move_up();
		}
		else if (envent->direction == DIRECTION_TYPE_LEFT)
		{
			data_breathe_set_curr_total_time(m_save_time);
			application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_breath, NULL);
		}
		return 1;
	}
	return 0;
}

static void app_window_breath_time_ok_hander(gui_click_struct *envent)
{
	data_breathe_set_curr_total_time(m_save_time);
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_breath, NULL);
}

static void app_window_breath_time_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
		app_window_breath_time_move_down();
	else
		app_window_breath_time_move_up();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_breath_time_init(void *buf)
{
}

static void app_window_breath_time_load(void *buf)
{
	m_save_time = data_breathe_get_curr_total_time();
	app_window_breath_time_ui_update_list(m_save_time);
}

static void app_window_breath_time_entry(void *buf)
{
}

static void app_window_breath_time_exit()
{
}

static void app_window_breath_time_destroy()
{
}

/*-----------------------------系统设置--------------------------------------*/

static const app_window_event_struct app_window_breath_time_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_breath_time_rolkey_handler,
		},
};

static const gui_touch_event_struct app_window_breath_time_touch_events[] =
	{
		{
			.id = BREATH_TIME_LAYOUT_ID_1MIN,
			.touch = app_window_breath_time_countdown_hander,
		},
		{
			.id = BREATH_TIME_LAYOUT_ID_2MIN,
			.touch = app_window_breath_time_countdown_hander,
		},
		{
			.id = BREATH_TIME_LAYOUT_ID_3MIN,
			.touch = app_window_breath_time_countdown_hander,
		},
		{
			.id = BREATH_TIME_LAYOUT_ID_OK,
			.click = app_window_breath_time_ok_hander,
		},
};

const gui_window_struct app_window_breath_time =
	{
		.screen = &gui_screen_breath_time,

		.init = app_window_breath_time_init,
		.load = app_window_breath_time_load,
		.entry = app_window_breath_time_entry,
		.exit = app_window_breath_time_exit,
		.destroy = app_window_breath_time_destroy,

		.touch_event_num = countof(app_window_breath_time_touch_events),
		.touch_events = app_window_breath_time_touch_events,

		.event_num = countof(app_window_breath_time_events),
		.events = app_window_breath_time_events,
};
