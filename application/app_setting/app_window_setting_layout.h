#ifndef __APP_WINDOW_SETTING_LAYOUT_H__
#define __APP_WINDOW_SETTING_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

enum
{
    SETTING_LAYOUT_ID_NONE,

    SETTING_LAYOUT_ID_PERSONNAL,
    SETTING_LAYOUT_ID_PERSONNAL_ICON,

    //------------里面的顺序是坐标顺序----------------------
    SETTING_LAYOUT_ID_NOTICE,
    SETTING_LAYOUT_ID_SETTING,
    SETTING_LAYOUT_ID_DISTURB,
    SETTING_LAYOUT_ID_SCREEN,
    SETTING_LAYOUT_ID_APP_VIEW,
    #if !GUI_SINGLE_KEY_SUPPORT
    SETTING_LAYOUT_ID_KEY_SETTING,
    #endif
    SETTING_LAYOUT_ID_SOUND_AND_TOUCH,
    SETTING_LAYOUT_ID_PASSWORD,
    SETTING_LAYOUT_ID_SOS,
    SETTING_LAYOUT_ID_BATTRY,
    SETTING_LAYOUT_ID_SLEEP,
    SETTING_LAYOUT_ID_SPORT,
    //-----------------------------------

};

extern const gui_screen_struct gui_screen_setting;

#endif
