#include "app_window_lowpower_ui.h"
#include "app_window_lowpower_layout.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"

#include "application.h"
#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

void app_window_lowpower_show_text(app_battery_info_struct *batt_info)
{
    gui_box_struct *box = gui_surface_get_box((gui_screen_struct *)&gui_screen_lowpower, LOWPOWER_LAYOUT_ID_TEXT);
    if (box != NULL)
    {
        if (SYS_MODE_NORMAL_TYPE == get_system_mode())
        {
            gui_surface_box_label_change_string_id(box, STRING_LOW_POWER_ALARM);
        }
        else
        {
            char buff[16];
            sprintf(buff, "%d%%", get_battery_capacity());
            gui_surface_box_label_change_string(box, (unsigned char *)buff);
        }
    }
}

void app_window_lowpower_show_image(app_battery_info_struct *batt_info)
{
    gui_box_struct *box = gui_surface_get_box((gui_screen_struct *)&gui_screen_lowpower, LOWPOWER_LAYOUT_ID_IMAGE);
    if (box != NULL)
    {
        if (batt_info->charger == 0)
        {
            gui_surface_box_image_change(box, (const picture_info_struct *)&pic_low_power_info);
        }
        else
        {
            gui_surface_box_image_change(box, (const picture_info_struct *)&pic_charger_info);
        }
    }
}
