#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_gridview.h"


/******************************************************
**
**列表上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/


//点击在列表的哪个条目上
void gui_touch_layout_gridview_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;
	
	short index = gui_surface_layout_gridview_get_item_index(surface,touch_point);
	if(index >= 0)
	{
		short id = gui_surface_layout_gridview_get_item_id(surface,index);
		gui_click_layout_struct event;
		event.id = id;
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


void gui_touch_layout_gridview_check_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
		gui_layout_grid_struct* grid = &surface->layout.grid;
		grid->last_offset_x = grid->offset_x;
		grid->last_offset_y = grid->offset_y;
	}
}

//列表移动 [只能上下移动]
void gui_touch_layout_gridview_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;
	
	gui_layout_grid_struct* grid = &surface->layout.grid;
	if(grid->scroll)
	{
		short delta_y = touch_point->y - touch_point->down_y;
		short offset_y = grid->last_offset_y + delta_y;
		short min_y = -grid->height + LCD_SIZE_HEIGHT;

		if(offset_y > 0)
			offset_y /= TOUCH_EMPTY_PULL_SLOW_SPEED;
		else if(offset_y < min_y)
			offset_y = min_y +  (offset_y - min_y) / TOUCH_EMPTY_PULL_SLOW_SPEED;
		gui_surface_layout_gridview_offset(surface, 0, offset_y);
	}
	gui_surface_force_update();
}


void gui_touch_layout_gridview_up(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(touch_point->curr_direction == DIRECTION_TYPE_NONE)
		return;
	
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	gui_layout_grid_struct* grid = &surface->layout.grid;
    gui_touch_layout_rebound_auto_moving(top_window, (DIRECTION_TYPE)touch_point->curr_direction, 0, touch_point->speed_y);
}

void gui_touch_layout_gridview_cancle(const gui_window_struct* top_window)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
		gui_layout_grid_struct* grid = &surface->layout.grid;
		gui_surface_layout_gridview_offset(surface, grid->last_offset_x, grid->last_offset_y);
	}
	gui_surface_force_update();
}

