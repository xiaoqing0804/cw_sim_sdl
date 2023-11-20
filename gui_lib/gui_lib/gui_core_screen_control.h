#ifndef __GUI_CORE_SCREEN_CONTROL_H__
#define __GUI_CORE_SCREEN_CONTROL_H__

#include "feature_all.h"
#include "gui_core_screen.h"
#include "gui_core_layout.h"


/*
**本文件是屏幕配置的静态结构
**screen是屏幕，也是排版，一个界面就是一个面
**widget是控件，它是一个控件数组，决定了屏幕内有多少控件
**这些是组合元素，组成了一个个控件等
*/

/***********************************定义*******************************************/

#define PIC_ANIMATION_FRAME(_dur, _align, _pic) \
    {.duration=_dur, .type = TYPE_GUI_DRAW_PICTURE, .align = _align, .picture=_pic}

#define PIC_ANIMATION_FRAME_XY(_dur, _align, _xPos, _yPos, _pic) \
    {.duration=_dur, .type = TYPE_GUI_DRAW_PICTURE, .align = _align, .x=_xPos, .y=_yPos, .picture=_pic}



/***********************************基本元素*******************************************/

typedef struct
{
	const picture_info_struct* pic_info;
}gui_picture_struct;

typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_PICTURE
	short x;
	short y;
    unsigned int duration;        // ms
    const picture_info_struct* picture;
}gui_animation_frame_struct;



/***********************************组合控件*******************************************/

//controller: bt-icon
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_PICTURE

	short x;
	short y;

    const picture_info_struct* pic_linked;
    const picture_info_struct* pic_unlink;
}gui_bt_icon_struct;


//controller: batt-icon
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_PICTURE

	short x;
	short y;

    unsigned int pics_num;
    const gui_picture_struct* gui_pics;
}gui_batt_icon_struct;


//controller: animation
typedef struct
{
    unsigned char   type;
    unsigned char   id;
    unsigned short  frames_num;
    const gui_animation_frame_struct* frames;
}gui_animation_struct;


//controller: chart
typedef struct
{
	GUI_DRAW_HEADER;

    unsigned short mFlags;
    unsigned short mStyle;
    unsigned short mBarWidth;
    unsigned short mLabelNum;

    GUI_COLOR mColor;
    GUI_COLOR mFillColor;
    GUI_COLOR mGridColor;
    GUI_COLOR mAxisColor;

    short xMin;
    short xMax;

    short yMin;

    const gui_font_struct* mLabelText;

    short (*yMax)(void* chart);
    short (*getCount)(void* chart);
    short (*getXValue)(void* chart, short index);
    short (*getYValue)(void* chart, short index);
    short (*getYBottomValue)(void* chart, short index);
    short (*fmtXAxis)(void* chart, short value, char* axis);
    short (*fmtYAxis)(void* chart, short value, char* axis);

}gui_chart_struct;

//controller: switch
typedef struct
{
    GUI_DRAW_HEADER;
    unsigned short  init_status;        // 0: off; 1: on
    unsigned short  frame_num;          // 2, 3, 4, 5
    const picture_info_struct* frame_pics[5];  // [off-frame : xxx  : on-frame]
}gui_switch_struct;


#endif

