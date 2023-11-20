
#include "debug_info.h"
#include "feature_all.h"
#include "middleware_rtc.h"
#include "system_util_math.h"

#include "application_touch.h"
#include "application_config_list.h"
#include "application_password.h"
#include "application_touch_gesture.h"

#include "gui_surface.h"
#include "gui_window_history.h"
#include "gui_touch.h"
#include "gui_display.h"
#include "gui_event_core_list.h"

/*
** 本文件对触摸进行分类区分:
** 1.控件点击: 由控件反馈上来
** 2.手势: 通用处理
*/
static GUI_STATUS_TYPE g_application_gesture_status = GUI_STATUS_TYPE_NONE;
static gui_touch_point_struct g_application_touch_point = { 0 };
static TOUCH_EVENT_TYPE g_application_touch_status = TOUCH_EVENT_TYPE_NONE;

static void application_touch_check_gesture()
{
	g_application_touch_point.last_direction = g_application_touch_point.direction;

	switch(g_application_touch_point.gesture_orientation)
	{
		case ORIENTATION_TYPE_HORIZONTAL:
			{
				if(g_application_touch_point.x > g_application_touch_point.down_x)
					g_application_touch_point.direction = DIRECTION_TYPE_LEFT;
				else if(g_application_touch_point.x < g_application_touch_point.down_x)
					g_application_touch_point.direction = DIRECTION_TYPE_RIGHT;

				if(g_application_touch_point.x > g_application_touch_point.last_x)
					g_application_touch_point.curr_direction = DIRECTION_TYPE_LEFT;
				else if(g_application_touch_point.x < g_application_touch_point.last_x)
					g_application_touch_point.curr_direction = DIRECTION_TYPE_RIGHT;
			}
			break;

		case ORIENTATION_TYPE_VERTICAL:
			{
				if(g_application_touch_point.y > g_application_touch_point.down_y)
					g_application_touch_point.direction = DIRECTION_TYPE_UP;
				else if(g_application_touch_point.y < g_application_touch_point.down_y)
					g_application_touch_point.direction = DIRECTION_TYPE_DOWN;

				if(g_application_touch_point.y > g_application_touch_point.last_y)
					g_application_touch_point.curr_direction = DIRECTION_TYPE_UP;
				else if(g_application_touch_point.y < g_application_touch_point.last_y)
					g_application_touch_point.curr_direction = DIRECTION_TYPE_DOWN;
			}
			break;

		case ORIENTATION_TYPE_ALL:
			{
				if(ABS(g_application_touch_point.x - g_application_touch_point.down_x) > ABS(g_application_touch_point.y - g_application_touch_point.down_y))
				{
					if(g_application_touch_point.x > g_application_touch_point.down_x)
						g_application_touch_point.direction = DIRECTION_TYPE_LEFT;
					else if(g_application_touch_point.x < g_application_touch_point.down_x)
						g_application_touch_point.direction = DIRECTION_TYPE_RIGHT;

					if(g_application_touch_point.x > g_application_touch_point.last_x)
						g_application_touch_point.curr_direction = DIRECTION_TYPE_LEFT;
					else if(g_application_touch_point.x < g_application_touch_point.last_x)
						g_application_touch_point.curr_direction = DIRECTION_TYPE_RIGHT;
				}
				else
				{
					if(g_application_touch_point.y > g_application_touch_point.down_y)
						g_application_touch_point.direction = DIRECTION_TYPE_UP;
					else if(g_application_touch_point.y < g_application_touch_point.down_y)
						g_application_touch_point.direction = DIRECTION_TYPE_DOWN;

					if(g_application_touch_point.y > g_application_touch_point.last_y)
						g_application_touch_point.curr_direction = DIRECTION_TYPE_UP;
					else if(g_application_touch_point.y < g_application_touch_point.last_y)
						g_application_touch_point.curr_direction = DIRECTION_TYPE_DOWN;
				}
			}
			break;

		default:
			{
				if(ABS(g_application_touch_point.x - g_application_touch_point.down_x) > ABS(g_application_touch_point.y - g_application_touch_point.down_y))
				{
					if(gui_touch_is_free_direction())
						g_application_touch_point.gesture_orientation = ORIENTATION_TYPE_ALL;
					else
						g_application_touch_point.gesture_orientation = ORIENTATION_TYPE_HORIZONTAL;

					if(g_application_touch_point.x > g_application_touch_point.down_x)
						g_application_touch_point.direction = DIRECTION_TYPE_LEFT;
					else if(g_application_touch_point.x < g_application_touch_point.down_x)
						g_application_touch_point.direction = DIRECTION_TYPE_RIGHT;
				}
				else
				{
					if(gui_touch_is_free_direction())
						g_application_touch_point.gesture_orientation = ORIENTATION_TYPE_ALL;
					else
						g_application_touch_point.gesture_orientation = ORIENTATION_TYPE_VERTICAL;

					if(g_application_touch_point.y > g_application_touch_point.down_y)
						g_application_touch_point.direction = DIRECTION_TYPE_UP;
					else if(g_application_touch_point.y < g_application_touch_point.down_y)
						g_application_touch_point.direction = DIRECTION_TYPE_DOWN;
				}
				g_application_touch_point.curr_direction = g_application_touch_point.direction;
			}
			break;
	}

	GUI_DEBUG("application_touch_check_gesture g_application_touch_point.direction=%d",g_application_touch_point.direction);

}

