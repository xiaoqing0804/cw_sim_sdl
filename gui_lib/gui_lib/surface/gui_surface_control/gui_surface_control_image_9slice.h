
#ifndef __GUI_SURFACE_CONTROL_IMAGE_9SLICE_H__
#define __GUI_SURFACE_CONTROL_IMAGE_9SLICE_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"
#include "gui_surface_control_base.h"
#include "gui_event_core_list.h"

extern void gui_surface_box_image_9slice_create(gui_box_struct* box);

extern gui_node_struct* gui_surface_box_9slice_arrange_children(gui_box_struct* box, gui_image_9slice_struct* img_9slice);

#endif

