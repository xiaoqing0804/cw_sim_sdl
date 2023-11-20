#ifndef __GUI_SURFACE_BOX_SCALE_H__
#define __GUI_SURFACE_BOX_SCALE_H__

#include "feature_all.h"
#include "gui_core_all.h"

/*
// 父surface的改变，导致需要缩放整个box
extern void gui_surface_box_scale_by_parent(gui_surface_struct *surface, gui_box_struct *box, float offset_scale);

// 自身缩放整个box，缩放的大小是一个增量，需要考虑锚点的影响
extern void gui_surface_box_scale_offset(gui_surface_struct *surface, gui_box_struct *box, float offset_scale);

// 自身直接缩放整个box，缩放的大小是一个整体量，需要考虑锚点的影响
extern void gui_surface_box_scale(gui_surface_struct *surface, gui_box_struct *box, float scale);
*/

extern void gui_surface_box_calculate_scale(gui_scale_struct *gui_scale);

#endif