//计算速度
static void application_touch_check_time()
{
	/*
	int offset_x = g_application_touch_point.x - g_application_touch_point.last_x;
	int offset_y = g_application_touch_point.y - g_application_touch_point.last_y;
	int offset_ms = (int)rtc_get_duration_ms_by_counter(g_application_touch_point.last_time,g_application_touch_point.time);
	*/

	int offset_x = 0, offset_y = 0, offset_ms = 0;
	for (short i = 0; i < GUI_TOUCH_SPEED_TOTAL; i++)
	{
		offset_x += g_application_touch_point.record_x[i];
		offset_y += g_application_touch_point.record_y[i];
		offset_ms += g_application_touch_point.record_time[i];
	}
	if(offset_ms > 0)
	{
		GUI_DEBUG("application_touch_check_time offset_x=%d offset_y=%d  offset_ms=%d",offset_x,offset_y,offset_ms);

		int speed_x = (offset_x * 1000) / offset_ms;
		if(offset_x != 0)
			g_application_touch_point.speed_x = speed_x;
		else if(offset_ms > 100) //出现异常时
			g_application_touch_point.speed_x = 0;

		int speed_y = (offset_y * 1000) / offset_ms;
		if(offset_y != 0)
			g_application_touch_point.speed_y = speed_y;
		else if(offset_ms > 100) //出现异常时
			g_application_touch_point.speed_y = 0;

		GUI_DEBUG("application_touch_check_time speed_x=%d  speed_y=%d",g_application_touch_point.speed_x,g_application_touch_point.speed_y);
	}
	else
	{
		GUI_DEBUG("application_touch_check_time offset_ms=%d",offset_ms);
		g_application_touch_point.speed_x = 0;
		g_application_touch_point.speed_y = 0;
	}
	g_application_touch_point.time_ms = (int)rtc_get_duration_ms_by_counter(g_application_touch_point.last_time,g_application_touch_point.time);
}


//-------------------对外接口---------------------------------------

void application_touch_down(int x,int y,uint32_t time)
{
	GUI_DEBUG("application_touch_down x=%d y=%d",x,y);
	if(is_locked_screen())
	{
		return;
	}

#if defined(GUI_PASSWORD_SUPPORT) && GUI_PASSWORD_SUPPORT
    if (application_password_isLocked()) {
        return;
    }
#endif

	if(application_touch_gesture_swipe_is_moving())
		return;

	if(gui_touch_is_moving())
	{
		//GUI_DEBUG("application_touch_gesture_is_moving");
		g_application_touch_status = TOUCH_EVENT_TYPE_NONE;
		g_application_gesture_status = GUI_STATUS_TYPE_NONE;
		return;
	}
	application_touch_finish();

	g_application_touch_status = TOUCH_EVENT_TYPE_DOWN;
	g_application_gesture_status = GUI_STATUS_TYPE_NONE;
	memset(&g_application_touch_point,0,sizeof(g_application_touch_point));
	application_touch_gesture_init();

	g_application_touch_point.down_x = x;
	g_application_touch_point.down_y = y;
	g_application_touch_point.down_time  = time;

	g_application_touch_point.last_x = x;
	g_application_touch_point.last_y = y;
	g_application_touch_point.last_time  = time;

	g_application_touch_point.x = x;
	g_application_touch_point.y = y;
	g_application_touch_point.time = time;

	g_application_touch_point.speed_x = 0;
	g_application_touch_point.speed_y = 0;

	if(gui_touch_down(&g_application_touch_point))
	{
		g_application_gesture_status = GUI_STATUS_TYPE_IDLE;
	}
	else
	{
		g_application_gesture_status = GUI_STATUS_TYPE_START;
	}
	GUI_DEBUG("application_touch_down g_application_gesture_status=%d",g_application_gesture_status);
}


