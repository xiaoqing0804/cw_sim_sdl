#include "app_window_power_off_ui.h"
#include "app_window_power_off_layout.h"

void app_window_power_off_ui_slide(unsigned short id, short move_x)
{
    gui_box_struct *box_bg = gui_surface_get_box(&app_screen_power_off, id);
    gui_box_struct *box_icon = gui_surface_get_box(&app_screen_power_off, id + 1);
    gui_box_struct *box_text = gui_surface_get_box(&app_screen_power_off, id + 2);

    int width = box_bg->width - POWER_OFF_ICON_LEFT * 2;
    if (move_x >= 0 && move_x <= (width - box_icon->width))
    {
        gui_surface_box_change_x(box_icon, box_bg->x + POWER_OFF_ICON_LEFT + move_x);
    }
    box_text->visible = (move_x == 0);
}

unsigned char app_window_power_off_ui_is_slide_over(unsigned short id, short move_x)
{
    gui_box_struct *box_bg = gui_surface_get_box(&app_screen_power_off, id);
    gui_box_struct *box_icon = gui_surface_get_box(&app_screen_power_off, id + 1);
    int width = box_bg->width - POWER_OFF_ICON_LEFT * 2;

    // 预留一个box_icon的宽度
    return (move_x > (width - box_icon->width * 1.5f));
}
