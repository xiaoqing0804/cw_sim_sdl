#include "gui_window.h"
#include "gui_window_history.h"
#include "gui_window_history_cache.h"
#include "gui_surface.h"
#include "gui_surface_layout_scroll.h"
#include "gui_window_swipe.h"

/****************************************定义******************************************/
#define SWIPE_ZOOM_MIN_SCALE (0.4f) // 缩放时的最小值

static gui_window_swiping_struct g_gui_window_swiping = {0};

/****************************************私有静态******************************************/
void gui_window_swipe_deinit(void)  // 20230920 Taylor.Le, 
{
    memset(&g_gui_window_swiping,0,sizeof(g_gui_window_swiping));
}

static void gui_window_swipe_init(const gui_window_struct *window,const gui_window_struct *next_window,unsigned char direction)
{
    if (g_gui_window_swiping.next_window != NULL && g_gui_window_swiping.next_window != next_window)
        g_gui_window_swiping.next_window->destroy();

    g_gui_window_swiping.window = window;
    g_gui_window_swiping.next_window = next_window;
    g_gui_window_swiping.direction = direction;
}

static unsigned char gui_window_swipe_scale_is_disable(gui_surface_struct *surface)
{
    if (surface && surface->window && surface->window->config)
    {
        const gui_window_config_struct *config = surface->window->config;
        if (config->disable_scale)
            return 1;
    }
    return 0;
}

static void gui_window_swipe_scale_main_x(int main_offset_x)
{
    unsigned char is_disable = gui_window_swipe_scale_is_disable(gui_surface_get_main_surface());
    short offset_x = ABS(main_offset_x);
    if (offset_x == 0 || is_disable)
    {
        gui_surface_main_surface_scale_all(1.0f);
    }
    else
    {
        float scale = 1.0f - (float)offset_x / LCD_SIZE_WIDTH;
        scale = math_range_float(scale, 0.0f, 1.0f);
        scale = SWIPE_ZOOM_MIN_SCALE + (1.0f - SWIPE_ZOOM_MIN_SCALE) * scale;
        scale = math_range_float(scale, SWIPE_ZOOM_MIN_SCALE, 1.0f);
        gui_surface_main_surface_scale_all(scale);
    }
}

static void gui_window_swipe_scale_vice_x(int vice_offset_x)
{
    unsigned char is_disable = gui_window_swipe_scale_is_disable(gui_surface_get_vice_surface());
    short offset_x = ABS(LCD_SIZE_WIDTH - ABS(vice_offset_x));
    if (offset_x == 0 || is_disable)
    {
        gui_surface_vice_surface_scale_all(1.0f);
    }
    else
    {
        float scale = (float)offset_x / LCD_SIZE_WIDTH;
        scale = math_range_float(scale, 0.0f, 1.0f);
        scale = SWIPE_ZOOM_MIN_SCALE + (1.0f - SWIPE_ZOOM_MIN_SCALE) * scale;
        scale = math_range_float(scale, SWIPE_ZOOM_MIN_SCALE, 1.0f);
        gui_surface_vice_surface_scale_all(scale);
    }
}

/**********************************************执行**************************************************************/

/*显示副屏内容，一般是拖拽时触发，会显示双屏内容，也仅只是显示*/
void gui_window_swipe_start(const gui_window_struct *window,const gui_window_struct *next_window,unsigned char direction)
{
    gui_window_swipe_init(window, next_window, direction);

    gui_surface_clear_vice_surface();
    if (next_window != NULL)
    {
        gui_surface_create_vice_surface(next_window);

        if (next_window->init)
        {
            next_window->init(NULL);
            gui_window_history_set_inited_window(next_window);
        }
        if (next_window->load)
        {
            next_window->load(NULL);
            gui_window_history_set_loaded_window(next_window);
        }
        gui_surface_load_surface(); 
    }
    gui_surface_force_update();
    application_send_event(EVENT_SWIPE_START, NULL);
}

/*双屏在拖拽时显示*/
void gui_window_swipe_offset(int main_offset_x, int main_offset_y, int vice_offset_x, int vice_offset_y)
{
    gui_window_swipe_offset_main(main_offset_x, main_offset_y);
    gui_window_swipe_offset_vice(vice_offset_x, vice_offset_y);
}

void gui_window_swipe_offset_main(int main_offset_x, int main_offset_y)
{
    gui_surface_main_surface_move_to_x(main_offset_x);
    gui_surface_main_surface_move_to_y(main_offset_y);
}

void gui_window_swipe_offset_vice(int vice_offset_x, int vice_offset_y)
{
    gui_surface_vice_surface_move_to_x(vice_offset_x);
    gui_surface_vice_surface_move_to_y(vice_offset_y);
}

/*双屏在拖拽时显示缩放*/
void gui_window_swipe_scale(int main_offset_x, int vice_offset_x)
{
#if (GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_G2D) && GUI_SURFACE_ZOOM_SUPPORT
    if (main_offset_x == 0)
        gui_window_swipe_scale_main_x(0);
    else
        gui_window_swipe_scale_main_x(main_offset_x);

    if (vice_offset_x == 0)
        gui_window_swipe_scale_vice_x(0);
    else
        gui_window_swipe_scale_vice_x(vice_offset_x);
#endif
}

void gui_window_swipe_end()
{
    application_send_event(EVENT_SWIPE_END, NULL);

    gui_surface_swap_surface();
    gui_window_swipe_offset(0, 0, 0, 0);
    gui_surface_clear_vice_surface();
    gui_window_swipe_scale(0, 0);

    if (g_gui_window_swiping.next_window != NULL)
    {
        if (gui_window_history_replace(g_gui_window_swiping.next_window, GUI_WINDOW_TYPE_WINDOW, NULL))
        {
            gui_window_history_change_switch_mode(GUI_WINDOW_SWITCH_MODE_SWIPE);

            if (g_gui_window_swiping.next_window->entry)
                g_gui_window_swiping.next_window->entry(NULL);
        }
    }
    memset(&g_gui_window_swiping,0,sizeof(g_gui_window_swiping));

    //gui_surface_force_update();
    application_send_event(EVENT_GUI_RENDER_REQ, NULL);

    gui_window_history_set_inited_window(NULL);
    gui_window_history_set_loaded_window(NULL);
}

void gui_window_swipe_cancle()
{
    application_send_event(EVENT_SWIPE_CANCEL, NULL);

    if (g_gui_window_swiping.next_window != NULL)
    {
        g_gui_window_swiping.next_window->destroy();
    }
    memset(&g_gui_window_swiping, 0, sizeof(g_gui_window_swiping));

    gui_window_swipe_offset(0, 0, 0, 0);
    gui_surface_clear_vice_surface();
    gui_window_swipe_scale(0, 0);

    // rentry top window
    gui_window_history_rentry_top_window(); // 20221125 Taylor.Le,

    //gui_surface_force_update();
    application_send_event(EVENT_GUI_RENDER_REQ, NULL);

    gui_window_history_set_inited_window(NULL);
    gui_window_history_set_loaded_window(NULL);
}

const gui_window_struct *gui_window_swipe_get_vice(void) // 20230513 Taylor.Le, +  ui bug-fixed
{
    return &(g_gui_window_swiping.next_window);
}

gui_window_swiping_struct *gui_window_swipe_get_swiping(void)
{
    return &g_gui_window_swiping;
}

unsigned char gui_window_swipe_is_swiping(void)
{
    return g_gui_window_swiping.next_window != NULL;
}
