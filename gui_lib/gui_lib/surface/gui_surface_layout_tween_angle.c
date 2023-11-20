#include "gui_surface_layout_tween_angle.h"
#include "gui_surface_layout.h"
#include "system_util_tween.h"
#include "system_util_math.h"
#include "debug_info.h"

#define LAYOUT_TWEEN_ANGLE_A (-1600.0f)
#define LAYOUT_TWEEN_ANGLE_MAX_SPEED (1600.0f)

#define LAYOUT_TWEEN_ANGLE_MIN_DURATION (20)
#define LAYOUT_TWEEN_ANGLE_MAX_DURATION (1000)
#define LAYOUT_TWEEN_ANGLE_TIMER_INTERVAL (30)

static gui_layout_tween_angle_struct g_gui_layout_tween_angle;

static void gui_surface_layout_tween_angle_timer(unsigned int timer, void *param);

static void gui_surface_layout_tween_angle_stop_timer()
{
    if (g_gui_layout_tween_angle.time_id > 0)
    {
        application_stop_user_timer(g_gui_layout_tween_angle.time_id);
        g_gui_layout_tween_angle.time_id = 0;
    }
}

static void gui_surface_layout_tween_angle_update(gui_screen_struct *screen)
{
    gui_surface_struct *surface = g_gui_layout_tween_angle.surface;
    if (surface != NULL && screen == surface->screen)
    {
        unsigned int duration_ms = time_get_ms_duration_with_curr(g_gui_layout_tween_angle.start_time_ms);
        if (duration_ms > g_gui_layout_tween_angle.duration)
        {
            duration_ms = g_gui_layout_tween_angle.duration;
        }

        // 时间到了
        if (duration_ms >= g_gui_layout_tween_angle.duration)
        {
            g_gui_layout_tween_angle.curr_angle = g_gui_layout_tween_angle.end_angle;
            if (g_gui_layout_tween_angle.scroll_step != NULL)
            {
                g_gui_layout_tween_angle.scroll_step(&g_gui_layout_tween_angle);
            }
            if (g_gui_layout_tween_angle.scroll_finish != NULL)
            {
                g_gui_layout_tween_angle.scroll_finish(&g_gui_layout_tween_angle);
                gui_surface_layout_tween_angle_clear();
            }
        }
        else if (g_gui_layout_tween_angle.scroll_step != NULL)
        {
            float change_angle = g_gui_layout_tween_angle.end_angle - g_gui_layout_tween_angle.start_angle;
            float offset_angle = 0;

            if (g_gui_layout_tween_angle.mode == TWEEN_TYPE_LINEAR)
            {
                offset_angle = tween_linear_ease_in(duration_ms, g_gui_layout_tween_angle.start_angle, change_angle, g_gui_layout_tween_angle.duration);
            }
            else if (g_gui_layout_tween_angle.mode == TWEEN_TYPE_CIRCULAR_OUT)
            {
                offset_angle = tween_circ_ease_out(duration_ms, g_gui_layout_tween_angle.start_angle, change_angle, g_gui_layout_tween_angle.duration);
            }
            else if (g_gui_layout_tween_angle.mode == TWEEN_TYPE_SIN_IN_OUT) {
                offset_angle = tween_sine_ease_in_out(duration_ms, g_gui_layout_tween_angle.start_angle, change_angle, g_gui_layout_tween_angle.duration);
            }

            g_gui_layout_tween_angle.curr_angle = offset_angle;
            if (g_gui_layout_tween_angle.scroll_step != NULL)
            {
                g_gui_layout_tween_angle.scroll_step(&g_gui_layout_tween_angle);
            }
            g_gui_layout_tween_angle.status = 1;
            g_gui_layout_tween_angle.time_id = application_start_user_timer(LAYOUT_TWEEN_ANGLE_TIMER_INTERVAL, gui_surface_layout_tween_angle_timer, screen);
        }
    }
}

