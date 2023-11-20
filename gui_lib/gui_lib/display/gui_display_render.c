#include "gui_display_render.h"
#include "gui_display_render_cache.h"
#include "gui_display_render_g2d.h"
#include "gui_display_draw_lib.h"
#include "os/os_api.h"

static gui_frame_struct g_frame_data = {0};
static gui_frame_struct *g_frame = &g_frame_data;

#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3

static gui_frame_struct g_frame_1_data = {0};
static gui_frame_struct *g_frame_for_render = &g_frame_1_data;

static gui_frame_struct g_frame_2_data = {0};
static gui_frame_struct *g_frame_for_swap = &g_frame_2_data;

static OS_MUTEX g_task_render_mutex;
void gui_display_render_init_data(void)
{
    os_mutex_create(&g_task_render_mutex);
}

void gui_display_render_switch_to_node()
{
    os_mutex_pend(&g_task_render_mutex, OS_MAX_DELAY);
    swap_front_back((void **)&g_frame, (void **)&g_frame_for_swap);
    gui_display_render_clear();
    g_frame_for_swap->swap = 1;
    os_mutex_post(&g_task_render_mutex);
}

void gui_display_render_switch_to_render()
{
    os_mutex_pend(&g_task_render_mutex, OS_MAX_DELAY);
    if (g_frame_for_swap->swap == 1)
    {
        g_frame_for_swap->swap = 0;
        swap_front_back((void **)&g_frame_for_swap, (void **)&g_frame_for_render);
        g_frame_for_swap->swap = 0;
    }
    os_mutex_post(&g_task_render_mutex);
}
#endif

void gui_display_render_init(void)
{
    gui_display_render_memory_init();

    memset(&g_frame_data, 0, sizeof(gui_frame_struct));
    g_frame_data.list = gui_display_render_cache_get_list();
    g_frame = &g_frame_data;

#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
    memset(&g_frame_1_data, 0, sizeof(gui_frame_struct));
    g_frame_1_data.list = gui_display_render_cache_get_list_1();
    g_frame_for_render = &g_frame_1_data;

    memset(&g_frame_2_data, 0, sizeof(gui_frame_struct));
    g_frame_2_data.list = gui_display_render_cache_get_list_2();
    g_frame_for_swap = &g_frame_2_data;
#endif
}

void gui_display_render_deinit(void)
{
    gui_display_render_memory_deinit();
    memset(&g_frame_data, 0, sizeof(gui_frame_struct));
#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
    memset(&g_frame_1_data, 0, sizeof(gui_frame_struct));
    memset(&g_frame_2_data, 0, sizeof(gui_frame_struct));
#endif
}

// 提供给组织模块用于创建渲染体(组织链表)
static gui_render_struct *gui_display_render_create()
{
    gui_render_struct *render = gui_display_render_cache_get(g_frame->list);
    if (render != NULL)
    {
        if (g_frame->frist == NULL)
            g_frame->frist = render;
        else
            g_frame->end->next = render;
        g_frame->end = render;
        g_frame->count++;
    }
    return render;
}

// 提供给渲染模块使用的接口
gui_render_struct *gui_display_render_frist()
{
#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
    return g_frame_for_render->frist;
#else
    return g_frame->frist;
#endif
}

void gui_display_render_clear()
{
    g_frame->count = 0;
    g_frame->swap = 0;
    g_frame->frist = NULL;
    g_frame->end = NULL;
    g_frame->update = 0;
    gui_display_render_cache_clear(g_frame->list);
}

static void gui_display_render_check_item_in_screen(gui_scale_item_struct *item, gui_scale_item_struct *surface_scale)
{
    short surface_x = surface_scale->clip_x + surface_scale->x;
    short surface_y = surface_scale->clip_y + surface_scale->y;

    if (item->clip_left < surface_x)
        item->clip_left = surface_x;
    if (item->clip_top < surface_y)
        item->clip_top = surface_y;
    if (item->clip_right >= (surface_x + surface_scale->clip_width))
        item->clip_right = surface_x + surface_scale->clip_width - 1;
    if (item->clip_bottom >= (surface_y + surface_scale->clip_height))
        item->clip_bottom = surface_y + surface_scale->clip_height - 1;

    if (item->clip_left < 0)
        item->clip_left = 0;
    if (item->clip_top < 0)
        item->clip_top = 0;
    if (item->clip_right >= (LCD_SIZE_WIDTH))
        item->clip_right = LCD_SIZE_WIDTH - 1;
    if (item->clip_bottom >= (LCD_SIZE_HEIGHT))
        item->clip_bottom = LCD_SIZE_HEIGHT - 1;
}

static void gui_display_render_check_in_screen(gui_render_struct *render, gui_scale_struct *gui_scale)
{
    gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);

    short surface_x = surface_scale->clip_x + surface_scale->x;
    short surface_y = surface_scale->clip_y + surface_scale->y;

    if (render->clip_left < surface_x)
        render->clip_left = surface_x;
    if (render->clip_top < surface_y)
        render->clip_top = surface_y;
    if (render->clip_right >= (surface_x + surface_scale->clip_width))
        render->clip_right = surface_x + surface_scale->clip_width - 1;
    if (render->clip_bottom >= (surface_y + surface_scale->clip_height))
        render->clip_bottom = surface_y + surface_scale->clip_height - 1;

    if (render->clip_left < 0)
        render->clip_left = 0;
    if (render->clip_top < 0)
        render->clip_top = 0;
    if (render->clip_right >= (LCD_SIZE_WIDTH))
        render->clip_right = LCD_SIZE_WIDTH - 1;
    if (render->clip_bottom >= (LCD_SIZE_HEIGHT))
        render->clip_bottom = LCD_SIZE_HEIGHT - 1;
}

