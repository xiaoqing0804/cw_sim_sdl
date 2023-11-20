#include "app_window_o2_layout.h"

static const gui_number_image_list_struct gui_o2_data_image =
    {
        .number =
            {
                &pic_o2_data_0_info,
                &pic_o2_data_1_info,
                &pic_o2_data_2_info,
                &pic_o2_data_3_info,
                &pic_o2_data_4_info,
                &pic_o2_data_5_info,
                &pic_o2_data_6_info,
                &pic_o2_data_7_info,
                &pic_o2_data_8_info,
                &pic_o2_data_9_info,
            },
        .percent = &pic_o2_data_10_info,
};

/**************************测量********************************/

static const gui_image_struct gui_o2_start_bg_image[] =
    {
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 0,
            .y = 0,
            .data = &pic_o2_start_bg_1_001_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 170,
            .y = 0,
            .data = &pic_o2_start_bg_1_003_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 0,
            .y = 170,
            .data = &pic_o2_start_bg_1_002_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 170,
            .y = 170,
            .data = &pic_o2_start_bg_1_004_info,
        },
};

static const gui_image_number_struct gui_o2_start_time_text =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .number_image_list = &gui_o2_data_image,
        .value.string = "0",
};

/**************************测量结果********************************/
static const gui_image_struct gui_o2_result_bg_1_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_o2_result_bg_001_info,
};
static const gui_image_struct gui_o2_result_bg_2_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_o2_result_bg_002_info,
};

static const gui_image_number_struct gui_o2_result_data_text =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .number_image_list = &gui_o2_data_image,
        .value.string = "0%%",
};

static const gui_image_struct gui_o2_result_retry_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_HCENTER,
        .data = &pic_o2_result_retry_info,
};

/**********************************************************/

static const gui_widget_struct gui_o2_widget[] =
    {

        /**************************测量********************************/
        {
            .id = O2_LAYOUT_ID_START_BG,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = (LCD_SIZE_WIDTH - 340) / 2,
            .y = (LCD_SIZE_HEIGHT - 340) / 2,
            .width = 340,  // LCD_SIZE_WIDTH,
            .height = 340, // LCD_SIZE_HEIGHT,
            .visible = 1,
            .child_num = countof(gui_o2_start_bg_image),
            .children = &gui_o2_start_bg_image,
        },

        {
            .id = O2_LAYOUT_ID_START_TIME,
            .type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
            .y = 353,
            .width = LCD_SIZE_WIDTH,
            .height = 66,
            .visible = 1,
            .clip = 0,
            .space_x = 3,
            .child_num = 1,
            .children = &gui_o2_start_time_text,
        },

        /**************************测量结果********************************/
        {
            .id = O2_LAYOUT_ID_RESULT_BG_1,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 57,
            .y = 112,
            .width = 240,
            .height = 166,
            .visible = 1,
            .child_num = 1,
            .children = &gui_o2_result_bg_1_image,
        },
        {
            .id = O2_LAYOUT_ID_RESULT_BG_2,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 296,
            .y = 112,
            .width = 113,
            .height = 166,
            .visible = 1,
            .child_num = 1,
            .children = &gui_o2_result_bg_2_image,
        },

        {
            .id = O2_LAYOUT_ID_RESULT_DATA,
            .type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
            .x = 0,
            .y = 112,
            .width = LCD_SIZE_WIDTH,
            .height = 166,
            .visible = 1,
            .clip = 0,
            .space_x = 3,
            .child_num = 1,
            .children = &gui_o2_result_data_text,
        },

        {
            .id = O2_LAYOUT_ID_RESULT_RETRY,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = (LCD_SIZE_WIDTH - 102) / 2,
            .y = 318,
            .width = 102,
            .height = 102, // LCD_SIZE_HEIGHT,
            .visible = 1,
            .child_num = 1,
            .children = &gui_o2_result_retry_image,
        },
};

const gui_screen_struct app_o2_screen =
    {
        .type = TYPE_GUI_LAYOUT_PANNEL,
        .children = gui_o2_widget,
        .child_num = countof(gui_o2_widget),
};
