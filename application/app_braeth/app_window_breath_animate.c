#include "app_window_breath_animate.h"
#include "picture.h"
#include "language.h"
#include "data_common.h"
#include "debug_info.h"
#include "app_task_main.h"

static unsigned char g_app_window_breath_animate_back = 0;//0吸气，1呼气
static float g_app_window_breath_animate_angle = 0;

static const gui_screen_struct *g_app_window_breath_animate_screen = NULL;
static unsigned short app_window_breath_animate_id = 0;

/// @brief 更新图片位置 (6张图，360度排列，每张偏转60度，然后每张按极坐标轨迹运动)
static void app_window_breath_animate_update()
{
	gui_box_struct *breath_ani_bg = gui_surface_get_box(g_app_window_breath_animate_screen, app_window_breath_animate_id);
	if (breath_ani_bg != NULL)
	{
		short count = 0;
		gui_node_struct *breath_ani_node = breath_ani_bg->child;
		while (breath_ani_node != NULL)
		{
			// 使用极坐标公式来产生运动的曲线 （r = a * θ）
			float radian = ANGLE_2_RADIAN(g_app_window_breath_animate_angle + count);
			float r = g_app_window_breath_animate_angle;
			short x = r * cos(radian);   //把角度转化成坐标点
			short y = r * sin(radian);
			short center_x = LCD_SIZE_HALF_WIDTH + x;  //把锚点放到图片中心
			short center_y = LCD_SIZE_HALF_HEIGHT - y;

			breath_ani_node->x = GUI_VALUE_ORGIN_TO_SCALE(breath_ani_node, center_x) - breath_ani_node->width / 2;
			breath_ani_node->y = GUI_VALUE_ORGIN_TO_SCALE(breath_ani_node, center_y) - breath_ani_node->height / 2;

			breath_ani_node = breath_ani_node->brother;
			count += 60;  //每张偏转60度
		}
		gui_surface_force_update();
	}
}

/// @brief 步进
/// @param step 单步长度
void app_window_breath_animate_step(float step)
{
	if (g_app_window_breath_animate_back == 0)
		g_app_window_breath_animate_angle += step;
	else
		g_app_window_breath_animate_angle -= step;

	if (g_app_window_breath_animate_angle >= 90 && g_app_window_breath_animate_back == 0)
	{
		g_app_window_breath_animate_angle = 90;
		g_app_window_breath_animate_back = 1;
	}
	else if (g_app_window_breath_animate_angle <= 0 && g_app_window_breath_animate_back == 1)
	{
		g_app_window_breath_animate_angle = 0;
		g_app_window_breath_animate_back = 0;
	}
	app_window_breath_animate_update();
}

void app_window_breath_animate_timer(void *buf)
{
	app_window_breath_animate_step(2);
}

void app_window_breath_animate_init(const gui_screen_struct *screen, unsigned short id)
{
	g_app_window_breath_animate_back = 0;
	g_app_window_breath_animate_angle = 0;

	g_app_window_breath_animate_screen = screen;
	app_window_breath_animate_id = id;
	app_window_breath_animate_update();
}

void app_window_breath_animate_auto_start()
{
	application_open_act_timer(APPLICATION_TIMER_ACT, 50);
}

void app_window_breath_animate_auto_stop()
{
	application_close_act_timer(APPLICATION_TIMER_ACT);
}

unsigned char app_window_breath_animate_is_back()
{
	return g_app_window_breath_animate_back;
}