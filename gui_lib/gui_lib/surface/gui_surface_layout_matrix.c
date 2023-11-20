#include "system_util_math.h"
#include "app_task_main.h"
#include "application.h"

#include "gui_surface_node.h"
#include "gui_surface_layout.h"
#include "gui_surface_layout_matrix.h"
#include "gui_touch_layout_rebound.h"
#include "app_task_main.h"
#include "application_config_app_info.h"

/*******************************************
**
**对matrix进行排版，移动
**
********************************************/

#define MATRIX_STEP_VALUE (0.25f)		  // 拨码器每次转动时增加或减少的百分比
#define MATRIX_TO_APP_STEP_VALUE (0.618f) // 打开App或进入蜂窝列表前每次增加或减少的百分比
#define MATRIX_APP_SACLE (0.618f)		  // 当达到屏幕的一定大小时，就打开应用
#define MATRIX_MIN_SACLE (0.15f)		  // 屏幕上最低的缩小尺寸
#define MATRIX_MOVE_MIN_GAP (5)			  // 逼近时，该距离认为已重合

#define MATRIX_TIMER_DELAY (500)   // 定时器的延迟时间
#define MATRIX_TIMER_INTERVAL (30) // 定时器的启动时间

typedef struct
{
	unsigned char row;
	unsigned char col;
	short org_x;
	short org_y;
	short org_diameter;
	short cache_x;
	short cache_y;
	short cache_diameter;
	short x;
	short y;
	short diameter;
	gui_box_struct *box; //  节点  和 交叉点
} matrix_net_node_struct;

static unsigned int g_layout_matrix_timer_id = 0;
static short g_layout_matrix_box_index = -1;
static matrix_net_node_struct g_matrix_net_nodes[MATRIX_NET_ROW_TOTAL][MATRIX_NET_COL_TOTAL] = {0};

/*******************************数据接口************************************/

unsigned char gui_surface_layout_matrix_click_layout(gui_surface_struct *surface)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return 0;

	gui_click_layout_struct event;
	event.id = (unsigned char)matrix->center_box->id;
	if (surface->window && surface->window->click_on_layout_item)
	{
		g_layout_matrix_box_index = gui_surface_layout_matrix_get_item_position(surface, matrix->center_box);
		surface->window->click_on_layout_item(&event);
		return 1;
	}
	return 0;
}

short gui_surface_layout_matrix_get_count(gui_surface_struct *surface)
{
	matrix_net_node_struct *net_node = NULL;
	short count = 0;
	for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
		{
			net_node = &g_matrix_net_nodes[i][j];
			if (net_node->box != NULL)
				count++;
		}
	}
	return count;
}

gui_box_struct *gui_surface_layout_matrix_get_item(gui_surface_struct *surface, short index)
{
	matrix_net_node_struct *net_node = NULL;
	short count = 0;
	for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
		{
			net_node = &g_matrix_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				if (count == index)
					return net_node->box;
				count++;
			}
		}
	}
	return NULL;
}

short gui_surface_layout_matrix_get_item_position(gui_surface_struct *surface, gui_box_struct *find_box)
{
	matrix_net_node_struct *net_node = NULL;
	short count = 0;
	for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
		{
			net_node = &g_matrix_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				if (net_node->box == find_box)
					return count;
				count++;
			}
		}
	}
	return -1;
}

// 点击在列表的哪个条目上,返回条目编号
short gui_surface_layout_matrix_get_item_index(gui_surface_struct *surface, gui_touch_point_struct *touch_point)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix_net_node_struct *net_node = NULL;
	gui_box_struct *box = NULL;
	geometry_rect rect_box;
	short count = 0;
	for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
		{
			net_node = &g_matrix_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				box = net_node->box;
				rect_box.x = net_node->x + matrix->offset_x - net_node->diameter / 2;
				rect_box.y = net_node->y + matrix->offset_y - net_node->diameter / 2;
				rect_box.width = net_node->diameter;
				rect_box.height = net_node->diameter;
				if (check_rect_contain_point_xy(&rect_box, touch_point->x, touch_point->y))
					return count;
				count++;
			}
		}
	}
	return -1;
}

