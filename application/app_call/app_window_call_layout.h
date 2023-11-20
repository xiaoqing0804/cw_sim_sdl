#ifndef __APP_CALL_LAYOUT_H__
#define __APP_CALL_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

#define GUI_CALL_CLOG_ITEM_H    100
enum
{
	CALL_REPLY = 100,
	CALL_HANGUP,
    CALL_INFO,
	CALL_TEXT_INFO,
};


extern const gui_screen_struct app_call_screen;

#endif

