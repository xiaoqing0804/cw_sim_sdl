#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_message.h"

#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "app_window_message_delete_all.h"
#include "app_window_message_delete_all_layout.h"

static const gui_font_struct gui_message_delete_all_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_CLEAR_ALL,
};

static const gui_image_struct gui_message_delete_all_cancel_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_operator2_cancel_info,
};

static const gui_image_struct gui_message_delete_all_ok_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_operator2_ok_info,
};

static const gui_widget_struct gui_message_delete_all_widget[] =
    {
        {
            .id = 0,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 0,
            .y = 0,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT * 3 / 4,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_delete_all_text,
        },

        {
            .id = APP_MESSAGE_DEL_CANCEL,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 91,
            .y = 306,
            .width = 102,
            .height = 102,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_delete_all_cancel_image,
        },
        {
            .id = APP_MESSAGE_DEL_OK,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 270,
            .y = 306,
            .width = 102,
            .height = 102,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_delete_all_ok_image,
        },
};

const gui_screen_struct gui_message_delete_all_screen =
    {
        .order = 0,
        .children = gui_message_delete_all_widget,
        .child_num = countof(gui_message_delete_all_widget),
};


