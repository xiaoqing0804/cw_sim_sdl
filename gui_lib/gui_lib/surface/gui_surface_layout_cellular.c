#include "system_util_math.h"
#include "app_task_main.h"
#include "application.h"

#include "gui_surface_node.h"
#include "gui_surface_layout.h"
#include "gui_surface_layout_cellular.h"
#include "gui_touch_layout_rebound.h"
#include "app_task_main.h"



/*******************************************
**
**对cellular进行排版，移动
**
********************************************/

#if GUI_LAYOUT_CELL_ZOOM_SUPPORT == 1
#define LAYOUT_CELL_ZOOM_MAX_SCALE (2.5f)
#define LAYOUT_CELL_ZOOM_DEFAULT (1)

static unsigned int g_layout_cellular_timer_id = 0;
static unsigned int g_layout_cellular_rebound_timer_id = 0;

#else
#define LAYOUT_CELL_ZOOM_DEFAULT (0)
#endif

static short g_layout_cellular_near_center_box_position = -1;

/*******************************数据接口************************************/

short gui_surface_layout_cellular_get_count(gui_surface_struct* surface)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
			count++;
		box = box->brother;
	}
	return count;
}

short gui_surface_layout_cellular_get_row_num(gui_surface_struct* surface)
{
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	short row_offset = cellular->max_column - cellular->min_column;//像蜂窝一样，每行少一个
	return ( row_offset << 1 ) + 1;
}



short gui_surface_layout_cellular_get_item_id(gui_surface_struct* surface,short index)
{
	gui_box_struct* box = gui_surface_layout_cellular_get_item(surface,index);
	return (box != NULL) ? box->id : 0;
}

const picture_info_struct* gui_surface_layout_cellular_get_max_picture(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children;
	const picture_info_struct* max_picture = (const picture_info_struct*)(*picture_arr);
	return max_picture;
}

const picture_info_struct* gui_surface_layout_cellular_get_default_picture(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children + LAYOUT_CELL_ZOOM_DEFAULT;
	const picture_info_struct* default_picture = (const picture_info_struct*)(*picture_arr);
	return default_picture;
}

const picture_info_struct* gui_surface_layout_cellular_get_min_picture(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children + widget->child_num-1;
	const picture_info_struct* min_picture = (const picture_info_struct*)(*picture_arr);
	return min_picture;
}

gui_box_struct* gui_surface_layout_cellular_get_item(gui_surface_struct* surface,short index)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			if(count++ == index)
				return box;
		}
		box = box->brother;
	}
	return NULL;
}

short gui_surface_layout_cellular_get_item_position(gui_surface_struct* surface,gui_box_struct* find_box)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			if(find_box == box)
				return count;
			count++;
		}
		box = box->brother;
	}
	return -1;
}


//点击在列表的哪个条目上,返回条目编号
short gui_surface_layout_cellular_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point)
{
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_box_struct* box = surface->child;

	geometry_rect rect_box;
	short count = 0;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			rect_box.x = box->x;
			rect_box.y = box->y;
			rect_box.width = cellular->diameter;
			rect_box.height = cellular->diameter;
			if(check_rect_contain_point_xy(&rect_box,touch_point->x,touch_point->y))
				return count;
			count++;
		}
		box = box->brother;
	}
	return -1;
}

gui_box_struct* gui_surface_layout_cellular_get_center_item(gui_surface_struct* surface)
{
	short min_distance = SHORT_MAX;
	gui_box_struct* center = NULL;
	gui_box_struct* box = surface->child;
	short box_radius = box->width / 2;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			short len_x = ABS(box->x + box_radius - LCD_SIZE_HALF_WIDTH);  //到屏幕中心的偏移
			short len_y = ABS(box->y + box_radius - LCD_SIZE_HALF_HEIGHT);  //到屏幕中心的偏移
			short distance = math_sqrt_16((unsigned int)len_x * (unsigned int)len_x + (unsigned int)len_y * (unsigned int)len_y);//离屏幕中心的距离
			if(min_distance > distance)
			{
				min_distance = distance;
				center = box;
			}
		}
		box = box->brother;
	}
	return center;
}


