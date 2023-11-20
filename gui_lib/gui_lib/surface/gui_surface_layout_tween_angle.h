#ifndef __GUI_SURFACE_LAYOUT_TWEEN_ANGLE_H__
#define __GUI_SURFACE_LAYOUT_TWEEN_ANGLE_H__

#include "feature_all.h"
#include "gui_core.h"
#include "system_util_tween.h"

#define LAYOUT_TWEEN_ANGLE_TIME_DURATION (120)

typedef struct _gui_layout_tween_angle_struct gui_layout_tween_angle_struct;
struct _gui_layout_tween_angle_struct
{
    float start_angle;
    float end_angle;

    float move_angle; // 需要外部配置
    float speed_angle; // 需要外部配置

    float curr_angle;

    short duration;
    unsigned char status;      // 0停止,1启动,2暂停
    unsigned char mode;        // 需要外部配置 // TWEEN_TYPE

    unsigned int start_time_ms;
    unsigned int time_id;
    gui_surface_struct *surface;

    void (*scroll_step)(gui_layout_tween_angle_struct *tween);   // 需要外部配置
    void (*scroll_finish)(gui_layout_tween_angle_struct *tween); // 需要外部配置
    void (*scroll_cancel)(gui_layout_tween_angle_struct *tween); // 需要外部配置
};

/***********************************************数据接口*************************************************************/
extern gui_layout_tween_angle_struct *gui_surface_layout_tween_angle_get_tween(void);
extern float gui_surface_layout_tween_angle_get_tween_progress(void);
extern unsigned char gui_surface_layout_tween_angle_is_running(void);
extern unsigned char gui_surface_layout_tween_angle_is_pause(void);
extern float gui_surface_layout_tween_angle_get_speed(float speed);
extern float gui_surface_layout_tween_angle_calculate_speed(float angle);

/***********************************************操作接口*************************************************************/
extern void gui_surface_layout_tween_angle_clear(void);
extern gui_layout_tween_angle_struct *gui_surface_layout_tween_angle_init(gui_surface_struct *surface, float start_angle);
extern void gui_surface_layout_tween_angle_start(gui_surface_struct *surface, float start_angle);
extern void gui_surface_layout_tween_angle_move(gui_surface_struct *surface, float start_angle);
extern void gui_surface_layout_tween_angle_pause(void);
extern void gui_surface_layout_tween_angle_stop(void);

#endif
