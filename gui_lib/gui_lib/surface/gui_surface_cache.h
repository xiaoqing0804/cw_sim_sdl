#ifndef __GUI_SURFACE_CACHE_H__
#define __GUI_SURFACE_CACHE_H__

#include "feature_all.h"
#include "gui_core.h"

extern gui_box_struct* gui_surface_cache_add_box(void);
extern void gui_surface_cache_remove_box(gui_box_struct* box);
extern void gui_surface_cache_remove_box_and_children(gui_box_struct* box);
extern void gui_surface_cache_clear_box(void);

extern gui_node_struct* gui_surface_cache_add_node(void);
extern void gui_surface_cache_remove_node_from_list(gui_box_struct* box, gui_node_struct* node);
extern void gui_surface_cache_remove_node(gui_node_struct* node);
extern void gui_surface_cache_remove_nodes(gui_node_struct* node);
extern void gui_surface_cache_clear_node(void);
extern gui_node_struct* gui_surface_cache_find_front(gui_node_struct* root_node,gui_node_struct* node);
extern gui_node_struct* gui_surface_cache_find_front_in_child(gui_node_struct* root_node,gui_node_struct* node);


extern void gui_surface_cache_remove_surface(gui_surface_struct* surface);
extern short gui_surface_cache_count_box(void);	
extern short gui_surface_cache_count_node(void);	


#endif
