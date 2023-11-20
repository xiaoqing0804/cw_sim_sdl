#include "app_window_sos_setting_ui.h"
#include "app_window_sos_setting_layout.h"
#include "data_sos.h"

#include "gui_surface_box_image.h"

void app_window_sos_setting_ui_show_status()
{
    gui_box_struct *box = gui_surface_get_box(&gui_screen_sos_setting, SOS_SETTING_LAYOUT_ID_OPEN);

    if (data_sos_status_is_on())
        gui_surface_box_image_change(box, &pic_setting_list_status_open_info);
    else
        gui_surface_box_image_change(box, &pic_setting_list_status_close_info);
}

void app_window_sos_setting_ui_show()
{
    application_titlebar_create(&gui_screen_sos_setting, STRING_SOS);
    app_window_sos_setting_ui_show_status();
}
