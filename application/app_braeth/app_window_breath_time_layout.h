#ifndef __APP_WINDOW_BREATH_TIME_LAYOUT_H__
#define __APP_WINDOW_BREATH_TIME_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	BREATH_TIME_LAYOUT_ID_NONE,

	BREATH_TIME_LAYOUT_ID_MIN_TITLE,
	BREATH_TIME_LAYOUT_ID_1MIN,
	BREATH_TIME_LAYOUT_ID_2MIN,
	BREATH_TIME_LAYOUT_ID_3MIN,

	BREATH_TIME_LAYOUT_ID_OK,
};

extern const gui_screen_struct gui_screen_breath_time;

#endif
