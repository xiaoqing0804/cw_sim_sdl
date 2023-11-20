#include "feature_all.h"
#include "gui_surface.h"
#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_window_swipe.h"

#include "application_touch.h"
#include "application_config_list.h"

#include "application_config_main_window.h"

#include "app_more_info/app_window_moreinfo.h"
#include "application_touch_gesture_tween.h"
#include "application_touch_gesture_swipe.h"

#include "application_touch_gesture_swipe_cover.h"

/****************************************************本地静态函数************************************************************************/

static void application_touch_gesture_swipe_auto_scroll_step(gui_touch_gesture_tween_struct *tween)
{
	gui_window_swiping_struct *swiping = gui_window_swipe_get_swiping();

	gui_window_swipe_offset(tween->curr_x1, tween->curr_y1, tween->curr_x2, tween->curr_y2);
	gui_window_swipe_scale(tween->curr_x1, tween->curr_x2);
	application_touch_gesture_swipe_cover_check_move(swiping,tween);
	gui_surface_force_update();
}

static void application_touch_gesture_swipe_auto_scroll_finish(gui_touch_gesture_tween_struct *tween)
{
	gui_window_swiping_struct *swiping = gui_window_swipe_get_swiping();

	if (tween->success)
		gui_window_swipe_end();
	else
		gui_window_swipe_cancle();

    gui_surface_main_surface_scale_all(1.0f);
    gui_surface_vice_surface_scale_all(1.0f);
	gui_surface_box_label_scroll_restart();

	application_touch_gesture_deinit();				// 20230920 Taylor.Le, +
	application_touch_gesture_swipe_cover_check_end(swiping,tween);
	gui_surface_force_update();
}

/****************************************************执行************************************************************************/

void application_touch_gesture_swipe_start(const gui_window_swipe_struct *swipe_window, gui_touch_point_struct *touch_point)
{
	gui_window_swiping_struct *swiping = gui_window_swipe_get_swiping();
	if(application_touch_gesture_swipe_cover_check(swiping))
		return;

	const gui_window_struct *window = NULL;
	switch (touch_point->direction)
	{
	case DIRECTION_TYPE_LEFT:
	{
		if (swipe_window != NULL && swipe_window->left != NULL)
			window = swipe_window->left;
	}
	break;

	case DIRECTION_TYPE_RIGHT:
	{
		if (swipe_window != NULL && swipe_window->right != NULL)
			window = swipe_window->right;
	}
	break;

	case DIRECTION_TYPE_UP:
	{
		if (swipe_window != NULL && swipe_window->up != NULL)
			window = swipe_window->up;
	}
	break;

	case DIRECTION_TYPE_DOWN:
	{
		if (swipe_window != NULL && swipe_window->down != NULL)
			window = swipe_window->down;
	}
	break;
	}

	if (window == APP_MAIN_WINDOW_MAGIC)
	{
		window = application_main_window_get_curr_window();
	}
	if (window == APP_MAIN_WINDOW_NEXT_MAGIC)
	{
		window = application_main_window_get_next_window();
	}
	if (window == APP_MAIN_WINDOW_PREV_MAGIC)
	{
		window = application_main_window_get_prev_window();
	}
	if (window == APP_FUNC_WINDOW_MAGIC)
	{
		window = app_window_moreinfo_get();
	}

	touch_point->swipe_x = touch_point->x;
	touch_point->swipe_y = touch_point->y;
	touch_point->swipe_start_x = gui_surface_main_get_offset_x();
	touch_point->swipe_start_y = gui_surface_main_get_offset_y();
	application_touch_gesture_swipe_cancle();

	gui_window_swipe_start(swipe_window->window, window, touch_point->direction);
}

void application_touch_gesture_swipe_move(const gui_window_swipe_struct *swipe_window, gui_touch_point_struct *touch_point)
{
	short offset_x = touch_point->swipe_start_x + touch_point->x - touch_point->swipe_x;
	short offset_y = touch_point->swipe_start_y + touch_point->y - touch_point->swipe_y;

	gui_window_swiping_struct *swiping = gui_window_swipe_get_swiping();
	switch (swiping->direction)
	{
		case DIRECTION_TYPE_LEFT:
		{
			if (swipe_window->left == NULL) // 没有东西可以拉出来，速度就要慢下来
			{
				offset_x /= TOUCH_EMPTY_PULL_SLOW_SPEED;
			}

			gui_window_swipe_offset(offset_x, 0, offset_x - LCD_SIZE_WIDTH, 0);
			gui_window_swipe_scale(offset_x, offset_x - LCD_SIZE_WIDTH);
		}
		break;

		case DIRECTION_TYPE_RIGHT:
		{
			if (swipe_window->right == NULL) // 没有东西可以拉出来，速度就要慢下来
				offset_x /= TOUCH_EMPTY_PULL_SLOW_SPEED;

			gui_window_swipe_offset(offset_x, 0, offset_x + LCD_SIZE_WIDTH, 0);
			gui_window_swipe_scale(offset_x, offset_x + LCD_SIZE_WIDTH);
		}
		break;

		case DIRECTION_TYPE_UP:
		{
			if (swipe_window->up == NULL) // 没有东西可以拉出来，速度就要慢下来
				offset_y /= TOUCH_EMPTY_PULL_SLOW_SPEED;

			if(!application_touch_gesture_swipe_cover_move(swiping, offset_x, offset_y))
			{
				gui_window_swipe_offset(0, offset_y, 0, offset_y - LCD_SIZE_HEIGHT);
			}
		}
		break;

		case DIRECTION_TYPE_DOWN:
		{
			if (swipe_window->down == NULL) // 没有东西可以拉出来，速度就要慢下来
				offset_y /= TOUCH_EMPTY_PULL_SLOW_SPEED;

			if(!application_touch_gesture_swipe_cover_move(swiping, offset_x, offset_y))
			{
				gui_window_swipe_offset(0, offset_y, 0, offset_y + LCD_SIZE_HEIGHT);
			}
		}
		break;
	}
	gui_surface_force_update();
}

