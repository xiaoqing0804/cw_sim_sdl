#ifndef __GUI_TOUCH_LAYOUT_GRIDVIEW_H__
#define __GUI_TOUCH_LAYOUT_GRIDVIEW_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern void gui_touch_layout_gridview_check_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern short gui_touch_layout_gridview_check_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point,unsigned char* id);
extern void gui_touch_layout_gridview_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_gridview_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_gridview_up(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_gridview_cancle(const gui_window_struct* top_window);

#endif

