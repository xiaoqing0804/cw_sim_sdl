#ifndef __APP_WINDOW_WOMAN_ALARM_LAYOUT_H__
#define __APP_WINDOW_WOMAN_ALARM_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

#define ICON_Y (LCD_SIZE_HEIGHT / 56)
#define NAME_Y (LCD_SIZE_HEIGHT / 6)
#define VALUE_Y (LCD_SIZE_HEIGHT / 4)
#define ICON_L_Y (LCD_SIZE_HEIGHT / 3)

enum
{
    WOMAN_ALARM_LAYOUT_ID_NONE,
    WOMAN_ALARM_LAYOUT_ID_BG,
    WOMAN_ALARM_LAYOUT_ID_PIC,
    WOMAN_ALARM_LAYOUT_ID_TIME,
    WOMAN_ALARM_LAYOUT_ID_TEXT,
};

extern const gui_screen_struct gui_screen_woman_alarm;

#endif
