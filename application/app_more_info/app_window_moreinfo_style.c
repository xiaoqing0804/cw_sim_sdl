#include "app_window_moreinfo_style.h"
#include "app_window_moreinfo_style_ui.h"
#include "app_window_moreinfo_style_layout.h"
#include "app_window_moreinfo.h"

#include "debug_info.h"
#include "data_receive_package.h"
#include "application_config_app_info.h"

/*-----------------------------响应事件--------------------------------------*/
static void app_window_moreinfo_style_click_on_layout_item(gui_click_layout_struct *event)
{
	app_window_moreinfo_set(event->id);
	app_window_moreinfo_style_ui_set_checked(event->id);
	gui_surface_commit();
}

static void app_window_style_view_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&app_screen_moreinfo_style);

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

static void app_window_moreinfo_style_init(void *buf)
{
}

static void app_window_moreinfo_style_load(void *buf)
{
	app_window_moreinfo_style_ui_show();
}

static void app_window_moreinfo_style_entry(void *buf)
{
}

static void app_window_moreinfo_style_exit()
{
}

static void app_window_moreinfo_style_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_moreinfo_style_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_style_view_rolkey_handler,
		},
};

const gui_window_struct app_window_moreinfo_style =
	{
		.screen = &app_screen_moreinfo_style,

		.init = app_window_moreinfo_style_init,
		.load = app_window_moreinfo_style_load,
		.entry = app_window_moreinfo_style_entry,
		.exit = app_window_moreinfo_style_exit,
		.destroy = app_window_moreinfo_style_destroy,

		/*排版界面上响应点击事件*/
		.click_on_layout_item = app_window_moreinfo_style_click_on_layout_item,

		.event_num = countof(app_window_moreinfo_style_events),
		.events = app_window_moreinfo_style_events,
};