unsigned short gui_surface_layout_cellular_get_next_low_width(gui_surface_struct* surface,gui_widget_struct* widget)
{
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children;
	const picture_info_struct* picture = (const picture_info_struct*)(*picture_arr);
	for(unsigned char i = 0; i < widget->child_num; i++)
	{
		if(picture->width < cellular->diameter)
		{
			return picture->width;
		}
		picture_arr++;
		picture = (const picture_info_struct*)(*picture_arr);
	}
	return cellular->diameter;
}

unsigned short gui_surface_layout_cellular_get_next_hight_width(gui_surface_struct* surface,gui_widget_struct* widget)
{
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children + widget->child_num-1;
	const picture_info_struct* picture = (const picture_info_struct*)(*picture_arr);
	for(unsigned char i = 0; i < widget->child_num; i++)
	{
		if(picture->width > cellular->diameter)
		{
			return picture->width;
		}
		picture_arr--;
		picture = (const picture_info_struct*)(*picture_arr);
	}
	return cellular->diameter;
}


void gui_surface_layout_cellular_move_near_center(gui_surface_struct* surface,gui_box_struct* near_center_box)
{
	if(near_center_box != NULL)
	{
		short offset_x = LCD_SIZE_HALF_WIDTH - (near_center_box->x + near_center_box->width/2);
		short offset_y = LCD_SIZE_HALF_HEIGHT - (near_center_box->y + near_center_box->height/2);
		gui_surface_layout_move(surface, offset_x, offset_y);
	}

}

void gui_surface_layout_cellular_scale(gui_surface_struct* surface,float scale)
{
	const gui_layout_cellular_struct* layout_config = surface->screen->layout_config;
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;

	cellular->margin = layout_config->margin * scale;
	cellular->space = layout_config->space * scale;

	short row = gui_surface_layout_cellular_get_row_num(surface);
	short width =  cellular->max_column * cellular->diameter + (cellular->max_column-1) * cellular->space;
	short height =  row * cellular->diameter + (row - 1) * cellular->space;
	cellular->width = width  + cellular->margin * 2;
	cellular->height = height + cellular->margin * 2;

	gui_surface_layout_cellular_commit_position(surface);

}

//确定返回时的中心点
void gui_surface_layout_cellular_set_near_center_box(gui_surface_struct* surface,gui_box_struct* box)
{
	g_layout_cellular_near_center_box_position = gui_surface_layout_cellular_get_item_position(surface,box);
}


void gui_surface_layout_cellular_exit()
{
#if GUI_LAYOUT_CELL_ZOOM_SUPPORT == 1
	gui_surface_layout_cellular_clear_zoom_timer();
#endif
}

#if GUI_LAYOUT_CELL_ZOOM_SUPPORT == 1

static void gui_surface_layout_cellular_timer_zoom_in(unsigned int timer, void* param)
{
	application_stop_user_timer(g_layout_cellular_timer_id);
	g_layout_cellular_timer_id = 0;

	gui_surface_struct* surface = (gui_surface_struct*)param;
	if(surface->screen->type != TYPE_GUI_LAYOUT_CELLULAR)
		return;


	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_box_struct* center_box = cellular->center_box;
	const picture_info_struct* max_picture = gui_surface_layout_cellular_get_max_picture(center_box);
	if(cellular->diameter >= max_picture->width * LAYOUT_CELL_ZOOM_MAX_SCALE)
	{
	    uievent_struct uievent = {center_box->id};
		center_box->alpha = 255;
		center_box->scale = 1;
		cellular->diameter = max_picture->width;
		//entry_app_by_id(center_box->id);
		application_window_event_handler(EVENT_GUI_EVENT_IND, &uievent);
	}
	else
	{
		center_box->alpha *= 0.7f;
		center_box->scale *= 1.2f;
		cellular->diameter *= 1.2f;
		gui_surface_layout_cellular_scale(surface,(float)cellular->diameter / (float)cellular->max_diameter);
		gui_surface_layout_cellular_move_near_center(surface,center_box);
		gui_surface_commit();
		g_layout_cellular_timer_id = application_start_user_timer(20, gui_surface_layout_cellular_timer_zoom_in, param);
	}
}

