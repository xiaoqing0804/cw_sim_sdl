#ifndef __APP_WINDOW_COUNTDOWN_MY_TIME_LAYOUT_H__
#define __APP_WINDOW_COUNTDOWN_MY_TIME_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	COUNTDOWN_MY_TIME_ID_NONE,
	COUNTDOWN_MY_TIME_ID_HOUR_UP,
	COUNTDOWN_MY_TIME_ID_HOUR,
	COUNTDOWN_MY_TIME_ID_HOUR_DOWN,
	COUNTDOWN_MY_TIME_ID_MIN_UP,
	COUNTDOWN_MY_TIME_ID_MIN,
	COUNTDOWN_MY_TIME_ID_MIN_DOWN,
	COUNTDOWN_MY_TIME_ID_SECOND_UP,
	COUNTDOWN_MY_TIME_ID_SECOND,
	COUNTDOWN_MY_TIME_ID_SECOND_DOWN,
	COUNTDOWN_MY_TIME_ID_STATR,
	
	MY_COUNT_LAYOUT_ID_PUBLIC_TXT,
	MY_COUNT_LAYOUT_ID_PUBLIC_TIME,
}APP_WINDOW_COUNTDOWN_MY_TIME_LAYOUT_ID;


#define COUNTDOWN_OPBAR_H   52
#define COUNTDOWN_ITEM_H    35

extern const gui_screen_struct gui_screen_countdown_my_time;


#endif

