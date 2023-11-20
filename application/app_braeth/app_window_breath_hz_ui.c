#include "app_window_breath_hz_ui.h"
#include "app_window_breath_hz_layout.h"
#include "app_window_breath.h"
#include "app_window_breath_time.h"
#include "app_window_breath_start.h"
#include "data_breathe.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "application_titlebar.h"

static const STRING_ID_TYPE g_app_window_breath_hz_ui_str_id[] = {
	STRING_BREATH_SPEED_QUICK,
	STRING_BREATH_SPEED_NORMAL,
	STRING_BREATH_SPEED_SNOW,
};

void app_window_breath_hz_ui_update_list(short select_hz)
{
	unsigned char speed1 = select_hz - 1;
	unsigned char speed2 = select_hz;
	unsigned char speed3 = select_hz + 1;
	if (speed1 > 2)
		speed1 = 2;
	if (speed3 > 2)
		speed3 = 0;

	char temp[40];
	snprintf(temp, sizeof(temp), "%s", GUI_Get_ID_String(g_app_window_breath_hz_ui_str_id[speed1]));
	gui_box_struct *fast = gui_surface_get_box(&gui_screen_breath_hz, (unsigned short)BREATH_HZ_LAYOUT_ID_LIST_1);
	gui_surface_box_label_change_string(fast, (unsigned char *)temp);

	snprintf(temp, sizeof(temp), "%s", GUI_Get_ID_String(g_app_window_breath_hz_ui_str_id[speed2]));
	gui_box_struct *medium = gui_surface_get_box(&gui_screen_breath_hz, (unsigned short)BREATH_HZ_LAYOUT_ID_LIST_2);
	gui_surface_box_label_change_string(medium, (unsigned char *)temp);

	snprintf(temp, sizeof(temp), "%s", GUI_Get_ID_String(g_app_window_breath_hz_ui_str_id[speed3]));
	gui_box_struct *slow = gui_surface_get_box(&gui_screen_breath_hz, (unsigned short)BREATH_HZ_LAYOUT_ID_LIST_3);
	gui_surface_box_label_change_string(slow, (unsigned char *)temp);
}
