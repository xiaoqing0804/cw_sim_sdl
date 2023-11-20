#include "system_util_math.h"
#include "app_task_main.h"
#include "application.h"

#include "gui_surface_node.h"
#include "gui_surface_layout.h"
#include "gui_surface_layout_apple_cellular.h"
#include "gui_touch_layout_rebound.h"
#include "app_task_main.h"

/*******************************************
**
**对cellular进行排版，移动
**
********************************************/

#define APPLE_CELLULAR_COS_30 (0.866f)			 // cos(30)
#define APPLE_CELLULAR_STEP_VALUE (0.25f)		 // 拨码器每次转动时增加或减少的百分比
#define APPLE_CELLULAR_TO_APP_STEP_VALUE (0.4f) // 打开App或进入蜂窝列表前每次增加或减少的百分比
#define APPLE_CELLULAR_APP_SACLE (0.75f)			 // 当达到屏幕的一定大小时，就打开应用
#define APPLE_CELLULAR_MIN_SACLE (0.2f)			 // 屏幕上最低的缩小尺寸
#define APPLE_CELLULAR_MOVE_MIN_GAP (5)			 // 逼近时，该距离认为已重合

#define APPLE_CELLULAR_BIG_MODE_DISTANCE_SACLE (0.19f) // 扩大的百分比带来的距离变化的参数。值越大，每增加距离就越远
#define APPLE_CELLULAR_BIG_MODE_DIAMETER_SACLE (0.3f)  // 最远距离与中心的直径大小比例
#define APPLE_CELLULAR_BIG_MODE_DIAMETER_OFFSET (5)	   // 最远距离与中心的直径大小比例

#define APPLE_CELLULAR_TIMER_DELAY (300)   // 定时器的延迟时间
#define APPLE_CELLULAR_TIMER_INTERVAL (30) // 定时器的启动时间

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
} apple_cellular_net_node_struct;

static unsigned int g_layout_apple_cellular_timer_id = 0;
static short g_layout_apple_cellular_box_index = -1;
static short g_layout_apple_cellular_default_center_index = 0; // 默认中心，只初始化一次
static apple_cellular_net_node_struct g_apple_cellular_net_nodes[APPLE_CELLULAR_NET_ROW_TOTAL][APPLE_CELLULAR_NET_COL_TOTAL] = {0};

/*******************************数据接口************************************/

unsigned char gui_surface_layout_apple_cellular_click_layout(gui_surface_struct *surface)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return 0;

	gui_click_layout_struct event;
	event.id = (unsigned char)cellular->center_box->id;
	if (surface->window && surface->window->click_on_layout_item)
	{
		g_layout_apple_cellular_box_index = gui_surface_layout_apple_cellular_get_item_position(surface, cellular->center_box);
		surface->window->click_on_layout_item(&event);
		return 1;
	}
	return 0;
}

short gui_surface_layout_apple_cellular_get_count(gui_surface_struct *surface)
{
	apple_cellular_net_node_struct *net_node = NULL;
	short count = 0;
	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
			if (net_node->box != NULL)
				count++;
		}
	}
	return count;
}

gui_box_struct *gui_surface_layout_apple_cellular_get_item(gui_surface_struct *surface, short index)
{
	apple_cellular_net_node_struct *net_node = NULL;
	short count = 0;
	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				if (count == index)
				{
					return net_node->box;
				}
				count++;
			}
		}
	}
	return NULL;
}

short gui_surface_layout_apple_cellular_get_item_position(gui_surface_struct *surface, gui_box_struct *find_box)
{
	apple_cellular_net_node_struct *net_node = NULL;
	short count = 0;
	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
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
short gui_surface_layout_apple_cellular_get_item_index(gui_surface_struct *surface, gui_touch_point_struct *touch_point)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	apple_cellular_net_node_struct *net_node = NULL;
	gui_box_struct *box = NULL;
	geometry_rect rect_box;
	short count = 0;
	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				box = net_node->box;
				rect_box.x = net_node->x + cellular->offset_x - net_node->diameter / 2;
				rect_box.y = net_node->y + cellular->offset_y - net_node->diameter / 2;
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

gui_box_struct *gui_surface_layout_apple_cellular_get_center_item(gui_surface_struct *surface)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	apple_cellular_net_node_struct *net_node = NULL;
	gui_box_struct *center = NULL;
	short min_distance = SHORT_MAX;
	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				short len_x = ABS(net_node->x + cellular->offset_x - LCD_SIZE_HALF_WIDTH);
				short len_y = ABS(net_node->y + cellular->offset_y - LCD_SIZE_HALF_HEIGHT);
				short distance = math_sqrt_16((unsigned int)len_x * (unsigned int)len_x + (unsigned int)len_y * (unsigned int)len_y); // 离屏幕中心的距离
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

void gui_surface_layout_apple_cellular_move_to_center_box(gui_surface_struct *surface, gui_box_struct *center_box)
{
	gui_surface_layout_apple_cellular_commit_position(surface);
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	if (center_box != NULL)
	{
		short offset_x = LCD_SIZE_HALF_WIDTH - (center_box->x /*+ center_box->width / 2*/);
		short offset_y = LCD_SIZE_HALF_HEIGHT - (center_box->y /*+ center_box->height / 2*/);
		cellular->offset_x += offset_x;
		cellular->offset_y += offset_y;
	}
}

void gui_surface_layout_apple_cellular_move_to_screen_center(gui_surface_struct *surface)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	short offset_x = cellular->org_offset_x - cellular->offset_x;
	short offset_y = cellular->org_offset_y - cellular->offset_y;
	cellular->offset_x += offset_x;
	cellular->offset_y += offset_y;
}

