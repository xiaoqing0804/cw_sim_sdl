#include "app_window_password_setting_layout.h"

#define PASSWORD_SETTING_LEFT (GUI_CONTENT_GAP_LEFT)
#define PASSWORD_SETTING_TOP (GUI_CONTENT_GAP_TOP)

#define PASSWORD_SETTING_ITEM_WIDTH (GUI_CONTENT_WIDTH)
#define PASSWORD_SETTING_ITEM_HEIGHT (GUI_ITEM_HEIGHT)

#define PASSWORD_SETTING_ITEM_BUTTON_WIDTH (88)
#define PASSWORD_SETTING_ITEM_BUTTON_X (PASSWORD_SETTING_LEFT + PASSWORD_SETTING_ITEM_WIDTH - GUI_ITEM_GAP_LEFT - PASSWORD_SETTING_ITEM_BUTTON_WIDTH)

#define PASSWORD_SETTING_ITEM_HINT_X (GUI_ITEM_GAP_LEFT + PASSWORD_SETTING_LEFT)
#define PASSWORD_SETTING_ITEM_HINT_WIDTH (PASSWORD_SETTING_ITEM_BUTTON_X - GUI_ITEM_SPACE - PASSWORD_SETTING_ITEM_HINT_X)

#define PASSWORD_SETTING_ITEM_Y(index) (GUI_CONTENT_GAP_TOP + (index) * (GUI_ITEM_HEIGHT + GUI_ITEM_SPACE))

static const gui_image_struct gui_setting_common_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

/**************************密码开关*****************************/

static const gui_font_struct gui_password_setting_item_open_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = 0,
		.y = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.width = PASSWORD_SETTING_ITEM_HINT_WIDTH,
		.height = PASSWORD_SETTING_ITEM_HEIGHT,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_PASSWORD_SET,
		.scroll = 1,
};

static const gui_image_struct gui_password_setting_item_status =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_VCENTER),
		.data = &pic_setting_list_status_open_info,
};

/**************************密码设置*****************************/

static const gui_font_struct gui_password_setting_item_set_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = 0,
		.y = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.width = PASSWORD_SETTING_ITEM_HINT_WIDTH,
		.height = PASSWORD_SETTING_ITEM_HEIGHT,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_CHANGE_PASSWORD,
		.scroll = 1,
};

static const gui_font_struct gui_password_setting_item_set_gray_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = 0,
		.y = 0,
		.color = COLOR_RGB(128, 128, 128),
		.size = SYS_FONT_MEDIUM,
		.width = PASSWORD_SETTING_ITEM_HINT_WIDTH,
		.height = PASSWORD_SETTING_ITEM_HEIGHT,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_CHANGE_PASSWORD,
		.scroll = 1,
};

static const gui_image_struct gui_password_setting_item_arrow =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_VCENTER),
		.data = &pic_setting_list_hint_arrow_info,
};

/******************************************************/
static const gui_widget_struct gui_widget_password_setting[] =
	{

		/**************************密码开关*****************************/
		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_SETTING_LEFT,
			.y = PASSWORD_SETTING_ITEM_Y(0),
			.width = PASSWORD_SETTING_ITEM_WIDTH,
			.height = PASSWORD_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_setting_common_bg,
		},

		{
			.type = TYPE_GUI_DRAW_TEXT,
			.x = PASSWORD_SETTING_ITEM_HINT_X,
			.y = PASSWORD_SETTING_ITEM_Y(0),
			.width = PASSWORD_SETTING_ITEM_HINT_WIDTH,
			.height = PASSWORD_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_password_setting_item_open_title,
		},

		{
			.id = PASSWORD_SETTING_LAYOUT_ID_OPEN,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_SETTING_ITEM_BUTTON_X,
			.y = PASSWORD_SETTING_ITEM_Y(0),
			.width = PASSWORD_SETTING_ITEM_BUTTON_WIDTH,
			.height = PASSWORD_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_setting_item_status,
		},

		/**************************密码设置*****************************/

		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_SETTING_LEFT,
			.y = PASSWORD_SETTING_ITEM_Y(1),
			.width = PASSWORD_SETTING_ITEM_WIDTH,
			.height = PASSWORD_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_setting_common_bg,
		},

		{
			.id = PASSWORD_SETTING_LAYOUT_ID_TITLE,
			.type = TYPE_GUI_DRAW_TEXT,
			.x = PASSWORD_SETTING_ITEM_HINT_X,
			.y = PASSWORD_SETTING_ITEM_Y(1),
			.width = PASSWORD_SETTING_ITEM_HINT_WIDTH,
			.height = PASSWORD_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_password_setting_item_set_title,
		},

		{
			.id = PASSWORD_SETTING_LAYOUT_ID_TITLE_GRAY,
			.type = TYPE_GUI_DRAW_TEXT,
			.x = PASSWORD_SETTING_ITEM_HINT_X,
			.y = PASSWORD_SETTING_ITEM_Y(1),
			.width = PASSWORD_SETTING_ITEM_HINT_WIDTH,
			.height = PASSWORD_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_password_setting_item_set_gray_title,
		},

		{
			.id = PASSWORD_SETTING_LAYOUT_ID_ARROW,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_SETTING_ITEM_BUTTON_X,
			.y = PASSWORD_SETTING_ITEM_Y(1),
			.width = PASSWORD_SETTING_ITEM_BUTTON_WIDTH,
			.height = PASSWORD_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_setting_item_arrow,
		},

};

const gui_screen_struct gui_screen_password_setting =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_password_setting,
		.child_num = countof(gui_widget_password_setting),
};