gui_box_struct *gui_surface_layout_matrix_get_center_item(gui_surface_struct *surface)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix_net_node_struct *net_node = NULL;
	gui_box_struct *center = NULL;
	short min_distance = SHORT_MAX;
	for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
		{
			net_node = &g_matrix_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				short len_x = ABS(net_node->x + matrix->offset_x - LCD_SIZE_HALF_WIDTH);
				short len_y = ABS(net_node->y + matrix->offset_y - LCD_SIZE_HALF_HEIGHT);
				short distance = math_sqrt_16(len_x * len_x + len_y * len_y); // 离屏幕中心的距离
				if (min_distance > distance)
				{
					min_distance = distance;
					center = net_node->box;
				}
			}
		}
	}
	return center;
}

void gui_surface_layout_matrix_move_to_center_box(gui_surface_struct *surface, gui_box_struct *center_box)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	if (center_box != NULL)
	{
		short offset_x = LCD_SIZE_HALF_WIDTH - (center_box->x);
		short offset_y = LCD_SIZE_HALF_HEIGHT - (center_box->y);
		matrix->offset_x += offset_x;
		matrix->offset_y += offset_y;
	}
}

void gui_surface_layout_matrix_move_to_screen_center(gui_surface_struct *surface)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	short offset_x = matrix->org_offset_x - matrix->offset_x;
	short offset_y = matrix->org_offset_y - matrix->offset_y;
	matrix->offset_x += offset_x;
	matrix->offset_y += offset_y;
}

unsigned char gui_surface_layout_matrix_finish_move_offset_step(gui_surface_struct *surface)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	short offset_x = matrix->org_offset_x - matrix->offset_x;
	short offset_y = matrix->org_offset_y - matrix->offset_y;
	return (ABS(offset_x) < MATRIX_MOVE_MIN_GAP && ABS(offset_y) < MATRIX_MOVE_MIN_GAP);
}

unsigned char gui_surface_layout_matrix_finish_to_center_box_step(gui_surface_struct *surface)
{
	gui_surface_layout_matrix_commit_position(surface);
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	gui_box_struct *center_box = matrix->center_box;
	short offset_x = LCD_SIZE_HALF_WIDTH - (center_box->x);
	short offset_y = LCD_SIZE_HALF_HEIGHT - (center_box->y);
	return (ABS(offset_x) < MATRIX_MOVE_MIN_GAP && ABS(offset_y) < MATRIX_MOVE_MIN_GAP);
}

unsigned char gui_surface_layout_matrix_move_offset_step(gui_surface_struct *surface, short offset_x, short offset_y)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	short gap_x = (offset_x) / 3;
	short gap_y = (offset_y) / 3;
	if (ABS(offset_x) < MATRIX_MOVE_MIN_GAP && ABS(offset_y) < MATRIX_MOVE_MIN_GAP)
	{
		matrix->offset_x += offset_x;
		matrix->offset_y += offset_y;
		return 1;
	}
	else
	{
		matrix->offset_x += gap_x;
		matrix->offset_y += gap_y;
		return 0;
	}
}

unsigned char gui_surface_layout_matrix_move_to_step(gui_surface_struct *surface, short move_to_x, short move_to_y)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	short offset_x = move_to_x - matrix->offset_x;
	short offset_y = move_to_y - matrix->offset_y;
	return gui_surface_layout_matrix_move_offset_step(surface, offset_x, offset_y);
}

unsigned char gui_surface_layout_matrix_move_to_screen_center_step(gui_surface_struct *surface)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	return gui_surface_layout_matrix_move_to_step(surface, matrix->org_offset_x, matrix->org_offset_y);
}

unsigned char gui_surface_layout_matrix_move_to_center_box_step(gui_surface_struct *surface)
{
	gui_surface_layout_matrix_commit_position(surface);
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	gui_box_struct *center_box = matrix->center_box;
	short offset_x = LCD_SIZE_HALF_WIDTH - (center_box->x);
	short offset_y = LCD_SIZE_HALF_HEIGHT - (center_box->y);
	return gui_surface_layout_matrix_move_offset_step(surface, offset_x, offset_y);
}

