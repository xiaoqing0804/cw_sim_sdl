#ifndef __GUI_SURFACE_LAYOUT_RING_H__
#define __GUI_SURFACE_LAYOUT_RING_H__

#include "feature_all.h"
#include "gui_core.h"

/*******************************数据接口************************************/



/*******************************操作接口************************************/
//根据排版类型，进行排版
extern void gui_surface_layout_ring_arrange(gui_surface_struct* surface);

extern void gui_surface_layout_ring_switch_to_item(gui_surface_struct* surface, short skip_item);

//对排版中的子元素，使用指定的偏移
extern void gui_surface_layout_ring_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);

//对排版中的子元素，进行指定的偏移
extern void gui_surface_layout_ring_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y, float angle);
extern void gui_surface_layout_ring_move_end(gui_surface_struct* surface);


extern short gui_surface_layout_ring_get_item_index(gui_surface_struct* surface, gui_touch_point_struct* touch_point);

extern gui_box_struct* gui_surface_layout_ring_get_current_item(gui_surface_struct* surface);

#endif
