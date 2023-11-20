#ifndef __APP_WINDOW_POPUP_YESNO_H__
#define __APP_WINDOW_POPUP_YESNO_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef struct
{
    unsigned char text_type; // GUI_FONT_VALUE_TYPE
    unsigned int text;

    void (*click_on_yes)(void);
    void (*click_on_no)(void);
} gui_popup_yesno_struct;

extern const gui_window_struct app_window_popup_yesno;

#endif
