#include "gui_surface_node.h"
#include "gui_surface_cache.h"
#include "gui_core.h"

static geometry_rect g_full_surface_rect = {
	.x = 0,
	.y = 0,
	.width = LCD_SIZE_WIDTH,
	.height = LCD_SIZE_HEIGHT,
};

gui_node_struct* gui_surface_node_find_by_id(gui_box_struct* box,unsigned short id)
{
	if(box != NULL)
	{
		gui_node_struct* node = box->child;
		while(node != NULL)
		{
			if(node->id > 0 &&  id == node->id)
				return node;
			node = node->brother;
		}
	}
	return NULL;
}

gui_node_struct* gui_surface_node_find_child(gui_node_struct* node,unsigned short id)
{
	while(node != NULL)
	{
		if(node->id > 0 &&  id == node->id)
			return node;
		node = node->child;
	}
	return NULL;
}

gui_node_struct* gui_surface_node_check_clip(gui_box_struct* box, gui_node_struct* node,short width,short height)
{
	gui_widget_struct* widget = box->widget;
	short start_x = node->x;
	short start_y = node->y;
	if(widget->clip)
	{
		if(start_x >= 0)
		{
			node->clip_x = 0;   // start_x; // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
			node->clip_width = (start_x + width > box->width) ? (box->width - start_x) : width;
		}
		else
		{
			node->clip_x = - start_x;   // 0;   // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
			node->clip_width = (start_x + width > box->width) ? box->width : (width - ABS(start_x));
		}

		if(start_y >= 0)
		{
			node->clip_y = 0;   // start_y; // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
			node->clip_height = (start_y + height > box->height) ? (box->height - start_y) : height;
		}
		else
		{
			node->clip_y = - start_y;   // 0;   // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
			node->clip_height = (start_y + height > box->height) ? box->height : (height - ABS(start_y));
		}
		
	}
	else
	{
		node->clip_x = 0;   // start_x;     // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
		node->clip_width = width;

		node->clip_y = 0;   // start_y;     // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
		node->clip_height = height;
	}
	return node;
}

gui_node_struct* gui_surface_node_compose_check_clip(gui_box_struct* box, gui_node_struct* node, gui_node_struct* compose_node, short width, short height)
{
    gui_surface_node_check_clip(box, node, node->width, node->height);

    gui_widget_struct* widget = box->widget;
    if (widget->clip)
    {
        if (compose_node->x >= node->clip_x)
        {
            compose_node->clip_x = 0;
            compose_node->clip_width = ((compose_node->x + width) > (node->clip_x + node->clip_width)) ? (node->clip_width - compose_node->x) : width;
        }
        else
        {
            short start_x = compose_node->x - node->clip_x;
            compose_node->clip_x = -start_x;
            compose_node->clip_width = (start_x + width > (node->clip_x + node->clip_width)) ? node->clip_width : (width - ABS(start_x));
        }

        if (compose_node->y >= node->clip_y)
        {
            compose_node->clip_y = 0;
            compose_node->clip_height = ((compose_node->y + height) > (node->clip_y + node->clip_height)) ? (node->clip_height - compose_node->y) : height;
        }
        else
        {
            short start_y = compose_node->y - node->clip_y;
            compose_node->clip_y = -start_y;
            compose_node->clip_height = (start_y + height > (node->clip_y + node->clip_height)) ? node->clip_height : (height - ABS(start_y));
        }
    }
    else
    {
        compose_node->clip_x = 0;
        compose_node->clip_width = width;

        compose_node->clip_y = 0;
        compose_node->clip_height = height;
    }
    return compose_node;
}

short gui_surface_node_check_x(gui_box_struct* box, unsigned char align, short x, short width)
{
	gui_widget_struct* widget = box->widget;

	if(widget->child_num == 1) //单个兄弟节点
	{
		if(GUI_ALIGN_IS_HCENTER(align))
			return (box->width - width) / 2;
		else if(GUI_ALIGN_IS_RIGHT(align))
			return box->width - width;
		else if(GUI_ALIGN_IS_LEFT(align))
			return 0;
	}
	return x;
}

short gui_surface_node_check_y(gui_box_struct* box,unsigned char align, short y,short height)
{
	gui_widget_struct* widget = box->widget;
	if(widget->child_num == 1) //单个兄弟节点
	{
		if(GUI_ALIGN_IS_VCENTER(align) )
			return (box->height - height) / 2;
		else if(GUI_ALIGN_IS_BOTTOM(align))
			return box->height - height;
		else if(GUI_ALIGN_IS_TOP(align))
			return 0;
	}
	return y;
}