unsigned char gui_surface_layout_apple_cellular_finish_move_offset_step(gui_surface_struct *surface)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	short offset_x = cellular->org_offset_x - cellular->offset_x;
	short offset_y = cellular->org_offset_y - cellular->offset_y;
	return (ABS(offset_x) < APPLE_CELLULAR_MOVE_MIN_GAP && ABS(offset_y) < APPLE_CELLULAR_MOVE_MIN_GAP);
}

unsigned char gui_surface_layout_apple_cellular_finish_to_center_box_step(gui_surface_struct *surface)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	gui_box_struct *center_box = cellular->center_box;
	short offset_x = LCD_SIZE_HALF_WIDTH - (center_box->x /*+ center_box->width / 2*/);
	short offset_y = LCD_SIZE_HALF_HEIGHT - (center_box->y /*+ center_box->height / 2*/);
	return (ABS(offset_x) < APPLE_CELLULAR_MOVE_MIN_GAP && ABS(offset_y) < APPLE_CELLULAR_MOVE_MIN_GAP);
}

unsigned char gui_surface_layout_apple_cellular_move_offset_step(gui_surface_struct *surface, short offset_x, short offset_y)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	short gap_x = (offset_x) / 3;
	short gap_y = (offset_y) / 3;
	if (ABS(offset_x) < APPLE_CELLULAR_MOVE_MIN_GAP && ABS(offset_y) < APPLE_CELLULAR_MOVE_MIN_GAP)
	{
		cellular->offset_x += offset_x;
		cellular->offset_y += offset_y;
		return 1;
	}
	else
	{
		cellular->offset_x += gap_x;
		cellular->offset_y += gap_y;
		return 0;
	}
}

unsigned char gui_surface_layout_apple_cellular_move_to_step(gui_surface_struct *surface, short move_to_x, short move_to_y)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	short offset_x = move_to_x - cellular->offset_x;
	short offset_y = move_to_y - cellular->offset_y;
	return gui_surface_layout_apple_cellular_move_offset_step(surface, offset_x, offset_y);
}

unsigned char gui_surface_layout_apple_cellular_move_to_screen_center_step(gui_surface_struct *surface)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	return gui_surface_layout_apple_cellular_move_to_step(surface, cellular->org_offset_x, cellular->org_offset_y);
}

unsigned char gui_surface_layout_apple_cellular_move_to_center_box_step(gui_surface_struct *surface)
{
	gui_surface_layout_apple_cellular_commit_position(surface);
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	gui_box_struct *center_box = cellular->center_box;
	short offset_x = LCD_SIZE_HALF_WIDTH - (center_box->x /*+ center_box->width / 2*/);
	short offset_y = LCD_SIZE_HALF_HEIGHT - (center_box->y /*+ center_box->height / 2*/);
	return gui_surface_layout_apple_cellular_move_offset_step(surface, offset_x, offset_y);
}

void gui_surface_layout_apple_cellular_exit(void)
{
	gui_surface_layout_apple_cellular_stop_timer();
}

void gui_surface_layout_apple_cellular_stop_timer(void)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;
}

unsigned char gui_surface_layout_apple_cellular_timer_running(void)
{
	return g_layout_apple_cellular_timer_id > 0;
}

/*******************************操作接口************************************/

