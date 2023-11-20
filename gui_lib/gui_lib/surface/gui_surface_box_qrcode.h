﻿#ifndef __GUI_SURFACE_BOX_QRCODE_H__
#define __GUI_SURFACE_BOX_QRCODE_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern gui_node_struct* gui_surface_box_qrcode_arrange_content(gui_box_struct* box,const gui_qr_code_struct* qr_code,unsigned char* string);
extern gui_node_struct* gui_surface_box_qrcode_arrange_children(gui_box_struct* box,const gui_qr_code_struct* qr_code);
extern gui_node_struct* gui_surface_box_qrcode_arrange(gui_box_struct* box);

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_qrcode_create(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_qrcode_change(gui_box_struct* box,unsigned char* string);
extern void gui_surface_box_qrcode_arrange_refresh(gui_box_struct* box);

#endif
