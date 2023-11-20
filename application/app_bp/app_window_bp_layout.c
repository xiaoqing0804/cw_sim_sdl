#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "data_common.h"

#include "gui_surface_control_animation.h"

#include "app_window_bp_layout.h"
#include "get_data.h"

static const gui_image_struct gui_bp_bg[] =
    {
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 0,
            .y = 0,
            .data = &pic_bp_bg_16_001_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = LCD_SIZE_HALF_WIDTH,
            .y = 0,
            .data = &pic_bp_bg_16_003_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 0,
            .y = LCD_SIZE_HALF_HEIGHT,
            .data = &pic_bp_bg_16_002_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = LCD_SIZE_HALF_WIDTH,
            .y = LCD_SIZE_HALF_HEIGHT,
            .data = &pic_bp_bg_16_004_info,
        },
};

static const gui_image_struct gui_hr_reset_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_HCENTER,
        .data = &pic_bp_remind_bg_info,
};

static const gui_animation_frame_struct gui_bp_ani_frames[] =
    {
        PIC_ANIMATION_FRAME(500, GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER), &pic_bp_gif_01_info),
        PIC_ANIMATION_FRAME(500, GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER), &pic_bp_gif_05_info),
        PIC_ANIMATION_FRAME(500, GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER), &pic_bp_gif_13_info),
        PIC_ANIMATION_FRAME(500, GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER), &pic_bp_gif_05_info),

};

static const gui_animation_struct gui_bp_ani =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .id = 1,
        .frames_num = countof(gui_bp_ani_frames),
        .frames = gui_bp_ani_frames,
};

static const gui_image_struct gui_bp_reset_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_hr_reset_info,
};

static const gui_font_struct gui_bp_txt = // 鑴墜鏂囧瓧
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_BP,
};

static const gui_font_struct gui_daily_trend_text = //
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_DAILY_TREND,
};
static const gui_number_image_list_struct gui_bp_data_image =
    {
        .number =
            {
                &pic_bp_data_00_info,
                &pic_bp_data_01_info,
                &pic_bp_data_02_info,
                &pic_bp_data_03_info,
                &pic_bp_data_04_info,
                &pic_bp_data_05_info,
                &pic_bp_data_06_info,
                &pic_bp_data_07_info,
                &pic_bp_data_08_info,
                &pic_bp_data_09_info,

            },
        .dash = &pic_bp_data_11_info,
        .slash = &pic_bp_data_10_info,
};

/*
static const gui_image_number_struct gui_bp_number =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .number_image_list = &gui_bp_data_image,
    .value.string = "00",
};
*/

static const gui_font_struct gui_bp_number = //
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_NUMBER_50,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "",
};

/****************************************************************************************/
static const gui_image_struct gui_remind_bg[] =
    {
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .data = &pic_bp_remind_bg_1_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 210,
            .data = &pic_bp_remind_bg_2_info,
        },

};

static const gui_image_struct gui_remind_ic =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .data = &pic_o2_remind_ic_info,
};

static const gui_font_struct gui_bp_remind_text = //
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .id = 0,
        .x = 0,
        .y = 0,
        .anchor_x = 0,
        .anchor_y = 0,
        .auto_wrap = 0,
        .color = COLOR_RGB(130, 146, 146),
        .size = SYS_FONT_XSMALL,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "90mmHg<SBP<140mmHg\n60mmHg<DBP<90mmHg",
};

static const gui_font_struct gui_bp_normal_text = //
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .id = 0,
        .x = 0,
        .y = 0,
        .anchor_x = 0,
        .anchor_y = 0,
        .auto_wrap = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_NORMAL_BP,
};

static const gui_image_struct gui_data_bg_bp[] =
    {
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .data = &pic_bp_bg2_001_info,
        },

        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 210,
            .data = &pic_bp_bg2_003_info,
        },

        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .y = 156,
            .data = &pic_bp_bg2_002_info,
        },

        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 210,
            .y = 156,
            .data = &pic_bp_bg2_004_info,
        },
};

