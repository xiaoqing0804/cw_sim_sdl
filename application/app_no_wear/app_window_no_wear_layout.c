#include "app_window_no_wear_layout.h"

static const gui_image_struct gui_no_wear_bg_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_o2_no_bg_info,
};

static const gui_image_struct gui_no_wear_round_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_o2_no_round_info,
};

static const gui_image_struct gui_no_wear_arrow_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_o2_no_arrow_info,
};

static const gui_image_struct gui_no_wear_retry_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_HCENTER,
        .data = &pic_o2_result_retry_info,
};

static const gui_font_struct gui_no_wear_title_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .align = GUI_ALIGN_HCENTER,
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_HCENTER,
        .value.string_id = STRING_HEART_NO_TOUCH,
        .scroll = 1,
};

/**********************************************************/

static const gui_widget_struct gui_no_wear_widget[] =
    {
        {
            .id = NO_WEAR_LAYOUT_TITLE_ID,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 40,
            .y = 110,
            .width = LCD_SIZE_WIDTH - 80,
            .height = 50+30,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_no_wear_title_text,
        },

        {
            .id = NO_WEAR_LAYOUT_BG_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 106,
            .y = 178+30,
            .width = 256,
            .height = 100,
            .visible = 1,
            .child_num = 1,
            .children = &gui_no_wear_bg_image,
        },

        {
            .id = NO_WEAR_LAYOUT_ROUND_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 171,
            .y = 205+30,
            .width = 28,
            .height = 28,
            .visible = 1,
            .child_num = 1,
            .children = &gui_no_wear_round_image,
        },

        {
            .id = NO_WEAR_LAYOUT_ARROW_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 122,
            .y = 208+30,
            .width = 29,
            .height = 20,
            .visible = 1,
            .child_num = 1,
            .children = &gui_no_wear_arrow_image,
        },

        {
            .id = NO_WEAR_LAYOUT_RETRY_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 0,
            .y = 323,
            .width = LCD_SIZE_WIDTH,
            .height = 96,
            .visible = 1,
            .child_num = 1,
            .children = &gui_no_wear_retry_image,
        },

};

const gui_screen_struct app_no_wear_screen =
    {
        .type = TYPE_GUI_LAYOUT_PANNEL,
        .children = gui_no_wear_widget,
        .child_num = countof(gui_no_wear_widget),
};
