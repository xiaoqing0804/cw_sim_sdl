#include "app_window_brightness.h"
#include "app_window_brightness_layout.h"
#include "app_window_brightness_ui.h"

#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_manager_user_info.h"
#include "data_common.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box.h"
#include "gui_surface_box_image.h"
#include "application_titlebar.h"

static unsigned char m_save_brightness = 0;
static unsigned char g_brightness_level = 0;

/*-------------------------事件流程------------------------------------*/

/// @brief 背光亮度
/// @param brightness_level
static void app_window_light_set_backlight(int brightness_level)
{
	g_brightness = brightness_level * BRIGHTNESS_LEVEL_GAP;
	oled_backlight_set();
	block_save_user_info(&g_brightness);
}

/// @brief 背光亮度改变事件
/// @param
static void app_window_light_update()
{
	app_window_light_set_backlight(g_brightness_level);
	app_window_brightness_ui_update_line(g_brightness_level);
}

/// @brief 拨码器转动改变背光亮度
/// @param dlt
static void app_window_light_change_level(short dlt)
{
	g_brightness_level += dlt;
	if (g_brightness_level > BRIGHTNESS_TOTAL_LEVEL)
		g_brightness_level -= BRIGHTNESS_TOTAL_LEVEL;
	else if (g_brightness_level < 1)
		g_brightness_level += BRIGHTNESS_TOTAL_LEVEL;
}
static void app_window_light_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	short dlt = (rolkey->rotate == ROTATE_TYPE_BACKWARD) ? -1 : 1;
	app_window_light_change_level(dlt);
	app_window_light_update();
}

/// @brief 滑动改变背光亮度
/// @param event
/// @return
static unsigned char app_window_set_brightness(gui_touch_struct *event)
{
	if (event->type == TOUCH_EVENT_TYPE_MOVE)
	{
		if (gui_run_time_lock())
			return 1;

		if (event->direction == DIRECTION_TYPE_LEFT)
		{
			application_go_back();
		}
		else if (event->direction == DIRECTION_TYPE_UP)
		{
			if (--g_brightness_level < 1)
				g_brightness_level += BRIGHTNESS_TOTAL_LEVEL;

			app_window_brightness_ui_update_line(g_brightness_level);
		}
		else if (event->direction == DIRECTION_TYPE_DOWN)
		{
			if (++g_brightness_level > BRIGHTNESS_TOTAL_LEVEL)
				g_brightness_level = 1;

			app_window_brightness_ui_update_line(g_brightness_level);
		}
		g_brightness = g_brightness_level * BRIGHTNESS_LEVEL_GAP;
		oled_backlight_set();
		return 1;
	}
	else if (event->type == TOUCH_EVENT_TYPE_DOWN)
	{
		return 1;
	}
	return 0;
}

/// @brief 亮度调节结束事件
/// @param envent
static void app_window_brightness_ok(gui_click_struct *envent)
{
	app_window_light_set_backlight(g_brightness_level);
	application_go_back();
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_light_init(void *buf)
{
	m_save_brightness = oled_backlight_get();
	g_brightness_level = m_save_brightness / BRIGHTNESS_LEVEL_GAP;
}

static void app_window_light_load(void *buf)
{
	app_window_brightness_ui_update_line(g_brightness_level);

}

static void app_window_light_entry(void *buf)
{
}

static void app_window_light_exit()
{
}

static void app_window_light_destroy()
{
}

/*-----------------------------触摸事件--------------------------------------*/
static const gui_touch_event_struct app_window_light_touch_events[] =
	{
		{
			.id = LIGHT_LAYOUT_ID_PIC,
			.click = app_window_brightness_ok,
		},

		{
			.id = LIGHT_LAYOUT_BG_ID,
			.touch = app_window_set_brightness,
		},
};

static const app_window_event_struct app_window_light_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_light_rolkey_handler,
		},
};

const gui_window_struct app_window_brightness =
	{
		.screen = &gui_screen_light,

		.init = app_window_light_init,
		.load = app_window_light_load,
		.entry = app_window_light_entry,
		.exit = app_window_light_exit,
		.destroy = app_window_light_destroy,

		.touch_event_num = countof(app_window_light_touch_events),
		.touch_events = app_window_light_touch_events,

		.event_num = countof(app_window_light_events),
		.events = app_window_light_events,
};
