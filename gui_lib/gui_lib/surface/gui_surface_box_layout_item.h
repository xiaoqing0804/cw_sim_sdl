#ifndef __GUI_SURFACE_BOX_LAYOUT_ITEM_H__
#define __GUI_SURFACE_BOX_LAYOUT_ITEM_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern const gui_draw_struct* gui_surface_box_layout_item_find_by_id(gui_box_struct* box,unsigned short id);

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_layout_item_create(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_layout_item_change_visible(gui_box_struct* box,unsigned char node_id,unsigned char visible);
extern void gui_surface_box_layout_item_change_image(gui_box_struct* box,unsigned char node_id,picture_info_struct* picture);
extern void gui_surface_box_layout_item_change_string(gui_box_struct* box,unsigned char node_id, unsigned char* str);
extern void gui_surface_box_layout_item_change_string_id(gui_box_struct* box,unsigned char node_id,int string_id);
extern void gui_surface_box_layout_item_change_number(gui_box_struct* box,unsigned char node_id,int number);

#endif
