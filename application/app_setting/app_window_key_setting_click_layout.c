#include "app_window_key_setting_click_layout.h"

#define KEY_SETTING_CLICK_ITEM_ICON_X (GUI_ITEM_GAP_LEFT)
#define KEY_SETTING_CLICK_ITEM_ICON_Y ((GUI_ITEM_HEIGHT - 62) / 2)

#define KEY_SETTING_CLICK_ITEM_TXT_X (108)
#define KEY_SETTING_CLICK_ITEM_TXT_Y (0)
#define KEY_SETTING_CLICK_ITEM_TXT_WIDTH (235)

#define KEY_SETTING_CLICK_ITEM_Y(index) (GUI_CONTENT_GAP_TOP + (index) * (GUI_ITEM_HEIGHT + GUI_ITEM_SPACE))

const gui_image_struct gui_key_setting_click_item_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

const gui_image_struct gui_key_setting_click_item_status =
	{
		.id = KEY_SETTING_CLICK_LAYOUT_ID_CHECKED,
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 44,
		.y = (GUI_ITEM_HEIGHT - 44) / 2,
		.data = &pic_setting_list_status_checked_info,
};

/**********************************item***************************************/

gui_image_struct gui_key_setting_click_item_icon =
	{
		.id = KEY_SETTING_CLICK_LAYOUT_ID_ICON,
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = KEY_SETTING_CLICK_ITEM_ICON_X,
		.y = KEY_SETTING_CLICK_ITEM_ICON_Y,
		.scale = 62 / 98.0f,
		.data = &pic_app_about_88_info,
};

gui_font_struct gui_key_setting_click_item_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = KEY_SETTING_CLICK_ITEM_TXT_X,
		.y = KEY_SETTING_CLICK_ITEM_TXT_Y,
		.width = KEY_SETTING_CLICK_ITEM_TXT_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_KEY_1,
		.scroll = 1,
};

const gui_mix_struct gui_widget_key_setting_mix[] =
	{
		{
			.data = &gui_key_setting_click_item_bg,
		},
		{
			.data = &gui_key_setting_click_item_icon,
		},
		{
			.data = &gui_key_setting_click_item_title,
		},
		{
			.data = &gui_key_setting_click_item_status,
		},

};

/*************************************************************************/

const gui_widget_struct gui_widget_key_setting_click =
	{
		.id = MOREINFO_WINDOW_STYLE_RING_TWO,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = GUI_CONTENT_GAP_LEFT,
		.y = KEY_SETTING_CLICK_ITEM_Y(0),
		.width = GUI_CONTENT_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.visible = 1,
		.clip = 1,
		.child_num = countof(gui_widget_key_setting_mix),
		.children = gui_widget_key_setting_mix,
};

const gui_layout_list_struct gui_layout_config_key_setting_click =
	{
		.row_height = GUI_ITEM_HEIGHT,

		.top = GUI_CONTENT_GAP_TOP,
		.bottom = GUI_CONTENT_GAP_BOTTOM,
		.space = GUI_ITEM_SPACE,
		.scroll = 1,
};

const gui_screen_struct app_screen_key_setting_click =
	{
		.type = TYPE_GUI_LAYOUT_LIST,
		.layout_config = &gui_layout_config_key_setting_click,
};
