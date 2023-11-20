#include "math.h"
#include "gui_touch.h"
#include "system_util_math.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_ring_center.h"
#include "gui_surface_layout_ring_center_config.h"

#if 0   // 废弃
/******************************************************
**
**上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/

//点击
void gui_touch_layout_ring_center_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
		short index = gui_surface_layout_ring_center_get_item_index(surface,touch_point);
		if(index >= 0)
		{
			short id = gui_surface_layout_ring_center_get_item_id(surface,index);
			
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

//移动 [可以任何方向移动]
void gui_touch_layout_ring_center_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;
		
	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
	ring_center->last_offset_x = ring_center->offset_x;
}

//移动 [可以任何方向移动]
void gui_touch_layout_ring_center_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface != NULL)
	{
		gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
		
		short x1 = touch_point->last_x - LCD_SIZE_HALF_WIDTH;
		short y1 = touch_point->last_y - LCD_SIZE_HALF_HEIGHT;
		short x2 = touch_point->x - LCD_SIZE_HALF_WIDTH;
		short y2 = touch_point->y - LCD_SIZE_HALF_HEIGHT;
		short offset_x = 0;	
		if(x1 != 0 && x2 != 0 && y1 != 0 && y2 != 0)
		{
			float d1 = (float)y1 / (float)x1;
			float angle1 = atan(d1)*57.29578f; //180.0/3.1415926;

			float d2 = (float)y2 / (float)x2;
			float angle2 = atan(d2)*57.29578f; //180.0/3.1415926;

			short step_angle = ring_center->step_angle / 4;
			offset_x = math_range(angle2 - angle1,-step_angle,step_angle);
		}
		gui_surface_layout_ring_center_move(surface,offset_x,0);
	}
	gui_surface_force_update();
}


//移动 [可以任何方向移动]
void gui_touch_layout_ring_center_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(touch_point->direction == DIRECTION_TYPE_NONE)
		return;

	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;

	int speed_offset_x = touch_point->speed_x * TOUCH_REBOUND_MAX_TIME / 1000;
	int speed_offset_y = touch_point->speed_y * TOUCH_REBOUND_MAX_TIME / 1000;
	
	short x1 = touch_point->last_x - LCD_SIZE_HALF_WIDTH;
	short y1 = touch_point->last_y - LCD_SIZE_HALF_HEIGHT;
	short x2 = touch_point->x + speed_offset_x - LCD_SIZE_HALF_WIDTH;
	short y2 = touch_point->y + speed_offset_y - LCD_SIZE_HALF_HEIGHT;
	short offset_x = ring_center->offset_x;	
	if(x1 != 0 && x2 != 0 && y1 != 0 && y2 != 0)
	{
		float d1 = (float)y1 / (float)x1;
		float angle1 = atan(d1)*57.29578f; //180.0/3.1415926;

		float d2 = (float)y2 / (float)x2;
		float angle2 = atan(d2)*57.29578f; //180.0/3.1415926;

		short step_angle = ring_center->step_angle * 2 / 3;
		offset_x += math_range(angle2 - angle1,-step_angle,step_angle);
	}
	
	int to_angle = gui_touch_layout_ring_center_adjust_right_angle(offset_x);
	gui_touch_layout_rebound_auto_moving(top_window,DIRECTION_TYPE_LEFT,to_angle,TOUCH_AUTO_MOVE_MIN_SPEED);
}


void gui_touch_layout_ring_center_touch_cancle(const gui_window_struct* top_window)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
		gui_layout_ring_center_struct* ring_center = &surface->layout.ring_center;
		gui_surface_layout_ring_center_offset(surface, ring_center->last_offset_x, 0);
	}
	gui_surface_force_update();
}

#endif