// 根据排版类型，进行排版
void gui_surface_layout_apple_cellular_arrange(gui_surface_struct *surface)
{
	gui_surface_layout_clear_history(surface->window);

	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	memcpy(cellular, layout_config, sizeof(gui_layout_apple_cellular_struct));

	// 标准位置，计算的起点（相当于坐标原点）
	cellular->step = GUI_APPLE_CELLULAR_STEP_STATUS_BIG;
	cellular->scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	gui_surface_layout_apple_cellular_init_nets(surface);
	gui_surface_layout_apple_cellular_init_net_size(surface);
	gui_surface_layout_apple_cellular_init_net_position(surface);

	// 注意中心点
	if (g_layout_apple_cellular_box_index < 0)
	{
		gui_surface_layout_apple_cellular_commit_position(surface); // 同步box位置
		cellular->center_box = gui_surface_layout_apple_cellular_get_center_item(surface);
		g_layout_apple_cellular_default_center_index = gui_surface_layout_apple_cellular_get_item_position(surface, cellular->center_box);
	}
	else
	{
		cellular->center_box = gui_surface_layout_apple_cellular_get_item(surface, g_layout_apple_cellular_box_index);
		gui_surface_layout_apple_cellular_move_to_center_box(surface, cellular->center_box);
	}
	gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface); // 因为App放大时，是整体放大，所以先要保证cache同步
	gui_surface_layout_apple_cellular_commit_position(surface);				// 同步box位置

	// 从外面进入时，要有动画
	cellular->step = GUI_APPLE_CELLULAR_STEP_STATUS_APP;
	cellular->scale = (float)LCD_SIZE_WIDTH * APPLE_CELLULAR_APP_SACLE / layout_config->mid_diameter;
	gui_surface_layout_apple_cellular_calculate_app_zoom_position(surface);
	gui_surface_layout_apple_cellular_commit_position(surface);
	gui_surface_layout_cellular_entry_list(surface);
}

// 对排版中的子元素，使用指定的偏移
void gui_surface_layout_apple_cellular_offset(gui_surface_struct *surface, short layout_offset_x, short layout_offset_y)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	cellular->offset_x = layout_offset_x;
	cellular->offset_y = layout_offset_y;

	// 除了大模式，其它都是平移，不用改变间隔和大小
	if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_BIG)
	{
		gui_surface_layout_apple_cellular_init_net_position(surface);
		gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
	}
	gui_surface_layout_apple_cellular_commit_position(surface);
}

// 对排版中的子元素，进行指定的偏移
void gui_surface_layout_apple_cellular_move(gui_surface_struct *surface, short move_offset_x, short move_offset_y)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	cellular->offset_x += move_offset_x;
	cellular->offset_y += move_offset_y;

	// 除了大模式，其它都是平移，不用改变间隔和大小
	if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_BIG)
	{
		gui_surface_layout_apple_cellular_init_net_position(surface);
		gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
	}
	gui_surface_layout_apple_cellular_commit_position(surface);
}

// 初始化网格
void gui_surface_layout_apple_cellular_init_nets(gui_surface_struct *surface)
{
	memset(g_apple_cellular_net_nodes, 0, sizeof(g_apple_cellular_net_nodes));

	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	short row_total = APPLE_CELLULAR_MAX_COL_TOTAL - APPLE_CELLULAR_MIN_COL_TOTAL + 1;
	short column_total = APPLE_CELLULAR_MIN_COL_TOTAL;

	apple_cellular_net_node_struct *net_node = NULL;
	gui_box_struct *box = surface->child;
	short column_start = APPLE_CELLULAR_NET_FRIST_NODE;
	short column_index = column_start;
	short column_count = 0;
	short row_index = 0;
	while (box != NULL)
	{
		if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
		{
			if (column_count >= column_total)
			{
				column_total = row_index >= (row_total - 1) ? (column_total - 1) : (column_total + 1);
				column_start = row_index >= (row_total - 1) ? (column_start + 1) : (column_start - 1);
				column_count = 0;
				row_index++;
				column_index = column_start;
			}

			net_node = &g_apple_cellular_net_nodes[row_index][column_index];
			net_node->box = box;
			net_node->row = row_index;
			net_node->col = column_count;
			net_node->diameter = layout_config->mid_diameter;

			column_index += APPLE_CELLULAR_NET_STEP;
			column_count++;

			box->visible = 0;
		}
		box = box->brother;
	}
}

// 网格排版参数
void gui_surface_layout_apple_cellular_init_net_size(gui_surface_struct *surface)
{
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;

	short diameter = layout_config->mid_diameter;
	short space = layout_config->space;
	short width = diameter + (APPLE_CELLULAR_COL_TOTAL - 1) * (diameter + space);
	short height = diameter + (APPLE_CELLULAR_ROW_TOTAL - 1) * (diameter + space) * APPLE_CELLULAR_COS_30; // 长度只算到圆心

	cellular->width = width;
	cellular->height = height;
	cellular->org_offset_x = (LCD_SIZE_WIDTH - width) / 2;
	cellular->org_offset_y = (LCD_SIZE_HEIGHT - height) / 2;
	cellular->offset_x = cellular->org_offset_x;
	cellular->offset_y = cellular->org_offset_y;
	cellular->diameter = diameter * cellular->scale;
	cellular->space = space * cellular->scale;
}

