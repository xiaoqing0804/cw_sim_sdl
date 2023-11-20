#include "app_window_ota.h"
#include "app_window_ota_ui.h"
#include "app_window_ota_layout.h"

#include "picture.h"
#include "language.h"
#include "debug_info.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "ota.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image_number.h"

#include "application_config_main_window.h"

static unsigned int m_ota_sec = 0;

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_ota_ui_flag()
{
    gui_box_struct *box;
   
    char temp[20];
   
    snprintf(temp, sizeof(temp), "%d", ota_font_updata_check());
    box = gui_surface_get_box(&app_ota_screen_layout, 5);
    if (box != NULL)
    {
        gui_surface_box_image_number_change_string(box, (unsigned char *)temp);
    }
};
static void app_window_ota_ui_display_time()
{
   gui_box_struct *box;

    unsigned int pos, size, sec;
    char temp[20];

    ota_get_status(&size, &pos);
    if (size == 0)
        size = 1;
    if (pos > size)
        size = pos;
    
    sec = HAL_GetTickMS() - m_ota_sec;
    sec = sec / 1000;
    snprintf(temp, sizeof(temp), "%02d:%02d", sec / 60, sec % 60);
    box = gui_surface_get_box(&app_ota_screen_layout, 6);
    if (box != NULL)
    {
        gui_surface_box_image_number_change_string(box, (unsigned char *)temp);
    }
};
static void app_window_ota_ui_display_prograss()
{
    gui_box_struct *box;

    unsigned int pos, size, sec;
    char temp[20];

    ota_get_status(&size, &pos);
    if (size == 0)
        size = 1;
    if (pos > size)
        size = pos;

    if (0 == pos)
    {
        snprintf(temp, sizeof(temp), "......");
    }
    else
    {
        double value, value_pos, value_size;
        value_pos = (double)pos;
        value_size = (double)size;
        value = value_pos / value_size;
        value *= 100;
        snprintf(temp, sizeof(temp), "%.1f%%", value);
    }
    box = gui_surface_get_box(&app_ota_screen_layout, 7);
    if (box != NULL)
    {
        gui_surface_box_image_number_change_string(box, (unsigned char *)temp);
    }
};


void app_window_ota_ui_show()
{
    app_window_ota_ui_flag();
    app_window_ota_ui_display_time();
    app_window_ota_ui_display_prograss();
    gui_surface_commit();
}
