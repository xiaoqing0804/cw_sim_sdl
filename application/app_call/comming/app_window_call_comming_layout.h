#ifndef __APP_WINDOW_CALL_COMMING_LAYOUT_H__
#define __APP_WINDOW_CALL_COMMING_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"
#include "gui_surface_control_base.h"


enum
{
	CALL_ING_REPLY = 100,
	CALL_ING_REJECT,
	CALL_ING_ACCEPT,
	CALL_ING_INFO,
    CALL_ING_TIME,
    CALL_ING_NEW_CALL,
};


extern const gui_screen_struct app_call_comming_screen;


#endif

