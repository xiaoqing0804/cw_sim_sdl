#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "data_manager_message.h"

#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#include "data_manager_contact.h"
#endif

#include "srv_call.h"
#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_control_base.h"
#include "application_config_main_window.h"
#include "app_window_countdown_ui.h"
#include "app_window_countdown_layout.h"
#include "app_window_countdown_my_time_layout.h"
#include "app_window_countdown_time_layout.h"
#include "app_window_countdown.h"
#include "app_window_countdown_time_out.h"
 extern short countdown_my_time_hour;
 extern short countdown_my_time_min;
 extern short countdown_my_time_second;
 extern unsigned char countdown_flag;
 extern unsigned int countdown_save;

//****************************************************countdown my time****************************************************//
/// @brief 时分秒ui布局
/// @param hour
/// @param minte
/// @param second
void app_window_countdown_my_time_update(unsigned char hour, unsigned char minte, unsigned char second)
{
	char temp[40];


    if (hour) {
        if(countdown_my_time_hour == 0)
        {
            snprintf(temp, sizeof(temp), STR_FMT_PAT,TIM_MAX_HOUR);
            gui_box_struct*  hour_up = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_HOUR_UP);
            gui_surface_box_image_number_change_string(hour_up,(unsigned char *)temp);
        }
        else
        {
            snprintf(temp, sizeof(temp), STR_FMT_PAT,countdown_my_time_hour -1);
            gui_box_struct*  hour_up = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_HOUR_UP);
            gui_surface_box_image_number_change_string(hour_up,(unsigned char *)temp);
        }

        snprintf(temp, sizeof(temp), STR_FMT_PAT,countdown_my_time_hour);
        gui_box_struct*  hour = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_HOUR);
        gui_surface_box_image_number_change_string(hour,(unsigned char *)temp);

        if(countdown_my_time_hour == TIM_MAX_HOUR)
        {
            snprintf(temp, sizeof(temp), STR_FMT_PAT,1);
            gui_box_struct*  hour_down = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_HOUR_DOWN);
            gui_surface_box_image_number_change_string(hour_down,(unsigned char *)temp);
        }
        else
        {
            snprintf(temp, sizeof(temp), STR_FMT_PAT,countdown_my_time_hour+1);
            gui_box_struct*  hour_down = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_HOUR_DOWN);
            gui_surface_box_image_number_change_string(hour_down,(unsigned char *)temp);
        }
    }


    if (minte) {
        if(countdown_my_time_min == 0)
        {
            snprintf(temp, sizeof(temp), STR_FMT_PAT,59);
            gui_box_struct*  min_up = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_MIN_UP);
            gui_surface_box_image_number_change_string(min_up,(unsigned char *)temp);
        }
        else
        {
            snprintf(temp, sizeof(temp), STR_FMT_PAT,countdown_my_time_min -1);
            gui_box_struct*  min_up = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_MIN_UP);
            gui_surface_box_image_number_change_string(min_up,(unsigned char *)temp);
        }

        snprintf(temp, sizeof(temp), STR_FMT_PAT,countdown_my_time_min);
        gui_box_struct*  min = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_MIN);
        gui_surface_box_image_number_change_string(min,(unsigned char *)temp);

        if(countdown_my_time_min == 59)
        {
            snprintf(temp, sizeof(temp), STR_FMT_PAT,0);
            gui_box_struct*  min_down = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_MIN_DOWN);
            gui_surface_box_image_number_change_string(min_down,(unsigned char *)temp);
        }
        else
        {
            snprintf(temp, sizeof(temp), STR_FMT_PAT,countdown_my_time_min+1);
            gui_box_struct*  min_down = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_MIN_DOWN);
            gui_surface_box_image_number_change_string(min_down,(unsigned char *)temp);
        }

    }

    if (second) {
        if(countdown_my_time_second == 0)
        {
            snprintf(temp, sizeof(temp), "%02d",59);
            gui_box_struct*  min_up = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_SECOND_UP);
            gui_surface_box_image_number_change_string(min_up,(unsigned char *)temp);
        }
        else
        {
            snprintf(temp, sizeof(temp), "%02d",countdown_my_time_second -1);
            gui_box_struct*  min_up = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_SECOND_UP);
            gui_surface_box_image_number_change_string(min_up,(unsigned char *)temp);
        }

        snprintf(temp, sizeof(temp), "%02d",countdown_my_time_second);
        gui_box_struct*  second = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_SECOND);
        gui_surface_box_image_number_change_string(second,(unsigned char *)temp);

        if(countdown_my_time_second == 59)
        {
            snprintf(temp, sizeof(temp), "%02d",0);
            gui_box_struct*  min_down = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_SECOND_DOWN);
            gui_surface_box_image_number_change_string(min_down,(unsigned char *)temp);
        }
        else
        {
            snprintf(temp, sizeof(temp), "%02d",countdown_my_time_second+1);
            gui_box_struct*  min_down = gui_surface_get_box(&gui_screen_countdown_my_time, (unsigned short) COUNTDOWN_MY_TIME_ID_SECOND_DOWN);
            gui_surface_box_image_number_change_string(min_down,(unsigned char *)temp);
        }
    }
}