// 初始化网格原始位置(在放大和缩小的边缘,这里的缩放比例是1)
void gui_surface_layout_apple_cellular_init_net_position(gui_surface_struct *surface)
{
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	apple_cellular_net_node_struct *net_node = NULL;

	short cell_center_x = 0;
	short cell_center_y = layout_config->mid_diameter / 2;

	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		cell_center_x = layout_config->mid_diameter / 2;
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
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

			cell_center_x += (layout_config->mid_diameter + layout_config->space) / 2;
		}
		cell_center_y += (layout_config->mid_diameter + layout_config->space) * APPLE_CELLULAR_COS_30;
	}
}

// 提交位置偏移，提交一次图标的具体位置（当使用正中间box做位置前,需要调用一次，保证同步）
void gui_surface_layout_apple_cellular_commit_position(gui_surface_struct *surface)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	apple_cellular_net_node_struct *net_node = NULL;
	gui_box_struct *box = NULL;

	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				box = net_node->box;
				box->visible = 1;
				box->x = net_node->x + cellular->offset_x;
				box->y = net_node->y + cellular->offset_y;
				box->scale = (float)net_node->diameter / cellular->icon_diameter;

				/*
					gui_node_struct *node = (gui_node_struct *)box->child;
					node->x = 0;
					node->y = 0;
					node->width = cellular->icon_diameter;
					node->height = cellular->icon_diameter;
					gui_surface_node_check_clip(box, node, box->width, box->height);
				*/
			}
		}
	}
}

// 计算小模式状态下的位置（该模式都是平放，间隔和大小都一样）
void gui_surface_layout_apple_cellular_calculate_small_zoom_position(gui_surface_struct *surface)
{
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	apple_cellular_net_node_struct *net_node = NULL;

	if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL)
	{
		float diameter = layout_config->mid_diameter * cellular->scale;
		float space = layout_config->space * cellular->scale;

		float width = diameter + (APPLE_CELLULAR_COL_TOTAL - 1) * (diameter + space);
		float height = diameter + (APPLE_CELLULAR_ROW_TOTAL - 1) * (diameter + space) * APPLE_CELLULAR_COS_30;

		float cell_start_x = (cellular->width - width) / 2 + diameter / 2;
		float cell_center_x = 0;
		float cell_center_y = (cellular->height - height) / 2 + diameter / 2;
		float cell_gap_y = (diameter + space) * APPLE_CELLULAR_COS_30;

		for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
		{
			cell_center_x = cell_start_x;
			for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
			{
				net_node = &g_apple_cellular_net_nodes[i][j];
				net_node->diameter = diameter;
				net_node->x = (short)cell_center_x;
				net_node->y = (short)cell_center_y;

				cell_center_x += (diameter + space) / 2;
			}
			cell_center_y += cell_gap_y;
		}
	}
}

