#ifndef __APP_WINDOW_HEARTRATE_LAYOUT_H__
#define __APP_WINDOW_HEARTRATE_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum
{
    HR_BOX_START_ID = 100,

    HR_BOX_BG_IMAGE_ID,

    // curr
    HR_BOX_CURR_ICON_ID,
    HR_BOX_CURR_TITLE_ID,
    HR_BOX_CURR_VALUE_ID,
    HR_BOX_CURR_HISTORY_ID,
    HR_BOX_CURR_LINE_ID,
    HR_BOX_CURR_BPM_ID,

    // resting
    HR_BOX_RESTING_ICON_ID,
    HR_BOX_RESTING_TITLE_ID,
    HR_BOX_RESTING_VALUE_ID,
    HR_BOX_RESTING_HISTORY_ID,
    HR_BOX_RESTING_LINE_ID,
    HR_BOX_RESTING_BPM_ID,

    // walk
    HR_BOX_WALK_ICON_ID,
    HR_BOX_WALK_TITLE_ID,
    HR_BOX_WALK_VALUE_ID,
    HR_BOX_WALK_HISTORY_ID,
    HR_BOX_WALK_BPM_ID,
};

extern const gui_screen_struct app_heartrate_screen;

#endif
