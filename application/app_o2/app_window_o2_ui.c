#include "app_window_o2_ui.h"
#include "app_window_o2_layout.h"
#include "app_window_o2.h"
#include "gui_surface_box_image_number.h"


static void app_window_o2_ui_switch_to_result(unsigned char status)
{
    gui_box_struct *box;

    box = gui_surface_get_box(&app_o2_screen, (unsigned short)O2_LAYOUT_ID_RESULT_BG_1);
    if (box != NULL)
        box->visible = status;

    box = gui_surface_get_box(&app_o2_screen, (unsigned short)O2_LAYOUT_ID_RESULT_BG_2);
    if (box != NULL)
        box->visible = status;

    box = gui_surface_get_box(&app_o2_screen, (unsigned short)O2_LAYOUT_ID_RESULT_DATA);
    if (box != NULL)
        box->visible = status;

    box = gui_surface_get_box(&app_o2_screen, (unsigned short)O2_LAYOUT_ID_RESULT_RETRY);
    if (box != NULL)
        box->visible = status;
}

static void app_window_o2_ui_switch_to_start(unsigned char status)
{
    gui_box_struct *box;

    box = gui_surface_get_box(&app_o2_screen, (unsigned short)O2_LAYOUT_ID_START_BG);
    if (box != NULL)
        box->visible = status;

    box = gui_surface_get_box(&app_o2_screen, (unsigned short)O2_LAYOUT_ID_START_TIME);
    if (box != NULL)
        box->visible = status;
}

void app_window_o2_ui_switch(unsigned char status)
{
    app_window_o2_ui_switch_to_start(status == O2_STATUS_START);
    app_window_o2_ui_switch_to_result(status == O2_STATUS_RESULT);
}

void app_window_o2_ui_show_time(unsigned char time_number)
{
    gui_box_struct *box = gui_surface_get_box(&app_o2_screen, (unsigned short)O2_LAYOUT_ID_START_TIME);
    if (box != NULL)
        gui_surface_box_image_number_change_number(box, time_number);
}

void app_window_o2_ui_show_data(unsigned char number)
{
    gui_box_struct *box = gui_surface_get_box(&app_o2_screen, (unsigned short)O2_LAYOUT_ID_RESULT_DATA);
    if (box != NULL)
    {
        unsigned char buff[10] = {0};
        snprintf((char *)buff, 10, "%d%%", number);
        gui_surface_box_image_number_change_string(box, buff);
    }
}

void app_window_o2_ui_show(unsigned char status)
{
    application_titlebar_create(&app_o2_screen, STRING_O2);
    app_window_o2_ui_switch(status);
}