void gui_surface_layout_matrix_clear(void)
{
	gui_surface_layout_matrix_stop_timer();
	g_layout_matrix_box_index = -1;
}

void gui_surface_layout_matrix_exit(void)
{
	gui_surface_layout_matrix_stop_timer();
}

void gui_surface_layout_matrix_stop_timer(void)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;
}

unsigned char gui_surface_layout_matrix_timer_running(void)
{
	return g_layout_matrix_timer_id > 0;
}

/*******************************操作接口************************************/

// 根据排版类型，进行排版
void gui_surface_layout_matrix_arrange(gui_surface_struct *surface)
{
	gui_surface_layout_clear_history(surface->window);

	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	memcpy(matrix, layout_config, sizeof(gui_layout_matrix_struct));

	// 标准位置，计算的起点（相当于坐标原点）
	gui_surface_layout_matrix_init_orgin_nets(surface);
	gui_surface_layout_matrix_init_orgin_net_size(surface);
	gui_surface_layout_matrix_init_orgin_net_position(surface);

	// 大模式
	matrix->step = GUI_MATRIX_STEP_STATUS_BIG;
	matrix->scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	gui_surface_layout_matrix_calculate_big_zoom_position(surface); // 因为App放大时，是整体放大，所以先要保证cache同步
	gui_surface_layout_matrix_commit_position(surface);				// 同步box位置

	// 偏移到中心点
	if (g_layout_matrix_box_index < 0)
	{
		matrix->center_box = gui_surface_layout_matrix_get_center_item(surface);
		g_layout_matrix_box_index = gui_surface_layout_matrix_get_item_position(surface, matrix->center_box);
	}
	else
	{
		matrix->center_box = gui_surface_layout_matrix_get_item(surface, g_layout_matrix_box_index);
		gui_surface_layout_matrix_move_to_center_box(surface, matrix->center_box);
	}
	gui_surface_layout_matrix_commit_position(surface); // 同步box位置

	// 从外面进入时，要有动画
	matrix->step = GUI_MATRIX_STEP_STATUS_APP;
	matrix->scale = (float)LCD_SIZE_WIDTH * MATRIX_APP_SACLE / layout_config->mid_diameter;
	gui_surface_layout_matrix_calculate_app_zoom_position(surface);
	gui_surface_layout_matrix_commit_position(surface);

	gui_surface_layout_matrix_entry_list(surface);
}

// 对排版中的子元素，使用指定的偏移
void gui_surface_layout_matrix_offset(gui_surface_struct *surface, short layout_offset_x, short layout_offset_y)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix->offset_x = layout_offset_x;
	matrix->offset_y = layout_offset_y;
	gui_surface_layout_matrix_commit_position(surface);
}

// 对排版中的子元素，进行指定的偏移
void gui_surface_layout_matrix_move(gui_surface_struct *surface, short move_offset_x, short move_offset_y)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix->offset_x += move_offset_x;
	matrix->offset_y += move_offset_y;
	gui_surface_layout_matrix_commit_position(surface);
}

// 初始化网格
void gui_surface_layout_matrix_init_orgin_nets(gui_surface_struct *surface)
{
	memset(g_matrix_net_nodes, 0, sizeof(g_matrix_net_nodes));

	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	matrix_net_node_struct *net_node = NULL;
	gui_box_struct *box = surface->child;
	short column_index = 0;
	short row_index = 0;
	while (box != NULL)
	{
		if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			if (column_index >= MATRIX_COL_TOTAL)
			{
				column_index = 0;
				row_index++;
			}

			net_node = &g_matrix_net_nodes[row_index][column_index];
			net_node->box = box;
			net_node->row = row_index;
			net_node->col = column_index;
			net_node->diameter = layout_config->mid_diameter;

			column_index++;
			box->visible = 0;
		}
		box = box->brother;
	}
}

