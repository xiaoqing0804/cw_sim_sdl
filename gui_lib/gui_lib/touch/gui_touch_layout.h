#ifndef __GUI_TOUCH_LAYOUT_H__
#define __GUI_TOUCH_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern void gui_touch_layout_check_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern TOUCH_TYPE gui_touch_layout_check_down_type(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern TOUCH_TYPE gui_touch_layout_check_move_type(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern TOUCH_TYPE gui_touch_layout_check_only_move_updown(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern TOUCH_TYPE gui_touch_layout_check_only_move_leftright(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern TOUCH_TYPE gui_touch_layout_check_move_all(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);

extern void gui_touch_layout_check_click(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_check_up(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern void gui_touch_layout_check_free(const gui_window_struct* top_window,gui_touch_point_struct* touch_point);
extern unsigned char gui_touch_layout_is_free_direction(const gui_window_struct* top_window);
extern void gui_touch_layout_check_cancle(const gui_window_struct* top_window,unsigned char touch_type);

#endif

