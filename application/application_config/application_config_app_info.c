#include "debug_info.h"
#include "data_common.h"
#include "app_config.h"

#include "application_config_app_info.h"
#include "application_config_list.h"
#include "app_games/app_window_games_list.h"
#include "app_window_setting_screen.h"
#include "service_call_out.h"

extern const gui_window_struct app_window_breath;
extern const gui_window_struct app_window_heartrate;
extern const gui_window_struct app_window_QR;
extern const gui_window_struct app_window_WOMAN;
extern const gui_window_struct app_window_main_watchface_select;
extern const gui_window_struct app_window_findphone;
extern const gui_window_struct app_window_music;
extern const gui_window_struct app_window_o2;
extern const gui_window_struct app_window_photograph;
extern const gui_window_struct app_window_seting;
extern const gui_window_struct app_window_sport;
extern const gui_window_struct app_window_steps;
extern const gui_window_struct app_window_stopwatch;
extern const gui_window_struct app_window_countdown;
extern const gui_window_struct app_window_countdown_my_time;
extern const gui_window_struct app_window_about;
extern const gui_window_struct app_window_weather;
extern const gui_window_struct app_window_reset;
extern const gui_window_struct app_window_shutdown;
extern const gui_window_struct app_window_lcd_time;
extern const gui_window_struct app_window_sleep;
extern const gui_window_struct app_window_vib;
extern const gui_window_struct app_window_reboot;
extern const gui_window_struct app_window_brightness;
extern const gui_window_struct app_window_bp;
extern const gui_window_struct app_window_telephone;
extern const gui_window_struct app_siri_window;
extern const gui_window_struct app_window_message_list;
extern const gui_window_struct app_window_call_clog;
extern const gui_window_struct app_window_call_phonebook;
extern const gui_window_struct app_window_calendar;
extern const gui_window_struct app_window_calculator;
extern const gui_window_struct app_window_qr_card_list;
extern const gui_window_struct app_window_language_list;
extern const gui_window_struct app_window_password_setting;
extern const gui_window_struct app_window_disturb;
extern const gui_window_struct app_window_key_define;
extern const gui_window_struct app_window_wakey_time;
extern const gui_window_struct app_window_aod_dial;
extern const gui_window_struct app_window_clock;
extern const gui_window_struct app_window_call_list;
extern const gui_window_struct app_window_sos;
extern const gui_window_struct app_window_widget_delete;
extern const gui_window_struct app_window_main_locker;
extern const gui_window_struct app_window_woman; // Ů����������
extern const gui_window_struct app_window_games_list;
extern const gui_window_struct app_window_setting_common;
extern const gui_window_struct app_window_sos_setting;

#if GUI_SIDEBAR_SUPPORT
extern void app_window_sidebar_update_connrec(unsigned int app_id);
#endif

extern void app_window_alipay_entry(app_info_struct *app_info); // TCFG_PAY_ALIOS_ENABLE

static void app_entry_common(app_info_struct *app_info)
{
	const gui_window_struct *window = app_info->window;

	if (app_info->id == APP_INFO_ID_HOME)
	{
		application_goto_main();
		return;
	}

	if (app_info->id == APP_INFO_ID_LOCK) // 点击锁屏
	{
		set_locked_screen(1);
		return;
	}

	if (app_info->id == APP_INFO_ID_SOS)
	{
		unsigned char ret = service_call_out_send_sos();
		if (ret) {
			if (2 == service_call_get_sos_status()) {
				window = &app_window_sos_setting;
			}
			else {
				return;
			}
		}
	}

	if (window != NULL)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, window, NULL);
	}
}

