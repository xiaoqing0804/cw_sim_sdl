
#include "picture.h"
#include "language.h"
#include "data_manager_contact.h"

#include "gui_surface_control_base.h"

#include "application_config_main_window.h"

#include "app_window_call_layout.h"

//****************************************************call****************************************************//
static const gui_image_struct gui_miss_ind_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_missed_call_info,
};

static const gui_font_struct gui_call_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "",
};

static const gui_font_struct gui_call_number =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "",
};

static const gui_image_struct gui_call_reply_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_reply_info,
};

static const gui_widget_struct gui_call_widget[] =
{
    {
        .id = CALL_INFO,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 110,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_text,
    },

    {
        .id = CALL_TEXT_INFO,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 138,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_number,
    },

	{
        .id = CALL_REPLY,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 182,
        .y = 200,
        .width = 120,
        .height = 53,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_reply_image,
    },

    {
        .id = CALL_HANGUP,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .y = 308,
        .width = LCD_SIZE_WIDTH,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_miss_ind_image,
    },
};

const gui_screen_struct app_call_screen =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.order = 0,
	.children = gui_call_widget,
	.child_num = countof(gui_call_widget),
};
//****************************************************call****************************************************//

