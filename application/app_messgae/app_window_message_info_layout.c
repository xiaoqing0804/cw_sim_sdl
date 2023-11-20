
#include "picture.h"
#include "language.h"
#include "feature_all.h"
#include "gui_core_all.h"

#include "app_window_message_list_layout.h"
#include "app_window_message_info_layout.h"



static const gui_image_struct gui_message_info_bg_top_img =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_message_info_bg_top_info,
};

static const gui_image_struct gui_message_info_bg_bot_img =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_message_info_bg_bot_info,
};

gui_canvas_struct gui_message_info_bg_mid_rect =
{
    .id = 1,
	.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,	  // TYPE_GUI_DRAW
	.penSize = 2,
	.penColor = COLOR_RGB(33, 33, 33),
	.canvas.rect.x0 = 0,
	.canvas.rect.y0 = 0,
	.canvas.rect.x1 = MSG_BG_IMG_W-1,
	.canvas.rect.y1 = MSG_BG_MID_H-1,
};


static const gui_image_struct gui_message_info_icon =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_msg_other_info,
};

static const gui_font_struct gui_message_info_time_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .auto_wrap = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_NUMBER_20,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "00:00",
};

const gui_font_struct gui_message_info_title_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .auto_size = 1,
        .width = LCD_SIZE_WIDTH - 120,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_SMALL,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "title",
};

const gui_font_struct gui_message_info_body_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .auto_wrap = 1,
        .color = COLOR_RGB(146, 146, 146),
        .size = SYS_FONT_SMALL,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "body",
};

static const gui_image_struct gui_message_goback_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .data = &pic_message_info_back_info,
};

static const gui_widget_struct gui_message_info_widget[] =
    {
        // bg -------------------------------------------------------------
        {
            .id =APP_MESSAGE_INFO_BG_TOP,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = MSG_BASE_X,
            .y = MSG_BG_Y_POS,
            .width = MSG_BG_IMG_W,
            .height = MSG_BG_TOP_H,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_info_bg_top_img,
        },
        {
            .id =APP_MESSAGE_INFO_BG_MID,
            .type = TYPE_GUI_CONTROL_CANVAS,
            .x = MSG_BASE_X,
            .y = MSG_BG_Y_POS+MSG_BG_TOP_H,
            .width = MSG_BG_IMG_W,
            .height = MSG_BG_MID_H,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_info_bg_mid_rect,
        },
        {
            .id =APP_MESSAGE_INFO_BG_BOT,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = MSG_BASE_X,
            .y = MSG_BG_Y_POS+MSG_BG_TOP_H+MSG_BG_MID_H,
            .width = MSG_BG_IMG_W,
            .height = MSG_BG_BOT_H,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_info_bg_bot_img,
        },

        // msg -------------------------------------------------------------
        {
            .id = APP_MESSAGE_INFO_ICON,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = MSG_BASE_X+28,
            .y = MSG_ICON_Y_POS,
            .width = 80,
            .height = 80,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_info_icon,
        },
        {
            .id = APP_MESSAGE_INFO_TIME,
            .type = TYPE_GUI_CONTROL_LABEL,
        	.x = MSG_BASE_X+MSG_BG_IMG_W-80,    // 220,
            .y = MSG_TIME_Y_POS,
            .width = 62,
            .height = 20,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_info_time_text,
        },
        {
            .id = APP_MESSAGE_INFO_TITLE,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = MSG_BASE_X+12,
            .y = MSG_BODY_Y_POS,
            .width = MSG_BG_IMG_W-24,
            .height = 50,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_info_body_text,
        },

        // goback ------------------------------------------------------------------
        {
            .id = APP_MESSAGE_INFO_GOBACK,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .fix = 1,
            .order = 120,
            .x = 0,
            .y = LCD_SIZE_HEIGHT-MSG_OP_BAR_H,
            .width = LCD_SIZE_WIDTH,
            .height = MSG_OP_BAR_H,
            .visible = 1,
            .child_num = 1,
            .children = &gui_message_goback_image,
        },
};

static const gui_layout_scroll_struct gui_message_info_layout =
{
    .top = GUI_CONTENT_GAP_TOP,
    .bottom = 0,
	.scroll = 1,//是否可以上下滚动
	.dynamic_height = 0,
};

const gui_screen_struct gui_message_info_screen =
{
	.type = TYPE_GUI_LAYOUT_SCROLL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_message_info_widget,
	.child_num = countof(gui_message_info_widget),
	.layout_config = &gui_message_info_layout,
};


