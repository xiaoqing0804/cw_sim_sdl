#include "app_window_aod_dial_ui.h"
#include "app_window_aod_dial_layout.h"

static void app_window_aod_dial_ui_show_on_off()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_aod_dial, AOD_DIAL_LAYOUT_ID_OPEN);
	if (data_watchface_get_standby_clock())
		gui_surface_box_layout_item_change_image(box, AOD_DIAL_LAYOUT_ID_OPEN_STATUS, &pic_setting_list_status_open_info);
	else
		gui_surface_box_layout_item_change_image(box, AOD_DIAL_LAYOUT_ID_OPEN_STATUS, &pic_setting_list_status_close_info);
}

static void app_window_aod_dial_ui_show_select_number_clock()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_aod_dial, AOD_DIAL_LAYOUT_ID_NUMBER);
	gui_node_struct *node_text_1 = gui_surface_box_find_node(box, AOD_DIAL_LAYOUT_ID_TITLE);
	gui_node_struct *node_text_1_gray = gui_surface_box_find_node(box, AOD_DIAL_LAYOUT_ID_TITLE_GRAY);

	if (data_watchface_get_standby_clock())
	{
		node_text_1->visible = 1;
		node_text_1_gray->visible = 0;

		gui_surface_box_layout_item_change_image(box, AOD_DIAL_LAYOUT_ID_CHECKED, &pic_setting_list_status_checked_info);
		gui_node_struct *node_1 = gui_surface_box_find_node(box, AOD_DIAL_LAYOUT_ID_CHECKED);
		node_1->visible = (application_main_window_get_idle_index() == 0);
	}
	else
	{
		node_text_1->visible = 0;
		node_text_1_gray->visible = 1;

		gui_surface_box_layout_item_change_image(box, AOD_DIAL_LAYOUT_ID_CHECKED, &pic_setting_list_status_checked_unselect_info);
		gui_node_struct *node_1 = gui_surface_box_find_node(box, AOD_DIAL_LAYOUT_ID_CHECKED);
		node_1->visible = (application_main_window_get_idle_index() == 0);
	}
}

static void app_window_aod_dial_ui_show_select_pointer_clock()
{
	gui_box_struct *box = gui_surface_get_box(&gui_screen_aod_dial, AOD_DIAL_LAYOUT_ID_POINTER);
	gui_node_struct *node_text_1 = gui_surface_box_find_node(box, AOD_DIAL_LAYOUT_ID_TITLE);
	gui_node_struct *node_text_1_gray = gui_surface_box_find_node(box, AOD_DIAL_LAYOUT_ID_TITLE_GRAY);

	if (data_watchface_get_standby_clock())
	{
		node_text_1->visible = 1;
		node_text_1_gray->visible = 0;

		gui_surface_box_layout_item_change_image(box, AOD_DIAL_LAYOUT_ID_CHECKED, &pic_setting_list_status_checked_info);
		gui_node_struct *node_1 = gui_surface_box_find_node(box, AOD_DIAL_LAYOUT_ID_CHECKED);
		node_1->visible = (application_main_window_get_idle_index() == 1);
	}
	else
	{
		node_text_1->visible = 0;
		node_text_1_gray->visible = 1;

		gui_surface_box_layout_item_change_image(box, AOD_DIAL_LAYOUT_ID_CHECKED, &pic_setting_list_status_checked_unselect_info);
		gui_node_struct *node_1 = gui_surface_box_find_node(box, AOD_DIAL_LAYOUT_ID_CHECKED);
		node_1->visible = (application_main_window_get_idle_index() == 1);
	}
}

void app_window_aod_dial_ui_show_content()
{
	app_window_aod_dial_ui_show_on_off();
	app_window_aod_dial_ui_show_select_number_clock();
	app_window_aod_dial_ui_show_select_pointer_clock();
}

void app_window_aod_dial_ui_show()
{
	application_titlebar_create(&gui_screen_aod_dial, STRING_STANDBY_DIAL);
	app_window_aod_dial_ui_show_content();
}

unsigned char app_window_aod_dial_ui_is_touch_on(short x, short y)
{
	return (x > 0);
}
