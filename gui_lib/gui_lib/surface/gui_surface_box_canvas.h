#ifndef __GUI_SURFACE_BOX_CANVAS_H__
#define __GUI_SURFACE_BOX_CANVAS_H__


#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern gui_node_struct* gui_surface_box_canvas_init(gui_node_struct* node);
extern void gui_surface_box_canvas_create(gui_box_struct* box);

extern void gui_surface_box_canvas_change(gui_box_struct* box, unsigned short node_id, gui_canvas_struct* canvas);

extern void gui_surface_box_canvas_flush(gui_box_struct* box, unsigned short node_id);

#endif

