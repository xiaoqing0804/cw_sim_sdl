
#include "app_window_call_dial_layout.h"

//****************************************************call dial****************************************************//
static const gui_image_struct gui_call_dial_pad_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_call_bg_1_info,
};

/*static const gui_image_struct gui_call_dial_del_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_call_delecont_info,
};*/

static const gui_font_struct gui_call_dial_number_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_26,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "1234567890",
};

static const gui_widget_struct gui_call_dial_widget[] =
{
    {
        .id = CALL_DIAL_PAD_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_dial_pad_image,
    },

    /*{
        .id = CALL_DIAL_DEL_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 320,
        .y = 32,
        .width = 60,
        .height = 42,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_dial_del_image,
    },*/

    {
        .id = CALL_DIAL_NUMBER_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 55,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_dial_number_text,
    },
};

const gui_screen_struct app_call_dial_screen =
{
    .children = gui_call_dial_widget,
    .child_num = countof(gui_call_dial_widget),
};
//****************************************************call dial****************************************************//



