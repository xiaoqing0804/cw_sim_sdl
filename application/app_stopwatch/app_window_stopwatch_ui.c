#include "app_window_stopwatch_ui.h"
#include "data_stopwatch.h"

#include "bsp_includes.h"
#include "data_common.h"
#include "sys_timer_thread.h"

#include "app_window_stopwatch.h"
#include "app_window_stopwatch_layout.h"
#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "app_widget/app_window_widget_delete.h"
/// @brief 显示当前时间
/// @param void

static bool recording_flag = false;
static unsigned int record_time_index = 0;
static char current_record_time[20] ="00:00:00";

#define MAX_NUMBER_OF_RECORD 20
static unsigned int record_time[MAX_NUMBER_OF_RECORD] = {0};

bool app_window_stopwatch_set_record_time(unsigned int time_ms)
{
	if(record_time_index < MAX_NUMBER_OF_RECORD)
	{
		record_time[record_time_index] = time_ms;
		record_time_index++;
		recording_flag = true;
		memset(current_record_time,0,sizeof(current_record_time));
		if (time_ms > 60 * 60 * 1000)
		{
			snprintf(current_record_time, sizeof(current_record_time), "60:00:00");
		}
		else
		{
			snprintf(current_record_time,sizeof(current_record_time),"%d       %02d:%02d:%02d",
																	record_time_index,
																	data_stopwatch_get_escape_min(time_ms),
																	data_stopwatch_get_escape_second(time_ms),
																	data_stopwatch_get_escape_ms(time_ms));
		}
		gui_box_struct* box = gui_surface_get_box(&gui_screen_stopwatch,(unsigned short)STOPWATCH_TIME_ID_RECORD_TIME);
		gui_surface_box_label_change_string(box, (unsigned char *)current_record_time);
		return true;
	}
	return false;
}

void app_window_stopwatch_clear_record_time(void)
{
	memset(record_time,0,sizeof(recording_flag));
	record_time_index = 0;
	recording_flag = false;
}

unsigned int app_window_stopwatch_get_record_time(unsigned int index)
{
	if(index <= MAX_NUMBER_OF_RECORD)
		return record_time[index];
}

unsigned char stop_watch_get_count(void)
{
    return record_time_index;
}

static void app_window_stopwatch_ui_update_escape_time(void)
{
	char temp[40];
	gui_box_struct *box = gui_surface_get_box(&gui_screen_stopwatch, (unsigned short)STOPWATCH_TIME_ID_TEXT);
	if (data_stopwatch_status_is_stop())
	{
		snprintf(temp, sizeof(temp), "00:00:00");
	}
	else
	{
		unsigned int time_ms = data_stopwatch_get_escape_time_ms();
		if (time_ms > 60 * 60 * 1000)
		{
			snprintf(temp, sizeof(temp), "60:00:00");
		}
		else
		{
			snprintf(temp, sizeof(temp), "%02d:%02d:%02d",
					 data_stopwatch_get_escape_min(time_ms),
					 data_stopwatch_get_escape_second(time_ms),
					 data_stopwatch_get_escape_ms(time_ms));
		}
	}
	if (box != NULL)
	{
		//刷新未点击记录按钮的动态时间
		gui_surface_box_label_change_string(box, (unsigned char *)temp);
		if(recording_flag)
		{
			//刷新动态时间
			box = gui_surface_get_box(&gui_screen_stopwatch, (unsigned short)STOPWATCH_TIME_ID_RECORD_TEXT);
			if (box != NULL)
                gui_surface_box_label_change_string(box, (unsigned char *)temp);

			//刷新中间记录的时间
			box = gui_surface_get_box(&gui_screen_stopwatch,(unsigned short)STOPWATCH_TIME_ID_RECORD_TIME);
			if(box != NULL)
			{
				memset(temp,0,sizeof(temp));
				snprintf(temp, sizeof(temp), "%d       %02d:%02d:%02d",
					record_time_index,
					data_stopwatch_get_escape_min(app_window_stopwatch_get_record_time(record_time_index-1)),
					data_stopwatch_get_escape_second(app_window_stopwatch_get_record_time(record_time_index-1)),
					data_stopwatch_get_escape_ms(app_window_stopwatch_get_record_time(record_time_index-1)));
				gui_surface_box_label_change_string(box, (unsigned char *)temp);
			}

		}
	}
}
/// @brief 不同状态下开始暂停清除的图标切换
/// @param void
static void app_window_stopwatch_ui_show_status()
{
	gui_box_struct *start_icon = gui_surface_get_box(&gui_screen_stopwatch, (unsigned short)STOPWATCH_TIME_ID_START);
	gui_box_struct *clear_icon = gui_surface_get_box(&gui_screen_stopwatch, (unsigned short)STOPWATCH_TIME_ID_RESET_RECORD);
	if (data_stopwatch_status_is_start())
	{
		gui_surface_box_image_change(start_icon, (const picture_info_struct *)&pic_stopwatch_suspend_info);
		gui_surface_box_image_change(clear_icon, (const picture_info_struct *)&pic_stopwatch_record_info);
	}
	else if (data_stopwatch_status_is_pause())
	{
		gui_surface_box_image_change(start_icon, (const picture_info_struct *)&pic_stopwatch_start_info);
		gui_surface_box_image_change(clear_icon, (const picture_info_struct *)&pic_stopwatch_clear_info);
	}
	else
	{
		gui_surface_box_image_change(start_icon, (const picture_info_struct *)&pic_stopwatch_start_info);
		gui_surface_box_image_change(clear_icon, (const picture_info_struct *)&pic_stopwatch_clear_no_info);
	}
	if(recording_flag)
	{
		gui_box_struct * box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_TEXT);
		gui_surface_box_change_visible(box,0);
		box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_NAME);
		gui_surface_box_change_visible(box,0);
		box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_RECORD_TEXT);
		gui_surface_box_change_visible(box,1);
	 	box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_RECORD_RECT);
		gui_surface_box_change_visible(box,1);
		box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_RECORD_NAME);
		gui_surface_box_change_visible(box,1);
		box = gui_surface_get_box(&gui_screen_stopwatch,(unsigned short)STOPWATCH_TIME_ID_RECORD_TIME);
		gui_surface_box_change_visible(box,1);
	}
	else
	{
		gui_box_struct * box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_TEXT);
		gui_surface_box_change_visible(box,1);
		box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_NAME);
		gui_surface_box_change_visible(box,1);
		box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_RECORD_TEXT);
		gui_surface_box_change_visible(box,0);
	 	box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_RECORD_RECT);
		gui_surface_box_change_visible(box,0);
		box = gui_surface_get_box(&gui_screen_stopwatch ,(unsigned short)STOPWATCH_TIME_ID_RECORD_NAME);
		gui_surface_box_change_visible(box,0);
		box = gui_surface_get_box(&gui_screen_stopwatch,(unsigned short)STOPWATCH_TIME_ID_RECORD_TIME);
		gui_surface_box_change_visible(box,0);
	}
}



void app_window_stopwatch_ui_show()
{
	app_window_stopwatch_ui_show_status();
	app_window_stopwatch_ui_update_escape_time();
	gui_surface_commit();
}
