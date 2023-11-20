#include "app_window_findphone.h"
#include "app_window_findphone_ui.h"
#include "app_window_findphone_layout.h"


#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "bt_module.h"			// iPhone14查找手机死机问题

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"


#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_animation.h"
#include "application_config_main_window.h"



#define UI_PI		3.14159265358979f


static const gui_image_struct gui_findphone_bg_frames =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_findphone_Gif_05_info,
};


// ble
static const gui_image_struct gui_findphone_unlink_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_ble_unlink_info,
};


static const gui_font_struct gui_findphone_unlink_txt =   //name
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.auto_wrap = 0,
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id =STRING_DISCONNECT,
};

// text
static const gui_font_struct gui_find_text_ind =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_FIND_PHONE_CHILD,
};


static const gui_widget_struct gui_find_widget[] =
{
    {
        .id = 1,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_findphone_unlink_image,
    },

    {
        .id = 2,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 0,
        .y = 0,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_findphone_bg_frames,
    },

	{
		.id = 3,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 382,
		.width = LCD_SIZE_HEIGHT,
		.height = 50,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_findphone_unlink_txt,
	},

    {
		.id = 4,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 360,
		.width = LCD_SIZE_HEIGHT,
		.height = 73,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_find_text_ind,
	},

};

const gui_screen_struct app_findphone_screen =
{
	.children = gui_find_widget,
	.child_num = countof(gui_find_widget),
};

