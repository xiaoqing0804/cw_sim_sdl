#include "gui_surface_layout.h"
#include "gui_surface_box.h"
#include "gui_surface_cache.h"
#include "gui_core.h"
#include "gui_core_all.h"
#include "gui_window_history.h"

#include "gui_surface_layout_listview.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_layout_gridview.h"
#include "gui_surface_layout_cellular.h"
#include "gui_surface_layout_apple_cellular.h"
#include "gui_surface_layout_ring.h"
#include "gui_surface_layout_ring_center.h"
#include "gui_surface_layout_scroll.h"
#include "gui_surface_layout_flow.h"
#include "gui_surface_layout_loop.h"
#include "gui_surface_layout_card.h"
#include "gui_surface_layout_matrix.h"

void gui_surface_layout_arrange(gui_surface_struct* surface)
{
    if(surface == NULL || surface->screen == NULL)
        return;

	switch(surface->screen->type)
	{
		case TYPE_GUI_LAYOUT_LIST:
			gui_surface_layout_listview_arrange(surface);
			break;

		case TYPE_GUI_LAYOUT_PAGE:
			gui_surface_layout_pageview_arrange(surface);
			break;

		case TYPE_GUI_LAYOUT_GRID:
			gui_surface_layout_gridview_arrange(surface);
			break;

		case TYPE_GUI_LAYOUT_CELLULAR:
			gui_surface_layout_cellular_arrange(surface);
			break;

	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		gui_surface_layout_apple_cellular_arrange(surface);
		break;

		case TYPE_GUI_LAYOUT_LOOP:
			gui_surface_layout_loop_arrange(surface);
			break;

		case TYPE_GUI_LAYOUT_RING:
			gui_surface_layout_ring_arrange(surface);
			break;
		// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
		// 废弃 	gui_surface_layout_ring_center_arrange(surface);
		// 废弃 	break;
		case TYPE_GUI_LAYOUT_SCROLL:
			gui_surface_layout_scrollview_arrange(surface);
			break;
		case TYPE_GUI_LAYOUT_FLOW:
			gui_surface_layout_flowview_arrange(surface);
			break;

        case TYPE_GUI_LAYOUT_CARD:
            gui_surface_layout_card_arrange(surface);
            break;

		case TYPE_GUI_LAYOUT_MATRIX:
			gui_surface_layout_matrix_arrange(surface);
		break;
	}
}

unsigned char gui_surface_layout_is_delay_create_widget(const gui_screen_struct* screen,gui_widget_struct* widget)
{
	switch(screen->type)
	{
		case TYPE_GUI_LAYOUT_LIST:
			return gui_surface_layout_listview_is_delay_create_widget(screen, widget);
		default:
			return 0;
	}
}

/********************************************偏移****************************************************/
short gui_surface_layout_get_offset_x(gui_surface_struct* surface)
{
	gui_layout_header_struct* layout_header = &surface->layout.header;
	return layout_header->offset_x;
}

short gui_surface_layout_get_offset_y(gui_surface_struct* surface)
{
	gui_layout_header_struct* layout_header = &surface->layout.header;
	return layout_header->offset_y;
}

void gui_surface_layout_restore_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y)	// Taylor.Le, +
{
	if(surface == NULL || surface->screen == NULL)
		return;

	switch(surface->screen->type)
	{
		case TYPE_GUI_LAYOUT_LIST:
			
			if (layout_offset_y < surface->layout.list.min_offset) {
				layout_offset_y = surface->layout.list.min_offset;
			}
			else if (layout_offset_y > surface->layout.list.max_offset) {
				layout_offset_y = surface->layout.list.max_offset;
			}
			break;
		case TYPE_GUI_LAYOUT_RING:
			SYS_DEBUG("gui: surface_layout_restore_offset(%d)", layout_offset_x);
			if (layout_offset_x > 0) {
				layout_offset_x = ((layout_offset_x + surface->layout.ring.item_gap/2) / surface->layout.ring.item_gap)*surface->layout.ring.item_gap;
			}
			else {
				layout_offset_x = ((layout_offset_x - surface->layout.ring.item_gap /2) / surface->layout.ring.item_gap)*surface->layout.ring.item_gap;
			}
		    gui_layout_ring_struct *ring = &surface->layout.ring;
			ring->auto_start = 0;
			SYS_DEBUG("layout_offset_x=%d",layout_offset_x);
			break;
		case TYPE_GUI_LAYOUT_LOOP:
			if (layout_offset_y > 0) {
				layout_offset_y = ((layout_offset_y + surface->layout.loop.item_gap/2) / surface->layout.loop.item_gap)*surface->layout.loop.item_gap;
			}
			else {
				layout_offset_y = ((layout_offset_y - surface->layout.loop.item_gap /2) / surface->layout.loop.item_gap)*surface->layout.loop.item_gap;
			}
			break;
	}

	gui_surface_layout_set_offset(surface, layout_offset_x, layout_offset_y);
}