/// @brief 处理时分秒滑动时逻辑
/// @param dlt
/// @param type
void app_window_countdown_my_time_update_value(short dlt, unsigned char type)
{
    switch(type) {
        case 1:
            countdown_my_time_hour += dlt;
            if(countdown_my_time_hour > TIM_MAX_HOUR) {
                countdown_my_time_hour -= (TIM_MAX_HOUR+1);
            }
            else {
                if(countdown_my_time_hour < 0)
                    countdown_my_time_hour += (TIM_MAX_HOUR+1);
            }
            app_window_countdown_my_time_update(1, 0, 0);
            gui_surface_commit();
            break;

        case 2:
            countdown_my_time_min += dlt;
            if(countdown_my_time_min > 59) {
                countdown_my_time_min -= (59+1);
            }
            else {
                if(countdown_my_time_min < 0)
                    countdown_my_time_min += (59+1);
            }
            app_window_countdown_my_time_update(0, 1, 0);
            gui_surface_commit();
            break;

        case 3:
            countdown_my_time_second += dlt;
            if(countdown_my_time_second > 59) {
                countdown_my_time_second -= (59+1);
            }
            else {
                if(countdown_my_time_second < 0)
                    countdown_my_time_second += (59+1);
            }
            app_window_countdown_my_time_update(0, 0, 1);
            gui_surface_commit();
            break;
    }
}

/// @brief 处理时分秒滑动区域
/// @param type
/// @param x
/// @param y
/// @param direction
static unsigned char app_window_countdown_my_time_touch_handler_function(char type,int x,int y,char direction)
{
    static unsigned char touch = 0;
    static short pre_y = 0;
    static short rem_y = 0;
    short dlt_y, dlt_val = 0;

    if (type == TOUCH_EVENT_TYPE_DOWN) {

        if (y > 30 && y < (LCD_SIZE_HEIGHT-COUNTDOWN_OPBAR_H)) {
            if (x < LCD_SIZE_WIDTH/3) {
                touch = 1;
            }
            else if (x > LCD_SIZE_WIDTH*2/3) {
                touch = 3;
            }
            else {
                touch = 2;
            }
            pre_y = y;
            rem_y = 0;
        }
    }
    else if (type == TOUCH_EVENT_TYPE_MOVE) {

        if(direction == DIRECTION_TYPE_LEFT) {
            application_go_back();
        }
        else if (direction == DIRECTION_TYPE_UP || direction == DIRECTION_TYPE_DOWN) {
            dlt_y = pre_y - y;
            dlt_y += rem_y;
            dlt_val = dlt_y / TIM_ITEM_HEITH;
            if (dlt_val != 0) {
                pre_y = y;
                rem_y = dlt_y % TIM_ITEM_HEITH;
            }

            if (dlt_val != 0) {
                app_window_countdown_my_time_update_value(dlt_val, touch);
            }
        }
    }
    else if (type == TOUCH_EVENT_TYPE_UP) {
        touch = 0;
    }
    return touch;
}


//****************************************************countdown my time****************************************************//



//****************************************************countdown time****************************************************//
/// @brief 点击开始暂停切换操作
/// @param void
void app_window_countdown_time_touch_event_click_strat_function()
{
    if(countdown_flag == 0){
		gui_box_struct*  box = gui_surface_get_box(&gui_screen_countdown_time, (unsigned short) COUNTDOWN_TIME_ID_START);
		gui_surface_box_image_change(box,(const picture_info_struct*)&pic_stopwatch_suspend_info);

		application_open_act_timer(APPLICATION_TIMER_ACT,1000);
		gui_surface_commit();

		countdown_flag = 1;
	}
	else{
		gui_box_struct*  box = gui_surface_get_box(&gui_screen_countdown_time, (unsigned short) COUNTDOWN_TIME_ID_START);
		gui_surface_box_image_change(box,(const picture_info_struct*)&pic_stopwatch_start_info);


		application_close_act_timer(APPLICATION_TIMER_ACT);
		gui_surface_commit();
		countdown_flag = 0;
	}

}

/// @brief 首次进入界面布局
/// @param void
void app_window_countdown_time_initial_entry()
{
	char temp[40];

    snprintf(temp, sizeof(temp), "%02d:%02d:%02d",(countdown_save/60)/60,(countdown_save/60)%60, countdown_save%60);
	gui_box_struct*  box = gui_surface_get_box(&gui_screen_countdown_time, (unsigned short) COUNTDOWN_TIME_ID_TEXT);
	gui_surface_box_label_change_string(box,(unsigned char *)temp);

	if(countdown_flag==0)
	{
		gui_box_struct*  box = gui_surface_get_box(&gui_screen_countdown_time, (unsigned short) COUNTDOWN_TIME_ID_START);
		gui_surface_box_image_change(box,(const picture_info_struct*)&pic_stopwatch_start_info);

	}
	else
	{
		gui_box_struct*  box = gui_surface_get_box(&gui_screen_countdown_time, (unsigned short) COUNTDOWN_TIME_ID_START);
		gui_surface_box_image_change(box,(const picture_info_struct*)&pic_stopwatch_suspend_info);
	}

}

/// @brief 倒计时功能
/// @param void
void app_window_countdown_time_static_event_counter_function()
{
	char temp[40];

	if(countdown_flag == 1){
		gui_box_struct*  box = gui_surface_get_box(&gui_screen_countdown_time, (unsigned short) COUNTDOWN_TIME_ID_TEXT);

		countdown_save--;
		snprintf(temp, sizeof(temp), "%02d:%02d:%02d",(countdown_save/60)/60,(countdown_save/60)%60, countdown_save%60);

		gui_surface_box_label_change_string(box,(unsigned char *)temp);
		gui_surface_commit();
	}

	if(countdown_save == 0)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_main_time_out, NULL);
	}
}

//****************************************************countdown my time****************************************************//
