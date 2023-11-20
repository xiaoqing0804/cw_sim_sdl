#include "app_window_key_setting_click.h"
#include "app_window_key_setting_click_ui.h"
#include "app_window_key_setting_click_layout.h"
#include "app_window_key_setting_click_type.h"
#include "data_key_define.h"
#include "config_key_define.h"

#include "app_window_moreinfo.h"
#include "data_receive_package.h"
#include "application_config_app_info.h"

/*-----------------------------响应事件--------------------------------------*/
static void app_window_key_setting_click_click_on_layout_item(gui_click_layout_struct *event)
{
	app_window_key_setting_click_type_set_key(event->id);
	app_window_key_setting_click_ui_list_refresh();
	gui_surface_commit();
}

static void app_window_key_setting_click_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&app_screen_key_setting_click);

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

static void app_window_key_setting_click_init(void *buf)
{
	unsigned int type = (unsigned char)buf;
	app_window_key_setting_click_type_set_type(type);
}

static void app_window_key_setting_click_load(void *buf)
{
	unsigned short string_id = app_window_key_setting_click_type_get_string_id();
	app_window_key_setting_click_ui_show(string_id);
}

static void app_window_key_setting_click_entry(void *buf)
{
}

static void app_window_key_setting_click_exit()
{
}

static void app_window_key_setting_click_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_key_setting_click_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_key_setting_click_rolkey_handler,
		},
};

const gui_window_struct app_window_key_setting_click =
	{
		.screen = &app_screen_key_setting_click,

		.init = app_window_key_setting_click_init,
		.load = app_window_key_setting_click_load,
		.entry = app_window_key_setting_click_entry,
		.exit = app_window_key_setting_click_exit,
		.destroy = app_window_key_setting_click_destroy,

		/*排版界面上响应点击事件*/
		.click_on_layout_item = app_window_key_setting_click_click_on_layout_item,

		.event_num = countof(app_window_key_setting_click_events),
		.events = app_window_key_setting_click_events,
};
