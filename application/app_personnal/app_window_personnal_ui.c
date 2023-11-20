#include "app_window_personnal_ui.h"
#include "app_window_personnal_layout.h"

#include "application_titlebar.h"
#include "gui_surface_box_layout_item.h"
#include "gui_surface_box_image.h"
#include "data_user_info.h"

static void app_window_personnal_ui_show_hight()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_personnal, PERSONNAL_LAYOUT_ID_HEIGHT);
	if (box != NULL)
	{
		unsigned int value = data_user_info_get_hight();
		if (g_unit_setting.select.bit.distance) {
			// 1cm = 0.394 in;  1ft = 12 in
			value = (value * 394)/1000;		// in
		}
		gui_surface_box_layout_item_change_number(box, PERSONNAL_LAYOUT_ID_HEIGHT_TEXT, value);
	}
}

static void app_window_personnal_ui_show_weight()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_personnal, PERSONNAL_LAYOUT_ID_WEIGHT);
	if (box != NULL)
	{
		unsigned int value = data_user_info_get_weight();
		switch(g_unit_setting.select.bit.weight) {	// //0: kg , 1 :lb ,2 :st
			case 1:	// 1kg = 2.205lb
				value = value * 2205/1000;
				break;
			case 2:	// 1 Ç§¿Ë=0.157473 Ó¢Ê¯
				value = value * 157/1000;
				break;
			case 0:	
			default:
				break;
		}
		gui_surface_box_layout_item_change_number(box, PERSONNAL_LAYOUT_ID_WEIGHT_TEXT, value);
	}
}

static void app_window_personnal_ui_show_bmi()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_personnal, PERSONNAL_LAYOUT_ID_BMI);
	if (box != NULL)
	{
		unsigned char buff[8] = {0};
		float bmi = data_user_info_get_bmi();
		snprintf((unsigned char *)buff, sizeof(buff), "%.1f", (bmi < 10000) ? bmi : 0.0f);
		gui_surface_box_layout_item_change_string(box, PERSONNAL_LAYOUT_ID_BMI_TEXT, buff);
	}
}

static void app_window_personnal_ui_show_head()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_personnal, PERSONNAL_LAYOUT_ID_HEAD);
	if (box != NULL)
	{
		if (get_ble_connect_flag() > 0)
			gui_surface_box_image_change(box, &pic_setting_app_icon_personal_login_info);
		else
			gui_surface_box_image_change(box, &pic_setting_app_icon_personal_info);
	}
}

void app_window_personnal_ui_show()
{
	app_window_personnal_ui_show_head();
	app_window_personnal_ui_show_hight();
	app_window_personnal_ui_show_weight();
	app_window_personnal_ui_show_bmi();
}