// 网格排版参数
void gui_surface_layout_matrix_init_orgin_net_size(gui_surface_struct *surface)
{
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;

	short diameter = layout_config->mid_diameter;
	short space = layout_config->space;
	matrix->width = diameter + (MATRIX_COL_TOTAL - 1) * (diameter + space);
	matrix->height = diameter + (MATRIX_ROW_TOTAL - 1) * (diameter + space); // 长度只算到圆心

	matrix->offset_x = (LCD_SIZE_WIDTH - matrix->width) / 2;
	matrix->offset_y = (LCD_SIZE_HEIGHT - matrix->height) / 2;

	matrix->org_offset_x = matrix->offset_x;
	matrix->org_offset_y = matrix->offset_y;
}

// 初始化网格原始位置(在放大和缩小的边缘,这里的缩放比例是1)
void gui_surface_layout_matrix_init_orgin_net_position(gui_surface_struct *surface)
{
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	matrix_net_node_struct *net_node = NULL;

	short cell_center_x = 0;
	short cell_center_y = layout_config->mid_diameter / 2;

	for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
	{
		cell_center_x = layout_config->mid_diameter / 2;
		for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
		{
			net_node = &g_matrix_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				net_node->box->visible = 0;
			}

			net_node->org_x = cell_center_x;
			net_node->org_y = cell_center_y;
			net_node->org_diameter = layout_config->mid_diameter;

			net_node->x = cell_center_x;
			net_node->y = cell_center_y;
			net_node->diameter = layout_config->mid_diameter;

			cell_center_x += layout_config->mid_diameter + layout_config->space;
		}
		cell_center_y += layout_config->mid_diameter + layout_config->space;
	}
}

// 提交位置偏移，提交一次图标的具体位置（当使用正中间box做位置前,需要调用一次，保证同步）
void gui_surface_layout_matrix_commit_position(gui_surface_struct *surface)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix_net_node_struct *net_node = NULL;
	gui_box_struct *box = NULL;

	for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
		{
			net_node = &g_matrix_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				box = net_node->box;
				box->visible = 1;
				box->x = net_node->x + matrix->offset_x;
				box->y = net_node->y + matrix->offset_y;
				box->scale = (float)net_node->diameter / matrix->icon_diameter;
			}
		}
	}
}

// 计算小模式状态下的位置（该模式都是平放，间隔和大小都一样）
void gui_surface_layout_matrix_calculate_small_zoom_position(gui_surface_struct *surface)
{
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix_net_node_struct *net_node = NULL;

	if (matrix->step == GUI_MATRIX_STEP_STATUS_SAMLL)
	{
		float diameter = layout_config->mid_diameter * matrix->scale;
		float space = layout_config->space * matrix->scale;

		float width = diameter + (MATRIX_COL_TOTAL - 1) * (diameter + space);
		float height = diameter + (MATRIX_ROW_TOTAL - 1) * (diameter + space);

		float cell_start_x = (matrix->width - width) / 2 + diameter / 2;
		float cell_center_x = 0;
		float cell_center_y = (matrix->height - height) / 2 + diameter / 2;
		float cell_gap_y = (diameter + space);

		for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
		{
			cell_center_x = cell_start_x;
			for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
			{
				net_node = &g_matrix_net_nodes[i][j];
				net_node->diameter = diameter;
				net_node->x = (short)cell_center_x;
				net_node->y = (short)cell_center_y;

				cell_center_x += diameter + space;
			}
			cell_center_y += cell_gap_y;
		}
	}
}