// 计算大模式状态时的位置（注意如果朝应用模式放大时，是整体放大，起点是这里，所以先要保证cache同步）
void gui_surface_layout_apple_cellular_calculate_big_zoom_position(gui_surface_struct *surface)
{
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	apple_cellular_net_node_struct *net_node = NULL;

	float max_scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	float ratio_scale = (cellular->scale - 1.0f) / (max_scale - 1.0f);

	// 扩大的百分比带来的距离变化的参数。值越大，每增加距离就越远
	// 此处可再增加一个自变量，让它收敛更快
	float distance_scale = APPLE_CELLULAR_BIG_MODE_DISTANCE_SACLE * ratio_scale;

	short x = 0, y = 0;
	float gap_x = 0, gap_y = 0;
	float offset_diameter_x = 0, offset_diameter_y = 0;
	float scale_x = 0, scale_y = 0;
	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				gap_x = (net_node->org_x + cellular->offset_x - LCD_SIZE_HALF_WIDTH) * distance_scale;
				net_node->x = net_node->org_x + gap_x;

				gap_y = (net_node->org_y + cellular->offset_y - LCD_SIZE_HALF_HEIGHT) * distance_scale;
				net_node->y = net_node->org_y + gap_y;

				scale_y = 1.0f - ABS(net_node->y + cellular->offset_y - LCD_SIZE_HALF_HEIGHT) * (1.0f - APPLE_CELLULAR_BIG_MODE_DIAMETER_SACLE) / LCD_SIZE_HALF_HEIGHT;
				offset_diameter_y = APPLE_CELLULAR_BIG_MODE_DIAMETER_OFFSET * scale_y * ratio_scale;

				scale_x = 1.0f - ABS(net_node->x + cellular->offset_x - LCD_SIZE_HALF_WIDTH) * (1.0f - APPLE_CELLULAR_BIG_MODE_DIAMETER_SACLE) / LCD_SIZE_HALF_WIDTH;
				offset_diameter_x = APPLE_CELLULAR_BIG_MODE_DIAMETER_OFFSET * scale_x * ratio_scale;

				net_node->diameter = net_node->org_diameter + offset_diameter_y + offset_diameter_x + 0.5f;

				if ((cellular->scale - 1.0f) > (max_scale - 1.0f) / 2)
				{
#if LCD_SHAPE == LCD_ROUND_CORNER || LCD_SHAPE == LCD_SQUARE
					x = net_node->x + cellular->offset_x - LCD_SIZE_HALF_WIDTH;
					y = net_node->y + cellular->offset_y - LCD_SIZE_HALF_HEIGHT;
					short distance = math_sqrt_16(x * x + y * y);

					if (((ABS(x) + net_node->diameter / 2) > LCD_SIZE_HALF_WIDTH && (ABS(x) - net_node->diameter / 2) < LCD_SIZE_HALF_WIDTH) || ((ABS(y) + net_node->diameter / 2) > LCD_SIZE_HALF_HEIGHT && (ABS(y) - net_node->diameter / 2) < LCD_SIZE_HALF_HEIGHT))
					{
						short diameter_x = LCD_SIZE_HALF_WIDTH - (ABS(x) - net_node->diameter / 2);
						diameter_x = MAX(diameter_x, 0);

						short diameter_y = LCD_SIZE_HALF_HEIGHT - (ABS(y) - net_node->diameter / 2);
						diameter_y = MAX(diameter_y, 0);

						short diameter_new = MIN(diameter_x, diameter_y);
						short distance_new = distance - net_node->diameter / 2 + diameter_new / 2 - 2;
						float ratio = (float)distance_new / distance;
						net_node->x = ratio * x + LCD_SIZE_HALF_WIDTH - cellular->offset_x;
						net_node->y = ratio * y + LCD_SIZE_HALF_HEIGHT - cellular->offset_y;
						net_node->diameter = diameter_new;
					}
#else
					x = net_node->x + cellular->offset_x - LCD_SIZE_HALF_WIDTH;
					y = net_node->y + cellular->offset_y - LCD_SIZE_HALF_HEIGHT;
					short distance = math_sqrt_16(x * x + y * y);
					if ((distance + net_node->diameter / 2) > LCD_SIZE_HALF_WIDTH && (distance - net_node->diameter / 2) < LCD_SIZE_HALF_WIDTH)
					{
						short diameter_new = net_node->diameter / 2 - (distance - LCD_SIZE_HALF_WIDTH);
						short distance_new = distance - net_node->diameter / 2 + diameter_new / 2 - 2;
						float ratio = (float)distance_new / distance;
						net_node->x = ratio * x + LCD_SIZE_HALF_WIDTH - cellular->offset_x;
						net_node->y = ratio * y + LCD_SIZE_HALF_HEIGHT - cellular->offset_y;
						net_node->diameter = diameter_new;
					}
					else
					{
						net_node->diameter += net_node->diameter * (1.0f - (float)distance / LCD_SIZE_HALF_WIDTH) * 0.1f;
					}
#endif
				}

				net_node->cache_x = net_node->x;
				net_node->cache_y = net_node->y;
				net_node->cache_diameter = net_node->diameter;
			}
		}
	}
}

// 计算应用模式状态时的位置（整体放大）
void gui_surface_layout_apple_cellular_calculate_app_zoom_position(gui_surface_struct *surface)
{
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	apple_cellular_net_node_struct *net_node = NULL;

	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;

	short x = 0, y = 0;
	float ratio = 0;
	short distance = 0, distance_new = 0;
	for (short i = 0; i < APPLE_CELLULAR_NET_ROW_TOTAL; i++)
	{
		for (short j = 0; j < APPLE_CELLULAR_NET_COL_TOTAL; j++)
		{
			net_node = &g_apple_cellular_net_nodes[i][j];
			if (net_node->box != NULL)
			{
				x = net_node->cache_x + cellular->offset_x - LCD_SIZE_HALF_WIDTH;
				y = net_node->cache_y + cellular->offset_y - LCD_SIZE_HALF_HEIGHT;

				// 中心点，不能除以0
				if (x == 0 && y == 0)
				{
					net_node->x = net_node->cache_x;
					net_node->y = net_node->cache_y;
				}
				else
				{
					distance = math_sqrt_16(x * x + y * y);
					distance_new = distance + (cellular->scale - scale) * distance;

					ratio = (float)distance_new / distance;
					net_node->x = ratio * x + LCD_SIZE_HALF_WIDTH - cellular->offset_x;
					net_node->y = ratio * y + LCD_SIZE_HALF_HEIGHT - cellular->offset_y;
				}
				net_node->diameter = net_node->cache_diameter + (cellular->scale - scale) * net_node->cache_diameter;
			}
		}
	}
}