static void gui_surface_layout_cellular_timer_zoom_out_default(unsigned int timer, void* param)
{
	application_stop_user_timer(g_layout_cellular_timer_id);
	g_layout_cellular_timer_id = 0;

	gui_surface_struct* surface = (gui_surface_struct*)param;
	if(surface->screen->type != TYPE_GUI_LAYOUT_CELLULAR)
	{
		return;
	}

	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_box_struct* center_box = cellular->center_box;
	const picture_info_struct* default_picture = gui_surface_layout_cellular_get_default_picture(center_box);
	cellular->diameter = default_picture->width;
	gui_surface_layout_cellular_scale(surface,1.0f);
	gui_surface_layout_cellular_move_near_center(surface,center_box);
	gui_surface_commit();
}

static void gui_surface_layout_cellular_timer_zoom_out(unsigned int timer, void* param)
{
	application_stop_user_timer(g_layout_cellular_timer_id);
	g_layout_cellular_timer_id = 0;

	gui_surface_struct* surface = (gui_surface_struct*)param;
	if(surface->screen->type != TYPE_GUI_LAYOUT_CELLULAR)
	{
		return;
	}

	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_box_struct* center_box = cellular->center_box;
	const picture_info_struct* max_picture = gui_surface_layout_cellular_get_max_picture(center_box);
	cellular->diameter *= 0.83f;
	if(cellular->diameter <= max_picture->width)
	{
		center_box->alpha = 255;
		center_box->scale = 1;
		cellular->diameter = max_picture->width;
		gui_surface_layout_cellular_scale(surface,1.0f);
		g_layout_cellular_timer_id = application_start_user_timer(20, gui_surface_layout_cellular_timer_zoom_out_default, param);
	}
	else
	{
		short alpha = (short)center_box->alpha * 1.4f;
		center_box->alpha = alpha;
		center_box->scale *= 0.83f;
		gui_surface_layout_cellular_scale(surface,(float)cellular->diameter / (float)cellular->max_diameter);
		g_layout_cellular_timer_id = application_start_user_timer(20, gui_surface_layout_cellular_timer_zoom_out, param);
	}
	gui_surface_layout_cellular_move_near_center(surface,center_box);
	gui_surface_commit();
}


//放大
void gui_surface_layout_cellular_zoom_in(gui_surface_struct* surface)
{
	application_stop_user_timer(g_layout_cellular_timer_id);

	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_box_struct* near_center_box = gui_surface_layout_cellular_get_center_item(surface);
	near_center_box->alpha = 255;
	near_center_box->scale = 1;
	cellular->center_box = near_center_box;
	g_layout_cellular_near_center_box_position = gui_surface_layout_cellular_get_item_position(surface,near_center_box);
	g_layout_cellular_timer_id = application_start_user_timer(1, gui_surface_layout_cellular_timer_zoom_in, surface);
}

//缩小
void gui_surface_layout_cellular_zoom_out(gui_surface_struct* surface)
{
	application_stop_user_timer(g_layout_cellular_timer_id);
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_box_struct* near_center_box = gui_surface_layout_cellular_get_item(surface,g_layout_cellular_near_center_box_position);
	near_center_box->alpha = 30;
	near_center_box->scale = LAYOUT_CELL_ZOOM_MAX_SCALE;
	const picture_info_struct* max_picture = gui_surface_layout_cellular_get_max_picture(near_center_box);
	cellular->diameter = max_picture->width * LAYOUT_CELL_ZOOM_MAX_SCALE;
	cellular->center_box = near_center_box;
	gui_surface_layout_cellular_scale(surface,(float)cellular->diameter / (float)cellular->max_diameter);
	gui_surface_layout_cellular_move_near_center(surface,near_center_box);
	g_layout_cellular_timer_id = application_start_user_timer(20, gui_surface_layout_cellular_timer_zoom_out, surface);
}

void gui_surface_layout_cellular_clear_zoom_timer()
{
	if(g_layout_cellular_timer_id > 0)
	{
		application_stop_user_timer(g_layout_cellular_timer_id);
		g_layout_cellular_timer_id = 0;
	}

	if(g_layout_cellular_rebound_timer_id > 0)
	{
		application_stop_user_timer(g_layout_cellular_rebound_timer_id);
		g_layout_cellular_rebound_timer_id = 0;
	}
}


