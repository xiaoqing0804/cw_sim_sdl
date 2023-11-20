
#include "app_window_call_clog_layout.h"

//****************************************************call clog****************************************************//


static const gui_font_struct gui_text_call_no =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .auto_wrap = 1,
    .width = LCD_SIZE_WIDTH,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_NO_CALL_LOG,
};

static const gui_image_struct gui_call_no_call_record =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_no_call_record_info,
};


static const gui_widget_struct gui_call_clog_widget[] =
{
    {
		.id = CALL_DIAL_PAD_NO,
		.type = TYPE_GUI_CONTROL_LABEL,
        .y = 268,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_call_no,
	},

    {
		.id = CALL_DIAL_PAD_NO_CALL_RECORD,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 169,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_call_no_call_record,
	},
};

static const gui_layout_list_struct gui_call_clog_layout =
{
	.total = 0,
	.height = 0,

	.row_height = GUI_CALL_CLOG_ITEM_H,

	.top = 110,
	.bottom = 10,
	.space = 15,

	.scroll = 1,
};

const gui_screen_struct app_call_clog_screen =
{
    .type = TYPE_GUI_LAYOUT_LIST,
    .children = gui_call_clog_widget,
    .child_num = countof(gui_call_clog_widget),
    .layout_config = &gui_call_clog_layout,
};



