#include "picture.h"
#include "debug_info.h"

#include "gui_display_draw_lib.h"
#include "gui_display_draw_picture.h"

void gui_display_draw_picture_before()
{
	gui_display_draw_picture_scale_preload();   // gui_display_draw_picture_scale_check();
}

void gui_display_draw_picture_after()
{
	gui_display_draw_picture_scale_clear();
}

void gui_display_draw_picture(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
	if(gui_display_draw_picture_scale(render_buf,render,y_start,y_end))
		return;
	GUI_DrawPicture((picture_info_struct*)render->data, render->x, render->y);
}

