#include "app_window_power_off_layout.h"

static const gui_image_struct gui_power_off_bg_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_setting_list_icon_bg_4_info,
};

static const gui_image_struct gui_power_off_icon_shutdown_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_power_off_shutdown_info,
};

static const gui_image_struct gui_power_off_icon_reboot_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_power_off_reboot_info,
};

static const gui_image_struct gui_power_off_icon_sos_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_power_off_sos_info,
};

static const gui_font_struct gui_power_off_title_shutdown_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_SHUTDOWN,
};

static const gui_font_struct gui_power_off_title_reboot_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_REBOOT,
};

static const gui_font_struct gui_power_off_title_sos_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string = "SOS",
};

static const gui_widget_struct gui_widget_power_off[] =
	{

		//---------------------bg---------------------------------
		{
			.id = POWER_OFF_LAYOUT_ID_SHUTDOWN_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = POWER_OFF_CONTENT_LEFT,
			.y = POWER_OFF_ITEM_Y(0),
			.width = POWER_OFF_ITEM_WIDTH,
			.height = POWER_OFF_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_power_off_bg_image,
		},

		{
			.id = POWER_OFF_LAYOUT_ID_REBOOT_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = POWER_OFF_CONTENT_LEFT,
			.y = POWER_OFF_ITEM_Y(1),
			.width = POWER_OFF_ITEM_WIDTH,
			.height = POWER_OFF_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_power_off_bg_image,
		},

		{
			.id = POWER_OFF_LAYOUT_ID_SOS_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = POWER_OFF_CONTENT_LEFT,
			.y = POWER_OFF_ITEM_Y(2),
			.width = POWER_OFF_ITEM_WIDTH,
			.height = POWER_OFF_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_power_off_bg_image,
		},

		//---------------------icon---------------------------------
		{
			.id = POWER_OFF_LAYOUT_ID_SHUTDOWN_ICON,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = POWER_OFF_CONTENT_LEFT + POWER_OFF_ICON_LEFT,
			.y = POWER_OFF_ITEM_Y(0) + POWER_OFF_ICON_TOP,
			.width = POWER_OFF_ICON_WIDTH,
			.height = POWER_OFF_ICON_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_power_off_icon_shutdown_image,
		},
		{
			.id = POWER_OFF_LAYOUT_ID_REBOOT_ICON,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = POWER_OFF_CONTENT_LEFT + POWER_OFF_ICON_LEFT,
			.y = POWER_OFF_ITEM_Y(1) + POWER_OFF_ICON_TOP,
			.width = POWER_OFF_ICON_WIDTH,
			.height = POWER_OFF_ICON_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_power_off_icon_reboot_image,
		},
		{
			.id = POWER_OFF_LAYOUT_ID_SOS_ICON,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = POWER_OFF_CONTENT_LEFT + POWER_OFF_ICON_LEFT,
			.y = POWER_OFF_ITEM_Y(2) + POWER_OFF_ICON_TOP,
			.width = POWER_OFF_ICON_WIDTH,
			.height = POWER_OFF_ICON_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_power_off_icon_sos_image,
		},

		//---------------------text---------------------------------
		{
			.id = POWER_OFF_LAYOUT_ID_SHUTDOWN_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = POWER_OFF_CONTENT_LEFT + POWER_OFF_TITLE_LEFT,
			.y = POWER_OFF_ITEM_Y(0) + POWER_OFF_TITLE_TOP,
			.width = POWER_OFF_TITLE_WIDTH,
			.height = POWER_OFF_TITLE_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_power_off_title_shutdown_text,
		},
		{
			.id = POWER_OFF_LAYOUT_ID_REBOOT_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = POWER_OFF_CONTENT_LEFT + POWER_OFF_TITLE_LEFT,
			.y = POWER_OFF_ITEM_Y(1) + POWER_OFF_TITLE_TOP,
			.width = POWER_OFF_TITLE_WIDTH,
			.height = POWER_OFF_TITLE_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_power_off_title_reboot_text,
		},
		{
			.id = POWER_OFF_LAYOUT_ID_SOS_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = POWER_OFF_CONTENT_LEFT + POWER_OFF_TITLE_LEFT,
			.y = POWER_OFF_ITEM_Y(2) + POWER_OFF_TITLE_TOP,
			.width = POWER_OFF_TITLE_WIDTH,
			.height = POWER_OFF_TITLE_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_power_off_title_sos_text,
		},
};

const gui_screen_struct app_screen_power_off =
	{
		.children = gui_widget_power_off,
		.child_num = countof(gui_widget_power_off),
};