void gui_surface_node_replace_brother(gui_box_struct* box,gui_node_struct* old_node,gui_node_struct* new_node)
{
	gui_node_struct* front_node = gui_surface_cache_find_front(box->child,old_node);
	gui_node_struct* next_node = old_node->brother;

	//gui_surface_cache_remove_nodes(old_node);
	gui_surface_cache_remove_node(old_node);
	if(new_node != NULL)
	{
		if(front_node == NULL)
			box->child = new_node;
		else
			front_node->brother = new_node;
		new_node->brother = next_node;
	}
	else
	{
		if(front_node == NULL)
			box->child = next_node;
		else
			front_node->brother = next_node;
	}
}

void gui_surface_node_replace_child(gui_box_struct* box,gui_node_struct* old_node,gui_node_struct* new_node)
{
	gui_node_struct* front_node = gui_surface_cache_find_front_in_child(box->child,old_node);
	gui_node_struct* next_node = old_node->child;
		
	gui_surface_cache_remove_nodes(old_node);
	if(new_node != NULL)
	{
		if(front_node == NULL)
			box->child = new_node;
		else
			front_node->child = new_node;
		new_node->child = next_node;
	}
	else
	{
		if(front_node == NULL)
			box->child = next_node;
		else
			front_node->child = next_node;
	}
}


void gui_surface_node_get_rect_in_screen(gui_surface_struct* surface,gui_box_struct* box,gui_node_struct* node,geometry_rect* rect)
{
	rect->x = surface->x + box->x + node->x + node->clip_x;     // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	rect->y = surface->y + box->y + node->y + node->clip_y;     // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	rect->width = node->clip_width;
	rect->height = node->clip_height;
}

void gui_surface_node_compose_get_rect_in_screen(gui_surface_struct* surface,gui_box_struct* box,gui_node_struct* node,gui_node_struct* compose,geometry_rect* rect)
{
	rect->x = surface->x + box->x + node->x + compose->x + compose->clip_x;   // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	rect->y = surface->y + box->y + node->y + compose->y + compose->clip_y;   // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	rect->width = compose->clip_width;                              // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	rect->height = compose->clip_height;                            // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
}


void gui_surface_node_get_rect_in_screen_with_scale(gui_scale_struct* gui_scale, geometry_rect* rect)
{
	gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);
	gui_scale_item_struct *box_scale = &(gui_scale->box_scale);
	gui_scale_item_struct *node_scale = &(gui_scale->node_scale);

	rect->x = surface_scale->x + surface_scale->clip_x + box_scale->x + node_scale->x + node_scale->clip_x;
	rect->y = surface_scale->y + surface_scale->clip_y + box_scale->y + node_scale->y + node_scale->clip_y;
	rect->width = node_scale->clip_width;
	rect->height = node_scale->clip_height;
}

void gui_surface_node_compose_get_rect_in_screen_with_scale(gui_scale_struct* gui_scale, geometry_rect* rect)
{
	gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);
	gui_scale_item_struct *box_scale = &(gui_scale->box_scale);
	gui_scale_item_struct *node_scale = &(gui_scale->node_scale);
	gui_scale_item_struct *compose_scale = &(gui_scale->compose_scale);

	rect->x = surface_scale->x + surface_scale->clip_x + box_scale->x + node_scale->x + compose_scale->x + compose_scale->clip_x;
	rect->y = surface_scale->y + surface_scale->clip_y + box_scale->y + node_scale->y + compose_scale->y + compose_scale->clip_y;
	rect->width = compose_scale->clip_width;
	rect->height = compose_scale->clip_height;
}

unsigned char gui_surface_node_check_rect_in_surface(gui_scale_struct* gui_scale, geometry_rect* rect)
{
	gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);
	g_full_surface_rect.x = surface_scale->x + surface_scale->clip_x;
	g_full_surface_rect.y = surface_scale->y + surface_scale->clip_y;
	g_full_surface_rect.width = surface_scale->clip_width;
	g_full_surface_rect.height = surface_scale->clip_height;
    return check_rect_intersect_rect((geometry_rect*)&g_full_surface_rect,rect);
}
