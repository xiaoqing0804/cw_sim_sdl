
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "app_task_main.h"

#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "data_manager_sensor.h"
#include "data_receive_package.h"

#include "application_titlebar.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"
#include "application.h"

#include "app_window_bp.h"
#include "app_window_bp_measur.h"
#include "app_window_bp_layout.h"

#include "app_widget/app_window_widget_delete.h"
#include "app_weather/app_window_wear.h"
#include "get_data.h"




static void app_bp_start_value(unsigned char spb_value,unsigned char dpb_value)
{
    gui_box_struct *box;
    char temp[40];

    box = gui_surface_get_box(&gui_screen_bp, (unsigned short)BP_SBP_VALUE_ID);
    if (box != NULL)
    {
        if (spb_value == 0)
        {
            gui_surface_box_label_change_string(box, "--/--");
        }
        else
        {
            sprintf(temp, "%d/%d", spb_value, dpb_value);
            gui_surface_box_label_change_string(box, (unsigned char *)temp);
        }
    }
       gui_box_struct *box_sbp = gui_surface_get_box(&gui_screen_bp, BP_BOX_ANI_RESET_ID);
        if(box_sbp != NULL)
        {
             box_sbp->visible = 1;
        }

}

// 进入bp数据展示界面
void ui_bp_value_start_updata(unsigned char spb_value,unsigned char dpb_value)
{

    app_bp_start_value(spb_value,dpb_value);

    gui_surface_commit();
}




static void bp_ready_visible(void)
{
    gui_box_struct *box;

    box = gui_surface_get_box(&gui_screen_bp, BP_SBP_VALUE_ID);
    if (box != NULL)
    {
        if (box->visible)
        {
            box->visible = 0;
        }
        else
        {
            gui_surface_box_label_change_string(box, "--/--");

            box->visible = 1;
        }
        gui_surface_commit();
    }

        box = gui_surface_get_box(&gui_screen_bp, BP_BOX_ANI_RESET_ID);
        if(box != NULL)
        {
             box->visible = 0;
        }



}

// 准备动画界面
void ui_bp_value_ready_updata(void)
{
    bp_ready_visible();

    gui_surface_commit();
}



static void app_bp_messung_value(unsigned char spb_value,unsigned char dpb_value)
{
    gui_box_struct *box;
    char temp[40];
    box = gui_surface_get_box(&gui_screen_bp, BP_SBP_VALUE_ID);
    if (box != NULL)
    {
        box->visible = 1;
        sprintf(temp, "%d/%d", spb_value, dpb_value);

        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }

}



// 测量出值界面
void ui_bp_value_messung_updata(unsigned char spb_value,unsigned char dpb_value)
{

    app_bp_messung_value(spb_value,dpb_value);
    gui_surface_commit();
}
