#include "app_window_breath_hz.h"
#include "app_window_breath_hz_ui.h"
#include "app_window_breath_hz_layout.h"
#include "app_window_breath.h"
#include "app_window_breath_time.h"
#include "app_window_breath_start.h"
#include "data_breathe.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "application_titlebar.h"

/*-----------------------------定义--------------------------------------*/
unsigned char m_save_speed_status = 0;

/*-----------------------------本地逻辑--------------------------------------*/
static void app_window_breath_hz_move_down()
{
	m_save_speed_status++;
	if (m_save_speed_status > 2)
		m_save_speed_status = 0;
	app_window_breath_hz_ui_update_list(m_save_speed_status);
	gui_surface_commit();
}

static void app_window_breath_hz_move_up()
{
	if ((m_save_speed_status > 0) && (m_save_speed_status < 3))
		m_save_speed_status--;
	else
		m_save_speed_status = 2;
	app_window_breath_hz_ui_update_list(m_save_speed_status);
	gui_surface_commit();
}

/*-----------------------------事件及触屏--------------------------------------*/

static unsigned char app_window_breath_hz_event_countdown_hander(gui_touch_struct *envent)
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
			app_window_breath_hz_move_down();
		}
		else if (envent->direction == DIRECTION_TYPE_UP)
		{
			app_window_breath_hz_move_up();
		}
		else if (envent->direction == DIRECTION_TYPE_LEFT)
		{
			data_breathe_set_curr_speed_type(m_save_speed_status);
			application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_breath, NULL);
		}
		return 1;
	}
	return 0;
}

static void app_window_breath_hz_ok_hander(gui_click_struct *envent)
{
	data_breathe_set_curr_speed_type((BREATHE_SPEED_TYPE_ENUM)m_save_speed_status);
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_breath, NULL);
}

static void app_window_breath_hz_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
		app_window_breath_hz_move_down();
	else
		app_window_breath_hz_move_up();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_breath_hz_init(void *buf)
{
	m_save_speed_status = data_breathe_get_curr_speed_type();
}

static void app_window_breath_hz_load(void *buf)
{
	m_save_speed_status = data_breathe_get_curr_speed_type();
	app_window_breath_hz_ui_update_list(m_save_speed_status);
}

static void app_window_breath_hz_entry(void *buf)
{
}

static void app_window_breath_hz_exit()
{
}

static void app_window_breath_hz_destroy()
{
}

/*-----------------------------系统设置--------------------------------------*/

static const gui_touch_event_struct app_window_breath_hz_touch_events[] =
	{
		{
			.id = BREATH_HZ_LAYOUT_ID_LIST_1,
			.touch = app_window_breath_hz_event_countdown_hander,
		},
		{
			.id = BREATH_HZ_LAYOUT_ID_LIST_2,
			.touch = app_window_breath_hz_event_countdown_hander,
		},
		{
			.id = BREATH_HZ_LAYOUT_ID_LIST_3,
			.touch = app_window_breath_hz_event_countdown_hander,
		},
		{
			.id = BREATH_HZ_LAYOUT_ID_OK_BUTTON,
			.click = app_window_breath_hz_ok_hander,
		},

};

static const app_window_event_struct app_window_breath_hz_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_breath_hz_rolkey_handler,
		},
};

const gui_window_struct app_window_breath_hz =
	{
		.screen = &gui_screen_breath_hz,

		.init = app_window_breath_hz_init,
		.load = app_window_breath_hz_load,
		.entry = app_window_breath_hz_entry,
		.exit = app_window_breath_hz_exit,
		.destroy = app_window_breath_hz_destroy,

		.touch_event_num = countof(app_window_breath_hz_touch_events),
		.touch_events = app_window_breath_hz_touch_events,

		.event_num = countof(app_window_breath_hz_events),
		.events = app_window_breath_hz_events,
};
