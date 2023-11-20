#include "feature_all.h"
#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_touch_layout.h"
#include "gui_touch_layout_rebound.h"

static const gui_window_struct* g_gui_touch_window = NULL;
static TOUCH_TYPE g_gui_touch_type = TOUCH_TYPE_NONE;

static const gui_touch_event_struct* g_gui_touch_event = NULL;
static unsigned char g_gui_touch_down = 0;

static const gui_touch_event_struct* g_gui_touch_event_full_screen = NULL;
static unsigned char g_gui_touch_down_full_screen = 0;

//检查点击是否在事件响应的区域
static unsigned char gui_touch_in_area(const gui_window_struct* top_window,const gui_touch_event_struct* touch_event, gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	gui_surface_struct* surface = gui_surface_get_surface(screen);
	gui_box_struct* box = gui_surface_get_box(top_window->screen, touch_event->id);
	if(box != NULL && box->visible)
	{
		geometry_rect rect_box = 
		{ 
			.x = box->x + surface->x - touch_event->offset_left,
			.y = box->y + surface->y - touch_event->offset_top,
			.width = box->width + touch_event->offset_left + touch_event->offset_right,
			.height = box->height + touch_event->offset_top + touch_event->offset_bottom,
		};
		if(check_rect_contain_point_xy(&rect_box,touch_point->x,touch_point->y))
			return 1;
	}
	return 0;
}

static const gui_touch_event_struct* gui_touch_find_full_screen_touch_event(const gui_window_struct* touch_window)
{
	//在注册的点击事件中，查找全屏控件(全屏优先级低)
	const gui_touch_event_struct* touch_event = touch_window->touch_events;
	for(short i = 0; i < touch_window->touch_event_num; i++)
	{
		if(IS_FULL_SCREEN_TOUCH(touch_event))
			return touch_event;
		touch_event++;
	}
	return NULL;
}
	




//-------------------对外接口----------------------------------------
// Taylor.Le, +
unsigned char gui_touch_longpress(gui_touch_point_struct* touch_point)
{
	if(g_gui_touch_window == NULL)
		return 0;
	
	const gui_touch_event_struct* touch_event = g_gui_touch_window->touch_events;
	for(short i = 0; i < g_gui_touch_window->touch_event_num; i++)
	{
		if(touch_event->long_touch)
		{
			if(IS_FULL_SCREEN_TOUCH(touch_event) || gui_touch_in_area(g_gui_touch_window,touch_event,touch_point))
			{
				gui_touch_struct event;
				event.x = touch_point->x;
				event.y = touch_point->y;
				event.down_x = touch_point->down_x;
				event.down_y = touch_point->down_y;
				event.direction = DIRECTION_TYPE_NONE;
				event.type = TOUCH_EVENT_TYPE_CANCLE;
				if(g_gui_touch_event && g_gui_touch_down)
				{
					event.id = g_gui_touch_event->id;
					if(g_gui_touch_event->touch)
						g_gui_touch_event->touch(&event);
				}
				
				if(g_gui_touch_event_full_screen && g_gui_touch_down_full_screen)
				{
					event.id = g_gui_touch_event_full_screen->id;
					if(g_gui_touch_event_full_screen->touch)
						g_gui_touch_event_full_screen->touch(&event);
				}

				gui_click_struct long_touch_event;
				long_touch_event.type = TOUCH_EVENT_TYPE_LONGPRESS;
				long_touch_event.id = touch_event->id;
				long_touch_event.x = touch_point->x;
				long_touch_event.y = touch_point->y;
				touch_event->long_touch(&long_touch_event);
				return 1;
			}	
		}
		touch_event++;
	}

    return 0;
}
//

