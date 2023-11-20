#ifndef __GUI_SURFACE_BOX_IMAGE_NUMBER_H__
#define __GUI_SURFACE_BOX_IMAGE_NUMBER_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern const picture_info_struct* gui_surface_box_image_number_get_picture(const gui_image_number_struct* image_number,unsigned char str);
extern gui_node_struct* gui_surface_box_image_number_arrange_content(gui_box_struct* box,const gui_image_number_struct* image_number,unsigned char* str);
extern gui_node_struct* gui_surface_box_image_number_arrange_children(gui_box_struct* box,const gui_image_number_struct* image_number);
extern gui_node_struct* gui_surface_box_image_number_arrange(gui_box_struct* box);

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_image_number_create(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_image_number_change_content(gui_box_struct* box,const gui_image_number_struct* image_number,unsigned char* str);
extern void gui_surface_box_image_number_change_string(gui_box_struct* box,unsigned char* str);
extern void gui_surface_box_image_number_change_string_id(gui_box_struct* box,int string_id);
extern void gui_surface_box_image_number_change_number(gui_box_struct* box,int number);

#endif
