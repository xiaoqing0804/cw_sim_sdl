#include "app_window_personnal_layout.h"

#define PERSONNAL_LIST_LEFT (GUI_CONTENT_GAP_LEFT)
#define PERSONNAL_LIST_TOP (161)
#define PERSONNAL_LIST_BOTTOM (GUI_CONTENT_GAP_BOTTOM)

#define PERSONNAL_START_ID (PERSONNAL_LAYOUT_ID_HEIGHT)
#define PERSONNAL_END_ID (PERSONNAL_LAYOUT_ID_BMI)

#define PERSONNAL_ITEM_HEIGHT (GUI_ITEM_HEIGHT)
#define PERSONNAL_ITEM_GAP (GUI_ITEM_SPACE)
#define PERSONNAL_ROW_HEIGHT (PERSONNAL_ITEM_HEIGHT + PERSONNAL_ITEM_GAP)

#define PERSONNAL_ITEM_NAME_X (GUI_ITEM_GAP_LEFT)
#define PERSONNAL_ITEM_NAME_WIDTH (200)

#define PERSONNAL_ITEM_VALUE_X (270)
#define PERSONNAL_ITEM_VALUE_WIDTH (122)

#define PERSONNAL_ITEM_Y(id) (PERSONNAL_LIST_TOP + 1 + ((id)-PERSONNAL_START_ID) * (PERSONNAL_ROW_HEIGHT))

#define PERSONNAL_LIST_WIDTH (GUI_CONTENT_WIDTH)
#define PERSONNAL_LIST_HEIGHT (PERSONNAL_ITEM_Y(PERSONNAL_END_ID) + PERSONNAL_ITEM_HEIGHT + PERSONNAL_LIST_BOTTOM)

/**********************************************************/

static const gui_canvas_struct gui_personnal_title_bg_rect =
    {
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL, // TYPE_GUI_DRAW
        .penSize = 2,
        .penColor = COLOR_RGB(0, 0, 0),
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_WIDTH,
        .canvas.rect.y1 = PERSONNAL_LIST_TOP,
};

static const gui_image_struct gui_personnal_title_icon =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .data = &pic_setting_app_icon_personal_info,
};

/*********************************************************/

static const gui_image_struct gui_personnal_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_setting_list_icon_bg_2_info,
};

/***************************1******************************/

static const gui_font_struct gui_personnal_height_text_name =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = PERSONNAL_ITEM_NAME_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = PERSONNAL_ITEM_NAME_WIDTH,
        .height = PERSONNAL_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_HEIGHT,
};

static const gui_font_struct gui_personnal_height_text_value =
    {
        .id = PERSONNAL_LAYOUT_ID_HEIGHT_TEXT,
        .type = TYPE_GUI_DRAW_TEXT,
        .x = PERSONNAL_ITEM_VALUE_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = PERSONNAL_ITEM_VALUE_WIDTH,
        .height = PERSONNAL_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_NUMBER,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_VCENTER),
        .value.string_id = 0,
};

static const gui_mix_struct gui_widget_personnal_height[] =
    {
        {
            .data = &gui_personnal_bg,
        },
        {
            .data = &gui_personnal_height_text_name,
        },
        {
            .data = &gui_personnal_height_text_value,
        },
};

/**************************2********************************/

static const gui_font_struct gui_personnal_weight_text_name =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = PERSONNAL_ITEM_NAME_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = PERSONNAL_ITEM_NAME_WIDTH,
        .height = PERSONNAL_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = STRING_WEIGHT,
};

static const gui_font_struct gui_personnal_weight_text_value =
    {
        .id = PERSONNAL_LAYOUT_ID_WEIGHT_TEXT,
        .type = TYPE_GUI_DRAW_TEXT,
        .x = PERSONNAL_ITEM_VALUE_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = PERSONNAL_ITEM_VALUE_WIDTH,
        .height = PERSONNAL_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_NUMBER,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_VCENTER),
        .value.string_id = 0,
};

