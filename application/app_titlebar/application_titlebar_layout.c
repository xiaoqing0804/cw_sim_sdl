#include "application_titlebar_layout.h"

static const gui_canvas_struct gui_titlebar_bg =
	{
		.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL, // TYPE_GUI_DRAW
		.penSize = 2,
		.penColor = COLOR_RGB(0, 0, 0),
		.canvas.rect.x0 = 0,
		.canvas.rect.y0 = 0,
		.canvas.rect.x1 = LCD_SIZE_WIDTH,
		.canvas.rect.y1 = 88,
};

gui_font_struct gui_titlebar_name =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value.string_id = 0,
		.scroll = 1,
};

/***********************************************/

const gui_widget_struct gui_widget_titlebar_bg =
	{
		.id = GUI_IDS_TITLE_BG,
		.type = TYPE_GUI_CONTROL_CANVAS,
		.width = LCD_SIZE_WIDTH,
		.height = GUI_TITLE_BAR_HEIGHT,
		.order = APP_TITLEBAR_BG_ORDER,
		.visible = 1,
		.fix = 1,
		.child_num = 1,
		.children = &gui_titlebar_bg,
};

const gui_widget_struct gui_widget_titlebar_name =
	{
		.id = GUI_IDS_TITLE_NAME,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = GUI_TITLE_BAR_LEFT,
		.width = GUI_TITLE_BAR_WIDTH,
		.height = GUI_TITLE_BAR_HEIGHT,
		.order = APP_TITLEBAR_BG_ORDER + 1,
		.visible = 1,
		.fix = 1,
		.clip = 1,
		.child_num = 1,
		.children = &gui_titlebar_name,
};
