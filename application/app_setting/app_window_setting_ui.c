#include "app_window_setting_ui.h"
#include "app_window_setting_layout.h"
#include "application_titlebar.h"
#include "gui_surface_box_layout_item.h"

#include "app_window_personnal.h"
#include "app_window_notification_setting.h"
#include "app_window_setting_common.h"
#include "app_window_disturb_setting.h"
#include "app_window_setting_screen.h"
#include "app_window_moreinfo_style.h"
#include "app_window_key_define.h"
#include "app_window_password.h"
#include "app_window_sos_setting.h"
#include "app_window_battery.h"
#include "app_window_sound_touch.h"
#include "app_window_password_setting.h"

static const app_window_setting_list_item_struct app_window_setting_list[] =
	{
		{
			SETTING_LAYOUT_ID_PERSONNAL,
			&app_window_personnal,
		},

		{
			SETTING_LAYOUT_ID_NOTICE,
			&app_window_notification_setting,
		},
		{
			SETTING_LAYOUT_ID_SETTING,
			&app_window_setting_common,
		},
		{
			SETTING_LAYOUT_ID_DISTURB,
			&app_window_disturb_setting,
		},
		{
			SETTING_LAYOUT_ID_SCREEN,
			&app_window_setting_screen,
		},
		{
			SETTING_LAYOUT_ID_APP_VIEW,
			&app_window_moreinfo_style,
		},
		#if !GUI_SINGLE_KEY_SUPPORT
		{
			SETTING_LAYOUT_ID_KEY_SETTING,
			&app_window_key_define,
		},
		#endif
		{
			SETTING_LAYOUT_ID_SOUND_AND_TOUCH,
			&app_window_sound_touch,
		},
		{
			SETTING_LAYOUT_ID_PASSWORD,
			&app_window_password_setting,
		},
		{
			SETTING_LAYOUT_ID_SOS,
			&app_window_sos_setting,
		},
		{
			SETTING_LAYOUT_ID_BATTRY,
			&app_window_battery,
		},
};

const gui_window_struct *app_window_setting_ui_find_app(unsigned short id)
{
	for (short i = 0; i < countof(app_window_setting_list); i++)
	{
		if (app_window_setting_list[i].id == id)
			return app_window_setting_list[i].window;
	}
	return NULL;
}

static void app_window_personnal_ui_show_head()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_setting, SETTING_LAYOUT_ID_PERSONNAL);
	if (box != NULL)
	{
		picture_info_struct *picture = get_ble_connect_flag() > 0 ? &pic_setting_list_icon_personal_login_info : &pic_setting_list_icon_personal_info;
		gui_surface_box_layout_item_change_image(box, SETTING_LAYOUT_ID_PERSONNAL_ICON, picture);
	}
}

void app_window_setting_ui_show_content()
{
	app_window_personnal_ui_show_head();
}

void app_window_setting_ui_show()
{
	application_titlebar_create(&gui_screen_setting, STRING_SETTING);
	app_window_setting_ui_show_content();
}
