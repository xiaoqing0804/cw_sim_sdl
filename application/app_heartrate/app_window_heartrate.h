#ifndef __APP_WINDOW_HEARTRATE_H__
#define __APP_WINDOW_HEARTRATE_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

#define HEARTRATE_MEASURE_TICK_TO_START (3)
#define HEARTRATE_MEASURE_TICK_RESULT (15)
#define HEARTRATE_MEASURE_TICK_TIMEOUT (60)

#define HEARTRATE_MEASURE_ANI_INTERVAL (100)

extern unsigned char app_window_heartrate_get_status(void);

extern const gui_window_struct app_window_heartrate;

#endif
