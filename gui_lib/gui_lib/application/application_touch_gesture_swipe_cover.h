#ifndef __APPLICATION_TOUCH_GESTURE_SWIPE_COVER_H__
#define __APPLICATION_TOUCH_GESTURE_SWIPE_COVER_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern unsigned char application_touch_gesture_swipe_cover_check(gui_window_swiping_struct *swiping);
extern unsigned char application_touch_gesture_swipe_cover_check_move(gui_window_swiping_struct *swiping, gui_touch_gesture_tween_struct *tween);
extern unsigned char application_touch_gesture_swipe_cover_check_end(gui_window_swiping_struct *swiping, gui_touch_gesture_tween_struct *tween);
extern unsigned char application_touch_gesture_swipe_cover_move(gui_window_swiping_struct *swiping, short offset_x, short offset_y);
extern unsigned char application_touch_gesture_swipe_cover_end(gui_window_swiping_struct *swiping, gui_touch_gesture_tween_struct *tween, short speed_x, short speed_y);

#endif
