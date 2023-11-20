#include "gui_surface_layout_ring_center.h" 
#include "gui_surface_layout_ring_center_config.h" 
#include "system_util_math.h"
#include "gui_surface_node.h"
#include "gui_window_history.h"
#include "app_more_info/app_window_moreinfo.h"
#include "data_common.h"

#if 0   // 废弃
/*******************************************
**
**对ring_center进行排版，移动
**
********************************************/

#define LAYOUT_RING_SWITCH_MOVE_COUNT 5
#define LAYOUT_RING_SWITCH_MOVE_TIME  (20)

static unsigned int g_layout_ring_center_switch_timer_id = 0;
static short g_layout_ring_center_switch_curr_angle = 0;
static short g_layout_ring_center_switch_next_angle = 0;
static short g_layout_ring_center_switch_step_angle = 0;
static short g_layout_ring_center_switch_move_count = 0;

/*******************************数据接口************************************/

short gui_surface_layout_ring_center_get_curr_angle(gui_surface_struct* surface,short index)
{
	const gui_ring_center_position_struct* pos = gui_surface_layout_ring_center_config_get(index);
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	return gui_surface_layout_ring_center_adjust_angle(pos->angle + ring_center->offset_x);
}

short gui_surface_layout_ring_center_get_offset_angle(gui_surface_struct* surface)
{
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	return gui_surface_layout_ring_center_adjust_angle(ring_center->offset_x);
}

short gui_surface_layout_ring_center_adjust_angle(short angle)
{
	short result_angle = angle % 360;
	return (result_angle < 0) ? (360 + result_angle) : result_angle;
}

int gui_touch_layout_ring_center_adjust_right_angle(int speed_offset_angle)
{
	int curr_angle = gui_surface_layout_ring_center_adjust_angle(speed_offset_angle);
	for(unsigned char i = 0; i < gui_surface_layout_ring_center_config_real_count(); i++)
	{
		const gui_ring_center_position_struct* curr_pos = gui_surface_layout_ring_center_config_get(i);
		const gui_ring_center_position_struct* next_pos = gui_surface_layout_ring_center_config_get(i+1);
		if(curr_angle >= curr_pos->angle && curr_angle < next_pos->angle)
		{
			short to_offset_angle;
			if(curr_angle >= (curr_pos->angle + next_pos->angle)/2)
				to_offset_angle = next_pos->angle - curr_angle;
			else
				to_offset_angle = curr_pos->angle - curr_angle;
			return speed_offset_angle + to_offset_angle;
		}
	}
	return 0;
}


short gui_surface_layout_ring_center_get_default_angle(gui_surface_struct* surface,short index)
{
	const gui_ring_center_position_struct* pos = gui_surface_layout_ring_center_config_get(index);
	return (pos != NULL) ? pos->angle : -1;
}


short gui_surface_layout_ring_center_get_item_id(gui_surface_struct* surface,short index)
{
	gui_box_struct* box = gui_surface_layout_ring_center_get_item(surface,index);
	return (box != NULL) ? box->id : 0;
}

gui_box_struct* gui_surface_layout_ring_center_get_item(gui_surface_struct* surface,short index)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			if(count++ == index)
				return box;
		}
		box = box->brother;
	}
	return NULL;
}


//点击在列表的哪个条目上,返回条目编号
short gui_surface_layout_ring_center_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point)
{
    if(application_get_moreinfo_tyep()==MOREINFO_WINDOW_STYLE_KALEIDOSCOPE)
    {
        gui_layout_cellular_struct* cellular = &surface->layout.cellular;
        gui_box_struct* box = surface->child;

        geometry_rect rect_box;
        short count = 0;
        while(box != NULL)
        {
            if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
            {
                rect_box.x = box->x;
                rect_box.y = box->y;
                rect_box.width = cellular->diameter;
                rect_box.height = cellular->diameter;
                if(check_rect_contain_point_xy(&rect_box,touch_point->x,touch_point->y))
                    return count;
                count++;
            }
            box = box->brother;
        }
        return -1;
    }
    else
    {
        gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
        geometry_rect rect_box;
        rect_box.x = ring_center->touch_x;
        rect_box.y = ring_center->touch_y;
        rect_box.width = ring_center->touch_width;
        rect_box.height = ring_center->touch_height;
        if(check_rect_contain_point_xy(&rect_box,touch_point->x,touch_point->y))
        {
            return ring_center->index;
        }
        return -1;
    }

}


