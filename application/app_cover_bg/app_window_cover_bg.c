#include "app_window_cover_bg.h"
#include "app_window_cover_bg_ui.h"
#include "app_window_cover_bg_layout.h"

#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_window_swipe.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_cache.h"

void app_window_cover_bg_move(unsigned char direction)
{
    gui_surface_struct *surface = gui_surface_get_top_surface();
    if (surface != NULL)
    {
        if (app_window_cover_bg_ui_is_exist(surface))
            app_window_cover_bg_ui_move(surface, direction);
        else
            app_window_cover_bg_ui_create(surface);
    }
    gui_surface_force_update();
}

void app_window_cover_bg_end()
{
    gui_surface_struct *surface = gui_surface_get_top_surface();
    if (surface != NULL)
    {
        app_window_cover_bg_ui_end(surface);
        gui_surface_force_update();
    }
}