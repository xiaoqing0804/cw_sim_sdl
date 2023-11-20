#ifndef __APP_WINDOW_MORE_INFO_KALEIDOSCOPE_H__
#define __APP_WINDOW_MORE_INFO_KALEIDOSCOPE_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"
#include "app_window_moreinfo_kaleidoscope_layout.h"

//一个泡，从中心冒出，到屏幕外结束
typedef struct
{
    gui_kaleidoscope_app_struct *app;
    gui_box_struct *box;
    float scale;  //屏幕中心到屏幕外的比例，比例决定位置和泡的半径
    short status; //0在圆心位置  1、2 在中间显示 3出屏幕 0回到圆心
} gui_kaleidoscope_item_struct;


//每一条射线包含2个泡，2个泡之间间隔1个状态
typedef struct
{
    gui_kaleidoscope_item_struct items[2];
} gui_kaleidoscope_ray_struct;

extern const gui_window_struct app_window_moreinfo_kaleidoscope;

#endif
