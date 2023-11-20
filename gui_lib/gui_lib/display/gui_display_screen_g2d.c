#include "gui_core.h"
#include "gui_display_screen_g2d.h"
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

#if(GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_G2D)
#include "bsp_includes.h"
#include "os_mem.h"
#include "bsp_g2d_imb.h"

#include "gui_display_render_g2d.h"

extern unsigned char* res_buffer_take(unsigned int size);


#ifdef __CW_JL_VLT_MEM__
void gui_display_screen_memory_init(void)
{
    bsp_g2d_imb_init(NULL);
}
void gui_display_screen_memory_deinit(void)
{
    bsp_g2d_imb_deinit(NULL);
}
#endif

static inline unsigned char gui_display_screen_g2d_in_area(gui_render_struct* render, short x0, short y0, short x1, short y1)
{
	if(render->clip_top > y1 || render->clip_bottom < y0)
		return 0;
	if(render->clip_left > x1 || render->clip_right < x0)
		return 0;
	return 1;
}

//
// 提供给 imb 模块调用，用来绘制不能用imb渲染的对象
void gui_display_screen_g2d_render(unsigned char* render_buf,gui_render_struct* render, short x, short y, short w, short h)
{
    short y_start = y;
    short y_end   = y+h-1;

    if (!gui_display_screen_g2d_in_area(render, x, y_start, x+w-1, y_end)) {
        return;
    }

    //SYS_DEBUG("gui: g2d_render, render=%x, rect={x:%d, y:%d, w:%d, h:%d}", (unsigned int)render, x, y, w, h);
    gui_setFrameBufferRect(render_buf, x, y, w, h);
    gui_setScale(render->scale);
    gui_setClip(render->clip_left, render->clip_top, render->clip_right, render->clip_bottom);

#if 0
    unsigned short  hi, wi;
    unsigned short* pdes = (unsigned short*)render_buf;
    for(hi=0; hi<h; hi++) {
        for (wi=0; wi<w; wi++) {
            *pdes = COLOR_RGB(255, 0, 0);
            pdes ++;
        }
    }
#else
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
#endif
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void gui_display_screen_g2d_shape(gui_render_struct* render)
{
#if GUI_SURFACE_ZOOM_SUPPORT
    //SYS_DEBUG("gui: TYPE_GUI_DRAW_SHAPE, scale=%f", render->scale);
    if (!FLOAT_EQUAL_ONE(render->scale)) {
        gui_canvas_struct* canvas = (gui_canvas_struct*)res_buffer_take(sizeof(gui_canvas_struct));
        if (canvas == NULL) {
            return;
        }
        memcpy(canvas, render->data, sizeof(gui_canvas_struct));
        render->data = canvas;
        if (render->type == TYPE_GUI_DRAW_SHAPE_POLYGON || render->type == TYPE_GUI_DRAW_SHAPE_POLYGON_FILL) {
            gui_point_struct* points = (gui_point_struct*)res_buffer_take(canvas->canvas.polygon.point_num*sizeof(gui_point_struct));
            if (points == NULL) {
                return;
            }
            memcpy(points, canvas->canvas.polygon.points, canvas->canvas.polygon.point_num*sizeof(gui_point_struct));
            canvas->canvas.polygon.points = points;
        }
        gui_display_render_canvas_coordinate_transormation_by_scale(render);
    }
#endif

    if (render->type == TYPE_GUI_DRAW_SHAPE_RECT_FILL) {
        gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
        u32 color = ((100-canvas->opacity)<<24)+canvas->penColor;
        int x0, y0, x1, y1;
        x0 = render->x+canvas->canvas.rect.x0;
        y0 = render->y+canvas->canvas.rect.y0;
        x1 = render->x+canvas->canvas.rect.x1;
        y1 = render->y+canvas->canvas.rect.y1;
        //SYS_DEBUG("gui: canvas_rect{%d, %d, %d, %d}", canvas->canvas.rect.x0, canvas->canvas.rect.y0, canvas->canvas.rect.x1, canvas->canvas.rect.y1);
        //SYS_DEBUG("gui: draw_rect{%d, %d, %d, %d}, color=%x", x0, y0, x1, y1, color);
        imb_create_color_fill_task(x0, y0, x1, y1, color);
        return;
    }
    imb_create_custom_task(render);
}


static void gui_display_screen_g2d_pointer_zoom(gui_render_struct* render)
{
    gui_pointer_struct* pointer = (gui_pointer_struct*)render->data;
    if ((pointer->type == TYPE_GUI_DRAW_POINTER_LINE_60)||(pointer->type == TYPE_GUI_DRAW_POINTER_LINE_360)) {
        short* pos = pointer->shape.line.position;
        pos[0] = 5*render->width;// - (short)(5*pointer->hand_width);
        pos[1] = 5*render->height - (short)((10*pointer->hand_lenth) * render->scale);
        pos[2] = pos[0];// + (short)(10*pointer->hand_width);
        pos[3] = pos[1] + (short)(10*(pointer->hand_lenth + pointer->hilt_lenth) * render->scale);
        SYS_DEBUG("gui: TYPE_GUI_DRAW_POINTER, scale=%f", render->scale);
        imb_create_custom_task(render);
    }
    else if ((pointer->type == TYPE_GUI_DRAW_POINTER_16IMAGES) || (pointer->type == TYPE_GUI_DRAW_POINTER_1IMAGES)) {
        picture_info_struct* pic = (pointer->type == TYPE_GUI_DRAW_POINTER_16IMAGES) ? pointer->shape.pics[16] : pointer->shape.pics[1];
        if (pic != NULL) {
            // 有缩放时，一律显示最后一张附加图片...
            render->x = render->x + render->width/2 - (short)((pointer->hand_width/2) * render->scale);
            render->y = render->y + render->height/2 - (short)((pointer->hand_lenth) * render->scale);
            render->width = (short)(pointer->hand_width * render->scale);
            render->height = (short)((pointer->hand_lenth + pointer->hilt_lenth) * render->scale);
            render->clip_left = render->x;
            render->clip_top  = render->y;
            render->clip_right  = render->x + render->width - 1;
            render->clip_bottom = render->y + render->height - 1;
            imb_create_image_task_ext(render, pic);
            return;
        }
        if (pointer->type == TYPE_GUI_DRAW_POINTER_16IMAGES) {
            imb_create_custom_task(render);
        }
    }
    else {
        SYS_DEBUG("gui: g2d_object, pointer:%x error no type!!! %d", (unsigned int)pointer, pointer->type);
    }
}
static void gui_display_screen_g2d_pointer(gui_render_struct* render)
{
    gui_pointer_struct* pointer = (gui_pointer_struct*)render->data;
    if (pointer != NULL) {
        if ((pointer->type == TYPE_GUI_DRAW_POINTER_LINE_60)||(pointer->type == TYPE_GUI_DRAW_POINTER_LINE_360)) {
            // 画线指针，需要备份指针坐标等数据.
            gui_pointer_struct* pt2 = (gui_pointer_struct*)res_buffer_take(sizeof(gui_pointer_struct) + 8);
            if (pt2 != NULL) {
                short* pos = (short*)(pt2 + 1);
                memcpy(pt2, pointer, sizeof(gui_pointer_struct));
                memcpy(pos, pointer->shape.line.position, 8);
                pt2->shape.line.position = pos;
                render->data = pt2;
            }
            else {
                return;
            }
        }

        #if GUI_SURFACE_ZOOM_SUPPORT
        if (!FLOAT_EQUAL_ONE(render->scale)) {
            gui_display_screen_g2d_pointer_zoom(render);
            return;
        }
        #endif

        if (pointer->type == TYPE_GUI_DRAW_POINTER_1IMAGES) {
            imb_create_rotate_image_task(render, pointer->shape.pics[0], render->value*6);
        }
        else {
            imb_create_custom_task(render);
        }
    }
    else {
        SYS_DEBUG("gui: g2d_object, pointer error no data!!!");
    }
}

// 创建各个 render 的imb-task...
static void gui_display_screen_g2d_object(gui_render_struct* render,short y_start,short y_end)
{
    //SYS_DEBUG("gui: g2d_object, type=%d", render->type);
	switch(render->type)
	{
        case TYPE_GUI_DRAW_POINTER:
            gui_display_screen_g2d_pointer(render);
            break;

		case TYPE_GUI_DRAW_PICTURE:
            if (0 == imb_create_image_task(render)) {
                imb_create_custom_task(render);
            }
            break;

		case TYPE_GUI_DRAW_TEXT:
            if (0 == imb_create_text_task(render)) {
                imb_create_custom_task(render);
            }
            break;
		case TYPE_GUI_DRAW_SHAPE_CUSTOM:
            break;

		case TYPE_GUI_DRAW_SHAPE_POINT:
		case TYPE_GUI_DRAW_SHAPE_LINE:
		case TYPE_GUI_DRAW_SHAPE_STYLE_LINE:
		case TYPE_GUI_DRAW_SHAPE_RECT:
		case TYPE_GUI_DRAW_SHAPE_RECT_FILL:
		case TYPE_GUI_DRAW_SHAPE_CIRCLE:
		case TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL:
		case TYPE_GUI_DRAW_SHAPE_ARC:
		case TYPE_GUI_DRAW_SHAPE_ARC_FILL:
        case TYPE_GUI_DRAW_SHAPE_POLYGON:
        case TYPE_GUI_DRAW_SHAPE_POLYGON_FILL:
            gui_display_screen_g2d_shape(render);
            break;

        case TYPE_GUI_DRAW_DLWF_PICTURE:
        case TYPE_GUI_DRAW_DLWF_SHAPE:
		case TYPE_GUI_DRAW_QR_CODE:
        default:
            imb_create_custom_task(render);
            break;
	}
}

static void* gui_display_screen_g2d_check_bg(void)
{
	gui_render_struct* render =  gui_display_render_frist();
	while (render != NULL) {
        if (render->type == TYPE_GUI_DRAW_PICTURE) {//20230816 Taylor.Le, && render->width == LCD_SIZE_WIDTH && render->height == LCD_SIZE_HEIGHT) {
            picture_info_struct* pic = (picture_info_struct*)render->data;
            if (pic->alpha != 10 && pic->alpha != 11) {
                return render;
            }
        }
        else if (render->type == TYPE_GUI_DRAW_DLWF_PICTURE) {  //20230816 Taylor.Le,
            return render;
        }
		render = render->next;
	}
    return NULL;
}

static void gui_display_screen_g2d_before(void)
{
    //flash_mutex_take();
    bsp_g2d_imb_before(gui_display_screen_g2d_check_bg());
}

static void gui_display_screen_g2d_after(void)
{
    bsp_g2d_imb_after(NULL);
    //flash_mutex_give();
}


static void gui_display_screen_g2d_frame(short y_start,short y_end)
{
	gui_render_struct* render =  gui_display_render_frist();
	while(render != NULL)
	{
		if(gui_display_screen_g2d_in_area(render, 0, y_start, LCD_SIZE_WIDTH-1, y_end))//相交
		{
			if(render->type == TYPE_GUI_DRAW_TEXT) {
				if(render->clip_left <= render->clip_right && render->clip_top <= render->clip_bottom)
				{
					gui_display_screen_g2d_object(render, y_start, y_end);
				}
			}
			else {
				if(render->clip_left <= render->clip_right && render->clip_top <= render->clip_bottom)	 // 20230616 Taylor.Le, m
				{
					gui_display_screen_g2d_object(render, y_start, y_end);
				}
                else {
                    //SYS_DEBUG("gui: render: %x, type=%d, outside clip{lf: %d, rt: %d, top: %d, bot: %d}!!!", (unsigned int)render, render->type, render->clip_left, render->clip_right, render->clip_top, render->clip_bottom);
                }
			}
		}
        else {
            //SYS_DEBUG("gui: render %d, outside screen!!!", render->type);
        }
		render = render->next;
	}
}

static void gui_display_screen_g2d_start(short y_start,short y_end)
{
    bsp_g2d_imb_start(NULL);
}

//
static void gui_display_screen_g2d_update_before()
{
	gui_display_draw_picture_before();
	gui_display_draw_qrcode_check();
	gui_display_draw_barcode_check();
    gui_display_screen_g2d_before();
}

static void gui_display_screen_g2d_update_after()
{
    gui_display_screen_g2d_after();
	gui_display_draw_qrcode_clear();
	gui_display_draw_barcode_clear();
	gui_display_draw_picture_after();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void gui_display_screen_g2d_update()
{
	short y_start = 0;
	short y_end = LCD_SIZE_HEIGHT - 1;

    //SYS_DEBUG("gui: g2d_update");

	gui_display_screen_g2d_update_before();

    gui_display_screen_g2d_frame(y_start, y_end);
    gui_display_screen_g2d_start(y_start, y_end);

	gui_display_screen_g2d_update_after();
}

void gui_display_screen_g2d_init()
{
    bsp_g2d_init();
}


void gui_display_screen_g2d_cache_release(unsigned int wnd_owner)
{
    bsp_g2d_imb_cache_release(wnd_owner);
}


#endif

