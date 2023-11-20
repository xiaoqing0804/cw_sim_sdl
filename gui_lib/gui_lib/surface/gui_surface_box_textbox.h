#ifndef __GUI_SURFACE_BOX_TEXTBOX_H__
#define __GUI_SURFACE_BOX_TEXTBOX_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_textbox_create(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_textbox_change_string_id(gui_box_struct* box,int string_id);
extern void gui_surface_box_textbox_change_number(gui_box_struct* box,int number);
extern void gui_surface_box_textbox_change_string(gui_box_struct* box,unsigned char* str);

#endif
