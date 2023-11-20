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
extern unsigned char wakey_flag;

static const char* week_string[7] =
{
	"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"
};



static void app_window_ble_status_ui(void *buf)
{
	if(get_ble_connect_flag() > 0){
		gui_box_struct*  ble_img = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_BLE);
		gui_surface_box_image_change(ble_img,(const picture_info_struct*)&pic_quick_ble_yes_info);
	}

	if((ext_btaud_status_get()->dev_status > 0))
	{
		gui_box_struct*  ble_img = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_BLE);
		gui_surface_box_image_change(ble_img,(const picture_info_struct*)&pic_quick_hfp_yes_1_info);
	}

	if((ext_btaud_status_get()->dev_status == 0) && get_ble_connect_flag() == 0)
	{
		gui_box_struct*  ble_img = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_BLE);
		gui_surface_box_image_change(ble_img,(const picture_info_struct*)&pic_quick_all_no_info);

	}

	if((ext_btaud_status_get()->dev_status > 0) && get_ble_connect_flag() > 0)
	{
		gui_box_struct*  ble_img = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_BLE);
		gui_surface_box_image_change(ble_img,(const picture_info_struct*)&pic_quick_all_yes_info);
	}
	gui_surface_commit();
}

static void app_window_quick_ui(void *buf)
{
	char temp[20];
	int value;
	time_struct time;
	unsigned int ampm,sec;

	app_window_ble_status_ui(buf);
	sys_time_get(&time);

	snprintf(temp, sizeof(temp), "%d%%", get_battery_capacity());
	gui_box_struct*  batt_flg = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_BATTERY_TEXT);
	gui_surface_box_label_change_string(batt_flg,(unsigned char *)temp);


	gui_box_struct* week_data = gui_surface_get_box(&gui_screen_quick,(unsigned short)QUICK_ID_WEEK);
	gui_surface_box_label_change_string(week_data,(unsigned char *)week_string[time.wed]);


    if(g_forget_disturb.switch_flag == 0){
	gui_box_struct*  img = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_SYS_DISTURB);
	gui_surface_box_image_change(img,(const picture_info_struct*)&pic_quick_disturb_off_info);
	}else{
	gui_box_struct*  img = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_SYS_DISTURB);
	gui_surface_box_image_change(img,(const picture_info_struct*)&pic_quick_disturb_on_info);
	}

	if(forget_aod.switch_flag == 0){
		gui_box_struct*  img = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_SYS_BRIGHT);
		gui_surface_box_image_change(img,(const picture_info_struct*)&pic_quick_bright_off_info);

		gui_box_struct*  text = gui_surface_get_box(&gui_screen_quick,(unsigned short) QUICK_ID_SYS_BRIGHT_TEXT);
		if (text != NULL) text->visible = 1;

		gui_box_struct*  text1 = gui_surface_get_box(&gui_screen_quick,(unsigned short) QUICK_ID_SYS_BRIGHT_ON_TEXT);
		if (text1 != NULL) text1->visible = 0;

	}else{
		gui_box_struct*  img = gui_surface_get_box(&gui_screen_quick, (unsigned short) QUICK_ID_SYS_BRIGHT);
		gui_surface_box_image_change(img,(const picture_info_struct*)&pic_quick_bright_on_info);

		gui_box_struct*  text = gui_surface_get_box(&gui_screen_quick,(unsigned short) QUICK_ID_SYS_BRIGHT_TEXT);
		if (text != NULL) text->visible = 0;

		gui_box_struct*  text1 = gui_surface_get_box(&gui_screen_quick,(unsigned short) QUICK_ID_SYS_BRIGHT_ON_TEXT);
		if (text1 != NULL)
		{
			text1->visible = 1;
			snprintf(temp, sizeof(temp), "%d Min",application_get_aod_timeout());
			gui_surface_box_label_change_string(text1,(unsigned char *)temp);
		}
	}

    gui_box_struct* call_onoff = gui_surface_get_box(&gui_screen_quick, QUICK_ID_SYS_HFP);

	if(ext_btaud_onoff_get() > 0)

	{
		gui_surface_box_image_change(call_onoff,(const picture_info_struct*)&pic_quick_hfp_yes_info);
	}
	else
	{
		gui_surface_box_image_change(call_onoff,(const picture_info_struct*)&pic_quick_hfp_no_info);
	}

	gui_surface_commit();
}

void app_window_quick_ui_show()
{
	app_window_quick_ui(NULL);
}
