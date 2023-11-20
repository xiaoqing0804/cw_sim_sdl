#ifndef __GUI_DISPLAY_DRAW_QRCODE_H__
#define __GUI_DISPLAY_DRAW_QRCODE_H__

#include "picture.h"
#include "feature_all.h"
#include "gui_display_render.h"


extern void gui_display_draw_qrcode_check(void);
extern void gui_display_draw_qrcode_clear(void);
extern void gui_display_draw_qrcode_to_frame(gui_render_struct* render);
extern void gui_display_draw_qrcode(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);

#endif

