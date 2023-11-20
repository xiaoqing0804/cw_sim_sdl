#ifndef __GUI_SURFACE_SCALE_H__
#define __GUI_SURFACE_SCALE_H__

#include "feature_all.h"
#include "gui_core_all.h"

/*
extern void gui_surface_scale_clear(gui_surface_struct *surface);

// 增量式缩放整个surface
extern void gui_surface_scale_offset(gui_surface_struct *surface, float offset_scale);

// 直接缩放整个surface
extern void gui_surface_scale(gui_surface_struct *surface, float scale);
*/

extern void gui_surface_calculate_scale(gui_scale_struct *gui_scale);

#endif