/*******************************操作接口************************************/

//根据排版类型，进行排版
void gui_surface_layout_ring_center_arrange(gui_surface_struct* surface)
{
	const gui_layout_ring_center_struct* layout_config = surface->screen->layout_config;
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	ring_center->offset_x = 0;
	ring_center->offset_y = 0;
	ring_center->last_offset_x = 0;
	ring_center->last_offset_y = 0;
	ring_center->index = 0;
	ring_center->id = 0;
	ring_center->diameter = layout_config->diameter;
	ring_center->touch_x = layout_config->touch_x;
	ring_center->touch_y = layout_config->touch_y;
	ring_center->touch_width = layout_config->touch_width;
	ring_center->touch_height = layout_config->touch_height;
	ring_center->postion_list = layout_config->postion_list;
	ring_center->postion_list_num = layout_config->postion_list_num;
	ring_center->step_angle = layout_config->step_angle;
	
	gui_surface_layout_ring_center_init(surface);
	gui_surface_layout_ring_center_commit_position(surface);
	gui_surface_layout_ring_center_check_switch_item(surface);
}

void gui_surface_layout_ring_center_init(gui_surface_struct* surface)
{
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	gui_box_struct* box = surface->child;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			box->width = ring_center->diameter;
			box->height = ring_center->diameter;
		}
		box = box->brother;
	}
	gui_surface_layout_ring_center_config_set(ring_center->postion_list,ring_center->postion_list_num);
}

//对排版中的子元素，使用指定的偏移
void gui_surface_layout_ring_center_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y)
{
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	ring_center->offset_x = layout_offset_x;
	gui_surface_layout_ring_center_commit_position(surface);
	gui_surface_layout_ring_center_check_switch_item(surface);
}

//对排版中的子元素，进行指定的偏移
void gui_surface_layout_ring_center_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y)
{
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	ring_center->offset_x = (ring_center->offset_x + move_offset_x);
	gui_surface_layout_ring_center_commit_position(surface);
	gui_surface_layout_ring_center_check_switch_item(surface);
}

void gui_surface_layout_ring_center_move_end(gui_surface_struct* surface)
{
}

void gui_surface_layout_ring_center_exit()
{
	if(g_layout_ring_center_switch_timer_id > 0)
	{
		application_stop_user_timer(g_layout_ring_center_switch_timer_id);
		g_layout_ring_center_switch_timer_id = 0;
	}
}


/*****************************************************切换条目*******************************************************/


void gui_surface_layout_ring_center_check_switch_item(gui_surface_struct* surface)
{
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			short curr_angle = gui_surface_layout_ring_center_get_curr_angle(surface,count);
			if((curr_angle >= 0 && curr_angle <= ring_center->step_angle/2) || (curr_angle >= 360-ring_center->step_angle/2 && curr_angle <= 360))
			{
				if(box->id != ring_center->id )
				{
					ring_center->index = count;
					ring_center->id = box->id;
					gui_surface_layout_ring_center_show_item(surface,count);
				}
				break;
			}
			count++;
		}
		box = box->brother;
	}

}