static void gui_surface_layout_cellular_rebound_zoom_timer(unsigned int timer, void* param)
{
	application_stop_user_timer(g_layout_cellular_rebound_timer_id);
	g_layout_cellular_rebound_timer_id = 0;

	gui_surface_struct* surface = (gui_surface_struct*)param;
	if(surface->screen->type != TYPE_GUI_LAYOUT_CELLULAR)
		return;

	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_box_struct* center_box = cellular->center_box;
	gui_widget_struct* widget = center_box->widget;

	const picture_info_struct* default_picture = gui_surface_layout_cellular_get_default_picture(center_box);
	if(cellular->diameter < default_picture->width)
	{
		cellular->diameter = gui_surface_layout_cellular_get_next_hight_width(surface,widget);
		gui_surface_layout_cellular_scale(surface,(float)cellular->diameter / (float)cellular->max_diameter);
		g_layout_cellular_rebound_timer_id = application_start_user_timer(20, gui_surface_layout_cellular_rebound_zoom_timer, param);
	}
	else
	{
		center_box->alpha = 255;
		center_box->scale = 1;
		cellular->diameter = default_picture->width;
		gui_surface_layout_cellular_scale(surface,1.0f);
	}
	gui_surface_layout_cellular_move_near_center(surface,center_box);
	gui_surface_commit();
}


#endif


/*******************************操作接口************************************/

//根据排版类型，进行排版
void gui_surface_layout_cellular_arrange(gui_surface_struct* surface)
{
	const gui_layout_cellular_struct* layout_config = surface->screen->layout_config;
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;

	cellular->max_diameter = layout_config->max_diameter == 0 ? layout_config->diameter : layout_config->max_diameter;
	cellular->diameter= layout_config->diameter;
	cellular->min_column = layout_config->min_column;
	cellular->max_column = layout_config->max_column;
	cellular->margin = layout_config->margin;
	cellular->space = layout_config->space;
	cellular->default_center = layout_config->default_center;

	short row = gui_surface_layout_cellular_get_row_num(surface);
	short width =  cellular->max_column * cellular->diameter + (cellular->max_column-1) *cellular->space;
	short height =  row * cellular->diameter + (row - 1) * cellular->space;
	cellular->width = width  + cellular->margin * 2;
	cellular->height = height*0.866f + cellular->margin * 2;

	cellular->offset_x = -(cellular->width - LCD_SIZE_WIDTH) / 2;
	cellular->offset_y = -(cellular->height - LCD_SIZE_HEIGHT) / 2;
	cellular->last_offset_x = 0;
	cellular->last_offset_y = 0;

	gui_surface_layout_clear_history(surface->window);
	gui_surface_layout_cellular_commit_position(surface);

	if(g_layout_cellular_near_center_box_position < 0)
	{
		g_layout_cellular_near_center_box_position = cellular->default_center;
	}

#if GUI_LAYOUT_CELL_ZOOM_SUPPORT == 1
	gui_surface_layout_cellular_clear_zoom_timer();
	gui_surface_layout_cellular_zoom_out(surface);
#else
	gui_box_struct* near_center_box = gui_surface_layout_cellular_get_item(surface,g_layout_cellular_near_center_box_position);
	cellular->center_box = near_center_box;
	gui_surface_layout_cellular_move_near_center(surface,near_center_box);
#endif

	g_layout_cellular_near_center_box_position = -1;

}



//对排版中的子元素，使用指定的偏移
void gui_surface_layout_cellular_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y)
{
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	cellular->offset_x = layout_offset_x;
	cellular->offset_y = layout_offset_y;
	gui_surface_layout_cellular_commit_position(surface);
}

//对排版中的子元素，进行指定的偏移
void gui_surface_layout_cellular_move(gui_surface_struct* surface,short move_offset_x,short move_offset_y)
{
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	cellular->offset_x += move_offset_x;
	cellular->offset_y += move_offset_y;
	gui_surface_layout_cellular_commit_position(surface);
}



