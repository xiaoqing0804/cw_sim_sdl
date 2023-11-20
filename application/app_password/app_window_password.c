#include "app_window_password.h"
#include "app_window_password_ui.h"
#include "app_window_password_layout.h"
#include "app_window_password_status.h"

#include "debug_info.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "data_receive_package.h"
#include "app_window_password.h"
#include "application_password.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_password_event_touch(gui_click_struct *event)
{
	if (event->id >= PASSWORD_BG_0 && event->id <= PASSWORD_BG_9)
	{
		app_window_password_status_add('0' + (event->id - PASSWORD_BG_0));
		app_window_password_ui_show();
		gui_surface_commit();

		application_open_act_timer(APPLICATION_TIMER_ACT, 100);
	}
}

static void app_window_password_delete_event_touch(gui_click_struct *event)
{
	app_window_password_status_remove();
	app_window_password_ui_show();
	gui_surface_commit();
}

static void app_password_key1_short(void *buf)
{
	unsigned char force = 1;
	application_send_event(EVENT_BACKLIGHT_OFF, &force);
}

static void app_window_password_acttimer_handler(void *buf)
{
	application_close_act_timer(APPLICATION_TIMER_ACT);
	app_window_password_status_complete_step();
}

static void app_window_password_update_window(void *buf)
{
	app_window_password_ui_show();
	gui_surface_commit();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_password_init(void *buf)
{
}

static void app_window_password_load(void *buf)
{
	application_password_setTempLock(1);
	app_window_password_ui_show();
}

static void app_window_password_entry(void *buf)
{
}

static void app_window_password_exit()
{
	application_password_setTempLock(0);
	application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_password_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_password_touch_events[] =
	{
		{
			.id = PASSWORD_BG_1,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_2,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_3,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_4,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_5,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_6,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_7,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_8,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_9,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_0,
			.click = app_window_password_event_touch,
		},
		{
			.id = PASSWORD_BG_DELECL,
			.click = app_window_password_delete_event_touch,
		},
};

static const app_window_event_struct app_password_static_events[] =
	{
		{
			.id = EVENT_ACT,
			.handler = app_window_password_acttimer_handler,
		},

		{
			.id = EVENT_UPDATE_WINDOW,
			.handler = app_window_password_update_window,
		},

		{
			.id = EVENT_KEY1_SHORT,
			.handler = app_password_key1_short,
		},
};

static const gui_window_config_struct app_window_password_config =
	{
		.entry_back_to_destory = 1,
};

const gui_window_struct app_window_password =
	{
		.config = &app_window_password_config,
		.screen = &gui_screen_password,

		.init = app_window_password_init,
		.load = app_window_password_load,
		.entry = app_window_password_entry,
		.exit = app_window_password_exit,
		.destroy = app_window_password_destroy,

		.touch_event_num = countof(app_window_password_touch_events),
		.touch_events = app_window_password_touch_events,

		.event_num = countof(app_password_static_events),
		.events = app_password_static_events,
};
