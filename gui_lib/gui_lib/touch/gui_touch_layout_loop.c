#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_loop.h"
#include "gui_surface_layout_tween_position.h"

/******************************************************
**
**蜂窝上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/
//点击
void gui_touch_layout_loop_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
		short index = gui_surface_layout_loop_get_item_index(surface,touch_point);
		if(index >= 0)
		{
			short id = gui_surface_layout_loop_get_item_id(surface,index);
			gui_click_layout_struct event;
			event.id = (unsigned char)id;
			event.index = index;
			event.x = touch_point->x;
			event.y = touch_point->y;
			if(top_window->click_on_layout_item)
			{
				top_window->click_on_layout_item(&event);
			}
		}
	}
}


/*************************移动********************************/

static void gui_touch_layout_loop_auto_scroll_step(gui_layout_position_tween_struct* layout_tween)
{
    gui_surface_layout_set_offset(layout_tween->surface, layout_tween->curr_x, layout_tween->curr_y);
    gui_surface_force_update();
}

static void gui_touch_layout_loop_auto_scroll_finish(gui_layout_position_tween_struct* layout_tween)
{
    gui_surface_layout_move_end(layout_tween->surface);
}


//移动 [可以任何方向移动]
void gui_touch_layout_loop_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface != NULL)
	{
		gui_layout_loop_struct* loop = &surface->layout.loop;
		loop->last_offset_x = loop->offset_x;
		loop->last_offset_y = loop->offset_y;

		gui_surface_layout_tween_position_pause();
	}
}

//移动 [可以任何方向移动]
void gui_touch_layout_loop_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface != NULL)
	{
		short delta_y = touch_point->y - touch_point->last_y;
		GUI_DEBUG("gui_touch_layout_loop_touch_move delta_y=%d",delta_y);
		gui_surface_layout_loop_move(surface,0,delta_y);
	}
	gui_surface_force_update();
}

//移动 [可以任何方向移动]
void gui_touch_layout_loop_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(touch_point->curr_direction == DIRECTION_TYPE_NONE)
		return;

	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;

	//gui_touch_layout_rebound_auto_moving(top_window, (DIRECTION_TYPE)touch_point->curr_direction, 0, touch_point->speed_y);

	gui_layout_loop_struct* loop = &surface->layout.loop;
	short move_y = gui_surface_layout_tween_position_get_distance(touch_point->speed_y);
	gui_layout_position_tween_struct* position_tween = gui_surface_layout_tween_position_init(surface);
	position_tween->mode = TWEEN_TYPE_CIRCULAR_OUT;
	position_tween->orientation = ORIENTATION_TYPE_VERTICAL;
	position_tween->scroll_step = gui_touch_layout_loop_auto_scroll_step;
	position_tween->scroll_finish = gui_touch_layout_loop_auto_scroll_finish;
	position_tween->loop = 1;
	position_tween->move_y = move_y;
	position_tween->speed_y = touch_point->speed_y;
	gui_surface_layout_tween_position_start(surface);
}

