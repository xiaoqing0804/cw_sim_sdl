/*****************************************
 *
 * 只考虑了X方向，Y方向的单独运动
 *
 * ***************************************/
#include "gui_surface_layout_tween_position.h"
#include "gui_surface_layout.h"
#include "system_util_tween.h"
#include "system_util_math.h"
#include "debug_info.h"

#define LAYOUT_TWEEN_POSITION_A (-1600.0f) // 加速度a

#define LAYOUT_TWEEN_POSITION_MAX_SPEED (1600.0f)

#define LAYOUT_TWEEN_POSITION_REBOUND_DURATION (120)
#define LAYOUT_TWEEN_POSITION_MIN_DURATION (20)
#define LAYOUT_TWEEN_POSITION_MAX_DURATION (1000)
#define LAYOUT_TWEEN_POSITION_TIMER_INTERVAL (30)

#define LAYOUT_TWEEN_POSITION_REBOUND_OFFSET (30)

static gui_layout_position_tween_struct g_gui_layout_position_tween;

static void gui_surface_layout_tween_position_timer(unsigned int timer, void *param);

/************************************************回弹检测***********************************************************/

static short gui_surface_layout_tween_position_get_near_x(gui_layout_position_tween_struct *tween)
{
    if (!tween->over_screen_size) // 整个列表在屏幕内
        return tween->min_x;

    if (tween->curr_x < tween->min_x)
        return tween->min_x;

    if (tween->curr_x > tween->max_x)
        return tween->max_x;

    return tween->curr_x;
}

static short gui_surface_layout_tween_position_get_near_y(gui_layout_position_tween_struct *tween)
{
    if (!tween->over_screen_size) // 整个列表在屏幕内
        return tween->min_y;

    if (tween->curr_y < tween->min_y)
        return tween->min_y;

    if (tween->curr_y > tween->max_y)
        return tween->max_y;

    return tween->curr_y;
}

// 超出范围，需要回弹
static unsigned char gui_surface_layout_tween_position_is_over(gui_layout_position_tween_struct *tween, short curr_x, short curr_y)
{
    if (!tween->over_screen_size) // 整个列表在屏幕内
        return (curr_y != tween->min_y || curr_x != tween->min_x);

    if (curr_y < tween->min_y || curr_y > tween->max_y)
        return 1;

    if (curr_x < tween->min_x || curr_x > tween->max_x)
        return 1;

    return 0;
}

static unsigned char gui_surface_layout_tween_position_curr_is_over(gui_layout_position_tween_struct *tween)
{
    return gui_surface_layout_tween_position_is_over(tween, tween->curr_x, tween->curr_y);
}

// 检查是否超出范围，是否需要回弹
static void gui_surface_layout_tween_position_check_rebound(gui_screen_struct *screen, gui_layout_position_tween_struct *tween)
{
    // 超出范围，需要回弹
    if (gui_surface_layout_tween_position_curr_is_over(tween) && tween->loop == 0)
    {
        SYS_DEBUG("gui_surface_layout_tween_position_curr_is_over");

        tween->start_x = tween->curr_x;
        tween->start_y = tween->curr_y;
        tween->end_x = gui_surface_layout_tween_position_get_near_x(tween);
        tween->end_y = gui_surface_layout_tween_position_get_near_y(tween);
        tween->duration = LAYOUT_TWEEN_POSITION_REBOUND_DURATION;
        tween->start_time_ms = time_get_ms_curr_timestamp();
        tween->status = 1;
        tween->time_id = application_start_user_timer(LAYOUT_TWEEN_POSITION_TIMER_INTERVAL, gui_surface_layout_tween_position_timer, screen);
    }
    else if (tween->scroll_finish != NULL)
    {
        SYS_DEBUG("scroll_finish");
        tween->scroll_finish(tween);
        gui_surface_layout_tween_position_clear();
    }
}

/************************************************数值校正***********************************************************/

