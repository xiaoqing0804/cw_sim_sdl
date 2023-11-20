#ifndef __APP_WINDOW_LIGHT_LAYOUT_H__
#define __APP_WINDOW_LIGHT_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	LIGHT_LAYOUT_ID_NONE,
	LIGHT_LAYOUT_ID_TITLE,
	LIGHT_LAYOUT_ID_LINE_0,
	LIGHT_LAYOUT_ID_LINE_2,
	LIGHT_LAYOUT_ID_LINE_1,
	LIGHT_LAYOUT_ID_PIC,
	LIGHT_LAYOUT_ID_PIC_TEXT,
	LIGHT_LAYOUT_BG_ID,
};

extern const gui_screen_struct gui_screen_light;

#endif
