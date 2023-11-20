
#include "app_window_call_outgoing_layout.h"

//****************************************************call outgoing****************************************************//
static const gui_image_struct gui_call_hungup_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_no_little_info,
};

static const gui_image_struct gui_call_mic_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_mic_on_info,
};

static const gui_image_struct gui_call_phone_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_out_watch_info,
};



static const gui_image_struct gui_call_vol_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_info,
};

static const gui_font_struct gui_call_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "1234567890",
};

static const gui_font_struct gui_call_num =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "00:00:00",
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


static const gui_font_struct gui_new_call_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.auto_wrap = 0,
	.color = COLOR_RGB(0, 253, 147),
	.size = SYS_FONT_SMALL,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "New call...",
};

static const gui_control_digital_struct  gui_call_time =
{
 .value_type = GUI_DIGITAL_VALUE_TYPE_FONT,
 .value.font = &gui_call_time_txt,
};

// vol
static const gui_image_struct gui_call_volup_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_up_info,
};

static const gui_image_struct gui_call_voldn_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_down_info,
};


// vol-bg
static const gui_image_struct gui_call_vol_bg_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_line_info,
};

static const gui_image_struct gui_call_vol_ind_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_line1_info,
};

static const gui_widget_struct gui_call_outgoing_widget[] =
{



     {
        .id = CALL_OUTGOING_MIC_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x= 63,
        .y = 308,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_mic_image,
    },

     {
        .id = CALL_OUTGOING_HUNGUP_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x= 181,
        .y = 308,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_hungup_image,
    },



     {
        .id = CALL_OUTGOING_PHONE_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x= 298,
        .y = 308,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_phone_image,
    },



    {
        .id = CALL_OUTGOING_TEXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 140,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_text,
    },

    {
        .id = CALL_OUTGOING_TIME_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 201,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_num,
    },

    {
        .id = CALL_OUTGOING_CURRENT_TIME_ID,
        .type = TYPE_GUI_CONTROL_TIME,
		.y = 22,
        .width = LCD_SIZE_WIDTH,
        .height = 26,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_time,
    },



///////////////////////////////////////////////////////////////////////////////////
    {   // vol - bg
        .id = CALL_LAYOUT_VOLBG_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 95,
        .y = 278,
        .width = 279,
        .height = 6,
        .visible= 0,
        .child_num = 1,
        .children = &gui_call_vol_bg_image,
    },

    {   // vol - ind
        .id = CALL_LAYOUT_VOLIND_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 95,    // 16+52,
        .y = 278,   // 326+22,
        .width = 279,
        .height = 6,
        .visible= 0,
        .child_num = 1,
        .children = &gui_call_vol_ind_image,
    },


       {
        .id = CALL_LAYOUT_VOLDN_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x= 35,
        .y = 254,
        .width = 56,
        .height = 56,
        .visible= 0,
        .child_num = 1,
        .children = &gui_call_voldn_image,
    },

    {
        .id = CALL_LAYOUT_VOLUP_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x= 383,
        .y = 254,
        .width = 56,
        .height = 56,
        .visible= 0,
        .child_num = 1,
        .children = &gui_call_volup_image,
    },



};

const gui_screen_struct app_call_outgoing_screen =
{
	.children = gui_call_outgoing_widget,
	.child_num = countof(gui_call_outgoing_widget),
};

//****************************************************call outgoing****************************************************//


