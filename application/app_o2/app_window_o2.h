#ifndef __APP_WINDOW_O2_H__
#define __APP_WINDOW_O2_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

#define O2_MEASURE_TICK_TOTAL (15)
#define O2_MEASURE_TICK_TO_START (13)

typedef enum
{
    O2_STATUS_START = 0,
    O2_STATUS_RESULT,
};

extern const gui_window_struct app_window_o2;

#endif
