#ifndef __APP_WINDOW_AOD_DIAL_LAYOUT_H__
#define __APP_WINDOW_AOD_DIAL_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

enum
{
    AOD_DIAL_LAYOUT_ID_NONE,

    // box
    AOD_DIAL_LAYOUT_ID_OPEN,
    AOD_DIAL_LAYOUT_ID_NUMBER,
    AOD_DIAL_LAYOUT_ID_POINTER,

    // node
    AOD_DIAL_LAYOUT_ID_OPEN_STATUS,
    AOD_DIAL_LAYOUT_ID_CHECKED,
    AOD_DIAL_LAYOUT_ID_TITLE,
    AOD_DIAL_LAYOUT_ID_TITLE_GRAY,
};

extern const gui_screen_struct gui_screen_aod_dial;

#endif
