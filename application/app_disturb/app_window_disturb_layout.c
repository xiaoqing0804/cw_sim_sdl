#include "app_window_disturb.h"
#include "app_window_disturb_ui.h"
#include "app_window_disturb_layout.h"

#include "picture.h"
#include "language.h"
#include "gui_surface_control_base.h"

static const gui_font_struct gui_text_disturb =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_DISTURB_MODE,
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

static const gui_widget_struct gui_widget_disturb[] =
	{
		// 提示语
		{
			.id = DISTURB_LAYOUT_ID_TETX,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 0,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT - 60,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_text_disturb,
		},
		// 关闭按键
		{
			.id = DISTURB_LAYOUT_ID_NO,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 91,
			.y = 306, // pic_operator2_cancel_info.height,
			.width = 102,
			.height = 102,
			.visible = 1,
			.child_num = 1,
			.children = &gui_cancel_image,
		},
		// 确定按键
		{
			.id = DISTURB_LAYOUT_ID_YES,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 270,
			.y = 306, // pic_operator2_ok_info.height,
			.width = 102,
			.height = 102,
			.visible = 1,
			.child_num = 1,
			.children = &gui_ok_image,
		},
};

const gui_screen_struct gui_screen_disturb =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_disturb,
		.child_num = countof(gui_widget_disturb),
};
