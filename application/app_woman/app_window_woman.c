#include "app_window_woman.h"
#include "app_window_woman_ui.h"
#include "app_window_woman_layout.h"
#include "app_window_woman_info.h"

#include "data_common.h"
#include "gui_surface.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_woman_touch_hander(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_woman_info, NULL);
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_woman_init(void *buf)
{
}

static void app_window_woman_load(void *buf)
{
	app_window_woman_ui_change_curr_period(g_woman_data.status);
}

static void app_window_woman_entry(void *buf)
{
}

static void app_window_woman_exit()
{
}

static void app_window_woman_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_woman_touch_events[] =
	{
		{
			.id = WOMAN_LAYOUT_ID_PIC_BOTTOM,
			.click = app_window_woman_touch_hander,
		},
};

const gui_window_struct app_window_woman =
	{
		.screen = &gui_screen_woman,
		.init = app_window_woman_init,
		.load = app_window_woman_load,
		.entry = app_window_woman_entry,
		.exit = app_window_woman_exit,
		.destroy = app_window_woman_destroy,

		.touch_event_num = countof(app_window_woman_touch_events),
		.touch_events = app_window_woman_touch_events,
};
