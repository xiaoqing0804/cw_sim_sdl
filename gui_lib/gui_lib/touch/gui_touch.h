#ifndef __GUI_TOUCH_H__
#define __GUI_TOUCH_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern unsigned char gui_touch_longpress(gui_touch_point_struct* touch_point);
extern unsigned char gui_touch_down(gui_touch_point_struct* touch_point);
extern unsigned char gui_touch_move(gui_touch_point_struct* touch_point);
extern void gui_touch_up(gui_touch_point_struct* touch_point,unsigned char click);
extern unsigned char gui_touch_is_moving(void);
extern unsigned char gui_touch_is_free_direction(void);
extern void gui_touch_cancle(void);
extern void gui_touch_rebound_cancle(void);


#endif

