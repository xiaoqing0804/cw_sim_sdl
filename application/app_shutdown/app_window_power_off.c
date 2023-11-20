#include "app_window_power_off.h"
#include "app_window_power_off_ui.h"
#include "app_window_power_off_layout.h"
#include "app_window_goodbye.h"
#include "app_window_popup_warn.h"
#include "data_manager_contact.h"
#include "bsp_includes.h"
#include "data_sos.h"

/*-----------------------------本地逻辑--------------------------------------*/

static void app_window_power_off_send_sos_hint()
{
	gui_popup_warn_struct popup_warn = {
		.text_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.text = STRING_SOS_NO_CONTACT,
	};
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_popup_warn, &popup_warn);
}

static void app_window_power_off_send_sos()
{
	if (!service_call_out_send_sos())
	{
		app_window_power_off_send_sos_hint();
	}
}

static void app_window_power_off_slide_success(unsigned short id)
{
	if (id == POWER_OFF_LAYOUT_ID_SHUTDOWN_BG)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_goodbye, (unsigned char)GOODBYE_SHUTDOWN);
	}
	else if (id == POWER_OFF_LAYOUT_ID_REBOOT_BG)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_goodbye, (unsigned char)GOODBYE_RESET);
	}
	else if (id == POWER_OFF_LAYOUT_ID_SOS_BG)
	{
		app_window_power_off_send_sos();
	}
}

/*-----------------------------事件及触屏--------------------------------------*/

static unsigned char app_window_power_off_touch_handler(gui_touch_struct *event)
{
	short move_x = event->x - event->down_x;

	if (event->type == TOUCH_EVENT_TYPE_MOVE)
	{
		app_window_power_off_ui_slide(event->id, move_x);
	}
	else if (event->type == TOUCH_EVENT_TYPE_UP)
	{
		if (app_window_power_off_ui_is_slide_over(event->id, move_x))
		{
			app_window_power_off_slide_success(event->id);
		}
		else
		{
			app_window_power_off_ui_slide(event->id, 0);
		}
	}
	gui_surface_commit();
	return 1;
}

static void app_window_power_off_key1_short(void *buf)
{
	application_go_back();
}

/*-----------------------------主流程--------------------------------------*/
static void app_window_power_off_init(void *buf)
{
}

static void app_window_power_off_load(void *buf)
{
}

static void app_window_power_off_entry(void *buf)
{
}

static void app_window_power_off_exit()
{
}

static void app_window_power_off_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_power_off_static_events[] =
	{
		{
			.id = EVENT_KEY1_SHORT,
			.handler = app_window_power_off_key1_short,
		},
};

static const gui_touch_event_struct app_window_power_off_touch_events[] =
	{
		{
			.id = POWER_OFF_LAYOUT_ID_SHUTDOWN_BG,
			.touch = app_window_power_off_touch_handler,
		},

		{
			.id = POWER_OFF_LAYOUT_ID_REBOOT_BG,
			.touch = app_window_power_off_touch_handler,
		},

		{
			.id = POWER_OFF_LAYOUT_ID_SOS_BG,
			.touch = app_window_power_off_touch_handler,
		},
};

const gui_window_struct app_window_power_off =
	{
		.screen = &app_screen_power_off,

		.init = app_window_power_off_init,
		.load = app_window_power_off_load,
		.entry = app_window_power_off_entry,
		.exit = app_window_power_off_exit,
		.destroy = app_window_power_off_destroy,

		.touch_event_num = countof(app_window_power_off_touch_events),
		.touch_events = app_window_power_off_touch_events,

		.event_num = countof(app_window_power_off_static_events),
		.events = app_window_power_off_static_events,
};
