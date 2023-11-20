#include "picture.h"
#include "language.h"
#include "app_window_qr_card_list_layout.h"

#if defined(GUI_QR_INFO_SUPPORT)&&GUI_QR_INFO_SUPPORT

static const gui_layout_list_struct gui_qr_card_list_layout =
{
	.row_height = QR_CARD_LIST_ITEM_HEIGHT,
	.top = 60,
	.bottom = 15,
	.space = 20,
	.scroll = 1,
};

static const gui_font_struct gui_qr_card_nothing =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .size = SYS_FONT_MEDIUM,
    .auto_wrap = 1,
    .width = LCD_SIZE_WIDTH,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string = STRING_CARD,
};


static const gui_widget_struct gui_qr_card_list_widgets[] =
{
	{
		.id = QR_CARD_LIST_NO,
		.type = TYPE_GUI_CONTROL_LABEL,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_qr_card_nothing,
	},
};

const gui_screen_struct gui_screen_qr_card_list =
{
	.type = TYPE_GUI_LAYOUT_LIST,
	.children = gui_qr_card_list_widgets,
    .child_num = countof(gui_qr_card_list_widgets),
	.layout_config = &gui_qr_card_list_layout,
};

#endif

