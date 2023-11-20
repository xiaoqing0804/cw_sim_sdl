#include "app_window_sos_layout.h"

static const gui_font_struct gui_sos_no_helper =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .value_align = GUI_ALIGN_HCENTER,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .auto_wrap = 1,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_BT_PHONE_CONNECT,
};


static const gui_image_struct gui_sos_no_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_HCENTER,
        .data = &pic_sos_no_info,
};

static const gui_widget_struct gui_sos_widget[] =
    {
        {
            .id = SOS_LAYOUT_ID_SOS_NO_IOCN,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .y = 86 + 70,
            .width = LCD_SIZE_WIDTH,
            .height = 70,
            .visible = 1,
            .child_num = 1,
            .children = &gui_sos_no_image,
        },

        {
            .id = SOS_LAYOUT_ID_SOS_NO_HELPER,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = GUI_CONTENT_GAP_LEFT,
            .y = 262 + 20,
            .width = GUI_CONTENT_WIDTH,
            .height = 120,
            .visible = 1,
            .child_num = 1,
            .children = &gui_sos_no_helper,
        },
};

const gui_screen_struct gui_screen_sos =
    {
        .children = gui_sos_widget,
        .child_num = countof(gui_sos_widget),
};
