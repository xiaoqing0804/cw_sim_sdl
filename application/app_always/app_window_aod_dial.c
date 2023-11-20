#include "app_window_aod_dial.h"
#include "app_window_aod_dial_ui.h"
#include "app_window_aod_dial_layout.h"

static char dial_index = 0;
static char dial_flag = 0;

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_aod_dial_click_on_layout_item(gui_click_layout_struct *event)
{
	if (app_window_aod_dial_ui_is_touch_on(event->x_in_item, event->y_in_item))
	{
		if (event->id == AOD_DIAL_LAYOUT_ID_OPEN)
		{
			data_watchface_switch_standby_clock();
		}
		else if (event->id == AOD_DIAL_LAYOUT_ID_NUMBER)
		{
			if (data_watchface_get_standby_clock())
			{
				application_main_window_set_idle_index(0);
			}
		}
		else if (event->id == AOD_DIAL_LAYOUT_ID_POINTER)
		{
			if (data_watchface_get_standby_clock())
			{
				application_main_window_set_idle_index(1);
			}
		}
		app_window_aod_dial_ui_show_content();
		gui_surface_commit();
	}
}

/*-----------------------------主流程--------------------------------------*/
static void app_window_aod_dial_init(void *buf)
{
}

static void app_window_aod_dial_load(void *buf)
{
	app_window_aod_dial_ui_show();
}

static void app_window_aod_dial_entry(void *buf)
{
}

static void app_window_aod_dial_exit()
{
}

static void app_window_aod_dial_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

const gui_window_struct app_window_aod_dial =
	{
		.screen = &gui_screen_aod_dial,
		.init = app_window_aod_dial_init,
		.load = app_window_aod_dial_load,
		.entry = app_window_aod_dial_entry,
		.exit = app_window_aod_dial_exit,
		.destroy = app_window_aod_dial_destroy,

		.click_on_layout_item = app_window_aod_dial_click_on_layout_item,
};
