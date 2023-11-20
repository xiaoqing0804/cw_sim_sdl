#include "app_window_heartrate_ui.h"
#include "app_window_heartrate_layout.h"
#include "app_window_heartrate.h"

#include "gui_surface_box_image_number.h"
#include "gui_surface_box_label.h"
#include "application_titlebar.h"
#include "data_heartrate.h"

const picture_info_struct *g_heartrate_ui_icon_ani[] =
    {
        &pic_hr_gif_1_info,
        &pic_hr_gif_2_info,
        &pic_hr_gif_3_info,
        &pic_hr_gif_4_info,
        &pic_hr_gif_5_info,
        &pic_hr_gif_6_info,
        &pic_hr_gif_7_info,
        &pic_hr_gif_8_info,
        &pic_hr_gif_9_info,
        &pic_hr_gif_10_info,
};

static unsigned char g_heartrate_ui_count = 0;

void app_window_heartrate_ui_show_ani()
{
    if (g_heartrate_ui_count >= countof(g_heartrate_ui_icon_ani))
        g_heartrate_ui_count = 0;

    gui_box_struct *box = gui_surface_get_box(&app_heartrate_screen, (unsigned short)HR_BOX_CURR_ICON_ID);
    if (box != NULL)
        gui_surface_box_image_change(box, g_heartrate_ui_icon_ani[g_heartrate_ui_count]);

    g_heartrate_ui_count++;
}

void app_window_heartrate_ui_show_result()
{
    unsigned char buff[30] = {0};
    gui_box_struct *box;

    /**********************************************/
    box = gui_surface_get_box(&app_heartrate_screen, (unsigned short)HR_BOX_CURR_VALUE_ID);
    if (box != NULL)
    {
        short value = data_heartrate_get_curr_heartrate();
        if (value == 0)
            snprintf((char *)buff, 30, "--");
        else if (app_window_heartrate_get_status() == HEARTRATE_STATUS_START)
            snprintf((char *)buff, 30, "--");
        else
            snprintf((char *)buff, 30, "%d", value);
        gui_surface_box_label_change_string(box, buff);
    }

    box = gui_surface_get_box(&app_heartrate_screen, (unsigned short)HR_BOX_CURR_HISTORY_ID);
    if (box != NULL)
    {
        short value = data_heartrate_get_curr_heartrate_front();
        short time = data_heartrate_get_curr_heartrate_minutes();
        if (value == 0)
            snprintf((char *)buff, 30, "-- bpm (-- %s)", GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_TIME));
        else if (time >= 60)
            snprintf((char *)buff, 30, "%d bpm (%d %s)", value, time / 60, GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_HOUR));
        else
            snprintf((char *)buff, 30, "%d bpm (%d %s)", value, time, GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_TIME));
        gui_surface_box_label_change_string(box, buff);
    }

    /**********************************************/
    box = gui_surface_get_box(&app_heartrate_screen, (unsigned short)HR_BOX_RESTING_VALUE_ID);
    if (box != NULL)
    {
        short value = data_heartrate_get_resting_heartrate();
        if (value == 0)
            snprintf((char *)buff, 30, "--");
        else
            snprintf((char *)buff, 30, "%d", value);
        gui_surface_box_label_change_string(box, buff);
    }

    box = gui_surface_get_box(&app_heartrate_screen, (unsigned short)HR_BOX_RESTING_HISTORY_ID);
    if (box != NULL)
    {
        short value = data_heartrate_get_resting_heartrate_front();
        short time = data_heartrate_get_resting_heartrate_minutes();
        if (value == 0)
            snprintf((char *)buff, 30, "-- bpm (-- %s)", GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_TIME));
        else if (time >= 60)
            snprintf((char *)buff, 30, "%d bpm (%d %s)", value, time / 60, GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_HOUR));
        else
            snprintf((char *)buff, 30, "%d bpm (%d %s)", value, time, GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_TIME));
        gui_surface_box_label_change_string(box, buff);
    }

    /**********************************************/
    box = gui_surface_get_box(&app_heartrate_screen, (unsigned short)HR_BOX_WALK_VALUE_ID);
    if (box != NULL)
    {
        short value = data_heartrate_get_walk_heartrate();
        if (value == 0)
            snprintf((char *)buff, 30, "--");
        else
            snprintf((char *)buff, 30, "%d", value);
        gui_surface_box_label_change_string(box, buff);
    }

    box = gui_surface_get_box(&app_heartrate_screen, (unsigned short)HR_BOX_WALK_HISTORY_ID);
    if (box != NULL)
    {
        short value = data_heartrate_get_walk_heartrate_front();
        short time = data_heartrate_get_walk_heartrate_minutes();
        if (value == 0)
            snprintf((char *)buff, 30, "-- bpm (-- %s)", GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_TIME));
        else if (time >= 60)
            snprintf((char *)buff, 30, "%d bpm (%d %s)", value, time / 60, GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_HOUR));
        else
            snprintf((char *)buff, 30, "%d bpm (%d %s)", value, time, GUI_Get_ID_String(STRING_HEART_RATE_UPDATE_TIME));
        gui_surface_box_label_change_string(box, buff);
    }
}

void app_window_heartrate_ui_show()
{
    g_heartrate_ui_count = 0;
    application_titlebar_create(&app_heartrate_screen, STRING_HR);

    gui_surface_struct *surface = gui_surface_get_surface(&app_heartrate_screen);
    if (surface != NULL)
    {
        application_titlebar_hide_bg(surface);
        application_titlebar_unfix(surface);
    }
    app_window_heartrate_ui_show_result();
}
