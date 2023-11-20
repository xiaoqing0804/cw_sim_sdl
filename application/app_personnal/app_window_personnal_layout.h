#ifndef __APP_WINDOW_PERSONNAL_LAYOUT_H__
#define __APP_WINDOW_PERSONNAL_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

enum
{
    PERSONNAL_LAYOUT_ID_NONE,
    PERSONNAL_LAYOUT_ID_HEAD,
    PERSONNAL_LAYOUT_ID_HEIGHT,
    PERSONNAL_LAYOUT_ID_WEIGHT,
    PERSONNAL_LAYOUT_ID_BMI,

    PERSONNAL_LAYOUT_ID_HEIGHT_TEXT,
    PERSONNAL_LAYOUT_ID_WEIGHT_TEXT,
    PERSONNAL_LAYOUT_ID_BMI_TEXT,
};

extern const gui_screen_struct gui_screen_personnal;

#endif
