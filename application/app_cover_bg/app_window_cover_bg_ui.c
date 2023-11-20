#include "app_window_cover_bg_ui.h"
#include "app_window_cover_bg_layout.h"

#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_window_swipe.h"
#include "gui_surface_box_canvas.h"

unsigned char app_window_cover_bg_ui_is_exist(gui_surface_struct *surface)
{
    gui_box_struct *box = gui_surface_get_box_by_id(surface, GUI_IDS_COVER_BG);
    return box != NULL;
}

void app_window_cover_bg_ui_create(gui_surface_struct *surface)
{
    gui_box_struct *box = gui_surface_get_box_by_id(surface, GUI_IDS_COVER_BG);
    if (box == NULL)
    {
        box = gui_surface_box_create(surface, &gui_widget_cover_bg);
        box->order = -1;
        gui_surface_add_box(surface, box);
    }
}

void app_window_cover_bg_ui_move(gui_surface_struct *surface, unsigned char direction)
{
    float progress = 0;
    if (direction == DIRECTION_TYPE_UP || direction == DIRECTION_TYPE_DOWN)
    {
        progress = (float)ABS(surface->y) / LCD_SIZE_HEIGHT;
    }
    else if (direction == DIRECTION_TYPE_LEFT || direction == DIRECTION_TYPE_RIGHT)
    {
        progress = (float)ABS(surface->x) / LCD_SIZE_WIDTH;
    }
    gui_canvas_cover_bg_rect.opacity = math_range(5 + progress * 100, 0, 100);
    gui_surface_force_update();
}

void app_window_cover_bg_ui_end(gui_surface_struct *surface)
{
    gui_box_struct *box = gui_surface_get_box_by_id(surface, GUI_IDS_COVER_BG);
    if (box != NULL)
    {
        gui_surface_remove_box(surface, box);
        gui_surface_cache_remove_box_and_children(box);
    }
}