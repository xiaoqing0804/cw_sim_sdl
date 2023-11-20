#include "app_window_popup_warn_ui.h"
#include "app_window_popup_warn_layout.h"
#include "gui_surface_box_label.h"

void app_window_popup_warn_ui_show_text(gui_popup_warn_struct *popup_warn)
{
    gui_box_struct *box = gui_surface_get_box(&gui_screen_popup_warn, POPUP_WARN_LAYOUT_ID_INFO);
    if (box != NULL)
    {
        if (popup_warn->text_type == GUI_FONT_VALUE_TYPE_STRING)
            gui_surface_box_label_change_string(box, (unsigned char *)popup_warn->text);
        else if (popup_warn->text_type == GUI_FONT_VALUE_TYPE_STRING_ID)
            gui_surface_box_label_change_string_id(box, popup_warn->text);
    }
}

void app_window_popup_warn_ui_show(gui_popup_warn_struct *popup_warn)
{
    if (!popup_warn->no_title)
    {
        if (popup_warn->title > 0)
            application_titlebar_create(&gui_screen_popup_warn, popup_warn->title);
        else
            application_titlebar_create(&gui_screen_popup_warn, STRING_HINT);
    }
    app_window_popup_warn_ui_show_text(popup_warn);
}