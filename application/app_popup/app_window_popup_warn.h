#ifndef __APP_WINDOW_POPUP_WARN_H__
#define __APP_WINDOW_POPUP_WARN_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef struct
{
    unsigned char no_title;
    unsigned char text_type; // GUI_FONT_VALUE_TYPE

    unsigned int title;
    unsigned int text;

} gui_popup_warn_struct;

extern const gui_window_struct app_window_popup_warn;

#endif
