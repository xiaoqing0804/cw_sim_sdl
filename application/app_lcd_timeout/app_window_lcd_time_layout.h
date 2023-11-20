#ifndef __APP_WINDOW_LCD_TIME_LAYOUT_H__
#define __APP_WINDOW_LCD_TIME_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"
#include "gui_surface_control.h"

#define LCD_TIME_LINE_Y       35
#define LCD_TIME_LINE_H       48
#define LCD_TIME_FONT_W       18

typedef enum
{
	LCD_TIME_ID_NONE,
	LCD_TIME_ID_TITLE,
	LCD_TIME_ID_LINE_0,
	LCD_TIME_ID_LINE_1,
	LCD_TIME_ID_LINE_2,
	LCD_TIME_ID_BG,
	LCD_TIME_ID_PIC,
	LCD_TIME_ID_PIC_TXT,
};

extern const gui_screen_struct gui_screen_lcd_time;

#endif

