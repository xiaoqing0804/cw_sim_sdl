#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_listview.h"
#include "gui_surface_layout_tween_position.h"

/******************************************************
**
**列表上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/

static void gui_touch_layout_listview_auto_scroll_step(gui_layout_position_tween_struct* layout_tween)
{
    gui_surface_layout_set_offset(layout_tween->surface, layout_tween->curr_x, layout_tween->curr_y);
    gui_surface_force_update();
}

static void gui_touch_layout_listview_auto_scroll_finish(gui_layout_position_tween_struct* layout_tween)
{
    gui_surface_layout_move_end(layout_tween->surface);
}



//点击在列表的哪个条目上
void gui_touch_layout_listview_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	short index = gui_surface_layout_listview_get_item_index(surface,touch_point);
	if(index >= 0)
	{
        gui_layout_list_struct* list = &surface->layout.list;
		gui_box_struct* item = gui_surface_layout_listview_get_item(surface,index);
		
		gui_click_layout_struct event;
		event.id = (unsigned short)item->id;
		event.index = item->layout_index;
		event.x = touch_point->x;
		event.y = touch_point->y;
		event.x_in_item = (touch_point->x - list->offset_x) - item->x;
        event.y_in_item = (touch_point->y - list->offset_x) - item->y;
		if(top_window->click_on_layout_item)
		{
			top_window->click_on_layout_item(&event);
		}
	}
}


/*************************移动********************************/

void gui_touch_layout_listview_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	gui_layout_list_struct* list = &surface->layout.list;
	list->last_offset_x = list->offset_x;
	list->last_offset_y = list->offset_y;
	
	SYS_DEBUG("gui_touch_layout_listview_touch_start");
	gui_surface_layout_tween_position_pause();
}

//列表移动 [只能上下移动]
void gui_touch_layout_listview_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	gui_layout_list_struct* list = &surface->layout.list;
	if(list->scroll)
	{
		short delta_y = touch_point->y - touch_point->down_y;
		short offset_y = list->last_offset_y + delta_y;
		if(offset_y > list->max_offset)
			offset_y = list->max_offset + (offset_y - list->max_offset) / TOUCH_EMPTY_PULL_SLOW_SPEED;
		else if(offset_y < list->min_offset)
			offset_y = list->min_offset +  (offset_y - list->min_offset) / TOUCH_EMPTY_PULL_SLOW_SPEED;

		gui_surface_layout_listview_offset(surface, 0, offset_y);
	}
	gui_surface_force_update();
}

void gui_touch_layout_listview_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	SYS_DEBUG("gui_touch_layout_listview_touch_end");

	if(touch_point->curr_direction == DIRECTION_TYPE_NONE)
		return;

	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;

	gui_layout_list_struct* list = &surface->layout.list;
    SYS_DEBUG("gui: listview, touch_end, offset_y=%d, speed=%d", list->offset_y, touch_point->speed_y);

	short move_y = gui_surface_layout_tween_position_get_distance(touch_point->speed_y);
	SYS_DEBUG("gui: listview, touch_end, move_y=%d",move_y);

	gui_layout_position_tween_struct* position_tween = gui_surface_layout_tween_position_init(surface);
	position_tween->mode = TWEEN_TYPE_CIRCULAR_OUT;
	position_tween->orientation = ORIENTATION_TYPE_VERTICAL;
	position_tween->scroll_step = gui_touch_layout_listview_auto_scroll_step;
	position_tween->scroll_finish = gui_touch_layout_listview_auto_scroll_finish;
	position_tween->min_y = list->min_offset;
	position_tween->max_y = list->max_offset;
	position_tween->move_y = move_y;
	position_tween->speed_y = touch_point->speed_y;
	gui_surface_layout_tween_position_start(surface);
}

void gui_touch_layout_listview_touch_free(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;

	if(gui_surface_layout_tween_position_is_pause())
	{
		gui_layout_list_struct* list = &surface->layout.list;
		short move_y = gui_surface_layout_tween_position_get_distance(touch_point->speed_y);

		gui_layout_position_tween_struct* position_tween = gui_surface_layout_tween_position_init(surface);
		position_tween->mode = TWEEN_TYPE_CIRCULAR_OUT;
		position_tween->orientation = ORIENTATION_TYPE_VERTICAL;
		position_tween->scroll_step = gui_touch_layout_listview_auto_scroll_step;
		position_tween->scroll_finish = gui_touch_layout_listview_auto_scroll_finish;
		position_tween->min_y = list->min_offset;
		position_tween->max_y = list->max_offset;
		position_tween->move_y = move_y;
		position_tween->speed_y = touch_point->speed_y;
		gui_surface_layout_tween_position_start(surface);
	}
}

void gui_touch_layout_listview_touch_cancle(const gui_window_struct* top_window)
{
	SYS_DEBUG("gui_touch_layout_listview_touch_cancle");
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
		gui_surface_layout_tween_position_stop();
		gui_layout_list_struct* list = &surface->layout.list;
		gui_surface_layout_listview_offset(surface, list->last_offset_x, list->last_offset_y);
	}
	gui_surface_force_update();
}


