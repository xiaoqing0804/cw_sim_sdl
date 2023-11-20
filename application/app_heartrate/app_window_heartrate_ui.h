#ifndef __APP_WINDOW_HEARTRATE_UI_H__
#define __APP_WINDOW_HEARTRATE_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum
{
    HEARTRATE_STATUS_START = 0,
    HEARTRATE_STATUS_RESULT,
};

extern void app_window_heartrate_ui_show_ani(void);
extern void app_window_heartrate_ui_show_result(void);
extern void app_window_heartrate_ui_show();

#endif