void gui_surface_layout_set_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y)
{
	if(surface == NULL || surface->screen == NULL)
		return;

	switch(surface->screen->type)
	{
		case TYPE_GUI_LAYOUT_LIST:
			gui_surface_layout_listview_offset(surface,layout_offset_x,layout_offset_y);
			break;

		case TYPE_GUI_LAYOUT_PAGE:
            gui_surface_layout_pageview_offset(surface,layout_offset_x,layout_offset_y);
			break;

		case TYPE_GUI_LAYOUT_GRID:
			gui_surface_layout_gridview_offset(surface,layout_offset_x,layout_offset_y);
			break;

		case TYPE_GUI_LAYOUT_CELLULAR:
			gui_surface_layout_cellular_offset(surface,layout_offset_x,layout_offset_y);
			break;

	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		gui_surface_layout_apple_cellular_offset(surface, layout_offset_x, layout_offset_y);
		break;

		case TYPE_GUI_LAYOUT_LOOP:
			gui_surface_layout_loop_offset(surface,layout_offset_x,layout_offset_y);
			break;

		case TYPE_GUI_LAYOUT_RING:
			gui_surface_layout_ring_offset(surface,layout_offset_x,layout_offset_y);
			break;
		// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
		// 废弃 	gui_surface_layout_ring_center_offset(surface,layout_offset_x,layout_offset_y);
		// 废弃 	break;
		case TYPE_GUI_LAYOUT_SCROLL:
			gui_surface_layout_scrollview_offset(surface,layout_offset_x,layout_offset_y);
			break;
		case TYPE_GUI_LAYOUT_FLOW:
			gui_surface_layout_flowview_offset(surface,layout_offset_x,layout_offset_y);
			break;

        case TYPE_GUI_LAYOUT_CARD:
            gui_surface_layout_card_set_offset(surface, layout_offset_x, layout_offset_y);
            break;

		case TYPE_GUI_LAYOUT_MATRIX:
			gui_surface_layout_matrix_offset(surface, layout_offset_x, layout_offset_y);
		break;
	}
}


void gui_surface_layout_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y)
{
	GUI_DEBUG("gui_surface_layout_move");
	gui_layout_header_struct* layout_header = &surface->layout.header;
	short layout_offset_x = layout_header->offset_x + move_offset_x;
	short layout_offset_y = layout_header->offset_y + move_offset_y;
	gui_surface_layout_set_offset(surface,layout_offset_x,layout_offset_y);
}


void gui_surface_layout_move_end(gui_surface_struct* surface)
{
    if(surface == NULL || surface->screen == NULL)
        return;

	switch(surface->screen->type)
	{
		case TYPE_GUI_LAYOUT_RING:
			gui_surface_layout_ring_move_end(surface);
			break;
		// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
		// 废弃 	gui_surface_layout_ring_center_move_end(surface);
		// 废弃 	break;

        case TYPE_GUI_LAYOUT_CARD:
            gui_surface_layout_card_move_end(surface);
            break;
	}
}


void gui_surface_layout_move_cancle(gui_surface_struct* surface)
{
    if(surface == NULL || surface->screen == NULL)
        return;

	switch(surface->screen->type)
	{
		case TYPE_GUI_LAYOUT_RING:
			gui_surface_layout_ring_move_end(surface);
			break;
		// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
		// 废弃 	gui_surface_layout_ring_center_move_end(surface);
		// 废弃 	break;

        case TYPE_GUI_LAYOUT_CARD:
            gui_surface_layout_card_move_end(surface);
            break;
	}
}



/***************************************前后台切换****************************************************/

//当从后台返回时，需要把之前的位置重新取出来
void gui_surface_layout_entry(const gui_window_struct* window)
{
	gui_surface_struct* surface = gui_surface_get_surface_by_window((gui_window_struct*)window);
	gui_window_history_struct* history = gui_window_history_find(window);
	if(history != NULL && surface != NULL) //主界面无历史
	{
		if(history->has_record == 1)
		{
			// Taylor.Le, -gui_surface_layout_set_offset(surface,history->record.layout_offset_x,history->record.layout_offset_y);
			gui_surface_layout_restore_offset(surface,history->record.layout_offset_x,history->record.layout_offset_y);
			history->has_record = 0;
		}
	}
}

void gui_surface_layout_clear_history(const gui_window_struct* window)
{
	gui_window_history_struct* history = gui_window_history_find(window);
	if(history != NULL) //主界面无历史
	{
		history->record.layout_offset_x = 0;
		history->record.layout_offset_y = 0;
		history->has_record = 0;
	}
}


//进入后台时，保存当前的位置
void gui_surface_layout_exit(const gui_window_struct* window)
{
	gui_surface_struct* surface = gui_surface_get_surface_by_window((gui_window_struct*)window);
	if(surface == NULL || surface->screen == NULL)
        return;
		
	gui_window_history_struct* history = gui_window_history_find(window);
	if(history != NULL)//主界面无历史
	{
		history->record.layout_offset_x = gui_surface_layout_get_offset_x(surface);
		history->record.layout_offset_y = gui_surface_layout_get_offset_y(surface);
		history->has_record = 1;
	}
	
	switch(surface->screen->type)
	{
		case TYPE_GUI_LAYOUT_CELLULAR:
			gui_surface_layout_cellular_exit();
			break;

	case TYPE_GUI_LAYOUT_APPLE_CELLULAR:
		gui_surface_layout_apple_cellular_exit();
		break;

		// 废弃 case TYPE_GUI_LAYOUT_RING_CENTER:
		// 废弃 	gui_surface_layout_ring_center_exit();
		// 废弃 	break;

		case TYPE_GUI_LAYOUT_LOOP:
			gui_surface_layout_loop_exit();
			break;

        case TYPE_GUI_LAYOUT_CARD:
            gui_surface_layout_card_exit();
            break;

		case TYPE_GUI_LAYOUT_MATRIX:
			gui_surface_layout_matrix_exit();
		break;
	}
	
}


