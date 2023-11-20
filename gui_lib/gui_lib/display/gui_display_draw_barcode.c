#include "picture.h"
#include "debug_info.h"
#include "barcode_code128.h"

#include "gui_display_draw_lib.h"
#include "gui_display_draw_barcode.h"
#include "os_mem.h"

typedef struct
{
	short x;
	unsigned char length;
	unsigned char scale;
	unsigned char *data;
	unsigned char data_count;
} gui_render_barcode_struct;

void gui_display_draw_barcode_check()
{
	gui_render_struct *render = gui_display_render_frist();
	while (render != NULL)
	{
		if (render->type == TYPE_GUI_DRAW_BAR_CODE_128)
		{
			unsigned char *code_string = (unsigned char *)render->data;
			zint_symbol *symbol = os_mem_alloc(RAM_TYPE_BUFFER_ON, sizeof(zint_symbol));
			symbol->input_mode = DATA_MODE;
			symbol->symbology = BARCODE_CODE128;
			symbol->output_options = 0;
			symbol->encoded_data = os_mem_alloc(RAM_TYPE_BUFFER_ON, C128_MAX);
			barcode_code128_create(symbol, (unsigned char *)code_string, strlen(code_string));

			short scale = render->width / symbol->width;
			scale = scale <= 1 ? 1 : scale;
			short width = symbol->width * scale;

			gui_render_barcode_struct *render_barcode = os_mem_alloc(RAM_TYPE_BUFFER_ON, sizeof(gui_render_barcode_struct));
			render_barcode->length = width;
			render_barcode->data = symbol->encoded_data;
			render_barcode->data_count = symbol->encoded_data_count;
			render_barcode->scale = scale;
			render_barcode->x = render->x + (render->width - width) / 2;

			render->value = (unsigned int)render_barcode;
			render->clip_left = render_barcode->x;
			render->clip_right = render_barcode->x + width;

			os_mem_free((void *)symbol);
		}
		render = render->next;
	}
}

void gui_display_draw_barcode_clear()
{
	gui_render_struct *render = gui_display_render_frist();
	while (render != NULL)
	{
		if (render->type == TYPE_GUI_DRAW_BAR_CODE_128)
		{
			gui_render_barcode_struct *render_barcode = (gui_render_barcode_struct *)render->value;
			if (render_barcode != NULL)
			{
				if (render_barcode->data != NULL)
				{
					os_mem_free(render_barcode->data);
				}
				os_mem_free((void *)render_barcode);
			}
			render->value = NULL;
		}
		render = render->next;
	}
}

void gui_display_draw_barcode_show_row(unsigned short *frame_buf_row, gui_render_barcode_struct *render_barcode)
{
	const unsigned char *line_list;
	unsigned char is_black = 1;
	short line_width = 0;

	for (short i = 0; i < render_barcode->data_count; i++)
	{
		line_list = barcode_code128_get_line(render_barcode->data[i]);

		for (short j = 0; j < BARCODE_CODE128C_MAX_CHAR && line_list[j] != '\0'; j++)
		{
			line_width = (line_list[j] - '0') * render_barcode->scale;

			for (short k = 0; k < line_width; k++)
			{
				if (is_black)
					*frame_buf_row++ = COLOR_BLACK;
				else
					*frame_buf_row++ = COLOR_WHITE;
			}
			is_black = !is_black;
		}
	}
}

void gui_display_draw_barcode_to_frame(gui_render_struct *render)
{
	short y0 = render->y;
	if (render->y < gui_lib_ctx->y0)
	{
		y0 = gui_lib_ctx->y0;
	}

	short y1 = render->y + render->height - 1;
	if (y1 > gui_lib_ctx->y1)
	{
		y1 = gui_lib_ctx->y1;
	}

	if (y1 - y0 < 0)
	{
		return;
	}

	gui_render_barcode_struct *render_barcode = (gui_render_barcode_struct *)render->value;
	unsigned int buf_offset = UI_CHARGE_XY(render_barcode->x, y0);
	unsigned char *frame_buf = gui_lib_ctx->frame_buffer + buf_offset;
	for (short y = y0; y <= y1; y++)
	{
		gui_display_draw_barcode_show_row(frame_buf, render_barcode);
		frame_buf += gui_lib_ctx->bw;
	}
}

void gui_display_draw_barcode(unsigned char *render_buf, gui_render_struct *render, short y_start, short y_end)
{
	if (render->type == TYPE_GUI_DRAW_BAR_CODE_128 && render->value != 0)
	{
		gui_display_draw_barcode_to_frame(render);
	}
}

