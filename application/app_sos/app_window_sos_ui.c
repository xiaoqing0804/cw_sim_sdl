
#include "service_call_out.h"
#include "gui_surface_box_label.h"

#include "app_window_sos_ui.h"
#include "app_window_sos_layout.h"


void app_window_sos_ui_show(void)
{
    gui_box_struct *box = gui_surface_get_box(&gui_screen_sos, SOS_LAYOUT_ID_SOS_NO_HELPER);
    if (box != NULL) {
        switch(service_call_get_sos_status()) {
            case 1:     // no-connect
                break;
            case 2:     // sos-off
                gui_surface_box_label_change_string(box, (unsigned char*)"SOS off");
                break;
            case 3:     // no-number
                gui_surface_box_label_change_string_id(box, STRING_NO_CONTACT);
                break;
            default:
                break;
        }
    }
}
