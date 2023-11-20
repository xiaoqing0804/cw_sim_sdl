
#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_message.h"
#include "system_util_math.h"

#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "app_window_moreinfo.h"
#include "app_window_moreinfo_kaleidoscope.h"
#include "app_window_moreinfo_kaleidoscope_layout.h"
#include "application_config_app_info.h"
#include "gui_surface_layout_ring_center.h"
#include <math.h>
#include "gui_surface_box_scale.h"

#include "bsp_wdt/wdt.h"

#define MAX_KALEIDOSCOPE_CNT 5

unsigned char keleidoscope_buff[MAX_KALEIDOSCOPE_CNT];
static unsigned char keleidoscope_cnt = 0;

static unsigned char g_kaleidoscope_app_index = 0;
static gui_kaleidoscope_ray_struct kaleidoscopes[KALEIDOSCOPE_RAY_TOTAL] = {0};

static unsigned char g_kaleidoscope_timer_index = 0;
static unsigned char g_kaleidoscope_zoom_out = 0;
static unsigned int g_temp_timer_hd;
static gui_box_struct *g_box_array[KALEIDOSCOPE_APP_TOTAL];

#define CUR_GAP ((LCD_SIZE_HALF_WIDTH / 100) * 100)
#define CUR_MAX (CUR_GAP)
#define CUR_STEP (CUR_GAP / 10)
#define CUR_DUR ((CUR_GAP * 40) / 100)
static short g_kaleidoscope_status0 = 1;               // 偶数线, 0: 显示两个icon； 1： 显示一个icon...
static short g_kaleidoscope_status1 = 1;               // 奇数线
static short g_kaleidoscope_cur_offset0 = CUR_GAP;     // 偶数线
static short g_kaleidoscope_cur_offset1 = CUR_GAP / 2; // 奇数线
static float g_kaleidoscope_width = 0;
static float g_kaleidoscope_height = 0;
static unsigned char g_kaleidoscope_box_index[KALEIDOSCOPE_RAY_TOTAL][2];

#define C_DIS(v) ((v)*LCD_SIZE_HALF_WIDTH)
static const float g_ccur[] = {0, 0.5f, 1.0f, 1.5f, 2.0f};
static const float g_cdis[] = {0.18f, C_DIS(0.34f), C_DIS(0.751667f), C_DIS(1.5), C_DIS(2.5f)};
static const float g_scale[] = {0.3f, 0.6f, 1.05f, 1.5f, 2.0f};
#define LG3_MAP_SIZE countof(g_ccur)

static const float g_cos_sin[][2] = {
    {0.0, -1.0f},
    {SIN_22_5, -COS_22_5},
    {SIN_45_0, -COS_45_0},
    {SIN_67_5, -COS_67_5},

    {1.0, 0.0f},
    {SIN_22_5, COS_22_5},
    {SIN_45_0, COS_45_0},
    {SIN_67_5, COS_67_5},

    {0.0, 1.0f},
    {-SIN_22_5, COS_22_5},
    {-SIN_45_0, COS_45_0},
    {-SIN_67_5, COS_67_5},

    {-1.0, 0.0f},
    {-SIN_22_5, -COS_22_5},
    {-SIN_45_0, -COS_45_0},
    {-SIN_67_5, -COS_67_5},
};

static const gui_image_struct g_kaleidoscope_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .data = &pic_app_hr_88_info,
};

static const gui_widget_struct g_kaleidoscope_widget =
    {
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = KALEIDOSCOPE_MAX_WIDTH,
        .height = KALEIDOSCOPE_MAX_WIDTH,
        .anchor_x = ANCHOR_VALUE(0.5f),
        .anchor_y = ANCHOR_VALUE(0.5f),
        .visible = 1,
        .child_num = 1,
        .children = &g_kaleidoscope_image,
};

//
static gui_kaleidoscope_app_struct *app_window_moreinfo_kaleidoscope_create_app()
{
    if (g_kaleidoscope_app_index >= KALEIDOSCOPE_APP_TOTAL)
    {
        g_kaleidoscope_app_index = 0;
    }
    return &g_kaleidoscope_app[g_kaleidoscope_app_index++];
}

