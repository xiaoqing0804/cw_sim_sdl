#include "app_window_sos_setting_layout.h"

#define SOS_SETTING_LEFT (GUI_CONTENT_GAP_LEFT)
#define SOS_SETTING_TOP (GUI_CONTENT_GAP_TOP)

#define SOS_SETTING_ITEM_WIDTH (GUI_CONTENT_WIDTH)
#define SOS_SETTING_ITEM_HEIGHT (GUI_ITEM_HEIGHT)

#define SOS_SETTING_ITEM_BUTTON_WIDTH (88)
#define SOS_SETTING_ITEM_BUTTON_X (SOS_SETTING_LEFT + SOS_SETTING_ITEM_WIDTH - SOS_SETTING_LEFT - SOS_SETTING_ITEM_BUTTON_WIDTH)

#define SOS_SETTING_ITEM_HINT_X (GUI_ITEM_GAP_LEFT + SOS_SETTING_LEFT)
#define SOS_SETTING_ITEM_HINT_WIDTH (SOS_SETTING_ITEM_BUTTON_X - GUI_ITEM_SPACE - SOS_SETTING_ITEM_HINT_X)

static const gui_image_struct gui_sos_setting_item_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

static const gui_font_struct gui_sos_setting_item_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = 0,
		.y = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.width = SOS_SETTING_ITEM_HINT_WIDTH,
		.height = SOS_SETTING_ITEM_HEIGHT,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_SOS,
};

static const gui_image_struct gui_sos_setting_item_status =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.data = &pic_setting_list_status_open_info,
};

static const gui_widget_struct gui_widget_sos_setting[] =
	{
		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = SOS_SETTING_LEFT,
			.y = SOS_SETTING_TOP,
			.width = SOS_SETTING_ITEM_WIDTH,
			.height = SOS_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_sos_setting_item_bg,
		},

		{
			.type = TYPE_GUI_DRAW_TEXT,
			.x = SOS_SETTING_ITEM_HINT_X,
			.y = SOS_SETTING_TOP,
			.width = SOS_SETTING_ITEM_HINT_WIDTH,
			.height = SOS_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_sos_setting_item_title,
		},

		{
			.id = SOS_SETTING_LAYOUT_ID_OPEN,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = SOS_SETTING_ITEM_BUTTON_X,
			.y = SOS_SETTING_TOP,
			.width = SOS_SETTING_ITEM_BUTTON_WIDTH,
			.height = SOS_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_sos_setting_item_status,
		},
};

const gui_screen_struct gui_screen_sos_setting =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_sos_setting,
		.child_num = countof(gui_widget_sos_setting),
};
