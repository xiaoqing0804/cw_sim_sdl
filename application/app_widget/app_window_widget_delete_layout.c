#include "app_window_widget_delete_layout.h"

short g_widget_delete_layout_x_left = (44 - 4);
short g_widget_delete_layout_x_right = 44 + 44 + 4;

static const gui_image_struct gui_pic_list_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 28,
        .data = &pic_widget_list_bg_info,
};

static const gui_image_struct gui_widget_delete_del_icon = {
    .type = TYPE_GUI_DRAW_PICTURE,
    .id = WIDGET_ITEM_DEL_ICON,
    .x = 44,
    .y = 28,
    .data = &pic_widget_btn_delete_info,
};

static const gui_image_struct gui_widget_delete_add_icon = {
    .type = TYPE_GUI_DRAW_PICTURE,
    .id = WIDGET_ITEM_ADD_ICON,
    .x = 44,
    .y = 28,
    .data = &pic_widget_btn_add_l_info,
};

// app
gui_image_struct gui_widget_delete_app_icon = {
    .id = WIDGET_ITEM_APP_ICON,
    .type = TYPE_GUI_DRAW_PICTURE,
    .x = 98,
    .y = 10,
    .scale = 80 / 98.0f,
    .data = NULL,
};

gui_font_struct gui_widget_delete_app_name =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .id = WIDGET_ITEM_APP_NAME,
        .x = 190,
        .y = 33,
        .width = 170,
        .height = 45,
        .scroll = 1,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
};

static const gui_image_struct gui_widget_delete_mup_icon = {
    .type = TYPE_GUI_DRAW_PICTURE,
    .id = WIDGET_ITEM_MUP_ICON,
    .x = 385,
    .y = 33,
    .data = &pic_widget_btn_top_info,
};

static const gui_mix_struct gui_widget_delete_item[] = {
    {
        .data = &gui_pic_list_bg,
    },
    {
        .data = &gui_widget_delete_del_icon,
    },
    {
        .data = &gui_widget_delete_add_icon,
    },
    {
        .data = &gui_widget_delete_app_icon,
    },
    {
        .data = &gui_widget_delete_app_name,
    },
    {
        .data = &gui_widget_delete_mup_icon,
    },
};

const gui_widget_struct gui_widget_delete_info = {
    .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
    .width = LCD_SIZE_WIDTH,
    .height = WND_WIDGET_DELETE_LIST_ITEM_H,
    .clip = 1,
    .visible = 1,
    .child_num = countof(gui_widget_delete_item),
    .children = gui_widget_delete_item,
};

/**********************************静态**********************************************/

static const gui_layout_list_struct gui_window_widget_delete_layout =
    {
        .row_height = WND_WIDGET_DELETE_LIST_ITEM_H,

        .top = 90,
        .bottom = 90,
        .space = 10,

        .scroll = 1,
};

const gui_screen_struct gui_screen_widget_delete =
    {
        .type = TYPE_GUI_LAYOUT_LIST,
        .layout_config = &gui_window_widget_delete_layout,
};