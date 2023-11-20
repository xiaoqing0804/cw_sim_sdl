#include "app_charger/app_window_charger.h"
#include "app_charger/app_window_charger_ui.h"
#include "app_charger/app_window_charger_layout.h"

#include "app_config.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "gui_surface_control_base.h"
#include "app_ota/app_window_ota.h"

#include "app_main/app_window_main_watchface_update.h"
///
static void app_window_charger_load_ui_show()

{
    time_struct time;
    char buff[16];
    sys_time_get(&time);

    app_battery_info_struct* batt_info = application_get_battery_info();
	//SYS_DEBUG("app_window_charger_change_value=%d",batt_info->percent);
    if(batt_info->percent==100)
    {   
    
        gui_box_struct* box = gui_surface_get_box(&gui_charger_screen,(unsigned short)CHRAGER_LAYOUT_TXT);
            if (box != NULL) {
            gui_surface_box_label_change_string_id(box, STRING_CHARGING_FULL);
        }
    }
}

///


    //特殊情况测试界面
    #if defined(TCFG_APP_PC_EN)&&TCFG_APP_PC_EN
static void app_window_charger_usb_update(unsigned char onoff)
{
    gui_box_struct* box;

    box = gui_surface_get_box(&gui_charger_screen, 10);
    if (box != NULL) {
        box->visible = 1;
    }

    box = gui_surface_get_box(&gui_charger_screen, 11);
    if (box != NULL) {
        box->visible = 1;
        if (onoff) {
            gui_surface_box_image_change(box, &pic_progress_bar_open_info);
        }
        else {
            gui_surface_box_image_change(box, &pic_progress_bar_shut_info);
        }
    }
}

static void app_window_charger_usb_click(gui_click_struct *event)
{
    unsigned char   onoff;

    SYS_DEBUG("test: app_window_charger_usb_click()");
    if (app_usb_running()) {
        app_usb_stop_req();
        onoff = 0;
    }
    else {
        app_usb_start_req();
        onoff = 1;
    }
    app_window_charger_usb_update(onoff);
    gui_surface_commit();
}

static const gui_touch_event_struct app_window_charger_touch_events[] =
{
    {.id = 11, .click = app_window_charger_usb_click, .offset_top = 15, .offset_bottom = 15}
};
#endif

#if defined(TCFG_APP_PC_EN)&&TCFG_APP_PC_EN
static void app_window_charger_on_timer(void* buf)
{
    application_close_act_timer(APPLICATION_TIMER_ACT);

    if (pc_app_check()) {
        app_window_charger_usb_update(app_usb_running());
        gui_surface_commit();
    }
}
static void app_window_mass_usb_offline(void* buf)
{
    gui_box_struct* box;

    box = gui_surface_get_box(&gui_charger_screen, 11);
    if (box != NULL) {
        gui_surface_box_image_change(box, &pic_progress_bar_shut_info);
        gui_surface_commit();
    }
    app_usb_stop_req();
}
#endif

    ///
