#ifndef __APP_WINDOW_SETTING_SCREEN_UI_H__
#define __APP_WINDOW_SETTING_SCREEN_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

//亮度的变化比移动时的距离要小很多
#define SETTING_SCREEN_UI_BRIGHTNESS_RATIO (0.35f)

extern void app_window_setting_screen_ui_show_wrist(void);
extern void app_window_setting_screen_ui_show_brightness(void);
extern void app_window_setting_screen_ui_show(void);

extern unsigned char app_window_setting_screen_ui_is_touch_on_wrist_button(short x, short y);
extern unsigned char app_window_setting_screen_ui_is_touch_on_brightness_low(short x, short y);
extern unsigned char app_window_setting_screen_ui_is_touch_on_brightness_high(short x, short y);

#endif

