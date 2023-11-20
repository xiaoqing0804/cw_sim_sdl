
#include "picture.h"
#include "gui_display_draw_pointer.h"
#include "gui_drivers_flash.h"

#include "gui_display_draw_lib.h"
#include "gui_display_draw_lib_aa.h"

#include "debug_info.h"


void ui_draw_pointer_line(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
	gui_pointer_struct* pointer = (gui_pointer_struct*)render->data;
    short* line_pos = pointer->shape.line.position;
    if (line_pos != NULL) {
        int x0, y0, x1, y1;         // Taylor.Le, m
        x0 = render->x*10 + line_pos[0];
        y0 = render->y*10 + line_pos[1];
        x1 = render->x*10 + line_pos[2];
        y1 = render->y*10 + line_pos[3];
        //SYS_DEBUG("gui: p_line(%d, %d, %d, %d), pos:0x%x", x0, y0, x1, y1, (unsigned int)line_pos);
        gui_setColor(pointer->shape.line.color);
        gui_setPenSize(pointer->hand_width);
        GUI_AA_DrawLineX10(x0, y0, x1, y1);
    }
}

void gui_display_draw_pointer(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
	gui_pointer_struct* pointer = (gui_pointer_struct*)render->data;
    if (pointer->type == TYPE_GUI_DRAW_POINTER_LINE_60 || pointer->type == TYPE_GUI_DRAW_POINTER_LINE_360) {
        // for draw line
        ui_draw_pointer_line(render_buf, render, y_start, y_end);
    }
    else if (pointer->type == TYPE_GUI_DRAW_POINTER_8IMAGES) {
        GUI_DrawPointer8((picture_info_struct**)pointer->shape.pics, render->x, render->y, render->width, render->height, pointer->center_x, pointer->center_y, render->value);
    }
    else if (pointer->type == TYPE_GUI_DRAW_POINTER_16IMAGES) {
		#if PICTURE_ALPHA_POINT_FAST_SUPPORT
		GUI_DrawPointer16((picture_info_struct**)pointer->shape.pics, render->x, render->y, render->width, render->height, pointer->center_x, pointer->center_y, render->value);
		#endif
    }
}

