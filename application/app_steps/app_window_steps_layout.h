#ifndef __APP_WINDOW_STEPS_LAYOUT_H__
#define __APP_WINDOW_STEPS_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	STEPS_LAYOUT_ID_NONE,

	STEPS_LAYOUT_ID_BG,
	STEPS_STEPS_NUM_ID,
	STEPS_KCAL_NUM_ID,

	STEPS_KM_NUM_ID,
	STEPS_HR_NUM_ID,
	
	STEPS_STEPS_TXT_ID,
	STEPS_KCAL_TXT_ID,

	STEPS_KM_TXT_ID,
	STEPS_HR_TXT_ID,


}APP_WINDOW_STEPS_LAYOUT_ID;


extern const gui_screen_struct gui_screen_steps;

#endif

