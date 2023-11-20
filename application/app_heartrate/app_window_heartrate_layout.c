#include "app_window_heartrate_layout.h"

static const gui_image_struct gui_hr_bg_image[] =
    {
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
            .x = 0,
            .y = 2,
            .data = &pic_hr_bg_001_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
            .x = 0,
            .y = LCD_SIZE_HALF_HEIGHT,
            .data = &pic_hr_bg_002_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
            .x = LCD_SIZE_HALF_WIDTH,
            .y = 2,
            .data = &pic_hr_bg_003_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
            .x = LCD_SIZE_HALF_WIDTH,
            .y = LCD_SIZE_HALF_HEIGHT,
            .data = &pic_hr_bg_004_info,
        },
};

static const gui_image_struct gui_hr_icon_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_hr_gif_1_info,
};

static const gui_image_struct gui_hr_item_line_image[] =
    {
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 0,
            .y = 0,
            .data = &pic_hr_item_line_1_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 182,
            .y = 0,
            .data = &pic_hr_item_line_2_info,
        },
};

static const gui_font_struct gui_hr_history_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(152, 182, 213),
        .size = SYS_FONT_XSMALL,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value_align = GUI_ALIGN_TOP,
        .value.string = "",
        .scroll = 1,
};

static const gui_font_struct gui_hr_value_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_NUMBER_38,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_BOTTOM),
        .value.string = "0",
};

static const gui_font_struct gui_hr_bmp_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_NUMBER_26,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value_align = GUI_ALIGN_BOTTOM,
        .value.string = "bmp",
};

/**************************当前心率********************************/

static const gui_font_struct gui_hr_curr_title_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_BOTTOM,
        .value.string_id = STRING_CURRENT_HEART_RATE,
        .scroll = 1,
};

/**************************静息心率********************************/

static const gui_font_struct gui_hr_resting_title_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_RESTING_HEART_RATE,
        .value_align = GUI_ALIGN_BOTTOM,
        .scroll = 1,
};

/**************************步行心率********************************/

static const gui_font_struct gui_hr_walk_title_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_WALK_HEART_RATE,
        .value_align = GUI_ALIGN_BOTTOM,
        .scroll = 1,
};

/**********************************************************/

static const gui_widget_struct gui_hreartrate_widget[] =
    {
        {
            .id = HR_BOX_BG_IMAGE_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 1,
            .fix = 1,
            .child_num = countof(gui_hr_bg_image),
            .children = gui_hr_bg_image,
        },

        /*******************************当前心率**********************************/
        {
            .id = HR_BOX_CURR_ICON_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 36,
            .y = 146,
            .width = 68,
            .height = 68,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_icon_image,
        },
        {
            .id = HR_BOX_CURR_TITLE_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 107,
            .y = 180 - 70,
            .width = 144,
            .height = 70,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_hr_curr_title_text,
        },
        {
            .id = HR_BOX_CURR_VALUE_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 259,
            .y = 180 - 60,
            .width = 115,
            .height = 70,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_value_text,
        },
        {
            .id = HR_BOX_CURR_BPM_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 375,
            .y = 180 - 65,
            .width = 60,
            .height = 70,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_bmp_text,
        },
        {
            .id = HR_BOX_CURR_HISTORY_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 107,
            .y = 190,
            .width = 320,
            .height = 70,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_hr_history_text,
        },
        {
            .id = HR_BOX_CURR_LINE_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = (LCD_SIZE_WIDTH - 364) / 2,
            .y = 245,
            .width = 364,
            .height = 4,
            .visible = 1,
            .child_num = countof(gui_hr_item_line_image),
            .children = gui_hr_item_line_image,
        },

        /*******************************静息心率**********************************/
        {
            .id = HR_BOX_RESTING_ICON_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 36,
            .y = 296,
            .width = 68,
            .height = 68,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_icon_image,
        },
        {
            .id = HR_BOX_RESTING_TITLE_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 107,
            .y = 330 - 70,
            .width = 144,
            .height = 70,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_hr_resting_title_text,
        },
        {
            .id = HR_BOX_RESTING_VALUE_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 259,
            .y = 330 - 60,
            .width = 115,
            .height = 70,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_value_text,
        },
        {
            .id = HR_BOX_RESTING_BPM_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 375,
            .y = 330 - 65,
            .width = 60,
            .height = 70,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_bmp_text,
        },
        {
            .id = HR_BOX_RESTING_HISTORY_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 107,
            .y = 340,
            .width = 320,
            .height = 70,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_hr_history_text,
        },
        {
            .id = HR_BOX_RESTING_LINE_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = (LCD_SIZE_WIDTH - 364) / 2,
            .y = 397,
            .width = 364,
            .height = 4,
            .visible = 1,
            .child_num = countof(gui_hr_item_line_image),
            .children = gui_hr_item_line_image,
        },

        /*******************************步行心率**********************************/
        {
            .id = HR_BOX_WALK_ICON_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 36,
            .y = 449,
            .width = 68,
            .height = 68,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_icon_image,
        },
        {
            .id = HR_BOX_WALK_TITLE_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 107,
            .y = 487 - 70,
            .width = 144,
            .height = 70,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_hr_walk_title_text,
        },
        {
            .id = HR_BOX_WALK_VALUE_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 259,
            .y = 487 - 60,
            .width = 115,
            .height = 70,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_value_text,
        },
        {
            .id = HR_BOX_WALK_BPM_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 375,
            .y = 487 - 65,
            .width = 60,
            .height = 70,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_bmp_text,
        },
        {
            .id = HR_BOX_WALK_HISTORY_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 107,
            .y = 497,
            .width = 320,
            .height = 70,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_hr_history_text,
        },
};

const gui_layout_scroll_struct gui_layout_config_hr =
    {
        .height = 620,
        .scroll = 1,
};

const gui_screen_struct app_heartrate_screen =
    {
        .type = TYPE_GUI_LAYOUT_SCROLL,
        .children = gui_hreartrate_widget,
        .child_num = countof(gui_hreartrate_widget),
        .layout_config = &gui_layout_config_hr,
};
