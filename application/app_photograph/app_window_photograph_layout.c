#include "app_window_photograph.h"
#include "app_window_photograph_ui.h"
#include "app_window_photograph_layout.h"

#include "debug_info.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "arithmetic_steps.h"
#include "data_receive_package.h"

#include "gui_window.h"


#include "app_widget/app_window_widget_delete.h"



// cap
static const gui_image_struct gui_photo_cap_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_photograph_info,
};

// ble
static const gui_font_struct gui_photo_connect_ind =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_DISCONNECT,
};
/*
static const gui_image_struct gui_photo_conn_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_main_ble_disconnect_info,
};
*/
// time
static const gui_font_struct gui_photo_click_ind =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_PHOTOGRAPH_CLICK,
};




static const gui_widget_struct gui_photo_widget[] =
{
    {
        .id = PHOTOGRAPH_ID_TEXT,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 0,
        .y = 170,
        .width = LCD_SIZE_WIDTH,
        .height = 93,
        .visible= 1,
        .child_num = 1,
        .children = &gui_photo_cap_image,
    },
/*
    {
        .id = 4,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 0,
        .y = 200,
        .width = LCD_SIZE_WIDTH,
        .height = 22,
        .visible= 1,
        .child_num = 1,
        .children = &gui_photo_conn_image,
    },
*/
    {
        .id = 5,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 290,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_photo_connect_ind,
    },

    {
        .id = PHOTOGRAPH_ID_YES,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 310,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_photo_click_ind,
    },
};

const gui_screen_struct app_photo_layout_screen =
{
	.children = gui_photo_widget,
	.child_num = countof(gui_photo_widget),
};



