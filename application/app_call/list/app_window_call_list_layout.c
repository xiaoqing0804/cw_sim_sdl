
#include "app_window_call_list_layout.h"

//****************************************************call list****************************************************//
#define call_text_x 140

static const gui_image_struct gui_pic_list_book =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 35,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_call_list_book_info,
};

static const gui_font_struct gui_text_list_book =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = call_text_x,
    .y = 0+25,
    .anchor_x = 0,
    .anchor_y = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CONTACT,
};

static const gui_mix_struct gui_item_call_list_book[] =
{
	{
		.data = &gui_pic_list_book,
	},
	{
		.data = &gui_text_list_book,
	},
};


static const gui_image_struct gui_pic_list_clog =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 35,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_call_list_callong_info,
};

static const gui_font_struct gui_text_list_clog =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = call_text_x,
    .y = 0+25,
    .anchor_x = 0,
    .anchor_y = 0,
    .scroll = 1,
    .width = LCD_SIZE_WIDTH-150,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ID_CALLLOG,
};

static const gui_mix_struct gui_item_call_list_clog[] =
{
	{
		.data = &gui_pic_list_clog,
	},
	{
		.data = &gui_text_list_clog,
	},
};


static const gui_image_struct gui_pic_list_dail =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 35,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_call_list_dail_info,
};

static const gui_font_struct gui_text_list_dail =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = call_text_x,
    .y = 0+25,
    .anchor_x = 0,
    .anchor_y = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CALL_DIAL,
};

static const gui_mix_struct gui_item_call_list_dail[] =
{
	{
		.data = &gui_pic_list_dail,
	},
	{
		.data = &gui_text_list_dail,
	},
};


static const gui_widget_struct gui_call_list_widget[] =
{


	{
		.id = CALL_BOOK_IND_ID,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 30,
		.y = 75+10,
		.width = LCD_SIZE_WIDTH,
		.height = 92,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_call_list_book),
		.children = gui_item_call_list_book,
	},


	{
		.id = CALL_CLOG_IND_ID,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 30,
		.y = 166+30,
		.width = LCD_SIZE_WIDTH,
		.height = 92,
		.rotate = 0,
		.visible= 1,
		.clip = 1,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_call_list_clog),
		.children = gui_item_call_list_clog,
	},


	{
		.id = CALL_DAIL_IND_ID,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 30,
		.y = 265+45,
		.width = LCD_SIZE_WIDTH,
		.height = 92,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_call_list_dail),
		.children = (gui_item_call_list_dail),
	},


};

const gui_screen_struct app_call_list_screen =
{
	.children = gui_call_list_widget,
	.child_num = countof(gui_call_list_widget),
};
//****************************************************call list****************************************************//