static unsigned int app_window_moreinfo_kaleidoscope_get_box(void)
{
    static unsigned int box_index = 0;
    unsigned int count;

    for (count = 0; count < KALEIDOSCOPE_APP_TOTAL; count++, box_index++)
    {
        if (box_index >= KALEIDOSCOPE_APP_TOTAL)
        {
            box_index = 0;
        }
        if (g_box_array[box_index]->layout_index == 0)
        {
            break;
        }
    }
    if (box_index < KALEIDOSCOPE_APP_TOTAL)
    {
        g_box_array[box_index]->visible = 1;
        g_box_array[box_index]->layout_index = 1;
        return box_index;
    }
    return 0xFF;
}

static unsigned int app_window_moreinfo_kaleidoscope_free_box(unsigned int index)
{
    if (index < KALEIDOSCOPE_APP_TOTAL)
    {
        g_box_array[index]->visible = 0;
        g_box_array[index]->layout_index = 0;
    }
}

static float app_window_moreinfo_kaleidoscope_get_distance(float dx)
{
    // return (0.538*dx + 0.213)*dx*LCD_SIZE_HALF_WIDTH;
    return lg3_interpolation(g_ccur, g_cdis, LG3_MAP_SIZE, dx);
}

static float app_window_moreinfo_kaleidoscope_get_scale(float dx)
{
    // return (0.9*dx + 0.05)*dx;
    return lg3_interpolation(g_ccur, g_scale, LG3_MAP_SIZE, dx);
}

static void app_window_moreinfo_kaleidoscope_arrang(void);
static void app_window_moreinfo_kaleidoscope_step(int zoom)
{
    // static unsigned int pre_ts = 0xFFFFFFFF;
    // unsigned int ts = sys_timer_get_tick();
    unsigned int i;

    if (zoom > 0)
    {
        g_kaleidoscope_cur_offset0 += zoom;
        g_kaleidoscope_cur_offset1 += zoom;

        if (g_kaleidoscope_cur_offset0 > CUR_MAX)
        {
            if (g_kaleidoscope_status0 != 0)
            {
                g_kaleidoscope_status0 = 0;

                g_kaleidoscope_cur_offset0 = CUR_STEP;
                for (i = 0; i < KALEIDOSCOPE_RAY_TOTAL; i += 2)
                {
                    g_kaleidoscope_box_index[i][1] = g_kaleidoscope_box_index[i][0];
                    g_kaleidoscope_box_index[i][0] = app_window_moreinfo_kaleidoscope_get_box();
                }
            }
        }

        if (g_kaleidoscope_cur_offset1 > CUR_MAX)
        {
            if (g_kaleidoscope_status1 != 0)
            {
                g_kaleidoscope_status1 = 0;

                g_kaleidoscope_cur_offset1 = CUR_STEP;
                for (i = 1; i < KALEIDOSCOPE_RAY_TOTAL; i += 2)
                {
                    g_kaleidoscope_box_index[i][1] = g_kaleidoscope_box_index[i][0];
                    g_kaleidoscope_box_index[i][0] = app_window_moreinfo_kaleidoscope_get_box();
                }
            }
        }

        if (g_kaleidoscope_cur_offset0 >= CUR_DUR)
        {
            if (g_kaleidoscope_status0 != 1)
            {
                g_kaleidoscope_status0 = 1;

                for (i = 0; i < KALEIDOSCOPE_RAY_TOTAL; i += 2)
                {
                    app_window_moreinfo_kaleidoscope_free_box(g_kaleidoscope_box_index[i][1]);
                    g_kaleidoscope_box_index[i][1] = 0xFF;
                }
            }
        }
        if (g_kaleidoscope_cur_offset1 >= CUR_DUR)
        {
            if (g_kaleidoscope_status1 != 1)
            {
                g_kaleidoscope_status1 = 1;

                for (i = 1; i < KALEIDOSCOPE_RAY_TOTAL; i += 2)
                {
                    app_window_moreinfo_kaleidoscope_free_box(g_kaleidoscope_box_index[i][1]);
                    g_kaleidoscope_box_index[i][1] = 0xFF;
                }
            }
        }
    }
    else
    {
        g_kaleidoscope_cur_offset0 += zoom;
        g_kaleidoscope_cur_offset1 += zoom;

        if (g_kaleidoscope_cur_offset0 < 0)
        {
            if (g_kaleidoscope_status0 != 1)
            {
                g_kaleidoscope_status0 = 1;

                g_kaleidoscope_cur_offset0 = CUR_MAX - CUR_STEP;
                for (i = 0; i < KALEIDOSCOPE_RAY_TOTAL; i += 2)
                {
                    app_window_moreinfo_kaleidoscope_free_box(g_kaleidoscope_box_index[i][0]);
                    g_kaleidoscope_box_index[i][0] = g_kaleidoscope_box_index[i][1];
                    g_kaleidoscope_box_index[i][1] = 0xFF;
                }
            }
        }

        if (g_kaleidoscope_cur_offset1 < 0)
        {
            if (g_kaleidoscope_status1 != 1)
            {
                g_kaleidoscope_status1 = 1;

                g_kaleidoscope_cur_offset1 = CUR_MAX - CUR_STEP;
                for (i = 1; i < KALEIDOSCOPE_RAY_TOTAL; i += 2)
                {
                    app_window_moreinfo_kaleidoscope_free_box(g_kaleidoscope_box_index[i][0]);
                    g_kaleidoscope_box_index[i][0] = g_kaleidoscope_box_index[i][1];
                    g_kaleidoscope_box_index[i][1] = 0xFF;
                }
            }
        }

        if (g_kaleidoscope_cur_offset0 <= CUR_DUR)
        {
            if (g_kaleidoscope_status0 != 0)
            {
                g_kaleidoscope_status0 = 0;

                for (i = 0; i < KALEIDOSCOPE_RAY_TOTAL; i += 2)
                {
                    g_kaleidoscope_box_index[i][1] = app_window_moreinfo_kaleidoscope_get_box();
                }
            }
        }

        if (g_kaleidoscope_cur_offset1 <= CUR_DUR)
        {
            if (g_kaleidoscope_status1 != 0)
            {
                g_kaleidoscope_status1 = 0;

                for (i = 1; i < KALEIDOSCOPE_RAY_TOTAL; i += 2)
                {
                    g_kaleidoscope_box_index[i][1] = app_window_moreinfo_kaleidoscope_get_box();
                }
            }
        }
    }

    app_window_moreinfo_kaleidoscope_arrang();
    gui_surface_commit();
}

