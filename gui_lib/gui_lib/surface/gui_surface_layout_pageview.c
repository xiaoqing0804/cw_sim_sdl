#include "gui_surface_layout_pageview.h" 
#include "gui_surface_node.h"
#include "gui_window_history.h"

/*********************************数据获取***************************************/

short gui_surface_layout_pageview_get_count(gui_surface_struct* surface)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
			count++;
		box = box->brother;
	}
	return count;
}

gui_box_struct* gui_surface_layout_pageview_get_page(gui_surface_struct* surface,short curr_page)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
		{
			if(count++ == curr_page)
			{
				return box;
			}
		}
		box = box->brother;
	}
	return NULL;
}

short gui_surface_layout_pageview_get_item_id(gui_surface_struct* surface,gui_touch_point_struct* touch_point)
{
	geometry_rect rect_node;
	gui_layout_page_struct* page = &surface->layout.page;
	gui_box_struct* box = gui_surface_layout_pageview_get_page(surface,page->curr_page);
	if(box != NULL)
	{
		gui_node_struct* find_node = NULL;
		gui_node_struct* node = box->child;
		while(node != NULL)
		{
			gui_surface_node_get_rect_in_screen(surface,box,node,&rect_node);
			if(check_rect_contain_point_xy(&rect_node,touch_point->x,touch_point->y))
				find_node = node;
			node = node->brother;
		}
		if(find_node != NULL)
		{
			return find_node->id;
		}
	}
	return 0;
}


/*******************************排版***************************************************/

void gui_surface_layout_pageview_arrange(gui_surface_struct* surface)
{
	const gui_layout_page_struct* layout_config = surface->screen->layout_config;
	gui_layout_page_struct* page = &surface->layout.page;

    memset(page, 0, sizeof(gui_layout_page_struct));
	page->can_swipe = layout_config->can_swipe;
    page->page_width = layout_config->page_width != 0 ? layout_config->page_width : LCD_SIZE_WIDTH;
    page->page_height = layout_config->page_height != 0 ? layout_config->page_height : LCD_SIZE_HEIGHT;

	page->curr_page = layout_config->curr_page;
	if(layout_config->orientation == ORIENTATION_TYPE_HORIZONTAL || layout_config->orientation == ORIENTATION_TYPE_VERTICAL)
		page->orientation = layout_config->orientation;
	else
		page->orientation = ORIENTATION_TYPE_HORIZONTAL;

	gui_surface_layout_pageview_commit_position(surface);

    if (layout_config->orientation == ORIENTATION_TYPE_HORIZONTAL) {
        page->max_offset = (LCD_SIZE_WIDTH - page->page_width)/2;
        page->min_offset = (1 - page->total)*page->page_width - page->max_offset;
        page->item_gap   = page->page_width;
    }
    else {
        page->max_offset = (LCD_SIZE_HEIGHT - page->page_height)/2;
        page->min_offset = (1 - page->total)*page->page_height - page->max_offset;
        page->item_gap   = page->page_height;
    }
}



void gui_surface_layout_pageview_show_item(gui_surface_struct* surface,short curr_page)
{
	gui_layout_page_struct* page = &surface->layout.page;
	page->curr_page = curr_page;
	
	gui_window_history_struct* top = gui_window_history_get_top();
	if(top != NULL)
	{
		gui_layout_value_struct event = {
		    // 20220519 Taylor.Le,  avoid div0 .page.progress = curr_page * 100 /(page->total-1),   //0-100
            .page.progress = ((page->total <= 1) ? 100 : (curr_page * 100 /(page->total-1))),    // avoid div0 //0-100
			.page.index = curr_page,
			.page.total = page->total,
		};
		if(top->window && top->window->layout_value_changed)
		{
			top->window->layout_value_changed(&event);
		}
	}
}


void gui_surface_layout_pageview_check_switch_page(gui_surface_struct* surface)
{
	gui_layout_page_struct* page = &(surface->layout.page);
	gui_box_struct* box = surface->child;
	if(page->orientation == ORIENTATION_TYPE_VERTICAL)
	{
		if(ABS(page->offset_y) % LCD_SIZE_HEIGHT == 0)
		{
			short curr_page = ABS(page->offset_y) / LCD_SIZE_HEIGHT;
			if(curr_page != page->curr_page)
			{
				gui_surface_layout_pageview_show_item(surface,curr_page);
			}
		}
	}
	else
	{
		if(ABS(page->offset_x) % (short)(box->width) == 0)
		{
			short curr_page = ABS(page->offset_x) / box->width;
			if(curr_page != page->curr_page)
			{
				gui_surface_layout_pageview_show_item(surface,curr_page);
			}
		}	
	}

}

void gui_surface_layout_pageview_switch_page(gui_surface_struct* surface,short curr_page)
{
	gui_layout_page_struct* page = &surface->layout.page;
	gui_box_struct* box = surface->child;

	page->curr_page = curr_page;
	if(page->orientation == ORIENTATION_TYPE_VERTICAL)
		page->offset_y = -curr_page * LCD_SIZE_HEIGHT;
	else
		page->offset_x = -curr_page * box->width;
	gui_surface_layout_pageview_show_item(surface,curr_page);
}

void gui_surface_layout_pageview_switch_page_by_step(gui_surface_struct* surface,short step)
{
	gui_layout_page_struct* page = &surface->layout.page;
	gui_box_struct* box = surface->child;
	short curr_page = page->curr_page + step;
	if(curr_page < 0)
		curr_page = 0;
	if(curr_page > page->total - 1)
		curr_page = page->total - 1;
	
	page->curr_page = curr_page;
	if(page->orientation == ORIENTATION_TYPE_VERTICAL)
		page->offset_y = -curr_page * LCD_SIZE_HEIGHT;
	else
		page->offset_x = -curr_page * box->width;
	gui_surface_layout_pageview_show_item(surface,curr_page);
}


void gui_surface_layout_pageview_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y)
{
	gui_layout_page_struct* page = &surface->layout.page;
	page->offset_x = layout_offset_x;
	page->offset_y = layout_offset_y;
	gui_surface_layout_pageview_commit_position(surface);
	gui_surface_layout_pageview_check_switch_page(surface);
}

void gui_surface_layout_pageview_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y)
{
	gui_layout_page_struct* page = &surface->layout.page;
	page->offset_x += move_offset_x;
	page->offset_y += move_offset_y;
	gui_surface_layout_pageview_commit_position(surface);
	gui_surface_layout_pageview_check_switch_page(surface);
}

void gui_surface_layout_pageview_commit_position(gui_surface_struct* surface)
{
	gui_layout_page_struct* page = &surface->layout.page;
	short count = 0;
	
	gui_box_struct* box = surface->child;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
		{
			if(page->orientation == ORIENTATION_TYPE_VERTICAL)
			{
				box->x = (LCD_SIZE_WIDTH - box->width) / 2;
				box->y = count * LCD_SIZE_HEIGHT + (LCD_SIZE_HEIGHT - box->height) / 2 + page->offset_y;
			}
			else
			{
				box->x = count * box->width+ (LCD_SIZE_WIDTH - box->width) / 2 + page->offset_x;   //  起始为空位置+n个图片 +偏移位置
				box->y = (LCD_SIZE_HEIGHT - box->height) / 2;
			}
			count++;
		}
		box = box->brother;
	}
	page->total = count;
}