/****************************************************************************************/
static short steps_window_getCount(void *chart)
{
    return 7;
}
static short steps_window_getXValue(void *chart, short index)
{
    return index;
}
static short steps_window_getBottomYValue(void *chart, short index)
{
    return 0;
}

static short steps_window_sbp_getYValue(void *chart, short index)
{
    sbp_week_data_info_struct *data = get_sbp_week_info();
    short value = data->sbp_week_data[index].sbp_value;
    if (value == 0)
    { // 为啥要加这句呢
        value = 0;
    }
    return value;
}
static short steps_window_bp_getYMax(void)
{
    return 150;
}
static const gui_chart_struct g_sbp_ext_chart = {
    /* mFlags*/ .mFlags = CHARTS_FLG_FIXED_AXIS,
    /* mStyle*/ .mStyle = CHARTS_STYLE_BAR,
    /* mBarWidth*/ .mBarWidth = 20,
    /* mLabelNum*/ .mLabelNum = 0,

    /* mColor*/ .mColor = COLOR_RGB(255, 255, 255),
    /* mFillColor*/ .mFillColor = COLOR_RGB(136, 35, 25),
    /* mGridColor*/ .mGridColor = COLOR_RGB(130, 130, 130),
    /* mAxisColor*/ .mAxisColor = COLOR_RGB(100, 100, 100),

    /* getCount*/ .getCount = steps_window_getCount,
    /* getXValue*/ .getXValue = steps_window_getXValue,
    /* getYValue*/ .getYValue = steps_window_sbp_getYValue,
    /* getYValue*/ .getYBottomValue = steps_window_getBottomYValue,
    /* fmtXAxis*/ .fmtXAxis = NULL,
    /* fmtYAxis*/ .fmtYAxis = NULL,

    /* mLabelText*/ .mLabelText = NULL,

    // internal
    /* xMax*/ .xMax = 6,
    /* yMax*/ .yMax = steps_window_bp_getYMax,
    /* xMin*/ .xMin = 0,
    /* yMin*/ .yMin = 50,
};

static short steps_window_dbp_getYValue(void *chart, short index)
{
    dbp_week_data_info_struct *data = get_dbp_week_info();
    short value = data->dbp_week_data[index].dbp_value;
    if (value == 0)
    {
        value = 0;
    }
    return value;
}
static const gui_chart_struct g_dbp_ext_chart = {
    /* mFlags*/ .mFlags = CHARTS_FLG_FIXED_AXIS,
    /* mStyle*/ .mStyle = CHARTS_STYLE_BAR,
    /* mBarWidth*/ .mBarWidth = 20,
    /* mLabelNum*/ .mLabelNum = 0,

    /* mColor*/ .mColor = COLOR_RGB(255, 255, 255),
    /* mFillColor*/ .mFillColor = COLOR_RGB(253, 243, 0),
    /* mGridColor*/ .mGridColor = COLOR_RGB(130, 130, 130),
    /* mAxisColor*/ .mAxisColor = COLOR_RGB(100, 100, 100),

    /* getCount*/ .getCount = steps_window_getCount,
    /* getXValue*/ .getXValue = steps_window_getXValue,
    /* getYValue*/ .getYValue = steps_window_dbp_getYValue,
    /* getYValue*/ .getYBottomValue = steps_window_getBottomYValue,
    /* fmtXAxis*/ .fmtXAxis = NULL,
    /* fmtYAxis*/ .fmtYAxis = NULL,

    /* mLabelText*/ .mLabelText = NULL,

    // internal
    /* xMax*/ .xMax = 6,
    /* yMax*/ .yMax = steps_window_bp_getYMax,
    /* xMin*/ .xMin = 0,
    /* yMin*/ .yMin = 50,
};