static void app_window_moreinfo_kaleidoscope_init_box(void)
{
    unsigned int i;
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_moreinfo_kaleidoscope);
    gui_kaleidoscope_app_struct *kaleidoscope_app = NULL;

    for (i = 0; i < KALEIDOSCOPE_APP_TOTAL; i++)
    {
        gui_box_struct *box = gui_surface_cache_add_box();
        if (box != NULL)
        {
            kaleidoscope_app = app_window_moreinfo_kaleidoscope_create_app();
            box->id = kaleidoscope_app->id;
            box->type = TYPE_GUI_CONTROL_IMAGE;
            box->widget = (gui_widget_struct *)&g_kaleidoscope_widget;
            box->width = kaleidoscope_app->picture->width;
            box->height = kaleidoscope_app->picture->height;
            g_kaleidoscope_width = box->width;
            g_kaleidoscope_height = box->height;
            box->scale = 1.0f;
            box->visible = 0;

            gui_node_struct *node = gui_surface_cache_add_node();
            if (node != NULL)
            {
                node->type = TYPE_GUI_DRAW_PICTURE;
                node->id = 0;
                node->width = kaleidoscope_app->picture->width;
                node->height = kaleidoscope_app->picture->height;
                node->data = (void *)(kaleidoscope_app->picture); // picture_info_struct*
                node->scale = 1.0f;
                gui_surface_node_check_clip(box, node, kaleidoscope_app->picture->width, kaleidoscope_app->picture->height);
                gui_surface_box_add_node(box, node);
            }
            g_box_array[i] = box;
            gui_surface_add_box(surface, box);
        }
    }

    memset(g_kaleidoscope_box_index, 0xFF, sizeof(g_kaleidoscope_box_index));
    for (i = 0; i < KALEIDOSCOPE_RAY_TOTAL; i++)
    {
        g_kaleidoscope_box_index[i][0] = app_window_moreinfo_kaleidoscope_get_box();
    }
}

