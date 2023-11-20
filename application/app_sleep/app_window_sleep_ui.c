#include "app_window_sleep.h"
#include "app_window_sleep_layout.h"
#include "app_window_sleep_ui.h"

#include "picture.h"
#include "language.h"
#include "debug_info.h"

#include "app_task_main.h"
#include "arithmetic_sleep.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "application_titlebar.h"

#include "app_widget/app_window_widget_delete.h"

const unsigned short g_sleep_ui_data_box[] =
	{
		SLEEP_LAYOUT_ID_HOUR,
		SLEEP_LAYOUT_ID_MIN,

		SLEEP_LAYOUT_ID_H,
		SLEEP_LAYOUT_ID_M,

		SLEEP_LAYOUT_ID_LIGHT,
		SLEEP_LAYOUT_ID_DEEP,
		SLEEP_LAYOUT_ID_DEEP_LOGO,
		SLEEP_LAYOUT_ID_LIGHT_LOGO,
};

const unsigned short g_sleep_ui_no_box[] =
	{
		SLEEP_LAYOUT_ID_NO_DATA,
		SLEEP_LAYOUT_ID_NO_TXT,
};

static void app_window_sleep_ui_show_box(unsigned char status)
{
	gui_box_struct *box;
	for (short i = 0; i < countof(g_sleep_ui_data_box); i++)
	{
		box = gui_surface_get_box(&gui_screen_sleep, g_sleep_ui_data_box[i]);
		if (box != NULL)
			box->visible = status;
	}
}

static void app_window_sleep_ui_show_no_box(unsigned char status)
{
	gui_box_struct *box;
	for (short i = 0; i < countof(g_sleep_ui_no_box); i++)
	{
		box = gui_surface_get_box(&gui_screen_sleep, g_sleep_ui_no_box[i]);
		if (box != NULL)
			box->visible = status;
	}
}

static void app_window_sleep_ui_show_data()
{
	int value = g_sleep_time_info.light_time + g_sleep_time_info.deep_time;

	char temp[40];
	snprintf(temp, sizeof(temp), "%02d", value / 3600);
	gui_box_struct *total_hour = gui_surface_get_box(&gui_screen_sleep, (unsigned short)SLEEP_LAYOUT_ID_HOUR);
	gui_surface_box_label_change_string(total_hour, (unsigned char *)temp);
	snprintf(temp, sizeof(temp), "%02d", (value / 60) % 60);
	gui_box_struct *total_min = gui_surface_get_box(&gui_screen_sleep, (unsigned short)SLEEP_LAYOUT_ID_MIN);
	gui_surface_box_label_change_string(total_min, (unsigned char *)temp);

	value = g_sleep_time_info.light_time;
	snprintf(temp, sizeof(temp), "%02d H %02d M", value / 3600, (value / 60) % 60);
	gui_box_struct *light = gui_surface_get_box(&gui_screen_sleep, (unsigned short)SLEEP_LAYOUT_ID_LIGHT);
	gui_surface_box_label_change_string(light, (unsigned char *)temp);

	value = g_sleep_time_info.deep_time;
	snprintf(temp, sizeof(temp), "%02d H %02d M", value / 3600, (value / 60) % 60);
	gui_box_struct *deep = gui_surface_get_box(&gui_screen_sleep, (unsigned short)SLEEP_LAYOUT_ID_DEEP);
	gui_surface_box_label_change_string(deep, (unsigned char *)temp);
}

void app_window_sleep_ui_show()
{
#if 0  // test...
	//g_sleep_time_info.end_time = sys_sec_get();
	g_sleep_time_info.light_time = 8*60*60;
	g_sleep_time_info.deep_time  = 3*60*60;
#endif //

	int total = g_sleep_time_info.light_time + g_sleep_time_info.deep_time;
	if (total > 0)
	{
		app_window_sleep_ui_show_box(1);
		app_window_sleep_ui_show_no_box(0);
		app_window_sleep_ui_show_data();
	}
	else
	{
		app_window_sleep_ui_show_box(0);
		app_window_sleep_ui_show_no_box(1);
	}
}
