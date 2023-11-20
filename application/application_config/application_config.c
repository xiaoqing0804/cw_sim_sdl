#include "application_config.h"
#include "application_config_main_window.h"
#include "application_lowpower.h"

#include "app_logo/app_window_logo.h"
#include "app_lowpower/app_window_lowpower.h"
#include "app_charger/app_window_charger.h"
#include "app_shutdown/app_window_shutdown.h"

#include "app_main/app_window_main.h"
#include "app_window_password.h"

extern gui_main_window_struct g_main_window_watchface;

extern const gui_window_struct app_window_logo;
extern const gui_window_struct app_window_shutdown;
extern const gui_window_struct app_window_lowpower;
extern const gui_window_struct app_window_charger;

extern const gui_window_struct app_window_password;

extern const gui_window_struct app_window_lowpower_icon;

extern const gui_window_struct app_window_powersaving;
extern const gui_window_struct app_window_goodbye;
extern const gui_window_struct app_window_idle_watch;
extern const gui_window_struct app_window_main_watchface_update;
extern const gui_window_struct app_window_findwatch;
extern const gui_window_struct app_window_findphone;
extern const gui_window_struct app_window_alarm;
extern const gui_window_struct app_window_alarm_drink;
extern const gui_window_struct app_window_alarm_sedentary;
extern const gui_window_struct app_window_alarm_target_finish;
extern const gui_window_struct app_window_pair;

extern const gui_window_struct app_window_photograph;
extern const gui_window_struct app_window_woman_alarm;
extern const gui_window_struct app_window_message_info;

extern const gui_window_struct app_window_ota;
extern const gui_window_struct app_window_heartrate;
extern const gui_window_struct app_window_bp;
extern const gui_window_struct app_window_o2;
extern const gui_window_struct app_window_wear;
extern const gui_window_struct app_window_hrtest;

extern const gui_window_struct app_window_call;
extern const gui_window_struct app_window_call_comming;
extern const gui_window_struct app_window_call_outgoing;



extern const gui_window_struct application_window_flasherr;
extern const gui_window_struct application_window_pop;
extern const gui_window_struct app_window_lcdrgb;                       // __CW_APP_TEST__
extern const gui_window_struct app_window_tptst;
extern const gui_window_struct app_window_factory_ageing;
extern const gui_window_struct app_window_factory_ageing_test_4;
extern const gui_window_struct app_window_gsensor;
extern const gui_window_struct apptst_window_battery;

extern const gui_window_struct app_window_power_off;

#if GUI_MOTION_GAME_SUPPORT
extern const gui_window_struct app_window_motion_game;
#endif

static const app_window_config_struct g_app_window_config =
{
	.main_window = &g_main_window_watchface,		//配置主界面,桌面，系统返回的根界面

	.logo_window = &app_window_logo, 		//配置logo界面,开机欢迎界面，如果为空，则直接进入主界面
	.shutdown_window = &app_window_power_off,//&app_window_shutdown, 	//配置的关机界面
	.lowpower_window = &app_window_lowpower,
	.charger_window = &app_window_charger,

	.key1_window = NULL,
	.key1_double_window = NULL,
	.key1_long_window = &app_window_power_off,

	.key2_window = NULL,
	.key2_double_window = NULL,
    .key2_long_window = NULL,

	.password_window = &app_window_password,
    .lowpower_icon_window = &app_window_lowpower_icon,

    .powersaving_window = NULL,//&app_window_powersaving,
    .goodbye_window = &app_window_goodbye,
    .idle_watch_window = NULL,
    .watchface_update_window = &app_window_main_watchface_update,
    .find_watch_window = &app_window_findwatch,
    .find_phone_window = &app_window_findphone,
    .alarm_window = &app_window_alarm,
    .alarm_drink_window = &app_window_alarm_drink,
    .alarm_sedentary_window = &app_window_alarm_sedentary,
    .alarm_target_finish_window = &app_window_alarm_target_finish,
    .ble_pair_window = &app_window_pair,

    .photograph_window = &app_window_photograph,
    .woman_alarm_window = &app_window_woman_alarm,//&app_window_woman_alarm,
    .message_info_window = &app_window_message_info,

    .ota_window = &app_window_ota,
    .hr_window  = &app_window_heartrate,
    .bp_window  = &app_window_bp,
    .o2_window  = &app_window_o2,
    .wear_window = &app_window_wear,
    .hrtest_window = &app_window_hrtest,

    .call_window = &app_window_call,
    .call_comming_window = &app_window_call_comming,
    .call_outgoing_window = &app_window_call_outgoing,

    .flasherr_window = &application_window_flasherr,        // 20230831 Taylor.Le, +
    .pop_window = &application_window_pop,
    .lcdrgb_window = &app_window_lcdrgb,                            // __CW_APP_TEST__
    .tptest_window = &app_window_tptst,
    .agetest_window= &app_window_factory_ageing_test_4,
    .gsensor_window= &app_window_gsensor,
    .battery_window= &apptst_window_battery,

#if GUI_MOTION_GAME_SUPPORT
    .motion_game_window = &app_window_motion_game,
#endif
};

const app_window_config_struct* application_config_get_window()
{
	return &g_app_window_config;
}