static void app_window_moreinfo_kaleidoscope_arrang(void)
{
    unsigned int box_index = 0;
    unsigned int i;
    int bx = 0;
    int by = 0;
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_moreinfo_kaleidoscope);
    float dx0, dx1, dist[2][2], scale[2][2];

    dx0 = (float)g_kaleidoscope_cur_offset0 / (float)CUR_GAP;
    dx1 = (float)g_kaleidoscope_cur_offset1 / (float)CUR_GAP;

    SYS_DEBUG("%d,%d  dxdy:(%f,%f)", g_kaleidoscope_cur_offset0, g_kaleidoscope_cur_offset1, dx0, dx1);
    if (dx0 > 1.0f)
        dx0 -= 1.0f;
    dist[0][0] = app_window_moreinfo_kaleidoscope_get_distance(dx0);
    scale[0][0] = app_window_moreinfo_kaleidoscope_get_scale(dx0);
    dx0 += 1.0f;
    dist[0][1] = app_window_moreinfo_kaleidoscope_get_distance(dx0);
    scale[0][1] = app_window_moreinfo_kaleidoscope_get_scale(dx0);

    if (dx1 > 1.0f)
        dx1 -= 1.0f;
    dist[1][0] = app_window_moreinfo_kaleidoscope_get_distance(dx1);
    scale[1][0] = app_window_moreinfo_kaleidoscope_get_scale(dx1);
    dx1 += 1.0f;
    dist[1][1] = app_window_moreinfo_kaleidoscope_get_distance(dx1);
    scale[1][1] = app_window_moreinfo_kaleidoscope_get_scale(dx1);

    for (i = 0; i < KALEIDOSCOPE_RAY_TOTAL; i++)
    {
        if (g_kaleidoscope_box_index[i][0] != 0xFF)
        {
            box_index = g_kaleidoscope_box_index[i][0];
            if (dist[i & 0x1][0] >= 7.0f)
            {
                bx = (int)(g_cos_sin[i][0] * dist[i & 0x1][0]);
                by = (int)(g_cos_sin[i][1] * dist[i & 0x1][0]);
                box_index = g_kaleidoscope_box_index[i][0];
                // g_box_array[box_index]->x = LCD_SIZE_HALF_WIDTH + bx - g_box_array[box_index]->width/2;
                // g_box_array[box_index]->y = LCD_SIZE_HALF_HEIGHT + by - g_box_array[box_index]->height/2;
                g_box_array[box_index]->width = g_kaleidoscope_width;
                g_box_array[box_index]->height = g_kaleidoscope_height;
                g_box_array[box_index]->x = LCD_SIZE_HALF_WIDTH + bx;  // - g_box_array[box_index]->width / 2;
                g_box_array[box_index]->y = LCD_SIZE_HALF_HEIGHT + by; // - g_box_array[box_index]->height / 2;
                g_box_array[box_index]->scale = 1.0f;

                g_box_array[box_index]->child->width = g_kaleidoscope_width;
                g_box_array[box_index]->child->height = g_kaleidoscope_height;
                g_box_array[box_index]->child->scale = 1.0f;
                // gui_surface_box_scale_offset(surface, g_box_array[box_index], scale[i & 0x1][0]);
                g_box_array[box_index]->scale = scale[i & 0x1][0];
                g_box_array[box_index]->visible = 1;
            }
            else
            {
                g_box_array[box_index]->visible = 0;
            }
            // SYS_DEBUG("app_window_moreinfo_kaleidoscope_arrang[%d, 0] bx=%d, by=%d, scale=%f, dis=%f, box=%d ,x= %f , y=%f", i, bx, by, scale[i & 0x1][0], dist[i & 0x1][0], box_index, g_box_array[box_index]->x, g_box_array[box_index]->y);
            // SYS_DEBUG("app_window_moreinfo_kaleidoscope_arrang g_box_array[box_index]->width %f g_box_array[box_index]->heigh %f", g_box_array[box_index]->width, g_box_array[box_index]->height);
        }
        if (g_kaleidoscope_box_index[i][1] != 0xFF)
        {
            if (dist[i & 0x1][1] >= 7.0f)
            {
                bx = (int)(g_cos_sin[i][0] * dist[i & 0x1][1]);
                by = (int)(g_cos_sin[i][1] * dist[i & 0x1][1]);
                box_index = g_kaleidoscope_box_index[i][1];
                g_box_array[box_index]->width = g_kaleidoscope_width;
                g_box_array[box_index]->height = g_kaleidoscope_height;
                g_box_array[box_index]->x = LCD_SIZE_HALF_WIDTH + bx;  // - g_box_array[box_index]->width / 2;
                g_box_array[box_index]->y = LCD_SIZE_HALF_HEIGHT + by; // - g_box_array[box_index]->height / 2;

                g_box_array[box_index]->child->width = g_kaleidoscope_width;
                g_box_array[box_index]->child->height = g_kaleidoscope_height;
                g_box_array[box_index]->child->scale = 1.0f;
                // gui_surface_box_scale_offset(surface, g_box_array[box_index], scale[i & 0x1][1]);
                g_box_array[box_index]->scale = scale[i & 0x1][1];
                g_box_array[box_index]->visible = 1;
            }
            else
            {
                g_box_array[box_index]->visible = 0;
            }
            // SYS_DEBUG("app_window_moreinfo_kaleidoscope_arrang[%d, 1] bx=%d, by=%d, scale=%f, dis=%f, box=%d ,x= %f , y=%f", i, bx, by, scale[i & 0x1][1], dist[i & 0x1][1], box_index, g_box_array[box_index]->x, g_box_array[box_index]->y);
            // SYS_DEBUG("app_window_moreinfo_kaleidoscope_arrang g_box_array[box_index]->width %f g_box_array[box_index]->heigh %f", g_box_array[box_index]->width, g_box_array[box_index]->height);
        }
    }
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_moreinfo_kaleidoscope_init(void *buf)
{
    g_kaleidoscope_timer_index = 0;
    g_temp_timer_hd = 0;

    g_kaleidoscope_status0 = 1;
    g_kaleidoscope_status1 = 1;
    g_kaleidoscope_cur_offset0 = CUR_GAP;
    g_kaleidoscope_cur_offset1 = CUR_GAP / 2;
    keleidoscope_cnt = 0;
}

