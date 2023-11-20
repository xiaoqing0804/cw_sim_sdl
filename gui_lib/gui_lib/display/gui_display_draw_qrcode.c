#include "qrencode.h"
#include "picture.h"
#include "debug_info.h"
#include "qrencode.h"

#include "gui_display_draw_lib.h"
#include "gui_display_draw_qrcode.h"
#include "os_mem.h"


typedef struct
{
	short x;
	short y;
	short width;
	short height;
	unsigned char scale;
	QRcode *data;
}gui_render_qrcode_struct;

#define QR_CODE_SCALE (8)

#define QR_CODE_VERSION 	(1)
#define QR_CODE_LEVEL 		(QR_ECLEVEL_H)        // TCFG_PAY_ALIOS_ENABLE (QR_ECLEVEL_L)
#define QR_CODE_MODE 		(QR_MODE_8)
#define QR_CODE_MAX_WIDTH 	(69)


static short gui_display_draw_qrcode_check_scale(gui_render_struct* render,QRcode *qrcode_data)
{
	if(render->width < qrcode_data->width)
		return 1;

    short scale = render->width / qrcode_data->width;
    /*    
	short scale = QR_CODE_SCALE;
	short width = qrcode_data->width * scale;
	while(width >= render->width)
	{
		if(scale == 1)
			break;
		width = qrcode_data->width * (--scale);
	}*/
	return scale;
}

void gui_display_draw_qrcode_check()
{
	gui_render_struct* render = gui_display_render_frist();
	while(render != NULL)
	{
		if(render->type == TYPE_GUI_DRAW_QR_CODE)
		{
			QRcode *qrcode_data = QRcode_encodeString((unsigned char*)render->data, QR_CODE_VERSION, QR_CODE_LEVEL, QR_CODE_MODE, 1);
			if(qrcode_data != NULL)
			{
				if(qrcode_data->width > QR_CODE_MAX_WIDTH)
				{
					QRcode_free(qrcode_data);
					return;
				}
				short scale = gui_display_draw_qrcode_check_scale(render,qrcode_data);
				short width = qrcode_data->width * scale;

				gui_render_qrcode_struct* render_qrcode = os_mem_alloc(RAM_TYPE_BUFFER_ON,sizeof(gui_render_qrcode_struct));
				render_qrcode->x = render->x + (render->width  - width) / 2;
				render_qrcode->y = render->y + (render->height - width) / 2;
				render_qrcode->scale = scale;
				render_qrcode->width = width;
				render_qrcode->height = width;	
				render_qrcode->data = qrcode_data;
				
				render->value = (unsigned int)render_qrcode;
				render->clip_left = render_qrcode->x;
				render->clip_right = render_qrcode->x + width;
				render->clip_top = render_qrcode->y;
				render->clip_bottom = render_qrcode->y + width;
			}
			
		}
		
		render = render->next;
		
	}
}

void gui_display_draw_qrcode_clear()
{
	gui_render_struct* render = gui_display_render_frist();
	while(render != NULL)
	{
		if(render->type == TYPE_GUI_DRAW_QR_CODE)
		{
			gui_render_qrcode_struct* render_qrcode = (gui_render_qrcode_struct*)render->value;
			if(render_qrcode != NULL)
			{
				if(render_qrcode->data!= NULL)
				{
					QRcode_free(render_qrcode->data);
				}
				os_mem_free((void*)render_qrcode);
			}
			render->value = NULL;
		}
		render = render->next;
	}
}

static char gui_display_draw_qrcode_check_position(int x, int y, int width, int height,gui_display_draw_point_struct* position)
{
    if (gui_lib_ctx->y0 < y) {
        position->y0 = y;
    } else {
        position->y0 = gui_lib_ctx->y0;
    }
	
    int iy1 = y + height - 1;
    if (iy1 > gui_lib_ctx->y1) {
       position->y1 = gui_lib_ctx->y1;
    }else {
       position->y1 = iy1;
    }
	
    position->dh = position->y1 - position->y0 + 1;
    
    if (x > 0) {
        position->x0 = x;
    }else {
        position->x0 = 0;
    }
    position->x1 = x + width - 1;
    position->dw = position->x1 - position->x0 + 1;

	if (position->dw <= 0 || position->dh <= 0) {
        return 0;
    }
	return 1;
}


void gui_display_draw_qrcode_to_frame(gui_render_struct* render)
{
	gui_render_qrcode_struct* render_qrcode = (gui_render_qrcode_struct*)render->value;
	QRcode* qrcode_data = render_qrcode->data;

	gui_display_draw_point_struct position;
	if(!gui_display_draw_qrcode_check_position(render_qrcode->x,render_qrcode->y,render_qrcode->width,render_qrcode->height,&position))
        return;
	
    unsigned int buf_offset = UI_CHARGE_XY(position.x0, position.y0);   //((position.y0-gui_lib_ctx->y0)*LCD_SIZE_WIDTH + position.x0)*COLOR_RGB_PIXEL;
    unsigned char* frame_buf = gui_lib_ctx->frame_buffer + buf_offset;

    short xx, yy, data_x, data_y;
	unsigned char* data_row;
    unsigned char* data = qrcode_data->data;
	unsigned short* frame_buf_row = (unsigned short*)frame_buf;
    for (yy = position.y0; yy <= position.y1; yy++)
	{
		data_y = (yy - render_qrcode->y) / render_qrcode->scale;
		data_y = math_range(data_y, 0, qrcode_data->width-1);
        data_row = data + (data_y * qrcode_data->width);
        for (xx = position.x0; xx <= position.x1; xx++)
		{
			data_x = (xx - render_qrcode->x) / render_qrcode->scale;
			data_x = math_range(data_x, 0, qrcode_data->width-1);
            if ((*(data_row + data_x) & 0x1) == 1)
            	*frame_buf_row++ = COLOR_BLACK;
            else
                *frame_buf_row++ = COLOR_WHITE;
        }
		frame_buf += gui_lib_ctx->bw;    //(LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
		frame_buf_row = frame_buf;
    }
	
}

void gui_display_draw_qrcode(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
	if(render->type == TYPE_GUI_DRAW_QR_CODE && render->value != 0)
	{
		gui_display_draw_qrcode_to_frame(render);
	}
}


