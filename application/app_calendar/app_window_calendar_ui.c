#include "app_window_calendar_ui.h"
#include "app_window_calendar_layout.h"

static const char *g_caledar_ui_month_string[] =
	{
		"Jan",
		"Feb",
		"Mar",
		"Apr",
		"May",
		"Jun",
		"Jul",
		"Aug",
		"Sep",
		"Oct",
		"Nov",
		"Dec",
};

static void app_window_caledar_ui_show_month()
{
	time_struct time;
	sys_time_get(&time);

	gui_box_struct *box = gui_surface_get_box(&app_calendar_screen, (unsigned short)CALENDAR_LAYOUT_ID_MON);
	if (box != NULL)
	{
		gui_surface_box_label_change_string(box, (unsigned char *)g_caledar_ui_month_string[time.mon - 1]);
	}
}

static void app_window_caledar_ui_show_day()
{
	time_struct time;
	sys_time_get(&time);

	char temp[20];
	sprintf(temp, "%02d", time.day);
	gui_box_struct *box = gui_surface_get_box(&app_calendar_screen, CALENDAR_LAYOUT_ID_DAY);
	if (box != NULL)
	{
		gui_surface_box_label_change_string(box, temp);
	}
}

void app_window_caledar_ui_show()
{
	app_window_caledar_ui_show_month();
	app_window_caledar_ui_show_day();
}
