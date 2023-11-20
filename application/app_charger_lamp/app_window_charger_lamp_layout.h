#ifndef __APP_WINDOW_CHARGER_LAMP_LAYOUT_H__
#define __APP_WINDOW_CHARGER_LAMP_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	CHARGER_LAMP_ID_NONE,
	
	CHARGER_LAMP_ID_BAT,
	CHARGER_LAMP_ID_BAT_RIGHT,	
	
	CHARGER_LAMP_ID_TIME_1,
	CHARGER_LAMP_ID_TIME_2,
	CHARGER_LAMP_ID_TIME_DOT,
	CHARGER_LAMP_ID_TIME_3,
	CHARGER_LAMP_ID_TIME_4,

	CHARGER_LAMP_ID_DATE_1,
	CHARGER_LAMP_ID_DATE_2,
	CHARGER_LAMP_ID_DATE_DOT,
	CHARGER_LAMP_ID_DATE_3,
	CHARGER_LAMP_ID_DATE_4,
	
	CHARGER_LAMP_ID_WEEK,

}APP_WINDOW_CHARGER_LAMP_LAYOUT_ID;


extern const gui_screen_struct gui_screen_charger_lamp;


#endif

