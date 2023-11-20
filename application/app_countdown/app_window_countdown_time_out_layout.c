#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager.h"
#include "data_manager_flash.h"
#include "watchface.h"
#include "arithmetic_common.h"
#include "arithmetic_sleep.h"

#include "application_config_app_info.h"

#include "system_util_math_geometry.h"
#include "font_convert.h"
#include "gui_surface_cache.h"
#include "gui_surface_box_pointer.h"
#include "gui_drivers_display.h"
#include "gui_surface_control_base.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_node.h"

#include "bsp_motor/motor.h"

#include "app_window_countdown_time_out_layout.h"

static const gui_font_struct gui_main_time_out_text =
{
	.x = 0,
	.y = 0,
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_TIMEUP,
};


// widget ----------------------------------------------------------------------------
enum{
    TIME_OUT_TXT_ID = 100,
};
static const gui_widget_struct gui_main_time_out_widget[] =
{
    {
        .id = TIME_OUT_TXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_main_time_out_text,
    },
};

const gui_screen_struct gui_main_time_out_screen =
{
	.order = 0,
	.children = gui_main_time_out_widget,
	.child_num = countof(gui_main_time_out_widget),
};




