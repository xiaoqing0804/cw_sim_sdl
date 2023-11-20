#include "app_window_lowpower_layout.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "application.h"
#include "gui_window.h"

static const gui_image_struct gui_lowpower_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .scale = 1.5f,
        .x = LCD_SIZE_HALF_WIDTH,
        .y = LCD_SIZE_HALF_HEIGHT,
        .anchor_x = ANCHOR_VALUE(0.5f),
        .anchor_y = ANCHOR_VALUE(0.5f),
        .data = &pic_low_power_info,
};

static const gui_font_struct gui_lowpower_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "100%",
};

static const gui_widget_struct gui_lowpower_widget[] =
    {
        {
            .id = LOWPOWER_LAYOUT_ID_IMAGE,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 1,
            .child_num = 1,
            .children = &gui_lowpower_image,
        },
        {
            .id = LOWPOWER_LAYOUT_ID_TEXT,
            .type = TYPE_GUI_CONTROL_LABEL,
            .y = LCD_SIZE_HEIGHT*8/10,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT*2/10,
            .visible = 1,
            .child_num = 1,
            .children = &gui_lowpower_text,
        },
};

const gui_screen_struct gui_screen_lowpower =
    {
        .order = 0,
        .children = gui_lowpower_widget,
        .child_num = countof(gui_lowpower_widget),
};
