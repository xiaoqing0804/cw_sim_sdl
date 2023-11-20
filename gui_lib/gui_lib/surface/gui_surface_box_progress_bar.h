#ifndef __GUI_SURFACE_BOX_PROGRESS_BAR_H__
#define __GUI_SURFACE_BOX_PROGRESS_BAR_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

extern gui_node_struct* gui_surface_box_progress_bar_arrange_children(gui_box_struct* box,unsigned char progress);
extern gui_node_struct* gui_surface_box_progress_bar_arrange(gui_box_struct* box);

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_box_progress_bar_create(gui_box_struct* box);
extern unsigned char gui_surface_box_progress_bar_get_value(gui_box_struct* box);

//界面改变--------------------------------------------------------------------------
extern void gui_surface_box_progress_bar_change(gui_box_struct* box,unsigned char progress);

#endif