//提交位置偏移
void gui_surface_layout_cellular_commit_position(gui_surface_struct* surface)
{
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	short column_num = cellular->min_column;
	short count = 0;
	short row = 0;
	short step = 1;
	short cell_x = 0;
	short cell_y = 0;

	gui_box_struct* box = surface->child;
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			if(count++ == 0)
			{
				cell_x = (cellular->width - (column_num * cellular->diameter + (column_num-1)*cellular->space))/2;
				cell_y = cellular->margin + row * (cellular->diameter + cellular->space)*0.966f;
			}
			else
			{
				cell_x += cellular->diameter + cellular->space;
			}
			box->x = cell_x + cellular->offset_x;
			box->y = cell_y + cellular->offset_y;

			box->width = cellular->diameter;
			box->height = cellular->diameter;

			if(count >= column_num)
			{
				row++;
				count = 0;
				column_num += step;
				if(column_num >= cellular->max_column && step > 0)
				{
					step = -1;
				}
			}
		}
		box = box->brother;
	}
	gui_surface_layout_cellular_arrange_zoom_and_position(surface);
}


void gui_surface_layout_cellular_switch_to_item(gui_surface_struct* surface, DIRECTION_TYPE direction)
{
#if GUI_LAYOUT_CELL_ZOOM_SUPPORT == 1
	application_stop_user_timer(g_layout_cellular_rebound_timer_id);
	g_layout_cellular_rebound_timer_id = 0;

	if(g_layout_cellular_timer_id > 0)
		return;
#endif

	if(gui_touch_layout_rebound_is_moving())
		return;

	gui_box_struct* near_center_box = gui_surface_layout_cellular_get_center_item(surface);
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;
	gui_widget_struct* widget = near_center_box->widget;

	if(direction == DIRECTION_TYPE_DOWN)//缩小
	{
		cellular->diameter = gui_surface_layout_cellular_get_next_low_width(surface,widget);
	#if GUI_LAYOUT_CELL_ZOOM_SUPPORT == 1
		const picture_info_struct* default_picture = gui_surface_layout_cellular_get_default_picture(near_center_box);
		if(cellular->diameter < default_picture->width)
		{
			g_layout_cellular_rebound_timer_id = application_start_user_timer(400, gui_surface_layout_cellular_rebound_zoom_timer, surface);
		}
	#endif
		gui_surface_layout_cellular_scale(surface,(float)cellular->diameter / (float)cellular->max_diameter);
		gui_surface_layout_cellular_move_near_center(surface,near_center_box);
	}
	else if(direction == DIRECTION_TYPE_UP)//放大
	{
		const picture_info_struct* max_picture = gui_surface_layout_cellular_get_max_picture(near_center_box);
		if(cellular->diameter >= max_picture->width)
		{
			#if GUI_LAYOUT_CELL_ZOOM_SUPPORT == 1
				gui_surface_layout_cellular_zoom_in(surface);
			#endif
		}
		else
		{
			cellular->diameter = gui_surface_layout_cellular_get_next_hight_width(surface,widget);
		}
		gui_surface_layout_cellular_scale(surface,(float)cellular->diameter / (float)cellular->max_diameter);
		gui_surface_layout_cellular_move_near_center(surface,near_center_box);
	}

}





#if LCD_SHAPE == LCD_SQUARE  //只能用这个