void gui_surface_layout_ring_center_show_curr_item(gui_surface_struct* surface)
{
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	gui_box_struct* box = surface->child;
	short count = 0;
	//SYS_DEBUG("gui_surface_layout_ring_center_show_curr_item_BOX_NULL");
	while(box != NULL)
	{
		//SYS_DEBUG("gui_surface_layout_ring_center_show_curr_item");
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			//SYS_DEBUG("TYPE_GUI_CONTROL_LAYOUT_CELL");
			short curr_angle = gui_surface_layout_ring_center_get_curr_angle(surface,count);
			if((curr_angle >= 0 && curr_angle <= ring_center->step_angle/2) || (curr_angle >= 360-ring_center->step_angle/2 && curr_angle <= 360))
			{
				//SYS_DEBUG("gui_surface_layout_ring_center_show_item");
				gui_surface_layout_ring_center_show_item(surface,count);
				break;
			}
			count++;
		}
		box = box->brother;
	}

}


void gui_surface_layout_ring_center_show_item(gui_surface_struct* surface,short item_index)
{
	gui_box_struct* box = gui_surface_layout_ring_center_get_item(surface,item_index);
	const gui_window_struct* top_window = gui_window_history_get_top_window();
	if(top_window != NULL)
	{
		gui_layout_value_struct event = 
		{
			.ring_center.index = item_index,
			.ring_center.id = box->id,
		};
		if(top_window->layout_value_changed)
		{
			top_window->layout_value_changed(&event);
		}
	}
}

static void gui_surface_layout_ring_center_switch_timer(unsigned int timer, void* param)
{
	application_stop_user_timer(g_layout_ring_center_switch_timer_id);
	g_layout_ring_center_switch_timer_id = 0;

	gui_surface_struct* surface = (gui_surface_struct*)param;
	if(surface->screen->type != TYPE_GUI_LAYOUT_RING_CENTER)
		return;

	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;

	g_layout_ring_center_switch_move_count++;
	if(g_layout_ring_center_switch_move_count < LAYOUT_RING_SWITCH_MOVE_COUNT)
	{
		ring_center->offset_x = -(g_layout_ring_center_switch_curr_angle + g_layout_ring_center_switch_move_count * g_layout_ring_center_switch_step_angle ) % 360;
		g_layout_ring_center_switch_timer_id = application_start_user_timer(LAYOUT_RING_SWITCH_MOVE_TIME, gui_surface_layout_ring_center_switch_timer, surface);
	}
	else
	{
		ring_center->offset_x = -(g_layout_ring_center_switch_next_angle) % 360;
		g_layout_ring_center_switch_move_count = 0;
	}
	gui_surface_layout_ring_center_commit_position(surface);
	gui_surface_layout_ring_center_check_switch_item(surface);
	gui_surface_commit();
}

void gui_surface_layout_ring_center_switch_to_item(gui_surface_struct* surface, short curr_index, short item_index)
{
	if(g_layout_ring_center_switch_timer_id > 0)
		return;
	application_stop_user_timer(g_layout_ring_center_switch_timer_id);
	g_layout_ring_center_switch_curr_angle = 0;
	g_layout_ring_center_switch_next_angle = 0;
	g_layout_ring_center_switch_step_angle = 0;
	g_layout_ring_center_switch_move_count = 1;

	curr_index = gui_surface_layout_ring_center_config_check_index(curr_index);
	item_index = gui_surface_layout_ring_center_config_check_index(item_index);
	
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	if(item_index > curr_index)
		g_layout_ring_center_switch_step_angle = ring_center->step_angle / LAYOUT_RING_SWITCH_MOVE_COUNT; 
	else if(item_index < curr_index)	
		g_layout_ring_center_switch_step_angle = -ring_center->step_angle / LAYOUT_RING_SWITCH_MOVE_COUNT;
	else
		g_layout_ring_center_switch_step_angle = 0;

	const gui_ring_center_position_struct* curr_pos = gui_surface_layout_ring_center_config_get(curr_index);
	g_layout_ring_center_switch_curr_angle = curr_pos->angle % 360;
	
	const gui_ring_center_position_struct* next_pos = gui_surface_layout_ring_center_config_get(item_index);
	g_layout_ring_center_switch_next_angle = next_pos->angle % 360;
	
	ring_center->offset_x = -(g_layout_ring_center_switch_curr_angle + g_layout_ring_center_switch_move_count * g_layout_ring_center_switch_step_angle ) % 360;
	gui_surface_layout_ring_center_commit_position(surface);
	gui_surface_layout_ring_center_check_switch_item(surface);

	g_layout_ring_center_switch_timer_id = application_start_user_timer(LAYOUT_RING_SWITCH_MOVE_TIME, gui_surface_layout_ring_center_switch_timer, surface);
}