static void app_window_moreinfo_kaleidoscope_load()
{
    app_window_moreinfo_kaleidoscope_init_box();
    app_window_moreinfo_kaleidoscope_arrang();
}

static void app_window_moreinfo_kaleidoscope_entry()
{
    //    application_open_act_timer(APPLICATION_TIMER_ACT, 14);
}

static void app_window_moreinfo_kaleidoscope_exit()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
    application_close_act_timer(APPLICATION_TIMER_ACT_1);
    g_kaleidoscope_timer_index = 0;

    application_stop_user_timer(g_temp_timer_hd);
    g_temp_timer_hd = 0;
    keleidoscope_cnt = 0;

    g_kaleidoscope_status0 = 1;
    g_kaleidoscope_status1 = 1;
    g_kaleidoscope_cur_offset0 = CUR_GAP;
    g_kaleidoscope_cur_offset1 = CUR_GAP / 2;
}

static void app_window_moreinfo_kaleidoscope_destroy()
{
}

/*-----------------------------自定义事件--------------------------------------*/
static gui_box_struct *app_window_moreinfo_kaleidoscope_find_box(int touch_x, int touch_y)
{
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_moreinfo_kaleidoscope);
    gui_box_struct *box = surface->child;

    int x, y, w, h, zw, zh;

    while (box != NULL)
    {
        if ((box->type == TYPE_GUI_CONTROL_IMAGE) && box->visible)
        {
            x = box->x;
            y = box->y;
            w = box->width;
            h = box->height;
            if (box->scale != 1.0f)
            {
                zw = w * box->scale;
                zh = h * box->scale;
                x = x - zw / 2;
                y = y - zh / 2;
                w = zw;
                h = zh;
            }

            if (check_rect_contain_xy(x, y, w, h, touch_x, touch_y))
            {
                return box;
            }
        }
        box = box->brother;
    }
    return NULL;
}

