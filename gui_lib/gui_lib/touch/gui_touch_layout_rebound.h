#ifndef __GUI_TOUCH_LAYOUT_REBOUND_H__
#define __GUI_TOUCH_LAYOUT_REBOUND_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern void gui_touch_layout_rebound_auto_moving(const gui_window_struct* window,DIRECTION_TYPE direction, short end_offset,int speed);
extern void gui_touch_layout_rebound_cancle(void);
extern unsigned char gui_touch_layout_rebound_is_moving(void);

#endif