static const app_info_struct app_info_list[] =
	{
		{
			APP_INFO_ID_BREATHE,
			STRING_BREATH,
			&app_window_breath,
			APP_SIDEBAR_PIC(breathe),
			APP_WIDGET_PIC(breath),
			APP_PICS(breath),
			app_entry_common,
		},

		{
			APP_INFO_ID_CALL,
			STRING_TELEPHONE,
			&app_window_call_list,
			APP_SIDEBAR_PIC(call),
			APP_WIDGET_PIC(telephone),
			APP_PICS(telephone),
			app_entry_common,
		},

		{
			APP_INFO_ID_FIND,
			STRING_FIND_PHONE,
			&app_window_findphone,
			APP_SIDEBAR_PIC(find),
			NULL, //&pic_app_widget_find_info,
			APP_PICS(findphone),
			app_entry_common,
		},

		{
			APP_INFO_ID_HR,
			STRING_HR,
			&app_window_heartrate,
			APP_SIDEBAR_PIC(hr),
			APP_WIDGET_PIC(hr),
			APP_PICS(hr),
			app_entry_common,
		},

		{
			APP_INFO_ID_METT,
			STRING_METT,
			NULL,
			NULL,
			NULL,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_MUSIC,
			STRING_MUSIC,
			&app_window_music,
			APP_SIDEBAR_PIC(music),
			APP_WIDGET_PIC(music),
			APP_PICS(music),
			app_entry_common,
		},

		{
			APP_INFO_ID_O2,
			STRING_O2,
			&app_window_o2,
			APP_SIDEBAR_PIC(o2),
			APP_WIDGET_PIC(O2),
			APP_PICS(O2),
			app_entry_common,
		},

		{
			APP_INFO_ID_PHOTO,
			STRING_PHOTOGRAPH,
			&app_window_photograph,
			APP_SIDEBAR_PIC(photo),
			APP_WIDGET_PIC(photograph),
			APP_PICS(photograph),
			app_entry_common,
		},

		{
			APP_INFO_ID_QR,
			STRING_QR_CODE,
			&app_window_QR,
			NULL,
			NULL,
			APP_PICS(QR_code),
			app_entry_common,
		},

		{
			APP_INFO_ID_SETTING,
			STRING_SETTING,
			&app_window_seting,
			NULL, // APP_PIC(setting),
			NULL, //&pic_app_widget_setting_info,
			APP_PICS(setting),
			app_entry_common,
		},

		{
			APP_INFO_ID_SLEEP,
			STRING_SLEEP,
			&app_window_sleep,
			APP_SIDEBAR_PIC(sleep),
			APP_WIDGET_PIC(sleep),
			APP_PICS(sleep),
			app_entry_common,
		},

		{
			APP_INFO_ID_SPORT,
			STRING_SPORT,
			&app_window_sport,
			APP_SIDEBAR_PIC(sport),
			NULL, //&pic_app_widget_sport_info,
			APP_PICS(sport_outdoor),
			app_entry_common,
		},

		{
			APP_INFO_ID_STEP,
			STRING_ACTIVITY_DAY,
			&app_window_steps,
			NULL,
			APP_WIDGET_PIC(steps),
			APP_PICS(steps),
			app_entry_common,
		},

		{
			APP_INFO_ID_STOPWATCH,
			STRING_STOPWATCH,
			&app_window_stopwatch,
			APP_SIDEBAR_PIC(stopwatch),
			APP_WIDGET_PIC(stopwatch),
			APP_PICS(stopwatch),
			app_entry_common,
		},

		{
			APP_INFO_ID_TEMPERATURE,
			STRING_TEMPERATURE,
			NULL,
			APP_SIDEBAR_PIC(stopwatch),
			NULL, //&pic_app_widget_temperature_info,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_KEY,
			STRING_KEY,
			&app_window_key_define,
			NULL,
			NULL,
			{},
			app_entry_common,
		},
		{
			APP_INFO_ID_WEATHER,
			STRING_WEATHER,
			&app_window_weather,
			APP_SIDEBAR_PIC(weather),
			APP_WIDGET_PIC(weather),
			APP_PICS(weather),
			app_entry_common,
		},

		{
			APP_INFO_ID_HOME,
			STRING_HOME,
			NULL,
			NULL,
			NULL,
			APP_PICS(home),
			app_entry_common,
		},

		{
			APP_INFO_ID_ABOUT,
			STRING_ABOUT,
			&app_window_about,
			NULL, // APP_SIDEBAR_PIC(about),
			NULL,
			APP_PICS(about),
			app_entry_common,
		},

		{
			APP_INFO_ID_BRIGHTNESS,
			STRING_BRIGHTNESS,
			&app_window_brightness,
			NULL, // APP_SIDEBAR_PIC(brightness),
			NULL,
			APP_PICS(brightness),
			app_entry_common,
		},

		{
			APP_INFO_ID_COUNTER,
			STRING_COUNTER,
			&app_window_countdown,
			NULL, // APP_SIDEBAR_PIC(counter),
			NULL,
			APP_PICS(counter),
			app_entry_common,
		},

		{
			APP_INFO_ID_DISTURB,
			STRING_DISTURB,
			&app_window_disturb,
			NULL,
			NULL,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_LANGUAGE,
			STRING_LANGUAGE,
			&app_window_language_list,
			NULL,
			NULL,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_LCDTIMEOUT,
			STRING_LCD_TIMEOUT,
			&app_window_lcd_time,
			NULL, // APP_SIDEBAR_PIC(lcdtimeout),
			NULL,
			APP_PICS(lcd_time),
			app_entry_common,
		},

		{
			APP_INFO_ID_REBOOT,
			STRING_REBOOT,
			&app_window_reboot,
			NULL, // APP_SIDEBAR_PIC(reboot),
			NULL,
			APP_PICS(reboot),
			app_entry_common,
		},

		{
			APP_INFO_ID_RESTORE,
			STRING_RESET_FACTORY,
			&app_window_reset,
			NULL, // APP_SIDEBAR_PIC(restore),
			NULL,
			APP_PICS(restore),
			app_entry_common,
		},

		{
			APP_INFO_ID_SHAKE,
			STRING_SHAKE,
			NULL,
			NULL,
			NULL,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_SHUTDOWN,
			STRING_SHUTDOWN,
			&app_window_shutdown,
			NULL, // APP_SIDEBAR_PIC(shutdown),
			NULL,
			APP_PICS(shutdown),
			app_entry_common,
		},

		{
			APP_INFO_ID_SOS,
			STRING_SOS,
			&app_window_sos,
			NULL,
			NULL,
			APP_PICS(sos),
			app_entry_common,
		},

		{
			APP_INFO_ID_VIB,
			STRING_VIB,
			&app_window_vib,
			NULL,
			NULL,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_WATCHFACE,
			STRING_WATCHFACE_SELECT,
			&app_window_main_watchface_select,
			NULL, // APP_SIDEBAR_PIC(watchface),
			NULL,
			APP_PICS(watchface),
			app_entry_common,
		},

		{
			APP_INFO_ID_WRIST,
			STRING_WRIST,
			NULL,
			NULL,
			NULL,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_ALARM,
			STRING_ALARM,
			&app_window_clock,
			NULL,			 // APP_SIDEBAR_PIC(clock),
			APP_PICS(clock), //&pic_app_widget_alarm_info,
			APP_PICS(clock),
			app_entry_common,
		},

		{
			APP_INFO_ID_BLOOD,
			STRING_BP,
			&app_window_bp,
			NULL,
			APP_WIDGET_PIC(BP),
			APP_PICS(BP),
			app_entry_common,
		},

		{
			APP_INFO_ID_CLACULATOR,
			STRING_CALC,
			&app_window_calculator,
			NULL,
			NULL,
			APP_PICS(calc),
			app_entry_common,
		},

		{
			APP_INFO_ID_MESSAGE,
			STRING_MESSAGE,
			&app_window_message_list,
			APP_SIDEBAR_PIC(msg),
			NULL, //&pic_app_widget_message_info,
			APP_PICS(message),
			app_entry_common,
		},

		{
			APP_INFO_ID_TELEPHONE,
			STRING_NULL,
			NULL, // &app_window_telephone,
			NULL,
			NULL,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_SIRI,
			STRING_VOICE_ASSITANT,
			&app_siri_window,
			NULL, // APP_SIDEBAR_PIC(siri),
			NULL,
			APP_PICS(siri),
			app_entry_common,
		},

		{
			APP_INFO_ID_CONTACTS,
			STRING_ID_PHONEBOOK,
			&app_window_call_phonebook,
			APP_SIDEBAR_PIC(contacts),
			NULL,
			APP_PICS(telephone),
			app_entry_common,
		},

		{
			APP_INFO_ID_CALL_LOG,
			STRING_ID_CALLLOG,
			&app_window_call_clog,
			NULL,
			NULL,
			APP_PICS(telephone),
			app_entry_common,
		},
		{
			APP_INFO_ID_CALENDAR,
			STRING_CALENDAR,
			&app_window_calendar,
			NULL, // APP_SIDEBAR_PIC(siri),
			NULL,
			APP_PICS(calendar),
			app_entry_common,
		},

		{
			APP_INFO_ID_PASSWORD,
			STRING_PASSWORD,
			&app_window_password_setting,
			NULL, // APP_SIDEBAR_PIC(siri),
			NULL,
			APP_PICS(password),
			app_entry_common,
		},

		{
			APP_INFO_ID_SCREEN_SET,
			STRING_SCREEN_SET,
			&app_window_setting_screen,
			NULL, // APP_SIDEBAR_PIC(brightness),
			NULL,
			APP_PICS(screen_set),
			app_entry_common,
		},

		{
			APP_INFO_ID_BED,
			STRING_BED_LAMP,
			NULL,
			NULL, // APP_SIDEBAR_PIC(brightness),
			NULL,
			{},
			app_entry_common,
		},
		{
			APP_INFO_ID_SCREEN_MENU,
			STRING_SYSTEM_MENU,
			&app_window_setting_common,
			NULL, // APP_SIDEBAR_PIC(brightness),
			NULL,
			APP_PICS(menu_set),
			app_entry_common,
		},

		{
			APP_INFO_ID_CONSTANT_LIGHTE,
			STRING_CONSTANT_LIGHTE,
			&app_window_wakey_time,
			NULL, // APP_SIDEBAR_PIC(brightness),
			NULL,
			APP_PICS(lcd_clock),
			app_entry_common,
		},

		{
			APP_INFO_ID_QR_PUSH,
			STRING_CARD_HOLDER,
			&app_window_qr_card_list,
			NULL, // APP_SIDEBAR_PIC(qr_push),
			NULL,
			APP_PICS(qr_push),
			app_entry_common,
		},

		{
			APP_INFO_ID_GAME,
			STRING_GAME,
			&app_window_games_list,
			NULL,
			NULL,
			APP_PICS(game),
			app_entry_common,
		},

		{
			APP_INFO_ID_AOD_DIAL,
			STRING_STANDBY_DIAL,
			&app_window_aod_dial,
			NULL, // APP_SIDEBAR_PIC(brightness),
			NULL,
			{},
			app_entry_common,
		},
		{
			APP_INFO_ID_WIDGET,
			NULL,
			&app_window_widget_delete,
			NULL, // APP_SIDEBAR_PIC(brightness),
			NULL,
			{},
			app_entry_common,
		},

		{
			APP_INFO_ID_LOCK,
			NULL,
			&app_window_main_locker,
			NULL,
			NULL,
			APP_PICS(lock),
			app_entry_common,
		},

		{
			APP_INFO_ID_WOMAN, // Ů����������
			STRING_WOMAN_PHY_PERIOD,
			&app_window_woman,
			NULL, // APP_SIDEBAR_PIC(woman),
			NULL,
			APP_PICS(woman),
			app_entry_common,
		},

#if TCFG_PAY_ALIOS_ENABLE
		{
			APP_INFO_ID_ALIPAY, // TCFG_PAY_ALIOS_ENABLE
			STRING_ALIPAY,
			NULL,
			NULL,
			NULL,
			APP_PICS(alipay),
			app_window_alipay_entry,
		},
#endif
};

