#include "app_window_popup_yesno.h"
#include "app_window_popup_yesno_ui.h"
#include "app_window_popup_yesno_layout.h"

/*-----------------------------定义--------------------------------------*/
static gui_popup_yesno_struct g_popup_yesno = {0};

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_popup_yesno_touch_event_yes_handle(gui_click_struct *event)
{
	if (g_popup_yesno.click_on_yes)
	{
		g_popup_yesno.click_on_yes();
	}
}
static void app_window_popup_yesno_touch_event_no_handle(gui_click_struct *event)
{
	if (g_popup_yesno.click_on_no)
	{
		g_popup_yesno.click_on_no();
	}
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_popup_yesno_init(void *buf)
{
	memcpy(&g_popup_yesno, buf, sizeof(gui_popup_yesno_struct));
}

static void app_window_popup_yesno_load(void *buf)
{
	app_window_popup_yesno_ui_show_text(&g_popup_yesno);
}

static void app_window_popup_yesno_entry(void *buf)
{
}

static void app_window_popup_yesno_exit()
{
}

static void app_window_popup_yesno_destroy()
{
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_popup_yesno_static_events[] =
	{
		{
			.id = EVENT_KEY1_SHORT,
			.handler = NULL,
		},
		{
			.id = EVENT_BL_TIMEOUT,
			.handler = NULL,
		},
};

static const gui_touch_event_struct app_window_popup_yesno_touch_events[] =
	{
		{
			.id = POPUP_YESNO_LAYOUT_ID_YES,
			.click = app_window_popup_yesno_touch_event_yes_handle,
		},
		{
			.id = POPUP_YESNO_LAYOUT_ID_NO,
			.click = app_window_popup_yesno_touch_event_no_handle,
		},

};

const gui_window_struct app_window_popup_yesno =
	{
		.screen = &gui_popup_yesno_screen,

		.init = app_window_popup_yesno_init,
		.load = app_window_popup_yesno_load,
		.entry = app_window_popup_yesno_entry,
		.exit = app_window_popup_yesno_exit,
		.destroy = app_window_popup_yesno_destroy,

		.touch_event_num = countof(app_window_popup_yesno_touch_events),
		.touch_events = app_window_popup_yesno_touch_events,

		.event_num = countof(app_window_popup_yesno_static_events),
		.events = app_window_popup_yesno_static_events,
};
