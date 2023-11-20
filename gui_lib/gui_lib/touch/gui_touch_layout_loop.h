#ifndef __GUI_TOUCH_LAYOUT_LOOP_H__
#define __GUI_TOUCH_LAYOUT_LOOP_H__

#include "feature_all.h"
#include "gui_core_all.h"

//点击
extern void gui_touch_layout_loop_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);

/*************************移动********************************/

//列表移动 [可以任何方向移动]
extern void gui_touch_layout_loop_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);

//列表移动 [可以任何方向移动]
extern void gui_touch_layout_loop_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);

//列表移动 [可以任何方向移动]
extern void gui_touch_layout_loop_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);

#endif

