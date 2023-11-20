#ifndef __GUI_UTIL_TWEEN_H__
#define __GUI_UTIL_TWEEN_H__

#include "feature_all.h"
#include "gui_core.h"
#include "system_util_tween.h"

#define UTIL_TWEEN_TIME_DURATION (120)
#define UTIL_TWEEN_VALUE_TOTAL (5)

typedef struct _gui_util_tween_struct gui_util_tween_struct;
typedef void (*tween_callback)(gui_util_tween_struct *tween);

struct _gui_util_tween_struct
{
    float start_value[UTIL_TWEEN_VALUE_TOTAL];  // 需要外部配置
    float change_value[UTIL_TWEEN_VALUE_TOTAL]; // 需要外部配置
    float end_value[UTIL_TWEEN_VALUE_TOTAL];
    float curr_value[UTIL_TWEEN_VALUE_TOTAL];

    short duration;       // 需要外部配置
    unsigned char mode;   // 需要外部配置 // TWEEN_TYPE
    unsigned char status; // 0停止,1启动,2暂停

    int tag;         // 需要外部配置，不使用可以不配置
    unsigned int id; // 标识，比如转场了，对比标识就知道不是同一个
    unsigned int start_time_ms;
    unsigned int time_id;

    tween_callback step;   // 需要外部配置
    tween_callback finish; // 需要外部配置
    tween_callback cancel  // 需要外部配置
};

/***********************************************数据接口*************************************************************/
extern gui_util_tween_struct *gui_util_tween_get_tween(void);
extern float gui_util_tween_get_tween_progress(void);
extern unsigned char gui_util_tween_is_running(void);
extern unsigned char gui_util_tween_is_pause(void);
extern unsigned char gui_util_tween_is_stop(void);
extern float gui_util_tween_get_speed(float speed);
extern float gui_util_tween_calculate_speed(float speed);

/***********************************************操作接口*************************************************************/
extern void gui_util_tween_clear(void);
extern gui_util_tween_struct *gui_util_tween_init(unsigned int tag);
extern void gui_util_tween_start();
extern void gui_util_tween_move();
extern void gui_util_tween_pause(void);
extern void gui_util_tween_stop(void);

#endif
