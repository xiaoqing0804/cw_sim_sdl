#include "debug_info.h"
#include "bsp_includes.h"

#include "app_window_goodbye.h"

#include "app_window_reset.h"
#include "app_window_reset_layout.h"

static void app_window_reset_init(void *buf)
{
}

static void app_window_reset_load(void *buf)
{
}

static void app_window_reset_entry(void *buf)
{
}

static void app_window_reset_exit()
{
}

static void app_window_reset_destroy()
{
}

static void app_window_reset_actimer_handler(void *buf)
{
}

static void app_window_reset_touch_event_click_yes_cancel(gui_click_struct *event)
{

	g_goodbye_type = GOODBYE_FACTORY_RESET;
	ext_btaud_onoff_set(0);
	application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_goodbye, NULL);
}

static void app_window_reset_touch_event_click_no_cancel(gui_click_struct *event)
{

	application_go_back();
}

/*-----------------------------����--------------------------------------*/
static const app_window_event_struct app_window_reset_static_events[] =
	{
		{
			.id = EVENT_ACT,
			.handler = app_window_reset_actimer_handler,
		},
		{
			.id = EVENT_KEY1_SHORT,
			.handler = NULL,
		},

		{
			.id = EVENT_BL_TIMEOUT, //????????ID.
			.handler = NULL,
		},

};

static const gui_touch_event_struct app_window_reset_touch_events[] =
	{
		{
			.id = RESET_EXIT_ID_YES,
			.click = app_window_reset_touch_event_click_yes_cancel,
		},
		{
			.id = RESET_EXIT_ID_NO,
			.click = app_window_reset_touch_event_click_no_cancel,
		},

};

gui_window_struct app_window_reset =
	{
		.screen = &gui_reset_screen,
		.config = NULL,

		.init = app_window_reset_init,
		.load = app_window_reset_load,
		.entry = app_window_reset_entry,
		.exit = app_window_reset_exit,
		.destroy = app_window_reset_destroy,

		.touch_event_num = countof(app_window_reset_touch_events),
		.touch_events = app_window_reset_touch_events,

		.event_num = countof(app_window_reset_static_events),
		.events = app_window_reset_static_events,
};
