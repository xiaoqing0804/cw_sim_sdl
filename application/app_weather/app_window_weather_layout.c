#include "app_window_weather_layout.h"
#include "gui_surface_control_base.h"
#include "picture.h"
#include "language.h"

static const gui_image_struct gui_weaher_bg_image[] =
	{
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
			.x = 0,
			.y = 0,
			.data = &pic_weather_bg_1_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
			.x = LCD_SIZE_HALF_WIDTH,
			.y = 0,
			.data = &pic_weather_bg_2_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
			.x = 0,
			.y = LCD_SIZE_HALF_HEIGHT,
			.data = &pic_weather_bg_3_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
			.x = LCD_SIZE_HALF_WIDTH,
			.y = LCD_SIZE_HALF_HEIGHT,
			.data = &pic_weather_bg_4_info,
		},
};

static const gui_image_struct gui_weather_icon_1 = // 大图标 后期接入天气  当天
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_sun_info,
};

static const gui_font_struct gui_weather_temperature_1 = // 今日天气
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_NUMBER_50,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "18℃~26℃",
};

static const gui_font_struct gui_weather_temperature_2 = // 今日天气
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "18℃~26℃",
};

static const gui_font_struct gui_weather_date = // 今日天气
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "03/03",
};

static const gui_number_image_list_struct gui_weather_image =
	{
		.number =
			{
				&pic_weather_num_0_info,
				&pic_weather_num_1_info,
				&pic_weather_num_2_info,
				&pic_weather_num_3_info,
				&pic_weather_num_4_info,
				&pic_weather_num_5_info,
				&pic_weather_num_6_info,
				&pic_weather_num_7_info,
				&pic_weather_num_8_info,
				&pic_weather_num_9_info,
			},
		.slash = &pic_weather_num_10_info,
		.dot = &pic_weather_num_11_info,
};

static const gui_image_number_struct gui_weather_number =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.number_image_list = &gui_weather_image,
		.value.string = "00:00",
};

static const gui_font_struct gui_no_weather_title = // 无天气
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_WEATHER_NO,
};

static const gui_image_struct gui_no_weather_icon =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.data = &pic_no_weather_info,
};

static const gui_widget_struct gui_weather_widget[] =
	{

		/****************有数据页面*******************/
		{
			.id = WEATHER_LAYOUT_ID_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 1,
			.child_num = countof(gui_weaher_bg_image),
			.children = gui_weaher_bg_image,
		},

		{
			.id = WEATHER_LAYOUT_ID_WEATHER_ICON_1,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 35,
			.y = 255,
			.width = 81,
			.height = 86,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_weather_icon_1,
		},

		{
			.id = WEATHER_LAYOUT_ID_TEMPERATURE_1,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 116,
			.y = 230,
			.width = 200,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.child_num = 1,
			.children = &gui_weather_temperature_1,
		},

		{
			.id = WEATHER_LAYOUT_ID_TEMPERATURE_2,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 232,
			.y = 332,
			.width = 84,
			.height = 18,
			.rotate = 0,
			.visible = 0,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_weather_temperature_2,
		},

		{
			.id = WEATHER_LAYOUT_ID_TEMPERATURE_3,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 232,
			.y = 389,
			.width = 84,
			.height = 18,
			.rotate = 0,
			.visible = 0,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_weather_temperature_2,
		},

		{
			.id = WEATHER_LAYOUT_ID_DATE_1,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 120,
			.y = 202,
			.width = 48,
			.height = 17,
			.rotate = 0,
			.visible = 0,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_weather_date,
		},

		{
			.id = WEATHER_LAYOUT_ID_DATE_2,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 120,
			.y = 333,
			.width = 48,
			.height = 17,
			.rotate = 0,
			.visible = 0,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_weather_date,
		},

		{
			.id = WEATHER_LAYOUT_ID_DATE_3,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 120,
			.y = 388,
			.width = 48,
			.height = 17,
			.rotate = 0,
			.visible = 0,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_weather_date,
		},

		/****************无数据页面*******************/
		{
			.id = WEATHER_LAYOUT_ID_NO_TITLE,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 250,
			.width = LCD_SIZE_HEIGHT,
			.height = 100,
			.rotate = 0,
			.visible = 0,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_no_weather_title,
		},

		{
			.id = WEATHER_LAYOUT_ID_NO_DATA,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = 150,
			.width = LCD_SIZE_WIDTH,
			.height = 86,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_no_weather_icon,
		},
};

const gui_screen_struct gui_screen_weather =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_weather_widget,
		.child_num = countof(gui_weather_widget),
};
