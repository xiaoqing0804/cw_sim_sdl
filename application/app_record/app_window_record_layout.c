#include "app_window_record_layout.h"
#include "picture.h"
#include "language.h"

static const gui_image_struct gui_pic_record_start =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_record_start_info,
};

static const gui_image_struct gui_pic_record_stop =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_record_stop_info,
};


static const gui_image_struct gui_pic_play_start =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_play_start_info,
};

static const gui_image_struct gui_pic_play_stop =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_play_stop_info,
};

static const gui_image_struct gui_pic_record =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_record_bg_info,
};


static const gui_font_struct gui_image_record_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_26,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00:00:00",
};


static const gui_widget_struct gui_widget_record[] =
{

	{
		.id = RECORD_ID_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 94,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_record,
	},

    // rec
	{
		.id = RECORD_ID_REC_START,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 143,
		.y = 206,
		.width = 70,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_record_start,
	},
    {
        .id = RECORD_ID_REC_STOP,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = (LCD_SIZE_WIDTH-69)/2,
        .y = 206,
        .width = 70,
        .height = 70,
        .visible= 0,
        .child_num = 1,
        .children = &gui_pic_record_stop,
    },

    // play
	{
		.id = RECORD_ID_PLAY_START,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 22,
		.y = 206,
		.width = 70,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_play_start,
	},
    {
        .id = RECORD_ID_PLAY_STOP,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = (LCD_SIZE_WIDTH-69)/2,
        .y = 206,
        .width = 70,
        .height = 70,
        .visible= 0,
        .child_num = 1,
        .children = &gui_pic_play_stop,
    },

	{
		.id = RECORD_ID_TIME,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 57,
		.width = LCD_SIZE_WIDTH,
		.height = 39,
		.visible= 1,
		.child_num = 1,
		.children = &gui_image_record_time,
	},
};

const gui_screen_struct gui_screen_record =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_widget_record,
	.child_num = countof(gui_widget_record),
};


