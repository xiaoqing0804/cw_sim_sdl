#ifndef __APP_WINDOW_LIGHT_UI_H__
#define __APP_WINDOW_LIGHT_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

#define BRIGHTNESS_TOTAL_LEVEL (5)
#define BRIGHTNESS_LEVEL_GAP (100 / BRIGHTNESS_TOTAL_LEVEL)

extern void app_window_brightness_ui_update_line(int brightness_level);

#endif
