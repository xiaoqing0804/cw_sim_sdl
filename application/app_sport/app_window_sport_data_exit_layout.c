#include "app_window_sport_data_exit_layout.h"
#include "picture.h"
#include "language.h"

static const gui_image_struct gui_pic_sport_exit_yes =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_yes_little_info,
};



static const gui_image_struct gui_pic_sport_exit_no =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_no_little_info,
};


static const gui_font_struct gui_text_sport_exit =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_CONTINUE,
};

static const gui_widget_struct gui_widget_sport_exit[] =
{

	{
		.id = SPORT_EXIT_ID_YES,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 30,
		.y = 180,
		.width = 75,
		.height = 75,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_sport_exit_yes,
	},

	{
		.id = SPORT_EXIT_ID_NO,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 140,
		.y = 180,
		.width = 75,
		.height = 75,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_sport_exit_no,
	},

	{
		.id = SPORT_EXIT_ID_TETX,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 30,
		.width = 240,
		.height = 144,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_text_sport_exit,
	},
};

const gui_screen_struct gui_screen_sport_exit =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_sport_exit,
	.child_num = countof(gui_widget_sport_exit),
};

