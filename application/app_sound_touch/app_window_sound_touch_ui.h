#ifndef __APP_WINDOW_SOUND_TOUCH_UI_H__
#define __APP_WINDOW_SOUND_TOUCH_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

extern void app_window_sound_touch_ui_show_wrist(void);
extern void app_window_sound_touch_ui_show_sound(void);
extern void app_window_sound_touch_ui_show(void);

extern unsigned char app_window_sound_touch_ui_is_touch_on_vibration_button(short x, short y);
extern unsigned char app_window_sound_touch_ui_is_touch_on_vibration_check_1(short x, short y);
extern unsigned char app_window_sound_touch_ui_is_touch_on_vibration_check_2(short x, short y);

extern unsigned char app_window_sound_touch_ui_is_touch_on_sound_low(short x, short y);
extern unsigned char app_window_sound_touch_ui_is_touch_on_sound_high(short x, short y);

#endif
