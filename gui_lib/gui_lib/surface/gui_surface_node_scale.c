#include "gui_surface_node_scale.h"
#include "os_mem.h"
#include "debug_info.h"

void gui_surface_node_calculate_scale(gui_scale_struct *gui_scale)
{
	gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);
	gui_scale_item_struct *box_scale = &(gui_scale->box_scale);
	gui_scale_item_struct *node_scale = &(gui_scale->node_scale);

	gui_node_struct *node = gui_scale->node;
	if (node == NULL)
		return;

	float scale;
	float x, y, clip_x, clip_y;
	float width, height, clip_width, clip_height;

	if (FLOAT_EQUAL_ONE(node->scale))
	{
		scale = 1.0f;

		width = node->width;
		height = node->height;

		clip_width = node->clip_width;
		clip_height = node->clip_height;
		clip_x = node->clip_x;
		clip_y = node->clip_y;
	}
	else
	{
		scale = node->scale;

		width = node->width * scale;
		height = node->height * scale;

		clip_width = node->clip_width * scale;
		clip_height = node->clip_height * scale;
		clip_x = node->clip_x * scale;
		clip_y = node->clip_y * scale;
	}

	if (node->draw != NULL)
	{
		if (node->draw->anchor_x == 0)
			x = node->x;
		else
			x = node->x - ANCHOR_CONVERT(FLOAT_TO_INT(width), node->draw->anchor_x);

		if (node->draw->anchor_y == 0)
			y = node->y;
		else
			y = node->y - ANCHOR_CONVERT(FLOAT_TO_INT(height), node->draw->anchor_y);
	}
	else
	{
		x = node->x;
		y = node->y;
	}

	if (FLOAT_EQUAL_ONE(box_scale->scale))
	{
		node_scale->scale = scale;

		node_scale->x = FLOAT_TO_INT(x);
		node_scale->y = FLOAT_TO_INT(y);
		node_scale->width = FLOAT_TO_INT(width);
		node_scale->height = FLOAT_TO_INT(height);

		node_scale->clip_x = FLOAT_TO_INT(clip_x);
		node_scale->clip_y = FLOAT_TO_INT(clip_y);
		node_scale->clip_width = FLOAT_TO_INT(clip_width);
		node_scale->clip_height = FLOAT_TO_INT(clip_height);
	}
	else
	{
		node_scale->scale = box_scale->scale * scale;

		node_scale->x = FLOAT_TO_INT(x * box_scale->scale);
		node_scale->y = FLOAT_TO_INT(y * box_scale->scale);
		node_scale->width = FLOAT_TO_INT(width * box_scale->scale);
		node_scale->height = FLOAT_TO_INT(height * box_scale->scale);

		node_scale->clip_x = FLOAT_TO_INT(clip_x * box_scale->scale);
		node_scale->clip_y = FLOAT_TO_INT(clip_y * box_scale->scale);
		node_scale->clip_width = FLOAT_TO_INT(clip_width * box_scale->scale);
		node_scale->clip_height = FLOAT_TO_INT(clip_height * box_scale->scale);
	}
}

void gui_surface_compose_calculate_scale(gui_scale_struct *gui_scale)
{
	gui_scale_item_struct *node_scale = &(gui_scale->node_scale);
	gui_scale_item_struct *compose_scale = &(gui_scale->compose_scale);

	gui_node_struct *compose = gui_scale->compose;
	if (compose == NULL)
		return;

	if (FLOAT_EQUAL_ONE(node_scale->scale))
	{
		compose_scale->scale = 1.0f;

		compose_scale->x = compose->x;
		compose_scale->y = compose->y;
		compose_scale->width = compose->width;
		compose_scale->height = compose->height;

		compose_scale->clip_width = compose->clip_width;
		compose_scale->clip_height = compose->clip_height;
		compose_scale->clip_x = compose->clip_x;
		compose_scale->clip_y = compose->clip_y;
	}
	else
	{
		compose_scale->scale = node_scale->scale;

		compose_scale->x = FLOAT_TO_INT(compose->x * node_scale->scale);
		compose_scale->y = FLOAT_TO_INT(compose->y * node_scale->scale);
		compose_scale->width = FLOAT_TO_INT(compose->width * node_scale->scale);
		compose_scale->height = FLOAT_TO_INT(compose->height * node_scale->scale);

		compose_scale->clip_width = FLOAT_TO_INT(compose->clip_width * node_scale->scale);
		compose_scale->clip_height = FLOAT_TO_INT(compose->clip_height * node_scale->scale);
		compose_scale->clip_x = FLOAT_TO_INT(compose->clip_x * node_scale->scale);
		compose_scale->clip_y = FLOAT_TO_INT(compose->clip_y * node_scale->scale);
	}
}
