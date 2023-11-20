#include "feature_all.h"

#include "gui_touch_layout.h"
#include "gui_window_history.h"
#include "gui_touch_layout_rebound.h"

#include "gui_touch_layout_listview.h"
#include "gui_touch_layout_gridview.h"
#include "gui_touch_layout_cellular.h"
#include "gui_touch_layout_pageview.h"
#include "gui_touch_layout_ring.h"
#include "gui_touch_layout_scroll.h"
#include "gui_touch_layout_loop.h"

#include "gui_surface_layout_listview.h"
#include "gui_surface_layout_gridview.h"
#include "gui_surface_layout_cellular.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_layout_scroll.h"
#include "gui_surface_layout_flow.h"

#include "gui_surface_layout_ring.h"
#include "gui_surface_layout_loop.h" 
#include "gui_surface_layout_matrix.h"


//--------------------------down--------------------------------

TOUCH_TYPE gui_touch_layout_check_down_type(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	gui_surface_struct* surface = gui_surface_get_surface(screen);
	
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_GRID:
		if(top_window->click_on_layout_item && gui_surface_layout_gridview_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;
	
	case TYPE_GUI_LAYOUT_LIST:
		if(top_window->click_on_layout_item && gui_surface_layout_listview_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;
	
	case TYPE_GUI_LAYOUT_PAGE:
		if(top_window->click_on_layout_item && gui_surface_layout_pageview_get_item_id(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_CELLULAR:
		if(top_window->click_on_layout_item && gui_surface_layout_cellular_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		if(top_window->click_on_layout_item && gui_surface_layout_apple_cellular_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_RING:
		if(top_window->click_on_layout_item && gui_surface_layout_ring_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_LOOP:
		if(top_window->click_on_layout_item && gui_surface_layout_loop_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;

	// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
	// 废弃 	if(top_window->click_on_layout_item && gui_surface_layout_ring_center_get_item_index(surface,touch_point) >= 0)
	// 废弃 		return TOUCH_TYPE_LAYOUT_ITEM;
	// 废弃 	return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_SCROLL:
		if(top_window->click_on_layout_item && gui_surface_layout_scrollview_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_FLOW:
		if(top_window->click_on_layout_item && gui_surface_layout_flowview_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
		return TOUCH_TYPE_LAYOUT;

    case TYPE_GUI_LAYOUT_CARD:
		if(top_window->click_on_layout_item && gui_surface_layout_card_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
        return TOUCH_TYPE_LAYOUT;

    case TYPE_GUI_LAYOUT_MATRIX:
		if(top_window->click_on_layout_item && gui_surface_layout_matrix_get_item_index(surface,touch_point) >= 0)
			return TOUCH_TYPE_LAYOUT_ITEM;
        return TOUCH_TYPE_LAYOUT;

	default: return TOUCH_TYPE_NONE;
		
	}
}

void gui_touch_layout_check_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	gui_surface_struct* surface = gui_surface_get_surface(screen);
	
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_GRID:
		gui_touch_layout_gridview_check_start(top_window,touch_point);
		break;
	
	case TYPE_GUI_LAYOUT_LIST:
		gui_touch_layout_listview_touch_start(top_window,touch_point);
		break;
	
	case TYPE_GUI_LAYOUT_PAGE:
		gui_touch_layout_pageview_touch_start(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_CELLULAR:
		gui_touch_layout_cellular_touch_start(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		gui_touch_layout_apple_cellular_touch_start(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_LOOP:
		gui_touch_layout_loop_touch_start(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_RING:
		gui_touch_layout_ring_touch_start(top_window,touch_point);
		break;

	// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
	// 废弃 	gui_touch_layout_ring_center_touch_start(top_window,touch_point);
	// 废弃 	break;
	case TYPE_GUI_LAYOUT_SCROLL:
		gui_touch_layout_scrollview_touch_start(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_FLOW:
		gui_touch_layout_flowview_touch_start(top_window,touch_point);
		break;

    case TYPE_GUI_LAYOUT_CARD:
        gui_touch_layout_card_touch_start(top_window, touch_point);
        break;

	case TYPE_GUI_LAYOUT_MATRIX:
		gui_touch_layout_matrix_touch_start(top_window,touch_point);
		break;

	default: break;
	}
}



//-------------------------move---------------------------------

static void gui_touch_layout_moveing(const gui_window_struct* top_window)
{
	gui_surface_struct* surface = gui_surface_get_surface_by_window(top_window);
	if(surface != NULL && top_window != NULL && top_window->layout_moving != NULL)
	{
		top_window->layout_moving(&surface->layout.header);
	}
}

//得到移动时的类型判断是不是点击在排版上了
TOUCH_TYPE gui_touch_layout_check_move_type(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	gui_surface_struct* surface = gui_surface_get_surface(screen);
	if(surface != NULL)
	{
		if(screen->type == TYPE_GUI_LAYOUT_GRID && surface->layout.grid.scroll)
			return TOUCH_TYPE_LAYOUT;

		if(screen->type == TYPE_GUI_LAYOUT_LIST && surface->layout.list.scroll)
			return TOUCH_TYPE_LAYOUT;

		if(screen->type == TYPE_GUI_LAYOUT_LOOP && surface->layout.loop.scroll)
			return TOUCH_TYPE_LAYOUT;
		
		if(screen->type == TYPE_GUI_LAYOUT_SCROLL
			|| screen->type == TYPE_GUI_LAYOUT_PAGE
			|| screen->type == TYPE_GUI_LAYOUT_CELLULAR 
			|| screen->type == TYPE_GUI_LAYOUT_APPLE_CELLULAR 
			|| screen->type == TYPE_GUI_LAYOUT_RING
			// 废弃 || screen->type == TYPE_GUI_LAYOUT_RING_CENTER
			|| screen->type == TYPE_GUI_LAYOUT_CARD
			|| screen->type == TYPE_GUI_LAYOUT_FLOW
			|| screen->type == TYPE_GUI_LAYOUT_MATRIX )
			return TOUCH_TYPE_LAYOUT;
	}
	return TOUCH_TYPE_NONE;
}

//只能上下滑动
TOUCH_TYPE gui_touch_layout_check_only_move_updown(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	gui_surface_struct* surface = gui_surface_get_surface(screen);
	if(surface == NULL)
		return TOUCH_TYPE_NONE;
	
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_GRID:
		{
			gui_layout_grid_struct* grid = &surface->layout.grid;
			if(grid->scroll)
			{
				if(grid->can_swipe)
				{
					if(grid->height <= LCD_SIZE_HEIGHT)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(grid->offset_y == 0 && touch_point->direction == DIRECTION_TYPE_UP)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(grid->offset_y == -(grid->height - LCD_SIZE_HEIGHT) && touch_point->direction == DIRECTION_TYPE_DOWN)
						return TOUCH_TYPE_LAYOUT_FORBID;
				}
				gui_touch_layout_gridview_move(top_window,touch_point);
				gui_touch_layout_moveing(top_window);
				return TOUCH_TYPE_LAYOUT;
			}
		}
		break;

	case TYPE_GUI_LAYOUT_PAGE:
		{
			gui_layout_page_struct* page = &surface->layout.page;
			if(page->orientation == ORIENTATION_TYPE_VERTICAL)
			{
				if(page->can_swipe)
				{
					if(page->total == 1)
						return TOUCH_TYPE_LAYOUT_FORBID;
					
					if(page->offset_y == 0 && touch_point->direction == DIRECTION_TYPE_UP)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(page->curr_page == (page->total - 1) && touch_point->direction == DIRECTION_TYPE_DOWN)
						return TOUCH_TYPE_LAYOUT_FORBID;				
				}
				gui_touch_layout_pageview_touch_move(top_window,touch_point);
				gui_touch_layout_moveing(top_window);
				return TOUCH_TYPE_LAYOUT;
			}
		}
		break;
	
	case TYPE_GUI_LAYOUT_LIST:
		{
			gui_layout_list_struct* list = &surface->layout.list;
			if(list->scroll)
			{
				if(list->can_swipe)
				{
					if(list->height <= LCD_SIZE_HEIGHT)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(touch_point->direction == DIRECTION_TYPE_UP)
					{
					    if (list->offset_y >= list->max_offset && !list->force_up)
							return TOUCH_TYPE_LAYOUT_FORBID;
					}
					if(touch_point->direction == DIRECTION_TYPE_DOWN)
					{
						if(list->offset_y <= list->min_offset && !list->force_down)
							return TOUCH_TYPE_LAYOUT_FORBID;
					}
				}
				gui_touch_layout_listview_touch_move(top_window,touch_point);
				gui_touch_layout_moveing(top_window);
				return TOUCH_TYPE_LAYOUT;
			}
		}
		break;	

	case TYPE_GUI_LAYOUT_SCROLL:
		{
			SYS_DEBUG("TYPE_GUI_LAYOUT_SCROLL");
			gui_layout_scroll_struct* scroll = &surface->layout.scroll;
			if(scroll->scroll)
			{
				if(scroll->can_swipe)
				{
					if(scroll->height <= LCD_SIZE_HEIGHT)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(scroll->offset_y == 0 && touch_point->direction == DIRECTION_TYPE_UP)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(scroll->offset_y == -(scroll->height - LCD_SIZE_HEIGHT) && touch_point->direction == DIRECTION_TYPE_DOWN)
						return TOUCH_TYPE_LAYOUT_FORBID;
				}
				SYS_DEBUG("TYPE_GUI_LAYOUT_SCROLL 1");
				gui_touch_layout_scrollview_touch_move(top_window,touch_point);
				gui_touch_layout_moveing(top_window);
				return TOUCH_TYPE_LAYOUT;
			}
		}
		break;

	case TYPE_GUI_LAYOUT_FLOW:
		{
			gui_layout_flow_struct* flow = &surface->layout.flow;
			if(flow->scroll)
			{
				if(flow->can_swipe)
				{
					if(flow->height <= LCD_SIZE_HEIGHT)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(flow->offset_y == 0 && touch_point->direction == DIRECTION_TYPE_UP)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(flow->offset_y == -(flow->height - LCD_SIZE_HEIGHT) && touch_point->direction == DIRECTION_TYPE_DOWN)
						return TOUCH_TYPE_LAYOUT_FORBID;
				}
				gui_touch_layout_flowview_touch_move(top_window,touch_point);
				gui_touch_layout_moveing(top_window);
				return TOUCH_TYPE_LAYOUT;
			}
		}
		break;
	case TYPE_GUI_LAYOUT_LOOP:
		{
			GUI_DEBUG("gui_touch_layout_check_only_move_updown TYPE_GUI_LAYOUT_LOOP");
				
			gui_layout_loop_struct* loop = &surface->layout.loop;
			if(loop->scroll)
			{
				GUI_DEBUG("gui_touch_layout_check_only_move_updown TYPE_GUI_LAYOUT_LOOP");
				gui_touch_layout_loop_touch_move(top_window,touch_point);
				gui_touch_layout_moveing(top_window);
				return TOUCH_TYPE_LAYOUT;
			}
		}
		break;

    case TYPE_GUI_LAYOUT_CARD:
        {
            gui_touch_layout_card_touch_move(top_window, touch_point);
			gui_touch_layout_moveing(top_window);
        	return TOUCH_TYPE_LAYOUT;
        }
        break;

	default:break;
	}
	return TOUCH_TYPE_NONE;
}

//只能左右滑动
TOUCH_TYPE gui_touch_layout_check_only_move_leftright(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
    
    gui_surface_struct* surface = gui_surface_get_surface(screen);
    if (surface == NULL) {
        return TOUCH_TYPE_NONE;
    }
    
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_PAGE:
		{
			gui_layout_page_struct* page = &surface->layout.page;
			if(page->orientation == ORIENTATION_TYPE_HORIZONTAL)
			{
				if(page->can_swipe)
				{
					if(page->total == 1)
						return TOUCH_TYPE_LAYOUT_FORBID;
					
					if(page->offset_x == 0 && touch_point->direction == DIRECTION_TYPE_LEFT)
						return TOUCH_TYPE_LAYOUT_FORBID;
					if(page->curr_page == (page->total - 1) && touch_point->direction == DIRECTION_TYPE_RIGHT)
						return TOUCH_TYPE_LAYOUT_FORBID;				
				}
				gui_touch_layout_pageview_touch_move(top_window,touch_point);
				gui_touch_layout_moveing(top_window);
				return TOUCH_TYPE_LAYOUT;
			}
		}
		break;

    case TYPE_GUI_LAYOUT_CARD:
        {
            gui_touch_layout_card_touch_move(top_window, touch_point);
			gui_touch_layout_moveing(top_window);
            return TOUCH_TYPE_LAYOUT;
        }
        break;

	default:break;
	}
	return TOUCH_TYPE_NONE;
}

//可以上下左右滑动
TOUCH_TYPE gui_touch_layout_check_move_all(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_CELLULAR:
		gui_touch_layout_cellular_touch_move(top_window,touch_point);
		gui_touch_layout_moveing(top_window);
		return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		gui_touch_layout_apple_cellular_touch_move(top_window,touch_point);
		gui_touch_layout_moveing(top_window);
		return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_RING:
		gui_touch_layout_ring_touch_move(top_window,touch_point);
		gui_touch_layout_moveing(top_window);
		return TOUCH_TYPE_LAYOUT;

	// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
	// 废弃 	gui_touch_layout_ring_center_touch_move(top_window,touch_point);
	// 废弃 	return TOUCH_TYPE_LAYOUT;

    case TYPE_GUI_LAYOUT_CARD:
        gui_touch_layout_card_touch_move(top_window, touch_point);
		gui_touch_layout_moveing(top_window);
        return TOUCH_TYPE_LAYOUT;

	case TYPE_GUI_LAYOUT_MATRIX:
		gui_touch_layout_matrix_touch_move(top_window,touch_point);
		gui_touch_layout_moveing(top_window);
		return TOUCH_TYPE_LAYOUT;

	default:break;
	}
	return TOUCH_TYPE_NONE;
}

//---------------------------up-------------------------------

//抬起时是点击事件
void gui_touch_layout_check_click(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_GRID:
		gui_touch_layout_gridview_click_on_item(top_window,touch_point);
		break;
	
	case TYPE_GUI_LAYOUT_LIST:
		gui_touch_layout_listview_click_on_item(top_window,touch_point);
		break;
	
	case TYPE_GUI_LAYOUT_PAGE:
		gui_touch_layout_pageview_click_on_item(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_CELLULAR:
		gui_touch_layout_cellular_click_on_item(top_window,touch_point);
		break;
	
	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		gui_touch_layout_apple_cellular_click_on_item(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_LOOP:
		gui_touch_layout_loop_click_on_item(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_RING:
		gui_touch_layout_ring_click_on_item(top_window,touch_point);
		break;
	// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
	// 废弃 	gui_touch_layout_ring_center_click_on_item(top_window,touch_point);
	// 废弃 	break;

	case TYPE_GUI_LAYOUT_SCROLL:
		gui_touch_layout_scrollview_click_on_item(top_window,touch_point);
		break;
	case TYPE_GUI_LAYOUT_FLOW:
		gui_touch_layout_flowview_click_on_item(top_window,touch_point);
		break;

    case TYPE_GUI_LAYOUT_CARD:
        gui_touch_layout_card_click_on_item(top_window, touch_point);
        break;

	case TYPE_GUI_LAYOUT_MATRIX:
		gui_touch_layout_matrix_click_on_item(top_window,touch_point);
		break;
        
	default:break;
		
	}

}

//触摸抬起事件
void gui_touch_layout_check_up(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_GRID:
		gui_touch_layout_gridview_up(top_window,touch_point);
		break;
	
	case TYPE_GUI_LAYOUT_SCROLL:
		gui_touch_layout_scrollview_touch_end(top_window,touch_point);
		break;
	
	case TYPE_GUI_LAYOUT_LIST:
		gui_touch_layout_listview_touch_end(top_window,touch_point);
		break;
	
	case TYPE_GUI_LAYOUT_PAGE:
		gui_touch_layout_pageview_touch_end(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_CELLULAR:
		gui_touch_layout_cellular_touch_end(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		gui_touch_layout_apple_cellular_touch_end(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_LOOP:
		gui_touch_layout_loop_touch_end(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_RING:
		gui_touch_layout_ring_touch_end(top_window,touch_point);
		break;
	// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
	// 废弃 	gui_touch_layout_ring_center_touch_end(top_window,touch_point);
	// 废弃 	break;
	case TYPE_GUI_LAYOUT_FLOW:
		gui_touch_layout_flowview_touch_end(top_window,touch_point);
		break;

    case TYPE_GUI_LAYOUT_CARD:
        gui_touch_layout_card_touch_end(top_window, touch_point);
        break;

	case TYPE_GUI_LAYOUT_MATRIX:
		gui_touch_layout_matrix_touch_end(top_window,touch_point);
		break;

	default:break;
		
	}

}

//释放响应事件
void gui_touch_layout_check_free(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	const gui_screen_struct* screen = top_window->screen;
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_LIST:
		gui_touch_layout_listview_touch_free(top_window,touch_point);
		break;

	case TYPE_GUI_LAYOUT_LOOP:
		break;

	default:
		break;
	}
}


void gui_touch_layout_check_cancle(const gui_window_struct* top_window,unsigned char touch_type)
{
	const gui_screen_struct* screen = top_window->screen;
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_GRID:
		gui_touch_layout_gridview_cancle(top_window);
		break;
	
	case TYPE_GUI_LAYOUT_LIST:
		gui_touch_layout_listview_touch_cancle(top_window);
		break;
	
	case TYPE_GUI_LAYOUT_PAGE:
		gui_touch_layout_pageview_touch_cancle(top_window);
		break;

	case TYPE_GUI_LAYOUT_RING:
		gui_touch_layout_ring_touch_cancle(top_window);
		break;
		
	// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
	// 废弃 	gui_touch_layout_ring_center_touch_cancle(top_window);
	// 废弃 	break;

	case TYPE_GUI_LAYOUT_SCROLL:
		gui_touch_layout_scrollview_touch_cancle(top_window,touch_type);
		break;
		
	case TYPE_GUI_LAYOUT_FLOW:
		gui_touch_layout_flowview_touch_cancle(top_window);
		break;
		
	case TYPE_GUI_LAYOUT_CELLULAR:
		gui_touch_layout_cellular_touch_cancle(top_window);
		break;

	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		gui_touch_layout_apple_cellular_touch_cancle(top_window);
		break;

    case TYPE_GUI_LAYOUT_CARD:
        gui_touch_layout_card_touch_cancle(top_window);
        break;

	case TYPE_GUI_LAYOUT_MATRIX:
		gui_touch_layout_matrix_touch_cancle(top_window);
		break;

	default:break;
		
	}		
}

unsigned char gui_touch_layout_is_free_direction(const gui_window_struct* top_window)
{
	const gui_screen_struct* screen = top_window->screen;
	switch(screen->type)
	{
	case TYPE_GUI_LAYOUT_CELLULAR:
	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
	case TYPE_GUI_LAYOUT_MATRIX:
		return 1;

	case TYPE_GUI_LAYOUT_RING:
		return 1;
	// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
	// 废弃 	return 1;
		
	default:break;
	}
	return 0;
}



