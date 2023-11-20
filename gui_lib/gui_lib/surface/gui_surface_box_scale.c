#include "os_mem.h"
#include "debug_info.h"
#include "gui_surface_box_scale.h"
#include "gui_surface_node_scale.h"

void gui_surface_box_calculate_scale(gui_scale_struct *gui_scale)
{
	gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);
	gui_scale_item_struct *box_scale = &(gui_scale->box_scale);

	gui_box_struct *box = gui_scale->box;
	if (box == NULL)
		return;

	if (FLOAT_EQUAL_ONE(box->scale)) // 减少浮点运算
	{
		box_scale->scale = 1.0f;
		box_scale->width = box->width;
		box_scale->height = box->height;
	}
	else
	{
		box_scale->scale = box->scale;
		box_scale->width = FLOAT_TO_INT(box->width * box_scale->scale);
		box_scale->height = FLOAT_TO_INT(box->height * box_scale->scale);
	}

	if (box->widget != NULL)
	{
		if (box->widget->anchor_x == 0)
			box_scale->x = box->x;
		else
			box_scale->x = box->x - ANCHOR_CONVERT(box_scale->width, box->widget->anchor_x);

		if (box->widget->anchor_y == 0)
			box_scale->y = box->y;
		else
			box_scale->y = box->y - ANCHOR_CONVERT(box_scale->height, box->widget->anchor_y);
	}
	else
	{
		box_scale->x = box->x;
		box_scale->y = box->y;
	}

	if (!FLOAT_EQUAL_ONE(surface_scale->scale))
	{
		box_scale->scale *= surface_scale->scale;

		box_scale->x = FLOAT_TO_INT(box_scale->x * surface_scale->scale);
		box_scale->y = FLOAT_TO_INT(box_scale->y * surface_scale->scale);

		box_scale->width = FLOAT_TO_INT(box_scale->width * surface_scale->scale);
		box_scale->height = FLOAT_TO_INT(box_scale->height * surface_scale->scale);
	}
}
