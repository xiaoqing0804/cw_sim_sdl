#include "app_window_disturb.h"
#include "app_window_disturb_ui.h"
#include "app_window_disturb_layout.h"

#include "debug_info.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "data_receive_package.h"
#include "gui_window.h"

#include "application_titlebar.h"

#include "app_quick/app_window_quick.h"

/*-----------------------------事件-------------------------------------*/
static void app_window_disturb_touch_event_click_disturb_on(gui_click_struct *event)
{
	if (DISTURB_LAYOUT_ID_YES == event->id)
	{
		g_forget_disturb.switch_flag = !g_forget_disturb.switch_flag;
		block_save_user_info(&g_forget_disturb);
		push_data_type_to_queue(DATA_TYPE_FORGET_DISTURB);
		application_go_back();
	}
	else if (DISTURB_LAYOUT_ID_NO == event->id)
	{
		application_go_back();
	}
}

static void disturb_child_window_shake_device(void *buf)
{
}

static void disturb_child_window_disturb(void *buf)
{
}

static void app_window_disturb_static_event_act(void *buf)
{
}

static void app_window_disturb_status(void *buf)
{
	app_window_disturb_ui_show();
	gui_surface_commit();
}

/*-----------------------------系统流程--------------------------------------*/

static void app_window_disturb_init(void *buf)
{
}

static void app_window_disturb_load(void *buf)
{
	app_window_disturb_ui_show();
}

static void app_window_disturb_entry(void *buf)
{
}

static void app_window_disturb_exit()
{
}

static void app_window_disturb_destroy()
{
}

/*-----------------------------触摸事件--------------------------------------*/

static const gui_touch_event_struct app_window_disturb_touch_events[] =
	{
		{
			.id = DISTURB_LAYOUT_ID_YES, // �ؼ�ID.
			.click = app_window_disturb_touch_event_click_disturb_on,
		},
		{
			.id = DISTURB_LAYOUT_ID_NO, // �ؼ�ID.
			.click = app_window_disturb_touch_event_click_disturb_on,
		},

};

static const app_window_event_struct app_window_disturb_static_events[] =
	{
		{
			.id = EVENT_SHAKE_DEVICE, // �ؼ�ID.
			.handler = disturb_child_window_shake_device,
		},
		{
			.id = EVENT_PHOTOGRAPH, // �ؼ�ID.
			.handler = disturb_child_window_disturb,
		},
		{EVENT_UPDATE_FORGET_DISTURB, app_window_disturb_status},

		{
			.id = EVENT_ACT, // �ؼ�ID.
			.handler = app_window_disturb_static_event_act,
		},
};

const gui_window_struct app_window_disturb =
	{
		.screen = &gui_screen_disturb,
		.init = app_window_disturb_init,
		.load = app_window_disturb_load,
		.entry = app_window_disturb_entry,
		.exit = app_window_disturb_exit,
		.destroy = app_window_disturb_destroy,

		.touch_event_num = countof(app_window_disturb_touch_events),
		.touch_events = app_window_disturb_touch_events,

		.event_num = countof(app_window_disturb_static_events),
		.events = app_window_disturb_static_events,
};
