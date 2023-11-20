#include "debug_info.h"
#include "math.h"
#include "feature_math.h"

#include "hal_lcd_area.h"
#include "system_util_math.h"

#include "gui_window_history.h"

#include "gui_surface_cache.h"
#include "gui_surface_layout.h"
#include "gui_surface_box_layout_item.h"
#include "gui_surface_layout_loop.h"

#include "gui_touch_layout_rebound.h"
#include "gui_surface_box_scale.h"
#include "gui_surface_layout_tween_position.h"

static const float k_temp[] = {-1, 0, 1, 2, 3, 4, 5};

// --|-- ---|--- ----|---- ---|--- --|--
static const float y_temp[] = {  0,
                                LCD_SIZE_HEIGHT*2/28,
                                LCD_SIZE_HEIGHT*7/28,
                                LCD_SIZE_HEIGHT*14/28,
                                LCD_SIZE_HEIGHT*21/28,
                                LCD_SIZE_HEIGHT*26/28,
                                LCD_SIZE_HEIGHT};

// -|- --|-- ---|--- ----|---- ---|--- --|-- -|-
static const float y_temp2[] = {LCD_SIZE_HEIGHT/32,
                                LCD_SIZE_HEIGHT*4/32,
                                LCD_SIZE_HEIGHT*9/32,
                                LCD_SIZE_HEIGHT*16/32,
                                LCD_SIZE_HEIGHT*23/32,
                                LCD_SIZE_HEIGHT*28/32,
                                LCD_SIZE_HEIGHT*31/32};

#define MID_SCALE   (1.0f)
static const float s_temp[] = {0, MID_SCALE/2.0f, MID_SCALE*3.0f/4.0f, MID_SCALE, MID_SCALE*3.0f/4.0f, MID_SCALE/2.0f, 0};


static int gui_surface_layout_loop_get_item_position_cy(gui_layout_loop_struct *loop, unsigned short index, float *scale)
{
    float* ypos_list = loop->y_pos_map;
    float dx;
    int y = SHORT_MIN;
    int cur_max = (loop->total + loop->column - 1) / loop->column;
    int row = index / loop->column;
    int temp = row * loop->item_gap + loop->offset_y;

    if (((index % loop->column) != 1)&&loop->palace_grid==0)
    {
        temp += loop->item_gap / 2;
        if (loop->y_pos_map2 != NULL) ypos_list = loop->y_pos_map2;
    }
    dx = (float)temp / (float)loop->item_gap;
    if (loop->loop_flag)
    {
        if (dx <= (float)(5 - cur_max))
        {
            dx += (float)cur_max;
        }
        else if (dx >= (float)cur_max)
        {
            dx -= (float)cur_max;
        }
        if(dx>=(float)(cur_max-0.5))
        {
            dx-=cur_max;
        }
    }
    SYS_DEBUG(
        "gui: loop_get_cy[%d], offset=%d, dx=%f, max=%d", index, loop->offset_y, dx, cur_max);

    *scale = 1.0f;
    if (loop->zoom_flag)
    {
        if (dx > -1.0 && dx < 5.0f)
        {
            y = (int)lg3_interpolation(loop->cursor_map, ypos_list, loop->map_size, dx);
            *scale = lgr_interpolation(loop->cursor_map, loop->scale_map, loop->map_size, dx);
        }
    }
    else
    {
        float dy = loop->row_height * dx;
        y = (int)dy + loop->row_height / 2;
    }
    return y;
}

