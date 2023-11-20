#include "app_window_usb_layout.h"

static const gui_font_struct gui_usb_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "Mass storage",
};

static const gui_image_struct gui_usb_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .data = &pic_widget_btn_delete_info,
};

static const gui_widget_struct gui_usb_widgets[] =
    {
        {
            .type = TYPE_GUI_CONTROL_LABEL,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 1,
            .child_num = 1,
            .children = &gui_usb_text,
        },
        {
            .id = 10,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .y = LCD_SIZE_HEIGHT / 2,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT / 2,
            .visible = 1,
            .child_num = 1,
            .children = &gui_usb_image,
        },
};

const gui_screen_struct gui_screen_usb =
    {
        .children = gui_usb_widgets,
        .child_num = countof(gui_usb_widgets),
};

