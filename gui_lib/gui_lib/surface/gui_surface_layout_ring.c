#include "system_util_math.h"
#include "gui_surface_node.h"
#include "gui_surface_layout_ring.h"
#include "gui_surface_layout_ring_config.h"
#include "gui_surface_box_scale.h"
#include "gui_window_history.h"
#include "gui_surface_layout_tween_angle.h"

#define RING_SCALE_MIN 0.2f

#define RING_ABS(x) (((x) > 0) ? (x) : (-(x))) // calculate absolute value.

static float gui_surface_layout_ring_adj_angle(float angle)
{
    while (angle >= 360.0f)
    {
        angle -= 360.0f;
    }
    while (angle < 0.0f)
    {
        angle += 360.0f;
    }
    return angle;
}

static float gui_surface_layout_ring_set_angle_int(gui_layout_ring_struct *ring, float angle)
{
    float max_ang = ring->mCount * ring->mAngGap;
    float max_ang2 = max_ang / 2.0f;

    while (angle >= max_ang2)
    {
        angle -= max_ang;
    }
    while (angle < -max_ang2)
    {
        angle += max_ang;
    }
    return angle;
}

static void gui_surface_layout_ring_set_angle(gui_layout_ring_struct *ring, float angle)
{
    ring->mAngVal = gui_surface_layout_ring_set_angle_int(ring, angle);
}

/*******************************************
**
**对ring进行排版，移动
**
********************************************/
/*
 *                      o P(x, y)
 *                     /
 *                    /
 *                   o------o p'(x0, y0)
 *                 //|     /|
 *               / / |   /  |
 *       R     /  /  | /    |
 *           /   /r  |      |
 *         /    /  / | y0   |y0
 *       /     / /   |      |
 *     /    a //     |      |
 *    O'-----O-------+------x0--->
 *        b
 */

static float gui_surface_layout_ring_get_bias_pos(gui_layout_ring_struct *ring, int32_t angle, int *out_x, int *out_y)
{
    float theta, rr, sin2, cos2, RR, bb, y0, x0;

    angle += ring->mBaseAng;
    angle = gui_surface_layout_ring_adj_angle(angle);
    theta = angle * MATH_PI / 180.0f;

    bb = ring->c_bias_x * ring->c_bias_x;
    RR = ring->mRadius * ring->mRadius;
    sin2 = sin(MATH_PI - theta);
    sin2 = sin2 * sin2;
    cos2 = 1 - sin2;
    // SYS_DEBUG("gui: ring_get_bias_pos, bb=%f, RR=%f, sin2=%f, cos2=%f", bb, RR, sin2, cos2);
    if (ring->c_bias_x < 0)
    {
        // 左疏右密 ...
        if (angle > 90 && angle < 270)
        {
            rr = RR + bb * (1 - 2 * sin2) - 2 * ring->c_bias_x * ((float)sqrt((RR - bb * sin2) * cos2));
            y0 = sqrt(rr) * sin(theta);
            if ((angle < 90 + ring->c_bias_h) || (angle > 270 - ring->c_bias_h))
            {
                x0 = sqrt(RR - y0 * y0);
            }
            else
            {
                x0 = -sqrt(RR - y0 * y0);
            }
        }
        else
        {
            rr = RR + bb * (1 - 2 * sin2) + 2 * ring->c_bias_x * ((float)sqrt((RR - bb * sin2) * cos2));
            y0 = sqrt(rr) * sin(theta);
            x0 = sqrt(RR - y0 * y0);
        }
    }
    else
    {
        // 右疏左密，???有待调试 ???
        if (angle > 90 && angle < 270)
        {
            rr = RR + bb * (1 - 2 * sin2) - 2 * ring->c_bias_x * ((float)sqrt((RR - bb * sin2) * cos2));
            y0 = sqrt(rr) * sin(theta);
            if ((angle < 90 + ring->c_bias_h) || (angle > 270 - ring->c_bias_h))
            {
                x0 = -sqrt(RR - y0 * y0);
            }
            else
            {
                x0 = sqrt(RR - y0 * y0);
            }
        }
        else
        {
            rr = RR + bb * (1 - 2 * sin2) + 2 * ring->c_bias_x * ((float)sqrt((RR - bb * sin2) * cos2));
            y0 = sqrt(rr) * sin(theta);
            x0 = +sqrt(RR - y0 * y0);
        }
    }

    *out_x = round(ring->c_x + x0);
    *out_y = round(ring->c_y - y0);
    // SYS_DEBUG("gui: ring_get_bias_pos, rr=%f, RR=%f, x0=%f, y0=%f, x=%d, y=%d", rr, RR, x0, y0, *out_x, *out_y);

    if (ring->cfg_map_size == 0)
    {                                                                                                            // 没有缩放插值表，就自己计算缩放参数...
        return (RING_SCALE_MIN + ((RING_SCALE_MIN - 1.0) * (sqrt(rr) + ring->c_bias_x) / (2 * ring->c_bias_x))); // (rr/RR);
    }
    return 1.0f;
}

