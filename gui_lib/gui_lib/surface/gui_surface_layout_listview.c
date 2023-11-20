#include "debug_info.h"
#include "math.h"
#include "feature_math.h"

#include "gui_surface_layout_listview.h"
#include "hal_lcd_area.h"
#include "system_util_math.h"
#include "gui_surface_box_layout_item.h"
#include "gui_surface_cache.h"
#include "gui_window_history.h"
#include "gui_touch_layout_rebound.h"
#include "gui_surface_box_scale.h"
#include "gui_surface_node_scale.h"

#include "gui_surface_layout.h"
#include "gui_surface_layout_tween_position.h"

#define LISTVIEW_AUTO_START_HEIGHT LCD_SIZE_HEIGHT

/************************************************************本地操作***************************************************************/

static void gui_surface_layout_listview_calculate_item_position_y(gui_layout_list_struct *list, float *y_top, float *y_bottom)
{
    if (list->zoom_flag) // 正常排列的点，与圆心连成一条斜线，在圆弧上的交点，投影到屏幕上
    {
        // delta_y1 是移动后以屏幕中心为原点的动态坐标
        short delta_y1 = LCD_SIZE_HALF_HEIGHT - ROUND_2(*y_top);
        short delta_y2 = LCD_SIZE_HALF_HEIGHT - ROUND_2(*y_bottom);

        unsigned int r2 = list->zoom_radius * list->zoom_radius;

        unsigned short y1_distance = math_sqrt_16(r2 + delta_y1 * delta_y1);
        float y1 = (float)(list->zoom_radius * delta_y1) / y1_distance; // 与圆弧相交的点的高度值
        *y_top = (LCD_SIZE_HALF_HEIGHT - y1);

        short y2_distance = math_sqrt_16(r2 + delta_y2 * delta_y2);
        float y2 = (float)(list->zoom_radius * delta_y2) / y2_distance; // 与圆弧相交的点的高度值
        *y_bottom = (LCD_SIZE_HALF_HEIGHT - y2);
    }
}

/// @brief
/// @param list
/// @param y_top 是以屏幕左上角为原点的动态坐标
/// @param y_bottom 是以屏幕左上角为原点的动态坐标
/// @return
static float gui_surface_layout_listview_get_item_position_center_y(gui_layout_list_struct *list, float *y_top, float *y_bottom)
{
    if (list->zoom_flag) // 正常排列的点，与圆心连成一条斜线，在圆弧上的交点，投影到屏幕上
    {
        gui_surface_layout_listview_calculate_item_position_y(list, y_top, y_bottom);
        *y_top *= list->zoom_scale;
        *y_bottom *= list->zoom_scale;
        return (*y_top + *y_bottom) / 2;
    }
    return (*y_top + *y_bottom) / 2;
}

static float gui_surface_layout_listview_get_item_position_scale(gui_layout_list_struct *list, float y_top, float y_bottom)
{
    return ABS(y_bottom - y_top) / list->row_height;
}

static float gui_surface_layout_listview_get_item_position_center_x(gui_layout_list_struct *list, float center_y, float *x_left, float *x_right)
{
    float center_x = (*x_left + *x_right) / 2;

    if (list->arc_flag)
    {
        float delta_y = LCD_SIZE_HALF_HEIGHT - center_y;
        if (list->arc_radius < delta_y)
            return center_x;

        unsigned int r2 = list->arc_radius * list->arc_radius;
        unsigned short distance = math_sqrt_16(r2 - delta_y * delta_y);
        short x_offset = list->arc_radius - distance;
        *x_left += x_offset;
        *x_right += x_offset;
        return center_x + x_offset;
    }
    return center_x;
}

static void gui_surface_layout_listview_drop_item_box(gui_surface_struct *surface)
{
    gui_box_struct *box = surface->child;
    gui_box_struct *start_box = NULL;
    gui_box_struct *end_box = NULL;
    gui_box_struct *curr_box = NULL;
    while (box != NULL)
    {
        curr_box = box;
        box = box->brother;
        if (curr_box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM && curr_box->will_drop == 1)
        {
            if (end_box != NULL)
                end_box->brother = NULL;
            gui_surface_cache_remove_box_and_children(curr_box);
        }
        else if (start_box == NULL)
        {
            start_box = curr_box;
            end_box = curr_box;
        }
        else
        {
            end_box->brother = curr_box;
            end_box = curr_box;
        }
    }
    surface->child = start_box;
}

