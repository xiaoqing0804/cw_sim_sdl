#include "app_window_setting_screen.h"
#include "app_window_setting_screen_ui.h"
#include "app_window_setting_screen_layout.h"

#include "debug_info.h"
#include "application_config_app_info.h"
#include "app_window_widget_delete.h"
#include "data_wrist_lift.h"
#include "data_brightness.h"

static unsigned char g_setting_screen_brightness;

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_setting_screen_click_on_layout_item(gui_click_layout_struct *event)
{
	app_info_struct *app_info = get_app_info_by_id((APP_INFO_ID)event->id);
	SYS_DEBUG("event->id=%d", event->id);

	if (event->id == APP_INFO_ID_WRIST)
	{
		if (app_window_setting_screen_ui_is_touch_on_wrist_button(event->x, event->y))
		{
			data_wrist_lift_switch_status();
		}
		app_window_setting_screen_ui_show_wrist();
		application_reset_display_timeout(0);
		gui_surface_commit();
	}
	else if (event->id == APP_INFO_ID_BRIGHTNESS)
	{
		if (app_window_setting_screen_ui_is_touch_on_brightness_low(event->x, event->y))
		{
			data_brightness_reduce_and_save(1);
		}
		else if (app_window_setting_screen_ui_is_touch_on_brightness_high(event->x, event->y))
		{
			data_brightness_add_and_save(1);
		}
		app_window_setting_screen_ui_show_brightness();
		gui_surface_commit();
	}
	else
	{
		entry_app_by_id(event->id);
	}
}

static unsigned char app_window_setting_screen_brightness_touch_handler(gui_touch_struct *event)
{
	short move_x = event->x - event->down_x;

	if (event->type == TOUCH_EVENT_TYPE_DOWN)
	{
		if (app_window_setting_screen_ui_is_touch_on_brightness_low(event->x, event->y))
			return 0;
		else if (app_window_setting_screen_ui_is_touch_on_brightness_high(event->x, event->y))
			return 0;
		g_setting_screen_brightness = data_brightness_get_value();
	}
	else if (event->type == TOUCH_EVENT_TYPE_MOVE)
	{
		data_brightness_set_and_save(g_setting_screen_brightness + move_x * SETTING_SCREEN_UI_BRIGHTNESS_RATIO);
		app_window_setting_screen_ui_show_brightness();
	}
	gui_surface_commit();
	return 1;
}

static void app_window_setting_screen_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_setting_screen);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface, DIRECTION_TYPE_DOWN);
	}
	else if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface, DIRECTION_TYPE_UP);
	}
	gui_surface_commit();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_setting_screen_init(void *buf)
{
}

static void app_window_setting_screen_load(void *buf)
{
	app_window_setting_screen_ui_show();
}

static void app_window_setting_screen_entry(void *buf)
{
}

static void app_window_setting_screen_exit()
{
}

static void app_window_setting_screen_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/
static const app_window_event_struct app_window_setting_screen_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_setting_screen_rolkey_handler,
		},
};

static const gui_touch_event_struct app_window_setting_screen_touch_events[] =
	{
		{
			.id = APP_INFO_ID_BRIGHTNESS,
			.touch = app_window_setting_screen_brightness_touch_handler,
		},
};

const gui_window_struct app_window_setting_screen =
	{
		.screen = &gui_screen_setting_screen,

		.init = app_window_setting_screen_init,
		.load = app_window_setting_screen_load,
		.entry = app_window_setting_screen_entry,
		.exit = app_window_setting_screen_exit,
		.destroy = app_window_setting_screen_destroy,

		.click_on_layout_item = app_window_setting_screen_click_on_layout_item,

		.event_num = countof(app_window_setting_screen_events),
		.events = app_window_setting_screen_events,

		.touch_event_num = countof(app_window_setting_screen_touch_events),
		.touch_events = app_window_setting_screen_touch_events,
};
