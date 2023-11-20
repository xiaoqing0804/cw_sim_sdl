/****************************
**密码流程界面
*****************************/
#include "app_window_password_status.h"
#include "application_password.h"

static password_info_struct g_password_info = {0};

static void app_window_password_status_unlock_step_callback(password_info_struct *info)
{
	if (info->step == 0)
	{
		app_window_password_status_swap(info->orgin_password);
		if (app_window_password_status_check_right())
		{
			info->step++;
			application_password_setLock(0);
			application_go_back();
			return;
		}
		else
		{
			info->error = PASSWORD_ERROR_WRONG;
		}
	}
	gui_surface_commit();
}

password_info_struct *app_window_password_status_init(password_input_step_callback step_callback)
{
	memset(&g_password_info, 0, sizeof(g_password_info));
	g_password_info.step_callback = step_callback;
	return &g_password_info;
}

void app_window_password_status_init_for_unlock()
{
	memset(&g_password_info, 0, sizeof(g_password_info));
	g_password_info.step_callback = app_window_password_status_unlock_step_callback;
}

password_info_struct *app_window_password_status_get_info()
{
	return &g_password_info;
}

/// @brief 得到当前输入框的内容
/// @return
unsigned char *app_window_password_status_get_value()
{
	return g_password_info.password;
}

unsigned char app_window_password_status_get_input_length()
{
	return strlen((const char *)g_password_info.password);
}

unsigned char app_window_password_status_is_input_max()
{
	return strlen((const char *)g_password_info.password) >= PASSWORD_STATUS_INPUT_TOTAL;
}

unsigned char app_window_password_status_get_error()
{
	return g_password_info.error;
}

unsigned char app_window_password_status_check_right()
{
	if (memcmp(g_password_info.orgin_password, g_password.password_indx, PASSWORD_STATUS_INPUT_TOTAL) == 0)
		return 1;
	if (memcmp(g_password_info.orgin_password, g_password.ultimate_password_indx, PASSWORD_STATUS_INPUT_TOTAL) == 0)
		return 1;
	return 0;
}

unsigned char app_window_password_status_check_match()
{
	return (memcmp(g_password_info.frist_password, g_password_info.second_password, PASSWORD_STATUS_INPUT_TOTAL) == 0);
}

/// @brief 输入一个密码字符
/// @param input_char
void app_window_password_status_add(unsigned char input_char)
{
	short count = strlen(g_password_info.password);
	if (count <= 3)
	{
		g_password_info.password[count] = input_char;
		g_password_info.error = PASSWORD_ERROR_NONE;
	}
}

/// @brief 删除最后的密码字符
void app_window_password_status_remove()
{
	short count = strlen(g_password_info.password);
	if (count > 0 && count < PASSWORD_STATUS_LENGTH)
	{
		g_password_info.password[count - 1] = 0;
	}
}

/// @brief 把工作区的数据存到保存区去
/// @param to 保存区的位置
void app_window_password_status_swap(unsigned char *to)
{
	memcpy(to, g_password_info.password, sizeof(g_password_info.password));
	memset(g_password_info.password, 0, sizeof(g_password_info.password));
}

void app_window_password_status_complete_step()
{
	if (app_window_password_status_is_input_max())
	{
		if (g_password_info.step_callback)
		{
			g_password_info.step_callback(&g_password_info);
		}
		application_send_event(EVENT_UPDATE_WINDOW, NULL);
	}
}
