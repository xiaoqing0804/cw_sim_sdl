#include "app_window_breath_start_ui.h"
#include "app_window_breath_start_layout.h"
#include "app_window_breath_animate.h"

#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"
#include "application_titlebar.h"

static const picture_info_struct *const breath_countdown_count[] =
	{
		&pic_break_ountdown_time_01_info,
		&pic_break_ountdown_time_02_info,
		&pic_break_ountdown_time_03_info,
};

/// @brief 显示呼/吸状态文字说明
static void app_window_breath_start_ui_update_status_string()
{
	gui_box_struct *breath_huxi = gui_surface_get_box(&gui_screen_breath_start, (unsigned short)BREATH_START_LAYOUT_ID_STATUS);
	char temp[40];
	if (app_window_breath_animate_is_back())
		snprintf(temp, sizeof(temp), "%s", GUI_Get_ID_String(STRING_BREATH_OUT));
	else
		snprintf(temp, sizeof(temp), "%s", GUI_Get_ID_String(STRING_BREATH_IN));
	gui_surface_box_label_change_string(breath_huxi, (unsigned char *)temp);
}

/// @brief 显示倒计时
/// @param second
void app_window_breath_start_ui_show_countdown(short second)
{
	gui_box_struct *breath_logo = gui_surface_get_box(&gui_screen_breath_start, (unsigned short)BREATH_START_LAYOUT_ID_START);
	gui_box_struct *breath_huxi = gui_surface_get_box(&gui_screen_breath_start, (unsigned short)BREATH_START_LAYOUT_ID_STATUS);
	breath_huxi->visible = 0;
	breath_logo->visible = 1;
	gui_surface_box_image_change(breath_logo, (const picture_info_struct *)breath_countdown_count[second]);
}

/// @brief 显示当前呼/吸状态
void app_window_breath_start_ui_show_status()
{
	gui_box_struct *breath_logo = gui_surface_get_box(&gui_screen_breath_start, (unsigned short)BREATH_START_LAYOUT_ID_START);
	gui_box_struct *breath_huxi = gui_surface_get_box(&gui_screen_breath_start, (unsigned short)BREATH_START_LAYOUT_ID_STATUS);
	breath_logo->visible = 0;
	breath_huxi->visible = 1;
	app_window_breath_start_ui_update_status_string();
}

void app_window_breath_start_ui_show()
{
	application_titlebar_create(&gui_screen_breath_start, STRING_BREATH);
	application_titlebar_hide_bg_from_screen(&gui_screen_breath_start);
	app_window_breath_animate_init(&gui_screen_breath_start, (unsigned short)BREATH_START_LAYOUT_ID_BG);
}
