#include "app_window_battery_chart.h"
#include "get_data.h"

static short battery_window_getCount(void *chart)
{
	return 24;
}
static short battery_window_getXValue(void *chart, short index)
{
	return index;
}
static short battery_window_getBottomYValue(void *chart, short index)
{
	return 0;
}

static short battery_window_getYValue(void *chart, short index)
{
	battery_day_info_struct *data = get_battery_day_info();
	short value = data->battery_percent[index];
	SYS_DEBUG("battery_window_getYValue %d,%d", value, index);
	return value;
}

static short battery_window_getYMax(void)
{
	return 100;
}

const gui_chart_struct g_battery_ext_chart = {
	/* mFlags*/ .mFlags = CHARTS_FLG_FIXED_AXIS,
	/* mStyle*/ .mStyle = CHARTS_STYLE_BAR,
	/* mBarWidth*/ .mBarWidth = 9,
	/* mLabelNum*/ .mLabelNum = 0,

	/* mColor*/ .mColor = COLOR_RGB(255, 255, 255),
	/* mFillColor*/ .mFillColor = COLOR_RGB(19, 218, 132),
	/* mGridColor*/ .mGridColor = COLOR_RGB(130, 130, 130),
	/* mAxisColor*/ .mAxisColor = COLOR_RGB(100, 100, 100),

	/* getCount*/ .getCount = battery_window_getCount,
	/* getXValue*/ .getXValue = battery_window_getXValue,
	/* getYValue*/ .getYValue = battery_window_getYValue,
	/* getYValue*/ .getYBottomValue = battery_window_getBottomYValue,
	/* fmtXAxis*/ .fmtXAxis = NULL,
	/* fmtYAxis*/ .fmtYAxis = NULL,

	/* mLabelText*/ .mLabelText = NULL,

	// internal
	/* xMax*/ .xMax = 23,
	/* yMax*/ .yMax = battery_window_getYMax,
	/* xMin*/ .xMin = 0,
	/* yMin*/ .yMin = 0,
};
