#ifndef __APP_WINDOW_NO_WEAR_LAYOUT_H__
#define __APP_WINDOW_NO_WEAR_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum
{
    NO_WEAR_LAYOUT_ID_NONE = 100,

    NO_WEAR_LAYOUT_TITLE_ID,
    NO_WEAR_LAYOUT_BG_ID,
    NO_WEAR_LAYOUT_ROUND_ID,
    NO_WEAR_LAYOUT_ARROW_ID,
    NO_WEAR_LAYOUT_RETRY_ID,
};

extern const gui_screen_struct app_no_wear_screen;

#endif
