#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "data_manager_message.h"

#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#include "data_manager_contact.h"
#endif

#include "srv_call.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_control_base.h"

#include "application_config_main_window.h"

#include "app_call/app_window_call.h"
#include "app_window_call_comming_layout.h"
#include "app_window_call_comming_ui.h"


//****************************************************call comming****************************************************//
/// @brief 判断安卓和ios手机链接（安卓显示短信恢复功能）
/// @param void
static void adjust_gui_elements(int g_phone_type)
{
    gui_box_struct *reject = gui_surface_get_box(&app_call_comming_screen, CALL_ING_REJECT);
    gui_box_struct *accept = gui_surface_get_box(&app_call_comming_screen, CALL_ING_ACCEPT);
    gui_box_struct *reply = gui_surface_get_box(&app_call_comming_screen, CALL_ING_REPLY);

    if (g_phone_type)
    {
        gui_surface_box_change_visible(reply, 0);
        gui_surface_box_image_change(reject, &pic_no_little_info);
        gui_surface_box_image_change(accept, &pic_yes_little_info);
        gui_surface_box_change_width(reject, 120);
        gui_surface_box_change_width(accept, 120);
    }
    else
    {
        gui_surface_box_image_change(reject, &pic_no_little_info);
        gui_surface_box_image_change(accept, &pic_yes_little_info);
        gui_surface_box_change_width(reject, 80);
        gui_surface_box_change_width(accept, 80);
        gui_surface_box_change_visible(reply, 1);
    }
}

/// @brief 显示通话界面是否显示联系人名字
/// @param void
static int app_window_call_update_info(void)
{
    gui_box_struct *box;
    srv_call_info *call = srv_call_get_info(0);
    if (call != NULL)
    {
        box = gui_surface_get_box(&app_call_comming_screen, CALL_ING_INFO);
        if (box != NULL)
        {
            if (call->number_flag && call->number_len != 0)
            {
                gui_surface_box_label_change_string(box, call->number);
            }
        }
        box = gui_surface_get_box(&app_call_comming_screen, CALL_ING_NEW_CALL);
        if (box != NULL)
        {
            if (call->name_flag && call->name_len != 0)
            {
                gui_surface_box_label_change_string(box, call->name);
            }
        }
    }
    else
    {
        SYS_DEBUG("app: call_update_info, call is null!!!");
    }

    gui_box_struct *reply = gui_surface_get_box(&app_call_comming_screen, CALL_ING_REPLY);
    if (reply != NULL)
    {
        adjust_gui_elements(g_phone_type);
    }
}

void app_window_call_number(void)
{
    app_window_call_update_info();
}

//****************************************************call comming****************************************************//

