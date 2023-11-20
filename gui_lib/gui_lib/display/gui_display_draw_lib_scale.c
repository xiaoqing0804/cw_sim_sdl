#include "picture.h"
#include "debug_info.h"
#include "os_mem.h"
#include "system_util_math.h"

#include "gui_display_draw_lib.h"
#include "gui_display_draw_picture.h"
#include "gui_drivers_flash.h"

#if defined(__CW_JL__)
#define __SCALE_ORGIN_PICTURE_IN_BUF__
#endif

typedef struct
{
	int x;
	int y;
	int width;
	int height;
#ifdef __SCALE_ORGIN_PICTURE_IN_BUF__
	unsigned char *pic_buf;
	unsigned char *pat_buf;
#endif
} gui_display_draw_scale_struct;

// 此函数在 gui task执行，计算缩放后，box内部的各个元素的位置和剪切区.
void gui_display_draw_box_scale_check(gui_box_struct *box, gui_render_struct *render)
{
}

// 此函数在 gui task执行，计算缩放后，图片的位置和剪切区.
void gui_display_draw_picture_scale_check(gui_render_struct *render)
{
	if ((render != NULL) && !FLOAT_EQUAL(render->scale, 1.0f))
	{
		//SYS_DEBUG("gui: scale0 = {%d, %d, %d, %d}", render->x, render->y, render->width, render->height);
		if (render->type == TYPE_GUI_DRAW_PICTURE)
		{
			picture_info_struct *picture_info = (picture_info_struct *)render->data;
			short width = render->width;
			short height = render->height;
			render->width = picture_info->width * render->scale + 0.5f;
			render->height = picture_info->height * render->scale + 0.5f;
			render->x += (width - render->width) / 2;
			render->y += (height - render->height) / 2;

			render->clip_left = render->x;
			render->clip_right = render->x + render->width - 1;
			render->clip_top = render->y;
			render->clip_bottom = render->y + render->height - 1;
		}
		else if (render->type == TYPE_GUI_DRAW_TEXT && render->scale < 1.0f)
		{
			// SYS_DEBUG("gui: text scale0, x=%d, y=%d, clip={%d, %d, %d, %d}", render->x, render->y, render->clip_left, render->clip_top, render->clip_right, render->clip_bottom);
			short rw = render->width;
			short rh = render->height;
			render->width = rw * render->scale + 0.5f;
			render->height = rh * render->scale + 0.5f;
			render->x += (rw - render->width) / 2;
			render->y += (rh - render->height) / 2;

			short cw = render->clip_right - render->clip_left + 1;
			short ch = render->clip_bottom - render->clip_top + 1;
			short sw = cw * render->scale + 0.5f;
			short sh = ch * render->scale + 0.5f;
			render->clip_left += (sw - rw) / 2;
			render->clip_right = render->clip_left + sw - 1;
			render->clip_top += (sh - rh) / 2;
			render->clip_bottom = render->clip_top + sh - 1;
			// SYS_DEBUG("gui: text scale1, x=%d, y=%d, clip={%d, %d, %d, %d}", render->x, render->y, render->clip_left, render->clip_top, render->clip_right, render->clip_bottom);
		}
		//SYS_DEBUG("gui: scale1 = {%d, %d, %d, %d}", render->x, render->y, render->width, render->height);
	}
}

