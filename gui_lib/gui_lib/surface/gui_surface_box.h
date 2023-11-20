#ifndef __GUI_SURFACE_BOX_H__
#define __GUI_SURFACE_BOX_H__

#include "feature_all.h"
#include "gui_core.h"

extern void gui_surface_box_parse(gui_box_struct* box);
extern void gui_surface_box_commit(gui_box_struct* box);

extern void gui_surface_box_change_x(gui_box_struct* box,short x);
extern void gui_surface_box_change_y(gui_box_struct* box,short y);
extern void gui_surface_box_change_width(gui_box_struct* box,short width);
extern void gui_surface_box_change_height(gui_box_struct* box,short height);
extern void gui_surface_box_change_visible(gui_box_struct* box,unsigned char visible);
extern gui_box_struct* gui_surface_box_create(gui_surface_struct* surface,const gui_widget_struct* widget);
extern void gui_surface_box_arrange_x(gui_box_struct* box);
extern void gui_surface_box_arrange_y(gui_box_struct* box);
extern void gui_surface_box_change_xy(gui_box_struct* box,short x,short y);
extern void gui_surface_box_exit(gui_box_struct* box);
extern void gui_surface_box_add_node(gui_box_struct* box, gui_node_struct* node);
extern gui_node_struct* gui_surface_box_find_node(gui_box_struct* box,unsigned short id);
extern void gui_surface_box_get_rect_in_screen(gui_surface_struct* surface,gui_box_struct* box,geometry_rect* rect);
extern void gui_surface_box_change_clip(gui_box_struct* box,short clip_x,short clip_y,short clip_width,short clip_height);
extern void gui_surface_box_change_node_clip(gui_box_struct* box,short node_id,short clip_x,short clip_y,short clip_width,short clip_height);


// Taylor.Le, +
extern void gui_surface_box_get_geometry_rect(gui_surface_struct *surface, gui_box_struct* box, geometry_rect* rect);
extern unsigned int gui_surface_box_contain_xy(gui_surface_struct *surface, gui_box_struct* box, short x, short y);

#endif
