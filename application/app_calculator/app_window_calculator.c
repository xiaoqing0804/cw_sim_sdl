#include "app_window_calculator.h"
#include "app_window_calculator_ui.h"
#include "app_window_calculator_layout.h"
#include "app_window_calculator_convert.h"
#include "app_window_calculator_key.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_calculator_event_touch(gui_click_struct *event)
{
	char key = window_calculator_get_key((unsigned short)event->x, (unsigned short)event->y);
	if (key > 0)
	{
		window_calculator_key_press(key);
		app_window_calculator_ui_show(window_calculator_get_show_data(), window_calculator_get_operation_sign());
		gui_surface_commit();
	}
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_calculator_init(void *buf)
{
}

static void app_window_calculator_load(void *buf)
{
	app_window_calculator_ui_show(window_calculator_get_show_data(), window_calculator_get_operation_sign());
}

static void app_window_calculator_entry(void *buf)
{
}

static void app_window_calculator_exit()
{
	window_calculator_clear();
}

static void app_window_calculator_destroy(void)
{
}

/*-----------------------------系统设置--------------------------------------*/

static const gui_touch_event_struct app_window_calculator_touch_events[] =
	{
		{
			.id = CALCULATOR_ID_BG,
			.click = app_window_calculator_event_touch,
		},
};

const gui_window_struct app_window_calculator =
	{
		.screen = &app_calculator_screen,

		.init = app_window_calculator_init,
		.load = app_window_calculator_load,
		.entry = app_window_calculator_entry,
		.exit = app_window_calculator_exit,
		.destroy = app_window_calculator_destroy,

		.touch_event_num = countof(app_window_calculator_touch_events),
		.touch_events = app_window_calculator_touch_events,
};
