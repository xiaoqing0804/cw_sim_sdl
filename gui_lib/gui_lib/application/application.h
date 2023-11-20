#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef struct
{
	gui_main_window_struct	*main_window;		//配置主界面,桌面，系统返回的根界面

	const gui_window_struct *logo_window; 		//配置logo界面,开机欢迎界面，如果为空，则直接进入主界面
	const gui_window_struct *shutdown_window; 	//配置的关机界面
	const gui_window_struct *lowpower_window;
    const gui_window_struct *charger_window;
	
	const gui_window_struct *key1_window;
	const gui_window_struct *key1_double_window;
	const gui_window_struct *key1_long_window;
	
	const gui_window_struct *key2_window;
	const gui_window_struct *key2_double_window;
	const gui_window_struct *key2_long_window;

	const gui_window_struct *password_window;
	const gui_window_struct *lowpower_icon_window;

    const gui_window_struct *powersaving_window;
    const gui_window_struct *goodbye_window;
    const gui_window_struct *idle_watch_window;
    const gui_window_struct *watchface_update_window;
    const gui_window_struct *find_watch_window;
    const gui_window_struct *find_phone_window;
    const gui_window_struct *alarm_window;
    const gui_window_struct *alarm_drink_window;
    const gui_window_struct *alarm_sedentary_window;
    const gui_window_struct *alarm_target_finish_window;
    const gui_window_struct *ble_pair_window;
    const gui_window_struct *photograph_window;
    const gui_window_struct *woman_alarm_window;
    const gui_window_struct *message_info_window;

    const gui_window_struct *ota_window;
    const gui_window_struct *hr_window;
    const gui_window_struct *o2_window;
    const gui_window_struct *bp_window;
    const gui_window_struct *wear_window;
    const gui_window_struct *hrtest_window;

    const gui_window_struct *call_window;
    const gui_window_struct *call_comming_window;
    const gui_window_struct *call_outgoing_window;

    const gui_window_struct *flasherr_window;   // 20230831 Taylor.Le, +
    const gui_window_struct *pop_window;
    const gui_window_struct *lcdrgb_window;     // __CW_APP_TEST__
    const gui_window_struct *tptest_window;
    const gui_window_struct *agetest_window;
    const gui_window_struct *gsensor_window;
    const gui_window_struct *battery_window;

    const gui_window_struct *motion_game_window;
}app_window_config_struct;

extern void application_init(void);
extern void application_go_back(void);
extern void application_remove_many(char count);

extern void application_goto_main_int(int force);
extern void application_goto_main(void);
extern void application_press_key1(void);
extern void application_long_key1(void);

extern void application_lowpower(void);
extern void application_charger(void);
extern void application_password(unsigned int setFlag); // 0: verify password; 1: turn on/off password

extern void application_switch(GUI_WINDOW_SWITCH_TYPE type, const gui_window_struct* window,void* data);
extern int  application_window_event_handler(short event, void* buf);
extern int application_event_handler_run(short event, void* buf);
extern int application_event_handler_all(short event);

extern void application_lowpower_icon(void);
extern void application_flasherr_window(void);      // 20230831 Taylor.Le, +

#endif

