#ifndef __GUI_SURFACE_BOX_LABEL_H__
#define __GUI_SURFACE_BOX_LABEL_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern void gui_surface_box_label_check_clip(gui_box_struct* box, gui_node_struct* text_box);

extern gui_node_struct* gui_surface_box_label_single_arrange(gui_box_struct* box,unsigned char* utf8Str, unsigned int strWidth, const gui_font_struct* text);
extern gui_node_struct* gui_surface_box_label_multi_arrange(gui_box_struct* box, unsigned char* utf8Str, unsigned int strWidth, const gui_font_struct* text);
extern gui_node_struct* gui_surface_box_label_arrange_textbox(gui_box_struct* box, const gui_font_struct* text,unsigned char* str,short x,short y,short width,short height);
extern gui_node_struct* gui_surface_box_label_arrange_content(gui_box_struct* box, const gui_font_struct* text,unsigned char* str);
extern gui_node_struct* gui_surface_box_label_arrange_children(gui_box_struct* box, const gui_font_struct* text);
extern gui_node_struct* gui_surface_box_label_arrange(gui_box_struct* box);

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_label_create(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_label_change_content(gui_box_struct* box,const gui_font_struct* text,unsigned char* str);
extern void gui_surface_box_label_change_string(gui_box_struct* box,unsigned char* str);
extern void gui_surface_box_label_change_string_id(gui_box_struct* box,int string_id);
extern void gui_surface_box_label_change_number(gui_box_struct* box,int number);

#endif
