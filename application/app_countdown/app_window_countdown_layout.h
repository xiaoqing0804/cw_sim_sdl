#ifndef __APP_WINDOW_COUNTDOWN_LAYOUT_H__
#define __APP_WINDOW_COUNTDOWN_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	COUNTDOWN_ID_NONE=100,
	COUNTDOWN_ID_1MIN,
	COUNTDOWN_ID_3MIN,
	COUNTDOWN_ID_5MIN,
	COUNTDOWN_ID_10MIN,
	COUNTDOWN_ID_CUSTOM,
	COUNTDOWN_ID_MYMIN,

}APP_WINDOW_COUNTDOWN_LAYOUT_ID;


extern const gui_screen_struct gui_screen_countdown;


#endif

