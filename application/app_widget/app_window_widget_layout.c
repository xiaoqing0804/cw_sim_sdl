#include "app_window_widget_layout.h"

static const gui_image_struct gui_widget_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.data = &pic_widget_btn_add_info,
};

static const gui_widget_struct gui_widget_widget[] =
	{
		{
			.id = WIDGET_LAYOUT_ID_ADD,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 0,
			.y = 0,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_widget_image,
		},
};

const gui_screen_struct gui_widget_screen =
	{
		.children = gui_widget_widget,
		.child_num = countof(gui_widget_widget),
};
