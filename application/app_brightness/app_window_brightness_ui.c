#include "app_window_brightness.h"
#include "app_window_brightness_layout.h"
#include "app_window_brightness_ui.h"

/// @brief
/// @param brightness_level
void app_window_brightness_ui_update_line(int brightness_level)
{
	char temp[40];

	int pre_brightness = (brightness_level == 1) ? BRIGHTNESS_TOTAL_LEVEL : (brightness_level - 1);
	snprintf(temp, sizeof(temp), "%02d", pre_brightness);
	gui_box_struct *hour_up = gui_surface_get_box(&gui_screen_light, (unsigned short)LIGHT_LAYOUT_ID_LINE_0);
	gui_surface_box_label_change_string(hour_up, (unsigned char *)temp);

	snprintf(temp, sizeof(temp), "%02d", brightness_level);
	gui_box_struct *hour = gui_surface_get_box(&gui_screen_light, (unsigned short)LIGHT_LAYOUT_ID_LINE_2);
	gui_surface_box_label_change_string(hour, (unsigned char *)temp);

	int next_brightness = (brightness_level == BRIGHTNESS_TOTAL_LEVEL) ? 1 : (brightness_level + 1);
	snprintf(temp, sizeof(temp), "%02d", next_brightness);
	gui_box_struct *hour_down = gui_surface_get_box(&gui_screen_light, (unsigned short)LIGHT_LAYOUT_ID_LINE_1);
	gui_surface_box_label_change_string(hour_down, (unsigned char *)temp);

	gui_surface_commit();
}
