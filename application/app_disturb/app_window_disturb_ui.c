#include "app_window_disturb.h"
#include "app_window_disturb_ui.h"
#include "app_window_disturb_layout.h"

#include "debug_info.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "data_receive_package.h"
#include "gui_window.h"

#include "application_titlebar.h"

#include "app_window_disturb_layout.h"

#include "app_quick/app_window_quick.h"

static void app_window_disturb_ui_show()
{
    application_titlebar_create(&gui_screen_disturb, STRING_DISTURB);

    char temp[40];
    if (g_forget_disturb.switch_flag)
        snprintf(temp, sizeof(temp), "%s", GUI_Get_ID_String(STRING_CLOSE_DISTURB_MODE));
    else
        snprintf(temp, sizeof(temp), "%s", GUI_Get_ID_String(STRING_DISTURB_MODE));

    gui_box_struct *disturb = gui_surface_get_box(&gui_screen_disturb, (unsigned short)DISTURB_LAYOUT_ID_TETX);
    gui_surface_box_label_change_string(disturb, (unsigned char *)temp);
}