/* get x value. */
static int gui_surface_layout_loop_get_item_position_cx(gui_layout_loop_struct *loop, unsigned short index, int y)
{
    int x = SHORT_MIN;
    int column = index % loop->column;
    int col_w = LCD_SIZE_WIDTH / loop->column;

    if (loop->map_size != 0 && loop->x_pos_map != NULL)
    {
        short temp = (index / loop->column) * loop->item_gap + loop->offset_y;
        if ((index % loop->column) != 1)
        {
            temp += loop->item_gap / 2;
        }
        float dx = (float)temp / (float)loop->item_gap;
        if (dx > -1.0 && dx < 5.0f)
        {
            x = (int)lg3_interpolation(loop->cursor_map, loop->x_pos_map + column * loop->map_size, loop->map_size, dx);
        }
    }
    else if (loop->arc_flag)
    {
        if ((column == 0) || (column == loop->column - 1))
        {
            //
            if (y > LCD_SIZE_HALF_HEIGHT)
            {
                y = y - LCD_SIZE_HALF_HEIGHT;
            }
            else
            {
                y = LCD_SIZE_HALF_HEIGHT - y;
            }
            x = (int)sqrt((float)((loop->arc_radius * loop->arc_radius) - (y * y)));
            x = loop->arc_radius - x + col_w * 5 / 10; // 2/3;

            if (column == loop->column - 1)
            {
                x = LCD_SIZE_WIDTH - x;
            }
        }
        else
        {
            //
            x = (2 * col_w * column + col_w) / 2;
        }
    }
    else
    {
        x = (2 * col_w * column + col_w) / 2;
    }
    return x;
}

static void gui_surface_layout_loop_set_offset(gui_layout_loop_struct *loop)
{
    loop->height = loop->item_gap * (loop->total + loop->column - 1) / loop->column;
    loop->max_offset = loop->item_gap;
    loop->min_offset = loop->item_gap * 4 - loop->height;
    
    // SYS_DEBUG("gui: layout_loop_set_offset(total=%d), min=%d, max=%d", loop->total, loop->min_offset, loop->max_offset);
}

static int gui_surface_layout_loop_commit_position(gui_surface_struct *surface)
{
    gui_screen_struct *screen = surface->screen;
    if (screen == NULL || screen->child_num == 0)
        return 0;

    gui_layout_loop_struct *loop = &surface->layout.loop;
    const gui_layout_loop_struct *list_config = screen->layout_config;
    gui_box_struct *box = surface->child;

    float scale;
    int count = 0, org_x = 0, org_y = 0, org_h;

    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
        {
            box->layout_index = count;

            org_x = 0;
            org_y = gui_surface_layout_loop_get_item_position_cy(loop, count, &scale);
            if (org_y > SHORT_MIN && org_y > 0 &&  org_y < LCD_SIZE_HEIGHT-1)
            {
                const picture_info_struct **picture_arr = (const picture_info_struct **)box->widget->children;
                const picture_info_struct *picture = (const picture_info_struct *)picture_arr[0];

                org_x = gui_surface_layout_loop_get_item_position_cx(loop, count, org_y);

                box->x = org_x;// 20231007 Taylor.Le,  - picture->width / 2;
                box->y = org_y;// 20231007 Taylor.Le,  - picture->height / 2;
                box->width = picture->width;
                box->height = picture->height;
                box->scale = 1.0f;

                box->child->scale = 1.0f;
                box->child->width = picture->width;
                box->child->height = picture->height;
                // SYS_DEBUG("gui: loopview, commit_position, item[%d] = {x %d, y: %d} vis=%d, idx=%d", count, org_x, org_y, box->visible, box->layout_index);
                // SYS_DEBUG("gui: loopview, commit_position {scale %f, box->scale: %f  box->child->scale=%f,", scale, box->scale, box->child->scale);
                if (loop->zoom_flag)
                {
#if defined(__CW_JL__)
                    box->scale = scale;
                    //gui_surface_box_scale_offset(surface, box, scale);
#else
                    // find pic
                    unsigned int i = 0;
                    unsigned int iw = picture->width * scale;
                    while ((iw < picture->width) && (i < box->widget->child_num))
                    {
                        i++;
                        picture = (const picture_info_struct *)picture_arr[i];
                    }
#endif
                }
                box->visible = 1;
            }
            else
            {
                box->visible = 0;
            }

            // SYS_DEBUG("gui: loopview, commit_position, item[%d] = {x %d, y: %d} vis=%d, idx=%d", count, org_x, org_y, box->visible, box->layout_index);
            count++;
        }
        box = box->brother;
    }
}

