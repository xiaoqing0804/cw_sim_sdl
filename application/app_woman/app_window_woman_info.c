#include "app_window_woman_info.h"
#include "app_window_woman_info_layout.h"
#include "app_window_woman_info_ui.h"

#include "data_common.h"
#include "gui_surface.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_box_layout_item.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_woman_info_touch_hander(gui_click_struct *event)
{
	gui_click_struct *woman_info = (gui_click_struct *)event;

	if (woman_info->id == WOMAN_INFO_LAYOUT_ID_YUEJIN)
	{
		g_woman_data.status = WOMAN_STATUS_YUEJIN;
	}
	else if (woman_info->id == WOMAN_INFO_LAYOUT_ID_ANQUAN)
	{
		g_woman_data.status = WOMAN_STATUS_ANQUAN;
	}
	else if (woman_info->id == WOMAN_INFO_LAYOUT_ID_PAIRUAN)
	{
		g_woman_data.status = WOMAN_STATUS_PAILUAN;
	}
	application_go_back();
}

static void app_window_woman_info_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_woman_info);

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

/*-----------------------------主流程--------------------------------------*/

static void app_window_woman_info_init(void *buf)
{
}

static void app_window_woman_info_load(void *buf)
{
	app_window_woman_info_ui_show(&g_woman_data);
}

static void app_window_woman_info_entry(void *buf)
{
}

static void app_window_woman_info_exit()
{
}

static void app_window_woman_info_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_woman_info_static_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_woman_info_rolkey_handler,
		},
};

static const gui_touch_event_struct app_window_woman_info_touch_events[] =
	{
		{
			.id = WOMAN_INFO_LAYOUT_ID_YUEJIN,
			.click = app_window_woman_info_touch_hander,
		},
		{
			.id = WOMAN_INFO_LAYOUT_ID_ANQUAN,
			.click = app_window_woman_info_touch_hander,
		},
		{
			.id = WOMAN_INFO_LAYOUT_ID_PAIRUAN,
			.click = app_window_woman_info_touch_hander,
		},
};

const gui_window_struct app_window_woman_info =
	{
		.screen = &gui_screen_woman_info,
		.init = app_window_woman_info_init,
		.load = app_window_woman_info_load,
		.entry = app_window_woman_info_entry,
		.exit = app_window_woman_info_exit,
		.destroy = app_window_woman_info_destroy,

		.touch_event_num = countof(app_window_woman_info_touch_events),
		.touch_events = app_window_woman_info_touch_events,

		.event_num = countof(app_window_woman_info_static_events),
		.events = app_window_woman_info_static_events,
};
