#ifndef __APP_WINDOW_QUICK_LAYOUT_H__
#define __APP_WINDOW_QUICK_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_date.h"
#include "gui_surface_control_time.h"

typedef enum
{
    QUICK_ID_BG,
	QUICK_ID_NONE,

	QUICK_ID_DATE,
	QUICK_ID_BATTERY,
	QUICK_ID_BATTERY_TEXT,
	QUICK_ID_WEEK,

    QUICK_ID_SYS_ALARM,
    QUICK_ID_SYS_HFP,
    QUICK_ID_SYS_MORE,
    QUICK_ID_SYS_DISTURB,
    QUICK_ID_SYS_BRIGHT,
    QUICK_ID_BLE,
    QUICK_ID_SYS_ALARM_TEXT,
    QUICK_ID_SYS_HFP_TEXT,
    QUICK_ID_SYS_MORE_TEXT,
    QUICK_ID_SYS_DISTURB_TEXT,
    QUICK_ID_SYS_BRIGHT_TEXT,
    QUICK_ID_SYS_BRIGHT_ON_TEXT,


}APP_WINDOW_QUICK_LAYOUT_ID;


extern const gui_screen_struct gui_screen_quick;


#endif

