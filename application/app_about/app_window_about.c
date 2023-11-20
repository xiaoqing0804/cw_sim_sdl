#include "app_window_about.h"
#include "app_window_about_ui.h"
#include "app_window_about_layout.h"

#include "gui_surface_layout_scroll.h"

#include "sys_init.h"
#include "data_common.h"
#include "bsp_includes.h"

#include "app_window_about_layout.h"
#include "gui_surface_box_label.h"
#include "data_receive_package.h"
#include "gui_surface_box_image.h"
#include "app_flashlight\app_window_tptest.h"
#include "app_test\app_window_pwrloss.h"

#include "app_test\app_window_hrtest.h" //hr test R
#include "app_test/app_window_factory.h"

/*-----------------------------定义--------------------------------------*/
static unsigned char g_ver_click_count;
static unsigned char g_hr_click_count; // hr test R
static unsigned char factory_flg = 0;

/*-----------------------------声明--------------------------------------*/
extern int data_manager_flash_get_checksum(void);

/*-----------------------------事件--------------------------------------*/

static void app_window_about_about_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_about);

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

static void app_window_about_ver_click_handler(gui_click_struct *event)
{
	if (++g_ver_click_count > 0)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_pwrloss, NULL);
	}
}

static unsigned char app_window_factory_event_touch(gui_touch_struct *event)
{
	SYS_DEBUG("app_window_factory_event_touch =%d", factory_flg);
	if (event->type == TOUCH_EVENT_TYPE_UP)
	{
		if (event->direction == DIRECTION_TYPE_LEFT)
		{
			application_go_back();
		}
		else if (event->direction == DIRECTION_TYPE_RIGHT)
		{
			if (++factory_flg >= 5)
			{
				application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_factory, NULL);
			}
		}
	}
	return 1;
}


/// @brief 
/// @param event 
static void app_window_about_hr_click_handler(gui_click_struct *event) // hr test R
{
	if (++g_hr_click_count > 2)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_hrtest, NULL);
	}
}

static void app_window_about_long_touch_handler(gui_click_struct *event)
{
	SYS_DEBUG("window_flashlight_touch longpress");
	application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_tptest, NULL);
}

/*-----------------------------系统流程--------------------------------------*/

static void app_window_about_init(void *buf)
{
}

static void app_window_about_load(void *buf)
{
	g_ver_click_count = 0;
	factory_flg = 0;
	g_hr_click_count = 0; // hr test R

	app_window_about_ui_show();
}

static void app_window_about_entry(void *buf)
{
}

static void app_window_about_exit()
{
}

static void app_window_about_destroy()
{
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_about_static_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_about_about_rolkey_handler,
		},
};

static const gui_touch_event_struct app_window_about_touch_events[] =
	{
		{
			.id = ABOUT_LAYOUT_ID_DEVSION,
			.click = app_window_about_ver_click_handler,
		},
		{
			// hr test R
			.id = ABOUT_LAYOUT_ID_CRC_ID,
			.click = app_window_about_hr_click_handler,
		},
		{
			.id = 0xFFFF,
			.touch = app_window_factory_event_touch,
			.long_touch = app_window_about_long_touch_handler,
		},
};

const gui_window_struct app_window_about =
	{
		.screen = &gui_screen_about,
		.init = app_window_about_init,
		.load = app_window_about_load,
		.entry = app_window_about_entry,
		.exit = app_window_about_exit,
		.destroy = app_window_about_destroy,

		.event_num = countof(app_window_about_static_events),
		.events = app_window_about_static_events,

		.touch_event_num = countof(app_window_about_touch_events),
		.touch_events = app_window_about_touch_events,
};
