#ifndef __GUI_TOUCH_LAYOUT_FLOWVIEW_H__
#define __GUI_TOUCH_LAYOUT_FLOWVIEW_H__

#include "feature_all.h"
#include "gui_core_all.h"

#include "feature_all.h"
#include "gui_core_all.h"

extern void gui_touch_layout_flowview_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_flowview_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_flowview_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_flowview_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_flowview_touch_cancle(const gui_window_struct* top_window);


#endif
