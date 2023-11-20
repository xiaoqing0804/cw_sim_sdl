#include "feature_all.h"
#include "gui_surface.h"
#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_window_swipe.h"
#include "application_touch.h"
#include "application_config_list.h"
#include "application_touch_gesture_tween.h"
#include "application_touch_gesture_swipe.h"
#include "app_window_cover_bg.h"

/****************************************************本地静态函数************************************************************************/

/****************************************************执行************************************************************************/

unsigned char application_touch_gesture_swipe_cover_check(gui_window_swiping_struct *swiping)
{
	if (swiping == NULL || swiping->next_window == NULL || swiping->window == NULL)
		return 0;

	const gui_window_swipe_struct *swipe_window = application_list_get_swipe_window(swiping->window);
	if (swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
		return 1;

	const gui_window_swipe_struct *next_swipe_window = application_list_get_swipe_window(swiping->next_window);
	if (next_swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
		return 1;

	return 0;
}

unsigned char application_touch_gesture_swipe_cover_check_move(gui_window_swiping_struct *swiping, gui_touch_gesture_tween_struct *tween)
{
	if (tween->swipe_type == WINDOW_SWIPE_TYPE_COVER)
	{
		app_window_cover_bg_move(tween->direction);
	}
	return 1;
}

unsigned char application_touch_gesture_swipe_cover_check_end(gui_window_swiping_struct *swiping, gui_touch_gesture_tween_struct *tween)
{
	if (tween->swipe_type == WINDOW_SWIPE_TYPE_COVER)
	{
		app_window_cover_bg_end();
	}
	return 1;
}

unsigned char application_touch_gesture_swipe_cover_move(gui_window_swiping_struct *swiping, short offset_x, short offset_y)
{
	if (swiping == NULL || swiping->next_window == NULL || swiping->window == NULL)
		return 0;

	const gui_window_swipe_struct *swipe_window = application_list_get_swipe_window(swiping->window);
	const gui_window_swipe_struct *next_swipe_window = application_list_get_swipe_window(swiping->next_window);

	switch (swiping->direction)
	{
		case DIRECTION_TYPE_UP:
		{
			if (next_swipe_window && next_swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
			{
				gui_surface_main_surface_order(0);
				gui_surface_vice_surface_order(1);
				app_window_cover_bg_move(DIRECTION_TYPE_UP);
				gui_window_swipe_offset(0, 0, 0, offset_y - LCD_SIZE_HEIGHT);
				return 1;
			}
			else if (swipe_window && swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
			{
				gui_surface_main_surface_order(1);
				gui_surface_vice_surface_order(0);
				app_window_cover_bg_move(DIRECTION_TYPE_UP);
				if(offset_y < 0)
					gui_window_swipe_offset(0, 0, 0, 0);
				else
					gui_window_swipe_offset(0, offset_y, 0, 0);
				return 1;
			}
			return 0;
		}
		break;

		case DIRECTION_TYPE_DOWN:
		{
			if (next_swipe_window && next_swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
			{
				gui_surface_main_surface_order(0);
				gui_surface_vice_surface_order(1);
				app_window_cover_bg_move(DIRECTION_TYPE_DOWN);
				gui_window_swipe_offset(0, 0, 0, offset_y + LCD_SIZE_HEIGHT);
				return 1;
			}
			else if (swipe_window && swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
			{
				gui_surface_main_surface_order(1);
				gui_surface_vice_surface_order(0);
				app_window_cover_bg_move(DIRECTION_TYPE_DOWN);
				if(offset_y > 0)
					gui_window_swipe_offset(0, 0, 0, 0);
				else
					gui_window_swipe_offset(0, offset_y, 0, 0);
				return 1;
			}
		}
		break;
	}
	return 0;
}

unsigned char application_touch_gesture_swipe_cover_end(gui_window_swiping_struct *swiping, gui_touch_gesture_tween_struct *tween, short speed_x, short speed_y)
{
	if (swiping == NULL || swiping->next_window == NULL || swiping->window == NULL)
		return 0;

	const gui_window_swipe_struct *swipe_window = application_list_get_swipe_window(swiping->window);
	const gui_window_swipe_struct *next_swipe_window = application_list_get_swipe_window(swiping->next_window);

	switch (swiping->direction)
	{
		case DIRECTION_TYPE_UP:
		{
			if (next_swipe_window && next_swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
			{
				short offset_y = gui_surface_vice_get_offset_y() - (-LCD_SIZE_HEIGHT);
				tween->success = ABS(offset_y) >= TOUCH_SWITCH_Y_MIN;
				tween->end_y1 = tween->start_y1;
				tween->end_y2 = tween->success ? 0 : -LCD_SIZE_HEIGHT;
				tween->duration = application_touch_gesture_tween_calculate_duration(tween->end_y2 - tween->start_y2, speed_y);
				tween->swipe_type = WINDOW_SWIPE_TYPE_COVER;
				return 1;
			}
			else if (swipe_window && swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
			{
				short offset_y = gui_surface_main_get_offset_y() - 0;
				tween->success = ABS(offset_y) >= TOUCH_SWITCH_Y_MIN;
				tween->end_y1 = tween->success ? LCD_SIZE_HEIGHT : 0;
				tween->end_y2 = tween->start_y2;
				tween->duration = application_touch_gesture_tween_calculate_duration(tween->end_y1 - tween->start_y1, speed_y);
				tween->swipe_type = WINDOW_SWIPE_TYPE_COVER;
				return 1;
			}
		}
		break;

		case DIRECTION_TYPE_DOWN:
		{
			if (next_swipe_window && next_swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
			{
				short offset_y = gui_surface_vice_get_offset_y() - (LCD_SIZE_HEIGHT);
				tween->success = ABS(offset_y) >= TOUCH_SWITCH_Y_MIN;
				tween->end_y1 = tween->start_y1;
				tween->end_y2 = tween->success ? 0 : LCD_SIZE_HEIGHT;
				tween->duration = application_touch_gesture_tween_calculate_duration(tween->end_y2 - tween->start_y2, speed_y);
				tween->swipe_type = WINDOW_SWIPE_TYPE_COVER;
				return 1;
			}
			else if (swipe_window && swipe_window->type == WINDOW_SWIPE_TYPE_COVER)
			{
				short offset_y = gui_surface_main_get_offset_y() - 0;
				tween->success = ABS(offset_y) >= TOUCH_SWITCH_Y_MIN;
				tween->end_y1 = tween->success ? -LCD_SIZE_HEIGHT : 0;
				tween->end_y2 = tween->start_y2;
				tween->duration = application_touch_gesture_tween_calculate_duration(tween->end_y1 - tween->start_y1, speed_y);
				tween->swipe_type = WINDOW_SWIPE_TYPE_COVER;
				return 1;
			}
		}
		break;
	}
	return 0;
}