unsigned char gui_touch_down(gui_touch_point_struct* touch_point)
{
	g_gui_touch_window = gui_window_history_get_top_window();
	g_gui_touch_type = TOUCH_TYPE_NONE;

	g_gui_touch_event = NULL;
	g_gui_touch_down = 0;
	
	g_gui_touch_event_full_screen = NULL;
	g_gui_touch_down_full_screen = 0;
	
	if(g_gui_touch_window == NULL)
		return 0;

	//保存数据
	gui_touch_layout_check_start(g_gui_touch_window,touch_point);
	
	//是否注册了点击事件
	if(g_gui_touch_type == TOUCH_TYPE_NONE && g_gui_touch_window->touch_event_num > 0)
	{
		//在注册的点击事件中，找到点击的控件
		const gui_touch_event_struct* touch_event = g_gui_touch_window->touch_events;
		for(short i = 0; i < g_gui_touch_window->touch_event_num; i++)
		{
			if(!IS_FULL_SCREEN_TOUCH(touch_event) && gui_touch_in_area(g_gui_touch_window,touch_event,touch_point))
			{
				gui_touch_struct event;
				event.type = TOUCH_EVENT_TYPE_DOWN;
				event.direction = DIRECTION_TYPE_NONE;
				event.x = touch_point->x;
				event.y = touch_point->y;
				event.down_x = touch_point->down_x;
				event.down_y = touch_point->down_y;
				event.id = touch_event->id;
				if(touch_event->touch && touch_event->touch(&event))
				{
					g_gui_touch_event = touch_event;
					g_gui_touch_down = 1;
					g_gui_touch_type = TOUCH_TYPE_TOUCH;
				}
				else if(touch_event->long_touch)
				{
					g_gui_touch_event = touch_event;
					g_gui_touch_type = TOUCH_TYPE_TOUCH;
				}
				else if(touch_event->click)
				{
					g_gui_touch_event = touch_event;
					g_gui_touch_type = TOUCH_TYPE_CLICK;
				}
				break;
			}
			touch_event++;
		}

		if(g_gui_touch_type != TOUCH_TYPE_NONE)
			return 1;
	}


	//如果没有点击事件，看看是不是点击的排版
	if(g_gui_touch_type == TOUCH_TYPE_NONE && g_gui_touch_window->screen->type != TYPE_GUI_LAYOUT_PANNEL)
	{
		g_gui_touch_type = gui_touch_layout_check_down_type(g_gui_touch_window,touch_point);
		if(g_gui_touch_type != TOUCH_TYPE_NONE)
			return 1;
	}

	if(g_gui_touch_type == TOUCH_TYPE_NONE && g_gui_touch_window->touch_event_num > 0)
	{
		const gui_touch_event_struct* touch_event = gui_touch_find_full_screen_touch_event(g_gui_touch_window);
		if(touch_event != NULL)
		{
			gui_touch_struct event;
			event.type = TOUCH_EVENT_TYPE_DOWN;
			event.direction = DIRECTION_TYPE_NONE;
			event.x = touch_point->x;
			event.y = touch_point->y;
			event.down_x = touch_point->down_x;
			event.down_y = touch_point->down_y;
			event.id = touch_event->id;
			if(touch_event->touch && touch_event->touch(&event))
			{
				g_gui_touch_event_full_screen = touch_event;
				g_gui_touch_type = TOUCH_TYPE_TOUCH;
				g_gui_touch_down_full_screen = 1;
			}
			else if(touch_event->long_touch)
			{
				g_gui_touch_event_full_screen = touch_event;
				g_gui_touch_type = TOUCH_TYPE_TOUCH;
			}
			else if(touch_event->click)
			{
				g_gui_touch_event_full_screen = touch_event;
				g_gui_touch_type = TOUCH_TYPE_CLICK;
			}
			if(g_gui_touch_type != TOUCH_TYPE_NONE)
				return 1;
		}
	}
	return 0;
}

