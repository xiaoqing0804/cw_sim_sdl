#include "app_window_findphone.h"
#include "app_window_findphone_ui.h"
#include "app_window_findphone_layout.h"

#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "bt_module.h"			// iPhone14查找手机死机问题

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"


#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_animation.h"
#include "application_config_main_window.h"






void app_window_findphone_ui_show()
{
    gui_box_struct* box;

    if (0 == get_ble_appconnect()) {
        SYS_DEBUG("app_window_findphone_load(0)");
        box = gui_surface_get_box(&app_findphone_screen, 1);
        if (box != NULL) {
            gui_surface_box_change_visible(box, 1);
        }
        box = gui_surface_get_box(&app_findphone_screen, 2);
        if (box != NULL) {
            gui_surface_box_change_visible(box, 0);
        }
        box = gui_surface_get_box(&app_findphone_screen, 3);
        if (box != NULL) {
            gui_surface_box_change_visible(box, 1);
        }
        box = gui_surface_get_box(&app_findphone_screen, 4);
        if (box != NULL) {
            gui_surface_box_change_visible(box, 0);
        }
    }
    else {
        SYS_DEBUG("app_window_findphone_load(1)");
        box = gui_surface_get_box(&app_findphone_screen, 1);
        if (box != NULL) {
            gui_surface_box_change_visible(box, 0);
        }
        box = gui_surface_get_box(&app_findphone_screen, 2);
        if (box != NULL) {
            gui_surface_box_change_visible(box, 1);
        }
        box = gui_surface_get_box(&app_findphone_screen, 3);
        if (box != NULL) {
            gui_surface_box_change_visible(box, 0);
        }
        box = gui_surface_get_box(&app_findphone_screen, 4);
        if (box != NULL) {
            gui_surface_box_change_visible(box, 1);
        }
    }
    gui_surface_commit();
}





