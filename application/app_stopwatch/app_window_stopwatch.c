#include "app_window_stopwatch.h"
#include "app_window_stopwatch_record_detail_layout.h"
#include "app_window_stopwatch_layout.h"
#include "app_window_stopwatch_ui.h"
#include "data_stopwatch.h"

#include "bsp_includes.h"
#include "data_common.h"
#include "sys_timer_thread.h"

#include "app_widget/app_window_widget_delete.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#define STOPWATCH_TIMER_INTERVAL (72)

bool app_window_stopwatch_set_record_time(unsigned long timer_ms);
void app_window_stopwatch_clear_record_time(void);
unsigned int app_window_stopwatch_get_record_time(unsigned int index);

/*-----------------------------主流程--------------------------------------*/

static void app_window_stopwatch_init(void *buf)
{
}

static void app_window_stopwatch_load(void *buf)
{
	data_stopwatch_time_init();
	app_window_stopwatch_ui_show();
}

static void app_window_stopwatch_entry(void *buf)
{
	if (data_stopwatch_status_is_start())
	{
		application_open_act_timer(APPLICATION_TIMER_ACT, STOPWATCH_TIMER_INTERVAL);
	}
}

static void app_window_stopwatch_exit()
{
	application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_stopwatch_destroy()
{
}

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_stopwatch_static_event_act(void *buf)
{
	app_window_stopwatch_ui_show();
}

static void app_window_stopwatch_touch_event_click_clear(gui_click_struct *event)
{
	if (data_stopwatch_status_is_pause())
	{
		application_close_act_timer(APPLICATION_TIMER_ACT);
		data_stopwatch_status_stop();
		app_window_stopwatch_ui_show();
		app_window_stopwatch_clear_record_time();
	}
	else if (data_stopwatch_status_is_start())
	{
		if(app_window_stopwatch_set_record_time(data_stopwatch_get_escape_time_ms()))
		{
		}

	}
	app_window_stopwatch_ui_show();

}
static void app_window_stopwatch_touch_event_click_detail(gui_click_struct *event)
{
	if(app_window_stopwatch_get_record_time(0))
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_stop_watch_record, NULL);
	}
}

static void app_window_stopwatch_touch_event_click_strat(gui_click_struct *event)
{
	if (data_stopwatch_status_is_start())
	{
		application_close_act_timer(APPLICATION_TIMER_ACT);
		data_stopwatch_status_pause();
		app_window_stopwatch_ui_show();
	}
	else if (data_stopwatch_status_is_pause())
	{
		data_stopwatch_status_restart();
		app_window_stopwatch_ui_show();
		application_open_act_timer(APPLICATION_TIMER_ACT, STOPWATCH_TIMER_INTERVAL);
	}
	else
	{
		data_stopwatch_time_start();
		app_window_stopwatch_ui_show();
		application_open_act_timer(APPLICATION_TIMER_ACT, STOPWATCH_TIMER_INTERVAL);
	}
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_stopwatch_touch_events[] = {
	{
		.id = STOPWATCH_TIME_ID_START,
		.click = app_window_stopwatch_touch_event_click_strat,
	},

	{
		.id = STOPWATCH_TIME_ID_RESET_RECORD,
		.click = app_window_stopwatch_touch_event_click_clear,
	},
	{
		.id = STOPWATCH_TIME_ID_RECORD_TIME,
		.click = app_window_stopwatch_touch_event_click_detail,
	},
};

static const app_window_event_struct app_window_stopwatch_static_events[] = {
	{
		.id = EVENT_ACT,
		.handler = app_window_stopwatch_static_event_act,
	},
	{
		.id = EVENT_BL_TIMEOUT,
		.handler = NULL,
	},
};

static const gui_window_config_struct app_window_stopwatch_config =
    {
        .disable_go_home = 1,
};

const gui_window_struct app_window_stopwatch = {
	.screen = &gui_screen_stopwatch,
    .config = &app_window_stopwatch_config,
	.init = app_window_stopwatch_init,
	.load = app_window_stopwatch_load,
	.entry = app_window_stopwatch_entry,
	.exit = app_window_stopwatch_exit,
	.destroy = app_window_stopwatch_destroy,

	.touch_event_num = countof(app_window_stopwatch_touch_events),
	.touch_events = app_window_stopwatch_touch_events,

	.event_num = countof(app_window_stopwatch_static_events),
	.events = app_window_stopwatch_static_events,
};
