#include "app_window_notification_setting_layout.h"

#define NOTIFICATION_SETTING_LEFT (GUI_CONTENT_GAP_LEFT)
#define NOTIFICATION_SETTING_TOP (GUI_CONTENT_GAP_TOP)

#define NOTIFICATION_SETTING_ITEM_WIDTH (GUI_CONTENT_WIDTH)
#define NOTIFICATION_SETTING_ITEM_HEIGHT (GUI_ITEM_HEIGHT)
#define NOTIFICATION_SETTING_ITEM_GAP (5)

#define NOTIFICATION_SETTING_ITEM_TITLE_X (GUI_CONTENT_GAP_LEFT + GUI_ITEM_GAP_LEFT)
#define NOTIFICATION_SETTING_ITEM_TITLE_WIDTH (260)

#define NOTIFICATION_SETTING_ITEM_BUTTON_WIDTH (122)
#define NOTIFICATION_SETTING_ITEM_BUTTON_X (GUI_CONTENT_GAP_LEFT + GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - NOTIFICATION_SETTING_ITEM_BUTTON_WIDTH)

static const gui_image_struct gui_notification_setting_item_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

static const gui_font_struct gui_notification_setting_item_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = 0,
		.y = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.width = NOTIFICATION_SETTING_ITEM_TITLE_WIDTH,
		.height = NOTIFICATION_SETTING_ITEM_HEIGHT,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_NOTICE,
		.scroll = 1,
};

static const gui_font_struct gui_notification_setting_item_hint =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = 0,
		.y = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_XSMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_NOTICE_HINT,
		.auto_wrap = 1,
};

static const gui_image_struct gui_notification_setting_item_status =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.data = &pic_setting_list_status_open_info,
};

static const gui_widget_struct gui_widget_notification_setting[] =
	{
		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = NOTIFICATION_SETTING_LEFT,
			.y = NOTIFICATION_SETTING_TOP,
			.width = NOTIFICATION_SETTING_ITEM_WIDTH,
			.height = NOTIFICATION_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_notification_setting_item_bg,
		},

		{
			.type = TYPE_GUI_DRAW_TEXT,
			.x = NOTIFICATION_SETTING_ITEM_TITLE_X,
			.y = NOTIFICATION_SETTING_TOP,
			.width = NOTIFICATION_SETTING_ITEM_TITLE_WIDTH,
			.height = NOTIFICATION_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_notification_setting_item_title,
		},

		{
			.id = NOTIFICATION_SETTING_LAYOUT_OPEN,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = NOTIFICATION_SETTING_ITEM_BUTTON_X,
			.y = NOTIFICATION_SETTING_TOP,
			.width = NOTIFICATION_SETTING_ITEM_BUTTON_WIDTH,
			.height = NOTIFICATION_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_notification_setting_item_status,
		},

		{
			.type = TYPE_GUI_DRAW_TEXT,
			.x = NOTIFICATION_SETTING_ITEM_TITLE_X,
			.y = NOTIFICATION_SETTING_TOP + NOTIFICATION_SETTING_ITEM_HEIGHT + NOTIFICATION_SETTING_ITEM_GAP,
			.width = NOTIFICATION_SETTING_ITEM_WIDTH - GUI_ITEM_GAP_LEFT * 2,
			.height = NOTIFICATION_SETTING_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_notification_setting_item_hint,
		},
};

const gui_screen_struct gui_screen_notification_setting =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_notification_setting,
		.child_num = countof(gui_widget_notification_setting),
};
