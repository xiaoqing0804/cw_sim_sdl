
#include "app_window_reboot.h"
#include "app_window_reboot_ui.h"
#include "app_window_reboot_layout.h"
#include "app_window_goodbye.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_reboot_touch_event_ok_handle(gui_click_struct *event)
{
	ext_btaud_onoff_set(0);
	application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_goodbye, GOODBYE_RESET);
}

static void app_window_reboot_touch_event_cancel_handle(gui_click_struct *event)
{
	application_go_back();
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_reboot_init(void *buf)
{
}

static void app_window_reboot_load(void *buf)
{
}

static void app_window_reboot_entry(void *buf)
{
}

static void app_window_reboot_exit()
{
}

static void app_window_reboot_destroy()
{
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_reboot_static_events[] =
	{
		{
			.id = EVENT_KEY1_SHORT,
			.handler = NULL,
		},
		{
			.id = EVENT_BL_TIMEOUT,
			.handler = NULL,
		},
};

static const gui_touch_event_struct app_window_reboot_touch_events[] =
	{
		{
			.id = REBOOT_LAYOUT_ID_YES,
			.click = app_window_reboot_touch_event_ok_handle,
		},
		{
			.id = REBOOT_LAYOUT_ID_NO,
			.click = app_window_reboot_touch_event_cancel_handle,
		},
};

const gui_window_struct app_window_reboot =
	{
		.screen = &gui_reboot_screen,

		.init = app_window_reboot_init,
		.load = app_window_reboot_load,
		.entry = app_window_reboot_entry,
		.exit = app_window_reboot_exit,
		.destroy = app_window_reboot_destroy,

		.touch_event_num = countof(app_window_reboot_touch_events),
		.touch_events = app_window_reboot_touch_events,

		.event_num = countof(app_window_reboot_static_events),
		.events = app_window_reboot_static_events,
};
