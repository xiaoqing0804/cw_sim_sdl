#include "app_window_findwatch.h"
#include "app_window_findwatch_layout.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"

#include "bsp_includes.h"


#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "application_config_main_window.h"



#define UI_PI		3.14159265358979f

static const gui_image_struct gui_find_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_find_device_info,
};

// text
static const gui_font_struct gui_find_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_FIND_DEVICE,
};


static const gui_widget_struct gui_find_widget[] =
{
    {
        .y = 150,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = 99,
        .visible= 1,
        .child_num = 1,
        .scale = 1.0f,
        .children = &gui_find_image,
    },
    {
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 300,
        .width = LCD_SIZE_WIDTH,
        .height = 120,
        .visible= 1,
        .child_num = 1,
        .children = &gui_find_text,
    },
};

const gui_screen_struct app_find_screen =
{
	.children = gui_find_widget,
	.child_num = countof(gui_find_widget),
};
