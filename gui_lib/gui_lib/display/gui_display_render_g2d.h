#ifndef __GUI_DISPLAY_RENDER_G2D_H__
#define __GUI_DISPLAY_RENDER_G2D_H__

#include "gui_display_render.h"


extern void gui_display_render_pointer_coordinate_transormation_by_scale(gui_render_struct* render);
extern void gui_display_render_canvas_coordinate_transormation_by_scale(gui_render_struct* render);
extern int  gui_display_render_coordinate_transormation_by_scale(gui_surface_struct* surface, gui_render_struct* render); // coordinate transformation

#endif

