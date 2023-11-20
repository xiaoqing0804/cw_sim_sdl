#include "app_window_reboot_layout.h"

#define REBOOT_BUTTON_LEFT (90)
#define REBOOT_BUTTON_TOP (306)
#define REBOOT_BUTTON_WIDTH (102)
#define REBOOT_BUTTON_HEIGHT (102)

static const gui_font_struct gui_reboot_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.auto_wrap = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value.string_id = STRING_REBOOT_TIP,
};

static const gui_image_struct gui_cancel_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_operator2_cancel_info,
};

static const gui_image_struct gui_ok_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_operator2_ok_info,
};

static const gui_widget_struct gui_reboot_widget[] =
	{
		{
			.id = REBOOT_LAYOUT_ID_TITLE,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = GUI_CONTENT_GAP_TOP,
			.width = GUI_CONTENT_WIDTH,
			.height = REBOOT_BUTTON_TOP - GUI_CONTENT_GAP_TOP,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_reboot_title,
		},

		{
			.id = REBOOT_LAYOUT_ID_NO,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = REBOOT_BUTTON_LEFT,
			.y = REBOOT_BUTTON_TOP, // pic_operator2_cancel_info.height,
			.width = REBOOT_BUTTON_WIDTH,
			.height = REBOOT_BUTTON_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_cancel_image,
		},
		{
			.id = REBOOT_LAYOUT_ID_YES,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = LCD_SIZE_WIDTH - REBOOT_BUTTON_LEFT - REBOOT_BUTTON_WIDTH,
			.y = REBOOT_BUTTON_TOP, // pic_operator2_ok_info.height,
			.width = REBOOT_BUTTON_WIDTH,
			.height = REBOOT_BUTTON_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_ok_image,
		},
};

const gui_screen_struct gui_reboot_screen =
	{
		.children = gui_reboot_widget,
		.child_num = countof(gui_reboot_widget),
};
