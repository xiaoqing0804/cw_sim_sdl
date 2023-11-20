#include "app_window_calendar_layout.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "bsp_includes.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "application_config_main_window.h"

#include "gui_surface_control_base.h"
#include "gui_surface_control_date.h"
#include "gui_surface_control_time.h"

static const gui_image_struct gui_calendar_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_calendar_bg_info,
};

static const gui_font_struct gui_calendar_date =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 122, 3),
		.size = SYS_FONT_NUMBER_45,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "37",
};

static const gui_font_struct gui_calendar_month = //
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_HCENTER,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "Jan",
};

static const gui_widget_struct gui_calendar_widget[] =
	{
		// 日历图片
		{
			.y = 117,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.width = LCD_SIZE_WIDTH,
			.height = 173,
			.visible = 1,
			.child_num = 1,
			.children = &gui_calendar_image,
		},

		// 日期坐标
		{
			// date
			.id = CALENDAR_LAYOUT_ID_DAY,
			.type = TYPE_GUI_CONTROL_DATE,
			.y = 280,
			.width = LCD_SIZE_WIDTH,
			.height = 45,
			.visible = 1,
			.child_num = 1,
			.children = &gui_calendar_date,
		},
		// 月份坐标
		{
			.id = CALENDAR_LAYOUT_ID_MON,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 220,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.child_num = 1,
			.visible = 1,
			.children = &gui_calendar_month,
		},

};

const gui_screen_struct app_calendar_screen =
	{
		.children = gui_calendar_widget,
		.child_num = countof(gui_calendar_widget),
};