/*****************************************************计算旋转的位置*******************************************************/

//得到图片的大小
static short gui_surface_layout_ring_center_get_zoom(gui_box_struct* box,short curr_angle,const gui_ring_center_position_struct* curr_pos,const gui_ring_center_position_struct* next_pos)
{
	gui_node_struct* node = box->child;
	picture_info_struct* org_picture = (picture_info_struct*)node->data;
	short zoom = 0;
	if(curr_angle >= (curr_pos->angle + next_pos->angle) / 2)
	{
		if(org_picture->width != next_pos->zoom)
			zoom = next_pos->zoom;
	}
	else
	{
		if(org_picture->width != curr_pos->zoom)
			zoom = curr_pos->zoom;
	}
	return zoom;
}

static void gui_surface_layout_ring_center_compute(gui_box_struct* box,short curr_angle,const gui_ring_center_position_struct* curr_pos,const gui_ring_center_position_struct* next_pos)
{
	gui_widget_struct* widget = box->widget;
	gui_node_struct* node = box->child;
	short zoom = gui_surface_layout_ring_center_get_zoom(box,curr_angle,curr_pos,next_pos);
	if(zoom > 0)
	{
		//换不同的图片
		const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children;
		const picture_info_struct* picture = (const picture_info_struct*)(*picture_arr);
		for(unsigned char j = 0; j < widget->child_num; j++)
		{
			if(picture->width == zoom)
			{
				node->data = (void*)picture;
				node->x = (box->width - picture->width) / 2;
				node->y = (box->height - picture->height) / 2;
				gui_surface_node_check_clip(box, node, picture->width, picture->height);
				break;
			}
			picture_arr++;
			picture = (const picture_info_struct*)(*picture_arr);
		}						
	}
	else
	{
		//换回原来的图片
		picture_info_struct* org_picture = (picture_info_struct*)node->data;
		node->x = (box->width - org_picture->width) / 2;
		node->y = (box->height - org_picture->height) / 2;
		gui_surface_node_check_clip(box, node, org_picture->width, org_picture->height);
	}

	//得到圆心位置的位置
	short center_x = (next_pos->x - curr_pos->x) * (curr_angle - curr_pos->angle) / (next_pos->angle - curr_pos->angle);
	short center_y = (next_pos->y - curr_pos->y) * (curr_angle - curr_pos->angle) / (next_pos->angle - curr_pos->angle);
	box->x = curr_pos->x + center_x - box->width / 2;
	box->y = curr_pos->y + center_y - box->height / 2;
	
}


//提交位置偏移
//拿到偏移的角度后，计算线性比例得到位置
void gui_surface_layout_ring_center_commit_position(gui_surface_struct* surface)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			short curr_angle = gui_surface_layout_ring_center_get_curr_angle(surface,count);
			for(unsigned char i = 0; i < gui_surface_layout_ring_center_config_real_count(); i++)
			{
				//在两个角度中间，线性计算位置
				const gui_ring_center_position_struct* curr_pos = gui_surface_layout_ring_center_config_get(i);
				const gui_ring_center_position_struct* next_pos = gui_surface_layout_ring_center_config_get(i+1);
				if(curr_angle >= curr_pos->angle && curr_angle < next_pos->angle)
				{
					gui_surface_layout_ring_center_compute(box,curr_angle,curr_pos,next_pos);
					break;		
				}
			}
			count++;
		}
		box = box->brother;
	}
}
#endif


