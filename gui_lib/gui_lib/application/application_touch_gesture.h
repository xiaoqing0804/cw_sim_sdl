#ifndef __APPLICATION_TOUCH_GESTURE_H__
#define __APPLICATION_TOUCH_GESTURE_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern void application_touch_gesture_deinit();
extern void application_touch_gesture_init(void);
extern void application_touch_gesture_start(gui_touch_point_struct* touch_point);
extern void application_touch_gesture_active(gui_touch_point_struct* touch_point);
extern void application_touch_gesture_keep(gui_touch_point_struct* touch_point);
extern void application_touch_gesture_end(gui_touch_point_struct* touch_point);
extern void application_touch_gesture_cancle(void);
extern void application_touch_gesture_finish(void);
extern void application_touch_gesture_go_back(void);

extern unsigned char application_touch_gesture_is_none(void);
extern unsigned char application_touch_gesture_is_moving(void);

#endif

