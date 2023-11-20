#include "app_window_breath_time_layout.h"

#include "picture.h"
#include "language.h"
#include "gui_surface_control_animation.h"

static const gui_font_struct gui_breath_time_min_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.max_width = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(0, 205, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_BREATH_MIN,
};

static const gui_font_struct gui_breath_hz_ok_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(0, 205, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_YES,
};

static const gui_image_struct gui_breath_hz_ok_button =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_breath_button_info,
};


static const gui_font_struct gui_breath_time_set_1 =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.max_width = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_NUMBER_38,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "2",
};

static const gui_font_struct gui_breath_time_set_2 =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.max_width = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(0, 205, 255),
		.size = SYS_FONT_NUMBER_50,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "3",
};

static const gui_font_struct gui_breath_time_set_3 =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.max_width = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_NUMBER_38,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "4",
};

static const gui_widget_struct gui_widget_breath_time[] =
	{
		{
			.id = BREATH_TIME_LAYOUT_ID_MIN_TITLE,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 255,
			.y = 175,
			.width = 40,
			.height = 20,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_time_min_text,
		},

		{
			.id = BREATH_TIME_LAYOUT_ID_OK, // ok
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 0,
			.y = 324,
			.width = LCD_SIZE_WIDTH,
			.height = 102,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_hz_ok_button,
		},

		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 197,
			.y = 353,
			.width = 72,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_hz_ok_title,
		},

		{
			.id = BREATH_TIME_LAYOUT_ID_1MIN,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 88,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_time_set_1,
		},

		{
			.id = BREATH_TIME_LAYOUT_ID_2MIN,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 162,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_time_set_2,
		},

		{
			.id = BREATH_TIME_LAYOUT_ID_3MIN,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 232,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_time_set_3,
		},
};

const gui_screen_struct gui_screen_breath_time =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_breath_time,
		.child_num = countof(gui_widget_breath_time),
};