static unsigned char app_window_moreinfo_kaleidoscope_touch_item(gui_touch_struct *event)
{
    static pre_dist = 0;
    static touch_up = 0;
    gui_box_struct *box;
    static short move_x = 0;
    static short move_y = 0;
    move_x = abs(event->x);
    move_y = abs(event->y);

    if (event->type == TOUCH_EVENT_TYPE_UP)
    {
        //         if (gui_run_time_lock())
        //             return 1;
        if (keleidoscope_cnt > 0)
            return 1;
        gui_box_struct *box = app_window_moreinfo_kaleidoscope_find_box(event->x, event->y);
        touch_up = (int)sqrt(move_x * move_x + move_y * move_y);
        if (abs(touch_up - pre_dist) < 5)
        {
            if (box != NULL)
            {
                app_info_struct *app_info = get_app_info_by_id((APP_INFO_ID)box->id);
                if (app_info != NULL)
                {
                    entry_app_by_info(app_info);
                }
            }
        }
    }
    else if (event->type == TOUCH_EVENT_TYPE_MOVE)
    {
        if (gui_run_time_lock())
            return 1;

        if ((event->direction == DIRECTION_TYPE_RIGHT) || (event->direction == DIRECTION_TYPE_UP))
        {
            keleidoscope_buff[keleidoscope_cnt] = 0;
            if (keleidoscope_cnt < MAX_KALEIDOSCOPE_CNT - 1)
            {
                keleidoscope_cnt++;
            }
        }
        else if ((event->direction == DIRECTION_TYPE_DOWN) || (event->direction == DIRECTION_TYPE_LEFT))
        {
            keleidoscope_buff[keleidoscope_cnt] = 1;
            if (keleidoscope_cnt < MAX_KALEIDOSCOPE_CNT - 1)
            {
                keleidoscope_cnt++;
            }
        }
        if ((keleidoscope_cnt == 1) && (g_kaleidoscope_timer_index == 0))
        {
            application_open_act_timer(APPLICATION_TIMER_ACT, 14);
        }

        //	    int dist = (int)sqrt(move_x*move_x + move_y*move_y);
        //        SYS_DEBUG("kaleidoscope x=%d  y=%d  dist=%d pre_dist=%d ",move_x,move_y,dist,pre_dist);
        //	    if (abs(dist-pre_dist) > 5) {
        //            app_window_moreinfo_kaleidoscope_step(dist-pre_dist);
        //            pre_dist = dist;
        //	    }

        return 1;
    }
    else if (event->type == TOUCH_EVENT_TYPE_DOWN)
    {
        pre_dist = (int)sqrt(move_x * move_x + move_y * move_y);
        return 1;
    }

    return 0;
}

static void app_window_kaleidoscope_updata(unsigned char kaleidoscope_out)
{
    SYS_DEBUG("g_kaleidoscope_timer_index =%d,%d", g_kaleidoscope_timer_index, kaleidoscope_out);

    if (++g_kaleidoscope_timer_index >= 5)
    {
        g_kaleidoscope_timer_index = 0;
        application_stop_user_timer(g_temp_timer_hd);
        g_temp_timer_hd = 0;
        application_open_act_timer(APPLICATION_TIMER_ACT, 10);
    }
    app_window_moreinfo_kaleidoscope_step(kaleidoscope_out > 0 ? CUR_STEP : -CUR_STEP);

    gui_surface_commit();
}

void app_window_moreinfo_kaleidoscope_user_timer_cb(unsigned int timer_hd, void *param)
{
    unsigned char cont_num = *((unsigned char *)param);
    app_window_kaleidoscope_updata(cont_num);
}

