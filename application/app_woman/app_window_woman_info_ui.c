#include "app_window_woman_info.h"
#include "app_window_woman_info_layout.h"
#include "app_window_woman_info_ui.h"
#include "data_datetime.h"

#include "data_common.h"
#include "gui_surface.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_box_layout_item.h"

static void app_window_woman_info_ui_show_data(unsigned int start, unsigned int end, short box_id)
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
	gui_box_struct *yuejin = gui_surface_get_box(&gui_screen_woman_info, box_id);
	gui_surface_box_label_change_string(yuejin, (unsigned char *)temp);
}

void app_window_woman_info_ui_show(woman_stage_time_struct *woman_data)
{
	/// 显示月经期信息
	app_window_woman_info_ui_show_data(woman_data->yuejin_start, woman_data->yuejin_end, WOMAN_INFO_LAYOUT_ID_YUEJIN);

	/// 显示安全期信息
	app_window_woman_info_ui_show_data(woman_data->anquan_start, woman_data->anquan_end, WOMAN_INFO_LAYOUT_ID_ANQUAN);

	/// 显示排卵期信息
	app_window_woman_info_ui_show_data(woman_data->pailuan_start, woman_data->pailuan_end, WOMAN_INFO_LAYOUT_ID_PAIRUAN);
}
