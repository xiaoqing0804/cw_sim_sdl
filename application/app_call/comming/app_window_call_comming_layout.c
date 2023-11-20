

#include "app_window_call_comming_layout.h"

//****************************************************call comming****************************************************//
static const gui_image_struct gui_call_reject_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_no_little_info,
};

static const gui_image_struct gui_call_accept_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_yes_little_info,
};

static const gui_image_struct gui_call_reply_comming_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_reply_info,
};

static const gui_font_struct gui_call_comming_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "",
};

static const gui_font_struct gui_call_time_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.auto_wrap = 0,
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_NUMBER_26,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "10:10",
};

static const gui_control_digital_struct  gui_call_time =
{
    .value_type = GUI_DIGITAL_VALUE_TYPE_FONT,
    .value.font = &gui_call_time_txt,
};

static const gui_font_struct gui_new_call_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.auto_wrap = 0,
	.color = COLOR_RGB(0, 253, 147),
	.size = SYS_FONT_SMALL,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "",
};

static const gui_widget_struct gui_call_comming_widget[] =
{
    {
        .id = CALL_ING_REJECT,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 91,
        .y = 308,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_reject_image,
    },
    {
        .id = CALL_ING_ACCEPT,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 272,
        .y = 308,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_accept_image,
    },

    {
        .id = CALL_ING_INFO,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 140,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_comming_text,
    },

    {
        .id = CALL_ING_TIME,
        .type = TYPE_GUI_CONTROL_TIME,
		.y = 22,
        .width = LCD_SIZE_WIDTH,
        .height = 26,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_time,
    },

    {
		.id = CALL_ING_NEW_CALL,
		.type = TYPE_GUI_CONTROL_LABEL,
        .y = 100,
		.width = LCD_SIZE_WIDTH,
		.height = 30,
		.visible= 1,
		.child_num = 1,
		.children = &gui_new_call_txt,
	},


	{
        .id = CALL_ING_REPLY,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 182,
        .y = 200,
        .width = 80,
        .height = 51,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_reply_comming_image,
    },

};


const gui_screen_struct app_call_comming_screen =
{
	.children = gui_call_comming_widget,
	.child_num = countof(gui_call_comming_widget),
};
//****************************************************call comming****************************************************//


