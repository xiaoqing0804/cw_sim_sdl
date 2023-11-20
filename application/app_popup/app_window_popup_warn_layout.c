
#include "app_window_popup_warn_layout.h"

#define POPUP_WARN_BACK_IMAGE_HEIGHT (88)

static const gui_font_struct gui_text_popup_warn =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .auto_wrap = 1,
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .value.string = "",
};

static const gui_image_struct gui_image_popup_warn =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_HCENTER,
        .data = &pic_message_info_back_info,
};

static const gui_widget_struct gui_widget_popup_warn[] =
    {
        {
            .id = POPUP_WARN_LAYOUT_ID_INFO,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = GUI_CONTENT_GAP_LEFT,
            .y = GUI_CONTENT_GAP_TOP,
            .width = LCD_SIZE_WIDTH - GUI_CONTENT_GAP_LEFT * 2,
            .height = LCD_SIZE_HEIGHT - GUI_CONTENT_GAP_TOP - POPUP_WARN_BACK_IMAGE_HEIGHT,
            .visible = 1,
            .child_num = 1,
            .children = &gui_text_popup_warn,
        },
        {
            .id = POPUP_WARN_LAYOUT_ID_BACK,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .y = LCD_SIZE_HEIGHT - POPUP_WARN_BACK_IMAGE_HEIGHT,
            .width = LCD_SIZE_WIDTH,
            .height = POPUP_WARN_BACK_IMAGE_HEIGHT,
            .visible = 1,
            .child_num = 1,
            .children = &gui_image_popup_warn,
        },
};

const gui_screen_struct gui_screen_popup_warn =
    {
        .children = gui_widget_popup_warn,
        .child_num = countof(gui_widget_popup_warn),
};