void application_touch_move(int x,int y,uint32_t time)
{
	GUI_DEBUG("application_touch_move x=%d y=%d",x,y);
#if defined(GUI_PASSWORD_SUPPORT) && GUI_PASSWORD_SUPPORT
    if (application_password_isLocked()) {
        return;
    }
#endif

	// GUI_DEBUG("application_touch_move x=%d y=%d g_application_touch_status=%d, gesture=%d",x,y,g_application_touch_status, g_application_gesture_status);
	if(g_application_touch_status == TOUCH_EVENT_TYPE_NONE)
		return;

	if((g_application_touch_status == TOUCH_EVENT_TYPE_DOWN) || (g_application_touch_status == TOUCH_EVENT_TYPE_LONGPRESS))
	{
		if(ABS(g_application_touch_point.down_x - x) < TOUCH_MOVE_START_MIN && ABS(g_application_touch_point.down_y - y) < TOUCH_MOVE_START_MIN )
		{
			if(g_application_touch_status == TOUCH_EVENT_TYPE_DOWN)
			{
				// Taylor.Le, +
	            unsigned int dur = rtc_get_duration_ms_by_counter(g_application_touch_point.down_time, time);
	            if ((dur >= TOUCH_LONGPRESS_TIMEOUT)&&(g_application_touch_status != TOUCH_EVENT_TYPE_LONGPRESS))
				{
	                g_application_touch_status = TOUCH_EVENT_TYPE_LONGPRESS;
	                if(gui_touch_longpress(&g_application_touch_point))
	                {
	                	application_touch_cancle();
						return;
	                }
	            }
			}
			return;
        }
		g_application_touch_status = TOUCH_EVENT_TYPE_MOVE;
	}

	if(g_application_touch_status != TOUCH_EVENT_TYPE_MOVE)
		return;

	if(g_application_touch_point.x == x && g_application_touch_point.y == y)
		return;

	//横向移动时，如果X没有移动，不必计算; 纵向移动时，如果Y没有移动，不必计算
	if((g_application_touch_point.gesture_orientation == ORIENTATION_TYPE_HORIZONTAL && g_application_touch_point.x == x)
		|| (g_application_touch_point.gesture_orientation == ORIENTATION_TYPE_VERTICAL && g_application_touch_point.y == y))
		return;

	g_application_touch_point.last_x = g_application_touch_point.x;
	g_application_touch_point.last_y = g_application_touch_point.y;
	g_application_touch_point.last_time  = g_application_touch_point.time;

	g_application_touch_point.x = x;
	g_application_touch_point.y = y;
	g_application_touch_point.time = time;

	if(g_application_touch_point.record_index >= GUI_TOUCH_SPEED_TOTAL)
	{
		g_application_touch_point.record_index = 0;
	}
	g_application_touch_point.record_time[g_application_touch_point.record_index] = rtc_get_duration_ms_by_counter(g_application_touch_point.last_time,g_application_touch_point.time);
	g_application_touch_point.record_x[g_application_touch_point.record_index] = g_application_touch_point.x - g_application_touch_point.last_x;
	g_application_touch_point.record_y[g_application_touch_point.record_index] = g_application_touch_point.y - g_application_touch_point.last_y;
	g_application_touch_point.record_index++;

	//判断手势变化
	application_touch_check_gesture();

	//计算速度
	application_touch_check_time();

	if(g_application_gesture_status == GUI_STATUS_TYPE_IDLE)
	{
		//多状态移动时，比如全屏list，它有上下移动，但判断不是上下移动时，就交给手势来处理
		if(!gui_touch_move(&g_application_touch_point))
		{
			GUI_DEBUG("gui_touch_move g_application_gesture_status =%d",g_application_gesture_status);

			//需要判断时间距离等，时间太长，距离太长等，都不需要进行手势判断，怕用户感觉卡顿
			if(ABS(g_application_touch_point.down_x - x) < TOUCH_GESTURE_START_MAX && ABS(g_application_touch_point.down_y - y) < TOUCH_GESTURE_START_MAX )
			{
				GUI_DEBUG("gui_touch_move < TOUCH_GESTURE_START_MAX");
				g_application_gesture_status = GUI_STATUS_TYPE_START;
			}
			else
			{
				g_application_gesture_status = GUI_STATUS_TYPE_NONE;
			}
			GUI_DEBUG("gui_touch_move g_application_gesture_status11 =%d",g_application_gesture_status);
		}
	}

	if(g_application_gesture_status == GUI_STATUS_TYPE_START)
	{
		application_touch_gesture_start(&g_application_touch_point);

		//进入手势时发现没有手势的定义，就不需要再执行手势搜索了
		if(application_touch_gesture_is_none())
			g_application_gesture_status = GUI_STATUS_TYPE_NONE;
		else
			g_application_gesture_status = GUI_STATUS_TYPE_KEEP;
	}
	else if(g_application_gesture_status == GUI_STATUS_TYPE_KEEP)
	{
		//GUI_DEBUG("application_touch_gesture_keep");
		application_touch_gesture_keep(&g_application_touch_point);
	}
}

