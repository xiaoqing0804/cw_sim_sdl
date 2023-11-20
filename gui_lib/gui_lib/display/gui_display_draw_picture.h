#ifndef __GUI_DISPLAY_DRAW_PICTURE_H__
#define __GUI_DISPLAY_DRAW_PICTURE_H__

#include "feature_all.h"
#include "gui_display_render.h"

extern void gui_display_draw_picture_before(void);
extern void gui_display_draw_picture_after(void);
extern void gui_display_draw_picture(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);

#endif

