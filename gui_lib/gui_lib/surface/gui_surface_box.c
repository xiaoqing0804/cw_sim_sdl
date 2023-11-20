#include "gui_surface_box.h"
#include "gui_surface_cache.h"
#include "gui_core.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_image_number.h"
#include "gui_surface_box_image_progress.h"
#include "gui_surface_box_textbox.h"
#include "gui_surface_box_pointer.h"
#include "gui_surface_box_qrcode.h"
#include "gui_surface_box_barcode.h"
#include "gui_surface_control.h"


#include "gui_surface_layout_listview.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_layout_scroll.h"
#include "gui_surface_layout_gridview.h"
#include "gui_surface_box_layout_item.h"
#include "gui_surface_box_layout_cellular.h"
#include "gui_surface_box_scale.h"
#include "gui_surface_node_scale.h"


static void gui_surface_box_parse(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;

    //SYS_DEBUG("gui: surface_box_parse, type=%d", widget->type);
	switch(widget->type)
	{
		case TYPE_GUI_CONTROL_IMAGE:
			gui_surface_box_image_create(box);
			break;

		case TYPE_GUI_CONTROL_LABEL:
			gui_surface_box_label_create(box);
			break;

        case TYPE_GUI_CONTROL_POINTER:
            gui_surface_box_pointer_create(box);
            break;

        case TYPE_GUI_CONTROL_CANVAS:
            gui_surface_box_canvas_create(box);
            break;

		case TYPE_GUI_CONTROL_LAYOUT_ITEM:
            gui_surface_box_layout_item_create(box);
            break;

		case TYPE_GUI_CONTROL_LAYOUT_CELL:
			gui_surface_box_layout_cellular_create(box);
			break;

		case TYPE_GUI_CONTROL_IMAGE_LIST:
            gui_surface_box_layout_item_create(box);
            break;

		case TYPE_GUI_CONTROL_IMAGE_NUMBER:
            gui_surface_box_image_number_create(box);
            break;

		case TYPE_GUI_CONTROL_IMAGE_PROGRESS:
            gui_surface_box_image_progress_create(box);
            break;

		case TYPE_GUI_CONTROL_PROGRESS_BAR:
			gui_surface_box_image_progress_create(box);
			break;

		case TYPE_GUI_CONTROL_QR_CODE:
			gui_surface_box_qrcode_create(box);
			break;

		case TYPE_GUI_CONTROL_BAR_CODE_128C:
			gui_surface_box_barcode_create(box);
			break;

		default:
			gui_surface_control_parse(box);
			break;
	}

}


//屏幕数组转化---------------------------------------------------------------------
gui_box_struct* gui_surface_box_create(gui_surface_struct* surface,const gui_widget_struct* widget)
{
	gui_box_struct* box = gui_surface_cache_add_box();
	box->id = widget->id;
	box->type = widget->type;
	box->widget = (gui_widget_struct*)widget;

	box->x = widget->x;
	box->y = widget->y;
	box->width = widget->width;
	box->height = widget->height;
	box->visible = widget->visible;
	box->rotate = widget->rotate;
	box->fix = widget->fix;
	box->order = widget->order;
	box->scale = GUI_INIT_SCALE(widget->scale);

	gui_surface_box_parse(box);
	
	//gui_surface_box_arrange_x(box);
	//gui_surface_box_arrange_y(box);
	return box;
}

void gui_surface_box_arrange_x(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	if(GUI_ALIGN_IS_HCENTER(widget->align))
		box->x =  (LCD_SIZE_WIDTH - box->width) / 2;
	else if(GUI_ALIGN_IS_RIGHT(widget->align))
		box->x = LCD_SIZE_WIDTH - box->width;
	else if(GUI_ALIGN_IS_LEFT(widget->align))
		box->x = 0;
}

void gui_surface_box_arrange_y(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	if(GUI_ALIGN_IS_HCENTER(widget->align))
		box->y =  (LCD_SIZE_WIDTH - box->width) / 2;
	else if(GUI_ALIGN_IS_RIGHT(widget->align))
		box->y = LCD_SIZE_WIDTH - box->width;
	else if(GUI_ALIGN_IS_LEFT(widget->align))
		box->y = 0;
}


void gui_surface_box_exit(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;

	switch(widget->type)
	{
		default:
            gui_surface_control_exit(box);
            break;
	}
}

//界面改变--------------------------------------------------------------------------

void gui_surface_box_change_x(gui_box_struct* box,short x)
{
	if(box == NULL)
		return;
	
	box->x = x;
}

