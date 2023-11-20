#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_touch_layout_pageview.h"
#include "gui_surface_layout_pageview.h"

/******************************************************
**
**列表上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/


/*************************点击 ********************************/

void gui_touch_layout_pageview_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(top_window == NULL || top_window->click_on_layout_item == NULL)
		return;

	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	gui_layout_page_struct* page = &surface->layout.page;

	short id = gui_surface_layout_pageview_get_item_id(surface,touch_point);
	short index = page->curr_page;
	if(index >= 0)
	{
		gui_click_layout_struct event;
		event.id = (unsigned short)id;
		event.index = index;
		event.x = touch_point->x;
		event.y = touch_point->y;
		top_window->click_on_layout_item(&event);
	}
}


/*************************移动********************************/

void gui_touch_layout_pageview_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;

	gui_layout_page_struct* page = &surface->layout.page;
	page->last_offset_x = page->offset_x;
	page->last_offset_y = page->offset_y;
}

void gui_touch_layout_pageview_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	gui_box_struct* box = surface->child;
	if(surface != NULL)
	{
		gui_layout_page_struct* page = &surface->layout.page;
		if(page->orientation == ORIENTATION_TYPE_HORIZONTAL)
		{
			short delta_x = touch_point->x - touch_point->down_x;
			short offset = page->last_offset_x + delta_x;
			short min_offset = -(page->total -1) * box->width;

			if(offset > 0)
				offset /= TOUCH_EMPTY_PULL_SLOW_SPEED;
			else if(offset < min_offset - 30)
				offset = min_offset +  (offset - min_offset) / TOUCH_EMPTY_PULL_SLOW_SPEED;
			gui_surface_layout_pageview_offset(surface,offset,0);
		}
		else
		{
			short delta_y = touch_point->y - touch_point->down_y;
			short offset = page->last_offset_y + delta_y;
			short min_offset = -(page->total - 1) * box->height;

			if(offset > 0)
				offset /= TOUCH_EMPTY_PULL_SLOW_SPEED;
			else if(offset < (min_offset - 30))
				offset = min_offset +  (offset - min_offset) / TOUCH_EMPTY_PULL_SLOW_SPEED;
			gui_surface_layout_pageview_offset(surface,0,offset);
		}
	}
	gui_surface_force_update();
}

void gui_touch_layout_pageview_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(touch_point->direction == DIRECTION_TYPE_NONE)
		return;
	
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	gui_layout_page_struct* page = &surface->layout.page;
	gui_box_struct* box = surface->child;

    // 20230607 Taylor.Le, 修改页表只有一页时， 没有回弹效果.
    if (page->total == 0) {
        return;
    }
    else if (page->orientation == ORIENTATION_TYPE_HORIZONTAL) {
        if (page->total == 1) {
            gui_touch_layout_rebound_auto_moving(top_window,(DIRECTION_TYPE)touch_point->direction,page->offset_x,0);
        }
        else {
            gui_touch_layout_rebound_auto_moving(top_window,(DIRECTION_TYPE)touch_point->direction,0,touch_point->speed_x);
        }
    }
    else {
        if (page->total == 1) {
            gui_touch_layout_rebound_auto_moving(top_window,(DIRECTION_TYPE)touch_point->direction,page->offset_y,0);
        }
        else {
            gui_touch_layout_rebound_auto_moving(top_window,(DIRECTION_TYPE)touch_point->direction,0,touch_point->speed_y);
        }
    }
}


void gui_touch_layout_pageview_touch_cancle(const gui_window_struct* top_window)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
		gui_layout_page_struct* page = &surface->layout.page;
		gui_surface_layout_pageview_offset(surface, page->last_offset_x, page->last_offset_y);
	}
	gui_surface_force_update();
}