static void gui_surface_layout_cellular_compute(gui_box_struct* box,const picture_info_struct *picture,short len_x,short len_y)
{
	gui_node_struct* node = box->child;
	short bound_len = (float)LCD_SIZE_HALF_WIDTH / 1.414f;
	short offset_height = (box->height - picture->height) / 2;
	short offset_width = (box->width - picture->width) / 2;

	short center_x = box->x + box->width / 2;
	short center_y = box->y + box->height / 2;

	if(center_x  > LCD_SIZE_HALF_WIDTH)
	{
		if(center_y < LCD_SIZE_HALF_HEIGHT) //第一象限
		{
			if(len_x > len_y)
			{
				node->x = 0;
				node->y = offset_height + len_y * offset_height / bound_len;
			}
			else if(len_x < len_y)
			{
				node->x = offset_width - len_x * offset_width / bound_len;
				node->y = box->height - picture->height;
			}
			else
			{
				node->x = 0;
				node->y = box->height - picture->height;
			}
		}
		else if(center_y > LCD_SIZE_HALF_HEIGHT)//第四象限
		{
			if(len_x > len_y)
			{
				node->x = 0;
				node->y = offset_height - len_y * offset_height / bound_len;
			}
			else if(len_x < len_y)
			{
				node->x = offset_width - len_x * offset_width / bound_len;
				node->y = 0;
			}
			else
			{
				node->x = 0;
				node->y = 0;
			}
		}
		else//X+轴
		{
			node->x = 0;
			node->y = offset_height;
		}
	}
	else if(center_x < LCD_SIZE_HALF_WIDTH)
	{
		if(center_y < LCD_SIZE_HALF_HEIGHT) //第二象限
		{
			if(len_x > len_y)
			{
				node->x = box->width - picture->width;
				node->y = offset_height + len_y * offset_height / bound_len;
			}
			else if(len_x < len_y)
			{
				node->x = offset_width + len_x * offset_width / bound_len;
				node->y = box->height - picture->height;
			}
			else
			{
				node->x = box->width - picture->width;
				node->y = box->height - picture->height;
			}
		}
		else if(center_y > LCD_SIZE_HALF_HEIGHT)//第三象限
		{
			if(len_x > len_y)
			{
				node->x = box->width - picture->width;
				node->y = offset_height - len_y * offset_height / bound_len;
			}
			else if(len_x < len_y)
			{
				node->x = offset_width + len_x * offset_width / bound_len;
				node->y = 0;
			}
			else
			{
				node->x = box->width - picture->width;
				node->y = 0;
			}
		}
		else//X-轴
		{
			node->x = box->width - picture->width;
			node->y = offset_height;
		}
	}
	else
	{
		if(center_y < LCD_SIZE_HALF_HEIGHT)//Y+轴
		{
			node->x = offset_width;
			node->y = box->height - picture->height;
		}
		else if(center_y > LCD_SIZE_HALF_HEIGHT)//Y-轴
		{
			node->x = offset_width;
			node->y = 0;
		}
	}
}


void gui_surface_layout_cellular_arrange_zoom_and_position(gui_surface_struct* surface)
{
	gui_box_struct* box = surface->child;
	const gui_layout_cellular_struct* layout_config = surface->screen->layout_config;
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;

	box->width = cellular->diameter;
	box->height = cellular->diameter;

	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			short box_radius = box->width / 2;
			short len_x = ABS(box->x + box_radius - LCD_SIZE_HALF_WIDTH);  //到屏幕中心的偏移
			short len_y = ABS(box->y + box_radius - LCD_SIZE_HALF_HEIGHT);  //到屏幕中心的偏移
			short distance = math_sqrt_16((unsigned int)len_x * (unsigned int)len_x + (unsigned int)len_y * (unsigned int)len_y);//离屏幕中心的距离

			//SYS_DEBUG("distance:%d",distance);

			gui_widget_struct* widget = box->widget;
			gui_node_struct* node = box->child;

			if(distance <= (LCD_SIZE_HALF_WIDTH + box_radius) )//在屏幕的内部
			{
				const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children;
				const picture_info_struct* picture = (const picture_info_struct*)(*picture_arr);

				short min_distance = distance - box_radius;						//圆离中心最近的一个点
				short picture_diameter = LCD_SIZE_HALF_WIDTH - min_distance;

				//SYS_DEBUG("min_distance:%d",min_distance);
				//SYS_DEBUG("picture_diameter:%d",picture_diameter);

				if(distance >= (LCD_SIZE_HALF_WIDTH - box_radius))//与屏幕边缘相交
				{
					const picture_info_struct** picture_arr_last = picture_arr + widget->child_num - 1;
					const picture_info_struct* picture_last = (const picture_info_struct*)(*picture_arr_last);

					//SYS_DEBUG("picture_last->width:%d",picture_last->width);
					if(picture_last->width <= picture_diameter)
					{
						node->visible = 1;
						for(unsigned char i = 0; i < widget->child_num; i++)
						{
							if(picture->width <= picture_diameter)
							{
								//SYS_DEBUG("picture->width:%d",picture->width);
								node->data = (void*)picture;

								if(picture_diameter < cellular->diameter)
								{
									gui_surface_layout_cellular_compute(box,picture,len_x,len_y);
								}
								else
								{
									node->x = box->width/2 - picture->width/2;
									node->y = box->height/2 - picture->height/2;
								}
								gui_surface_node_check_clip(box, node, picture->width, picture->height);
								break;
							}
							picture_arr++;
							//SYS_DEBUG("picture_arr:%x",picture_arr);
							picture = (const picture_info_struct*)(*picture_arr);
						}
					}
					else
					{
						//SYS_DEBUG("node->visible:%d",node->visible);
						node->visible = 0;
					}
				}
				else
				{
					node->data = (void *)picture;
					node->x = box->width/2 - picture->width/2;
					node->y = box->height/2 - picture->height/2;
					node->visible = 1;
					gui_surface_node_check_clip(box, node, picture->width, picture->height);
				}
			}
			else
			{
				node->visible = 0;
			}
		}
		box = box->brother;
	}
}

