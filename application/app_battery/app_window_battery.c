#include "app_window_battery.h"
#include "app_window_battery_ui.h"
#include "app_window_battery_layout.h"
#include "app_window_battery_chart.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_battery_rolkey_handker(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_battery);
	if (surface != NULL && rolkey != NULL)
	{
		if (rolkey->rotate == ROTATE_TYPE_FORWARD)
		{
			gui_surface_layout_scrollview_switch_to_direction(surface, DIRECTION_TYPE_DOWN);
		}
		else if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
		{
			gui_surface_layout_scrollview_switch_to_direction(surface, DIRECTION_TYPE_UP);
		}
		gui_surface_commit();
	}
}

/*-----------------------------主流程--------------------------------------*/
static void app_window_battery_init(void *buf)
{
}

static void app_window_battery_load(void *buf)
{
	app_window_battery_ui_show();
}

static void app_window_battery_entry(void *buf)
{
}

static void app_window_battery_exit()
{
}

static void app_window_battery_destroy()
{
}

/*-----------------------------系统设置--------------------------------------*/

static const app_window_event_struct app_window_battery_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_battery_rolkey_handker,
		},
};

const gui_window_struct app_window_battery =
	{
		.screen = &gui_screen_battery,

		.init = app_window_battery_init,
		.load = app_window_battery_load,
		.entry = app_window_battery_entry,
		.exit = app_window_battery_exit,
		.destroy = app_window_battery_destroy,

		.event_num = countof(app_window_battery_events),
		.events = app_window_battery_events,

};
