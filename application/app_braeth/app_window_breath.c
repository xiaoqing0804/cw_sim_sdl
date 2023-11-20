#include "app_window_breath.h"
#include "app_window_breath_ui.h"
#include "app_window_breath_layout.h"
#include "app_window_breath_animate.h"
#include "app_window_breath_time.h"
#include "app_window_breath_hz.h"
#include "app_window_breath_start.h"
#include "data_breathe.h"

#include "picture.h"
#include "language.h"
#include "data_common.h"
#include "debug_info.h"
#include "app_task_main.h"
#include "gui_window.h"
#include "application_titlebar.h"
#include "gui_surface_box_label.h"
#include "app_widget/app_window_widget_delete.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_breath_long_touch_handler(gui_click_struct *event)
{
	if (is_exist_widget_app(APP_INFO_ID_BREATHE))
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_BREATHE);
	}
}

static void app_window_breath_event_click_time_hander(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_breath_time, NULL);
}

static void app_window_breath_event_click_hz_hander(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_breath_hz, NULL);
}

static void app_window_breath_event_click_start_hander(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_breath_start, NULL);
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_breath_init(void *buf)
{
}

static void app_window_breath_load(void *buf)
{
	app_window_breath_ui_init_animate();
}

static void app_window_breath_entry(void *buf)
{
	app_window_breath_animate_auto_start();
}

static void app_window_breath_exit()
{
	app_window_breath_animate_auto_stop();
}

static void app_window_breath_destroy()
{
}

/*-----------------------------系统设置--------------------------------------*/

static const app_window_event_struct app_window_breath_event_handler[] =
	{
		{
			.id = EVENT_ACT,
			.handler = app_window_breath_animate_timer,
		},
};

static const gui_touch_event_struct app_window_breath_touch_events[] =
	{
		{
			.id = BREATH_LAYOUT_ID_TIME,
			.click = app_window_breath_event_click_time_hander,
			.offset_left = 30,
			.offset_top = 30,
		},

		{
			.id = BREATH_LAYOUT_ID_SPEED,
			.click = app_window_breath_event_click_hz_hander,
			.offset_left = 30,
			.offset_top = 30,
		},

		{
			.id = BREATH_LAYOUT_ID_BG,
			.click = app_window_breath_event_click_start_hander,
		},

		{
			.id = 0xFFFF, // fullscreen.
			.long_touch = app_window_breath_long_touch_handler,
		},
};

const gui_window_struct app_window_breath =
	{
		.screen = &gui_screen_breath,

		.init = app_window_breath_init,
		.load = app_window_breath_load,
		.entry = app_window_breath_entry,
		.exit = app_window_breath_exit,
		.destroy = app_window_breath_destroy,

		.touch_event_num = countof(app_window_breath_touch_events),
		.touch_events = app_window_breath_touch_events,

		.event_num = countof(app_window_breath_event_handler),
		.events = app_window_breath_event_handler,
};