/*************************进入应用模式时的定时器*************************/

static void gui_surface_layout_cellular_app_rebound_zoom_out_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	float scale = (float)LCD_SIZE_WIDTH * APPLE_CELLULAR_APP_SACLE / layout_config->mid_diameter;

	cellular->scale += APPLE_CELLULAR_TO_APP_STEP_VALUE;
	if (cellular->scale >= scale)
	{
		gui_surface_layout_apple_cellular_click_layout(surface);
	}
	else
	{
		gui_surface_layout_apple_cellular_calculate_app_zoom_position(surface);
		gui_surface_layout_apple_cellular_commit_position(surface);
		gui_surface_commit();

		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_app_rebound_zoom_out_timer, surface);
	}
}

static void gui_surface_layout_cellular_app_rebound_zoom_in_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	float app_scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;

	if (cellular->scale > app_scale)
	{
		cellular->scale -= APPLE_CELLULAR_TO_APP_STEP_VALUE;
	}
	else
	{
		cellular->scale -= APPLE_CELLULAR_STEP_VALUE;
	}

	if (cellular->scale <= scale)
	{
		cellular->scale = scale;
		cellular->step = GUI_APPLE_CELLULAR_STEP_STATUS_BIG;
		gui_surface_layout_apple_cellular_init_net_position(surface);
		gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
		gui_surface_layout_apple_cellular_commit_position(surface);
		gui_surface_commit();
	}
	else
	{
		gui_surface_layout_apple_cellular_calculate_app_zoom_position(surface);
		gui_surface_layout_apple_cellular_commit_position(surface);
		gui_surface_commit();

		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_app_rebound_zoom_in_timer, surface);
	}
}

static void gui_surface_layout_cellular_app_check_rebound(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;

	float scale = (float)layout_config->app_diameter / layout_config->mid_diameter;
	if (cellular->scale < scale)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_DELAY, gui_surface_layout_cellular_app_rebound_zoom_in_timer, surface);
	}
	else if (cellular->scale > scale)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_DELAY, gui_surface_layout_cellular_app_rebound_zoom_out_timer, surface);
	}
}

void gui_surface_layout_cellular_entry_list(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_app_rebound_zoom_in_timer, surface);
}

static void gui_surface_layout_cellular_entry_app_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	if (gui_surface_layout_apple_cellular_move_to_center_box_step(surface))
	{
		gui_surface_layout_apple_cellular_init_net_position(surface);
		gui_surface_layout_apple_cellular_move_to_center_box(surface, cellular->center_box);
		gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
		gui_surface_layout_apple_cellular_commit_position(surface);
		gui_surface_force_update();

		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_app_rebound_zoom_out_timer, surface);
	}
	else
	{
		gui_surface_layout_apple_cellular_init_net_position(surface);
		gui_surface_layout_apple_cellular_move_to_center_box_step(surface);
		gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
		gui_surface_layout_apple_cellular_commit_position(surface);
		gui_surface_force_update();

		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_entry_app_timer, surface);
	}
}

void gui_surface_layout_cellular_entry_app(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_entry_app_timer, surface);
}

void gui_surface_layout_cellular_entry_home_app(gui_surface_struct *surface)
{
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	cellular->center_box = gui_surface_layout_apple_cellular_get_item(surface, g_layout_apple_cellular_default_center_index);

	if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_BIG)
	{
		gui_surface_layout_cellular_entry_app(surface);
	}
	else if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL)
	{
		gui_surface_layout_apple_cellular_touch_on_small_mode(surface);
	}
}

/*************************大模式时的定时器*************************/

static void gui_surface_layout_cellular_big_rebound_zoom_out_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	short count = 0;
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	cellular->scale += APPLE_CELLULAR_STEP_VALUE;
	if (cellular->scale >= scale)
	{
		cellular->scale = scale;
		count++;
	}
	if (gui_surface_layout_apple_cellular_finish_to_center_box_step(surface))
	{
		count++;
	}
	if (count < 2)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_big_rebound_zoom_out_timer, surface);
	}
	gui_surface_layout_apple_cellular_init_net_position(surface);
	gui_surface_layout_apple_cellular_move_to_center_box_step(surface);
	gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
	gui_surface_layout_apple_cellular_commit_position(surface);

	gui_surface_commit();
}

static void gui_surface_layout_cellular_big_rebound_zoom_in_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	short count = 0;
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	cellular->scale -= APPLE_CELLULAR_STEP_VALUE;
	if (cellular->scale <= scale)
	{
		cellular->scale = scale;
		count++;
	}
	if (gui_surface_layout_apple_cellular_finish_to_center_box_step(surface))
	{
		count++;
	}
	if (count < 2)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_big_rebound_zoom_in_timer, surface);
	}
	gui_surface_layout_apple_cellular_init_net_position(surface);
	gui_surface_layout_apple_cellular_move_to_center_box_step(surface);
	gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
	gui_surface_layout_apple_cellular_commit_position(surface);

	gui_surface_commit();
}

