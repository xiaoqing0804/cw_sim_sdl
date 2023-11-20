#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_flow.h"

/******************************************************
**
**列表上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/

//点击在列表的哪个条目上
void gui_touch_layout_flowview_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	short index = gui_surface_layout_flowview_get_item_index(surface,touch_point);
	if(index >= 0)
	{
		short id = gui_surface_layout_flowview_get_item_id(surface,index);
		gui_click_layout_struct event;
		event.id = (unsigned short)id;
		event.index = index;
		event.x = touch_point->x;
		event.y = touch_point->y;
		if(top_window->click_on_layout_item)
		{
			top_window->click_on_layout_item(&event);
		}
	}
}



/*************************移动********************************/

void gui_touch_layout_flowview_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	gui_layout_flow_struct* flow = &surface->layout.flow;
	flow->last_offset_x = flow->offset_x;
	flow->last_offset_y = flow->offset_y;
	flow->move_x =  0;
	flow->move_y =  0;
}

//列表移动 [只能上下移动]
void gui_touch_layout_flowview_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	gui_layout_flow_struct* flow = &surface->layout.flow;
	if(flow->scroll)
	{
		short delta_y = touch_point->y - touch_point->down_y;
		short offset_y = flow->last_offset_y + delta_y;
		short min_y = -flow->height + LCD_SIZE_HEIGHT;

		if(offset_y > 0)
			offset_y /= TOUCH_EMPTY_PULL_SLOW_SPEED;
		else if(offset_y < min_y)
			offset_y = min_y +  (offset_y - min_y) / TOUCH_EMPTY_PULL_SLOW_SPEED;

		BT_DEBUG("gui_touch_layout_flowview_touch_move5 =%d",offset_y);
		
		gui_surface_layout_flowview_offset(surface, 0, offset_y);
	}
	gui_surface_force_update();
}

void gui_touch_layout_flowview_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(touch_point->curr_direction == DIRECTION_TYPE_NONE)
		return;
		
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;
	
	gui_layout_flow_struct* flow = &surface->layout.flow;
	gui_touch_layout_rebound_auto_moving(top_window, DIRECTION_TYPE_DOWN, 0, touch_point->speed_y);
}


void gui_touch_layout_flowview_touch_cancle(const gui_window_struct* top_window)
{

}