static void gui_surface_layout_listview_init(gui_layout_list_struct *list, gui_layout_list_struct *list_config)
{
    memcpy(list, list_config, sizeof(gui_layout_list_struct));
    list->item_gap = list_config->row_height;
    list->offset_y = list->auto_start ? LISTVIEW_AUTO_START_HEIGHT : 0;
    if (list->zoom_flag)
    {
        if (list->zoom_scale == 0)
        {
            list->zoom_scale = 1;
        }
        float y_top = LCD_SIZE_HALF_HEIGHT - list_config->row_height / 2;
        float y_bottom = LCD_SIZE_HALF_HEIGHT + list_config->row_height / 2;
        gui_surface_layout_listview_calculate_item_position_y(list, &y_top, &y_bottom);
        list->zoom_scale *= list_config->row_height / ABS(y_bottom - y_top);
    }
}

static void gui_surface_layout_listview_calculate_item_position(gui_surface_struct *surface, gui_box_struct *box, unsigned char box_exist)
{
    gui_layout_list_struct *list = &surface->layout.list;

    short y_top_orgin = list->top + (list->row_height + list->space) * list->total;
    short y_bottom_orgin = y_top_orgin + list->row_height;

    float y_top = y_top_orgin + list->offset_y;
    float y_bottom = y_bottom_orgin + list->offset_y;

    float center_y = gui_surface_layout_listview_get_item_position_center_y(list, &y_top, &y_bottom);
    if (list->arc_flag || list->zoom_flag)
        box->y = center_y; // 要从中心点，因为后面有放大缩小，放大缩小都是以锚点为中心
    else
        box->y = y_top;

    if ((y_bottom >= 0 && y_top <= LCD_SIZE_HEIGHT) || box->will_drop == 0)
    {
        float x_left = box->x;
        float x_right = x_left + box->width;
        float center_x = gui_surface_layout_listview_get_item_position_center_x(list, center_y, &x_left, &x_right);

        if (list->arc_flag || list->zoom_flag)
            box->x = center_x; // 要从中心点，因为后面有放大缩小，放大缩小都是以锚点为中心
        else
            box->x = x_left;

        if (!box_exist)
        {
            gui_surface_box_layout_item_create(box);
            gui_surface_add_box(surface, box);
        }

        box->scale = gui_surface_layout_listview_get_item_position_scale(list, y_top, y_bottom);

        // 缩放到0的话，就直接删除掉
        if (box->scale > EPSILON)
        {
            box->will_drop = 0;
        }
    }
    else if (!box_exist) // 加入进来，没有加到树上的，删除掉
    {
        gui_surface_cache_remove_box_and_children(box);
    }
}

static void gui_surface_layout_listview_auto_scroll_step(gui_layout_position_tween_struct *layout_tween)
{
    gui_surface_layout_set_offset(layout_tween->surface, layout_tween->curr_x, layout_tween->curr_y);
    gui_surface_force_update();
}

static void gui_surface_layout_listview_auto_scroll_finish(gui_layout_position_tween_struct *layout_tween)
{
    gui_surface_layout_move_end(layout_tween->surface);
}

static void gui_surface_layout_listview_auto_start_timer(unsigned int timer, void *param)
{
    application_stop_user_timer(timer);

    gui_surface_struct *surface = (gui_screen_struct *)param;
    gui_layout_list_struct *list = &surface->layout.list;
    if (surface->screen->type == TYPE_GUI_LAYOUT_LIST && list->offset_y == LISTVIEW_AUTO_START_HEIGHT)
    {
        gui_layout_position_tween_struct *position_tween = gui_surface_layout_tween_position_init(surface);
        position_tween->mode = TWEEN_TYPE_QUADRATIC_OUT;
        position_tween->orientation = ORIENTATION_TYPE_VERTICAL;
        position_tween->scroll_step = gui_surface_layout_listview_auto_scroll_step;
        position_tween->scroll_finish = gui_surface_layout_listview_auto_scroll_finish;
        position_tween->min_y = list->min_offset;
        position_tween->max_y = list->max_offset;
        position_tween->move_y = -LISTVIEW_AUTO_START_HEIGHT;
        position_tween->speed_y = -LISTVIEW_AUTO_START_HEIGHT * 3 / 2;
        gui_surface_layout_tween_position_start(surface);
    }
}

static void gui_surface_layout_listview_auto_start(gui_surface_struct *surface)
{
    gui_layout_list_struct *list = &surface->layout.list;
    if (list->auto_start)
    {
        application_start_user_timer(1, gui_surface_layout_listview_auto_start_timer, surface);
    }
}

