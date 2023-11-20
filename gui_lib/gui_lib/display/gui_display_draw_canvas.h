#ifndef __GUI_DISPLAY_DRAW_CANVAS_H__
#define __GUI_DISPLAY_DRAW_CANVAS_H__

#include "feature_all.h"
#include "gui_display_render.h"

extern void gui_display_draw_canvas_point(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_line(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_style_line(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_rect(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_fill_rect(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_circle(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_fill_circle(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_arc(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_fill_arc(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_polygon(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_draw_canvas_fill_polygon(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);

#endif

