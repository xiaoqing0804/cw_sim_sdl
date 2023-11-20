#include "picture.h"
#include "language.h"

#include "gui_surface_control.h"
#include "app_window_countdown_my_time_layout.h"

static const gui_number_image_list_struct gui_text_countdown_my_hms_hilig_image =
{
	.number =
	{
		&pic_counter_number_0_info,
		&pic_counter_number_1_info,
		&pic_counter_number_2_info,
		&pic_counter_number_3_info,
		&pic_counter_number_4_info,
		&pic_counter_number_5_info,
		&pic_counter_number_6_info,
		&pic_counter_number_7_info,
		&pic_counter_number_8_info,
		&pic_counter_number_9_info,
	},
};

static const gui_image_number_struct gui_text_countdown_my_hms_hilig =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.number_image_list = &gui_text_countdown_my_hms_hilig_image,
	.value.string = "00",
};

//UP***************************
static const gui_number_image_list_struct gui_text_countdown_my_hms_up_hilig_image =
{
	.number =
	{
		&pic_counter_up_number_0_info,
		&pic_counter_up_number_1_info,
		&pic_counter_up_number_2_info,
		&pic_counter_up_number_3_info,
		&pic_counter_up_number_4_info,
		&pic_counter_up_number_5_info,
		&pic_counter_up_number_6_info,
		&pic_counter_up_number_7_info,
		&pic_counter_up_number_8_info,
		&pic_counter_up_number_9_info,
	},
};

static const gui_image_number_struct gui_text_countdown_my_hms_up_hilig =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.number_image_list = &gui_text_countdown_my_hms_up_hilig_image,
	.value.string = "00",
};


//DOW***************************
static const gui_number_image_list_struct gui_text_countdown_my_hms_dow_hilig_image =
{
	.number =
	{
		&pic_counter_dow_number_0_info,
		&pic_counter_dow_number_1_info,
		&pic_counter_dow_number_2_info,
		&pic_counter_dow_number_3_info,
		&pic_counter_dow_number_4_info,
		&pic_counter_dow_number_5_info,
		&pic_counter_dow_number_6_info,
		&pic_counter_dow_number_7_info,
		&pic_counter_dow_number_8_info,
		&pic_counter_dow_number_9_info,
	},
};

static const gui_image_number_struct gui_text_countdown_my_hms_dow_hilig =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.number_image_list = &gui_text_countdown_my_hms_dow_hilig_image,
	.value.string = "00",
};



static const gui_image_struct gui_pic_countdown_my_time_start =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_stopwatch_start_info,
};


static const gui_font_struct gui_text_countdown_mytime_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CLOCK_TIME_SET,
};

static const gui_widget_struct gui_widget_countdown_my_time[] =
{
	{
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 34,
		.width = LCD_SIZE_WIDTH,
		.height = 100,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_mytime_txt,
	},

	{
		.id = COUNTDOWN_MY_TIME_ID_HOUR_UP,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 88,
		.y = 85,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_dow_hilig,
	},
	{
		.id = COUNTDOWN_MY_TIME_ID_HOUR,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 73,
		.y = 179,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_hilig,
	},

	{
		.id = COUNTDOWN_MY_TIME_ID_HOUR_DOWN,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 88,
		.y = 273,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_up_hilig,
	},


	{
		.id = COUNTDOWN_MY_TIME_ID_MIN_UP,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 202,
		.y = 85,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_dow_hilig,
	},
	{
		.id = COUNTDOWN_MY_TIME_ID_MIN,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 187,
		.y = 179,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_hilig,
	},
	{
		.id = COUNTDOWN_MY_TIME_ID_MIN_DOWN,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 202,
		.y = 273,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_up_hilig,
	},

	{
		.id = COUNTDOWN_MY_TIME_ID_SECOND_UP,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 311,
		.y = 85,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_dow_hilig,
	},
	{
		.id = COUNTDOWN_MY_TIME_ID_SECOND,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 296,
		.y = 179,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_hilig,
	},
	{
		.id = COUNTDOWN_MY_TIME_ID_SECOND_DOWN,
		.type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
		.x = 311,
		.y = 273,
		.width = LCD_SIZE_WIDTH/3,
		.height = COUNTDOWN_ITEM_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_countdown_my_hms_up_hilig,
	},

	{
		.id = COUNTDOWN_MY_TIME_ID_STATR,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 340,
		.width = LCD_SIZE_WIDTH,
		.height = COUNTDOWN_OPBAR_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_countdown_my_time_start,
	},
};


const gui_screen_struct gui_screen_countdown_my_time =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_widget_countdown_my_time,
	.child_num = countof(gui_widget_countdown_my_time),
};


