#include "debug_info.h"
#include "gui_surface.h"
#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_window_swipe.h"	// 20230920 Taylor.Le, 
#include "gui_event_core_id.h"
#include "application.h"
#include "application_touch.h"
#include "application_config_list.h"
#include "application_touch_gesture.h"
#include "application_touch_gesture_swipe.h"



static const gui_window_swipe_struct* g_curr_swipe_window = NULL;//当前的界面
static GUI_GESTURE_TYPE g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;

static unsigned char application_touch_gesture_check_forbid_swipe(const gui_window_swipe_struct* swipe_window,gui_touch_point_struct* touch_point)
{
	if(swipe_window->dont_pull_empty)
	{
		if(touch_point->direction == DIRECTION_TYPE_LEFT && swipe_window->left == NULL)
			return 1;

		else if(touch_point->direction == DIRECTION_TYPE_RIGHT && swipe_window->right == NULL)
			return 1;

		else if(touch_point->direction == DIRECTION_TYPE_UP && swipe_window->up == NULL)
			return 1;

		else if(touch_point->direction == DIRECTION_TYPE_DOWN && swipe_window->down == NULL)
			return 1;
	}
	return 0;
}

static void application_touch_gesture_check_swipe(const gui_window_swipe_struct* swipe_window,gui_touch_point_struct* touch_point)
{
	if(swipe_window != NULL && g_curr_gesture_type == GUI_GESTURE_TYPE_NONE)
	{
		if(touch_point->direction == DIRECTION_TYPE_LEFT ||  touch_point->direction == DIRECTION_TYPE_RIGHT)
		{
			if(swipe_window->left != NULL || swipe_window->right != NULL)
				g_curr_gesture_type = GUI_GESTURE_TYPE_SWIPE;
		}
		else if(touch_point->direction == DIRECTION_TYPE_UP ||	touch_point->direction == DIRECTION_TYPE_DOWN)
		{
			if(swipe_window->up != NULL || swipe_window->down != NULL)
				g_curr_gesture_type = GUI_GESTURE_TYPE_SWIPE;
		}

		if(application_touch_gesture_check_forbid_swipe(swipe_window,touch_point))
			g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;
	}
}

static void application_touch_gesture_check_cmd(gui_touch_point_struct* touch_point)
{
	//GUI_DEBUG("application_touch_gesture_check_cmd 1");
	if(g_curr_gesture_type == GUI_GESTURE_TYPE_NONE && touch_point->direction == DIRECTION_TYPE_LEFT && !gui_window_history_top_is_main())
	{
		//GUI_DEBUG("application_touch_gesture_check_cmd 2");
		const gui_window_struct* top_window = gui_window_history_get_top_window();
		if(top_window != NULL)
		{
			//GUI_DEBUG("application_touch_gesture_check_cmd 3");
			if(top_window->config != NULL && top_window->config->forbid_gesture_back )
				return;
			g_curr_gesture_type = GUI_GESTURE_TYPE_BACK;
			//GUI_DEBUG("application_touch_gesture_check_cmd 4");
		}
	}
}

// 20230920 Taylor.Le, +
void application_touch_gesture_deinit()
{
	g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;
}

void application_touch_gesture_init()
{
	g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;

	const gui_window_struct* top_window = gui_window_history_get_top_window();
	if(top_window != NULL){
		g_curr_swipe_window = application_list_get_swipe_window(top_window);
	}
	else{
		g_curr_swipe_window = NULL;
	}
	//GUI_DEBUG("g_curr_swipe_window = %X",g_curr_swipe_window);
}

void application_touch_gesture_start(gui_touch_point_struct* touch_point)
{
	if(g_curr_swipe_window != NULL)
	{
		application_touch_gesture_check_swipe(g_curr_swipe_window,touch_point);

		if(g_curr_gesture_type == GUI_GESTURE_TYPE_SWIPE)
		{
			//application_touch_gesture_swipe_start(g_curr_swipe_window,touch_point);
			//return;

			if(gui_window_history_top_is_main())
			{
				//GUI_DEBUG("application_touch_gesture_start_1");
				gui_window_swipe_deinit();  // 20230920 Taylor.Le, 
				application_touch_gesture_swipe_start(g_curr_swipe_window,touch_point);
				return;
			}

			/*之前是在一级界面，就能左右滑动，后来要求从功能列表进入的话，不能有滑动，要求右滑返回，所以加了以下限制*/
			gui_window_history_struct* top = gui_window_history_get_top();
			gui_window_history_struct* root = gui_window_history_get_root();
			if(top != NULL &&  (top->switch_mode == (unsigned char)GUI_WINDOW_SWITCH_MODE_SWIPE || top == root))
			{
				//GUI_DEBUG("application_touch_gesture_start_3");
				gui_window_swipe_deinit();  // 20230920 Taylor.Le, 
				application_touch_gesture_swipe_start(g_curr_swipe_window,touch_point);
				return;
			}

			//GUI_DEBUG("application_touch_gesture_start_2");
			g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;

		}
	}
	application_touch_gesture_check_cmd(touch_point);
}

void application_touch_gesture_keep(gui_touch_point_struct* touch_point)
{
	//GUI_DEBUG("g_curr_gesture_type = %d",g_curr_gesture_type);

	if(g_curr_gesture_type == GUI_GESTURE_TYPE_SWIPE)
	{
		if(application_touch_gesture_check_forbid_swipe(g_curr_swipe_window,touch_point))
			return;
			
		//方向切换时，显示的内容也要切换
		if((touch_point->last_direction != touch_point->direction))
		{
			// GUI_DEBUG("touch_point->last_direction != touch_point->direction");
			application_touch_gesture_swipe_start(g_curr_swipe_window,touch_point);
		}
		application_touch_gesture_swipe_move(g_curr_swipe_window,touch_point);
	}
}

void application_touch_gesture_end(gui_touch_point_struct* touch_point)
{

	if(g_curr_gesture_type == GUI_GESTURE_TYPE_SWIPE)
	{
		g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;	// 20230918 Taylor.Le, + 解决执行完成手势退出后，抬腕不起作用的问题..
		application_touch_gesture_swipe_end(g_curr_swipe_window,touch_point);
	}
	else if(g_curr_gesture_type == GUI_GESTURE_TYPE_BACK )
	{
		g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;	// 20230918 Taylor.Le, + 解决执行完成手势退出后，抬腕不起作用的问题..
		if(((touch_point->x - touch_point->down_x) > TOUCH_SWITCH_X_MIN)  && (touch_point->time_ms < 3000))
			application_touch_gesture_go_back();
	}
	//GUI_DEBUG("g_curr_gesture_type = %d",g_curr_gesture_type);
}

void application_touch_gesture_cancle()
{
	if(g_curr_gesture_type != GUI_GESTURE_TYPE_NONE)
	{
		g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;
		g_curr_swipe_window = NULL;
		application_touch_gesture_swipe_cancle();
	}
}

void application_touch_gesture_finish()
{
	if(g_curr_gesture_type != GUI_GESTURE_TYPE_NONE)
	{
		g_curr_gesture_type = GUI_GESTURE_TYPE_NONE;
		g_curr_swipe_window = NULL;
		application_touch_gesture_swipe_finish();
	}
}

void application_touch_gesture_go_back()
{
	if(application_window_event_handler(GUI_EVENT_GESTURE_BACK, NULL))
		return;
	gui_window_go_back();
}

unsigned char application_touch_gesture_is_none()
{
	return g_curr_gesture_type == GUI_GESTURE_TYPE_NONE;
}

unsigned char application_touch_gesture_is_moving()
{
	return application_touch_gesture_swipe_is_moving();
}