// 检测超出时的效果
static void gui_surface_layout_tween_angle_check_data(gui_surface_struct *surface)
{
    short duration = 0;
    g_gui_layout_tween_angle.start_angle = g_gui_layout_tween_angle.curr_angle;
    g_gui_layout_tween_angle.end_angle += g_gui_layout_tween_angle.move_angle;
    g_gui_layout_tween_angle.start_time_ms = time_get_ms_curr_timestamp();

    float offset_angle = g_gui_layout_tween_angle.move_angle;
    float speed = gui_surface_layout_tween_angle_get_speed(g_gui_layout_tween_angle.speed_angle);
    if(speed!=0){           //除0会死机
        duration = ABS((float)2.0f * offset_angle / speed) * 1000;
    }
    g_gui_layout_tween_angle.duration = math_range(duration, LAYOUT_TWEEN_ANGLE_MIN_DURATION, LAYOUT_TWEEN_ANGLE_MAX_DURATION);
}

static void gui_surface_layout_tween_angle_timer(unsigned int timer, void *param)
{
    gui_surface_layout_tween_angle_stop_timer();

    gui_screen_struct *screen = (gui_screen_struct *)param;
    gui_surface_layout_tween_angle_update(screen);
}

/***********************************************数据接口*************************************************************/

gui_layout_tween_angle_struct *gui_surface_layout_tween_angle_get_tween()
{
    return &g_gui_layout_tween_angle;
}

float gui_surface_layout_tween_angle_get_tween_progress()
{
    unsigned int duration_ms = time_get_ms_duration_with_curr(g_gui_layout_tween_angle.start_time_ms);
    return (float)duration_ms / g_gui_layout_tween_angle.duration;
}

unsigned char gui_surface_layout_tween_angle_is_running()
{
    return g_gui_layout_tween_angle.status == 1;
}

unsigned char gui_surface_layout_tween_angle_is_pause()
{
    return g_gui_layout_tween_angle.status == 2;
}

unsigned char gui_surface_layout_tween_angle_is_stop()
{
    return g_gui_layout_tween_angle.status == 0;
}

float gui_surface_layout_tween_angle_get_speed(float speed)
{
    return math_range_float(speed, -LAYOUT_TWEEN_ANGLE_MAX_SPEED, LAYOUT_TWEEN_ANGLE_MAX_SPEED);
}

float gui_surface_layout_tween_angle_calculate_speed(float angle)
{
    return angle * 10.0f; //( / 0.1f);
}

/***********************************************操作接口*************************************************************/

void gui_surface_layout_tween_angle_clear()
{
    gui_surface_layout_tween_angle_stop_timer();
    memset(&g_gui_layout_tween_angle, 0, sizeof(gui_layout_tween_angle_struct));
}

gui_layout_tween_angle_struct *gui_surface_layout_tween_angle_init(gui_surface_struct *surface, float start_angle)
{
    gui_surface_layout_tween_angle_clear();
    g_gui_layout_tween_angle.surface = surface;
    g_gui_layout_tween_angle.curr_angle = start_angle;
    g_gui_layout_tween_angle.start_angle = start_angle;
    g_gui_layout_tween_angle.end_angle = start_angle;
    g_gui_layout_tween_angle.start_time_ms = time_get_ms_curr_timestamp();
    return &g_gui_layout_tween_angle;
}

void gui_surface_layout_tween_angle_start(gui_surface_struct *surface, float start_angle)
{
    gui_surface_layout_tween_angle_check_data(surface);
    gui_surface_layout_tween_angle_update(surface->screen);
}

void gui_surface_layout_tween_angle_move(gui_surface_struct *surface, float start_angle)
{
    gui_surface_layout_tween_angle_check_data(surface);
}

void gui_surface_layout_tween_angle_pause()
{
    if (gui_surface_layout_tween_angle_is_running())
    {
        gui_surface_layout_tween_angle_clear();
        g_gui_layout_tween_angle.status = 2;
    }
}

void gui_surface_layout_tween_angle_stop()
{
    gui_surface_layout_tween_angle_stop_timer();

    if (gui_surface_layout_tween_angle_is_running() || gui_surface_layout_tween_angle_is_pause())
    {
        if (g_gui_layout_tween_angle.scroll_cancel != NULL)
        {
            g_gui_layout_tween_angle.scroll_cancel(&g_gui_layout_tween_angle);
        }
        gui_surface_layout_tween_angle_clear();
    }
}