void gui_surface_box_change_y(gui_box_struct* box,short y)
{
	if(box == NULL)
		return;
	
	box->y = y;
}

void gui_surface_box_change_xy(gui_box_struct* box,short x,short y)
{
	if(box == NULL)
		return;
	
    box->x = x;
	box->y = y;
}

void gui_surface_box_change_clip(gui_box_struct* box,short clip_x,short clip_y,short clip_width,short clip_height)
{
	if(box != NULL)
	{
		gui_node_struct* node = box->child;
		while(node != NULL)
		{
			node->clip_x =	clip_x;
			node->clip_width = clip_width;

			node->clip_y = clip_y;
			node->clip_height = clip_height;

			//嵌套的node
			gui_node_struct* compose_node = node->child;
			while(compose_node != NULL)
			{
				compose_node->clip_x =	clip_x;
				compose_node->clip_width = clip_width;

				compose_node->clip_y = clip_y;
				compose_node->clip_height = clip_height;

				compose_node = compose_node->child;
			}

			node = node->brother;
		}
	}
}

void gui_surface_box_change_node_clip(gui_box_struct* box,short node_id,short clip_x,short clip_y,short clip_width,short clip_height)
{
    if(box != NULL && node_id != 0)
    {
        gui_node_struct* node = box->child;
        while(node != NULL)
        {
            if (node->id == node_id) {
                node->clip_x =  clip_x;
                node->clip_width = clip_width;
                
                node->clip_y = clip_y;
                node->clip_height = clip_height;
                break;
            }
            node = node->brother;
        }
    }
}

void gui_surface_box_change_width(gui_box_struct* box,short width)
{
	if(box == NULL)
		return;
	
	box->width = width;
	box->update = 1;
}

void gui_surface_box_change_height(gui_box_struct* box,short height)
{
	if(box == NULL)
		return;
	
	box->height = height;
	box->update = 1;
}

void gui_surface_box_change_visible(gui_box_struct* box,unsigned char visible)
{
	if(box == NULL)
		return;
	
	box->visible = visible;
}


//刷新排版用
void gui_surface_box_commit(gui_box_struct* box)
{
	if(box == NULL)
		return;
	
	gui_widget_struct* widget = box->widget;
	switch(widget->type)
	{
		case TYPE_GUI_CONTROL_IMAGE:
			gui_surface_box_image_arrange_refresh(box);
			break;
	}
}

void gui_surface_box_add_node(gui_box_struct* box, gui_node_struct* node)
{
    if (box == NULL) return;

    if (box->child == NULL) {
        box->child = node;
    }
    else {
        gui_node_struct* pre_node = box->child;
        while(pre_node->brother != NULL) {
            pre_node = pre_node->brother;
        }
        pre_node->brother = node;
    }
    node->brother = NULL;
}

gui_node_struct* gui_surface_box_find_node(gui_box_struct* box,unsigned short id)
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

void gui_surface_box_get_rect_in_screen(gui_surface_struct* surface,gui_box_struct* box,geometry_rect* rect)
{
	if(box == NULL || surface == NULL)
		return;
	rect->x = surface->x + box->x;
	rect->y = surface->y + box->y;
	rect->width = box->width;
	rect->height = box->height;
}

// Taylor.Le, +
void gui_surface_box_get_geometry_rect(gui_surface_struct *surface, gui_box_struct* box, geometry_rect* rect)
{
	short x, y;

	if (box == NULL || rect == NULL) {
		return;
	}

	if (box->widget != NULL) {
		if (box->widget->anchor_x == 0)
			x = box->x;
		else
			x = box->x - ANCHOR_CONVERT(box->width, box->widget->anchor_x);

		if (box->widget->anchor_y == 0)
			y = box->y;
		else
			y = box->y - ANCHOR_CONVERT(box->height, box->widget->anchor_y);
	}
	else
	{
		x = box->x;
		y = box->y;
	}

	rect->x = (surface == NULL) ? x : (surface->x + surface->clip_x + x);
	rect->y = (surface == NULL) ? y : (surface->y + surface->clip_y + y);
	rect->width = box->width;
	rect->height = box->height;
}
unsigned int gui_surface_box_contain_xy(gui_surface_struct *surface, gui_box_struct* box, short x, short y)
{
	geometry_rect box_rect = {0};
	gui_surface_box_get_geometry_rect(surface, box, &box_rect);
	if (check_rect_contain_point_xy(&box_rect, x, y)) {
		return 1;
	}
	return 0;
}

