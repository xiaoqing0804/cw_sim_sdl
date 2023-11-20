#ifndef __GUI_SURFACE_LAYOUT_LOOP_H__
#define __GUI_SURFACE_LAYOUT_LOOP_H__

#include "feature_all.h"
#include "gui_core.h"

/*******************************数据接口************************************/

extern short gui_surface_layout_loop_get_item_id(gui_surface_struct* surface,short index);
extern gui_box_struct* gui_surface_layout_loop_get_item(gui_surface_struct* surface,short index);
extern short gui_surface_layout_loop_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point);


/*******************************操作接口************************************/

//根据排版类型，进行排版
extern void gui_surface_layout_loop_arrange(gui_surface_struct* surface);

//对排版中的子元素，使用指定的偏移
extern void gui_surface_layout_loop_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);

//对排版中的子元素，进行指定的偏移
extern void gui_surface_layout_loop_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y);

extern void gui_surface_layout_loop_exit(void);

extern void gui_surface_layout_loop_switch_to_item(gui_surface_struct* surface, DIRECTION_TYPE direction);


#endif