// 计算大模式状态时的位置（注意如果朝应用模式放大时，是整体放大，起点是这里，所以先要保证cache同步）
void gui_surface_layout_matrix_calculate_big_zoom_position(gui_surface_struct *surface)
{
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix_net_node_struct *net_node = NULL;

	if (matrix->step == GUI_MATRIX_STEP_STATUS_BIG)
	{
		float diameter = layout_config->mid_diameter * matrix->scale;
		float space = layout_config->space * matrix->scale;

		float width = diameter + (MATRIX_COL_TOTAL - 1) * (diameter + space);
		float height = diameter + (MATRIX_ROW_TOTAL - 1) * (diameter + space);

		float cell_start_x = (matrix->width - width) / 2 + diameter / 2;
		float cell_center_x = 0;
		float cell_center_y = (matrix->height - height) / 2 + diameter / 2;
		float cell_gap_y = (diameter + space);

		for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
		{
			cell_center_x = cell_start_x;
			for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
			{
				net_node = &g_matrix_net_nodes[i][j];

				net_node->x = (short)cell_center_x;
				net_node->y = (short)cell_center_y;
				net_node->diameter = diameter;

				net_node->cache_x = net_node->x;
				net_node->cache_y = net_node->y;
				net_node->cache_diameter = net_node->diameter;

				cell_center_x += diameter + space;
			}
			cell_center_y += cell_gap_y;
		}
	}
}

// 计算应用模式状态时的位置（整体放大）
void gui_surface_layout_matrix_calculate_app_zoom_position(gui_surface_struct *surface)
{
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix_net_node_struct *net_node = NULL;

	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;

	short x = 0, y = 0;
	float ratio = 0;
	short distance = 0, distance_new = 0;
	for (short i = 0; i < MATRIX_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < MATRIX_NET_COL_TOTAL; j++)
		{
			net_node = &g_matrix_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				x = net_node->cache_x + matrix->offset_x - LCD_SIZE_HALF_WIDTH;
				y = net_node->cache_y + matrix->offset_y - LCD_SIZE_HALF_HEIGHT;

				// 中心点，不能除以0
				if (x == 0 && y == 0)
				{
					net_node->x = net_node->cache_x;
					net_node->y = net_node->cache_y;
				}
				else
				{
					distance = math_sqrt_16(x * x + y * y);
					distance_new = distance + (matrix->scale - scale) * distance;

					ratio = (float)distance_new / distance;
					net_node->x = ratio * x + LCD_SIZE_HALF_WIDTH - matrix->offset_x;
					net_node->y = ratio * y + LCD_SIZE_HALF_HEIGHT - matrix->offset_y;
				}
				net_node->diameter = net_node->cache_diameter + (matrix->scale - scale) * net_node->cache_diameter;
			}
		}
	}
}

/*************************进入应用模式时的定时器*************************/

static void gui_surface_layout_matrix_app_rebound_zoom_out_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	float scale = (float)LCD_SIZE_WIDTH * MATRIX_APP_SACLE / layout_config->mid_diameter;

	matrix->scale += MATRIX_TO_APP_STEP_VALUE;
	if (matrix->scale >= scale)
	{
		gui_surface_layout_matrix_click_layout(surface);
	}
	else
	{
		gui_surface_layout_matrix_calculate_app_zoom_position(surface);
		gui_surface_layout_matrix_commit_position(surface);
		gui_surface_commit();

		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_app_rebound_zoom_out_timer, surface);
	}
}

static void gui_surface_layout_matrix_app_rebound_zoom_in_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	float app_scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;

	if (matrix->scale > app_scale)
		matrix->scale -= MATRIX_TO_APP_STEP_VALUE;
	else
		matrix->scale -= MATRIX_STEP_VALUE;

	if (matrix->scale <= scale)
	{
		matrix->scale = scale;
		matrix->step = GUI_MATRIX_STEP_STATUS_BIG;
		gui_surface_layout_matrix_calculate_big_zoom_position(surface);
		gui_surface_layout_matrix_commit_position(surface);
		gui_surface_commit();
	}
	else
	{
		gui_surface_layout_matrix_calculate_app_zoom_position(surface);
		gui_surface_layout_matrix_commit_position(surface);
		gui_surface_commit();

		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_app_rebound_zoom_in_timer, surface);
	}
}

