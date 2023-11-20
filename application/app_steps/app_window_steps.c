#include "picture.h"
#include "language.h"
#include "debug_info.h"
#include "app_task_main.h"

#include "arithmetic_common.h"
#include "bsp_hr\hr.h"
#include "gui_window.h"

#include "app_window_steps.h"
#include "app_window_steps_layout.h"
#include "app_window_steps_ui.h"

#include "application_titlebar.h"

#include "gui_surface_box_image_progress.h"
#include "gui_surface_box_image_number.h"
#include "gui_surface_box_label.h"

#include "app_widget/app_window_widget_delete.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_steps_long_touch_handler(gui_click_struct *event)
{
	if (is_exist_widget_app(APP_INFO_ID_STEP))
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_STEP);
	}
}

static void app_window_steps_sportinfo_handler(void *buf)
{
	app_window_step_ui_show();
	app_window_step_ui_update_unit();
	gui_surface_commit();
}

/*-----------------------------系统流程--------------------------------------*/

static void app_window_steps_init(void *buf)
{
}

static void app_window_steps_load(void *buf)
{
	app_window_step_ui_show();
}

static void app_window_steps_entry(void *buf)
{
}

static void app_window_steps_exit()
{
}

static void app_window_steps_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_steps_static_events[] =
	{
		{
			.id = EVENT_UPDATE_SPORTINFO,
			.handler = app_window_steps_sportinfo_handler,
		},
		{
			.id = EVENT_UPDATE_UNIT_SETTING,
			.handler = app_window_steps_sportinfo_handler,
		},
};

static const gui_touch_event_struct app_window_steps_touch_events =
	{
		.id = 0xFFFF, // fullscreen.
		.long_touch = app_window_steps_long_touch_handler,
};

const gui_window_struct app_window_steps =
	{
		.screen = &gui_screen_steps,

		.init = app_window_steps_init,
		.load = app_window_steps_load,
		.entry = app_window_steps_entry,
		.exit = app_window_steps_exit,
		.destroy = app_window_steps_destroy,

		.touch_event_num = 1,
		.touch_events = &app_window_steps_touch_events,

		.event_num = countof(app_window_steps_static_events),
		.events = app_window_steps_static_events,
};