unsigned char gui_touch_move(gui_touch_point_struct* touch_point)
{
	if(g_gui_touch_type == TOUCH_TYPE_TOUCH)
	{
		gui_touch_struct event;
		event.direction = touch_point->direction;
		event.x = touch_point->x;
		event.y = touch_point->y;
		event.down_x = touch_point->down_x;
		event.down_y = touch_point->down_y;
		if(g_gui_touch_event && g_gui_touch_event->touch && g_gui_touch_down)
		{
			event.id = g_gui_touch_event->id;
			
			event.type = TOUCH_EVENT_TYPE_MOVE;
			if(g_gui_touch_event->touch(&event))
				return 1;

			//如果点击事件不接收响应，需要取消触摸
			event.type = TOUCH_EVENT_TYPE_CANCLE;
			if(g_gui_touch_event->touch)
			{
				g_gui_touch_event->touch(&event);
			}
			g_gui_touch_event = NULL;
		}

		//如果点击事件没有响应，看看是不是全屏点击的排版
		if(g_gui_touch_event_full_screen && g_gui_touch_event_full_screen->touch && g_gui_touch_down_full_screen)
		{
			event.id = g_gui_touch_event_full_screen->id;
			
			event.type = TOUCH_EVENT_TYPE_MOVE;
			if(g_gui_touch_event_full_screen->touch(&event))
				return 1;

			//如果点击事件不接收响应，需要取消触摸
			event.type = TOUCH_EVENT_TYPE_CANCLE;
			if(g_gui_touch_event_full_screen->touch)
			{
				g_gui_touch_event_full_screen->touch(&event);
			}
			g_gui_touch_event_full_screen = NULL;
		}
		
		//如果点击事件没有响应，看看是不是全屏点击的排版
		if(!g_gui_touch_down_full_screen)
		{
			g_gui_touch_type = gui_touch_layout_check_move_type(g_gui_touch_window,touch_point);
			if(g_gui_touch_type != TOUCH_TYPE_NONE)
				return 1;
		}


		//当前面没有判断过全屏事件时，需要判断一下全屏事件
		if(!g_gui_touch_down_full_screen && g_gui_touch_event_full_screen == NULL)
		{
			const gui_touch_event_struct* touch_event = gui_touch_find_full_screen_touch_event(g_gui_touch_window);
			if(touch_event != NULL)
			{
				gui_touch_struct event;
				event.type = TOUCH_EVENT_TYPE_DOWN;
				event.direction = DIRECTION_TYPE_NONE;
				event.x = touch_point->x;
				event.y = touch_point->y;
				event.down_x = touch_point->down_x;
				event.down_y = touch_point->down_y;
				event.id = touch_event->id;
				if(touch_event->touch && touch_event->touch(&event))
				{
					g_gui_touch_event_full_screen = touch_event;
					g_gui_touch_type = TOUCH_TYPE_TOUCH;
					g_gui_touch_down_full_screen = 1;
					return 1;
				}
			}
		}
		return 0;
		
	}
	else if(g_gui_touch_type == TOUCH_TYPE_CLICK || g_gui_touch_type == TOUCH_TYPE_LAYOUT_ITEM)
	{	
		//有移动时，就取消点击事件,这时移动的距离只是刚刚够移动的临界长度,跳点多的屏要注意判断一下
		g_gui_touch_type = gui_touch_layout_check_move_type(g_gui_touch_window,touch_point);

		if(g_gui_touch_type == TOUCH_TYPE_NONE && !g_gui_touch_down_full_screen && g_gui_touch_event_full_screen == NULL)
		{
			const gui_touch_event_struct* touch_event = gui_touch_find_full_screen_touch_event(g_gui_touch_window);
			if(touch_event != NULL)
			{
				gui_touch_struct event;
				event.type = TOUCH_EVENT_TYPE_DOWN;
				event.direction = DIRECTION_TYPE_NONE;
				event.x = touch_point->x;
				event.y = touch_point->y;
				event.down_x = touch_point->down_x;
				event.down_y = touch_point->down_y;
				event.id = touch_event->id;
				if(touch_event->touch && touch_event->touch(&event))
				{
					g_gui_touch_event_full_screen = touch_event;
					g_gui_touch_type = TOUCH_TYPE_TOUCH;
					g_gui_touch_down_full_screen = 1;
					return 1;
				}
			}
		}
		
		return g_gui_touch_type == TOUCH_TYPE_LAYOUT;
	}
	else if(g_gui_touch_type == TOUCH_TYPE_LAYOUT)
	{
		if(touch_point->gesture_orientation == ORIENTATION_TYPE_HORIZONTAL)
		{
			g_gui_touch_type = gui_touch_layout_check_only_move_leftright(g_gui_touch_window,touch_point);
		}
		else if(touch_point->gesture_orientation == ORIENTATION_TYPE_VERTICAL)
		{
			//SYS_DEBUG("gui_touch_move ORIENTATION_TYPE_VERTICAL");
			g_gui_touch_type = gui_touch_layout_check_only_move_updown(g_gui_touch_window,touch_point);
		}
		else if(touch_point->gesture_orientation == ORIENTATION_TYPE_ALL)
		{
			g_gui_touch_type = gui_touch_layout_check_move_all(g_gui_touch_window,touch_point);
		}
		SYS_DEBUG("gui_touch_move g_gui_touch_type=%d",g_gui_touch_type);
		if(g_gui_touch_type == TOUCH_TYPE_LAYOUT_FORBID)
		{
			gui_touch_layout_check_cancle(g_gui_touch_window,g_gui_touch_type);
			g_gui_touch_type = TOUCH_TYPE_NONE;
			return 0;
		}
		if(g_gui_touch_type != TOUCH_TYPE_NONE)
			return 1;

		//当前面没有判断过全屏事件时，需要判断一下全屏事件
		if(!g_gui_touch_down_full_screen && g_gui_touch_event_full_screen == NULL)
		{
			const gui_touch_event_struct* touch_event = gui_touch_find_full_screen_touch_event(g_gui_touch_window);
			if(touch_event != NULL)
			{
				gui_touch_struct event;
				event.type = TOUCH_EVENT_TYPE_DOWN;
				event.direction = DIRECTION_TYPE_NONE;
				event.x = touch_point->x;
				event.y = touch_point->y;
				event.down_x = touch_point->down_x;
				event.down_y = touch_point->down_y;
				event.id = touch_event->id;
				if(touch_event->touch && touch_event->touch(&event))
				{
					g_gui_touch_event_full_screen = touch_event;
					g_gui_touch_type = TOUCH_TYPE_TOUCH;
					g_gui_touch_down_full_screen = 1;
					return 1;
				}
			}
		}
		
	}
	return 0;
}

