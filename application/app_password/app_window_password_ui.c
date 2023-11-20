#include "app_window_password_ui.h"
#include "app_window_password_layout.h"
#include "app_window_password_status.h"
#include "app_window_password_status.h"

static void app_window_password_ui_show_password_number(unsigned char visible)
{
    for (short i = 0; i < 4; i++)
    {
        gui_box_struct *box = gui_surface_get_box(&gui_screen_password, PASSWORD_NO_0 + i);
        if (box != NULL)
        {
            box->visible = visible;
        }
    }
}

static void app_window_password_ui_show_info(unsigned char error)
{
    gui_box_struct *box_info = gui_surface_get_box(&gui_screen_password, PASSWORD_INFO);
    if (box_info != NULL)
    {
        box_info->visible = 1;

        if (error == PASSWORD_ERROR_WRONG)
        {
            gui_surface_box_label_change_string_id(box_info, STRING_PASSWORD_WRONG);
        }
        else if (error == PASSWORD_ERROR_NO_MATCH)
        {
            gui_surface_box_label_change_string_id(box_info, STRING_PASSWORD_NO_MATCH);
        }
        else if (error == PASSWORD_ERROR_INPUT_CHAR)
        {
            gui_surface_box_label_change_string_id(box_info, STRING_PASSWORD_NEW);
        }
        else if (error == PASSWORD_ERROR_INPUT_CHAR_AGAIN)
        {
            gui_surface_box_label_change_string_id(box_info, STRING_PASSWORD_NEW_AGAIN);
        }
    }
    app_window_password_ui_show_password_number(0);
}

static void app_window_password_ui_show_password()
{
    unsigned char len = app_window_password_status_get_input_length();
    for (short i = 0; i < PASSWORD_STATUS_INPUT_TOTAL; i++)
    {
        gui_box_struct *box = gui_surface_get_box(&gui_screen_password, PASSWORD_NO_0 + i);
        if (box != NULL)
        {
            box->visible = 1;
            gui_surface_box_image_change(box, (i < len) ? &pic_password_yes_info : &pic_password_no_info);
        }
    }

    gui_box_struct *box_info = gui_surface_get_box(&gui_screen_password, PASSWORD_INFO);
    if (box_info != NULL)
    {
        box_info->visible = 0;
    }
}

void app_window_password_ui_show()
{
    unsigned char error = app_window_password_status_get_error();
    if (error == PASSWORD_ERROR_NONE)
    {
        app_window_password_ui_show_password();
    }
    else
    {
        app_window_password_ui_show_info(error);
    }
}
