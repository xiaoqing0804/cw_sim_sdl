#ifndef __GUI_SURFACE_LAYOUT_PAGEVIEW_H__
#define __GUI_SURFACE_LAYOUT_PAGEVIEW_H__

#include "feature_all.h"
#include "gui_core.h"

#include "gui_surface_layout_pageview.h" 

/*********************************数据获取***************************************/

extern short gui_surface_layout_pageview_get_count(gui_surface_struct* surface);
extern gui_box_struct* gui_surface_layout_pageview_get_page(gui_surface_struct* surface,short curr_page);
extern short gui_surface_layout_pageview_get_item_id(gui_surface_struct* surface,gui_touch_point_struct* touch_point);

/*******************************排版***************************************************/

extern void gui_surface_layout_pageview_arrange(gui_surface_struct* surface);
extern void gui_surface_layout_pageview_check_switch_page(gui_surface_struct* surface);
extern void gui_surface_layout_pageview_switch_page_by_step(gui_surface_struct* surface,short step);
extern void gui_surface_layout_pageview_switch_page(gui_surface_struct* surface,short page);
extern void gui_surface_layout_pageview_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);
extern void gui_surface_layout_pageview_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y);
extern void gui_surface_layout_pageview_commit_position(gui_surface_struct* surface);

#endif