static int gui_surface_layout_loop_get_total(gui_surface_struct *surface)
{
    gui_screen_struct *screen = surface->screen;
    if (screen == NULL || screen->child_num == 0)
        return 0;

    gui_box_struct *box = surface->child;
    int count = 0;
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL)
        {
             count++;
        }
        box = box->brother;
    }
    return count;
}

static void gui_surface_layout_loop_init(gui_layout_loop_struct *loop, gui_layout_loop_struct *list_config)
{
    memset(loop, 0, sizeof(gui_layout_loop_struct));
    loop->row_height = list_config->row_height;
    loop->column = ((list_config->column != 0) ? list_config->column : 3);
    loop->scroll = list_config->scroll;
    loop->can_swipe = list_config->can_swipe;
    loop->force_up = list_config->force_up;
    loop->force_down = list_config->force_down;

#if (LCD_SHAPE == LCD_CIRCLE)
    loop->arc_flag = 1;
#else
    loop->arc_flag = list_config->arc_flag;
#endif
    loop->arc_radius = ((list_config->arc_radius != 0) ? list_config->arc_radius : LCD_SIZE_WIDTH * 3 / 2);
    loop->zoom_flag = list_config->zoom_flag;
    loop->item_gap = list_config->row_height;

    loop->palace_grid = list_config->palace_grid;

    loop->loop_flag = list_config->loop_flag;

    loop->map_size = ((list_config->map_size != 0) ? list_config->map_size : countof(k_temp));
    loop->cursor_map = ((list_config->cursor_map != NULL) ? list_config->cursor_map : k_temp);
    loop->x_pos_map = list_config->x_pos_map;
    loop->y_pos_map = ((list_config->y_pos_map != NULL) ? list_config->y_pos_map : y_temp);
    loop->y_pos_map2 = ((list_config->y_pos_map2 != NULL) ? list_config->y_pos_map2 : y_temp2);
    loop->scale_map = ((list_config->scale_map != NULL) ? list_config->scale_map : s_temp);
}

/*******************************************
**
**对listview进行排版，移动
**
********************************************/

/*******************************数据接口************************************/
short gui_surface_layout_loop_get_item_id(gui_surface_struct *surface, short index)
{
    gui_box_struct *box = gui_surface_layout_loop_get_item(surface, index);
    return (box != NULL) ? box->id : 0;
}

gui_box_struct *gui_surface_layout_loop_get_item(gui_surface_struct *surface, short index)
{
    gui_box_struct *box = surface->child;

    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL && box->visible)
        {
            if (box->layout_index == index)
            {
                return box;
            }
        }
        box = box->brother;
    }
    return NULL;
}

short gui_surface_layout_loop_get_item_index(gui_surface_struct *surface, gui_touch_point_struct *touch_point)
{
    gui_layout_loop_struct *loop = &surface->layout.loop;
    gui_box_struct *box = surface->child;
    geometry_rect box_rect = {0};

    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_CELL && box->visible)
        {
            gui_surface_box_get_geometry_rect(surface, box, &box_rect);
            if (check_rect_contain_point_xy(&box_rect, touch_point->x, touch_point->y)) {
                SYS_DEBUG("gui: layout_loop_get_item_index(x: %d, y: %d), id=%d, idx=%d", touch_point->x, touch_point->y, box->id, box->layout_index);
                return box->layout_index;
            }
        }
        box = box->brother;
    }
    return -1;
}

/*******************************操作接口************************************/

// 根据排版类型，进行排版
void gui_surface_layout_loop_arrange(gui_surface_struct *surface)
{
    const gui_layout_loop_struct *list_config = surface->screen->layout_config;
    gui_layout_loop_struct *loop = &surface->layout.loop;

    gui_surface_layout_loop_init(loop, list_config);
    loop->total = gui_surface_layout_loop_get_total(surface);
    gui_surface_layout_loop_commit_position(surface);
    gui_surface_layout_loop_set_offset(loop);
}

