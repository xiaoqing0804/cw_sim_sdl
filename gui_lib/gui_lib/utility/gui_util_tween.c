#include "gui_util_tween.h"
#include "gui_surface_layout.h"
#include "system_util_tween.h"
#include "system_util_math.h"
#include "debug_info.h"

#define UTIL_TWEEN_MIN_SPEED (800.0f)
#define UTIL_TWEEN_MAX_SPEED (1600.0f)

#define UTIL_TWEEN_MIN_DURATION (20)
#define UTIL_TWEEN_MAX_DURATION (1000)
#define UTIL_TWEEN_TIMER_INTERVAL (30)

static gui_util_tween_struct g_gui_util_tween;

static void gui_util_tween_timer(unsigned int timer, void *param);

static void gui_util_tween_stop_timer()
{
    if (g_gui_util_tween.time_id > 0)
    {
        application_stop_user_timer(g_gui_util_tween.time_id);
        g_gui_util_tween.time_id = 0;
    }
}

static void gui_util_tween_update()
{
    unsigned int duration_ms = time_get_ms_duration_with_curr(g_gui_util_tween.start_time_ms);
    if (duration_ms > g_gui_util_tween.duration)
    {
        duration_ms = g_gui_util_tween.duration;
    }

    // 时间到了
    if (duration_ms >= g_gui_util_tween.duration)
    {
        for (short i = 0; i < UTIL_TWEEN_VALUE_TOTAL; i++)
        {
            g_gui_util_tween.curr_value[i] = g_gui_util_tween.end_value[i];
        }

        if (g_gui_util_tween.step != NULL)
        {
            g_gui_util_tween.step(&g_gui_util_tween);
        }

        gui_util_tween_stop_timer();
        g_gui_util_tween.status = 0;

        if (g_gui_util_tween.finish != NULL)
        {
            g_gui_util_tween.finish(&g_gui_util_tween);
        }
    }
    else if (g_gui_util_tween.step != NULL)
    {
        TWEEN_TYPE type = (TWEEN_TYPE)g_gui_util_tween.mode;

        for (short i = 0; i < UTIL_TWEEN_VALUE_TOTAL; i++)
        {
            float change_value = g_gui_util_tween.end_value[i] - g_gui_util_tween.start_value[i];
            if (!FLOAT_EQUAL_ZERO(change_value))
            {
                g_gui_util_tween.curr_value[i] = tween_ease(type, duration_ms, g_gui_util_tween.start_value[i], change_value, g_gui_util_tween.duration);
            }
            else
            {
                g_gui_util_tween.curr_value[i] = g_gui_util_tween.start_value[i];
            }
        }

        if (g_gui_util_tween.step != NULL)
        {
            g_gui_util_tween.step(&g_gui_util_tween);
        }
        g_gui_util_tween.status = 1;
        g_gui_util_tween.time_id = application_start_user_timer(UTIL_TWEEN_TIMER_INTERVAL, gui_util_tween_timer, NULL);
    }
}

// 检测超出时的效果
static void gui_util_tween_check_data()
{
    for (short i = 0; i < UTIL_TWEEN_VALUE_TOTAL; i++)
    {
        if (gui_util_tween_is_stop())
        {
            g_gui_util_tween.curr_value[i] = g_gui_util_tween.start_value[i];
        }
        else
        {
            g_gui_util_tween.start_value[i] = g_gui_util_tween.curr_value[i];
        }
        g_gui_util_tween.end_value[i] = g_gui_util_tween.start_value[i] + g_gui_util_tween.change_value[i];
    }

    g_gui_util_tween.start_time_ms = time_get_ms_curr_timestamp();
    g_gui_util_tween.duration = math_range(g_gui_util_tween.duration, UTIL_TWEEN_MIN_DURATION, UTIL_TWEEN_MAX_DURATION);
}

static void gui_util_tween_timer(unsigned int timer, void *param)
{
    gui_util_tween_stop_timer();
    gui_util_tween_update();
}

/***********************************************数据接口*************************************************************/

gui_util_tween_struct *gui_util_tween_get_tween()
{
    return &g_gui_util_tween;
}

float gui_util_tween_get_tween_progress()
{
    unsigned int duration_ms = time_get_ms_duration_with_curr(g_gui_util_tween.start_time_ms);
    return (float)duration_ms / g_gui_util_tween.duration;
}

unsigned char gui_util_tween_is_running()
{
    return g_gui_util_tween.status == 1;
}

unsigned char gui_util_tween_is_pause()
{
    return g_gui_util_tween.status == 2;
}

unsigned char gui_util_tween_is_stop()
{
    return g_gui_util_tween.status == 0;
}

float gui_util_tween_get_speed(float speed)
{
    return math_range_float(speed, UTIL_TWEEN_MIN_SPEED, UTIL_TWEEN_MAX_SPEED);
}

float gui_util_tween_calculate_speed(float speed)
{
    return speed * 10.0f; //( / 0.1f);
}

/***********************************************操作接口*************************************************************/

void gui_util_tween_clear()
{
    gui_util_tween_stop_timer();
    memset(&g_gui_util_tween, 0, sizeof(gui_util_tween_struct));
}

/// @brief 第一次使用时
/// @param id 标识，比如转场了，对比标识就知道不是同一个
/// @return
gui_util_tween_struct *gui_util_tween_init(unsigned int id)
{
    gui_util_tween_clear();
    g_gui_util_tween.id = id;
    g_gui_util_tween.start_time_ms = time_get_ms_curr_timestamp();
    return &g_gui_util_tween;
}

void gui_util_tween_start()
{
    gui_util_tween_check_data();
    gui_util_tween_update();
}

/// @brief 正在运动时，再次执行
void gui_util_tween_move()
{
    gui_util_tween_check_data();
}

void gui_util_tween_pause()
{
    if (gui_util_tween_is_running())
    {
        gui_util_tween_clear();
        g_gui_util_tween.status = 2;
    }
}

void gui_util_tween_stop()
{
    gui_util_tween_stop_timer();

    if (gui_util_tween_is_running() || gui_util_tween_is_pause())
    {
        if (g_gui_util_tween.cancel != NULL)
        {
            g_gui_util_tween.cancel(&g_gui_util_tween);
        }
        gui_util_tween_clear();
    }
}