static void gui_surface_layout_ring_get_pos(gui_layout_ring_struct *ring, int32_t angle, int *out_x, int *out_y)
{
    double x, y, theta;

    angle += ring->mBaseAng;
    angle = gui_surface_layout_ring_adj_angle(angle);
    theta = angle * MATH_PI / 180.0f;

    x = ring->c_x + ring->mRadius * cos(theta);
    y = ring->c_y - ring->mRadius * sin(theta);
    // SYS_DEBUG("gui_surface_layout_ring_get_pos %f,%f",x,y);
    *out_x = round(x);
    *out_y = round(y);
}

static float gui_surface_layout_ring_get_item_xy(gui_layout_ring_struct *ring, float angle, int *x0, int *y0)
{
    float zoom = 1.0f;
    if ((ring->mZoom) && (ring->c_bias_x != 0))
    {
        zoom = gui_surface_layout_ring_get_bias_pos(ring, (int)angle, x0, y0);
    }
    else
    {
        gui_surface_layout_ring_get_pos(ring, (int)angle, x0, y0);
    }
    if (ring->cfg_map_size != 0)
    {
        float x = (float)(*x0);
        zoom = lg3_interpolation(ring->cfg_pos_map, ring->cfg_zoom_map, ring->cfg_map_size, x);
    }
    return zoom;
}
static void gui_surface_layout_ring_update_item(gui_surface_struct *surface, gui_box_struct *box, int x0, int y0, float zoom)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    const picture_info_struct **picture_arr = (const picture_info_struct **)box->widget->children;
    const picture_info_struct *picture = (const picture_info_struct *)picture_arr[0];

    box->x = x0;
    box->y = y0;
    box->width = picture->width;
    box->height = picture->height;
    box->child->width = picture->width;
    box->child->height = picture->height;
    if ((ring->mZoom)) //&& (ring->c_bias_x != 0)
    {
        box->scale = 1.0f;
        box->child->scale = 1.0f;
#if defined(__CW_JL__)
        box->scale = zoom;
#else
        // find pic
        unsigned int i = 0, iw = picture->width * zoom;
        while ((iw < picture->width) && (i < box->widget->child_num))
        {
            i++;
            picture = (const picture_info_struct *)picture_arr[i];
        }
#endif
    }
}

static void gui_surface_layout_ring_reflash_items(gui_surface_struct *surface)
{
    gui_box_struct *box = surface->child;
    gui_layout_ring_struct *ring = &surface->layout.ring;

    int x0, y0;

    float angle = ring->mAngVal;
    float zoom = 1.0f;
    float disp_angle;

    SYS_DEBUG("gui: ring_reflash_items, angle=%f, gap=%f ------------", angle, ring->mAngGap);
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
        {
            if (ring->auto_start)
            {
                disp_angle = angle;
            }
            else
            {
                disp_angle = gui_surface_layout_ring_set_angle_int(ring, angle);
            }
            // SYS_DEBUG("gui: ring_reflash_items[%d], angle=%f", box->layout_index, disp_angle);
            if ((disp_angle >= -180.0f) && (disp_angle <= 180.0f))
            {
                zoom = gui_surface_layout_ring_get_item_xy(ring, disp_angle, &x0, &y0);
                gui_surface_layout_ring_update_item(surface, box, x0, y0, zoom);
                box->visible = 1;
            }
            else
            {
                box->visible = 0;
            }
            angle += ring->mAngGap;
        }
        box = box->brother;
    }
}

