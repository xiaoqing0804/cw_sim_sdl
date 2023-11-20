#include "app_window_breath_time_ui.h"
#include "app_window_breath_time_layout.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "application_titlebar.h"

void app_window_breath_time_ui_update_list(short select_time)
{
	unsigned char time_1_number = select_time / 60 - 1;
	if (time_1_number == 0)
		time_1_number = 3;

	unsigned char time_3_number = select_time / 60 + 1;
	if (time_3_number > 3)
		time_3_number = 1;

	char temp[10];
	snprintf(temp, sizeof(temp), "%d ", time_1_number);
	gui_box_struct *time_1 = gui_surface_get_box(&gui_screen_breath_time, (unsigned short)BREATH_TIME_LAYOUT_ID_1MIN);
	gui_surface_box_label_change_string(time_1, (unsigned char *)temp);

	snprintf(temp, sizeof(temp), "%d ", select_time / 60);
	gui_box_struct *time_2 = gui_surface_get_box(&gui_screen_breath_time, (unsigned short)BREATH_TIME_LAYOUT_ID_2MIN);
	gui_surface_box_label_change_string(time_2, (unsigned char *)temp);

	snprintf(temp, sizeof(temp), "%d ", time_3_number);
	gui_box_struct *time_3 = gui_surface_get_box(&gui_screen_breath_time, (unsigned short)BREATH_TIME_LAYOUT_ID_3MIN);
	gui_surface_box_label_change_string(time_3, (unsigned char *)temp);
}
