#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_scroll.h"
#include "gui_surface_layout_tween_position.h"


/******************************************************
**
**
**
*******************************************************/
static void gui_touch_layout_scrollview_auto_scroll_step(gui_layout_position_tween_struct* layout_tween)
{
    gui_surface_layout_set_offset(layout_tween->surface, layout_tween->curr_x, layout_tween->curr_y);
    gui_surface_force_update();
}

static void gui_touch_layout_scrollview_auto_scroll_finish(gui_layout_position_tween_struct* layout_tween)
{
    gui_surface_layout_move_end(layout_tween->surface);
}

/******************************************************
**
**列表上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/

//点击在列表的哪个条目上
void gui_touch_layout_scrollview_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
    gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
    if(surface == NULL) return;

    short index = gui_surface_layout_scrollview_get_item_index(surface,touch_point);
    if(index >= 0)
    {
        gui_box_struct* item = gui_surface_layout_scrollview_get_item(surface,index);
        gui_layout_scroll_struct* scroll = &surface->layout.scroll;

        short id = gui_surface_layout_scrollview_get_item_id(surface,index);
        gui_click_layout_struct event;
        event.id = (unsigned short)id;
        event.index = index;
        event.x = touch_point->x;
        event.y = touch_point->y;
        event.x_in_item = (touch_point->x - scroll->offset_x) - item->x;
        event.y_in_item = (touch_point->y - scroll->offset_x) - item->y;
        if(top_window->click_on_layout_item)
        {
            top_window->click_on_layout_item(&event);
        }
    }
}



/*************************移动********************************/

void gui_touch_layout_scrollview_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
    gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
    if(surface == NULL) return;

    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    scroll->last_offset_x = scroll->offset_x;
    scroll->last_offset_y = scroll->offset_y;
    scroll->move_x =  0;
    scroll->move_y =  0;

    gui_surface_layout_tween_position_pause();
}

//列表移动 [只能上下移动]
void gui_touch_layout_scrollview_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
    gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
    if(surface == NULL) return;

    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    if(scroll->scroll)
    {
        short delta_y = touch_point->y - touch_point->down_y;
        short offset_y = scroll->last_offset_y + delta_y;
        short min_y = -scroll->height + LCD_SIZE_HEIGHT;

        if(offset_y > scroll->max_offset)
        {
            if(scroll->forbid_up_rebound)
                offset_y = scroll->max_offset;
            else
                offset_y = scroll->max_offset + (offset_y - scroll->max_offset) / TOUCH_EMPTY_PULL_SLOW_SPEED;;
        }
        else if(offset_y < scroll->min_offset)
        {
            if(scroll->forbid_down_rebound)
                offset_y = scroll->min_offset;
            else
                offset_y = scroll->min_offset +  (offset_y - scroll->min_offset) / TOUCH_EMPTY_PULL_SLOW_SPEED;
        }
        gui_surface_layout_scrollview_offset(surface, 0, offset_y);
    }
    gui_surface_force_update();
}

void gui_touch_layout_scrollview_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(touch_point->curr_direction == DIRECTION_TYPE_NONE)
		return;

	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;

    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
	short move_y = gui_surface_layout_tween_position_get_distance(touch_point->speed_y);

	gui_layout_position_tween_struct* position_tween = gui_surface_layout_tween_position_init(surface);
	position_tween->mode = TWEEN_TYPE_CIRCULAR_OUT;
	position_tween->orientation = ORIENTATION_TYPE_VERTICAL;
	position_tween->scroll_step = gui_touch_layout_scrollview_auto_scroll_step;
	position_tween->scroll_finish = gui_touch_layout_scrollview_auto_scroll_finish;
	position_tween->min_y = scroll->min_offset;
	position_tween->max_y = scroll->max_offset;
	position_tween->move_y = move_y;
	position_tween->speed_y = touch_point->speed_y;
	gui_surface_layout_tween_position_start(surface);
}


void gui_touch_layout_scrollview_touch_cancle(const gui_window_struct* top_window,unsigned char touch_type)
{
    gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
    if(surface)
    {
        gui_surface_layout_tween_position_stop();

         gui_layout_scroll_struct* scroll = &surface->layout.scroll;
        if(scroll->can_swipe && touch_type == TOUCH_TYPE_LAYOUT_FORBID) //拉到底或顶被禁止的，不能回弹回去
            return;
        gui_surface_layout_scrollview_offset(surface, scroll->last_offset_x, scroll->last_offset_y);   
    }
    gui_surface_force_update();
}


