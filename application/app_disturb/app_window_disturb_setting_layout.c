#include "app_window_disturb_setting_layout.h"

#define DISTURB_SETTING_LEFT (GUI_CONTENT_GAP_LEFT)
#define DISTURB_SETTING_TOP (GUI_CONTENT_GAP_TOP)

#define DISTURB_SETTING_ITEM_WIDTH (GUI_CONTENT_WIDTH)
#define DISTURB_SETTING_ITEM_HEIGHT (GUI_ITEM_HEIGHT)
#define DISTURB_SETTING_ITEM_GAP (5)

#define DISTURB_SETTING_ITEM_BUTTON_WIDTH (88)
#define DISTURB_SETTING_ITEM_BUTTON_X (DISTURB_SETTING_LEFT + DISTURB_SETTING_ITEM_WIDTH - DISTURB_SETTING_LEFT - DISTURB_SETTING_ITEM_BUTTON_WIDTH)

#define DISTURB_SETTING_ITEM_TITLE_X (GUI_ITEM_GAP_LEFT + DISTURB_SETTING_LEFT)
#define DISTURB_SETTING_ITEM_TITLE_WIDTH (DISTURB_SETTING_ITEM_BUTTON_X - DISTURB_SETTING_ITEM_TITLE_X - GUI_ITEM_SPACE)

static const gui_image_struct gui_disturb_setting_item_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

static const gui_font_struct gui_disturb_setting_item_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = 0,
		.y = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.width = DISTURB_SETTING_ITEM_TITLE_WIDTH,
		.height = GUI_ITEM_TWO_LINE_TXT_UP_HEIGHT,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_DISTURB,
};

static const gui_font_struct gui_disturb_setting_item_hint =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_XSMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_DISTURB_HINT,
		.auto_wrap = 1,
};

static const gui_font_struct gui_disturb_setting_item_date =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = 0,
		.y = 0,
		.color = COLOR_RGB(128, 128, 128),
		.size = SYS_FONT_XSMALL,
		.width = DISTURB_SETTING_ITEM_TITLE_WIDTH,
		.height = GUI_ITEM_TWO_LINE_TXT_DOWN_HEIGHT,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value_align = GUI_ALIGN_TOP,
		.value.string_id = "",
};

static const gui_image_struct gui_disturb_setting_item_status =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.data = &pic_setting_list_status_open_info,
};

static const gui_widget_struct gui_widget_disturb_setting[] =
	{
		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = DISTURB_SETTING_LEFT,
			.y = DISTURB_SETTING_TOP,
			.width = DISTURB_SETTING_ITEM_WIDTH,
			.height = DISTURB_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_disturb_setting_item_bg,
		},

		{
			.type = TYPE_GUI_DRAW_TEXT,
			.x = DISTURB_SETTING_ITEM_TITLE_X,
			.y = DISTURB_SETTING_TOP,
			.width = DISTURB_SETTING_ITEM_TITLE_WIDTH,
			.height = GUI_ITEM_TWO_LINE_TXT_UP_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_disturb_setting_item_title,
		},

		{
			.id = DISTURB_SETTING_LAYOUT_DATE,
			.type = TYPE_GUI_DRAW_TEXT,
			.x = DISTURB_SETTING_ITEM_TITLE_X,
			.y = DISTURB_SETTING_TOP + GUI_ITEM_TWO_LINE_TXT_UP_HEIGHT,
			.width = DISTURB_SETTING_ITEM_TITLE_WIDTH,
			.height = GUI_ITEM_TWO_LINE_TXT_DOWN_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_disturb_setting_item_date,
		},

		{
			.id = DISTURB_SETTING_LAYOUT_OPEN,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = DISTURB_SETTING_ITEM_BUTTON_X,
			.y = DISTURB_SETTING_TOP,
			.width = DISTURB_SETTING_ITEM_BUTTON_WIDTH,
			.height = DISTURB_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_disturb_setting_item_status,
		},

		{
			.type = TYPE_GUI_DRAW_TEXT,
			.x = DISTURB_SETTING_ITEM_TITLE_X,
			.y = DISTURB_SETTING_TOP + DISTURB_SETTING_ITEM_HEIGHT + DISTURB_SETTING_ITEM_GAP,
			.width = DISTURB_SETTING_ITEM_WIDTH - GUI_ITEM_GAP_LEFT * 2,
			.height = DISTURB_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_disturb_setting_item_hint,
		},
};

const gui_screen_struct gui_screen_disturb_setting =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_disturb_setting,
		.child_num = countof(gui_widget_disturb_setting),
};
