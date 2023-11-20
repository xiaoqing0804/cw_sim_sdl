#include "app_window_setting.h"
#include "app_window_setting_layout.h"
#include "app_window_setting_ui.h"

#include "app_window_personnal.h"

#include "debug_info.h"
#include "application_config_app_info.h"
#include "app_window_widget_delete.h"
#include "application_titlebar.h"

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_setting_click_on_layout_item(gui_click_layout_struct *event)
{
	const gui_window_struct *window = app_window_setting_ui_find_app(event->id);
	if (window != NULL)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, window, NULL);
	}
}

static void app_window_setting_long_touch_handler(gui_click_struct *event)
{
}

static void app_window_setting_list_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_setting);

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

static void app_window_setting_ble_status(void *buf)
{
	app_window_setting_ui_show_content();
	gui_surface_commit();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_setting_list_init(void *buf)
{
}

static void app_window_setting_list_load(void *buf)
{
	app_window_setting_ui_show();
}

static void app_window_setting_list_entry(void *buf)
{
}

static void app_window_setting_list_exit()
{
}

static void app_window_setting_list_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_setting_touch_events[] =
	{
		{
			.id = 0xFFFF, // fullscreen.
			.long_touch = app_window_setting_long_touch_handler,
		},
};

static const app_window_event_struct app_window_setting_common_events[] =
	{
		{
			.id = EVENT_BLE_CONNECT_STATUS,
			.handler = app_window_setting_ble_status,
		},
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_setting_list_rolkey_handler,
		},
};

const gui_window_struct app_window_seting =
	{
		.screen = &gui_screen_setting,

		.init = app_window_setting_list_init,
		.load = app_window_setting_list_load,
		.entry = app_window_setting_list_entry,
		.exit = app_window_setting_list_exit,
		.destroy = app_window_setting_list_destroy,

		.click_on_layout_item = app_window_setting_click_on_layout_item,

		.touch_event_num = countof(app_window_setting_touch_events),
		.touch_events = app_window_setting_touch_events,

		.event_num = countof(app_window_setting_common_events),
		.events = app_window_setting_common_events,
};
