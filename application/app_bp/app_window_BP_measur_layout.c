#include "picture.h"
#include "language.h"
#include "bsp_includes.h"

#include "app_task_main.h"
#include "data_common.h"


#include "app_window_bp_measur_layout.h"

#define BP1_CHART_DATA_NUMBER    (16)      // 5 hour * 4 data/hour
#define BP1_CHART_LABEL_NUMBER   (5)

///////////////////////////////////////////////////////////////////////////////////////////////
#define TEST_BP1_UI     0

#if TEST_BP1_UI
static const unsigned char test_hr_value[HR_DATA_NUM] = {
    80,  75,  77,  76,     81,  87,  88,  82,
    90,  100, 120, 130,    122, 128, 110, 115,
    117, 119, 95,  97,     93,  96,  89,  180,
    175, 177, 176, 181,    187, 188, 182, 190,
    100, 120, 130, 122,    128, 110, 115, 117,
    119, 95,  97,  93,     96,  89,  80,  75,
    77,  76,  81,  87,     88,  82,  90,  100,
    120, 130, 122, 128,    110, 115, 117, 119,
    95,  97,  93,  96,     81,  87,  88,  82,
    90,  100, 120, 130,    122, 128, 110, 115,
    117, 119, 95,  97,     93,  96,  89,  180,
    175, 177, 176, 181,    187, 188, 182, 190
    };

#define BP1_VALUE_ARRAY      test_hr_value
#else
#define BP1_VALUE_ARRAY      g_o2_history_data
#endif
// for chart
static short heart_window_getCount(void* chart)
{
	time_struct time;
	int num = 0;

	sys_time_get(&time);

    num = (time.hour*60+time.min)/HR_MIN_TIME;

    if (num > BP1_CHART_DATA_NUMBER) {
        num = BP1_CHART_DATA_NUMBER;
    }

    return num;
}

static short heart_window_getXValue(void* chart, short index)
{
    return index;
}

static short heart_window_getYValue(void* chart, short index)
{
	time_struct time;
	int num = 0;

	sys_time_get(&time);

    num = (time.hour*60+time.min)/HR_MIN_TIME;

    if (num > BP1_CHART_DATA_NUMBER) {
        index += (num - BP1_CHART_DATA_NUMBER);
    }

    return BP1_VALUE_ARRAY[index];
}

static const gui_chart_struct    g_bp_ext_chart = {
    /* mFlags*/         .mFlags = CHARTS_FLG_FIXED_AXIS|CHARTS_FLG_SHOW_YLABEL|CHARTS_FLG_RIGHT_YLABEL|CHARTS_FLG_SHOW_XAXIS|CHARTS_FLG_SHOW_GRID,
    /* mStyle*/         .mStyle = CHARTS_STYLE_BAR,
    /* mBarWidth*/      .mBarWidth = 8,
    /* mLabelNum*/      .mLabelNum = BP1_CHART_LABEL_NUMBER,

    /* mColor*/         .mColor = COLOR_RGB(255, 0, 0),
    /* mFillColor*/     .mFillColor = COLOR_RGB(255, 0, 0),
    /* mGridColor*/     .mGridColor = COLOR_RGB(130, 130, 130),
    /* mAxisColor*/     .mAxisColor = COLOR_RGB(100, 100, 100),

    /* getCount*/       .getCount = heart_window_getCount,
    /* getXValue*/      .getXValue = heart_window_getXValue,
    /* getYValue*/      .getYValue = heart_window_getYValue,
    /* fmtXAxis*/       .fmtXAxis = NULL,
    /* fmtYAxis*/       .fmtYAxis = NULL,

    /* mLabelText*/     .mLabelText = NULL,

    // internal
    /* xMax*/          .xMax = BP1_CHART_DATA_NUMBER,
    /* yMax*/          .yMax = 200,
    /* xMin*/          .xMin = 0,
    /* yMin*/          .yMin = 0
};

//max icon
static const gui_image_struct gui_hr_max_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = NULL,
};

// max value
static const gui_font_struct gui_hr_maxvalue =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "---",
};


//min icon
static const gui_image_struct gui_hr_min_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = NULL,
};

// min value
static const gui_font_struct gui_hr_minvalue =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "---",
};





static const gui_widget_struct gui_bp_measur_widget[] =
{

   {   // max icon
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 25,
        .y = 228,
        .width = 15,
        .height = 25,
        .visible = 1,
        .child_num = 1,
        .children = &gui_hr_max_image,
    },

    {   // max value
        .id = BP_MEASUR_LAYOUT_ID_HR_MAX,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 40,
        .y = 235,
        .width = 50,
        .height = 30,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hr_maxvalue,
    },

    {   // min icon
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 153,
        .y = 228,
        .width = 15,
        .height = 24,
        .visible = 1,
        .child_num = 1,
        .children = &gui_hr_min_image,
    },

    {   // min value
        .id = BP_MEASUR_LAYOUT_ID_HR_MIN,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 170,
        .y = 235,
        .width = 50,
        .height = 30,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hr_minvalue,
    },

#if 1
    {   // chart {3, 30, 234, 175}
        .id = BP_MEASUR_LAYOUT_ID_HR_CHART,
        .type = TYPE_GUI_CONTROL_CHART,
        .x = 3,
        .y = 30,
        .width = LCD_SIZE_WIDTH-6,
        .height = 175,
        .visible= 1,
        .child_num = 1,
        .children = &g_bp_ext_chart,
    },
#endif



};

const gui_screen_struct gui_screen_bp_measur =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.order = 0,
	.children = gui_bp_measur_widget,
	.child_num = countof(gui_bp_measur_widget),
};



