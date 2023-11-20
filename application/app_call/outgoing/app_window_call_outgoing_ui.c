#include "app_window_call_outgoing_layout.h"
#include "app_window_call_outgoing_ui.h"

//****************************************************call outgoing****************************************************//
/// @brief 音量进度条显示
/// @param unsigned char flag
void app_call_volind_box_visible(unsigned char flag)
{
    gui_box_struct *box;
    box = gui_surface_get_box(&app_call_outgoing_screen, CALL_LAYOUT_VOLBG_ID);
    box->visible = flag;
    box = gui_surface_get_box(&app_call_outgoing_screen, CALL_LAYOUT_VOLIND_ID);
    box->visible = flag;
    box = gui_surface_get_box(&app_call_outgoing_screen, CALL_LAYOUT_VOLDN_ID);
    box->visible = flag;
    box = gui_surface_get_box(&app_call_outgoing_screen, CALL_LAYOUT_VOLUP_ID);
    box->visible = flag;
    gui_surface_commit();
}


//****************************************************call outgoing****************************************************//