static void gui_surface_layout_matrix_app_check_rebound(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;

	float scale = (float)layout_config->app_diameter / layout_config->mid_diameter;
	if (matrix->scale < scale)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_DELAY, gui_surface_layout_matrix_app_rebound_zoom_in_timer, surface);
	}
	else if (matrix->scale > scale)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_DELAY, gui_surface_layout_matrix_app_rebound_zoom_out_timer, surface);
	}
}

void gui_surface_layout_matrix_entry_list(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_app_rebound_zoom_in_timer, surface);
}

static void gui_surface_layout_matrix_entry_app_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	if (gui_surface_layout_matrix_move_to_center_box_step(surface))
	{
		gui_surface_layout_matrix_move_to_center_box(surface, matrix->center_box);
		gui_surface_layout_matrix_calculate_big_zoom_position(surface);
		gui_surface_layout_matrix_commit_position(surface);
		gui_surface_force_update();

		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_app_rebound_zoom_out_timer, surface);
	}
	else
	{
		gui_surface_layout_matrix_move_to_center_box_step(surface);
		gui_surface_layout_matrix_calculate_big_zoom_position(surface);
		gui_surface_layout_matrix_commit_position(surface);
		gui_surface_force_update();

		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_entry_app_timer, surface);
	}
}

void gui_surface_layout_matrix_entry_app(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_entry_app_timer, surface);
}

void gui_surface_layout_matrix_entry_home_app(gui_surface_struct *surface)
{
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix->center_box = gui_surface_layout_matrix_get_item(surface, g_layout_matrix_box_index);

	if (matrix->step == GUI_MATRIX_STEP_STATUS_BIG)
	{
		gui_surface_layout_matrix_entry_app(surface);
	}
	else if (matrix->step == GUI_MATRIX_STEP_STATUS_SAMLL)
	{
		gui_surface_layout_matrix_touch_on_small_mode(surface);
	}
}

/*************************大模式时的定时器*************************/

static void gui_surface_layout_matrix_big_rebound_zoom_out_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	short count = 0;
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	matrix->scale += MATRIX_STEP_VALUE;
	if (matrix->scale >= scale)
	{
		matrix->scale = scale;
		count++;
	}
	if (gui_surface_layout_matrix_finish_to_center_box_step(surface))
	{
		count++;
	}
	if (count < 2)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_big_rebound_zoom_out_timer, surface);
	}

	gui_surface_layout_matrix_move_to_center_box_step(surface);
	gui_surface_layout_matrix_calculate_big_zoom_position(surface);
	gui_surface_layout_matrix_commit_position(surface);

	gui_surface_commit();
}

static void gui_surface_layout_matrix_big_rebound_zoom_in_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	short count = 0;
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	matrix->scale -= MATRIX_STEP_VALUE;
	if (matrix->scale <= scale)
	{
		matrix->scale = scale;
		count++;
	}
	if (gui_surface_layout_matrix_finish_to_center_box_step(surface))
	{
		count++;
	}
	if (count < 2)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_big_rebound_zoom_in_timer, surface);
	}

	gui_surface_layout_matrix_move_to_center_box_step(surface);
	gui_surface_layout_matrix_calculate_big_zoom_position(surface);
	gui_surface_layout_matrix_commit_position(surface);

	gui_surface_commit();
}

static void gui_surface_layout_matrix_big_check_rebound(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;

	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	if (matrix->scale < scale)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_DELAY, gui_surface_layout_matrix_big_rebound_zoom_out_timer, surface);
	}
	else if (matrix->scale > scale)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_DELAY, gui_surface_layout_matrix_big_rebound_zoom_in_timer, surface);
	}
}

/*************************小模式时的定时器*************************/
static void gui_surface_layout_matrix_small_rebound_zoom_out_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	short count = 0;
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	float scale = (float)layout_config->min_diameter / layout_config->mid_diameter;
	matrix->scale += MATRIX_STEP_VALUE;
	if (matrix->scale >= scale)
	{
		matrix->scale = scale;
		count++;
	}
	if (gui_surface_layout_matrix_finish_move_offset_step(surface))
	{
		count++;
	}
	if (count < 2)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_small_rebound_zoom_out_timer, surface);
	}
	gui_surface_layout_matrix_move_to_screen_center_step(surface);
	gui_surface_layout_matrix_calculate_small_zoom_position(surface);
	gui_surface_layout_matrix_commit_position(surface);
	gui_surface_commit();
}

