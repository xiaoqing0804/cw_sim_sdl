
#include "app_window_pair_layout.h"

//****************************************************pair****************************************************//
static const gui_image_struct gui_pair_img =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_pair_finish_info,
};

static const gui_font_struct gui_text_pair =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.auto_wrap = 0,
		.color = COLOR_RGB(83, 212, 101),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_APP_PAIR_FINISH,
};

static const gui_widget_struct gui_widget_pair[] =
	{
		{
			.id = 1,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = 145,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_pair_img,
		},

		{
			.id = 2,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 351,
			.width = LCD_SIZE_WIDTH,
			.height = 51,
			.rotate = 0,
			.visible = 1,
			.order = 1,
			.child_num = 1,
			.children = &gui_text_pair,
		},

};

const gui_screen_struct gui_screen_pair =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_pair,
		.child_num = countof(gui_widget_pair),
};
