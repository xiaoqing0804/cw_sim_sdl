﻿#ifndef __GUI_SURFACE_CONTROL_TIME_H__
#define __GUI_SURFACE_CONTROL_TIME_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"
#include "gui_surface_control_base.h"
#include "gui_event_core_list.h"


//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_control_time_create(gui_box_struct* box);
extern void gui_surface_control_hour_create(gui_box_struct* box);
extern void gui_surface_control_time_exit(gui_box_struct* box);

extern void gui_surface_control_time_hour_create(gui_box_struct* box);
extern void gui_surface_control_time_hour_exit(gui_box_struct* box);

extern void gui_surface_control_time_min_create(gui_box_struct* box);
extern void gui_surface_control_time_min_exit(gui_box_struct* box);
//事件响应--------------------------------------------------------------------------
extern const gui_static_event_struct g_gui_control_time;
extern const gui_static_event_struct g_gui_control_time_hour;
extern const gui_static_event_struct g_gui_control_time_min;
#endif