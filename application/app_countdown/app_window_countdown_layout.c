#include "app_window_countdown_layout.h"
#include "picture.h"
#include "language.h"





static const gui_image_struct gui_pic_countdown_lap_1 =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_counter_min_1_info,
};

static const gui_image_struct gui_pic_countdown_lap_3 =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_counter_min_3_info,
};

static const gui_image_struct gui_pic_countdown_lap_5 =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_counter_min_5_info,
};

static const gui_image_struct gui_pic_countdown_lap_10 =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_counter_min_10_info,
};

static const gui_image_struct gui_pic_countdown_lap_custom =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_counter_custom_info,
};

static const gui_font_struct gui_text_countdown_my_min =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_COUNTER,
};

static const gui_font_struct gui_text_countdown_custom =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CUSTOM,
};


static const gui_widget_struct gui_widget_countdown[] =
{

    {
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 40,
		.width = LCD_SIZE_WIDTH,
		.height = 30,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_min,
	},



	{
		.id = COUNTDOWN_ID_1MIN,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 50,
		.y = 100,
		.width = 160,
		.height = 160,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_countdown_lap_1,
	},

	{
		.id = COUNTDOWN_ID_3MIN,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 256,
		.y = 100,
		.width = 160,
		.height = 160,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_countdown_lap_3,
	},

	{
		.id = COUNTDOWN_ID_5MIN,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 50,
		.y = 306,
		.width = 160,
		.height = 160,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_countdown_lap_5,
	},

	{
		.id = COUNTDOWN_ID_10MIN,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 256,
		.y = 306,
		.width = 160,
		.height = 160,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_countdown_lap_10,
	},

    {
		.id = COUNTDOWN_ID_CUSTOM,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 516,
		.width = LCD_SIZE_WIDTH,
		.height = 80,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_countdown_lap_custom,
	},


    {
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 540,
		.width = LCD_SIZE_WIDTH,
		.height = 30,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_custom,
	},

};


const gui_layout_scroll_struct gui_grid_list_countdown =
{

	.height = 700,		//高度
	.scroll = 1,//是否可以上下滚动
};


const gui_screen_struct gui_screen_countdown =
{
	.type = TYPE_GUI_LAYOUT_SCROLL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_countdown,
	.child_num = countof(gui_widget_countdown),

	.layout_config = &gui_grid_list_countdown,
};


