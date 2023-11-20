#include "app_window_stopwatch_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_base.h"

static const gui_image_struct gui_pic_stopwatch_stopwatch_clear =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_stopwatch_clear_no_info,
};

static const gui_image_struct gui_pic_stopwatch_stopwatch_start =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_stopwatch_start_info,
};

static const gui_image_struct gui_pic_stopwatch_stopwatch_rect =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_stopwatch_record_rect_info,
};

static const gui_font_struct gui_text_stopwatch_time =
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
    .size = SYS_FONT_NUMBER_50,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00:00:00",
};

static const gui_font_struct gui_text_stopwatch_name =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_STOPWATCH,
};

static const gui_font_struct gui_text_stopwatch_record_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = "00:00:00",
};

static const gui_font_struct gui_stopwatch_time_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.auto_wrap = 0,
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_NUMBER_38,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "10:10",
};

static const gui_control_digital_struct  gui_stopwatch_time =
{
     .value_type = GUI_DIGITAL_VALUE_TYPE_FONT,
     .value.font = &gui_stopwatch_time_txt,
};


static const gui_widget_struct gui_widget_stopwatch[] =
{

	{
		.id = STOPWATCH_TIME_ID_NAME,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 90,
		.width = LCD_SIZE_WIDTH,
		.height = 53,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_stopwatch_name,
	},

	{
        .id = STOPWATCH_TIME_ID_TIME,
        .type = TYPE_GUI_CONTROL_TIME,
		.x = 0,
		.y = 22,
        .width = LCD_SIZE_WIDTH,
        .height = 54,
        .visible= 1,
        .child_num = 1,
        .children = &gui_stopwatch_time,
    },

	{
		.id = 	STOPWATCH_TIME_ID_RESET_RECORD,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 91,
		.y = 308,
		.width = 102,
		.height = 102,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_stopwatch_stopwatch_clear,
	},

	{
		.id = 	STOPWATCH_TIME_ID_START,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 272,
		.y = 308,
		.width = 102,
		.height = 102,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_stopwatch_stopwatch_start,
	},

	{
		.id = STOPWATCH_TIME_ID_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 171,
		.width = LCD_SIZE_WIDTH,
		.height = 100,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_text_stopwatch_time,
	},

	{
		.id = STOPWATCH_TIME_ID_RECORD_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 133,
		.width = LCD_SIZE_WIDTH,
		.height = 53,
		.rotate = 0,
		.visible= 0,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_text_stopwatch_time,
	},
	{
		.id = STOPWATCH_TIME_ID_RECORD_NAME,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 72,
		.width = LCD_SIZE_WIDTH,
		.height = 53,
		.visible= 0,
		.child_num = 1,
		.children = &gui_text_stopwatch_name,
	},
	{
		.id = STOPWATCH_TIME_ID_RECORD_RECT,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 201,
		.x = 53,
		.width = 361,
		.height = 58,
		.visible = 0,
		.child_num = 1,
		.children = &gui_pic_stopwatch_stopwatch_rect,
	},
	{
		.id = STOPWATCH_TIME_ID_RECORD_TIME,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 201,
		.x = 53,
		.width = 361,
		.height = 58,
		.visible = 0,
		.child_num = 1,
		.children = &gui_text_stopwatch_record_time,
	},


};

const gui_screen_struct gui_screen_stopwatch =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_stopwatch,
	.child_num = countof(gui_widget_stopwatch),
};


