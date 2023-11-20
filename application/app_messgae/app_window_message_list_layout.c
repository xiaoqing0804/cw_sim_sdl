

#include "picture.h"
#include "language.h"
#include "feature_all.h"
#include "gui_core_all.h"
#include "app_window_message_list_layout.h"


// layout-item
const gui_image_struct gui_message_item_bg_img =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .id = APP_MESSAGE_ITEM_CV_BG_ID,
	.x = MSG_ITEM_BASE_X,
	.y = 32,
	.data = &pic_message_bg_info,
};

static const gui_image_struct gui_message_item_type_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = APP_MESSAGE_ITEM_CV_ICON_ID,
	.x = MSG_ITEM_BASE_X+28,
	.y = 0,
	.data = &pic_msg_other_info,
};

static const gui_font_struct gui_message_item_time_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = APP_MESSAGE_ITEM_CV_TIME_ID,
	.x = MSG_ITEM_BASE_X+MSG_ITEM_BG_IMG_W-80,  // 220,
    .y = 35,
    .width = 62,
    .height = 20,
	.auto_size = 1,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_20,     // 37
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "....",
};

const gui_font_struct gui_message_item_title_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = APP_MESSAGE_ITEM_CV_SUBJECT_ID,
	.x = MSG_ITEM_BASE_X+12,
    .y = 82,
    .width = MSG_ITEM_BG_IMG_W-24,
	.auto_wrap = 1,
    .space_y = MSG_TEXT_GAP,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "....",
};

const gui_font_struct gui_message_item_subject_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = APP_MESSAGE_ITEM_CV_SUBJECT_ID,
	.x = MSG_ITEM_BASE_X+12,
    .y = 82,
    .width = MSG_ITEM_BG_IMG_W-24,
	.auto_wrap = 1,
    .space_y = MSG_TEXT_GAP,
    .color = COLOR_RGB(180, 180, 180),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "....",
};

static const gui_mix_struct gui_message_item_info[] =
{
	{.data = &gui_message_item_bg_img	},      // bg
	{.data = &gui_message_item_type_icon	},  // icon
    {.data = &gui_message_item_time_txt },      // time
	{.data = &gui_message_item_title_txt	},  // subject
};

const gui_widget_struct gui_message_item_widget =
{
    .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
    .width = LCD_SIZE_WIDTH,
    .height = 214,
    .visible= 1,
    .child_num = countof(gui_message_item_info),
    .children = gui_message_item_info,
};


/// @brief 底部删除按钮
static const gui_image_struct gui_message_delect_img =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_HCENTER,
	.data = &pic_message_delect_info,
};


/// @brief 删除按钮图标
static const gui_image_struct gui_message_delect_one_img =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_HCENTER,
	.data = &pic_message_deletect_one_info,
};


/// @brief 无消息提示
static const gui_font_struct gui_message_list_empty_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_NO_MESSAGE,
};

/// @brief
static const gui_widget_struct gui_message_list_widget[] =
{
    {
        .id = APP_MESSAGE_CV_LIST_EMPTY,
        .type = TYPE_GUI_CONTROL_LABEL,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 0,
        .fix = 1,
        .child_num = 1,
        .children = &gui_message_list_empty_text,
    },

	{
        .id = APP_MESSAGE_CV_LIST_DELECT,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = MSG_DELETE_ALL_IMG_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_message_delect_img,
    },

	{
        .id = APP_MESSAGE_CV_LIST_DELECT_ONE,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = MSG_DELETE_BTN_IMG_X,
        .y = 0,
        .width = MSG_DELETE_BTN_IMG_W,
        .height = MSG_DELETE_BTN_IMG_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_message_delect_one_img,
    },
};

/// @brief
static const gui_layout_scroll_struct gui_message_list_layout =
{
    .top = GUI_CONTENT_GAP_TOP,
    .bottom = 0,
	.scroll = 1,//是否可以上下滚动
	.dynamic_height = 0,
    .can_swipe = 1,
    .forbid_down_rebound = 0,
};

/// @brief
const gui_screen_struct gui_screen_message_list =
{
	.type = TYPE_GUI_LAYOUT_SCROLL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_message_list_widget,
	.child_num = countof(gui_message_list_widget),
	.layout_config = &gui_message_list_layout,
};






