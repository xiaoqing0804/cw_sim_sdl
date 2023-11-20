#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_cellular.h"

#define CELLULAR_OFFSET_COUNT 5
static short g_gui_touch_layout_cellular_offset_x = 0;
static short g_gui_touch_layout_cellular_offset_y = 0;
static short g_gui_touch_layout_cellular_offset_count = 0;
static unsigned int g_gui_touch_layout_cellular_timer_id = 0;


/******************************************************
**
**蜂窝上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/
//点击
void gui_touch_layout_cellular_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
		short index = gui_surface_layout_cellular_get_item_index(surface,touch_point);
		if(index >= 0)
		{
			gui_box_struct* box = gui_surface_layout_cellular_get_item(surface,index);
			gui_click_layout_struct event;
			event.id = (unsigned char)box->id;
			event.index = index;
			event.x = touch_point->x;
			event.y = touch_point->y;
			if(top_window->click_on_layout_item)
			{
				gui_surface_layout_cellular_set_near_center_box(surface,box);
				top_window->click_on_layout_item(&event);
			}
		}
	}
}

static void gui_touch_layout_cellular_touch_timer_move(unsigned int timer, void* param)
{
	application_stop_user_timer(g_gui_touch_layout_cellular_timer_id);
	
	gui_surface_struct* surface = (gui_surface_struct*)param;
	if(surface->screen->type != TYPE_GUI_LAYOUT_CELLULAR)
	{
		g_gui_touch_layout_cellular_offset_count = 0;
		g_gui_touch_layout_cellular_timer_id = 0;
		return;
	}
	
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_box_struct* center_box = cellular->center_box;
	if(center_box == NULL)
	{
		g_gui_touch_layout_cellular_offset_count = 0;
		g_gui_touch_layout_cellular_timer_id = 0;
		return;
	}
	
	if(g_gui_touch_layout_cellular_offset_count <= 0)
	{
		g_gui_touch_layout_cellular_offset_count = 0;
		g_gui_touch_layout_cellular_timer_id = 0;
		short offset_x = LCD_SIZE_HALF_WIDTH - (center_box->x + center_box->width/2);
		short offset_y = LCD_SIZE_HALF_HEIGHT - (center_box->y + center_box->height/2);
		gui_surface_layout_move(surface, offset_x, offset_y);
		gui_surface_commit();
	}
	else
	{
		g_gui_touch_layout_cellular_offset_count--;
		gui_surface_layout_move(surface, g_gui_touch_layout_cellular_offset_x, g_gui_touch_layout_cellular_offset_y);
		gui_surface_commit();
		
		g_gui_touch_layout_cellular_timer_id = application_start_user_timer(20, gui_touch_layout_cellular_touch_timer_move, param);
	}
	
}


/*************************移动********************************/

//移动 [可以任何方向移动]
void gui_touch_layout_cellular_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface != NULL)
	{
		gui_layout_cellular_struct* cellular = &surface->layout.cellular;
		cellular->last_offset_x = cellular->offset_x;
		cellular->last_offset_y = cellular->offset_y;
	}
}

//移动 [可以任何方向移动]
void gui_touch_layout_cellular_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface != NULL)
	{
		short delta_x = touch_point->x - touch_point->last_x;
		short delta_y = touch_point->y - touch_point->last_y;
		gui_surface_layout_cellular_move(surface,delta_x,delta_y);
	}
	gui_surface_force_update();
}

//移动 [可以任何方向移动]
void gui_touch_layout_cellular_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(touch_point->curr_direction == DIRECTION_TYPE_NONE)
		return;
		
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;
	
	gui_box_struct* box = gui_surface_layout_cellular_get_center_item(surface);
	if(box != NULL)
	{
		gui_layout_cellular_struct* cellular = &surface->layout.cellular;
		cellular->center_box = box;
		
		short offset_x = LCD_SIZE_HALF_WIDTH - (box->x + box->width/2);
		short offset_y = LCD_SIZE_HALF_HEIGHT - (box->y + box->height/2);

		if(ABS(offset_x) < CELLULAR_OFFSET_COUNT && ABS(offset_y) < CELLULAR_OFFSET_COUNT)
		{
			gui_surface_layout_move(surface, offset_x, offset_y);
		}
		else
		{
			g_gui_touch_layout_cellular_offset_count = CELLULAR_OFFSET_COUNT;
			g_gui_touch_layout_cellular_offset_x = offset_x / g_gui_touch_layout_cellular_offset_count;
			g_gui_touch_layout_cellular_offset_y = offset_y / g_gui_touch_layout_cellular_offset_count;
			application_stop_user_timer(g_gui_touch_layout_cellular_timer_id);
			g_gui_touch_layout_cellular_timer_id = application_start_user_timer(1, gui_touch_layout_cellular_touch_timer_move, surface);
		}
		gui_surface_force_update();
	}
}

void gui_touch_layout_cellular_touch_cancle(const gui_window_struct* top_window)
{
	if(g_gui_touch_layout_cellular_timer_id > 0)
	{
		application_stop_user_timer(g_gui_touch_layout_cellular_timer_id);
		g_gui_touch_layout_cellular_timer_id = 0;
	}
}


