#include "gui_surface_layout_gridview.h"


/*******************************数据接口************************************/

short gui_surface_layout_gridview_get_item_id(gui_surface_struct* surface,short index)
{
	gui_box_struct* box = gui_surface_layout_gridview_get_item(surface,index);
	return (box != NULL) ? box->id : 0;
}

gui_box_struct* gui_surface_layout_gridview_get_item(gui_surface_struct* surface,short index)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
		{
			if(count++ == index)
				return box;
		}
		box = box->brother;
	}
	return NULL;
}

short gui_surface_layout_gridview_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point)
{
	gui_layout_grid_struct* grid = &surface->layout.grid;
	gui_box_struct* box = surface->child;
	geometry_rect rect_box;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
		{
			rect_box.x = box->x;
			rect_box.y = box->y;
			rect_box.width = grid->row_width;
			rect_box.height = grid->row_height;
			if(check_rect_contain_point_xy(&rect_box,touch_point->x,touch_point->y))
				return count;
			count++;
		}
		box = box->brother;
	}		
	return -1;

}



/*******************************操作接口************************************/


//根据排版类型，进行排版
void gui_surface_layout_gridview_arrange(gui_surface_struct* surface)
{
	const gui_layout_grid_struct* grid_config = surface->screen->layout_config;
	gui_layout_grid_struct* grid = &surface->layout.grid;
    
    memset(grid, 0, sizeof(gui_layout_grid_struct));
	grid->row_height = grid_config->row_height;
	grid->row_column = grid_config->row_column;

	grid->top = grid_config->top;
	grid->bottom = grid_config->bottom;
	grid->left = grid_config->left;
	grid->right = grid_config->right;
	grid->space = grid_config->space;

	grid->scroll = grid_config->scroll;
	grid->can_swipe = grid_config->can_swipe;
	
	gui_surface_layout_gridview_commit_position(surface);

}


//对排版中的子元素，使用指定的偏移
void gui_surface_layout_gridview_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y)
{
	gui_layout_grid_struct* grid = &surface->layout.grid;
	grid->offset_x = layout_offset_x;
	grid->offset_y = layout_offset_y;
	gui_surface_layout_gridview_commit_position(surface);
}

//对排版中的子元素，进行指定的偏移
void gui_surface_layout_gridview_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y)
{
	gui_layout_grid_struct* grid = &surface->layout.grid;
	grid->offset_x += move_offset_x;
	grid->offset_y += move_offset_y;
	gui_surface_layout_gridview_commit_position(surface);
}

void gui_surface_layout_gridview_commit_position(gui_surface_struct* surface)
{
	gui_layout_grid_struct* grid = &surface->layout.grid;
	gui_box_struct* box = surface->child;
	
	grid->row_width = (LCD_SIZE_WIDTH - grid->left - grid->right + grid->space)/grid->row_column;
	short column = 0;
	short row = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
		{
			short offset_x = (grid->row_width - box->width)/2;
			box->x = grid->left + column * grid->row_width + offset_x;
			box->y = grid->top + row * (grid->row_height + grid->space) + grid->offset_y;
			if(++column >= grid->row_column)
			{
				column = 0;
				row++;
			}
		}
		box = box->brother;
	}
	short height = grid->top + row * (grid->row_height + grid->space) - grid->space + grid->bottom;
	grid->total = row;
	grid->height = height < LCD_SIZE_HEIGHT ? LCD_SIZE_HEIGHT : height;;

    if (height > LCD_SIZE_HEIGHT) {
        grid->min_offset = LCD_SIZE_HEIGHT - height;
    }
    grid->max_offset = 0;
    grid->item_gap = grid->row_height + grid->space;
}




