#ifndef __APP_WND_MSG_INFO_LAYOUT_H__
#define __APP_WND_MSG_INFO_LAYOUT_H__
#include "feature.h"

#if (LCD_SIZE_WIDTH == 466)
#define MSG_BG_IMG_W       (392)
#define MSG_BASE_X         ((LCD_SIZE_WIDTH - MSG_BG_IMG_W)/2)
#define MSG_ICON_Y_POS      GUI_CONTENT_GAP_TOP
#define MSG_BG_Y_POS        (GUI_CONTENT_GAP_TOP+22)
#define MSG_BG_TOP_H        (39)        // message_info_bg_top.png
#define MSG_BG_MID_H        (50)
#define MSG_BG_BOT_H        (39)        //  message_info_bg_bot.png
#define MSG_OP_BAR_H        (88)       // (70)

#define MSG_TIME_Y_POS      (MSG_BG_Y_POS+5)
#define MSG_BODY_Y_POS      (MSG_BG_Y_POS+65)

#else

#define MSG_BG_IMG_W       (300)
#define MSG_BASE_X         ((LCD_SIZE_WIDTH - MSG_BG_IMG_W)/2)
#define MSG_ICON_Y_POS      GUI_CONTENT_GAP_TOP
#define MSG_BG_Y_POS        (GUI_CONTENT_GAP_TOP+22)
#define MSG_BG_TOP_H        (30)        // message_info_bg_top.png
#define MSG_BG_MID_H        (50)
#define MSG_BG_BOT_H        (30)        //  message_info_bg_bot.png
#define MSG_OP_BAR_H        (70)

#define MSG_TIME_Y_POS      (MSG_BG_Y_POS+5)
#define MSG_BODY_Y_POS      (MSG_BG_Y_POS+50)

#endif



enum
{
    APP_MESSAGE_INFO_BG_TOP = 10,
    APP_MESSAGE_INFO_BG_MID,
    APP_MESSAGE_INFO_BG_BOT,
    APP_MESSAGE_INFO_ICON,
    APP_MESSAGE_INFO_TIME,
    APP_MESSAGE_INFO_TITLE,
    APP_MESSAGE_INFO_GOBACK,
};

extern const gui_font_struct gui_message_info_body_text;
extern const gui_font_struct gui_message_info_title_text;
extern gui_canvas_struct gui_message_info_bg_mid_rect;

extern const gui_screen_struct gui_message_info_screen;


#endif