static void gui_surface_layout_listview_change_offset(gui_surface_struct *surface)
{
    gui_layout_list_struct *list = &surface->layout.list;
    if (list->height > LCD_SIZE_HEIGHT)
    {
        list->max_offset = 0;
        list->min_offset = -list->height + LCD_SIZE_HEIGHT;
    }
    else
    {
        list->max_offset = 0;
        list->min_offset = 0;
    }
}

/************************************************************数据接口***********************************************************************/

unsigned char gui_surface_layout_listview_is_delay_create_widget(const gui_screen_struct *screen, gui_widget_struct *widget)
{
    const gui_layout_list_struct *list_config = screen->layout_config;
    return (list_config != NULL) && list_config->clip && (widget->type == TYPE_GUI_CONTROL_LAYOUT_ITEM);
}

short gui_surface_layout_listview_get_item_id(gui_surface_struct *surface, short index)
{
    gui_box_struct *box = gui_surface_layout_listview_get_item(surface, index);
    return (box != NULL) ? box->id : 0;
}

gui_box_struct *gui_surface_layout_listview_get_item(gui_surface_struct *surface, short index)
{
    gui_box_struct *box = surface->child;
    short count = 0;
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM && box->visible)
        {
            if (count++ == index)
                return box;
        }
        box = box->brother;
    }
    return NULL;
}

short gui_surface_layout_listview_get_item_index(gui_surface_struct *surface, gui_touch_point_struct *touch_point)
{
    gui_layout_list_struct *list = &surface->layout.list;
    gui_box_struct *box = surface->child;
    geometry_rect rect_box;
    short count = 0;
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM && box->visible)
        {
            gui_surface_box_get_geometry_rect(surface, box, &rect_box);
            if (check_rect_contain_point_xy(&rect_box, touch_point->x, touch_point->y)) {
                return count;
            }
            count++;
        }
        box = box->brother;
    }
    return -1;
}

short gui_surface_layout_listview_get_progress(gui_surface_struct *surface)
{
    gui_layout_list_struct *list = &surface->layout.list;
    short progress;
    if (list->height <= LCD_SIZE_HEIGHT) // 20220519 Taylor.Le,  avoid div0
        progress = 100;
    else
        progress = ABS(list->offset_y) * 100 / (list->height - LCD_SIZE_HEIGHT);
    return math_range(progress, 0, 100);
}

/****************************************************编码器滚动*********************************************************/

void gui_surface_layout_listview_switch_to_item(gui_surface_struct *surface, DIRECTION_TYPE direction)
{
    if (gui_touch_layout_rebound_is_moving())
        return;

    gui_layout_list_struct *list = &surface->layout.list;
    if (list->height <= LCD_SIZE_HEIGHT)
        return;

    int offset_y = list->offset_y;
    short move_y = 0;
    if (direction == DIRECTION_TYPE_UP)
    {
        offset_y += list->item_gap;
        move_y = list->item_gap;
    }
    else
    {
        offset_y -= list->item_gap;
        move_y = -list->item_gap;
    }

    short speed_y = gui_surface_layout_tween_position_calculate_speed(move_y);
    if (gui_surface_layout_tween_position_is_running())
    {
        gui_layout_position_tween_struct *position_tween = gui_surface_layout_tween_position_get_tween();
        position_tween->mode = TWEEN_TYPE_LINEAR;
        position_tween->move_y = move_y;
        position_tween->speed_y += speed_y;
        gui_surface_layout_tween_position_move(surface);
    }
    else
    {
        gui_layout_position_tween_struct *position_tween = gui_surface_layout_tween_position_init(surface);
        position_tween->mode = TWEEN_TYPE_LINEAR;
        position_tween->orientation = ORIENTATION_TYPE_VERTICAL;
        position_tween->scroll_step = gui_surface_layout_listview_auto_scroll_step;
        position_tween->scroll_finish = gui_surface_layout_listview_auto_scroll_finish;
        position_tween->min_y = list->min_offset;
        position_tween->max_y = list->max_offset;
        position_tween->move_y = move_y;
        position_tween->speed_y = speed_y;
        gui_surface_layout_tween_position_start(surface);
    }
}

/***************************************************动态增加接口****************************************************************/

void gui_surface_layout_listview_dynamic_create(gui_surface_struct *surface, void (*refresh)(void))
{
    const gui_layout_list_struct *list_config = surface->screen->layout_config;
    gui_layout_list_struct *list = &surface->layout.list;
    gui_surface_layout_listview_init(list, list_config);
    gui_surface_layout_listview_clear_item_box(surface);
    list->dynamic_refresh = refresh;
    if (list->dynamic_refresh)
    {
        list->dynamic_refresh();
        gui_surface_force_update();
    }
    gui_surface_layout_listview_auto_start(surface);
}

