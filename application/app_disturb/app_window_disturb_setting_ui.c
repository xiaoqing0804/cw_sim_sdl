#include "app_window_disturb_setting_ui.h"
#include "app_window_disturb_setting_layout.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "data_disturb.h"

void app_window_disturb_setting_ui_show_status()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_disturb_setting, DISTURB_SETTING_LAYOUT_OPEN);
	if (data_disturb_status_is_on())
		gui_surface_box_image_change(box, &pic_setting_list_status_open_info);
	else
		gui_surface_box_image_change(box, &pic_setting_list_status_close_info);
}

void app_window_disturb_setting_ui_show_date()
{
	unsigned char str[16];
	data_disturb_get_time_string(str, 16);

	gui_box_struct *box = gui_surface_get_box(&gui_screen_disturb_setting, DISTURB_SETTING_LAYOUT_DATE);
	gui_surface_box_label_change_string(box, str);
}

void app_window_disturb_setting_ui_show()
{
	application_titlebar_create(&gui_screen_disturb_setting, STRING_DISTURB);
	app_window_disturb_setting_ui_show_status();
	app_window_disturb_setting_ui_show_date();
}