static void app_window_moreinfo_kaleidoscope_timer_handler(void *buf)
{

    static unsigned char cont_num;
    application_close_act_timer(APPLICATION_TIMER_ACT);

    if (keleidoscope_cnt <= 0)
        return;

    SYS_DEBUG("app_window_moreinfo_kaleidoscope_timer_handler =%d", keleidoscope_cnt);

    cont_num = keleidoscope_buff[0];
    for (int i = 0; i <= keleidoscope_cnt && i < MAX_KALEIDOSCOPE_CNT - 1; i++)
    {
        keleidoscope_buff[i] = keleidoscope_buff[i + 1];
    }
    keleidoscope_cnt--;

    SYS_DEBUG("app_window_moreinfo_kaleidoscope_timer_handler1 =%d = %d", keleidoscope_cnt, cont_num);

    //    app_window_moreinfo_kaleidoscope_step(cont_num);

    if (g_temp_timer_hd == 0)
    {
        g_temp_timer_hd = application_start_user_timer(14, app_window_moreinfo_kaleidoscope_user_timer_cb, &cont_num);
    }

    if (keleidoscope_cnt < 1)
    {
        application_close_act_timer(APPLICATION_TIMER_ACT);
    }
}

static void app_window_moreinfo_kaleidoscope_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    SYS_DEBUG("app_window_moreinfo_kaleidoscope_rolkey_handler =%d keleidoscope_cnt=%d", rolkey->rotate, keleidoscope_cnt);
    if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
    {
        keleidoscope_buff[keleidoscope_cnt] = 0;
        if (keleidoscope_cnt < MAX_KALEIDOSCOPE_CNT - 1)
        {
            keleidoscope_cnt++;
        }
    }
    else if (rolkey->rotate == ROTATE_TYPE_FORWARD)
    {
        keleidoscope_buff[keleidoscope_cnt] = 1;
        if (keleidoscope_cnt < MAX_KALEIDOSCOPE_CNT - 1)
        {
            keleidoscope_cnt++;
        }
    }

    if ((keleidoscope_cnt == 1) && (g_kaleidoscope_timer_index == 0))
    {
        application_open_act_timer(APPLICATION_TIMER_ACT, 14);
    }
}

static void app_window_moreinfo_kaleidoscope_key1_handler(void *buf)
{
    app_window_moreinfo_change();
}

static void app_window_moreinfo_kaleidosope_touch_event_click_on_layout_item(gui_click_layout_struct *event)
{
    SYS_DEBUG("app_window_moreinfo_kaleidosope_touch_event_click_on_layout_item x=%d y=%d index=%d", event->x, event->y, event->id);
    app_info_struct *app_info = get_app_info_by_id((APP_INFO_ID)event->id);
    if (app_info != NULL)
    {
        entry_app_by_info(app_info);
    }
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_moreinfo_kaleidoscope_events[] =
    {
        {
#if GUI_SINGLE_KEY_SUPPORT
            .id = EVENT_KEY1_DOUBLE,
#else
            .id = EVENT_KEY2_DOUBLE,
#endif
            .handler = app_window_moreinfo_kaleidoscope_key1_handler,
        },

        {
            .id = EVENT_ROLKEY,
            .handler = app_window_moreinfo_kaleidoscope_rolkey_handler,
        },

        {
            .id = EVENT_ACT,
            .handler = app_window_moreinfo_kaleidoscope_timer_handler,
        },
};

static const gui_touch_event_struct app_window_moreinfo_kaleidoscope_touch_events[] =
    {
        {
            .id = 0xFFFF,
            .touch = app_window_moreinfo_kaleidoscope_touch_item,
        },
};

static const gui_window_config_struct app_window_moreinfo_kaleidoscope_config =
    {
        .disable_scale = 1,
};

const gui_window_struct app_window_moreinfo_kaleidoscope =
    {
        .screen = &gui_screen_moreinfo_kaleidoscope,
        .config = &app_window_moreinfo_kaleidoscope_config,

        .init = app_window_moreinfo_kaleidoscope_init,
        .load = app_window_moreinfo_kaleidoscope_load,
        .entry = app_window_moreinfo_kaleidoscope_entry,
        .exit = app_window_moreinfo_kaleidoscope_exit,
        .destroy = app_window_moreinfo_kaleidoscope_destroy,

        .event_num = countof(app_window_moreinfo_kaleidoscope_events),
        .events = app_window_moreinfo_kaleidoscope_events,

        .touch_event_num = countof(app_window_moreinfo_kaleidoscope_touch_events),
        .touch_events = app_window_moreinfo_kaleidoscope_touch_events,
};