void gui_touch_up(gui_touch_point_struct* touch_point,unsigned char click)
{
    GUI_DEBUG("touch: gui_touch_up, g_gui_touch_type=%d, click=%d, evt=%x\n", g_gui_touch_type, click, (unsigned int)g_gui_touch_event);
	if(g_gui_touch_type == TOUCH_TYPE_TOUCH)
	{
		gui_touch_struct event;
		event.type = TOUCH_EVENT_TYPE_UP;
		event.direction = touch_point->direction;
		
		event.x = touch_point->x;
		event.y = touch_point->y;
		event.down_x = touch_point->down_x;
		event.down_y = touch_point->down_y;
		event.speed_x = touch_point->speed_x;
		event.speed_y = touch_point->speed_y;
			
		if(g_gui_touch_event && g_gui_touch_down)
		{
			event.id = g_gui_touch_event->id;
			if(g_gui_touch_event->touch)
				g_gui_touch_event->touch(&event);
		}
		else if(g_gui_touch_event_full_screen && g_gui_touch_down_full_screen)
		{
			event.id = g_gui_touch_event_full_screen->id;
			if(g_gui_touch_event_full_screen->touch)
				g_gui_touch_event_full_screen->touch(&event);
		}
	}
	else if(g_gui_touch_type == TOUCH_TYPE_CLICK)
	{
		gui_click_struct event;
		event.type = TOUCH_CLICK_TYPE_CLICK;
		event.id = g_gui_touch_event->id;
		event.x = touch_point->x;
		event.y = touch_point->y;
		
		if(g_gui_touch_event)
		{
			event.id = g_gui_touch_event->id;
			if(g_gui_touch_event->click)
				g_gui_touch_event->click(&event);
		}
		else if(g_gui_touch_event_full_screen)
		{
			event.id = g_gui_touch_event_full_screen->id;
			if(g_gui_touch_event_full_screen->click)
				g_gui_touch_event_full_screen->click(&event);
		}
	}
	else if(g_gui_touch_type == TOUCH_TYPE_LAYOUT_ITEM)
	{
		gui_touch_layout_check_click(g_gui_touch_window,touch_point);
	}
	else if(g_gui_touch_type == TOUCH_TYPE_LAYOUT)
	{
		//没有发生过移动
		if(click)
		{
			const gui_touch_event_struct* touch_event = gui_touch_find_full_screen_touch_event(g_gui_touch_window);
			if(touch_event != NULL)
			{
				gui_click_struct event;
				event.type = TOUCH_CLICK_TYPE_CLICK;
				event.id = touch_event->id;
				event.x = touch_point->x;
				event.y = touch_point->y;
				if(touch_event->click)
					touch_event->click(&event);
			}
            else if(g_gui_touch_event)
            {
				gui_click_struct event;
				event.type = TOUCH_CLICK_TYPE_CLICK;
                event.id = g_gui_touch_event->id;
				event.x = touch_point->x;
				event.y = touch_point->y;
                if(g_gui_touch_event->click)
                    g_gui_touch_event->click(&event);
            }
		}
		else if(touch_point->direction != DIRECTION_TYPE_NONE)
		{
			gui_touch_layout_check_up(g_gui_touch_window,touch_point);

		}

	}
	
	gui_touch_layout_check_free(g_gui_touch_window,touch_point);

	g_gui_touch_window = NULL;
	g_gui_touch_type = TOUCH_TYPE_NONE;
	
	g_gui_touch_event = NULL;
	g_gui_touch_down = 0;
	
	g_gui_touch_event_full_screen = NULL;
	g_gui_touch_down_full_screen = 0;
	
}