void application_touch_gesture_swipe_end(const gui_window_swipe_struct *swipe_window, gui_touch_point_struct *touch_point)
{
	gui_window_swiping_struct *swiping = gui_window_swipe_get_swiping();

	gui_surface_struct *surface = gui_surface_get_main_surface();
	gui_touch_gesture_tween_struct *tween = application_touch_gesture_tween_init(surface);
	tween->start_x1 = gui_surface_main_get_offset_x();
	tween->start_y1 = gui_surface_main_get_offset_y();
	tween->start_x2 = gui_surface_vice_get_offset_x();
	tween->start_y2 = gui_surface_vice_get_offset_y();
	tween->end_x1 = tween->start_x1;
	tween->end_y1 = tween->start_y1;
	tween->end_x2 = tween->start_x2;
	tween->end_y2 = tween->start_y2;
	tween->direction = swiping->direction;

	short speed_x = application_touch_gesture_tween_get_speed(touch_point->speed_x);
	short speed_y = application_touch_gesture_tween_get_speed(touch_point->speed_y);

	switch (swiping->direction)
	{
	case DIRECTION_TYPE_LEFT:
		tween->success = (swipe_window->left != NULL && ((ABS(gui_surface_main_get_offset_x()) >= TOUCH_SWITCH_X_MIN) || (speed_x > 1000)));	// 20230915 Taylor.Le, +speed
		tween->end_x1 = tween->success ? LCD_SIZE_WIDTH : 0;
		tween->end_x2 = tween->success ? 0 : -LCD_SIZE_WIDTH;
		tween->direction = tween->success ? DIRECTION_TYPE_LEFT : DIRECTION_TYPE_RIGHT;
		tween->duration = application_touch_gesture_tween_calculate_duration(tween->end_x1 - tween->start_x1, speed_x);
		break;

	case DIRECTION_TYPE_RIGHT:
		tween->success = (swipe_window->right != NULL && ((ABS(gui_surface_main_get_offset_x()) >= TOUCH_SWITCH_X_MIN) || (speed_x > 1000)));
		tween->end_x1 = tween->success ? -LCD_SIZE_WIDTH : 0;
		tween->end_x2 = tween->success ? 0 : LCD_SIZE_WIDTH;
		tween->direction = tween->success ? DIRECTION_TYPE_RIGHT : DIRECTION_TYPE_LEFT;
		tween->duration = application_touch_gesture_tween_calculate_duration(tween->end_x1 - tween->start_x1, speed_x);
		break;

	case DIRECTION_TYPE_UP:
		if(!application_touch_gesture_swipe_cover_end(swiping,tween,speed_x,speed_y))
		{
			tween->success = (swiping->next_window && ((ABS(gui_surface_main_get_offset_y()) >= TOUCH_SWITCH_Y_MIN) || (speed_x > 1000)));
			tween->end_y1 = tween->success ? LCD_SIZE_HEIGHT : 0;
			tween->end_y2 = tween->success ? 0 : -LCD_SIZE_HEIGHT;
			tween->duration = application_touch_gesture_tween_calculate_duration(tween->end_y1 - tween->start_y1, speed_y);
		}
		tween->direction = tween->success ? DIRECTION_TYPE_UP : DIRECTION_TYPE_DOWN;
		break;

	case DIRECTION_TYPE_DOWN:
		if(!application_touch_gesture_swipe_cover_end(swiping,tween,speed_x,speed_y))
		{
			tween->success = (swiping->next_window && ((ABS(gui_surface_main_get_offset_y()) >= TOUCH_SWITCH_Y_MIN) || (speed_x > 1000)));
			tween->end_y1 = tween->success ? -LCD_SIZE_HEIGHT : 0;
			tween->end_y2 = tween->success ? 0 : LCD_SIZE_HEIGHT;
			tween->duration = application_touch_gesture_tween_calculate_duration(tween->end_y1 - tween->start_y1, speed_y);
		}
		tween->direction = tween->success ? DIRECTION_TYPE_DOWN : DIRECTION_TYPE_UP;
		break;
	}

	tween->scroll_step = application_touch_gesture_swipe_auto_scroll_step;
	tween->scroll_finish = application_touch_gesture_swipe_auto_scroll_finish;
	application_touch_gesture_tween_start(surface);
}

void application_touch_gesture_swipe_cancle()
{
	gui_touch_gesture_tween_struct *tween = application_touch_gesture_tween_get_tween();
	if (tween->status == STATUS_TYPE_RUNNING)
	{
		application_touch_gesture_tween_clear();
	}
}

void application_touch_gesture_swipe_finish()
{
	application_touch_gesture_swipe_cancle();
}

unsigned char application_touch_gesture_swipe_is_moving()
{
	gui_touch_gesture_tween_struct *tween = application_touch_gesture_tween_get_tween();
	return tween->status == STATUS_TYPE_RUNNING;
}
