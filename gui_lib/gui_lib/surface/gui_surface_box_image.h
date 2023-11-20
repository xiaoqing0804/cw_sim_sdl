#ifndef __GUI_SURFACE_BOX_IMAGE_H__
#define __GUI_SURFACE_BOX_IMAGE_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern gui_node_struct* gui_surface_box_image_arrange_content(gui_box_struct* box,const gui_image_struct* image,const picture_info_struct* picture);
extern gui_node_struct* gui_surface_box_image_arrange_children(gui_box_struct* box,const gui_image_struct* image);
extern gui_node_struct* gui_surface_box_image_arrange(gui_box_struct* box);

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_image_create(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_image_change(gui_box_struct* box,const picture_info_struct* picture);
extern void gui_surface_box_image_arrange_refresh(gui_box_struct* box);

#endif
