#ifndef __APPLICATION_TOUCH_GESTURE_SWIPE_H__
#define __APPLICATION_TOUCH_GESTURE_SWIPE_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern void application_touch_gesture_swipe_start(const gui_window_swipe_struct* swipe_window,gui_touch_point_struct* touch_point);
extern void application_touch_gesture_swipe_move(const gui_window_swipe_struct* swipe_window,gui_touch_point_struct* touch_point);
extern void application_touch_gesture_swipe_end(const gui_window_swipe_struct* swipe_window,gui_touch_point_struct* touch_point);
extern void application_touch_gesture_swipe_cancle(void);
extern void application_touch_gesture_swipe_finish(void);
extern unsigned char application_touch_gesture_swipe_is_moving(void);

#endif

