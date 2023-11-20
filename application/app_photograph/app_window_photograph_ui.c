#include "app_window_photograph.h"
#include "app_window_photograph_ui.h"
#include "app_window_photograph_layout.h"


#include "debug_info.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "arithmetic_steps.h"
#include "data_receive_package.h"

#include "gui_window.h"


#include "app_widget/app_window_widget_delete.h"

static uint32_t m_last_time = 0;

void app_window_photograph_ui_show()
{
    gui_box_struct *box;

    if (0 == get_ble_appconnect())
    {

        m_last_time = HAL_GetTickMS();
        shake_set_onoff(1);

        box = gui_surface_get_box(&app_photo_layout_screen, 5);
        if (box != NULL)
        {
            gui_surface_box_change_visible(box, 1);
        }
        box = gui_surface_get_box(&app_photo_layout_screen, PHOTOGRAPH_ID_YES);
        if (box != NULL)
        {
            gui_surface_box_change_visible(box, 0);
        }
    }
    else
    {
        box = gui_surface_get_box(&app_photo_layout_screen, 5);
        if (box != NULL)
        {
            gui_surface_box_change_visible(box, 0);
        }
        box = gui_surface_get_box(&app_photo_layout_screen, PHOTOGRAPH_ID_YES);
        if (box != NULL)
        {
            gui_surface_box_change_visible(box, 1);
        }
    }
    gui_surface_commit();
}
