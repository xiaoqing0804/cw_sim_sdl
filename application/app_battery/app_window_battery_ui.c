#include "app_window_battery_ui.h"
#include "app_window_battery_layout.h"
#include "app_window_battery_chart.h"

static void app_window_battery_ui_show_data()
{
	time_struct time;
	unsigned int start_sec = sys_time_get(&time);

	battery_day_info_struct *data = get_battery_day_info();
	unsigned int end_sec = rtc_time_to_sec(data->endtime);

	unsigned int difference = 0;
	if (end_sec != NULL)
	{
		difference = start_sec - end_sec;
	}

	char temp[100];
	snprintf(temp, sizeof(temp), "%d %s", (difference / 60 / 60), GUI_Get_ID_String(STRING_WEATHER_UPDATA_TIME));

	gui_box_struct *box = gui_surface_get_box(&gui_screen_battery, (unsigned short)BATTERY_LAYOUT_ID_TIME);
	gui_surface_box_label_change_string(box, (unsigned char *)temp);
}

static void app_window_battery_ui_show_date()
{
	battery_day_info_struct *data = get_battery_day_info();

	char temp[100];
	char batt[20];
	strcpy(temp, GUI_Get_ID_String(STRING_LAST_CHARGED));
	snprintf(batt, sizeof(batt), " %d%%", data->last_battery);
	strcat(temp, batt);

	gui_box_struct *box = gui_surface_get_box(&gui_screen_battery, (unsigned short)BATTERY_LAYOUT_ID_LAST_NUM);
	gui_surface_box_label_change_string(box, (unsigned char *)temp);
}

void app_window_battery_ui_show()
{
	application_titlebar_create(&gui_screen_battery, STRING_BATTERY);
	app_window_battery_ui_show_data();
	app_window_battery_ui_show_date();
}
