
#include "app_window_popup_yesno_ui.h"
#include "app_window_popup_yesno_layout.h"

void app_window_popup_yesno_ui_show_text(gui_popup_yesno_struct *popup_yesno)
{
    gui_box_struct *box = gui_surface_get_box(&gui_popup_yesno_screen, POPUP_YESNO_LAYOUT_ID_TITLE);
    if (box != NULL)
    {
        if (popup_yesno->text_type == GUI_FONT_VALUE_TYPE_STRING)
            gui_surface_box_label_change_string(box, (unsigned char *)popup_yesno->text);
        else if (popup_yesno->text_type == GUI_FONT_VALUE_TYPE_STRING_ID)
            gui_surface_box_label_change_string_id(box, popup_yesno->text);
    }
}