static const gui_mix_struct gui_widget_personnal_weight[] =
    {
        {
            .data = &gui_personnal_bg,
        },
        {
            .data = &gui_personnal_weight_text_name,
        },
        {
            .data = &gui_personnal_weight_text_value,
        },
};

/**************************3********************************/

static const gui_font_struct gui_personnal_bmi_text_name =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = PERSONNAL_ITEM_NAME_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = PERSONNAL_ITEM_NAME_WIDTH,
        .height = PERSONNAL_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value_align = GUI_ALIGN_VCENTER,
        .value.string_id = "BMI",
};

static const gui_font_struct gui_personnal_bmi_text_value =
    {
        .id = PERSONNAL_LAYOUT_ID_BMI_TEXT,
        .type = TYPE_GUI_DRAW_TEXT,
        .x = PERSONNAL_ITEM_VALUE_X,
        .y = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .width = PERSONNAL_ITEM_VALUE_WIDTH,
        .height = PERSONNAL_ITEM_HEIGHT,
        .value_type = GUI_FONT_VALUE_TYPE_NUMBER,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_VCENTER),
        .value.string_id = 0,
};

static const gui_mix_struct gui_widget_personnal_bmi[] =
    {
        {
            .data = &gui_personnal_bg,
        },
        {
            .data = &gui_personnal_bmi_text_name,
        },
        {
            .data = &gui_personnal_bmi_text_value,
        },
};

/**********************************************************/

static const gui_widget_struct gui_widget_personnal[] =
    {
        {
            .id = PERSONNAL_LAYOUT_ID_HEIGHT,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = PERSONNAL_LIST_LEFT,
            .y = PERSONNAL_ITEM_Y(PERSONNAL_LAYOUT_ID_HEIGHT),
            .width = PERSONNAL_LIST_WIDTH,
            .height = PERSONNAL_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_personnal_height),
            .children = gui_widget_personnal_height,
        },
        {
            .id = PERSONNAL_LAYOUT_ID_WEIGHT,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = PERSONNAL_LIST_LEFT,
            .y = PERSONNAL_ITEM_Y(PERSONNAL_LAYOUT_ID_WEIGHT),
            .width = PERSONNAL_LIST_WIDTH,
            .height = PERSONNAL_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_personnal_weight),
            .children = gui_widget_personnal_weight,
        },
        {
            .id = PERSONNAL_LAYOUT_ID_BMI,
            .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
            .x = PERSONNAL_LIST_LEFT,
            .y = PERSONNAL_ITEM_Y(PERSONNAL_LAYOUT_ID_BMI),
            .width = PERSONNAL_LIST_WIDTH,
            .height = PERSONNAL_ITEM_HEIGHT,
            .visible = 1,
            .clip = 1,
            .child_num = countof(gui_widget_personnal_bmi),
            .children = gui_widget_personnal_bmi,
        },

        {
            .type = TYPE_GUI_CONTROL_CANVAS,
            .order = 1,
            .width = LCD_SIZE_WIDTH,
            .height = PERSONNAL_LIST_TOP,
            .visible = 1,
            .fix = 1,
            .child_num = 1,
            .children = &gui_personnal_title_bg_rect,
        },

        {
            .id = PERSONNAL_LAYOUT_ID_HEAD,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .width = LCD_SIZE_WIDTH,
            .height = PERSONNAL_LIST_TOP,
            .order = 2,
            .visible = 1,
            .fix = 1,
            .child_num = 1,
            .children = &gui_personnal_title_icon,
        },
};

const gui_layout_scroll_struct gui_layout_config_personnal =
    {
        .height = PERSONNAL_LIST_HEIGHT,
        .scroll = 1,
};

const gui_screen_struct gui_screen_personnal =
    {
        .type = TYPE_GUI_LAYOUT_SCROLL,
        .children = gui_widget_personnal,
        .child_num = countof(gui_widget_personnal),
        .layout_config = (const void *)&gui_layout_config_personnal,
};
