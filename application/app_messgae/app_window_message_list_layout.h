#ifndef __APP_WND_MSG_LIST_LAYOUT_H__
#define __APP_WND_MSG_LIST_LAYOUT_H__
#include "feature.h"

#if (LCD_SIZE_WIDTH == 466)
// 消息背景图片的宽度
#define MSG_ITEM_BG_IMG_W       (392)
// 
#define MSG_ITEM_BASE_X         ((LCD_SIZE_WIDTH - MSG_ITEM_BG_IMG_W)/2)
#define MSG_TEXT_GAP            (5) // 字符行间距

// 每条消息显示间距
#define MSG_ITEM_GAP            10


// 右测删除按钮的 宽度
#define MSG_DELETE_BTN_IMG_W        88
// 右测删除按钮的 高度
#define MSG_DELETE_BTN_IMG_H        214
// 右测删除按钮的 x 坐标
#define MSG_DELETE_BTN_IMG_X        (MSG_ITEM_BASE_X + MSG_ITEM_BG_IMG_W - MSG_DELETE_BTN_IMG_W)


// 底部删除所有信息的图片高度
#define MSG_DELETE_ALL_IMG_H    88

#else

#define MSG_ITEM_BG_IMG_W       (300)// 消息背景图片的宽度
#define MSG_ITEM_BASE_X         ((LCD_SIZE_WIDTH - MSG_ITEM_BG_IMG_W)/2)
#define MSG_TEXT_GAP            (5) // 字符行间距
#define MSG_ITEM_GAP            10// 每条消息显示间距

#define MSG_DELETE_BTN_IMG_W        68// 右测删除按钮的 宽度
#define MSG_DELETE_BTN_IMG_H        180// 右测删除按钮的 高度
#define MSG_DELETE_BTN_IMG_X        (MSG_ITEM_BASE_X + MSG_ITEM_BG_IMG_W - MSG_DELETE_BTN_IMG_W)// 右测删除按钮的 x 坐标

#define MSG_DELETE_ALL_IMG_H    70// 底部删除所有信息的图片高度

#endif



// layout sub-items id
#define APP_MESSAGE_ITEM_CV_BG_ID      1
#define APP_MESSAGE_ITEM_CV_ICON_ID    2
#define APP_MESSAGE_ITEM_CV_TIME_ID    3
#define APP_MESSAGE_ITEM_CV_SUBJECT_ID 4

extern const gui_image_struct  gui_message_item_bg_img;
extern const gui_font_struct   gui_message_item_title_txt;
extern const gui_font_struct   gui_message_item_subject_txt;
extern const gui_widget_struct gui_message_item_widget;


// box - id
#define APP_MESSAGE_CV_LIST_EMPTY       1       // 
#define APP_MESSAGE_CV_LIST_DELECT      2
#define APP_MESSAGE_CV_LIST_DELECT_ONE  3
#define MSG_ITEM_BOX_BASE_ID            10

extern const gui_screen_struct gui_screen_message_list;


#endif
