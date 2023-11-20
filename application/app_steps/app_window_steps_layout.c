#include "app_window_steps.h"
#include "app_window_steps_layout.h"
#include "app_window_steps_ui.h"

#include "gui_surface_control_base.h"
#include "picture.h"
#include "language.h"

static const gui_image_struct gui_steps_bg_image[] =
    {
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
            .x = 0,
            .y = 0,
            .data = &pic_Step_flag_bg_1_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
            .x = LCD_SIZE_HALF_WIDTH,
            .y = 0,
            .data = &pic_Step_flag_bg_2_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
            .x = 0,
            .y = LCD_SIZE_HALF_HEIGHT,
            .data = &pic_Step_flag_bg_3_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
            .x = LCD_SIZE_HALF_WIDTH,
            .y = LCD_SIZE_HALF_HEIGHT,
            .data = &pic_Step_flag_bg_4_info,
        },
};

static const gui_font_struct gui_kcal_number =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "00",
};

static const gui_font_struct gui_kal_txt = //
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .id = 0,
        .x = 0,
        .y = 0,
        .anchor_x = 0,
        .anchor_y = 0,
        .auto_wrap = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_XSMALL,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_ACTIVITY_KCAL,
        .scroll = 1,
};

static const gui_font_struct gui_km_number =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "00",
};

static const gui_font_struct gui_km_txt = //
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .id = 0,
        .x = 0,
        .y = 0,
        .anchor_x = 0,
        .anchor_y = 0,
        .auto_wrap = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_XSMALL,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "KM",
        .scroll = 1,
};

static const gui_font_struct gui_steps_number =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "00",
};

static const gui_font_struct gui_steps_txt = //
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .id = 0,
        .x = 0,
        .y = 0,
        .anchor_x = 0,
        .anchor_y = 0,
        .auto_wrap = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_XSMALL,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_ACTIVITY_STEP,
        .scroll = 1,
};

static const gui_font_struct gui_hr_number =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "00",
};

static const gui_font_struct gui_hr_txt = //
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .id = 0,
        .x = 0,
        .y = 0,
        .anchor_x = 0,
        .anchor_y = 0,
        .auto_wrap = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_XSMALL,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_HR,
        .scroll = 1,
};

static const gui_widget_struct gui_steps_widget[] =
    {
        {
            .id = STEPS_LAYOUT_ID_BG,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 1,
            .child_num = countof(gui_steps_bg_image),
            .children = gui_steps_bg_image,
        },

        {
            .id = STEPS_STEPS_NUM_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 115,
            .y = 110,
            .width = 30,
            .height = 38,
            .visible = 1,
            .child_num = 1,
            .children = &gui_steps_number,
        },

        {
            .id = STEPS_KCAL_NUM_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 300,
            .y = 280,
            .width = 30,
            .height = 38,
            .visible = 1,
            .child_num = 1,
            .children = &gui_kcal_number,
        },

        {
            .id = STEPS_KM_NUM_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 100,
            .y = 280,
            .width = 30,
            .height = 38,
            .visible = 1,
            .child_num = 1,
            .children = &gui_km_number,
        },

        {
            .id = STEPS_HR_NUM_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 300,
            .y = 80,
            .width = 30,
            .height = 38,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_number,
        },
        {
            .id = STEPS_STEPS_TXT_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 140,
            .y = 165,
            .width = 80,
            .height = 38,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_steps_txt,
        },

        {
            .id = STEPS_KCAL_TXT_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 320,
            .y = 340,
            .width = 80,
            .height = 38,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_kal_txt,
        },

        {
            .id = STEPS_KM_TXT_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 122,
            .y = 340,
            .width = 80,
            .height = 38,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_km_txt,
        },

        {
            .id = STEPS_HR_TXT_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 325,
            .y = 147,
            .width = 80,
            .height = 38,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_hr_txt,
        },
};

const gui_screen_struct gui_screen_steps =
    {
        .type = TYPE_GUI_LAYOUT_PANNEL,
        .order = 0,
        .children = gui_steps_widget,
        .child_num = countof(gui_steps_widget),
};
