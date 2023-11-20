#include "application_touch_gesture_tween.h"
#include "application_touch.h"
#include "application_config_list.h"
#include "gui_surface.h"
#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_window_swipe.h"
#include "app_task_main.h"
#include "system_util_all.h"

/************************************************定义*******************************************************/
#define GESTURE_TWEEN_MIN_DURATION (30)	  // 缓动一次的最小时间
#define GESTURE_TWEEN_MAX_DURATION (350)  // 缓动一次的最大时间
#define GESTURE_TWEEN_TIMER_INTERVAL (30) // 缓动的间隔时间
#define GESTURE_TWEEN_MIN_SPEED (800)	  // 缓动的最小速度
#define GESTURE_TWEEN_MAX_SPEED (1600)	  // 缓动的最大速度

/************************************************属性*******************************************************/
static gui_touch_gesture_tween_struct g_gui_touch_gesture_tween;

/*********************************************本地静态函数***************************************************/

static void application_touch_gesture_tween_timer(unsigned int timer, void *param);

static void application_touch_gesture_tween_update_position(gui_touch_gesture_tween_struct *tween, unsigned int duration_ms)
{
	short change_x1 = tween->end_x1 - tween->start_x1;
	short change_x2 = tween->end_x2 - tween->start_x2;
	short change_y1 = tween->end_y1 - tween->start_y1;
	short change_y2 = tween->end_y2 - tween->start_y2;

	short offset_x1 = tween->start_x1;
	short offset_y1 = tween->start_y1;
	short offset_x2 = tween->start_x2;
	short offset_y2 = tween->start_y2;

	if (change_x1 != 0)
		offset_x1 = tween_linear_ease_in(duration_ms, tween->start_x1, change_x1, tween->duration);
	if (change_x2 != 0)
		offset_x2 = tween_linear_ease_in(duration_ms, tween->start_x2, change_x2, tween->duration);
	if (change_y1 != 0)
		offset_y1 = tween_linear_ease_in(duration_ms, tween->start_y1, change_y1, tween->duration);
	if (change_y2 != 0)
		offset_y2 = tween_linear_ease_in(duration_ms, tween->start_y2, change_y2, tween->duration);

	tween->curr_x1 = offset_x1;
	tween->curr_x2 = offset_x2;
	tween->curr_y1 = offset_y1;
	tween->curr_y2 = offset_y2;
}

static void application_touch_gesture_tween_update(gui_screen_struct *screen, gui_touch_gesture_tween_struct *tween)
{
	GUI_DEBUG("application_touch_gesture_tween_update start");

	gui_surface_struct *surface = tween->surface;
	if (surface != NULL && screen == surface->screen)
	{
		unsigned int duration_ms = time_get_ms_duration_with_curr(tween->start_time_ms);
		if (duration_ms > tween->duration)
		{
			duration_ms = tween->duration;
		}

		// 时间到了
		if (duration_ms >= tween->duration)
		{
			tween->curr_x1 = tween->end_x1;
			tween->curr_x2 = tween->end_x2;
			tween->curr_y1 = tween->end_y1;
			tween->curr_y2 = tween->end_y2;

			if (tween->scroll_step != NULL)
			{
				tween->scroll_step(tween);
			}
			if (tween->scroll_finish != NULL)
			{
				tween->status = STATUS_TYPE_STOP;
				GUI_DEBUG("application_touch_gesture_tween_update scroll_finish");
				tween->scroll_finish(tween);
				application_touch_gesture_tween_clear();
			}
		}
		else if (tween->scroll_step != NULL)
		{
			application_touch_gesture_tween_update_position(tween, duration_ms);

			tween->status = STATUS_TYPE_RUNNING;
			if (tween->scroll_step != NULL)
			{
				tween->scroll_step(tween);
			}
			tween->time_id = application_start_user_timer(GESTURE_TWEEN_TIMER_INTERVAL, application_touch_gesture_tween_timer, screen);
		}
	}
	else {
		// error: 窗口不存在了！
		application_touch_gesture_tween_clear();
	}
	GUI_DEBUG("application_touch_gesture_tween_update end");
}

static void application_touch_gesture_tween_stop_timer(gui_touch_gesture_tween_struct *tween)
{
	if (tween->time_id > 0)
	{
		application_stop_user_timer(tween->time_id);
		tween->time_id = 0;
	}
}

static void application_touch_gesture_tween_timer(unsigned int timer, void *param)
{
	GUI_DEBUG("application_touch_gesture_tween_timer");

	application_touch_gesture_tween_stop_timer(&g_gui_touch_gesture_tween);

	gui_screen_struct *screen = (gui_screen_struct *)param;
	application_touch_gesture_tween_update(screen, &g_gui_touch_gesture_tween);
}

/************************************************数值及校正***********************************************************/

gui_touch_gesture_tween_struct *application_touch_gesture_tween_get_tween()
{
	return &g_gui_touch_gesture_tween;
}

short application_touch_gesture_tween_get_speed(short speed)
{
	if (speed < 0)
		return math_range(speed, -GESTURE_TWEEN_MAX_SPEED, -GESTURE_TWEEN_MIN_SPEED);
	return math_range(speed, GESTURE_TWEEN_MIN_SPEED, GESTURE_TWEEN_MAX_SPEED);
}

short application_touch_gesture_tween_calculate_duration(short distance, short speed)
{
	if (distance == 0 || speed == 0)
		return 0;
	short duration = (ABS(distance) << 10) / ABS(speed); // 匀减速运动时间 t = 2S / v
	return math_range(duration, GESTURE_TWEEN_MIN_DURATION, GESTURE_TWEEN_MAX_DURATION);
}

/***********************************************操作接口*************************************************************/

void application_touch_gesture_tween_clear()
{
	application_touch_gesture_tween_stop_timer(&g_gui_touch_gesture_tween);
	memset(&g_gui_touch_gesture_tween, 0, sizeof(gui_touch_gesture_tween_struct));
}

gui_touch_gesture_tween_struct *application_touch_gesture_tween_init(gui_surface_struct *surface)
{
	application_touch_gesture_tween_clear();

	g_gui_touch_gesture_tween.surface = surface;
	g_gui_touch_gesture_tween.start_time_ms = time_get_ms_curr_timestamp();

	return &g_gui_touch_gesture_tween;
}

void application_touch_gesture_tween_start(gui_surface_struct *surface)
{
	GUI_DEBUG("application_touch_gesture_tween_start");
	g_gui_touch_gesture_tween.status = STATUS_TYPE_RUNNING;
	application_touch_gesture_tween_update(surface->screen, &g_gui_touch_gesture_tween);
}
