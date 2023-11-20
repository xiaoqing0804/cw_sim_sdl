#ifndef __APP_WINDOW_WEATHER_UI_H__
#define __APP_WINDOW_WEATHER_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

extern void app_window_weather_ui_show_empty_page(void);
extern void app_window_weather_ui_show_data_page(void);
extern void app_window_weather_ui_show_icon(weather_info_item_struct *weather_info, unsigned short id);
extern void app_window_weather_ui_show_temperature(weather_info_item_struct *weather_info, unsigned short id);
extern void app_window_weather_ui_show_date(time_struct *time, unsigned short id);
extern void app_window_weather_ui_update_data(weather_info_item_struct *weather_info, short day_index);

#endif
