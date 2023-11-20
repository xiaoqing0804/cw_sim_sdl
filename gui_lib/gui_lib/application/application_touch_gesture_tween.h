#ifndef __APPLICATION_TOUCH_GESTURE_TWEEN_H__
#define __APPLICATION_TOUCH_GESTURE_TWEEN_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef struct _gui_touch_gesture_tween_struct gui_touch_gesture_tween_struct;
struct _gui_touch_gesture_tween_struct
{
    short start_x1; // 需要外部配置
    short end_x1;   // 需要外部配置

    short start_y1; // 需要外部配置
    short end_y1;   // 需要外部配置

    short start_x2; // 需要外部配置
    short end_x2;   // 需要外部配置

    short start_y2; // 需要外部配置
    short end_y2;   // 需要外部配置

    short curr_x1;
    short curr_y1;

    short curr_x2;
    short curr_y2;

    short duration;        // 需要外部配置
    unsigned char success; // 需要外部配置  --- 手势成功就是翻到下一页，失败就是回弹
    unsigned char status;
    unsigned char direction;      		//DIRECTION_TYPE
    unsigned char swipe_type;     //WINDOW_SWIPE_TYPE

    unsigned int start_time_ms;
    unsigned int time_id;
    gui_surface_struct *surface;

    void (*scroll_step)(gui_touch_gesture_tween_struct *tween);   // 需要外部配置
    void (*scroll_finish)(gui_touch_gesture_tween_struct *tween); // 需要外部配置
};

/************************************************数值及校正***********************************************************/
extern gui_touch_gesture_tween_struct *application_touch_gesture_tween_get_tween();
extern short application_touch_gesture_tween_get_speed(short speed);
extern short application_touch_gesture_tween_calculate_duration(short distance, short speed);

/***********************************************操作接口*************************************************************/
extern void application_touch_gesture_tween_clear();
extern gui_touch_gesture_tween_struct *application_touch_gesture_tween_init(gui_surface_struct *surface);
extern void application_touch_gesture_tween_start(gui_surface_struct *surface);

#endif
