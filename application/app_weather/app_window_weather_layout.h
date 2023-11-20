
#ifndef __APP_WINDOW_WEATHER_LAYOUT_H__
#define __APP_WINDOW_WEATHER_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	WEATHER_LAYOUT_ID_NONE,

	/****************有数据页面*******************/
	WEATHER_LAYOUT_ID_BG,
	WEATHER_LAYOUT_ID_WEATHER_ICON_1,
	WEATHER_LAYOUT_ID_TEMPERATURE_1,
	WEATHER_LAYOUT_ID_TEMPERATURE_2,
	WEATHER_LAYOUT_ID_TEMPERATURE_3,
	WEATHER_LAYOUT_ID_DATE_1,
	WEATHER_LAYOUT_ID_DATE_2,
	WEATHER_LAYOUT_ID_DATE_3,

	/****************无数据页面*******************/
	WEATHER_LAYOUT_ID_NO_TITLE,
	WEATHER_LAYOUT_ID_NO_DATA,
};

extern const gui_screen_struct gui_screen_weather;

#endif
