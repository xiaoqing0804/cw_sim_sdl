#include "app_window_steps.h"
#include "app_window_steps_layout.h"
#include "app_window_steps_ui.h"

#include "picture.h"
#include "language.h"
#include "debug_info.h"
#include "app_task_main.h"

#include "arithmetic_common.h"
#include "bsp_hr\hr.h"
#include "gui_window.h"


#include "application_titlebar.h"

#include "gui_surface_box_image_progress.h"
#include "gui_surface_box_image_number.h"
#include "gui_surface_box_label.h"

#include "app_widget/app_window_widget_delete.h"

/*-----------------------------ϵͳ�¼�--------------------------------------*/
void app_window_step_ui_show()
{
	gui_box_struct* box;

	char temp[20];
	int value;

    value = get_sport_info()->walkSteps % 100000;
	snprintf(temp, sizeof(temp), "%05d", value);
	gui_box_struct*  step_value = gui_surface_get_box(&gui_screen_steps, (unsigned short) STEPS_STEPS_NUM_ID);
	gui_surface_box_label_change_string(step_value,(unsigned char*)temp);


	value = get_sport_info()->calories % 10000000;
	snprintf(temp, sizeof(temp), "%04d", value/1000);
	gui_box_struct*  cak_value = gui_surface_get_box(&gui_screen_steps, (unsigned short) STEPS_KCAL_NUM_ID);
	gui_surface_box_label_change_string(cak_value,(unsigned char*)temp);

	value = get_sport_info()->distance % 1000000;
	if (g_unit_setting.select.bit.distance) {
		// 1KM = 0.6213712 Mile
		value = (value * 621)/1000;
	}
    snprintf(temp, sizeof(temp), "%d.%d%d", value/1000, (value%1000)/100,(value/10)%10);
    gui_box_struct*  km_value = gui_surface_get_box(&gui_screen_steps, (unsigned short) STEPS_KM_NUM_ID);
    gui_surface_box_label_change_string(km_value,(unsigned char*)temp);

	value = last_hr_result.hr;
    snprintf(temp, sizeof(temp), "%03d", value);
    gui_box_struct*  hr_value = gui_surface_get_box(&gui_screen_steps, (unsigned short) STEPS_HR_NUM_ID);
    gui_surface_box_label_change_string(hr_value,(unsigned char*)temp);

}

void app_window_step_ui_update_unit(void)
{
	gui_box_struct* box;

	box = gui_surface_get_box(&gui_screen_steps, STEPS_KM_TXT_ID);
	if (box != NULL) {
		if (g_unit_setting.select.bit.distance) {
			// mile
			gui_surface_box_label_change_string(box, "Mile");
		}
		else {
			// km
			gui_surface_box_label_change_string(box, "KM");
		}
	}
}


