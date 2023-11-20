#ifndef __GUI_SURFACE_NODE_H__
#define __GUI_SURFACE_NODE_H__

#include "feature_all.h"
#include "gui_core.h"

extern gui_node_struct* gui_surface_node_find_by_id(gui_box_struct* box,unsigned short id);
extern gui_node_struct* gui_surface_node_find_child(gui_node_struct* node,unsigned short id);
extern gui_node_struct* gui_surface_node_check_clip(gui_box_struct* box, gui_node_struct* node,short width,short height);
extern gui_node_struct* gui_surface_node_compose_check_clip(gui_box_struct* box, gui_node_struct* node,gui_node_struct* compose, short width,short height);
extern short gui_surface_node_check_x(gui_box_struct* box,unsigned char align,short x,short width);
extern short gui_surface_node_check_y(gui_box_struct* box,unsigned char align,short y,short height);
extern void gui_surface_node_replace_brother(gui_box_struct* box,gui_node_struct* old_node,gui_node_struct* new_node);
extern void gui_surface_node_replace_child(gui_box_struct* box,gui_node_struct* old_node,gui_node_struct* new_node);
extern void gui_surface_node_get_rect_in_screen(gui_surface_struct* surface,gui_box_struct* box,gui_node_struct* node,geometry_rect* rect);
extern void gui_surface_node_compose_get_rect_in_screen(gui_surface_struct* surface,gui_box_struct* box,gui_node_struct* node,gui_node_struct* compose_node,geometry_rect* rect);

extern void gui_surface_node_get_rect_in_screen_with_scale(gui_scale_struct* gui_scale, geometry_rect* rect);
extern void gui_surface_node_compose_get_rect_in_screen_with_scale(gui_scale_struct* gui_scale, geometry_rect* rect);
extern unsigned char gui_surface_node_check_rect_in_surface(gui_scale_struct* gui_scale, geometry_rect* rect);

#endif
