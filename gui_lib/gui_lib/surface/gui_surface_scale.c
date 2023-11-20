#include "os_mem.h"
#include "debug_info.h"
#include "gui_surface_scale.h"
#include "gui_surface_box_scale.h"

void gui_surface_calculate_scale(gui_scale_struct *gui_scale)
{
	gui_surface_struct *surface = gui_scale->surface;
	gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);
	if (surface == NULL || surface_scale == NULL)
		return;

	//SYS_DEBUG("gui_surface_calculate_scale surface->scale=%f", surface->scale);

	surface_scale->width = LCD_SIZE_WIDTH;
	surface_scale->height = LCD_SIZE_HEIGHT;
	surface_scale->x = surface->x;
	surface_scale->y = surface->y;

	if (FLOAT_EQUAL_ONE(surface->scale))
	{
		surface_scale->scale = 1.0f;

		surface_scale->clip_width = LCD_SIZE_WIDTH;
		surface_scale->clip_height = LCD_SIZE_HEIGHT;
		surface_scale->clip_x = 0;
		surface_scale->clip_y = 0;
	}
	else
	{
		//SYS_DEBUG("gui_surface_calculate_scale !1.0");

		surface_scale->scale = surface->scale;

		surface_scale->clip_width = FLOAT_TO_INT(LCD_SIZE_WIDTH * surface->scale);
		surface_scale->clip_height = FLOAT_TO_INT(LCD_SIZE_HEIGHT * surface->scale);
		surface_scale->clip_x = FLOAT_TO_INT((surface_scale->width - surface_scale->clip_width) / 2);
		surface_scale->clip_y = FLOAT_TO_INT((surface_scale->height - surface_scale->clip_height) / 2);
	}
}