#else //LCD_SQUARE

static void gui_surface_layout_cellular_compute(gui_box_struct* box,const picture_info_struct *picture,short len_x,short len_y)
{
	gui_node_struct* node = box->child;
	short offset_height = (box->height - picture->height) / 2;
	short offset_width = (box->width - picture->width) / 2;

	short center_x = box->x + box->width / 2;
	short center_y = box->y + box->height / 2;

	if(center_x  > LCD_SIZE_HALF_WIDTH)
	{
		if(center_y < LCD_SIZE_HALF_HEIGHT)
		{
			if(len_x > len_y)
			{
				node->x = 0;
				node->y = offset_height + len_y * offset_height / LCD_SIZE_HALF_HEIGHT;
			}
			else if(len_x < len_y)
			{
				node->x = offset_width - len_x * offset_width / LCD_SIZE_HALF_WIDTH;
				node->y = box->height - picture->height;
			}
			else
			{
				node->x = 0;
				node->y = box->height - picture->height;
			}
		}
		else if(center_y > LCD_SIZE_HALF_HEIGHT)//碌脷脣脛脧贸脧脼
		{
			if(len_x > len_y)
			{
				node->x = 0;
				node->y = offset_height - len_y * offset_height / LCD_SIZE_HALF_HEIGHT;
			}
			else if(len_x < len_y)
			{
				node->x = offset_width - len_x * offset_width / LCD_SIZE_HALF_WIDTH;
				node->y = 0;
			}
			else
			{
				node->x = 0;
				node->y = 0;
			}
		}
		else//X+脰谩
		{
			node->x = 0;
			node->y = offset_height;
		}
	}
	else if(center_x < LCD_SIZE_HALF_WIDTH)
	{
		if(center_y < LCD_SIZE_HALF_HEIGHT) //碌脷露镁脧贸脧脼
		{
			if(len_x > len_y)
			{
				node->x = box->width - picture->width;
				node->y = offset_height + len_y * offset_height / LCD_SIZE_HALF_HEIGHT;
			}
			else if(len_x < len_y)
			{
				node->x = offset_width + len_x * offset_width / LCD_SIZE_HALF_WIDTH;
				node->y = box->height - picture->height;
			}
			else
			{
				node->x = box->width - picture->width;
				node->y = box->height - picture->height;
			}
		}
		else if(center_y > LCD_SIZE_HALF_HEIGHT)//碌脷脠媒脧贸脧脼
		{
			if(len_x > len_y)
			{
				node->x = box->width - picture->width;
				node->y = offset_height - len_y * offset_height / LCD_SIZE_HALF_HEIGHT;
			}
			else if(len_x < len_y)
			{
				node->x = offset_width + len_x * offset_width / LCD_SIZE_HALF_WIDTH;
				node->y = 0;
			}
			else
			{
				node->x = box->width - picture->width;
				node->y = 0;
			}
		}
		else//X-脰谩
		{
			node->x = box->width - picture->width;
			node->y = offset_height;
		}
	}
	else
	{
		if(center_y < LCD_SIZE_HALF_HEIGHT)//Y+脰谩
		{
			node->x = offset_width;
			node->y = box->height - picture->height;
		}
		else if(center_y > LCD_SIZE_HALF_HEIGHT)//Y-脰谩
		{
			node->x = offset_width;
			node->y = 0;
		}
	}
}

