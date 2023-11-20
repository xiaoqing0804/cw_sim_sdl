#include "app_window_popup_yesno_layout.h"

#define POPUP_YESNO_BUTTON_LEFT (90)
#define POPUP_YESNO_BUTTON_TOP (306)
#define POPUP_YESNO_BUTTON_WIDTH (102)
#define POPUP_YESNO_BUTTON_HEIGHT (102)

static const gui_font_struct gui_popup_yesno_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value.string = "",
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

static const gui_widget_struct gui_popup_yesno_widget[] =
	{
		{
			.id = POPUP_YESNO_LAYOUT_ID_TITLE,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = GUI_CONTENT_GAP_TOP,
			.width = GUI_CONTENT_WIDTH,
			.height = POPUP_YESNO_BUTTON_TOP - GUI_CONTENT_GAP_TOP,
			.visible = 1,
			.clip = 1,
			.child_num = 1,
			.children = &gui_popup_yesno_title,
		},

		{
			.id = POPUP_YESNO_LAYOUT_ID_NO,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = POPUP_YESNO_BUTTON_LEFT,
			.y = POPUP_YESNO_BUTTON_TOP, // pic_operator2_cancel_info.height,
			.width = POPUP_YESNO_BUTTON_WIDTH,
			.height = POPUP_YESNO_BUTTON_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_cancel_image,
		},
		{
			.id = POPUP_YESNO_LAYOUT_ID_YES,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = LCD_SIZE_WIDTH - POPUP_YESNO_BUTTON_LEFT - POPUP_YESNO_BUTTON_WIDTH,
			.y = POPUP_YESNO_BUTTON_TOP, // pic_operator2_ok_info.height,
			.width = POPUP_YESNO_BUTTON_WIDTH,
			.height = POPUP_YESNO_BUTTON_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_ok_image,
		},
};

const gui_screen_struct gui_popup_yesno_screen =
	{
		.children = gui_popup_yesno_widget,
		.child_num = countof(gui_popup_yesno_widget),
};