static int gui_surface_layout_ring_get_count(gui_surface_struct *surface)
{
    int count = 0;
    gui_box_struct *box = surface->child;
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
        {
            box->layout_index = count; // index
            count++;
        }
        box = box->brother;
    }
    // SYS_DEBUG("gui: ring_get_count, =%d", count);
    return count;
}

static void gui_surface_layout_ring_commit_position(gui_surface_struct *surface)
{
    gui_surface_layout_ring_reflash_items(surface);
}

// 获取当前焦点项的索引..
static int gui_surface_layout_ring_update_current_index(gui_surface_struct *surface)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    int32_t count = ring->mCount;
    int32_t idx = 0;

    if (count != 0)
    {
        float fidx = 0.0f;
        float ang = ring->mAngVal;

        if (ang >= 0.0f)
        {
            fidx = ((ang + ring->mAngGap / 2.0f) / ring->mAngGap);
        }
        else
        {
            fidx = ((ang - ring->mAngGap / 2.0f) / ring->mAngGap);
        }
        idx = (int)fidx;
        idx = count - idx;
        if (idx >= count)
        {
            idx -= count;
        }
        else if (idx < 0)
        {
            idx += count;
        }
        ring->mIndex = idx;
    }

    return idx;
}

static void gui_surface_layout_ring_report_changed(gui_surface_struct *surface)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    const gui_window_struct *top_window = gui_window_history_get_top_window();
    if (top_window != NULL)
    {
        if (ring->auto_start)
            return; // 正在load-enter时，不上报焦点的改变.

        if (top_window->layout_value_changed)
        {
            gui_box_struct *box = gui_surface_layout_ring_get_current_item(surface);
            gui_layout_value_struct event =
                {
                    .ring.index = ring->mIndex,
                    .ring.id = box->id,
                };
            top_window->layout_value_changed(&event);
        }
    }
}

//
static void gui_surface_layout_ring_tween_scroll_step(gui_layout_tween_angle_struct *tween) // 需要外部配置
{
    gui_surface_struct *surface = tween->surface;
    gui_layout_ring_struct *ring = &surface->layout.ring;
    ring->mAngVal = tween->curr_angle;
    ring->offset_x = (short)tween->curr_angle;
    gui_surface_layout_ring_commit_position(surface);
    gui_surface_force_update();
}
static void gui_surface_layout_ring_tween_scroll_finish(gui_layout_tween_angle_struct *tween) // 需要外部配置
{
    gui_surface_struct *surface = tween->surface;
    gui_layout_ring_struct *ring = &surface->layout.ring;
    ring->auto_start = 0;
    ring->mAngVal = tween->curr_angle;
    ring->offset_x = (short)tween->curr_angle;
    gui_surface_layout_ring_commit_position(surface);
    gui_surface_layout_ring_update_current_index(surface);
    gui_surface_layout_ring_report_changed(surface);
    gui_surface_force_update();
}
static void gui_surface_layout_ring_scroll_cancel(gui_layout_tween_angle_struct *tween) // 需要外部配置
{
    gui_surface_struct *surface = tween->surface;
    gui_layout_ring_struct *ring = &surface->layout.ring;
    ring->auto_start = 0;
    ring->mAngVal = tween->end_angle;
    ring->offset_x = (short)tween->curr_angle;
    gui_surface_layout_ring_commit_position(surface);
    gui_surface_force_update();
}

static void gui_surface_layout_ring_auto_start_timer(unsigned int timer, void *param)
{
    application_stop_user_timer(timer);

    gui_surface_struct *surface = (gui_screen_struct *)param;
    gui_layout_ring_struct *ring = &surface->layout.ring;
    if (surface->screen->type == TYPE_GUI_LAYOUT_RING && ring->auto_start)
    {
        gui_layout_tween_angle_struct *angle_tween = gui_surface_layout_tween_angle_init(surface, 180.0f);
        angle_tween->move_angle = ring->mAngGap - 360.0f;
        angle_tween->speed_angle = -7;
        angle_tween->mode = TWEEN_TYPE_SIN_IN_OUT;
        angle_tween->scroll_step = gui_surface_layout_ring_tween_scroll_step;
        angle_tween->scroll_finish = gui_surface_layout_ring_tween_scroll_finish;
        angle_tween->scroll_cancel = gui_surface_layout_ring_scroll_cancel;
        gui_surface_layout_tween_angle_start(surface, 180.0f);
    }
}

