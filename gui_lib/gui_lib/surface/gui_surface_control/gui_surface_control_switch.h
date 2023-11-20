#ifndef __GUI_SURFACE_CONTROL_SWITCH_H__
#define __GUI_SURFACE_CONTROL_SWITCH_H__



#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"
#include "gui_surface_control_base.h"
#include "gui_event_core_list.h"

#define GUI_SWT_ON  1
#define GUI_SWT_OFF 0

//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_control_switch_create(gui_box_struct* box);
extern void gui_surface_control_switch_exit(gui_box_struct* box);


#endif