// 对Y的结束点进行检查，调整
static void gui_surface_layout_tween_position_check_data_y(gui_layout_position_tween_struct *tween)
{
    if (tween->over_screen_size)
    {
        if (tween->end_y < (tween->min_y - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
        {
            if (tween->start_y <= (tween->min_y - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
                tween->end_y = tween->start_y;
            else
                tween->end_y = tween->min_y - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET;
        }
        else if (tween->end_y > (tween->max_y + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
        {
            if (tween->start_y >= (tween->max_y + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
                tween->end_y = tween->start_y;
            else
                tween->end_y = tween->max_y + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET;
        }
    }
    else
    {
        if (tween->end_y < (tween->min_y - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
        {
            if (tween->start_y <= (tween->min_y - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
                tween->end_y = tween->start_y;
            else
                tween->end_y = tween->min_y - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET;
        }
        else if (tween->end_y > (tween->min_y + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
        {
            if (tween->start_y >= (tween->min_y - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
                tween->end_y = tween->start_y;
            else
                tween->end_y = tween->min_y + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET;
        }
    }
}

// 对X的结束点进行检查，调整
static void gui_surface_layout_tween_position_check_data_x(gui_layout_position_tween_struct *tween)
{
    if (tween->over_screen_size)
    {
        if (tween->end_x < (tween->min_x - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
        {
            if (tween->start_x <= (tween->min_x - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
                tween->end_x = tween->start_x;
            else
                tween->end_x = tween->min_x - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET;
        }
        else if (tween->end_x > (tween->max_x + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
        {
            if (tween->start_x >= (tween->max_x + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
                tween->end_x = tween->start_x;
            else
                tween->end_x = tween->max_x + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET;
        }
    }
    else
    {
        if (tween->end_x < (tween->min_x - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
        {
            if (tween->start_x <= (tween->min_x - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
                tween->end_x = tween->start_x;
            else
                tween->end_x = tween->min_x - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET;
        }
        else if (tween->end_x > (tween->min_x + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
        {
            if (tween->start_x >= (tween->min_x - LAYOUT_TWEEN_POSITION_REBOUND_OFFSET))
                tween->end_x = tween->start_x;
            else
                tween->end_x = tween->min_x + LAYOUT_TWEEN_POSITION_REBOUND_OFFSET;
        }
    }
}

// 对结束点的数值检测
static void gui_surface_layout_tween_position_check_data(gui_surface_struct *surface, gui_layout_position_tween_struct *tween)
{
    gui_layout_header_struct *layout_header = &surface->layout.header;
    tween->start_y = layout_header->offset_y;
    tween->start_x = layout_header->offset_x;

    unsigned char is_move_y = tween->speed_y == 0 || tween->move_y == 0;
    unsigned char is_move_x = tween->speed_x == 0 || tween->move_x == 0;

    if (is_move_y && is_move_x) // 在原地没有移动，停一帧后再反应，检测是否在正确位置
    {
        tween->end_x = tween->start_x;
        tween->end_y = tween->start_y;
        tween->duration = LAYOUT_TWEEN_POSITION_MIN_DURATION;
    }
    else if (is_move_y) // Y在原地没有移动，那么X肯定动了
    {
        tween->end_x += tween->move_x;

        short offset_x = tween->move_x;
        if (tween->loop == 0) // 回弹
        {
            gui_surface_layout_tween_position_check_data_x(tween);
            offset_x = tween->end_x - tween->start_x;
        }
        short speed = gui_surface_layout_tween_position_get_speed(tween->speed_x);
        short duration = gui_surface_layout_tween_position_calculate_duration(offset_x, speed);
        tween->duration = math_range(duration, LAYOUT_TWEEN_POSITION_MIN_DURATION, LAYOUT_TWEEN_POSITION_MAX_DURATION);
    }
    else
    {
        tween->end_y += tween->move_y;
        short offset_y = tween->move_y;
        if (tween->loop == 0) // 回弹
        {
            gui_surface_layout_tween_position_check_data_y(tween);
            offset_y = tween->end_y - tween->start_y;
        }
        short speed = gui_surface_layout_tween_position_get_speed(tween->speed_y);
        short duration = gui_surface_layout_tween_position_calculate_duration(offset_y, speed);
        tween->duration = math_range(duration, LAYOUT_TWEEN_POSITION_MIN_DURATION, LAYOUT_TWEEN_POSITION_MAX_DURATION);
    }
    tween->start_time_ms = time_get_ms_curr_timestamp();
}

/************************************************执行***********************************************************/

static void gui_surface_layout_tween_position_update(gui_screen_struct *screen, gui_layout_position_tween_struct *tween)
{
    //SYS_DEBUG("gui_surface_layout_tween_position_update start");

    gui_surface_struct *surface = tween->surface;
    if (surface != NULL && screen == surface->screen)
    {
        unsigned int duration_ms = time_get_ms_duration_with_curr(tween->start_time_ms);
        if (duration_ms > tween->duration)
        {
            duration_ms = tween->duration;
        }

        // 时间到了
        if (duration_ms >= tween->duration)
        {
            tween->curr_x = tween->end_x;
            tween->curr_y = tween->end_y;

            if (tween->scroll_step != NULL)
            {
                tween->scroll_step(tween);
            }
            gui_surface_layout_tween_position_check_rebound(screen, tween);
        }
        else if (tween->scroll_step != NULL)
        {
            short change_x = tween->end_x - tween->start_x;
            short change_y = tween->end_y - tween->start_y;
            short offset_x = tween->start_x;
            short offset_y = tween->start_y;

            switch (tween->mode)
            {
            case TWEEN_TYPE_QUADRATIC_OUT:
                if (change_x != 0)
                    offset_x = tween_quad_ease_out(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_quad_ease_out(duration_ms, tween->start_y, change_y, tween->duration);
                break;

            case TWEEN_TYPE_CUBIC_OUT:
                if (change_x != 0)
                    offset_x = tween_cubic_ease_out(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_cubic_ease_out(duration_ms, tween->start_y, change_y, tween->duration);
                break;

            case TWEEN_TYPE_QUARTIC_OUT:
                if (change_x != 0)
                    offset_x = tween_quart_ease_out(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_quart_ease_out(duration_ms, tween->start_y, change_y, tween->duration);
                break;

            case TWEEN_TYPE_QUINTIC_OUT:
                if (change_x != 0)
                    offset_x = tween_quint_ease_out(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_quint_ease_out(duration_ms, tween->start_y, change_y, tween->duration);
                break;

            case TWEEN_TYPE_SIN_OUT:
                if (change_x != 0)
                    offset_x = tween_sine_ease_out(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_sine_ease_out(duration_ms, tween->start_y, change_y, tween->duration);
                break;

            case TWEEN_TYPE_E_OUT:
                if (change_x != 0)
                    offset_x = tween_expo_ease_out(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_expo_ease_out(duration_ms, tween->start_y, change_y, tween->duration);
                break;

            case TWEEN_TYPE_CIRCULAR_OUT:
                if (change_x != 0)
                    offset_x = tween_circ_ease_out(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_circ_ease_out(duration_ms, tween->start_y, change_y, tween->duration);
                break;

            case TWEEN_TYPE_BOUNCE_OUT:
                if (change_x != 0)
                    offset_x = tween_bounce_ease_out(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_bounce_ease_out(duration_ms, tween->start_y, change_y, tween->duration);
                break;

            default:
                if (change_x != 0)
                    offset_x = tween_linear_ease_in(duration_ms, tween->start_x, change_x, tween->duration);
                if (change_y != 0)
                    offset_y = tween_linear_ease_in(duration_ms, tween->start_y, change_y, tween->duration);
                break;
            }

            tween->curr_x = offset_x;
            tween->curr_y = offset_y;
            if (tween->scroll_step != NULL)
            {
                tween->scroll_step(tween);
            }
            tween->status = 1;
            tween->time_id = application_start_user_timer(LAYOUT_TWEEN_POSITION_TIMER_INTERVAL, gui_surface_layout_tween_position_timer, screen);
        }
    }
    //SYS_DEBUG("gui_surface_layout_tween_position_update end");
}

static void gui_surface_layout_tween_position_stop_timer(gui_layout_position_tween_struct *tween)
{
    if (tween->time_id > 0)
    {
        application_stop_user_timer(tween->time_id);
        tween->time_id = 0;
    }
}

static void gui_surface_layout_tween_position_timer(unsigned int timer, void *param)
{
    SYS_DEBUG("gui_surface_layout_tween_position_timer");

    gui_surface_layout_tween_position_stop_timer(&g_gui_layout_position_tween);

    gui_screen_struct *screen = (gui_screen_struct *)param;
    gui_surface_layout_tween_position_update(screen, &g_gui_layout_position_tween);
}

/***********************************************数据接口*************************************************************/

gui_layout_position_tween_struct *gui_surface_layout_tween_position_get_tween()
{
    return &g_gui_layout_position_tween;
}

float gui_surface_layout_tween_position_get_tween_progress()
{
    unsigned int duration_ms = time_get_ms_duration_with_curr(g_gui_layout_position_tween.start_time_ms);
    return (float)duration_ms / g_gui_layout_position_tween.duration;
}

unsigned char gui_surface_layout_tween_position_is_running()
{
    return g_gui_layout_position_tween.status == 1;
}

unsigned char gui_surface_layout_tween_position_is_pause()
{
    return g_gui_layout_position_tween.status == 2;
}

unsigned char gui_surface_layout_tween_position_is_stop()
{
    return g_gui_layout_position_tween.status == 0;
}

short gui_surface_layout_tween_position_get_speed(short speed)
{
    return math_range(speed, -LAYOUT_TWEEN_POSITION_MAX_SPEED, LAYOUT_TWEEN_POSITION_MAX_SPEED);
}

short gui_surface_layout_tween_position_calculate_speed(short speed)
{
    return speed * 10; //( / 0.1f);
}

short gui_surface_layout_tween_position_calculate_duration(short offset, short speed)
{
    return ABS((float)offset / speed) * 1000;
}

short gui_surface_layout_tween_position_get_distance(short speed)
{
    speed = gui_surface_layout_tween_position_get_speed(speed);
    float time_second = ABS(speed / LAYOUT_TWEEN_POSITION_A);
    return (short)(speed * time_second - LAYOUT_TWEEN_POSITION_A * time_second * time_second / 2);
}

/***********************************************操作接口*************************************************************/

void gui_surface_layout_tween_position_clear()
{
    gui_surface_layout_tween_position_stop_timer(&g_gui_layout_position_tween);
    memset(&g_gui_layout_position_tween, 0, sizeof(gui_layout_position_tween_struct));
}

gui_layout_position_tween_struct *gui_surface_layout_tween_position_init(gui_surface_struct *surface)
{
    gui_surface_layout_tween_position_clear();

    g_gui_layout_position_tween.surface = surface;
    g_gui_layout_position_tween.start_time_ms = time_get_ms_curr_timestamp();

    gui_layout_header_struct *layout_header = &surface->layout.header;
    g_gui_layout_position_tween.start_x = layout_header->offset_x;
    g_gui_layout_position_tween.start_y = layout_header->offset_y;
    g_gui_layout_position_tween.end_x = layout_header->offset_x;
    g_gui_layout_position_tween.end_y = layout_header->offset_y;

    return &g_gui_layout_position_tween;
}

void gui_surface_layout_tween_position_start(gui_surface_struct *surface)
{
    SYS_DEBUG("gui_surface_layout_tween_position_start");

    short offset_x = g_gui_layout_position_tween.max_y - g_gui_layout_position_tween.min_y;
    short offset_y = g_gui_layout_position_tween.max_x - g_gui_layout_position_tween.min_x;
    g_gui_layout_position_tween.over_screen_size =  (ABS(offset_x) > 0 || ABS(offset_y) > 0);//当最大点和最小点重合时，就是在屏幕内部

    gui_surface_layout_tween_position_check_data(surface, &g_gui_layout_position_tween);
    gui_surface_layout_tween_position_update(surface->screen, &g_gui_layout_position_tween);
}

void gui_surface_layout_tween_position_move(gui_surface_struct *surface)
{
    gui_surface_layout_tween_position_check_data(surface, &g_gui_layout_position_tween);
}

void gui_surface_layout_tween_position_pause()
{
    if(gui_surface_layout_tween_position_is_running())
    {
        gui_surface_layout_tween_position_stop();
        g_gui_layout_position_tween.status = 2;
    }
}

void gui_surface_layout_tween_position_stop()
{
    SYS_DEBUG("gui_surface_layout_tween_position_stop");
    gui_surface_layout_tween_position_stop_timer(&g_gui_layout_position_tween);
    gui_surface_layout_tween_position_clear();
}
