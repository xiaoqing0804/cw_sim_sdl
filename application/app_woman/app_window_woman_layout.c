#include "app_window_woman_layout.h"
#include "picture.h"
#include "language.h"

static const gui_image_struct gui_woman_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_woman_bg_info,
};

static const gui_image_struct gui_woman_bottom =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.id = 0,
		.x = 0,
		.y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_music_dis_info,
};

static const gui_font_struct gui_woman_curr_status =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_WOMAN_PHY_PERIOD,
};

static const gui_widget_struct gui_widget_woman[] =
	{
		{
			.id = WOMAN_LAYOUT_ID_PIC_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = 80,
			.width = LCD_SIZE_WIDTH,
			.height = 249,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_woman_bg,
		},

		{
			.id = WOMAN_LAYOUT_ID_PIC_BOTTOM,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = 225 + 60,
			.width = LCD_SIZE_WIDTH,
			.height = 70,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_woman_bottom,
		},

		{
			.id = WOMAN_LAYOUT_ID_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 250 + 70,
			.width = LCD_SIZE_WIDTH,
			.height = 72,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_woman_curr_status,
		},
};

const gui_screen_struct gui_screen_woman =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_woman,
		.child_num = countof(gui_widget_woman),
};
