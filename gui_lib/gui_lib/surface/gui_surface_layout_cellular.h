#ifndef __GUI_SURFACE_LAYOUT_CELLULAR_H__
#define __GUI_SURFACE_LAYOUT_CELLULAR_H__

#include "feature_all.h"
#include "gui_core.h"

/*******************************数据接口************************************/

extern short gui_surface_layout_cellular_get_count(gui_surface_struct* surface);
extern short gui_surface_layout_cellular_get_row_num(gui_surface_struct* surface);
extern short gui_surface_layout_cellular_get_item_id(gui_surface_struct* surface,short index);
extern gui_box_struct* gui_surface_layout_cellular_get_item(gui_surface_struct* surface,short index);
extern short gui_surface_layout_cellular_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point);

extern gui_box_struct* gui_surface_layout_cellular_get_center_item(gui_surface_struct* surface);
extern void gui_surface_layout_cellular_move_near_center(gui_surface_struct* surface,gui_box_struct* near_center_box);
extern void gui_surface_layout_cellular_set_near_center_box(gui_surface_struct* surface,gui_box_struct* box);
extern void gui_surface_layout_cellular_exit(void);

#if GUI_LAYOUT_CELL_ZOOM_SUPPORT == 1
extern void gui_surface_layout_cellular_zoom_in(gui_surface_struct* surface); //放大
extern void gui_surface_layout_cellular_zoom_out(gui_surface_struct* surface);//缩小
extern void gui_surface_layout_cellular_clear_zoom_timer(void);
#endif

/*******************************操作接口************************************/

//根据排版类型，进行排版
extern void gui_surface_layout_cellular_arrange(gui_surface_struct* surface);

//对排版中的子元素，使用指定的偏移
extern void gui_surface_layout_cellular_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);

//对排版中的子元素，进行指定的偏移
extern void gui_surface_layout_cellular_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y);

extern void gui_surface_layout_cellular_switch_to_item(gui_surface_struct* surface, DIRECTION_TYPE direction);

//提交位置偏移
extern void gui_surface_layout_cellular_commit_position(gui_surface_struct* surface);

extern void gui_surface_layout_cellular_arrange_zoom_and_position(gui_surface_struct* surface);
extern void gui_surface_layout_cellular_switch_to_cellular(gui_surface_struct* surface, DIRECTION_TYPE direction);

#endif
