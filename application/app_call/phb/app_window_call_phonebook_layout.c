
#include "app_window_call_phonebook_layout.h"

//****************************************************call phonebook****************************************************//

static const gui_font_struct gui_text_call =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .auto_wrap = 1,
    .width = LCD_SIZE_WIDTH,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_NO_CONTACT,
};

static const gui_image_struct gui_call_no_contact =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_no_contact_info,
};


static const gui_widget_struct gui_call_phb_widget[] =
{
    {
		.id = CALL_DIAL_PAD_NO,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 268,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_call,
	},

    {
		.id = CALL_DIAL_PAD_NO_CONTACT,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 149,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_call_no_contact,
	},
};

static const gui_layout_list_struct gui_call_phb_layout =
{
	.total = 0,
	.height = 0,

	.row_height = GUI_CALL_PHB_ITEM_H,

	.top = 110,
	.bottom = 75,
	.space = 10,

	.scroll = 1,
};

const gui_screen_struct app_call_phb_screen =
{
    .type = TYPE_GUI_LAYOUT_LIST,
    .children = gui_call_phb_widget,
    .child_num = countof(gui_call_phb_widget),
    .layout_config = &gui_call_phb_layout,
};

///////////////////////////////////////////////////////////////////////////////////////////
static const gui_image_struct gui_call_phb_item_pic =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.x = 50,
	.y = 0,
	.data = &pic_head_portrait_info,
};

 gui_font_struct gui_call_phb_item_name =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.x = 162,
	.y = 10,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "Taylor",
};

 gui_font_struct gui_call_phb_item_number =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.x = 162,
	.y = 60,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "1234567890",
};


static const gui_mix_struct gui_call_phb_item[] =
{
	{
		.data = &gui_call_phb_item_pic,
	},
	{
		.data = &gui_call_phb_item_name,
	},
    {
        .data = &gui_call_phb_item_number,
    },
};

const gui_widget_struct gui_call_phb_widget_temp = {
        .id = 20,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = GUI_CALL_PHB_ITEM_H,
        .visible= 1,
        .child_num = countof(gui_call_phb_item),
        .children = gui_call_phb_item
};

static const gui_font_struct gui_text_call_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.y = 0,
    .size = SYS_FONT_MEDIUM,
    .auto_wrap = 1,
    .width = LCD_SIZE_WIDTH,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CONTACT,
};

static const gui_mix_struct gui_call_phb_txt[] =
{
	{
		.data = &gui_text_call_txt,
	},
};

gui_widget_struct gui_call_phb_widget_txt = {
        .id = 21,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = GUI_CALL_PHB_ITEM_H,
        .visible= 1,
        .child_num = countof(gui_call_phb_txt),
        .children = gui_call_phb_txt
};
//****************************************************call phonebook****************************************************//