static void gui_surface_layout_ring_auto_start(gui_surface_struct *surface)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    if (ring->auto_start)
    {
        application_start_user_timer(1, gui_surface_layout_ring_auto_start_timer, surface);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
gui_box_struct *gui_surface_layout_ring_get_item_by_index(gui_surface_struct *surface, short index)
{
    gui_box_struct *box = surface->child;
    short count = 0;
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
        {
            if (count++ == index)
                return box;
        }
        box = box->brother;
    }
    return NULL;
}

gui_box_struct *gui_surface_layout_ring_get_current_item(gui_surface_struct *surface)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    if (ring->auto_start)
        return NULL;
    return gui_surface_layout_ring_get_item_by_index(surface, ring->mIndex);
}

gui_box_struct *gui_surface_layout_ring_get_item_by_point(gui_surface_struct *surface, gui_touch_point_struct *touch_point)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    gui_box_struct *box = surface->child;
    geometry_rect box_rect = {0};


    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL && box->visible)
        {
            gui_surface_box_get_geometry_rect(surface, box, &box_rect);
            if (check_rect_contain_point_xy(&box_rect, touch_point->x, touch_point->y)) {
                // SYS_DEBUG("gui: ring_get_item_by_pos(x: %d, y: %d), id=%d, index=%d", box->id, box->layout_index);
                return box;
            }
        }
        box = box->brother;
    }
    return NULL;
}

short gui_surface_layout_ring_get_item_index(gui_surface_struct *surface, gui_touch_point_struct *touch_point)
{
    gui_box_struct *box = gui_surface_layout_ring_get_item_by_point(surface, touch_point);
    if (box != NULL)
        return box->layout_index;
    return -1;
}

short gui_surface_layout_ring_get_id_by_index(gui_surface_struct *surface, short index)
{
    gui_box_struct *box = gui_surface_layout_ring_get_item_by_index(surface, index);
    return (box != NULL) ? box->id : 0;
}

/*******************************操作接口************************************/
// 根据排版类型，进行排版
void gui_surface_layout_ring_arrange(gui_surface_struct *surface)
{
    const gui_layout_ring_struct *layout_config = surface->screen->layout_config;
    gui_layout_ring_struct *ring = &surface->layout.ring;

    memset(ring, 0, sizeof(gui_layout_ring_struct));
    ring->mBaseAng = layout_config->mBaseAng;
    ring->mCount = gui_surface_layout_ring_get_count(surface);
    ring->mZoom = layout_config->mZoom;
    ring->mRadius = layout_config->mRadius;
    ring->mAngGap = ((ring->mCount == 0) ? 360.0f : 360.0f / ring->mCount);
    if (!FLOAT_EQUAL(layout_config->mAngGap, 0.0f) && (layout_config->mAngGap > ring->mAngGap))
    {
        ring->mAngGap = layout_config->mAngGap;
    }
    ring->c_x = layout_config->c_x;
    ring->c_y = layout_config->c_y;
    ring->c_bias_x = layout_config->c_bias_x;
    ring->c_bias_h = 90 - (atan2f(ring->mRadius, RING_ABS(ring->c_bias_x)) * 180.0f / MATH_PI);
    ring->cfg_zoom_map = layout_config->cfg_zoom_map;
    ring->cfg_pos_map = layout_config->cfg_pos_map;
    ring->cfg_map_size = layout_config->cfg_map_size;

    ring->min_offset = -(ring->mCount * ring->mAngGap); // -360;
    ring->max_offset = (ring->mCount * ring->mAngGap);  // 360;
    ring->item_gap = (short)ring->mAngGap;
    ring->auto_start = layout_config->auto_start;
    ring->loop_flag = 1;
    if (ring->auto_start)
    {
        ring->mAngVal = 180.0f;
    }

    SYS_DEBUG("gui: ring_arrange, R=%f, gap=%f, bh=%f ...........", ring->mRadius, ring->mAngGap, ring->c_bias_h);
    gui_surface_layout_ring_commit_position(surface);
    gui_surface_layout_ring_update_current_index(surface);
    gui_surface_layout_ring_auto_start(surface);
}

