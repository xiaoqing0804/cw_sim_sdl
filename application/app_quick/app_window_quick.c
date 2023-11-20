#include "app_window_quick.h"
#include "app_window_quick_layout.h"
#include "app_window_quick_ui.h"

#include "debug_info.h"

#include "data_common.h"
#include "data_transfer.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"

#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "app_disturb/app_window_disturb.h"
#include "app_setting/app_window_setting.h"
#include "app_lcd_timeout/app_window_lcd_time.h"
#include "app_flashlight/app_window_flashlight.h"
#include "app_main/app_window_main_locker.h"
#include "app_main/app_window_main_watchface_select.h"
#include "app_siri/app_siri_window.h"
#include "app_brightness/app_window_brightness.h"

#include "app_reboot/app_window_reboot.h"

#include "app_reset/app_window_reset.h"
#include "app_games/app_window_games_list.h"
#include "app_charger/app_window_charger.h"
#include "bsp_btaud/ext_btaud.h"

#include "app_about/app_window_about.h"
#include "app_music/app_window_music.h"
#include "app_messgae/app_window_message_list.h"
#include "app_sport/app_window_sportlist.h"
#include "app_QR/app_window_QR.h"
#include "app_alarm/app_window_alarm_clock.h"
#include "app_more_info/app_window_moreinfo_style.h"
#include "app_find/app_window_findphone.h"

extern const gui_window_struct app_window_localmusic;
extern const gui_window_struct app_window_record;
extern unsigned char wakey_flag;

/*-----------------------------系统事件--------------------------------------*/
static void app_window_quick_init(void *buf)
{
}

static void app_window_ble_status(void *buf)
{
}

static void app_window_quick_load(void *buf)
{
	app_window_quick_ui_show();
}

static void app_window_quick_entry(void *buf)
{
}

static void app_window_quick_exit()
{
}

static void app_window_quick_destroy()
{
}

/*-----------------------------响应事件--------------------------------------*/

static void app_window_quick_alarm_event_touch(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_clock, NULL);
}

static void app_window_quick_hfp_event_touch(gui_click_struct *event)
{
	static unsigned char quick_hfp = 0;
	gui_box_struct *call_onoff = gui_surface_get_box(&gui_screen_quick, QUICK_ID_SYS_HFP);

	quick_hfp = ext_btaud_onoff_get();
	quick_hfp = !quick_hfp;

#if defined(__EXT_BT_AUDIO__)
	if (quick_hfp)

	{
		g_manual_hfp_flag = 0;
		ext_btaud_onoff_set(1);
		gui_surface_box_image_change(call_onoff, (const picture_info_struct *)&pic_quick_hfp_yes_info);
	}
	else
	{
		g_manual_hfp_flag = 1;
		ext_btaud_onoff_set(0);
		gui_surface_box_image_change(call_onoff, (const picture_info_struct *)&pic_quick_hfp_no_info);
	}

	gui_surface_commit();

#endif
}

static void app_window_quick_more_event_touch(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_seting, NULL);
}

static void app_window_quick_disturb_event_touch(gui_click_struct *event)
{
	if (g_forget_disturb.switch_flag)
	{
		g_forget_disturb.switch_flag = !g_forget_disturb.switch_flag;
		gui_box_struct *box = gui_surface_get_box(&gui_screen_quick, (unsigned short)QUICK_ID_SYS_DISTURB);
		gui_surface_box_image_change(box, (const picture_info_struct *)&pic_quick_disturb_off_info);
	}
	else
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_disturb, NULL);
	}

	block_save_user_info(&g_forget_disturb);
	push_data_type_to_queue(DATA_TYPE_FORGET_DISTURB);
	gui_surface_commit();
}
static void app_window_quick_bright_event_touch(gui_click_struct *event)
{
	forget_aod.switch_flag = !forget_aod.switch_flag;
	block_save_user_info(&forget_aod);
	application_reset_display_timeout(0);
	app_window_quick_ui_show();;
	gui_surface_commit();
}

/*-----------------------------配置--------------------------------------*/
static const gui_touch_event_struct app_window_quick_touch_events[] =
	{

		{
			.id = QUICK_ID_SYS_ALARM,
			.click = app_window_quick_alarm_event_touch,
		},

		{
			.id = QUICK_ID_SYS_HFP,
			.click = app_window_quick_hfp_event_touch,
		},

		{
			.id = QUICK_ID_SYS_MORE,
			.click = app_window_quick_more_event_touch,
		},

		{
			.id = QUICK_ID_SYS_DISTURB,
			.click = app_window_quick_disturb_event_touch,
		},

		{
			.id = QUICK_ID_SYS_BRIGHT,
			.click = app_window_quick_bright_event_touch,
		},
};

static void app_window_btaud_status(void *buf)
{
	app_window_quick_load(NULL);
	gui_surface_commit();
}

static const app_window_event_struct app_window_quick_events[] =
	{
		{
			EVENT_BTAUD_STATUS,
			app_window_btaud_status,
		},
		{
			EVENT_BLE_CONNECT_STATUS,
			app_window_ble_status,
		},
		{
			EVENT_UPDATE_FORGET_DISTURB,
			app_window_btaud_status,
		},
		{
			.id = EVENT_UPDATE_SYS_TIME,
			.handler = app_window_btaud_status,
		},
};

static const gui_window_config_struct app_window_quick_config =
	{
		.forbid_gesture_back = 1,
};

const gui_window_struct app_window_quick =
	{
		.screen = &gui_screen_quick,

		.config = &app_window_quick_config,

		.init = app_window_quick_init,
		.load = app_window_quick_load,
		.entry = app_window_quick_entry,
		.exit = app_window_quick_exit,
		.destroy = app_window_quick_destroy,

		.touch_event_num = countof(app_window_quick_touch_events),
		.touch_events = app_window_quick_touch_events,

		.event_num = countof(app_window_quick_events),
		.events = app_window_quick_events,
};
