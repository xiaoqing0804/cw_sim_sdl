#ifndef __APP_WINDOW_CALL_OUTGOING_LAYOUT_H__
#define __APP_WINDOW_CALL_OUTGOING_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"
#include "gui_surface_control_base.h"


enum
{
    CALL_OUTGOING_HUNGUP_ID = 100,
    CALL_OUTGOING_VOL_ID,
    CALL_OUTGOING_TEXT_ID,
    CALL_OUTGOING_TIME_ID,
    CALL_OUTGOING_CURRENT_TIME_ID,

    CALL_LAYOUT_VOLUP_ID,
    CALL_LAYOUT_VOLDN_ID,
    CALL_LAYOUT_VOLBG_ID ,
    CALL_LAYOUT_VOLIND_ID,

    CALL_OUTGOING_MIC_ID,
    CALL_OUTGOING_PHONE_ID,

};


extern const gui_screen_struct app_call_outgoing_screen;

#endif

