#ifndef __GUI_SURFACE_LAYOUT_CARD_H__
#define __GUI_SURFACE_LAYOUT_CARD_H__


#include "feature_all.h"
#include "gui_core.h"


extern void gui_surface_layout_card_arrange(gui_surface_struct* surface);
extern void gui_surface_layout_card_set_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);

extern void gui_surface_layout_card_move(gui_surface_struct* surface, int move);

extern void gui_surface_layout_card_move_end(gui_surface_struct* surface);

extern void gui_surface_layout_card_exit(void);

extern short gui_surface_layout_card_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point);

extern gui_box_struct* gui_surface_layout_card_get_item(gui_surface_struct* surface,short index);

extern unsigned short gui_surface_layout_card_count(gui_surface_struct* surface);

extern void gui_surface_layout_card_set_index(gui_surface_struct* surface, short index);

extern void gui_surface_layout_card_rolkey_handler(gui_surface_struct* surface, short dir); // dir: 1 inc; -1 dec

#endif