static void gui_surface_layout_cellular_big_check_rebound(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;

	float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
	if (cellular->scale < scale)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_DELAY, gui_surface_layout_cellular_big_rebound_zoom_out_timer, surface);
	}
	else if (cellular->scale > scale)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_DELAY, gui_surface_layout_cellular_big_rebound_zoom_in_timer, surface);
	}
}

/*************************小模式时的定时器*************************/
static void gui_surface_layout_cellular_small_rebound_zoom_out_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	short count = 0;
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	float scale = (float)layout_config->min_diameter / layout_config->mid_diameter;
	cellular->scale += APPLE_CELLULAR_STEP_VALUE;
	if (cellular->scale >= scale)
	{
		cellular->scale = scale;
		count++;
	}
	if (gui_surface_layout_apple_cellular_finish_move_offset_step(surface))
	{
		count++;
	}
	if (count < 2)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_small_rebound_zoom_out_timer, surface);
	}
	gui_surface_layout_apple_cellular_move_to_screen_center_step(surface);
	gui_surface_layout_apple_cellular_calculate_small_zoom_position(surface);
	gui_surface_layout_apple_cellular_commit_position(surface);
	gui_surface_commit();
}

static void gui_surface_layout_cellular_small_rebound_zoom_in_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	short count = 0;
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	float scale = (float)layout_config->min_diameter / layout_config->mid_diameter;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	cellular->scale -= APPLE_CELLULAR_STEP_VALUE;
	if (cellular->scale <= scale)
	{
		cellular->scale = scale;
		count++;
	}
	if (gui_surface_layout_apple_cellular_finish_move_offset_step(surface))
	{
		count++;
	}
	if (count < 2)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_cellular_small_rebound_zoom_in_timer, surface);
	}
	gui_surface_layout_apple_cellular_move_to_screen_center_step(surface);
	gui_surface_layout_apple_cellular_calculate_small_zoom_position(surface);
	gui_surface_layout_apple_cellular_commit_position(surface);
	gui_surface_commit();
}

static void gui_surface_layout_cellular_small_check_rebound(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	float scale = (float)layout_config->min_diameter / layout_config->mid_diameter;
	if (cellular->scale < scale)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_DELAY, gui_surface_layout_cellular_small_rebound_zoom_out_timer, surface);
	}
	else if (cellular->scale > scale)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_DELAY, gui_surface_layout_cellular_small_rebound_zoom_in_timer, surface);
	}
}

/*************************按拨码器时单步放大缩小*************************/
void gui_surface_layout_apple_cellular_app_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;

	if (direction == DIRECTION_TYPE_DOWN) // 缩小
	{
		float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
		cellular->scale -= APPLE_CELLULAR_STEP_VALUE;
		if (cellular->scale <= scale)
		{
			cellular->step = GUI_APPLE_CELLULAR_STEP_STATUS_BIG;
			gui_surface_layout_apple_cellular_init_net_position(surface);
			gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_big_check_rebound(surface);
		}
		else
		{
			gui_surface_layout_apple_cellular_calculate_app_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_app_check_rebound(surface);
		}
	}
	else if (direction == DIRECTION_TYPE_UP) // 放大
	{
		float scale = (float)LCD_SIZE_WIDTH * APPLE_CELLULAR_APP_SACLE / layout_config->mid_diameter;
		cellular->scale += APPLE_CELLULAR_STEP_VALUE;
		if (cellular->scale >= scale)
		{
			gui_surface_layout_apple_cellular_click_layout(surface);
		}
		else
		{
			gui_surface_layout_apple_cellular_calculate_app_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_app_check_rebound(surface);
		}
	}
}

void gui_surface_layout_apple_cellular_big_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;

	if (direction == DIRECTION_TYPE_DOWN) // 缩小
	{
		cellular->scale -= APPLE_CELLULAR_STEP_VALUE;
		if (cellular->scale < 1.0f)
		{
			cellular->scale = 1.0f;
			cellular->step = GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL;
			gui_surface_layout_apple_cellular_move_to_screen_center_step(surface);
			gui_surface_layout_apple_cellular_calculate_small_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_small_check_rebound(surface);
		}
		else
		{
			gui_surface_layout_apple_cellular_init_net_position(surface);
			gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_big_check_rebound(surface);
		}
	}
	else if (direction == DIRECTION_TYPE_UP) // 放大
	{
		float scale = (float)layout_config->max_diameter / layout_config->mid_diameter;
		cellular->scale += APPLE_CELLULAR_STEP_VALUE;
		if (cellular->scale >= scale)
		{
			cellular->step = GUI_APPLE_CELLULAR_STEP_STATUS_APP;
			gui_surface_layout_apple_cellular_calculate_app_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_app_check_rebound(surface);
		}
		else
		{
			gui_surface_layout_apple_cellular_init_net_position(surface);
			gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_big_check_rebound(surface);
		}
	}
}

