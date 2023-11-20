#include "app_window_notification_setting_ui.h"
#include "app_window_notification_setting_layout.h"
#include "gui_surface_box_image.h"
#include "data_notification.h"

void app_window_notification_setting_ui_show_status()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_notification_setting, NOTIFICATION_SETTING_LAYOUT_OPEN);

	if (data_notification_status_is_on())
		gui_surface_box_image_change(box, &pic_setting_list_status_open_info);
	else
		gui_surface_box_image_change(box, &pic_setting_list_status_close_info);
}

void app_window_notification_setting_ui_show()
{
	application_titlebar_create(&gui_screen_notification_setting, STRING_NOTICE);
	app_window_notification_setting_ui_show_status();
}
