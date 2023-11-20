#ifndef __GUI_SURFACE_LAYOUT_SCROLL_H__
#define __GUI_SURFACE_LAYOUT_SCROLL_H__

#include "feature_all.h"
#include "gui_core.h"

extern short gui_surface_layout_scrollview_get_item_id(gui_surface_struct* surface,short index);
extern gui_box_struct* gui_surface_layout_scrollview_get_item(gui_surface_struct* surface,short index);
extern short gui_surface_layout_scrollview_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point);

/*******************************操作接口************************************/

//根据排版类型，进行排版
extern void gui_surface_layout_scrollview_arrange(gui_surface_struct* surface);

//对排版中的子元素，使用指定的偏移
extern void gui_surface_layout_scrollview_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);

//对排版中的子元素，进行指定的偏移
extern void gui_surface_layout_scrollview_move(gui_surface_struct* surface,short offset_x,short offset_y);

extern void gui_surface_layout_scrollview_commit_position(gui_surface_struct* surface);
extern void gui_surface_layout_scrollview_switch_to_y(gui_surface_struct* surface, short progress);
extern void gui_surface_layout_scrollview_switch_to_direction(gui_surface_struct* surface, DIRECTION_TYPE direction);


#endif
