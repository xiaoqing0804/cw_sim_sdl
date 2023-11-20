#ifndef __GUI_SURFACE_LAYOUT_RING_CENTER_H__
#define __GUI_SURFACE_LAYOUT_RING_CENTER_H__

#include "feature_all.h"
#include "gui_core.h"

#if 0   // 废弃
/*******************************数据接口************************************/

extern short gui_surface_layout_ring_center_get_curr_angle(gui_surface_struct* surface,short index);
extern short gui_surface_layout_ring_center_get_offset_angle(gui_surface_struct* surface);
extern short gui_surface_layout_ring_center_adjust_angle(short angle);
extern int gui_touch_layout_ring_center_adjust_right_angle(int speed_offset_angle);
extern short gui_surface_layout_ring_center_get_default_angle(gui_surface_struct* surface,short index);

extern short gui_surface_layout_ring_center_get_item_id(gui_surface_struct* surface,short index);
extern gui_box_struct* gui_surface_layout_ring_center_get_item(gui_surface_struct* surface,short index);
extern short gui_surface_layout_ring_center_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point);

/*******************************操作接口************************************/

//根据排版类型，进行排版
extern void gui_surface_layout_ring_center_arrange(gui_surface_struct* surface);

extern void gui_surface_layout_ring_center_init(gui_surface_struct* surface);

extern void gui_surface_layout_ring_center_check_switch_item(gui_surface_struct* surface);
extern void gui_surface_layout_ring_center_show_item(gui_surface_struct* surface,short item_index);
extern void gui_surface_layout_ring_center_show_curr_item(gui_surface_struct* surface);


extern void gui_surface_layout_ring_center_switch_to_item(gui_surface_struct* surface,short curr_index,short item_index);

//对排版中的子元素，使用指定的偏移
extern void gui_surface_layout_ring_center_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);

//对排版中的子元素，进行指定的偏移
extern void gui_surface_layout_ring_center_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y);
extern void gui_surface_layout_ring_center_move_end(gui_surface_struct* surface);

extern void gui_surface_layout_ring_center_exit(void);


//提交位置偏移
extern void gui_surface_layout_ring_center_commit_position(gui_surface_struct* surface);

#endif
#endif