// 只做预加载数据，坐标及剪切区的计算，放gui task执行.
void gui_display_draw_picture_scale_preload(void)
{
#if !(defined(__CW_JL_G2D_IMB__) || defined(__CW_JL_G2D_IMB_EXT__))
	gui_render_struct *render = gui_display_render_frist();
	while (render != NULL)
	{
		if (render->type == TYPE_GUI_DRAW_PICTURE && !FLOAT_EQUAL(render->scale, 1))
		{
			picture_info_struct *picture_info = (picture_info_struct *)render->data;

#ifdef __SCALE_ORGIN_PICTURE_IN_BUF__
			gui_display_draw_scale_struct *scale_info = os_mem_alloc(RAM_TYPE_BUFFER_ON, sizeof(gui_display_draw_scale_struct));
			memset(scale_info, 0, sizeof(gui_display_draw_scale_struct));
			render->value = (unsigned int)scale_info;
			if (picture_info->alpha == 0)
			{
				int size = picture_info->width * picture_info->height * COLOR_RGB_PIXEL;
				scale_info->pic_buf = os_mem_alloc(RAM_TYPE_BUFFER_ON, size);
				if (picture_info->external_flag)
				{
					gui_drivers_flash_read_image_to((unsigned char *)scale_info->pic_buf, (unsigned int)picture_info->addr, size);
				}
				else
				{
					scale_info->pic_buf = (unsigned char *)picture_info->addr;
				}
				scale_info->pat_buf = NULL;
			}
			else if (picture_info->alpha == 3)
			{
				int size = picture_info->width * picture_info->height;
				scale_info->pic_buf = os_mem_alloc(RAM_TYPE_BUFFER_ON, size);
				if (picture_info->external_flag)
				{
					gui_drivers_flash_read_image_to((unsigned char *)scale_info->pic_buf, (unsigned int)picture_info->addr, size);

					unsigned int pat_addr = (unsigned int)picture_info->addr + picture_info->width * picture_info->height + 2;
					scale_info->pat_buf = os_mem_alloc(RAM_TYPE_BUFFER_ON, 256 * COLOR_RGB_PIXEL);
					gui_drivers_flash_read_image_to((unsigned char *)scale_info->pat_buf, pat_addr, 256 * COLOR_RGB_PIXEL);
				}
				else
				{
					scale_info->pic_buf = (unsigned char *)picture_info->addr;
					scale_info->pat_buf = (unsigned int)picture_info->addr + picture_info->width * picture_info->height + 2;
				}
			}
#else
			gui_display_draw_scale_struct *scale_info = os_mem_alloc(RAM_TYPE_DATA_ON, sizeof(gui_display_draw_scale_struct));
			render->value = (unsigned int)scale_info;
#endif
			scale_info->x = render->x;
			scale_info->y = render->y;
			scale_info->width = render->width;
			scale_info->height = render->height;
		}
		render = render->next;
	}
#endif // !defined(__CW_JL_G2D_IMB__)
}

void gui_display_draw_picture_scale_clear(void)
{
#if !(defined(__CW_JL_G2D_IMB__) || defined(__CW_JL_G2D_IMB_EXT__))
	gui_render_struct *render = gui_display_render_frist();
	while (render != NULL)
	{
		if (render->type == TYPE_GUI_DRAW_PICTURE && !FLOAT_EQUAL(render->scale, 1))
		{
#ifdef __SCALE_ORGIN_PICTURE_IN_BUF__
			gui_display_draw_scale_struct *scale_info = (gui_display_draw_scale_struct *)render->value;
			if (scale_info->pic_buf != NULL)
			{
				os_mem_free((void *)scale_info->pic_buf);
			}
			if (scale_info->pat_buf != NULL)
			{
				os_mem_free((void *)scale_info->pat_buf);
			}
			if (render->value != NULL)
			{
				os_mem_free((void *)render->value);
			}
#else
			os_mem_free((void *)render->value);
#endif
		}
		render = render->next;
	}
#endif // !defined(__CW_JL_G2D_IMB__)
}

static char gui_display_draw_check_position(int x, int y, int width, int height, gui_display_draw_point_struct *position)
{
	if (gui_lib_ctx->y0 < y)
	{
		position->img_y0 = 0;
		position->y0 = y;
	}
	else
	{
		position->img_y0 = gui_lib_ctx->y0 - y;
		position->y0 = gui_lib_ctx->y0;
	}

	int iy1 = y + height - 1;
	if (iy1 > gui_lib_ctx->y1)
	{
		position->y1 = gui_lib_ctx->y1;
	}
	else
	{
		position->y1 = iy1;
	}

	position->dh = position->y1 - position->y0 + 1;

	if (x > 0)
	{
		position->img_x0 = 0;
		position->x0 = x;
	}
	else
	{
		position->img_x0 = ABS(x);
		position->x0 = 0;
	}
	position->x1 = x + width - 1;
	position->dw = position->x1 - position->x0 + 1;

	if (position->dw <= 0 || position->dh <= 0)
	{
		return 0;
	}
	return 1;
}

