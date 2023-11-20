#include "app_window_photograph.h"
#include "app_window_photograph_ui.h"
#include "app_window_photograph_layout.h"

#include "debug_info.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "arithmetic_steps.h"
#include "data_receive_package.h"

#include "gui_window.h"

#include "app_widget/app_window_widget_delete.h"

#define DAL_TIME 1000
static uint32_t m_last_time = 0;

/*-------------------------------------------------------------------*/
static void app_window_photograph_touch_handler(gui_click_struct *event)
{
	if (is_exist_widget_app(APP_INFO_ID_PHOTO))
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_PHOTO);
	}
}

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_photograph_init(void *buf)
{
	shake_set_onoff(1);
}

static void app_window_photograph_load(void *buf)
{
	app_window_photograph_ui_show();
}

static void app_window_photograph_entry(void *buf)
{
}

static void app_window_photograph_exit()
{
}

static void app_window_photograph_destroy()
{
	shake_set_onoff(0);
	take_photo(0);
}

static void app_window_photograph_ble_status(void *buf)
{
	app_window_photograph_load(NULL);
}

static void photograph_child_window_shake_device(void *buf)
{

	if (0 == get_ble_appconnect())
		return;

	if (0 == g_photograph_info.onoff)
	{
		application_go_back();
	}

	if (HAL_GetTickMS() > (m_last_time + DAL_TIME))
	{
		m_last_time = HAL_GetTickMS();
		take_photo(1);
		send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
	}
}

static void photograph_child_window_photograph(void *buf)
{
	if (0 == g_photograph_info.onoff)
	{
		application_go_back();
	}
}

/*-----------------------------����--------------------------------------*/

static void app_window_photograph_yes_touch_event_click_on(gui_click_struct *event)
{

	if (0 == get_ble_appconnect())
	{
		return;
	}
	if (HAL_GetTickMS() > (m_last_time + DAL_TIME))
	{
		m_last_time = HAL_GetTickMS();
		take_photo(1);
		send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
	}
}
static const gui_touch_event_struct app_window_photograph_touch_events[] =
	{
		{
			.id = PHOTOGRAPH_ID_TEXT, // �ؼ�ID.
			.click = app_window_photograph_yes_touch_event_click_on,
		},
		{
			.id = PHOTOGRAPH_ID_YES, // �ؼ�ID.
			.click = app_window_photograph_yes_touch_event_click_on,
		},
		{
			.id = 0xFFFF, // fullscreen.
			.long_touch = app_window_photograph_touch_handler,
		},

};

static const app_window_event_struct app_window_photograph_events[] =
	{
		{
			.id = EVENT_SHAKE_DEVICE, // �ؼ�ID.
			.handler = photograph_child_window_shake_device,
		},
		{
			.id = EVENT_PHOTOGRAPH, // �ؼ�ID.
			.handler = photograph_child_window_photograph,
		},

		{
			.id = EVENT_BLE_CONNECT_STATUS,
			.handler = app_window_photograph_ble_status,

		},
		{
			.id = EVENT_BL_TIMEOUT,
			.handler = NULL,
		},

};

const gui_window_struct app_window_photograph =
	{
		.screen = &app_photo_layout_screen,

		.init = app_window_photograph_init,
		.load = app_window_photograph_load,
		.entry = app_window_photograph_entry,
		.exit = app_window_photograph_exit,
		.destroy = app_window_photograph_destroy,

		.touch_event_num = countof(app_window_photograph_touch_events),
		.touch_events = app_window_photograph_touch_events,

		.event_num = countof(app_window_photograph_events),
		.events = app_window_photograph_events,
};
