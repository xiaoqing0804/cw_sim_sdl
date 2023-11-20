#ifndef __APP_WINDOW_CHARGER_SET_LAYOUT_H__
#define __APP_WINDOW_CHARGER_SET_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	CHARGER_SET_ID_NONE,
	CHARGER_SET_ID_PIC,
	CHARGER_SET_ID_TITLE,
	CHARGER_SET_ID_TIME,
	CHARGER_SET_ID_MODE,
	CHARGER_SET_ID_MODE_ADD,
	CHARGER_SET_ID_MODE_DELECT,
	CHARGER_SET_ID_MODE_PROGRESS,

}APP_WINDOW_CHARGER_SET_ID;


extern const gui_screen_struct gui_screen_charger_set;


#endif