void gui_display_draw_picture_scale_picture(gui_render_struct *render)
{
#if !(defined(__CW_JL_G2D_IMB__) || defined(__CW_JL_G2D_IMB_EXT__))
	gui_display_draw_scale_struct *scale_info = (gui_display_draw_scale_struct *)render->value;
	picture_info_struct *picture_info = (picture_info_struct *)render->data;

	gui_display_draw_point_struct position;
	if (!gui_display_draw_check_position(scale_info->x, scale_info->y, scale_info->width, scale_info->height, &position))
		return;

	short x_pic_start = 0, x_pic_end = picture_info->width;
	short y_pic_start = 0, y_pic_end = picture_info->height;

#ifndef __SCALE_ORGIN_PICTURE_IN_BUF__
	y_pic_start = (short)(position.img_y0 / render->scale - 1.5f);
	y_pic_start = (short)math_range(y_pic_start, 0, picture_info->height - 1);

	y_pic_end = (short)((position.img_y0 + position.dh) / render->scale + 1.5f);
	y_pic_end = (short)math_range(y_pic_end, 0, picture_info->height - 1);
#endif

	if (picture_info->alpha == 0)
	{
		unsigned char *pic_buf;

#ifdef __SCALE_ORGIN_PICTURE_IN_BUF__
		pic_buf = scale_info->pic_buf;
#else
		unsigned int pic_addr_offset = (unsigned int)picture_info->addr + y_pic_start * picture_info->width * COLOR_RGB_PIXEL;
		unsigned int pic_size = (y_pic_end - y_pic_start) * picture_info->width * COLOR_RGB_PIXEL;
		if (pic_size > GUI_SCREEN_BUF_SIZE)
			return;
		if (picture_info->external_flag)
		{
			pic_buf = gui_drivers_flash_read_image_to_buff(pic_addr_offset, pic_size);
		}
		else
		{
			pic_buf = (unsigned char *)picture_info->addr;
		}
#endif

		unsigned int buf_offset = UI_CHARGE_XY(position.x0, position.y0); //((position.y0 - gui_lib_ctx->y0)*LCD_SIZE_WIDTH + position.x0)*COLOR_RGB_PIXEL;
		unsigned char *frame_buf = gui_lib_ctx->frame_buffer + buf_offset;
		unsigned char *frame_buf_x = frame_buf;

		short pic_x, pic_y;
		short draw_x, draw_y;
		unsigned short color, pic_color;
		unsigned char *p_color = (unsigned char *)&color;
		unsigned short r, g, b;
		for (draw_y = position.img_y0; draw_y < position.img_y0 + position.dh; draw_y++)
		{
			for (draw_x = position.img_x0; draw_x < position.img_x0 + position.dw; draw_x++)
			{
				pic_x = (short)(draw_x / render->scale + 0.5f);
				pic_y = (short)(draw_y / render->scale + 0.5f);

				if ((pic_x >= x_pic_start) && (pic_x < x_pic_end) && (pic_y >= y_pic_start) && (pic_y < y_pic_end))
				{
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
#if BYTE_ENDIAN == BYTE_ENDIAN_LITTLE
					pic_color = *((unsigned short *)(pic_buf + ((pic_y - y_pic_start) * picture_info->width + pic_x) * COLOR_RGB_PIXEL));
					*p_color++ = ((pic_color >> 8) & 0xFF);
					*p_color-- = (pic_color & 0xFF);

					r = COLOR_RGB_R(color);
					g = COLOR_RGB_G(color);
					b = COLOR_RGB_B(color);

					pic_color = COLOR_RGB((r * render->alpha) >> 8, (g * render->alpha) >> 8, (b * render->alpha) >> 8);

					*p_color++ = ((pic_color >> 8) & 0xFF);
					*p_color-- = (pic_color & 0xFF);
					*((unsigned short *)(frame_buf + draw_x * COLOR_RGB_PIXEL)) = color;
#else
					pic_color = *((unsigned short *)(pic_buf + ((pic_y - y_pic_start) * picture_info->width + pic_x) * COLOR_RGB_PIXEL));
					*p_color = pic_color;
					r = COLOR_RGB_R(color);
					g = COLOR_RGB_G(color);
					b = COLOR_RGB_B(color);
					pic_color = COLOR_RGB((r * render->alpha) >> 8, (g * render->alpha) >> 8, (b * render->alpha) >> 8);
					*p_color = pic_color;
#endif
#else
					p_color = pic_buf + ((pic_y - y_pic_start) * picture_info->width + pic_x) * COLOR_RGB_PIXEL;

					b = COLOR_RGB_B(*p_color);
					p_color++;

					g = COLOR_RGB_G(*p_color);
					p_color++;

					r = COLOR_RGB_R(*p_color);
					p_color++;

					pic_color = COLOR_RGB((r * render->alpha) >> 8, (g * render->alpha) >> 8, (b * render->alpha) >> 8);

					frame_buf_x = frame_buf + draw_x * COLOR_RGB_PIXEL;
					*frame_buf_x++ = 0;
					*frame_buf_x++ = 0;
					*frame_buf_x++ = 0;
#endif
				}
				else
				{
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
					*((unsigned short *)(frame_buf + draw_x * COLOR_RGB_PIXEL)) = 0;
#else
					frame_buf_x = frame_buf + draw_x * COLOR_RGB_PIXEL;
					*frame_buf_x++ = 0;
					*frame_buf_x++ = 0;
					*frame_buf_x++ = 0;
#endif
				}
			}
			frame_buf += gui_lib_ctx->bw; // (LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
		}
	}
	else if (picture_info->alpha == 3)
	{
		unsigned char *pic_buf;
		unsigned char *pat_buf;

#ifdef __SCALE_ORGIN_PICTURE_IN_BUF__
		pic_buf = scale_info->pic_buf;
		pat_buf = scale_info->pat_buf;
#else
		unsigned int pic_addr_offset = (unsigned int)picture_info->addr + y_pic_start * picture_info->width;
		unsigned int pic_size = (y_pic_end - y_pic_start) * picture_info->width;
		if (pic_size > GUI_SCREEN_BUF_SIZE)
			return;
		if (picture_info->external_flag)
		{
			unsigned int pat_addr = (unsigned int)picture_info->addr + picture_info->width * picture_info->height + 2;

			pic_buf = gui_drivers_flash_read_image_to_buff(pic_addr_offset, pic_size);

			// read pattern
			pat_buf = pic_buf + ((pic_size + 3) & 0xFFFFFFFC);
			gui_drivers_flash_read_image_to(pat_buf, pat_addr, 256 * COLOR_RGB_PIXEL);
		}
		else
		{
			pic_buf = (unsigned char *)picture_info->addr;
			pat_buf = (unsigned char *)(picture_info->addr + picture_info->width * picture_info->height + 2);
		}
#endif

		unsigned int buf_offset = UI_CHARGE_XY(position.x0, position.y0); //((position.y0 - gui_lib_ctx->y0)*LCD_SIZE_WIDTH + position.x0)*COLOR_RGB_PIXEL;
		unsigned char *frame_buf = gui_lib_ctx->frame_buffer + buf_offset;
		unsigned char *frame_buf_x = frame_buf;

		short pic_x, pic_y;
		short draw_x, draw_y;
		unsigned short color, pic_color;
		unsigned char *p_color = (unsigned char *)&color;
		unsigned short r, g, b;
		unsigned char color_index;

		for (draw_y = position.img_y0; draw_y < position.img_y0 + position.dh; draw_y++)
		{
			for (draw_x = position.img_x0; draw_x < position.img_x0 + position.dw; draw_x++)
			{
				pic_x = (short)(draw_x / render->scale + 0.5f);
				pic_y = (short)(draw_y / render->scale + 0.5f);

				if ((pic_x >= x_pic_start) && (pic_x < x_pic_end) && (pic_y >= y_pic_start) && (pic_y < y_pic_end))
				{
					color_index = *((unsigned char *)pic_buf + (pic_y - y_pic_start) * picture_info->width + pic_x);
					pic_color = *((unsigned short *)pat_buf + color_index);

#if BYTE_ENDIAN == BYTE_ENDIAN_LITTLE
					*p_color++ = ((pic_color >> 8) & 0xFF);
					*p_color-- = (pic_color & 0xFF);

					r = COLOR_RGB_R(color);
					g = COLOR_RGB_G(color);
					b = COLOR_RGB_B(color);

					pic_color = COLOR_RGB((r * render->alpha) >> 8, (g * render->alpha) >> 8, (b * render->alpha) >> 8);

					*p_color++ = ((pic_color >> 8) & 0xFF);
					*p_color-- = (pic_color & 0xFF);
					*((unsigned short *)(frame_buf + draw_x * COLOR_RGB_PIXEL)) = color;
#else
					*p_color = pic_color;
					r = COLOR_RGB_R(color);
					g = COLOR_RGB_G(color);
					b = COLOR_RGB_B(color);
					pic_color = COLOR_RGB((r * render->alpha) >> 8, (g * render->alpha) >> 8, (b * render->alpha) >> 8);
					*p_color = pic_color;
#endif
				}
				else
				{
					*((unsigned short *)(frame_buf + draw_x * COLOR_RGB_PIXEL)) = 0;
				}
			}
			frame_buf += gui_lib_ctx->bw; //(LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
		}
	}
#endif // !defined(__CW_JL_G2D_IMB__)
}

unsigned char gui_display_draw_picture_scale(unsigned char *render_buf, gui_render_struct *render, short y_start, short y_end)
{
#if !(defined(__CW_JL_G2D_IMB__) || defined(__CW_JL_G2D_IMB_EXT__))
	if (render->type == TYPE_GUI_DRAW_PICTURE && !FLOAT_EQUAL(render->scale, 1))
	{
		gui_display_draw_picture_scale_picture(render);
		return 1;
	}
#endif
	return 0;
}