void gui_surface_layout_listview_dynamic_init(gui_surface_struct *surface)
{
    gui_layout_list_struct *list = &surface->layout.list;
    list->total = 0;
    list->height = 0;
}

void gui_surface_layout_listview_dynamic_clear_delay(gui_surface_struct *surface)
{
    gui_box_struct *box = surface->child;
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
            box->will_drop = 1;
        box = box->brother;
    }
}

gui_box_struct *gui_surface_layout_listview_dynamic_get_box(gui_surface_struct *surface, short id)
{
    gui_box_struct *box = surface->child;
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM && box->id == id)
            return box;
        box = box->brother;
    }
    return gui_surface_cache_add_box();
}

unsigned char gui_surface_layout_listview_dynamic_exist(gui_surface_struct *surface, gui_box_struct *box)
{
    return box->child != NULL;
}


void gui_surface_layout_listview_dynamic_add_item(gui_surface_struct *surface, gui_box_struct *box)
{
    gui_layout_list_struct *list = &surface->layout.list;
    if (box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM && box->visible == 1)
    {
        box->will_drop = 1;
        box->layout_index = list->total;
        unsigned char box_exist = gui_surface_layout_listview_dynamic_exist(surface, box);
        gui_surface_layout_listview_calculate_item_position(surface, box, box_exist);
        list->total++;
    }
}

void gui_surface_layout_listview_dynamic_finish(gui_surface_struct *surface)
{
    gui_surface_layout_listview_drop_item_box(surface);

    gui_layout_list_struct *list = &surface->layout.list;
    list->height = list->top + list->total * (list->row_height + list->space) - list->space + list->bottom;

    gui_surface_layout_listview_change_offset(surface);
}

/*****************************************静态列表******************************************************/

// 在提交静态列表的结构前，对位置整理
static void gui_surface_layout_listview_commit_position(gui_surface_struct *surface)
{
    gui_screen_struct *screen = surface->screen;
    if (screen == NULL || screen->child_num == 0)
        return;

    gui_layout_list_struct *list = &surface->layout.list;
    list->total = 0;

    gui_box_struct *box = surface->child;
    while (box != NULL)
    {
        if (box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM && box->visible == 1)
        {
            box->will_drop = 0;
            box->layout_index = list->total;
            gui_surface_layout_listview_calculate_item_position(surface, box, box->child != NULL);
            list->total++;
        }
        box = box->brother;
    }

    list->height = list->top + list->total * (list->row_height + list->space) - list->space + list->bottom;
    gui_surface_layout_listview_change_offset(surface);
}

// 根据排版类型，进行排版
void gui_surface_layout_listview_arrange(gui_surface_struct *surface)
{
    const gui_layout_list_struct *list_config = surface->screen->layout_config;
    gui_layout_list_struct *list = &surface->layout.list;
    gui_surface_layout_listview_init(list, list_config);
    gui_surface_layout_listview_updata_arrange(surface);
    gui_surface_layout_listview_auto_start(surface);
}

/*********************************************操作接口********************************************************/

// 更新排版
void gui_surface_layout_listview_updata_arrange(gui_surface_struct *surface)
{
    gui_layout_list_struct *list = &surface->layout.list;
    if (list->dynamic_refresh)
        list->dynamic_refresh();
    else
        gui_surface_layout_listview_commit_position(surface);
}

void gui_surface_layout_listview_updata_progress(gui_surface_struct *surface)
{
    gui_window_history_struct *top = gui_window_history_get_top();
    gui_layout_value_struct event =
        {
            .list.progress = gui_surface_layout_listview_get_progress(surface), // 0-100
        };
    if (top != NULL && top->window && top->window->layout_value_changed)
    {
        top->window->layout_value_changed(&event);
    }
}

// 对排版中的子元素，使用指定的偏移
void gui_surface_layout_listview_offset(gui_surface_struct *surface, short layout_offset_x, short layout_offset_y)
{
    gui_layout_list_struct *list = &surface->layout.list;
    list->offset_x = layout_offset_x;
    list->offset_y = layout_offset_y;
    gui_surface_layout_listview_updata_arrange(surface);
    gui_surface_layout_listview_updata_progress(surface);
}

void gui_surface_layout_listview_clear_item_box(gui_surface_struct *surface)
{
    gui_layout_list_struct *list = &surface->layout.list;
    list->total = 0;
    list->height = 0;

    gui_box_struct *box = surface->child;
    while (box != NULL)
    {
        box->will_drop = (box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM);
        box = box->brother;
    }
    gui_surface_layout_listview_drop_item_box(surface);
}
