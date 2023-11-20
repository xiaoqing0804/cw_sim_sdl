#include "app_window_password_setting_ui.h"
#include "app_window_password_setting_layout.h"

void app_window_password_setting_ui_show_status()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_password_setting, PASSWORD_SETTING_LAYOUT_ID_OPEN);
	gui_box_struct *box_text = gui_surface_get_box(&gui_screen_password_setting, PASSWORD_SETTING_LAYOUT_ID_TITLE);
	gui_box_struct *box_text_gray = gui_surface_get_box(&gui_screen_password_setting, PASSWORD_SETTING_LAYOUT_ID_TITLE_GRAY);
	if (g_password.flag)
	{
		gui_surface_box_image_change(box, &pic_setting_list_status_open_info);
		box_text->visible = 1;
		box_text_gray->visible = 0;
	}
	else
	{
		gui_surface_box_image_change(box, &pic_setting_list_status_close_info);
		box_text->visible = 0;
		box_text_gray->visible = 1;
	}
}

void app_window_password_setting_ui_show()
{
	application_titlebar_create(&gui_screen_password_setting, STRING_PASSWORD);
	app_window_password_setting_ui_show_status();
}