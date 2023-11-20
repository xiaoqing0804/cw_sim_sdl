#include "app_window_setting_common.h"
#include "app_window_setting_common_ui.h"
#include "app_window_setting_common_layout.h"

#include "debug_info.h"
#include "application_config_app_info.h"
#include "app_window_widget_delete.h"
#include "gui_surface_layout_listview.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_setting_common_click_on_layout_item(gui_click_layout_struct *event)
{
	entry_app_by_id((APP_INFO_ID)event->id);
}

static void app_window_setting_common_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_setting_common);

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

static void app_window_setting_common_init(void *buf)
{
}

static void app_window_setting_common_load(void *buf)
{
	app_window_setting_common_ui_show();
}

static void app_window_setting_common_entry(void *buf)
{
}

static void app_window_setting_common_exit()
{
}

static void app_window_setting_common_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_setting_common_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_setting_common_rolkey_handler,
		},
};

const gui_window_struct app_window_setting_common =
	{
		.screen = &gui_screen_setting_common,

		.init = app_window_setting_common_init,
		.load = app_window_setting_common_load,
		.entry = app_window_setting_common_entry,
		.exit = app_window_setting_common_exit,
		.destroy = app_window_setting_common_destroy,

		.click_on_layout_item = app_window_setting_common_click_on_layout_item,

		.event_num = countof(app_window_setting_common_events),
		.events = app_window_setting_common_events,
};
