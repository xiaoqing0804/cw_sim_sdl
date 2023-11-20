#include "app_window_breath_hz_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_animation.h"

static const gui_font_struct gui_breath_hz_list_set_1 =
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
		.size = SYS_FONT_MEDIUM,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_BREATH_SPEED_QUICK,
};

static const gui_font_struct gui_breath_hz_list_set_2 =
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
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_BREATH_SPEED_NORMAL,
};

static const gui_font_struct gui_breath_hz_list_set_3 =
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
		.size = SYS_FONT_MEDIUM,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_BREATH_SPEED_SNOW,
};

static const gui_image_struct gui_breath_hz_ok_button =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_breath_button_info,
};

static const gui_font_struct gui_breath_hz_ok_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(0, 205, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_YES,
};

static const gui_widget_struct gui_widget_breath_hz[] =
	{
		{
			.id = BREATH_HZ_LAYOUT_ID_LIST_1,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 100,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_hz_list_set_1,
		},

		{
			.id = BREATH_HZ_LAYOUT_ID_LIST_2,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 164,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_hz_list_set_2,
		},

		{
			.id = BREATH_HZ_LAYOUT_ID_LIST_3,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 230,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_breath_hz_list_set_3,
		},

		{
			.id = BREATH_HZ_LAYOUT_ID_OK_BUTTON, // ok
			.type = TYPE_GUI_CONTROL_IMAGE,
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
};

const gui_screen_struct gui_screen_breath_hz =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_breath_hz,
		.child_num = countof(gui_widget_breath_hz),
};
