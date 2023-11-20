#include "app_window_no_wear_ui.h"
#include "app_window_no_wear_layout.h"
#include "app_window_no_wear.h"

#include "gui_surface_box_image_number.h"
#include "gui_surface_box_label.h"
#include "application_titlebar.h"

static unsigned char g_no_wear_ui_no_ani_count = 0;

void app_window_no_wear_ui_show_ani()
{
    short count = 1000 / NO_WEAR_ANI_INTERVAL;
    if (g_no_wear_ui_no_ani_count >= count)
        g_no_wear_ui_no_ani_count = 0;

    gui_box_struct *box;
    box = gui_surface_get_box(&app_no_wear_screen, (unsigned short)NO_WEAR_LAYOUT_ROUND_ID);
    if (box != NULL && (g_no_wear_ui_no_ani_count == 0 || g_no_wear_ui_no_ani_count == count / 2))
        box->visible = !box->visible;

    box = gui_surface_get_box(&app_no_wear_screen, (unsigned short)NO_WEAR_LAYOUT_ARROW_ID);
    if (box != NULL)
        gui_surface_box_change_x(box, (g_no_wear_ui_no_ani_count % 2 == 0) ? (box->x + 3) : (box->x - 3));

    g_no_wear_ui_no_ani_count++;
}

void app_window_no_wear_ui_show()
{
    g_no_wear_ui_no_ani_count = 0;
    app_window_no_wear_ui_show_ani();
}
