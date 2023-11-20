#include "app_window_ota.h"
#include "app_window_ota_ui.h"
#include "app_window_ota_layout.h"

#include "picture.h"
#include "language.h"
#include "debug_info.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "ota.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image_number.h"

#include "application_config_main_window.h"



static const gui_number_image_list_struct gui_ota_number_images =
{
	.number = 
	{
		&pic_ota_num_0_info,
		&pic_ota_num_1_info,
		&pic_ota_num_2_info,
		&pic_ota_num_3_info,
		&pic_ota_num_4_info,
		&pic_ota_num_5_info,
		&pic_ota_num_6_info,
		&pic_ota_num_7_info,
		&pic_ota_num_8_info,
		&pic_ota_num_9_info,
	},
	.dot = &pic_ota_num_dot_info,
	.colon = &pic_ota_num_col_info,
	.percent = &pic_ota_num_010_info,
};

static const gui_image_number_struct gui_ota_number =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.number_image_list = &gui_ota_number_images,
	.value.string = "00",
};


// ota
static const gui_image_struct gui_ota_image = 
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_ota_info,
};


static const gui_widget_struct gui_ota_widget[] =
{
    {   // bg
        .type = TYPE_GUI_CONTROL_IMAGE,
        .y = 15,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_ota_image,
    },

    {
        .id = 5,
        .type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
        .y = 10,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_ota_number,
    },

    {
        .id = 6,
        .type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
        .y = 50,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_ota_number,
    },

    {
        .id = 7,
        .type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
        .y = 350,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_ota_number,
    },

};

 const gui_screen_struct app_ota_screen_layout =
{
	.children = gui_ota_widget,
	.child_num = countof(gui_ota_widget),
};

