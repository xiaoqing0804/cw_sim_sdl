
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

#include "app_window_call.h"
#include "app_window_call_ui.h"
#include "app_window_call_layout.h"
#include "picture.h"

#include "application_titlebar.h"

//****************************************************call****************************************************//
static void app_phone_type_note_hint(void)
{
	gui_box_struct* reply = gui_surface_get_box(&app_call_screen, CALL_REPLY);
	if (reply != NULL)
	{
      if(g_phone_type)
      {
          gui_surface_box_change_visible(reply, 0);
          gui_box_struct* hangup = gui_surface_get_box(&app_call_screen, CALL_HANGUP);
          if (reply != NULL)
          {
              gui_surface_box_image_change(hangup, &pic_missed_call_info);
              gui_surface_box_change_width(hangup, LCD_SIZE_WIDTH);
          }
      }
      else
      {
          gui_box_struct* hangup = gui_surface_get_box(&app_call_screen, CALL_HANGUP);
          gui_surface_box_image_change(hangup, &pic_no_little_info);
          gui_surface_box_change_x(hangup, 0);
          //gui_surface_box_change_width(hangup, 120);
          gui_surface_box_change_visible(reply, 1);
      }
	}
}

static void update_call_info(void)
{
    srv_call_info* call = srv_call_get_info(0);
    if (call != NULL) {
        gui_box_struct* box = gui_surface_get_box(&app_call_screen, CALL_INFO);
        if (box != NULL) {
            if (call->name_flag) {
                gui_surface_box_label_change_string(box, (unsigned char*)call->name);
            }
            else {
                gui_surface_box_label_change_string(box, (unsigned char*)call->number);
            }
        }
    }
}

/// @brief 显示电话号码
/// @param box
/// @param call
void app_call_info_function(void)
{
    update_call_info();
    app_phone_type_note_hint();
	application_titlebar_create(&app_call_screen, STRING_TELEPHONE);
    application_titlebar_hide_bg_from_screen(&app_call_screen);
}


//****************************************************call****************************************************//
