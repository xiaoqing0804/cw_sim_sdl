#ifndef __GUI_SURFACE_LAYOUT_H__
#define __GUI_SURFACE_LAYOUT_H__

#include "feature_all.h"
#include "gui_core.h"

extern void gui_surface_layout_arrange(gui_surface_struct* surface);
extern unsigned char gui_surface_layout_is_delay_create_widget(const gui_screen_struct* screen,gui_widget_struct* widget);
extern void gui_surface_layout_set_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y);
extern short gui_surface_layout_get_offset_x(gui_surface_struct* surface);
extern short gui_surface_layout_get_offset_y(gui_surface_struct* surface);
extern void gui_surface_layout_move(gui_surface_struct* surface,short offset_x,short offset_y);
extern void gui_surface_layout_move_end(gui_surface_struct* surface);
extern void gui_surface_layout_exit(const gui_window_struct* window);
extern void gui_surface_layout_entry(const gui_window_struct* window);
extern void gui_surface_layout_clear_history(const gui_window_struct* window);

#endif
