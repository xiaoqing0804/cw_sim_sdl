#include "gui_surface_box_pointer.h"
#include "gui_surface_cache.h"
#include "math.h"

#include "debug_info.h"

#define MY_PI   (-3.1415926f)

void gui_surface_box_pointer_arrange(gui_node_struct* node)
{
    gui_pointer_struct* pointer = node->data;
    float angle;
    float cos;
    float sin;
    int   cx = node->x + node->width/2;
    int   cy = node->y + node->height/2;

    if (pointer->type == TYPE_GUI_DRAW_POINTER_LINE_360) {
        // [0 ~ 3600) 为了保留一位小数，初始角度放大十倍.... 
        angle = node->value * MY_PI / 1800;
    }
    else {
        // [0 ~ 60) => [0 ~ 360)
        angle = node->value * 60 * MY_PI / 1800;
    }
    cos = cosf(angle);
    sin = sinf(angle);

    if (pointer->type == TYPE_GUI_DRAW_POINTER_LINE_60 || pointer->type == TYPE_GUI_DRAW_POINTER_LINE_360) {
        // for draw line
        short* line_pos = pointer->shape.line.position;
        if (line_pos != NULL) {
            line_pos[0] = cx*10-5 + 10*pointer->hilt_lenth*sin;
            line_pos[1] = cy*10-5 + 10*pointer->hilt_lenth*cos;
            line_pos[2] = cx*10+5 - 10*pointer->hand_lenth*sin;
            line_pos[3] = cy*10+5 - 10*pointer->hand_lenth*cos;
            //SYS_DEBUG("gui: P0(%d, %d), P1(%d, %d)", line_pos[0], line_pos[1], line_pos[2], line_pos[3]);
        }
    }

#if 1  // 20230907 Taylor.Le, 新的缩放机制下，没有计算剪切区，所以不以指针方向计算剪切区!!!!
        node->clip_width = (short)node->width;
        node->clip_height = (short)node->height;
        node->clip_x = (short)node->x;
        node->clip_y = (short)node->y;
#else
    if (angle >= MY_PI / 2 && angle < 0)
    {
        node->clip_width = (short)(-(pointer->hand_lenth+pointer->hilt_lenth) * sin + pointer->hand_width * cos) + 1;
        node->clip_height = (short)((pointer->hand_lenth+pointer->hilt_lenth) * cos - pointer->hand_width * sin) + 1;
        node->clip_x = cx - ((short)(-pointer->hilt_lenth * sin + (pointer->hand_width / 2) * cos) + 1);
        node->clip_y = cy - ((short)(pointer->hand_lenth * cos - (pointer->hand_width / 2) * sin) + 1);
    }
    else if (angle >= MY_PI && angle < MY_PI / 2)
    {
        node->clip_width = (short)(-(pointer->hand_lenth+pointer->hilt_lenth) * sin - pointer->hand_width * cos) + 1;
        node->clip_height = (short)(-(pointer->hand_lenth+pointer->hilt_lenth) * cos - pointer->hand_width * sin) + 1;
        node->clip_x = cx - ((short)(-pointer->hilt_lenth * sin - (pointer->hand_width / 2) * cos) + 1);
        node->clip_y = cy - ((short)(-pointer->hilt_lenth * cos - (pointer->hand_width / 2) * sin) + 1);
    }
    else if (angle >= 3 * MY_PI / 2 && angle < MY_PI)
    {
        node->clip_width = (short)((pointer->hand_lenth+pointer->hilt_lenth) * sin - pointer->hand_width * cos) + 1;
        node->clip_height = (short)(-(pointer->hand_lenth+pointer->hilt_lenth) * cos + pointer->hand_width * sin) + 1;
        node->clip_x = cx - ((short)((pointer->hand_lenth) * sin - (pointer->hand_width / 2) * cos) + 1);
        node->clip_y = cy - ((short)(-pointer->hilt_lenth * cos + (pointer->hand_width / 2) * sin) + 1);
    }
    else
    {
        node->clip_width = (short)((pointer->hand_lenth+pointer->hilt_lenth) * sin + pointer->hand_width * cos) + 1;
        node->clip_height = (short)((pointer->hand_lenth+pointer->hilt_lenth) * cos + pointer->hand_width * sin) + 1;
        node->clip_x = cx - ((short)(pointer->hand_lenth * sin + (pointer->hand_width / 2) * cos) + 1);
        node->clip_y = cy - ((short)(pointer->hand_lenth * cos + (pointer->hand_width / 2) * sin) + 1);
    }
    //node->x = 0;
    //node->y = 0;
    //SYS_DEBUG("pointer %d: rect{%d, %d, %d, %d}", box->id, node->clip_x, node->clip_y, node->clip_width, node->clip_height);
#endif
}

void gui_surface_box_pointer_create(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	if(widget->child_num > 0)
	{
        gui_pointer_struct* pointer = (gui_pointer_struct*)widget->children;
		gui_node_struct* node = gui_surface_cache_add_node();
        node->id   = pointer->id;
		node->type = TYPE_GUI_DRAW_POINTER;
        node->x      = 0;//box->x;
        node->y      = 0;//box->y;
		node->width  = box->width;
		node->height = box->height;
        node->scale = GUI_INIT_SCALE(pointer->scale);

		node->value = pointer->value;
        node->draw = pointer;
		node->data = (void*)widget->children;   // gui_pointer_struct*
		gui_surface_box_pointer_arrange(node);
        box->child   = node;
	}
	else
	{
		box->child = NULL;
	}
}

void gui_surface_box_pointer_change(gui_box_struct* box, unsigned int value)
{
	if(box == NULL)
		return;
	
	gui_node_struct* node = box->child;
	if(node == NULL)
		return;
	
    node->value = value;
	gui_surface_box_pointer_arrange(node);
}

