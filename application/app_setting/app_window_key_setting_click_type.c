#include "app_window_key_setting_click_type.h"
#include "app_window_key_setting_click.h"
#include "app_window_key_setting_click_ui.h"
#include "app_window_key_setting_click_layout.h"
#include "data_key_define.h"
#include "config_key_define.h"

/// @brief 当前界面是什么按键类型（单击，双击，长按）
static unsigned char g_key_setting_type = KEY_DEFINE_TYPE_CLICK;

/// @brief 设置当前界面的按键类型
/// @param type 
void app_window_key_setting_click_type_set_type(unsigned short type)
{
	g_key_setting_type = type;
}

/// @brief 得到当前界面的按键类型
unsigned char app_window_key_setting_click_type_get_type()
{
	return g_key_setting_type;
}

/// @brief 由 当前界面的按键类型 得到界面标题
unsigned short app_window_key_setting_click_type_get_string_id()
{
	if (g_key_setting_type == KEY_DEFINE_TYPE_CLICK)
		return STRING_KEY_1;
	else if (g_key_setting_type == KEY_DEFINE_TYPE_DOUBLE)
		return STRING_KEY_DOUBLE;
	else if (g_key_setting_type == KEY_DEFINE_TYPE_LONG)
		return STRING_KEY_LONG;
	return STRING_KEY_1;
}

/// @brief 当前界面的选中的 应用
/// @param id 应用ID
unsigned char app_window_key_setting_click_type_is_selected(unsigned short id)
{
	return data_key_define_get_selected(g_key_setting_type) == id;
}

/// @brief 设置 当前界面的选中的 应用
/// @param id 
void app_window_key_setting_click_type_set_key(unsigned short id)
{
	if (g_key_setting_type == KEY_DEFINE_TYPE_CLICK)
	{
		data_key_define_set_click(id);
	}
	else if (g_key_setting_type == KEY_DEFINE_TYPE_DOUBLE)
	{
		data_key_define_set_double(id);
	}
	else if (g_key_setting_type == KEY_DEFINE_TYPE_LONG)
	{
		data_key_define_set_long(id);
	}
}
