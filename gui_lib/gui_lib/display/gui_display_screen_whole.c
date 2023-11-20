#include "gui_core.h"
#include "gui_display_screen_whole.h"
#include "gui_display_render.h"
#include "gui_display_draw_picture.h"
#include "gui_display_draw_character.h"
#include "gui_display_draw_canvas.h"
#include "gui_display_draw_pointer.h"
#include "gui_display_draw_dlwf.h"
#include "gui_display_draw_qrcode.h"
#include "gui_display_draw_barcode.h"
#include "gui_drivers_lcd.h"
#include "qrencode.h"

#include "gui_display_draw_lib.h"



#if(GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_WHOLE)
#include "os_mem.h"

#ifdef __CW_JL_VLT_MEM__
static unsigned char* g_screen_whole_render_buf_front;
static unsigned char* g_screen_whole_render_buf_back;
#else
static unsigned char  g_screen_whole_render_buf_1[GUI_SCREEN_WHOLE_BUF_SIZE];
static unsigned char  g_screen_whole_render_buf_2[GUI_SCREEN_WHOLE_BUF_SIZE];
static unsigned char* g_screen_whole_render_buf_front = g_screen_whole_render_buf_1;
static unsigned char* g_screen_whole_render_buf_back = g_screen_whole_render_buf_2;
#endif
static unsigned int   g_screen_whole_txdat_count = 0;

#ifdef __CW_JL_VLT_MEM__
void gui_display_screen_memory_init(void)
{
    g_screen_whole_render_buf_front = os_mem_alloc(RAM_TYPE_PSRAM_ON, GUI_SCREEN_WHOLE_BUF_SIZE);
    g_screen_whole_render_buf_back  = os_mem_alloc(RAM_TYPE_PSRAM_ON, GUI_SCREEN_WHOLE_BUF_SIZE);
    if (g_screen_whole_render_buf_front == NULL || g_screen_whole_render_buf_back == NULL) {
        DBG_DIRECT("gui: screen_memory_init, error!!!");
    }
}
void gui_display_screen_memory_deinit(void)
{
    os_mem_free(g_screen_whole_render_buf_front);
    os_mem_free(g_screen_whole_render_buf_back);
    g_screen_whole_render_buf_front = NULL;
    g_screen_whole_render_buf_back  = NULL;
}
#endif


static void gui_display_screen_whole_draw(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
	switch(render->type)
	{
		case TYPE_GUI_DRAW_PICTURE:
			gui_display_draw_picture(render_buf,render,y_start,y_end);
			break;

		case TYPE_GUI_DRAW_TEXT:
			gui_display_draw_character(render_buf,render,y_start,y_end);
			break;

        case TYPE_GUI_DRAW_POINTER:
            gui_display_draw_pointer(render_buf, render, y_start, y_end);
            break;

		case TYPE_GUI_DRAW_SHAPE_CUSTOM:
			//void (*draw)(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
			//render->data(render_buf,render,y_start,y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_POINT:
			gui_display_draw_canvas_point(render_buf,render,y_start,y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_LINE:
			gui_display_draw_canvas_line(render_buf,render,y_start,y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_STYLE_LINE:
			gui_display_draw_canvas_style_line(render_buf,render,y_start,y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_RECT:
            gui_display_draw_canvas_rect(render_buf, render, y_start, y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_RECT_FILL:
            gui_display_draw_canvas_fill_rect(render_buf, render, y_start, y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_CIRCLE:
            gui_display_draw_canvas_circle(render_buf, render, y_start, y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL:
            gui_display_draw_canvas_fill_circle(render_buf, render, y_start, y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_ARC:
            gui_display_draw_canvas_arc(render_buf, render, y_start, y_end);
			break;

		case TYPE_GUI_DRAW_SHAPE_ARC_FILL:
            gui_display_draw_canvas_fill_arc(render_buf, render, y_start, y_end);
			break;

        case TYPE_GUI_DRAW_SHAPE_POLYGON:
            gui_display_draw_canvas_polygon(render_buf, render, y_start, y_end);
            break;

        case TYPE_GUI_DRAW_SHAPE_POLYGON_FILL:
            gui_display_draw_canvas_fill_polygon(render_buf, render, y_start, y_end);
            break;


        case TYPE_GUI_DRAW_DLWF_PICTURE:
            gui_display_draw_dlwf_picture(render_buf, render, y_start, y_end);
            break;
        case TYPE_GUI_DRAW_DLWF_SHAPE:
            gui_display_draw_dlwf_shape(render_buf, render, y_start, y_end);
            break;

		case TYPE_GUI_DRAW_QR_CODE:
			gui_display_draw_qrcode(render_buf,render,y_start,y_end);
			break;
		
		case TYPE_GUI_DRAW_BAR_CODE_128:
			gui_display_draw_barcode(render_buf,render,y_start,y_end);
			break;
	}

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static inline unsigned char gui_display_screen_whole_in_area(gui_render_struct* render,short y_start,short y_end)
{
	if(render->clip_top > y_end || render->clip_bottom < y_start)
		return 0;
	return 1;
}

static void gui_display_screen_whole_frame(short y_start,short y_end)
{
	gui_render_struct* render =  gui_display_render_frist();
	while(render != NULL)
	{
		if(gui_display_screen_whole_in_area(render,y_start,y_end))//Ïà½»
		{
			if(render->clip_left <= render->clip_right && render->clip_top <= render->clip_bottom)
			{
                gui_setClip(render->clip_left, render->clip_top, render->clip_right, render->clip_bottom);
				gui_display_screen_whole_draw(g_screen_whole_render_buf_back,render,y_start,y_end);
			}
		}
		render = render->next;
	}
}

static void gui_display_screen_whole_push_buf_to_lcd(short y_start, short y_end)
{
	while(gui_drivers_lcd_wait(g_screen_whole_txdat_count));
    g_screen_whole_txdat_count = ((y_end-y_start+1)*LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);

	swap_front_back((void**)&g_screen_whole_render_buf_front,(void**)&g_screen_whole_render_buf_back);
	gui_drivers_lcd_display(g_screen_whole_render_buf_front,y_start,y_end);
}


static void gui_display_screen_whole_update_before()
{
	gui_display_draw_picture_before();
	gui_display_draw_qrcode_check();
	gui_display_draw_barcode_check();
}

static void gui_display_screen_whole_update_after()
{
	gui_display_draw_picture_after();
	gui_display_draw_qrcode_clear();
	gui_display_draw_barcode_clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gui_display_screen_whole_update()
{
	short y_start = 0;
	short y_end = LCD_SIZE_HEIGHT - 1;

	gui_display_screen_whole_update_before();

    g_screen_whole_txdat_count = 0;
    memset((int*)g_screen_whole_render_buf_back, 0, GUI_SCREEN_WHOLE_BUF_SIZE);
    gui_setFrameBuffer(g_screen_whole_render_buf_back, y_start, y_end);
    gui_display_screen_whole_frame(y_start, y_end);
    gui_display_screen_whole_push_buf_to_lcd(y_start, y_end);

	gui_display_screen_whole_update_after();
}

void gui_display_screen_whole_init()
{
}

#endif