static void gui_surface_layout_matrix_small_rebound_zoom_in_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	short count = 0;
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	float scale = (float)layout_config->min_diameter / layout_config->mid_diameter;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	matrix->scale -= MATRIX_STEP_VALUE;
	if (matrix->scale <= scale)
	{
		matrix->scale = scale;
		count++;
	}
	if (gui_surface_layout_matrix_finish_move_offset_step(surface))
	{
		count++;
	}
	if (count < 2)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_small_rebound_zoom_in_timer, surface);
	}
	gui_surface_layout_matrix_move_to_screen_center_step(surface);
	gui_surface_layout_matrix_calculate_small_zoom_position(surface);
	gui_surface_layout_matrix_commit_position(surface);
	gui_surface_commit();
}

static void gui_surface_layout_matrix_small_check_rebound(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	float scale = (float)layout_config->min_diameter / layout_config->mid_diameter;
	if (matrix->scale < scale)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_DELAY, gui_surface_layout_matrix_small_rebound_zoom_out_timer, surface);
	}
	else if (matrix->scale > scale)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_DELAY, gui_surface_layout_matrix_small_rebound_zoom_in_timer, surface);
	}
}

/*************************按拨码器时单步放大缩小*************************/
void gui_surface_layout_matrix_app_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;

	if (direction == DIRECTION_TYPE_DOWN) // 缩小
	{
		float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
		matrix->scale -= MATRIX_STEP_VALUE;
		if (matrix->scale <= scale)
		{
			matrix->step = GUI_MATRIX_STEP_STATUS_BIG;
			gui_surface_layout_matrix_calculate_big_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_big_check_rebound(surface);
		}
		else
		{
			gui_surface_layout_matrix_calculate_app_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_app_check_rebound(surface);
		}
	}
	else if (direction == DIRECTION_TYPE_UP) // 放大
	{
		float scale = (float)LCD_SIZE_WIDTH * MATRIX_APP_SACLE / layout_config->mid_diameter;
		matrix->scale += MATRIX_STEP_VALUE;
		if (matrix->scale >= scale)
		{
			gui_surface_layout_matrix_click_layout(surface);
		}
		else
		{
			gui_surface_layout_matrix_calculate_app_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_app_check_rebound(surface);
		}
	}
}

void gui_surface_layout_matrix_big_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;

	if (direction == DIRECTION_TYPE_DOWN) // 缩小
	{
		matrix->scale -= MATRIX_STEP_VALUE;
		if (matrix->scale < 1.0f)
		{
			matrix->scale = 1.0f;
			matrix->step = GUI_MATRIX_STEP_STATUS_SAMLL;
			gui_surface_layout_matrix_move_to_screen_center_step(surface);
			gui_surface_layout_matrix_calculate_small_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_small_check_rebound(surface);
		}
		else
		{
			gui_surface_layout_matrix_calculate_big_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_big_check_rebound(surface);
		}
	}
	else if (direction == DIRECTION_TYPE_UP) // 放大
	{
		float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
		matrix->scale += MATRIX_STEP_VALUE;
		if (matrix->scale >= scale)
		{
			matrix->step = GUI_MATRIX_STEP_STATUS_APP;
			gui_surface_layout_matrix_calculate_app_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_app_check_rebound(surface);
		}
		else
		{
			gui_surface_layout_matrix_calculate_big_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_big_check_rebound(surface);
		}
	}
}