void gui_surface_layout_cellular_arrange_zoom_and_position(gui_surface_struct* surface)
{
	gui_box_struct* box = surface->child;
	gui_layout_cellular_struct* cellular = &surface->layout.cellular;

	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			gui_widget_struct* widget = box->widget;
			gui_node_struct* node = box->child;
			const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children+1;
			const picture_info_struct* picture = (const picture_info_struct*)(*picture_arr);

			short box_radius = box->width / 2;

			short center_x = box->x + box_radius;
			short center_y = box->y + box_radius;

			short len_x = ABS(center_x - LCD_SIZE_HALF_WIDTH);
			short len_y = ABS(center_y - LCD_SIZE_HALF_HEIGHT);

			short offset_x = len_x - LCD_SIZE_HALF_WIDTH;
			short offset_y = len_y - LCD_SIZE_HALF_HEIGHT;

			short distance_x = box_radius - offset_x;
			short distance_y = box_radius - offset_y;
            short distance = math_sqrt_16((unsigned int)len_x * (unsigned int)len_x + (unsigned int)len_y * (unsigned int)len_y);//离屏幕中心的距离

			short picture_diameter = MIN(MIN(distance_x,distance_y),box->width);

			if(picture_diameter > 0 && picture_diameter <= box->width )
			{
			    const picture_info_struct** picture_arr_frist = (const picture_info_struct**)widget->children;
			    const picture_info_struct* picture_frist = (const picture_info_struct*)(*picture_arr_frist);

				const picture_info_struct** picture_arr_last = (const picture_info_struct**)widget->children + widget->child_num - 1;
				const picture_info_struct* picture_last = (const picture_info_struct*)(*picture_arr_last);

				//SYS_DEBUG("picture_last->width:%d",picture_last->width);
				if(picture_last->width <= picture_diameter)
				{
					node->visible = 1;
					for(unsigned char i = 0; i < widget->child_num; i++)
					{
						if(picture->width <= picture_diameter)
						{
                            if(distance < box->width/2)
                            {
                                if(picture_frist->width > picture->width && picture->width >=66)
                                {
                                    picture_arr--;
                                    //SYS_DEBUG("picture_arr:%x",picture_arr);
                                    picture = (const picture_info_struct*)(*picture_arr);
                                }
                            }
						    else if(distance < box->width+box->width/2)
                            {
                                    if(picture_frist->width > picture->width && picture->width >=66)
                                    {
                                        picture_arr++;
                                        //SYS_DEBUG("picture_arr:%x",picture_arr);
                                        picture = (const picture_info_struct*)(*picture_arr);
                                    }
                            }
                            else if(distance >(box->width+box->width/2)&&distance <=(box->width+box->width+box->width/2)&& picture->width >=66)
                            {
                                if(picture->width > picture_last->width)
                                {
                                    picture_arr++;
                                    //SYS_DEBUG("picture_arr:%x",picture_arr);
                                    picture = (const picture_info_struct*)(*picture_arr);
                                }
                            }

							//SYS_DEBUG("picture->width:%d",picture->width);
							node->data = (void*)picture;
							if(picture_diameter < cellular->diameter)
							{
								gui_surface_layout_cellular_compute(box,picture,len_x,len_y);
							}
							else
							{
								node->x = box->width/2 - picture->width/2;
								node->y = box->height/2 - picture->height/2;
							}
							gui_surface_node_check_clip(box, node, picture->width, picture->height);
							break;
						}
						picture_arr++;
						//SYS_DEBUG("picture_arr:%x",picture_arr);
						picture = (const picture_info_struct*)(*picture_arr);
					}
				}
				else
				{
					//SYS_DEBUG("node->visible:%d",node->visible);
					node->visible = 0;
				}
			}
			else
			{
				const picture_info_struct** picture_arr_last = picture_arr + widget->child_num - 1;
				const picture_info_struct* picture_last = (const picture_info_struct*)(*picture_arr_last);

				node->data = (void *)picture;
				node->x = box->width/2 - picture->width/2;
				node->y = box->height/2 - picture->height/2;
				if(picture_diameter <= 0 || picture_last->width > picture_diameter)
					node->visible = 0;
				else
					node->visible = 1;
				gui_surface_node_check_clip(box, node, picture->width, picture->height);
			}

		}

		box = box->brother;

	}

}

#endif


