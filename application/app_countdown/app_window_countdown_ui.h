#ifndef __APP_COUNTDOWN_H__
#define __APP_COUNTDOWN_H__

#include "feature_all.h"
#include "gui_core_all.h"

#define STR_FMT_PAT     "%02d :"
#define TIM_ITEM_HEITH  COUNTDOWN_ITEM_H

#define TIM_MAX_HOUR    23

extern void app_window_countdown_my_time_update(unsigned char hour, unsigned char minte, unsigned char second);
extern void app_window_countdown_my_time_update_value(short dlt, unsigned char type);
extern unsigned char app_window_countdown_my_time_touch_handler_function(char type,int x,int y,char direction);

extern void app_window_countdown_time_touch_event_click_strat_function();
extern void app_window_countdown_time_initial_entry();
extern void app_window_countdown_time_static_event_counter_function();
#endif
