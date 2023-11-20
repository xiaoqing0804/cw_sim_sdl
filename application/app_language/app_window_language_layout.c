#include "app_window_language_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_animation.h"

static const gui_image_struct gui_pic_language_yes_BG =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.data = &pic_language_set_yes_info,
};

static const gui_font_struct gui_public_language_line = // 灰白
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.number = "English",
};

static const gui_font_struct gui_public_language_line2 = // 绿字
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(19, 154, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.number = "中文",
};

static const gui_image_struct gui_pic_language_line =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.data = &pic_language_selected_info,
};

static const gui_font_struct gui_no_language = // 息屏时间
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.auto_wrap = 0,
		.color = COLOR_RGB(19, 154, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_LANGUAGE,
};

static const gui_widget_struct gui_widget_language_list[] =
	{
		{
			.id = LANGUAGE_ID_YES_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 0,
			.y = LCD_SIZE_HEIGHT - 88,
			.width = LCD_SIZE_WIDTH,
			.height = 88,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_pic_language_yes_BG,
		},

		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.y = -20,
			.visible = 1,
			.child_num = 1,
			.children = &gui_pic_language_line,
		},

		{
			.id = LANGUAGE_ID_LINE_1,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 101,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_public_language_line,
		},
		{
			.id = LANGUAGE_ID_LINE_2,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 190,
			.width = LCD_SIZE_WIDTH,
			.height = 48,
			.visible = 1,
			.child_num = 1,
			.children = &gui_public_language_line2,
		},
		{
			.id = LANGUAGE_ID_LINE_3,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 288,
			.width = LCD_SIZE_WIDTH,
			.height = 48,
			.visible = 1,
			.child_num = 1,
			.children = &gui_public_language_line,
		},

		{
			.id = LANGUAGE_ID_TXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 20,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_no_language,
		},
};

const gui_screen_struct gui_screen_language_list =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_language_list,
		.child_num = countof(gui_widget_language_list),
};
