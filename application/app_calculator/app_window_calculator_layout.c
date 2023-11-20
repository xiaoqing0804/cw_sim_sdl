#include "app_window_calculator_layout.h"

static const gui_image_struct gui_calculator_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_calculator_bg_info,
};

static const gui_font_struct gui_calculator_data = // 数据
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.size = SYS_FONT_NUMBER_29,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "",
};

static const gui_font_struct gui_calculator_clear =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = " ",
};

static const gui_widget_struct gui_calculator_widget[] =
	{
		{
			.id = CALCULATOR_ID_BG,
			.y = 0,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_calculator_image,
		},

		{
			// data
			.id = CALCULATOR_ID_TXET,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 50,
			.order = 1,
			.width = LCD_SIZE_WIDTH,
			.height = 45,
			.visible = 1,
			.child_num = 1,
			.children = &gui_calculator_data,
		},

		{
			// clear
			.id = CALCULATOR_ID_C,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 10,
			.width = LCD_SIZE_WIDTH,
			.height = 45,
			.visible = 1,
			.child_num = 1,
			.children = &gui_calculator_clear,
		},
};

const gui_screen_struct app_calculator_screen =
	{
		.children = gui_calculator_widget,
		.child_num = countof(gui_calculator_widget),
};