void gui_touch_cancle()
{
    GUI_DEBUG("touch: gui_touch_cancle, g_gui_touch_type=%d\n", g_gui_touch_type);
	if(g_gui_touch_type == TOUCH_TYPE_TOUCH)
	{
		gui_touch_struct event;
		event.x = 0;
		event.y = 0;
		event.down_x = 0;
		event.down_y = 0;
		event.direction = DIRECTION_TYPE_NONE;
		
		if(g_gui_touch_event && g_gui_touch_down)
		{
			event.type = TOUCH_EVENT_TYPE_CANCLE;
			event.id = g_gui_touch_event->id;
			if(g_gui_touch_event->touch)
				g_gui_touch_event->touch(&event);
		}
		
		if(g_gui_touch_event_full_screen && g_gui_touch_down_full_screen)
		{
			event.type = TOUCH_EVENT_TYPE_CANCLE;
			event.id = g_gui_touch_event_full_screen->id;
			if(g_gui_touch_event_full_screen->touch)
				g_gui_touch_event_full_screen->touch(&event);
		}
		
	}
	else if(g_gui_touch_type == TOUCH_TYPE_LAYOUT)
	{
		gui_touch_layout_check_cancle(g_gui_touch_window,g_gui_touch_type);
	}
	g_gui_touch_window = NULL;
	g_gui_touch_type = TOUCH_TYPE_NONE;
	
	g_gui_touch_event = NULL;
	g_gui_touch_down = 0;
	
	g_gui_touch_event_full_screen = NULL;
	g_gui_touch_down_full_screen = 0;

}


void gui_touch_rebound_cancle()
{
	if(gui_touch_layout_rebound_is_moving())
	{
		gui_touch_layout_rebound_cancle();
	}
}

unsigned char gui_touch_is_moving()
{
	return gui_touch_layout_rebound_is_moving();
}

unsigned char gui_touch_is_free_direction()
{
	if(g_gui_touch_window == NULL)
		return 0;
	return gui_touch_layout_is_free_direction(g_gui_touch_window);
}