void gui_surface_layout_matrix_small_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
	const gui_layout_matrix_struct *layout_config = surface->screen->layout_config;
	gui_layout_matrix_struct *matrix = &surface->layout.matrix;

	if (direction == DIRECTION_TYPE_DOWN) // 缩小
	{
		matrix->scale -= MATRIX_STEP_VALUE;
		if (matrix->scale < MATRIX_MIN_SACLE)
		{
			matrix->scale = MATRIX_MIN_SACLE;
		}
		gui_surface_layout_matrix_move_to_screen_center_step(surface);
		gui_surface_layout_matrix_calculate_small_zoom_position(surface);
		gui_surface_layout_matrix_commit_position(surface);
		gui_surface_layout_matrix_small_check_rebound(surface);
	}
	else if (direction == DIRECTION_TYPE_UP) // 放大
	{
		matrix->scale += MATRIX_STEP_VALUE;
		if (matrix->scale >= 1.0f)
		{
			matrix->scale = 1.0f;
			matrix->step = GUI_MATRIX_STEP_STATUS_BIG;
			gui_surface_layout_matrix_calculate_big_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_big_check_rebound(surface);
		}
		else
		{
			gui_surface_layout_matrix_move_to_center_box_step(surface);
			gui_surface_layout_matrix_calculate_small_zoom_position(surface);
			gui_surface_layout_matrix_commit_position(surface);
			gui_surface_layout_matrix_small_check_rebound(surface);
		}
	}
}

void gui_surface_layout_matrix_switch_to_item(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	if (matrix->step == GUI_MATRIX_STEP_STATUS_APP)
	{
		gui_surface_layout_matrix_app_zoom(surface, direction);
	}
	else if (matrix->step == GUI_MATRIX_STEP_STATUS_BIG)
	{
		gui_surface_layout_matrix_big_zoom(surface, direction);
	}
	else if (matrix->step == GUI_MATRIX_STEP_STATUS_SAMLL)
	{
		gui_surface_layout_matrix_small_zoom(surface, direction);
	}
}

/*******************************************触摸，手指滑动时的缩放*******************************************************/

static void gui_surface_layout_matrix_touch_small_step(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	if (!gui_surface_layout_matrix_move_to_screen_center_step(surface))
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_touch_small_step, surface);
	}
	gui_surface_layout_matrix_commit_position(surface);
	gui_surface_force_update();
}

static void gui_surface_layout_matrix_touch_big_step(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	if (!gui_surface_layout_matrix_move_to_center_box_step(surface))
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_touch_big_step, surface);
	}
	gui_surface_layout_matrix_calculate_big_zoom_position(surface);
	gui_surface_layout_matrix_commit_position(surface);
	gui_surface_force_update();
}

// 手指滑动结束，会找寻中间位置
void gui_surface_layout_matrix_touch_end(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	if (matrix->step == GUI_MATRIX_STEP_STATUS_BIG)
	{
		matrix->center_box = gui_surface_layout_matrix_get_center_item(surface);
		g_layout_matrix_box_index = gui_surface_layout_matrix_get_item_position(surface, matrix->center_box);
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_touch_big_step, surface);
	}
	else if (matrix->step == GUI_MATRIX_STEP_STATUS_SAMLL)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_touch_small_step, surface);
	}
}

/*******************************************触摸，手指点击*******************************************************/

void gui_surface_layout_matrix_touch_on_small_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	if (matrix->step == GUI_MATRIX_STEP_STATUS_SAMLL)
	{
		gui_surface_layout_matrix_switch_to_item(surface, DIRECTION_TYPE_UP);
		if (matrix->step == GUI_MATRIX_STEP_STATUS_SAMLL)
		{
			application_stop_user_timer(g_layout_matrix_timer_id);
			g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_touch_on_small_timer, surface);
		}
	}
}

// 在最小状态下，点击会放大到最大模式下
void gui_surface_layout_matrix_touch_on_small_mode(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_matrix_timer_id);
	g_layout_matrix_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_MATRIX)
		return;

	gui_layout_matrix_struct *matrix = &surface->layout.matrix;
	if (matrix->step == GUI_MATRIX_STEP_STATUS_SAMLL)
	{
		g_layout_matrix_timer_id = application_start_user_timer(MATRIX_TIMER_INTERVAL, gui_surface_layout_matrix_touch_on_small_timer, surface);
	}
}
