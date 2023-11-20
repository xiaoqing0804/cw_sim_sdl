#include "app_window_password_setting.h"
#include "app_window_password_setting_ui.h"
#include "app_window_password_setting_layout.h"
#include "app_window_password_status.h"
#include "app_window_password.h"
#include "application_password.h"

/*-----------------------------本地逻辑处理--------------------------------------*/
static void app_window_password_setting_close_step_callback(password_info_struct *info)
{
	if (info->step == 0)
	{
		app_window_password_status_swap(info->orgin_password);
		if (app_window_password_status_check_right())
		{
			application_password_setOnoff(0);

			application_go_back();
		}
		else
		{
			info->error = PASSWORD_ERROR_WRONG;
		}
	}
	gui_surface_commit();
}

static void app_window_password_setting_open_step_callback(password_info_struct *info)
{
	if (info->step == 0)
	{
		app_window_password_status_swap(info->frist_password);
		info->step++;
		info->error = PASSWORD_ERROR_INPUT_CHAR_AGAIN;
	}
	else if (info->step == 1)
	{
		app_window_password_status_swap(info->second_password);
		if (app_window_password_status_check_match())
		{
			application_password_ste(info->second_password);
			application_password_setOnoff(1);

			application_go_back();
		}
		else
		{
			info->error = PASSWORD_ERROR_NO_MATCH;
		}
	}
	gui_surface_commit();
}

static void app_window_password_setting_change_step_callback(password_info_struct *info)
{
	if (info->step == 0)
	{
		app_window_password_status_swap(info->orgin_password);
		if (app_window_password_status_check_right())
		{
			info->step++;
			info->error = PASSWORD_ERROR_INPUT_CHAR;
		}
		else
		{
			info->error = PASSWORD_ERROR_WRONG;
		}
	}
	else if (info->step == 1)
	{
		app_window_password_status_swap(info->frist_password);
		info->step++;
		info->error = PASSWORD_ERROR_INPUT_CHAR_AGAIN;
	}
	else if (info->step == 2)
	{
		app_window_password_status_swap(info->second_password);
		if (app_window_password_status_check_match())
		{
			application_password_ste(info->second_password);

			application_go_back();
		}
		else
		{
			info->error = PASSWORD_ERROR_NO_MATCH;
		}
	}
	gui_surface_commit();
}

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_password_setting_event_touch_open_handle(gui_click_struct *event)
{
	if (application_password_getOnoff())
	{
		app_window_password_status_init(app_window_password_setting_close_step_callback);
	}
	else
	{
		password_info_struct *info = app_window_password_status_init(app_window_password_setting_open_step_callback);
		info->error = PASSWORD_ERROR_INPUT_CHAR;
	}
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_password, NULL);
}

static void app_window_password_change_event_touch_set_handle(gui_click_struct *event)
{
	if (g_password.flag)
	{
		app_window_password_status_init(app_window_password_setting_change_step_callback);
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_password, NULL);
	}
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_password_setting_init(void *buf)
{
}

static void app_window_password_setting_load(void *buf)
{
	app_window_password_setting_ui_show();
}

static void app_window_password_setting_entry(void *buf)
{
}

static void app_window_password_setting_exit()
{
}

static void app_window_password_setting_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_password_setting_touch_events[] =
	{
		{
			.id = PASSWORD_SETTING_LAYOUT_ID_OPEN,
			.click = app_window_password_setting_event_touch_open_handle,
		},
		{
			.id = PASSWORD_SETTING_LAYOUT_ID_ARROW,
			.offset_left = 70,
			.offset_right = 30,
			.offset_top = 30,
			.offset_bottom = 30,
			.click = app_window_password_change_event_touch_set_handle,
		},
};

const gui_window_struct app_window_password_setting =
	{
		.screen = &gui_screen_password_setting,

		.init = app_window_password_setting_init,
		.load = app_window_password_setting_load,
		.entry = app_window_password_setting_entry,
		.exit = app_window_password_setting_exit,
		.destroy = app_window_password_setting_destroy,

		.touch_event_num = countof(app_window_password_setting_touch_events),
		.touch_events = app_window_password_setting_touch_events,
};
