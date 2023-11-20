#ifndef __GUI_SURFACE_BOX_IMAGE_LIST_H__
#define __GUI_SURFACE_BOX_IMAGE_LIST_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern gui_node_struct* gui_surface_box_image_list_arrange(gui_box_struct* box);

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_image_list_create(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_image_list_change(gui_box_struct* box,unsigned short node_id,const picture_info_struct* picture);


#endif
