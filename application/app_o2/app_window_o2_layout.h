#ifndef __APP_WINDOW_O2_LAYOUT_H__
#define __APP_WINDOW_O2_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum
{
    O2_LAYOUT_ID_NONE = 0,

    /**************************测量********************************/
    O2_LAYOUT_ID_START_BG,
    O2_LAYOUT_ID_START_TIME,

    /**************************测量结果********************************/
    O2_LAYOUT_ID_RESULT_BG_1,
    O2_LAYOUT_ID_RESULT_BG_2,
    O2_LAYOUT_ID_RESULT_DATA,
    O2_LAYOUT_ID_RESULT_RETRY,
};

extern const gui_screen_struct app_o2_screen;

#endif