app_info_struct *get_app_info_by_id(APP_INFO_ID id)
{
	for (unsigned char i = APP_INFO_ID_NONE; i < APP_INFO_ID_MAX; i++)
	{
		app_info_struct *app_info = (app_info_struct *)&app_info_list[i];
		if (app_info->id == id)
			return app_info;
	}
	return NULL;
}

picture_info_struct *get_app_normal_icon_by_info(app_info_struct *app_info)
{
	if (app_info)
		return (picture_info_struct *)app_info->icons[3];
	return NULL;
}

picture_info_struct *get_app_normal_icon_by_id(APP_INFO_ID id)
{
	app_info_struct *app_info = get_app_info_by_id(id);
	return get_app_normal_icon_by_info(app_info);
}

picture_info_struct *get_app_widget_icon_by_info(app_info_struct *app_info)
{
	if (app_info)
		return (picture_info_struct *)app_info->icon_widget;
	return NULL;
}

picture_info_struct *get_app_widget_icon_by_id(APP_INFO_ID id)
{
	app_info_struct *app_info = get_app_info_by_id(id);
	return get_app_widget_icon_by_info(app_info);
}


void entry_app_by_info(app_info_struct *app_info)
{
	if (app_info != NULL) 
	{
	#if GUI_SIDEBAR_SUPPORT
		if (app_info->icons[0] != NULL) {
			app_window_sidebar_update_connrec(app_info->id);
		}
	#endif

		if (app_info->entryApp != NULL) {
			app_info->entryApp(app_info);
		}
		else if (app_info->window != NULL) {
			application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, app_info->window, NULL);
		}
	}
}

void entry_app_by_id(APP_INFO_ID id)
{
	app_info_struct *app_info = get_app_info_by_id((APP_INFO_ID)id);
	if (app_info != NULL)
	{
		entry_app_by_info(app_info);
	}
}


