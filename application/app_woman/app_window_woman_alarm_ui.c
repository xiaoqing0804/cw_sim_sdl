#include "app_window_woman_alarm_ui.h"
#include "app_window_woman_alarm_layout.h"
#include "data_datetime.h"

#include "data_common.h"
#include "gui_surface.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_box_layout_item.h"
#include "bsp_motor/motor.h"

static void app_window_woman_alarm_ui_show_icon(const picture_info_struct *icon, unsigned short box_id)
{
	gui_box_struct *woman = gui_surface_get_box(&gui_screen_woman_alarm, box_id);
	gui_surface_box_image_change(woman, icon);
}

static void app_window_woman_alarm_ui_show_text(unsigned short text_id, unsigned short box_id)
{
	const char *str = GUI_Get_ID_String(text_id);
	gui_box_struct *woman_text = gui_surface_get_box(&gui_screen_woman_alarm, box_id);
	gui_surface_box_label_change_string(woman_text, (unsigned char *)str);
}

static void app_window_woman_alarm_ui_show_date(unsigned int start, unsigned int end, unsigned short box_id)
{
	time_struct time1, time2;
	sec_to_time(start, &time1);
	sec_to_time(end, &time2);

	char temp[30];
	snprintf(temp, sizeof(temp), "[ %02d/%02d ~ %02d/%02d ]",
			 data_datetime_get_date_front_value(&time1),
			 data_datetime_get_date_back_value(&time1),
			 data_datetime_get_date_front_value(&time2),
			 data_datetime_get_date_back_value(&time2));
	gui_box_struct *woman_time = gui_surface_get_box(&gui_screen_woman_alarm, box_id);
	gui_surface_box_label_change_string(woman_time, (unsigned char *)temp);
}

void app_window_woman_alarm_ui_show_yuejin(woman_stage_time_struct *woman_data)
{
	app_window_woman_alarm_ui_show_icon(&pic_woman_yuejin_info, (unsigned short)WOMAN_ALARM_LAYOUT_ID_PIC);
	app_window_woman_alarm_ui_show_text(STRING_WOMAN_YUEJIN, (unsigned short)WOMAN_ALARM_LAYOUT_ID_TEXT);
	app_window_woman_alarm_ui_show_date(woman_data->yuejin_start, woman_data->yuejin_end, (unsigned short)WOMAN_ALARM_LAYOUT_ID_TIME);
}

void app_window_woman_alarm_ui_show_pailuan_start(woman_stage_time_struct *woman_data)
{
	app_window_woman_alarm_ui_show_icon(&pic_woman_pailuan_info, (unsigned short)WOMAN_ALARM_LAYOUT_ID_PIC);
	app_window_woman_alarm_ui_show_text(STRING_WOMAN_PAILUAN, (unsigned short)WOMAN_ALARM_LAYOUT_ID_TEXT);
	app_window_woman_alarm_ui_show_date(woman_data->pailuan_start, woman_data->pailuan_end, (unsigned short)WOMAN_ALARM_LAYOUT_ID_TIME);
}

void app_window_woman_alarm_ui_show_pailuan(woman_stage_time_struct *woman_data)
{
	app_window_woman_alarm_ui_show_icon(&pic_woman_pailuan_info, (unsigned short)WOMAN_ALARM_LAYOUT_ID_PIC);
	app_window_woman_alarm_ui_show_text(STRING_WOMAN_PAILUAN_DAY, (unsigned short)WOMAN_ALARM_LAYOUT_ID_TEXT);
	app_window_woman_alarm_ui_show_date(woman_data->pailuan_day, woman_data->pailuan_day, (unsigned short)WOMAN_ALARM_LAYOUT_ID_TIME);
}

void app_window_woman_alarm_ui_show_pailuan_end(woman_stage_time_struct *woman_data)
{
	app_window_woman_alarm_ui_show_icon(&pic_woman_pailuan_info, (unsigned short)WOMAN_ALARM_LAYOUT_ID_PIC);
	app_window_woman_alarm_ui_show_text(STRING_WOMAN_PAILUAN_END, (unsigned short)WOMAN_ALARM_LAYOUT_ID_TEXT);
	app_window_woman_alarm_ui_show_date(woman_data->pailuan_end, woman_data->pailuan_end, (unsigned short)WOMAN_ALARM_LAYOUT_ID_TIME);
}
