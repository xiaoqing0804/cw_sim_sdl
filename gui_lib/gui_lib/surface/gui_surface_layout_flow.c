#include "gui_surface_layout_flow.h"
#include "debug_info.h"
#include "hal_lcd_area.h"
#include "system_util_math.h"
#include "gui_surface_box_layout_item.h"
#include "gui_surface_cache.h"
#include "gui_window_history.h"
#include "gui_touch_layout_rebound.h"

#include "gui_surface_layout.h"
/*******************************************
**
**对flowview进行排版，移势
**
********************************************/




/*******************************数据接口************************************/

short gui_surface_layout_flowview_get_item_id(gui_surface_struct* surface,short index)
{
	gui_box_struct* box = gui_surface_layout_flowview_get_item(surface,index);
	return (box != NULL) ? box->id : 0;
}

gui_box_struct* gui_surface_layout_flowview_get_item(gui_surface_struct* surface,short index)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(!box->fix && box->visible)
		{
			if(count++ == index)
				return box;
		}
		box = box->brother;
	}
	return NULL;
}

short gui_surface_layout_flowview_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point)
{
	//gui_layout_flow_struct* flow = &surface->layout.flow;
	gui_box_struct* box = surface->child;
	geometry_rect rect_box;
	short count = 0;
	while(box != NULL)
	{
		if(!box->fix && box->visible)
		{
			rect_box.x = box->x;
			rect_box.y = box->y;
			rect_box.width = box->width;
			rect_box.height = box->height;
			if(check_rect_contain_point_xy(&rect_box,touch_point->x,touch_point->y))
				return count;
			count++;
		}
		box = box->brother;
	}		
	return -1;

}


/*******************************操作接口************************************/

//根据排版类型，进行排牿
void gui_surface_layout_flowview_arrange(gui_surface_struct* surface)
{
	const gui_layout_flow_struct* flow_config = surface->screen->layout_config;
	gui_layout_flow_struct* flow = &surface->layout.flow;
    memset(flow, 0, sizeof(gui_layout_flow_struct));
	flow->height = flow_config->height;
	
	flow->scroll = flow_config->scroll;
	flow->can_swipe = flow_config->can_swipe;

	gui_surface_layout_flowview_commit_position(surface);
}

short gui_surface_layout_flowview_get_progress(gui_surface_struct* surface)
{
	gui_layout_flow_struct* flow = &surface->layout.flow;
	short progress;
    if (flow->height <= LCD_SIZE_HEIGHT) {   // 20220519 Taylor.Le,  avoid div0
        progress = 100;
    }
    else {
        progress = ABS(flow->offset_y) * 100 / (flow->height - LCD_SIZE_HEIGHT);
    }
	return math_range(progress, 0, 100);
}

//对排版中的子元素，使用指定的偏移
void gui_surface_layout_flowview_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y)
{
	gui_layout_flow_struct* flow = &surface->layout.flow;
	int offset_x = flow->offset_x;
	int offset_y = flow->offset_y;
	flow->offset_x = layout_offset_x;
	flow->offset_y = layout_offset_y;
	flow->move_x =  flow->offset_x - offset_x;
	flow->move_y =  flow->offset_y - offset_y;

	gui_surface_layout_flowview_commit_position(surface);
		
	gui_window_history_struct* top = gui_window_history_get_top();
	gui_layout_value_struct event = {
		.flow.progress = gui_surface_layout_flowview_get_progress(surface),   //0-100
	};
	if(top != NULL && top->window && top->window->layout_value_changed)
	{
		top->window->layout_value_changed(&event);
	}
}

//对排版中的子元素，进行指定的偏移
void gui_surface_layout_flowview_move(gui_surface_struct* surface,short offset_x,short offset_y)
{
	gui_layout_flow_struct* flow = &surface->layout.flow;
	flow->offset_x += offset_x;
	flow->offset_y += offset_y;
	flow->move_x =  offset_x;
	flow->move_y =  offset_y;
	
	gui_surface_layout_flowview_commit_position(surface);
		
	gui_window_history_struct* top = gui_window_history_get_top();
	gui_layout_value_struct event = {
		.flow.progress = gui_surface_layout_flowview_get_progress(surface),   //0-100
	};
	if(top != NULL && top->window && top->window->layout_value_changed)
	{
		top->window->layout_value_changed(&event);
	}
}


void gui_surface_layout_flowview_switch_to_y(gui_surface_struct* surface, short progress)
{
	if(gui_touch_layout_rebound_is_moving())
		return;
	
	gui_layout_flow_struct* flow = &surface->layout.flow;
	if(flow->height <= LCD_SIZE_HEIGHT)
		return;

	int offset_y = flow->offset_y;
	flow->offset_y = -(flow->height - LCD_SIZE_HEIGHT) * progress / 100;
	flow->move_y =  flow->offset_y - offset_y;
	gui_surface_layout_flowview_commit_position(surface);

	gui_window_history_struct* top = gui_window_history_get_top();
	gui_layout_value_struct event = {
		.flow.progress = gui_surface_layout_flowview_get_progress(surface),   //0-100
	};
	if(top != NULL && top->window && top->window->layout_value_changed)
	{
		top->window->layout_value_changed(&event);
	}
	
}

void gui_surface_layout_flowview_switch_to_direction(gui_surface_struct* surface, DIRECTION_TYPE direction)
{
	if(gui_touch_layout_rebound_is_moving())
		return;
	
	gui_layout_flow_struct* flow = &surface->layout.flow;
	if(flow->height <= LCD_SIZE_HEIGHT)
		return;

	int offset_y = flow->offset_y;
	if(direction == DIRECTION_TYPE_UP)
	{
		if(flow->offset_y > 0){
			flow->offset_y = 0;
		}
		else
			flow->offset_y += (flow->height - LCD_SIZE_HEIGHT) /10;
	}
	else
	{
		if(flow->offset_y < -flow->height + LCD_SIZE_HEIGHT)
			flow->offset_y = -flow->height + LCD_SIZE_HEIGHT;
		else
			flow->offset_y -= (flow->height - LCD_SIZE_HEIGHT)/10;;
	}
	
	flow->move_y =  flow->offset_y - offset_y;

	gui_surface_layout_flowview_commit_position(surface);

	gui_window_history_struct* top = gui_window_history_get_top();
	gui_layout_value_struct event = {
		.flow.progress = gui_surface_layout_flowview_get_progress(surface),   //0-100
	};
	if(top != NULL && top->window && top->window->layout_value_changed)
	{
		top->window->layout_value_changed(&event);
	}


}


void gui_surface_layout_flowview_commit_position(gui_surface_struct* surface)
{
	gui_layout_flow_struct* flow = &surface->layout.flow;
	gui_box_struct* box = surface->child;
	//short count = 0, org_y = 0;
	while(box != NULL)
	{
		if(!box->fix && box->visible)
		{
			box->y += flow->move_y;
		}
		box = box->brother;
	}
	flow->move_y = 0;
	flow->move_x = 0;
}