// 创建并设置渲染体
void gui_display_render_add(gui_scale_struct *gui_scale)
{
    gui_surface_struct *surface = gui_scale->surface;
    gui_box_struct *box = gui_scale->box;
    gui_node_struct *node = gui_scale->node;

    gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);
    gui_scale_item_struct *box_scale = &(gui_scale->box_scale);
    gui_scale_item_struct *node_scale = &(gui_scale->node_scale);

    short surface_x = surface_scale->clip_x + surface_scale->x;
    short surface_y = surface_scale->clip_y + surface_scale->y;

    node_scale->left = node_scale->x + box_scale->x + surface_x;
    node_scale->top = node_scale->y + box_scale->y + surface_y;
    node_scale->right = node_scale->left + node_scale->width - 1;
    node_scale->bottom = node_scale->top + node_scale->height - 1;

    node_scale->clip_left = node_scale->clip_x + node_scale->left;
    node_scale->clip_top = node_scale->clip_y + node_scale->top;
    node_scale->clip_right = node_scale->clip_left + node_scale->clip_width - 1;
    node_scale->clip_bottom = node_scale->clip_top + node_scale->clip_height - 1;

    gui_display_render_check_item_in_screen(node_scale, surface_scale);

    if (node->type == TYPE_GUI_DRAW_NONE || node->type == TYPE_GUI_DRAW_PICTURE_BOX || node->type == TYPE_GUI_DRAW_TEXT_BOX)
        return;

    gui_render_struct *render = gui_display_render_create();
    if (render != NULL)
    {
        render->window_owner = surface->window;
        render->alpha = box->alpha;
        render->type = node->type;
        render->value = node->value;

        if (FLOAT_EQUAL_ONE(node_scale->scale))
            render->scale = 1.0f;
        else
            render->scale = node_scale->scale;

        render->x = node_scale->left;
        render->y = node_scale->top;
        render->width = node_scale->width;
        render->height = node_scale->height;

        render->clip_left = node_scale->clip_left;
        render->clip_top = node_scale->clip_top;
        render->clip_right = node_scale->clip_right;
        render->clip_bottom = node_scale->clip_bottom;

        render->data = node->data;
    }
}

// 创建并设置渲染体
void gui_display_render_add_compose(gui_scale_struct *gui_scale)
{
    gui_surface_struct *surface = gui_scale->surface;
    gui_box_struct *box = gui_scale->box;
    gui_node_struct *node = gui_scale->node;
    gui_node_struct *compose = gui_scale->compose;

    gui_scale_item_struct *surface_scale = &(gui_scale->surface_scale);
    gui_scale_item_struct *box_scale = &(gui_scale->box_scale);
    gui_scale_item_struct *node_scale = &(gui_scale->node_scale);
    gui_scale_item_struct *compose_scale = &(gui_scale->compose_scale);

    short surface_x = surface_scale->clip_x + surface_scale->x;
    short surface_y = surface_scale->clip_y + surface_scale->y;

    compose_scale->left = compose_scale->x + node_scale->x + box_scale->x + surface_x;
    compose_scale->top = compose_scale->y + node_scale->y + box_scale->y + surface_y;
    compose_scale->right = compose_scale->left + compose_scale->width - 1;
    compose_scale->bottom = compose_scale->top + compose_scale->height - 1;

    compose_scale->clip_left = compose_scale->clip_x + compose_scale->left;
    compose_scale->clip_top = compose_scale->clip_y + compose_scale->top;
    compose_scale->clip_right = compose_scale->clip_left + compose_scale->clip_width - 1;
    compose_scale->clip_bottom = compose_scale->clip_top + compose_scale->clip_height - 1;


    if (box->widget->clip)
    {
        if (compose_scale->clip_left < node_scale->left)
            compose_scale->clip_left = node_scale->left;
        if (compose_scale->clip_top < node_scale->top)
            compose_scale->clip_top = node_scale->top;
        if (compose_scale->clip_right > node_scale->right)
            compose_scale->clip_right = node_scale->right;
        if (compose_scale->clip_bottom > node_scale->bottom)
            compose_scale->clip_bottom = node_scale->bottom;
    }
    gui_display_render_check_item_in_screen(compose_scale, surface_scale);

    if (compose->type == TYPE_GUI_DRAW_NONE || compose->type == TYPE_GUI_DRAW_PICTURE_BOX || compose->type == TYPE_GUI_DRAW_TEXT_BOX)
        return;

    gui_render_struct *render = gui_display_render_create();
    if (render != NULL)
    {
        render->window_owner = surface->window;
        render->alpha = box->alpha;
        render->type = compose->type;
        render->value = compose->value;

        if (FLOAT_EQUAL_ONE(render->scale))
            render->scale = 1.0f;
        else
            render->scale = compose_scale->scale;

        render->x = compose_scale->left;
        render->y = compose_scale->top;
        render->width = compose_scale->width;
        render->height = compose_scale->height;

        render->clip_left = compose_scale->clip_left;
        render->clip_top = compose_scale->clip_top;
        render->clip_right = compose_scale->clip_right;
        render->clip_bottom = compose_scale->clip_bottom;

        render->data = compose->data;
    }
}

void gui_display_render_clear_cache_images(gui_surface_struct *surface)
{
}
