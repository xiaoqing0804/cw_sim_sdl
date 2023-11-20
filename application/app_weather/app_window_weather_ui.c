#include "app_window_weather_ui.h"
#include "app_window_weather_layout.h"
#include "config_weather.h"
#include "data_weather.h"
#include "data_datetime.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "gui_window.h"

#include "app_window_weather.h"
#include "app_window_weather_layout.h"
#include "data_common.h"
#include "debug_info.h"

#include "application_titlebar.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#include "app_widget/app_window_widget_delete.h"

/// @brief 没有天气数据时
/// @param visible
static void app_window_weather_ui_show_no_data(unsigned char visible)
{
    gui_box_struct *box = NULL;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_NO_TITLE);
    if (box != NULL)
        box->visible = visible;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_NO_DATA);
    if (box != NULL)
        box->visible = visible;
}

/// @brief 有天气数据时
/// @param visible
static void app_window_weather_ui_show_has_data(unsigned char visible)
{
    gui_box_struct *box = NULL;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_BG);
    if (box != NULL)
        box->visible = visible;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_WEATHER_ICON_1);
    if (box != NULL)
        box->visible = visible;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_TEMPERATURE_1);
    if (box != NULL)
        box->visible = visible;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_TEMPERATURE_2);
    if (box != NULL)
        box->visible = visible;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_TEMPERATURE_3);
    if (box != NULL)
        box->visible = visible;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_DATE_1);
    if (box != NULL)
        box->visible = visible;
    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_DATE_2);
    if (box != NULL)
        box->visible = visible;

    box = gui_surface_get_box(&gui_screen_weather, WEATHER_LAYOUT_ID_DATE_3);
    if (box != NULL)
        box->visible = visible;
}

/// @brief 界面切换，有数据页面与没数据页面是不一样的
/// @param has_weather 有数据
static void app_window_weather_ui_show(unsigned char has_weather)
{
    app_window_weather_ui_show_has_data(has_weather);
    app_window_weather_ui_show_no_data(!has_weather);
}

/// @brief 界面切换到空数据页面
void app_window_weather_ui_show_empty_page()
{
    app_window_weather_ui_show(0);
}

/// @brief 界面切换到有数据页面
void app_window_weather_ui_show_data_page()
{
    app_window_weather_ui_show(1);
}

/// @brief 显示天气的图标
/// @param weather_info
/// @param id
void app_window_weather_ui_show_icon(weather_info_item_struct *weather_info, unsigned short id)
{
    const picture_info_struct *pic = NULL;
    if (weather_info != NULL)
        pic = config_weather_get_small_picture(weather_info->weather);
    else
        pic = config_weather_get_small_picture(WEATHER_TYPE_NONE);

    // icon
    gui_box_struct *box = gui_surface_get_box(&gui_screen_weather, id);
    if (box != NULL)
    {
        gui_surface_box_image_change(box, pic);
    }
}

/// @brief 显示温度数值
/// @param weather_info
/// @param id
void app_window_weather_ui_show_temperature(weather_info_item_struct *weather_info, unsigned short id)
{
    char temp[20] = {0};
    if (weather_info != NULL)
    {
        snprintf(temp, sizeof(temp), "%02d/%d%s",
                 data_weather_get_curr_low_temperature(weather_info),
                 data_weather_get_curr_high_temperature(weather_info),
                 data_weather_get_curr_temperature_flag());
    }
    else
    {
        snprintf(temp, sizeof(temp), "--/--");
    }
    gui_box_struct *box = gui_surface_get_box(&gui_screen_weather, id);
    if (box != NULL)
    {
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }
}

/// @brief 显示日期
/// @param time
/// @param id
void app_window_weather_ui_show_date(time_struct *time, unsigned short id)
{
    char temp[20] = {0};
    gui_box_struct *box = gui_surface_get_box(&gui_screen_weather, id);
    if (box != NULL)
    {
        snprintf(temp, sizeof(temp), "%02d/%02d",
                 data_datetime_get_date_front_value(time),
                 data_datetime_get_date_back_value(time));
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }
}

/// @brief 更新三天的天气
/// @param weather_info
/// @param day_index
void app_window_weather_ui_update_data(weather_info_item_struct *weather_info, short day_index)
{
    unsigned int sys_sec = sys_sec_get();
    time_struct time;

    // day0, today
    sec_to_time(sys_sec, &time);
    app_window_weather_ui_show_icon(weather_info, WEATHER_LAYOUT_ID_WEATHER_ICON_1);
    app_window_weather_ui_show_temperature(weather_info, WEATHER_LAYOUT_ID_TEMPERATURE_1);
    app_window_weather_ui_show_date(&time, WEATHER_LAYOUT_ID_DATE_1);

    // day1, tomorrow
    weather_info = (++day_index <= 2) ? data_weather_get_weather_info(day_index) : NULL;
    sec_to_time(sys_sec + (24 * 3600), &time);
    app_window_weather_ui_show_temperature(weather_info, WEATHER_LAYOUT_ID_TEMPERATURE_2);
    app_window_weather_ui_show_date(&time, WEATHER_LAYOUT_ID_DATE_2);

    // day2, after tomorrow
    weather_info = (++day_index <= 2) ? data_weather_get_weather_info(day_index) : NULL;
    sec_to_time(sys_sec + (2 * 24 * 3600), &time);
    app_window_weather_ui_show_temperature(weather_info, WEATHER_LAYOUT_ID_TEMPERATURE_3);
    app_window_weather_ui_show_date(&time, WEATHER_LAYOUT_ID_DATE_3);
}
