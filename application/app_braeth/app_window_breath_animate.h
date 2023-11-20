#ifndef __APP_WINDOW_BREATH_ANIMATE_H__
#define __APP_WINDOW_BREATH_ANIMATE_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

extern void app_window_breath_animate_step(float step);
extern void app_window_breath_animate_timer(void *buf);
extern void app_window_breath_animate_init(const gui_screen_struct *screen, unsigned short id);
extern void app_window_breath_animate_auto_start(void);
extern void app_window_breath_animate_auto_stop(void);
extern unsigned char app_window_breath_animate_is_back(void);

#endif
