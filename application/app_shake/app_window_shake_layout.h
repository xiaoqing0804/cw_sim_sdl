#ifndef __APP_WINDOW_SHAKE_LAYOUT_H__
#define __APP_WINDOW_SHAKE_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	SHAKE_LAYOUT_ID_NONE,
	SHAKE_LAYOUT_ID_PIC,
	SHAKE_LAYOUT_ID_TITLE,
	SHAKE_LAYOUT_ID_TIME,
	SHAKE_LAYOUT_ID_WATCHFACE,
	SHAKE_LAYOUT_ID_MENU,

}APP_WINDOW_SHAKE_LAYOUT_ID;


extern const gui_screen_struct gui_screen_shake;


#endif

