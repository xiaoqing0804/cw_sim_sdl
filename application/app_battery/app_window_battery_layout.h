#ifndef __APP_WINDOW_BATTERY_LAYOUT_H__
#define __APP_WINDOW_BATTERY_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"
#include "gui_surface_control.h"

typedef enum
{
	BATTERY_LAYOUT_ID_NONE = 100,
	BATTERY_LAYOUT_ID_SCHEDULE,
	BATTERY_LAYOUT_ID_NUM,
	BATTERY_LAYOUT_ID_FORM,
	BATTERY_LAYOUT_ID_LAST,
	BATTERY_LAYOUT_ID_LAST_NUM,
	BATTERY_LAYOUT_ID_TIME,
};

extern const gui_screen_struct gui_screen_battery;

#endif
