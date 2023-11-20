#ifndef __GUI_SURFACE_CONTROL_SCROLLTEXT_H__
#define __GUI_SURFACE_CONTROL_SCROLLTEXT_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"
#include "gui_surface_control_base.h"
#include "gui_event_core_list.h"


//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_control_scrolltext_create(gui_box_struct* box);
extern void gui_surface_control_scrolltext_exit(gui_box_struct* box);
extern void gui_surface_control_scrolltext_change_string(gui_box_struct* box, unsigned char* string);

#endif