// 对排版中的子元素，使用指定的偏移
void gui_surface_layout_loop_offset(gui_surface_struct *surface, short layout_offset_x, short layout_offset_y)
{
    gui_layout_loop_struct *loop = &surface->layout.loop;
    loop->offset_x = layout_offset_x;
    loop->offset_y = layout_offset_y;
    SYS_DEBUG("gui: layout_loop_offset(off_x=%d, off_y=%d)", loop->offset_x, loop->offset_y);
    SYS_DEBUG("gui: layout_loop_offset(max_offset=%d, min_offset=%d)", loop->max_offset, loop->min_offset);
    if (loop->offset_y > (loop->max_offset + (2 * loop->row_height)))
    {
        SYS_DEBUG("loop->offset_y > (loop->max_offset");
        // loop->offset_y -= (loop->max_offset - loop->min_offset + (2 * loop->row_height));
        loop->offset_y = loop->min_offset-32;
    }
    else if (loop->offset_y < (loop->min_offset - (3 * loop->row_height)))
    {
        SYS_DEBUG("loop->offset_y < (loop->min_offset");
        // loop->offset_y += (loop->max_offset - loop->min_offset + (2 * loop->row_height));
        loop->offset_y = 0;
    }
    SYS_DEBUG("gui: layout_loop_offset(off_x=%d, off_y=%d)", loop->offset_x, loop->offset_y);
    gui_surface_layout_loop_commit_position(surface);
}

// 对排版中的子元素，进行指定的偏移
void gui_surface_layout_loop_move(gui_surface_struct *surface, short move_offset_x, short move_offset_y)
{
    gui_layout_loop_struct *loop = &surface->layout.loop;
    loop->offset_x += move_offset_x;
    loop->offset_y += move_offset_y;
    SYS_DEBUG("gui: layout_loop_move(off_x=%d, off_y=%d)", loop->offset_x, loop->offset_y);
    gui_surface_layout_loop_commit_position(surface);
}


void gui_surface_layout_loop_auto_scroll_step(gui_layout_position_tween_struct* layout_tween)
{
    gui_surface_layout_loop_offset(layout_tween->surface, layout_tween->curr_x, layout_tween->curr_y);
    gui_surface_force_update();
}

void gui_surface_layout_loop_auto_scroll_finish(gui_layout_position_tween_struct* layout_tween)
{
}

void gui_surface_layout_loop_switch_to_item(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
    if (gui_touch_layout_rebound_is_moving())
    {
        return;
    }

    gui_layout_loop_struct *loop = &surface->layout.loop;
    if (loop->height <= LCD_SIZE_HEIGHT)
        return;

    int offset_y = loop->offset_y;
    short move_y = 0;
    if (direction == DIRECTION_TYPE_UP)
    {
        offset_y += loop->item_gap;
        move_y = loop->item_gap;
    }
    else
    {
        offset_y -= loop->item_gap;
        move_y = -loop->item_gap;
    }

    short speed_y = move_y * 10; //( / 0.1f);
    if (gui_surface_layout_tween_position_is_running())
    {
        gui_layout_position_tween_struct* position_tween = gui_surface_layout_tween_position_get_tween();
        position_tween->mode = TWEEN_TYPE_LINEAR;
        position_tween->move_y = move_y;
        position_tween->speed_y += speed_y;
        position_tween->loop = 1;
        gui_surface_layout_tween_position_move(surface);
    }
    else
    {
        gui_layout_position_tween_struct* position_tween = gui_surface_layout_tween_position_init(surface);
        position_tween->mode = TWEEN_TYPE_LINEAR;
        position_tween->orientation = ORIENTATION_TYPE_VERTICAL;
        position_tween->scroll_step = gui_surface_layout_loop_auto_scroll_step;
        position_tween->scroll_finish = gui_surface_layout_loop_auto_scroll_finish;
        position_tween->min_y = loop->min_offset;
        position_tween->max_y = loop->max_offset;
        position_tween->loop = 1;
        position_tween->move_y = move_y;
        position_tween->speed_y = speed_y;
        gui_surface_layout_tween_position_start(surface);
    }
    //gui_surface_layout_loop_offset(surface,0,offset_y);
}

void gui_surface_layout_loop_exit(void)
{
}
