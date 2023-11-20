#include "app_window_sound_touch_ui.h"
#include "app_window_sound_touch_layout.h"

#include "gui_surface_box_layout_item.h"
#include "application_config_app_info.h"
#include "ams.h"

static void app_window_sound_touch_ui_show_touch_on_off()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_sound_touch, SOUND_TOUCH_LAYOUT_ID_TOUCH);
	if (bsp_get_touch_motor_onoff())
	{
		gui_surface_box_layout_item_change_image(box, SOUND_TOUCH_LAYOUT_ID_TOUCH_OPEN, &pic_setting_list_status_open_info);
	}
	else
	{
		gui_surface_box_layout_item_change_image(box, SOUND_TOUCH_LAYOUT_ID_TOUCH_OPEN, &pic_setting_list_status_close_info);
	}
}

void app_window_sound_touch_ui_show_touch_1()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_sound_touch, SOUND_TOUCH_LAYOUT_ID_TOUCH);

	gui_node_struct *node_text_1 = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_TEXT_1);
	gui_node_struct *node_text_1_gray = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_TEXT_1_GRAY);

	if (bsp_get_touch_motor_onoff())
	{
		node_text_1->visible = 1;
		node_text_1_gray->visible = 0;

		gui_surface_box_layout_item_change_image(box, SOUND_TOUCH_LAYOUT_ID_CHECKED_1, &pic_setting_list_status_checked_info);
		gui_node_struct *node_1 = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_CHECKED_1);
		node_1->visible = !bsp_get_touch_motor_grade();
	}
	else
	{
		node_text_1->visible = 0;
		node_text_1_gray->visible = 1;

		gui_surface_box_layout_item_change_image(box, SOUND_TOUCH_LAYOUT_ID_CHECKED_1, &pic_setting_list_status_checked_unselect_info);
		gui_node_struct *node_1 = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_CHECKED_1);
		node_1->visible = !bsp_get_touch_motor_grade();
	}
}

void app_window_sound_touch_ui_show_touch_2()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_sound_touch, SOUND_TOUCH_LAYOUT_ID_TOUCH);
	gui_node_struct *node_text_2 = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_TEXT_2);
	gui_node_struct *node_text_2_gray = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_TEXT_2_GRAY);

	if (bsp_get_touch_motor_onoff())
	{
		node_text_2->visible = 1;
		node_text_2_gray->visible = 0;

		gui_surface_box_layout_item_change_image(box, SOUND_TOUCH_LAYOUT_ID_CHECKED_2, &pic_setting_list_status_checked_info);
		gui_node_struct *node_2 = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_CHECKED_2);
		node_2->visible = bsp_get_touch_motor_grade();
	}
	else
	{
		node_text_2->visible = 0;
		node_text_2_gray->visible = 1;

		gui_surface_box_layout_item_change_image(box, SOUND_TOUCH_LAYOUT_ID_CHECKED_2, &pic_setting_list_status_checked_unselect_info);
		gui_node_struct *node_2 = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_CHECKED_2);
		node_2->visible = bsp_get_touch_motor_grade();
	}
}

void app_window_sound_touch_ui_show_touch()
{
	app_window_sound_touch_ui_show_touch_on_off();
	app_window_sound_touch_ui_show_touch_1();
	app_window_sound_touch_ui_show_touch_2();
}

void app_window_sound_touch_ui_show_sound()
{
	const remote_music_struct *sound_info = remote_music_info_get();
	gui_box_struct *box = gui_surface_get_box(&gui_screen_sound_touch, SOUND_TOUCH_LAYOUT_ID_SOUND);
	gui_node_struct *node = gui_surface_box_find_node(box, SOUND_TOUCH_LAYOUT_ID_SOUND_PROGRESS);
	if (sound_info->volume == 0)
	{
		node->visible = 0;
		node->clip_width = node->width;
	}
	else
	{
		node->visible = 1;
		node->clip_width = node->width * sound_info->volume / 100;
	}
}

void app_window_sound_touch_ui_show()
{
	application_titlebar_create(&gui_screen_sound_touch, STRING_SOUND_AND_TOUCH);
	app_window_sound_touch_ui_show_sound();
	app_window_sound_touch_ui_show_touch();
}

unsigned char app_window_sound_touch_ui_is_touch_on_vibration_button(short x, short y)
{
	return (/*x > 300 &&*/ y >= 0 && y <= 90);
}

unsigned char app_window_sound_touch_ui_is_touch_on_vibration_check_1(short x, short y)
{
	return (/*x > 300 &&*/ y >= 90 && y <= 90 + 80);
}

unsigned char app_window_sound_touch_ui_is_touch_on_vibration_check_2(short x, short y)
{
	return (/*x > 300 &&*/ y >= 90 + 80 && y <= 90 + 80 + 80);
}

unsigned char app_window_sound_touch_ui_is_touch_on_sound_low(short x, short y)
{
	return (x < 88);
}

unsigned char app_window_sound_touch_ui_is_touch_on_sound_high(short x, short y)
{
	return (x > 350);
}
