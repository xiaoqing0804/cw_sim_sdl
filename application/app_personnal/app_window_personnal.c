#include "app_window_personnal.h"
#include "app_window_personnal_ui.h"
#include "app_window_personnal_layout.h"

#include "debug_info.h"
#include "application_config_app_info.h"
#include "app_window_widget_delete.h"
#include "application_titlebar.h"

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_personnal_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_personnal);

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

static void app_window_personnal_ble_status(void *buf)
{
	app_window_personnal_ui_show();
	gui_surface_commit();
}

static void app_window_personnal_unit_update(void* buf)
{
	app_window_personnal_ui_show();
	gui_surface_commit();
}


/*-----------------------------主流程--------------------------------------*/

static void app_window_personnal_init(void *buf)
{
}

static void app_window_personnal_load(void *buf)
{
	app_window_personnal_ui_show();
}

static void app_window_personnal_entry(void *buf)
{
}

static void app_window_personnal_exit()
{
}

static void app_window_personnal_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_personnal_events[] =
	{
		{
			.id = EVENT_BLE_CONNECT_STATUS,
			.handler = app_window_personnal_ble_status,
		},
		{
			.id = EVENT_UPDATE_UNIT_SETTING,
			.handler = app_window_personnal_unit_update,
		},
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_personnal_rolkey_handler,
		},
};

const gui_window_struct app_window_personnal =
	{
		.screen = &gui_screen_personnal,

		.init = app_window_personnal_init,
		.load = app_window_personnal_load,
		.entry = app_window_personnal_entry,
		.exit = app_window_personnal_exit,
		.destroy = app_window_personnal_destroy,

		.event_num = countof(app_window_personnal_events),
		.events = app_window_personnal_events,
};