void gui_surface_layout_apple_cellular_small_zoom(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
	const gui_layout_apple_cellular_struct *layout_config = surface->screen->layout_config;
	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;

	if (direction == DIRECTION_TYPE_DOWN) // 缩小
	{
		cellular->scale -= APPLE_CELLULAR_STEP_VALUE;
		if (cellular->scale < APPLE_CELLULAR_MIN_SACLE)
		{
			cellular->scale = APPLE_CELLULAR_MIN_SACLE;
		}
		gui_surface_layout_apple_cellular_move_to_screen_center_step(surface);
		gui_surface_layout_apple_cellular_calculate_small_zoom_position(surface);
		gui_surface_layout_apple_cellular_commit_position(surface);
		gui_surface_layout_cellular_small_check_rebound(surface);
	}
	else if (direction == DIRECTION_TYPE_UP) // 放大
	{
		cellular->scale += APPLE_CELLULAR_STEP_VALUE;
		if (cellular->scale >= 1.0f)
		{
			cellular->scale = 1.0f;
			cellular->step = GUI_APPLE_CELLULAR_STEP_STATUS_BIG;
			gui_surface_layout_apple_cellular_init_net_position(surface);
			gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_big_check_rebound(surface);
		}
		else
		{
			gui_surface_layout_apple_cellular_move_to_center_box_step(surface);
			gui_surface_layout_apple_cellular_calculate_small_zoom_position(surface);
			gui_surface_layout_apple_cellular_commit_position(surface);
			gui_surface_layout_cellular_small_check_rebound(surface);
		}
	}
}

void gui_surface_layout_apple_cellular_switch_to_item(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_APP)
	{
		gui_surface_layout_apple_cellular_app_zoom(surface, direction);
	}
	else if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_BIG)
	{
		gui_surface_layout_apple_cellular_big_zoom(surface, direction);
	}
	else if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL)
	{
		gui_surface_layout_apple_cellular_small_zoom(surface, direction);
	}
}

/*******************************************触摸，手指滑动时的缩放*******************************************************/

static void gui_surface_layout_apple_cellular_touch_small_step(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	if (!gui_surface_layout_apple_cellular_move_to_screen_center_step(surface))
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_apple_cellular_touch_small_step, surface);
	}
	gui_surface_layout_apple_cellular_commit_position(surface);
	gui_surface_force_update();
}

static void gui_surface_layout_apple_cellular_touch_big_step(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	if (!gui_surface_layout_apple_cellular_move_to_center_box_step(surface))
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_apple_cellular_touch_big_step, surface);
	}
	gui_surface_layout_apple_cellular_init_net_position(surface);
	gui_surface_layout_apple_cellular_calculate_big_zoom_position(surface);
	gui_surface_layout_apple_cellular_commit_position(surface);
	gui_surface_force_update();
}

// 手指滑动结束，会找寻中间位置
void gui_surface_layout_apple_cellular_touch_end(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_BIG)
	{
		cellular->center_box = gui_surface_layout_apple_cellular_get_center_item(surface);
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_apple_cellular_touch_big_step, surface);
	}
	else if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_apple_cellular_touch_small_step, surface);
	}
}

/*******************************************触摸，手指点击*******************************************************/

void gui_surface_layout_apple_cellular_touch_on_small_timer(unsigned int timer, void *param)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	gui_surface_struct *surface = (gui_surface_struct *)param;
	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL)
	{
		gui_surface_layout_apple_cellular_switch_to_item(surface, DIRECTION_TYPE_UP);
		if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL)
		{
			application_stop_user_timer(g_layout_apple_cellular_timer_id);
			g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_apple_cellular_touch_on_small_timer, surface);
		}
	}
}

// 在最小状态下，点击会放大到最大模式下
void gui_surface_layout_apple_cellular_touch_on_small_mode(gui_surface_struct *surface)
{
	application_stop_user_timer(g_layout_apple_cellular_timer_id);
	g_layout_apple_cellular_timer_id = 0;

	if (surface->screen->type != TYPE_GUI_LAYOUT_APPLE_CELLULAR)
		return;

	gui_layout_apple_cellular_struct *cellular = &surface->layout.cellular;
	if (cellular->step == GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL)
	{
		g_layout_apple_cellular_timer_id = application_start_user_timer(APPLE_CELLULAR_TIMER_INTERVAL, gui_surface_layout_apple_cellular_touch_on_small_timer, surface);
	}
}
