#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_apple_cellular.h"

/******************************************************
**
**蜂窝上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/

// 点击
void gui_touch_layout_apple_cellular_click_on_item(const gui_window_struct *top_window, gui_touch_point_struct *touch_point)
{
	if (gui_surface_layout_apple_cellular_timer_running())
		return;

	gui_surface_struct *surface = gui_surface_get_surface(top_window->screen);
	if (surface)
	{
		gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
		short index = gui_surface_layout_apple_cellular_get_item_index(surface, touch_point);
		if (index >= 0)
		{
			cellular->center_box = gui_surface_layout_apple_cellular_get_item(surface, index);
			if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL)
			{
				gui_surface_layout_apple_cellular_touch_on_small_mode(surface);
			}
			else
			{
				gui_surface_layout_cellular_entry_app(surface);
			}
		}
	}
}

/*************************移动********************************/

// 移动 [可以任何方向移动]
void gui_touch_layout_apple_cellular_touch_start(const gui_window_struct *top_window, gui_touch_point_struct *touch_point)
{
	gui_surface_struct *surface = gui_surface_get_surface(top_window->screen);
	if (surface != NULL)
	{
		gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
		cellular->last_offset_x = cellular->offset_x;
		cellular->last_offset_y = cellular->offset_y;
	}
}

// 移动 [可以任何方向移动]
void gui_touch_layout_apple_cellular_touch_move(const gui_window_struct *top_window, gui_touch_point_struct *touch_point)
{
	if (gui_surface_layout_apple_cellular_timer_running())
		return;

	gui_surface_struct *surface = gui_surface_get_surface(top_window->screen);
	if (surface != NULL)
	{
		short delta_x = touch_point->x - touch_point->last_x;
		short delta_y = touch_point->y - touch_point->last_y;
		gui_surface_layout_apple_cellular_move(surface, delta_x, delta_y);
	}
	gui_surface_force_update();
}

// 移动 [可以任何方向移动]
void gui_touch_layout_apple_cellular_touch_end(const gui_window_struct *top_window, gui_touch_point_struct *touch_point)
{
	if (gui_surface_layout_apple_cellular_timer_running())
		return;

	if (touch_point->curr_direction == DIRECTION_TYPE_NONE)
		return;

	gui_surface_struct *surface = gui_surface_get_surface(top_window->screen);
	if (surface == NULL)
		return;

	gui_surface_layout_apple_cellular_touch_end(surface);
}

void gui_touch_layout_apple_cellular_touch_cancle(const gui_window_struct *top_window)
{
}
