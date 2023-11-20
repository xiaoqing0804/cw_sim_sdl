#ifndef __GUI_SURFACE_BOX_IMAGE_PROGRESS_H__
#define __GUI_SURFACE_BOX_IMAGE_PROGRESS_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern gui_node_struct* gui_surface_box_image_progress_arrange_children(gui_box_struct* box,unsigned char progress);
extern gui_node_struct* gui_surface_box_image_progress_arrange(gui_box_struct* box);

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_image_progress_create(gui_box_struct* box);
extern unsigned char gui_surface_box_image_progress_get_value(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_image_progress_change(gui_box_struct* box,unsigned char progress);

#endif
