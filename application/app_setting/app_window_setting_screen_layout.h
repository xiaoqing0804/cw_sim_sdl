#ifndef __APP_WINDOW_SETTING_SCREEN_LAYOUT_H__
#define __APP_WINDOW_SETTING_SCREEN_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum
{
	APP_SETTING_SCREEN_LAYOUT_ID_NONE = 100,
	APP_SETTING_SCREEN_LAYOUT_ID_OPEN,
	APP_SETTING_SCREEN_LAYOUT_ID_BRIGHTNESS,
};

extern const gui_screen_struct gui_screen_setting_screen;

#endif
