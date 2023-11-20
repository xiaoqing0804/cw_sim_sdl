#ifndef __GUI_SURFACE_LAYOUT_POSITION_TWEEN_H__
#define __GUI_SURFACE_LAYOUT_POSITION_TWEEN_H__

#include "feature_all.h"
#include "gui_core.h"
#include "system_util_tween.h"

#define LAYOUT_TWEEN_TIME_DURATION (120)

typedef struct _gui_layout_position_tween_struct gui_layout_position_tween_struct;
struct _gui_layout_position_tween_struct
{
    short start_x;
    short end_x;

    short start_y;
    short end_y;

    short min_x; // 需要外部配置
    short max_x; // 需要外部配置

    short min_y; // 需要外部配置
    short max_y; // 需要外部配置

    short move_x; // 需要外部配置
    short move_y; // 需要外部配置

    short speed_x; // 需要外部配置
    short speed_y; // 需要外部配置

    short curr_x;
    short curr_y;

    short duration;
    unsigned char mode; // 需要外部配置 // TWEEN_TYPE

    unsigned char status : 2;           // 0停止,1启动,2暂停
    unsigned char orientation : 3;      // 0空，1横向 2纵向  ORIENTATION_TYPE
    unsigned char loop : 1;             // 循环，不需要回弹
    unsigned char over_screen_size : 1; // 整个列表在屏幕内

    unsigned int start_time_ms;
    unsigned int time_id;
    gui_surface_struct *surface;

    void (*scroll_step)(gui_layout_position_tween_struct *tween);   // 需要外部配置
    void (*scroll_finish)(gui_layout_position_tween_struct *tween); // 需要外部配置
};

/***********************************************数据接口*************************************************************/
extern gui_layout_position_tween_struct *gui_surface_layout_tween_position_get_tween(void);
extern float gui_surface_layout_tween_position_get_tween_progress(void);
extern unsigned char gui_surface_layout_tween_position_is_running(void);
extern unsigned char gui_surface_layout_tween_position_is_pause(void);
extern short gui_surface_layout_tween_position_get_speed(short speed);
extern short gui_surface_layout_tween_position_calculate_speed(short speed);
extern short gui_surface_layout_tween_position_calculate_duration(short offset, short speed);
extern short gui_surface_layout_tween_position_get_distance(short speed);

/***********************************************操作接口*************************************************************/
extern void gui_surface_layout_tween_position_clear(void);
extern gui_layout_position_tween_struct *gui_surface_layout_tween_position_init(gui_surface_struct *surface);
extern void gui_surface_layout_tween_position_start(gui_surface_struct *surface);
extern void gui_surface_layout_tween_position_move(gui_surface_struct *surface);
extern void gui_surface_layout_tween_position_pause();
extern void gui_surface_layout_tween_position_stop(void);

#endif