void application_touch_up(int x,int y,uint32_t time)
{
#if defined(GUI_PASSWORD_SUPPORT) && GUI_PASSWORD_SUPPORT
    if (application_password_isLocked()) {
        application_password(0);
        return;
    }
#endif

	GUI_DEBUG("application_touch_up x=%d y=%d g_application_touch_status=%d",x,y,g_application_touch_status);

	if(g_application_touch_status == TOUCH_EVENT_TYPE_NONE)
		return;

	unsigned char is_click = g_application_touch_status == TOUCH_EVENT_TYPE_DOWN;

	g_application_touch_status = TOUCH_EVENT_TYPE_UP;

	g_application_touch_point.last_x = g_application_touch_point.x;
	g_application_touch_point.last_y = g_application_touch_point.y;
	g_application_touch_point.last_time  = g_application_touch_point.time;

	g_application_touch_point.x = x;
	g_application_touch_point.y = y;
	g_application_touch_point.time  = time;

	//判断手势变化
	application_touch_check_gesture();

	GUI_DEBUG("application_touch_up x=%d y=%d g_application_gesture_status=%d",x,y,g_application_gesture_status);
	if(g_application_gesture_status == GUI_STATUS_TYPE_IDLE)
	{
		g_application_gesture_status = GUI_STATUS_TYPE_END;
		gui_touch_up(&g_application_touch_point,is_click);
	}
	else if(g_application_gesture_status == GUI_STATUS_TYPE_KEEP)
	{
		g_application_gesture_status = GUI_STATUS_TYPE_END;
		application_touch_gesture_end(&g_application_touch_point);
	}

	g_application_touch_status = TOUCH_EVENT_TYPE_NONE;
}

void application_touch_cancle()
{
	if(application_touch_event_is_active())
	{
		gui_touch_rebound_cancle();

		if(application_touch_is_runing())
		{
			gui_touch_cancle();
		}
		application_touch_gesture_cancle();

		g_application_touch_status = TOUCH_EVENT_TYPE_NONE;
		g_application_gesture_status = GUI_STATUS_TYPE_NONE;
		memset(&g_application_touch_point,0,sizeof(g_application_touch_point));
	}
}

void application_touch_finish()
{
	if(application_touch_gesture_is_moving())
	{
		application_touch_gesture_finish();
	}
}

unsigned char application_touch_event_is_active()
{
	return application_touch_gesture_is_moving()
		|| gui_touch_is_moving()
		|| application_touch_is_runing();
}

unsigned char application_touch_is_runing()
{
	return g_application_touch_status == TOUCH_EVENT_TYPE_DOWN
		|| g_application_touch_status == TOUCH_EVENT_TYPE_MOVE
		|| g_application_touch_status == TOUCH_EVENT_TYPE_LONGPRESS;
}



//事件响应--------------------------------------------------------------------------

static unsigned char application_touch_window_exit_event_enable(void)
{
	return 1;
}

/*
**当前界面关闭时，如果有触摸正在使用，则需要关闭
**1.手势非正常中止
**2.排版界面非正常中止
*/
static void application_touch_window_exit_event_handler(void *buf)
{
	application_touch_cancle();
}

const gui_static_event_struct g_application_touch_window_exit_event =
{
	.id = GUI_EVENT_WINDOW_EXIT,
	.enable = application_touch_window_exit_event_enable,
	.handler = application_touch_window_exit_event_handler,
};


