#ifndef __APP_WINDOW_LANGUAGE_LAYOUT_H__
#define __APP_WINDOW_LANGUAGE_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"
#include "gui_surface_control.h"

#define APP_LANGUAGE_ITEM_PIC_YES_ID 1
#define APP_LANGUAGE_ITEM_PIC_N0_ID 2

typedef enum
{
	LANGUAGE_ID_YES_BG = 100,
	LANGUAGE_ID_LINE_1,
	LANGUAGE_ID_LINE_2,
	LANGUAGE_ID_LINE_3,
	LANGUAGE_ID_TXT,
} APP_WINDOW_LANGUAGE_ID;

extern const gui_screen_struct gui_screen_language_list;

#endif