// 对排版中的子元素，使用指定的偏移
void gui_surface_layout_ring_offset(gui_surface_struct *surface, short layout_offset_x, short layout_offset_y)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;

    SYS_DEBUG("gui: layout_ring_offset(%d)", layout_offset_x);

    gui_surface_layout_ring_set_angle(ring, (float)layout_offset_x);
    gui_surface_layout_ring_commit_position(surface);
    gui_surface_layout_ring_update_current_index(surface);
    gui_surface_layout_ring_report_changed(surface);
    ring->offset_x = (short)ring->mAngVal;
}

// 对排版中的子元素，进行指定的偏移
void gui_surface_layout_ring_move(gui_surface_struct *surface, short move_offset_x, short move_offset_y, float angle)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    ring->offset_x = (short)angle;
    SYS_DEBUG("gui: gui_surface_layout_ring_move(%f)", angle);
    gui_surface_layout_ring_set_angle(ring, angle);
    gui_surface_layout_ring_commit_position(surface);
    gui_surface_layout_ring_update_current_index(surface);
    gui_surface_layout_ring_report_changed(surface);
}

//
void gui_surface_layout_ring_move_end(gui_surface_struct *surface)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    SYS_DEBUG("gui: gui_surface_layout_ring_move_end");
    ring->mAngVal = ((int)(ring->mAngVal / ring->mAngGap)) * ring->mAngGap;
    gui_surface_layout_ring_commit_position(surface);
    gui_surface_layout_ring_update_current_index(surface);
    gui_surface_layout_ring_report_changed(surface);
}

/*****************************************************切换条目*******************************************************/

void gui_surface_layout_ring_auto_scroll_step(gui_layout_tween_angle_struct *tween_angle)
{
    gui_surface_struct *surface = tween_angle->surface;
    gui_layout_ring_struct *ring = &surface->layout.ring;
    if (surface != NULL)
    {
        gui_surface_layout_ring_set_angle(ring, tween_angle->curr_angle);
        gui_surface_layout_ring_commit_position(surface);
    }
    ring->offset_x = (short)ring->mAngVal;
    gui_surface_force_update();
}

void gui_surface_layout_ring_auto_scroll_finish(gui_layout_tween_angle_struct *tween_angle)
{
    gui_surface_struct *surface = tween_angle->surface;
    gui_layout_ring_struct *ring = &surface->layout.ring;
    if (surface != NULL)
    {
        gui_surface_layout_ring_set_angle(ring, tween_angle->curr_angle);
        gui_surface_layout_ring_commit_position(surface);
        gui_surface_layout_ring_update_current_index(surface);
        gui_surface_layout_ring_report_changed(surface);
    }
    ring->offset_x = (short)ring->mAngVal;
    gui_surface_force_update();
}

void gui_surface_layout_ring_switch_to_item(gui_surface_struct *surface, short skip_item)
{
    gui_layout_ring_struct *ring = &surface->layout.ring;
    short move_angle = ring->mAngGap * skip_item;
    short speed_angle = gui_surface_layout_tween_angle_calculate_speed(move_angle);

    if (gui_surface_layout_tween_angle_is_running())
    {
        gui_layout_tween_angle_struct *tween_angle = gui_surface_layout_tween_angle_get_tween();
        tween_angle->mode = TWEEN_TYPE_LINEAR;
        tween_angle->move_angle = move_angle;
        tween_angle->speed_angle += speed_angle;
        if (tween_angle->speed_angle != 0)
        {
            gui_surface_layout_tween_angle_move(surface, ring->mAngVal);
        }
    }
    else
    {
        gui_layout_tween_angle_struct *tween_angle = gui_surface_layout_tween_angle_init(surface, ring->mAngVal);
        tween_angle->mode = TWEEN_TYPE_LINEAR;
        tween_angle->scroll_step = gui_surface_layout_ring_auto_scroll_step;
        tween_angle->scroll_finish = gui_surface_layout_ring_auto_scroll_finish;
        tween_angle->move_angle = move_angle;
        tween_angle->speed_angle = speed_angle;
        gui_surface_layout_tween_angle_start(surface, ring->mAngVal);
    }
}