static const gui_widget_struct gui_bp_widget[] =
    {

        {
            .id = BP_BG_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 0,
            .y = 0,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 1,
            .child_num = countof(gui_bp_bg),
            .children = gui_bp_bg,
        },

        {
            // value
            .id = BP_SBP_VALUE_ID,
            .type = TYPE_GUI_CONTROL_IMAGE_NUMBER,
            .y = 186,
            .width = LCD_SIZE_WIDTH,
            .height = 47,
            .visible = 1,
            .child_num = 1,
            .children = &gui_bp_number,
        },

        {
            // ani
            .id = BP_BOX_ANI_IMAGE_ID,
            .type = TYPE_GUI_CONTROL_ANIMATION,
            .x = 57,
            .y = 195,
            .width = 100,
            .height = 100,
            .visible = 0,
            .child_num = 1,
            .children = &gui_bp_ani,
        },

        {
            // reset icon
            .id = BP_BOX_ANI_RESET_ID,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 0,
            .y = 340,
            .width = LCD_SIZE_WIDTH,
            .height = 100,
            .visible = 1,
            .child_num = 1,
            .children = &gui_hr_reset_image,
        },
        {
            .id = BP_LAYOUT_ID_PUBLIC_TXT,
            .type = TYPE_GUI_CONTROL_LABEL,
            .y = 34,
            .width = LCD_SIZE_HEIGHT,
            .height = 100,
            .rotate = 0,
            .visible = 1,
            .clip = 0,
            .space_x = 0,
            .space_y = 0,
            .child_num = 1,
            .children = &gui_bp_txt,
        },

        /****************************************************************************************/
        {
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 20,
            .y = 467,
            .width = 420,
            .height = 178,
            .visible = 1,
            .child_num = countof(gui_remind_bg),
            .children = gui_remind_bg,
        },

        {
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 52,
            .y = 493,
            .width = 42,
            .height = 42,
            .visible = 1,
            .child_num = 1,
            .children = &gui_remind_ic,
        },

        {
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 106,
            .y = 500,
            .width = 150,
            .height = 30,
            .visible = 1,
            .child_num = 1,
            .children = &gui_bp_normal_text,
        },
        {
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 52,
            .y = 554,
            .width = 200,
            .height = 30,
            .visible = 1,
            .child_num = 1,
            .children = &gui_bp_remind_text,
        },
        /****************************************************************************************/
        {
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 24,
            .y = 667,
            .width = 420,
            .height = 311,
            .visible = 1,
            .child_num = countof(gui_data_bg_bp),
            .children = &gui_data_bg_bp,
        },

        {
            // chart {3, 30, 234, 175}
            .id = BP_SBP_CHART,
            .type = TYPE_GUI_CONTROL_CHART,
            .x = 98,
            .y = 724,
            .width = 320,
            .height = 191,
            .visible = 1,
            .child_num = 1,
            .children = &g_sbp_ext_chart,
        },

        {
            // chart {3, 30, 234, 175}
            .id = BP_DBP_CHART,
            .type = TYPE_GUI_CONTROL_CHART,
            .x = 98,
            .y = 724,
            .width = 320,
            .height = 191,
            .visible = 1,
            .child_num = 1,
            .children = &g_dbp_ext_chart,
        },
        /****************************************************************************************/

        {
            .type = TYPE_GUI_CONTROL_LABEL,
            .y = 1011,
            .width = LCD_SIZE_WIDTH,
            .height = 30,
            .visible = 1,
            .child_num = 1,
            .children = &gui_daily_trend_text,
        },

};

const gui_layout_scroll_struct gui_layout_scroll_bp =
    {
        .height = 1115, // �߶�
        .scroll = 1,    // �Ƿ��������¹���
};

const gui_screen_struct gui_screen_bp =
    {
        .type = TYPE_GUI_LAYOUT_SCROLL,
        .layout_config = &gui_layout_scroll_bp,
        .space_x = 0,
        .space_y = 0,
        .order = 0,
        .children = gui_bp_widget,
        .child_num = countof(gui_bp_widget),

};
