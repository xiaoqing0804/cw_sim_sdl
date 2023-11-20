#include "math.h"
#include "gui_touch.h"
#include "system_util_math.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_layout_ring.h"
#include "gui_surface_layout_ring_config.h"


//
static float gui_touch_layout_ring_get_rot(gui_layout_ring_struct* ring, int x, int y)
{
    float ret = 0.0f;

    float cx, cy;

    cx = (float)x - ring->c_x;
    cy = (float)y - ring->c_y;
    ret = atan2f(cx, cy) * 180.0f / MATH_PI;

    return ret;
}


/******************************************************
**
**上下滑动
**在上下滑动时，列表的偏移值是向上走，所以偏移值是负的
**
*******************************************************/

//点击
void gui_touch_layout_ring_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)	{
        gui_layout_ring_struct* ring = &surface->layout.ring;
		gui_box_struct* box = gui_surface_layout_ring_get_item_by_point(surface,touch_point);
		if(box != NULL) {
            if (ring->c_bias_x != 0) {
                short go_index = box->layout_index;
                if (go_index != ring->mIndex) {
                    // move to focus
                    float mov_dlt = (ring->mIndex - go_index)*ring->mAngGap;
                    if (mov_dlt > 180.0f) {
                        mov_dlt -= 360.0f;
                    }
                    else if (mov_dlt < -180.0f) {
                        mov_dlt += 360.0f;
                    }
                    SYS_DEBUG("gui: layout_ring_click_on_item(%d, %d, %f)", ring->mIndex, go_index, ring->mAngGap);
                    gui_touch_layout_rebound_auto_moving(top_window,DIRECTION_TYPE_LEFT, (short)mov_dlt, 0);
                    return;
                }
            }
            
			if(top_window->click_on_layout_item) {
                gui_click_layout_struct event;
                event.id = (unsigned char)box->id;
                event.index = box->layout_index;
                event.x = touch_point->x;
                event.y = touch_point->y;
				top_window->click_on_layout_item(&event);
			}
		}
	}
}


/*************************移动********************************/

//移动 [可以任何方向移动]
void gui_touch_layout_ring_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;

	gui_layout_ring_struct* ring = &surface->layout.ring;

    if (ring->mPenDn == 0) {
        ring->mSith = gui_touch_layout_ring_get_rot(ring, touch_point->x, touch_point->y);
        ring->mPenDn = 1;
    }
}

//移动 [可以任何方向移动]
void gui_touch_layout_ring_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface != NULL)
	{
		gui_layout_ring_struct* ring = &surface->layout.ring;

        if (ring->mPenDn == 1) {
            float rot = gui_touch_layout_ring_get_rot(ring, touch_point->x, touch_point->y);
            float dlt = 0.0f;
            float angle = ring->mAngVal;

            SYS_DEBUG("gui: ring_touch_move, rot=%f, Sith=%f------------", rot, ring->mSith);
            if (rot != ring->mSith) {
                dlt = rot - ring->mSith;
				// [ 20230825 Taylor.Le, 角度计算跳变问题
                if (dlt > 180.0f) {
                    dlt -= 360.0f;
                }
                else if (dlt <= -180.0f) {
                    dlt += 360.0f;
                }
				// ]
                if (dlt >= 2.0f || dlt <= -2.0f) {
                    ring->mSith = rot;
                    SYS_DEBUG("ring->mAngVal =%f dlt=%f",angle,dlt);
                    angle += dlt;
                    gui_surface_layout_ring_move(surface, 0, 0, angle);
                    ring->mov_speed = (short)dlt;
                 }
            }
        }
        gui_surface_force_update();
	}
}


//移动 [可以任何方向移动]
void gui_touch_layout_ring_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
	if(touch_point->direction == DIRECTION_TYPE_NONE)
		return;

	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	gui_layout_ring_struct* ring = &surface->layout.ring;
    ring->mPenDn = 0;

    SYS_DEBUG("gui: ring_touch_end, sith=%f, spd=%d, spdx=%d, spdy=%d", ring->mSith, ring->mov_speed, touch_point->speed_x, touch_point->speed_y);

    short mov_speed = ring->mov_speed * (short)sqrt(touch_point->speed_x*touch_point->speed_x + touch_point->speed_y*touch_point->speed_y)/TOUCH_AUTO_MOVE_GAP_MS;
    
    gui_touch_layout_rebound_auto_moving(top_window,DIRECTION_TYPE_LEFT, 0, mov_speed);
}


void gui_touch_layout_ring_touch_cancle(const gui_window_struct* top_window)
{
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
	    gui_surface_layout_ring_move_end(surface);
        gui_surface_force_update();
	}
}



