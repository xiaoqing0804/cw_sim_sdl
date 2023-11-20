#include "app_window_moreinfo_style_layout.h"

#define MOREINFO_STYLE_ITEM_ICON_X (GUI_ITEM_GAP_LEFT)
#define MOREINFO_STYLE_ITEM_ICON_Y ((GUI_ITEM_HEIGHT - 62) / 2)

#define MOREINFO_STYLE_ITEM_TXT_X (108)
#define MOREINFO_STYLE_ITEM_TXT_Y (0)
#define MOREINFO_STYLE_ITEM_TXT_WIDTH (230)

#define MOREINFO_STYLE_ITEM_Y(index) (GUI_CONTENT_GAP_TOP + (index) * (GUI_ITEM_HEIGHT + GUI_ITEM_SPACE))

static const gui_image_struct gui_moreinfo_style_item_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_moreinfo_style_item_arrow =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 23,
		.y = (GUI_ITEM_HEIGHT - 46) / 2,
		.data = &pic_setting_list_hint_arrow_info,
};

static const gui_image_struct gui_moreinfo_style_item_status =
	{
		.id = MOREINFO_STYLE_LAYOUT_ID_CHECKED,
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 44,
		.y = (GUI_ITEM_HEIGHT - 44) / 2,
		.data = &pic_setting_list_status_checked_info,
};

/**********************************matrix***************************************/

static const gui_image_struct gui_moreinfo_style_item_matrix_pic =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = MOREINFO_STYLE_ITEM_ICON_X,
		.y = MOREINFO_STYLE_ITEM_ICON_Y,
		.data = &pic_moreinfo_style_matrix_info,
};

const gui_font_struct gui_moreinfo_style_item_matrix_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = MOREINFO_STYLE_ITEM_TXT_X,
		.y = MOREINFO_STYLE_ITEM_TXT_Y,
		.width = MOREINFO_STYLE_ITEM_TXT_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_MOREINFO_MATRIX,
		.scroll = 1,
};

static const gui_mix_struct gui_item_style_matrix[] =
	{
		{
			.data = &gui_moreinfo_style_item_bg,
		},
		{
			.data = &gui_moreinfo_style_item_matrix_pic,
		},
		{
			.data = &gui_moreinfo_style_item_matrix_txt,
		},
		{
			.data = &gui_moreinfo_style_item_status,
		},
};

/**********************************cellular***************************************/

static const gui_image_struct gui_moreinfo_style_item_cellular_pic =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = MOREINFO_STYLE_ITEM_ICON_X,
		.y = MOREINFO_STYLE_ITEM_ICON_Y,
		.data = &pic_moreinfo_style_cell_info,
};

const gui_font_struct gui_moreinfo_style_item_cellular_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = MOREINFO_STYLE_ITEM_TXT_X,
		.y = MOREINFO_STYLE_ITEM_TXT_Y,
		.width = MOREINFO_STYLE_ITEM_TXT_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_MOREINFO_CELL,
		.scroll = 1,
};

static const gui_mix_struct gui_item_style_cellular[] =
	{
		{
			.data = &gui_moreinfo_style_item_bg,
		},
		{
			.data = &gui_moreinfo_style_item_cellular_pic,
		},
		{
			.data = &gui_moreinfo_style_item_cellular_txt,
		},
		{
			.data = &gui_moreinfo_style_item_status,
		},
};

/**********************************kaleidoscope***************************************/

static const gui_image_struct gui_moreinfo_style_item_kaleidoscope_pic =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = MOREINFO_STYLE_ITEM_ICON_X,
		.y = MOREINFO_STYLE_ITEM_ICON_Y,
		.data = &pic_moreinfo_style_kaleidoscope_info,
};

const gui_font_struct gui_moreinfo_style_item_kaleidoscope_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = MOREINFO_STYLE_ITEM_TXT_X,
		.y = MOREINFO_STYLE_ITEM_TXT_Y,
		.width = MOREINFO_STYLE_ITEM_TXT_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_MOREINFO_KALE,
		.scroll = 1,
};

static const gui_mix_struct gui_item_style_kaleidoscope[] =
	{
		{
			.data = &gui_moreinfo_style_item_bg,
		},
		{
			.data = &gui_moreinfo_style_item_kaleidoscope_pic,
		},
		{
			.data = &gui_moreinfo_style_item_kaleidoscope_txt,
		},
		{
			.data = &gui_moreinfo_style_item_status,
		},
};

/**********************************list***************************************/

static const gui_image_struct gui_moreinfo_style_item_list_pic =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = MOREINFO_STYLE_ITEM_ICON_X,
		.y = MOREINFO_STYLE_ITEM_ICON_Y,
		.data = &pic_moreinfo_style_list_info,
};

const gui_font_struct gui_moreinfo_style_item_list_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = MOREINFO_STYLE_ITEM_TXT_X,
		.y = MOREINFO_STYLE_ITEM_TXT_Y,
		.width = MOREINFO_STYLE_ITEM_TXT_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_MOREINFO_LIST,
		.scroll = 1,
};

static const gui_mix_struct gui_item_style_list[] =
	{
		{
			.data = &gui_moreinfo_style_item_bg,
		},
		{
			.data = &gui_moreinfo_style_item_list_pic,
		},
		{
			.data = &gui_moreinfo_style_item_list_txt,
		},
		{
			.data = &gui_moreinfo_style_item_status,
		},
};

/**********************************ring two***************************************/

static const gui_image_struct gui_moreinfo_style_item_ring_two_pic =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = MOREINFO_STYLE_ITEM_ICON_X,
		.y = MOREINFO_STYLE_ITEM_ICON_Y,
		.data = &pic_moreinfo_style_ring_info,
};

const gui_font_struct gui_moreinfo_style_item_ring_two_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = MOREINFO_STYLE_ITEM_TXT_X,
		.y = MOREINFO_STYLE_ITEM_TXT_Y,
		.width = MOREINFO_STYLE_ITEM_TXT_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_MOREINFO_RING_TWO,
		.scroll = 1,
};

static const gui_mix_struct gui_item_style_ring[] =
	{
		{
			.data = &gui_moreinfo_style_item_bg,
		},
		{
			.data = &gui_moreinfo_style_item_ring_two_pic,
		},
		{
			.data = &gui_moreinfo_style_item_ring_two_txt,
		},
		{
			.data = &gui_moreinfo_style_item_status,
		},

};

/*************************************************************************/

static const gui_widget_struct gui_widget_moreinfo_style[] =
	{
		{
			.id = MOREINFO_WINDOW_STYLE_RING_TWO,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = MOREINFO_STYLE_ITEM_Y(0),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_item_style_ring),
			.children = gui_item_style_ring,
		},

		{
			.id = MOREINFO_WINDOW_STYLE_LIST,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = MOREINFO_STYLE_ITEM_Y(1),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_item_style_list),
			.children = gui_item_style_list,
		},

		{
			.id = MOREINFO_WINDOW_STYLE_KALEIDOSCOPE,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = MOREINFO_STYLE_ITEM_Y(2),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_item_style_kaleidoscope),
			.children = gui_item_style_kaleidoscope,
		},

		{
			.id = MOREINFO_WINDOW_STYLE_CELL,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = MOREINFO_STYLE_ITEM_Y(3),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_item_style_cellular),
			.children = gui_item_style_cellular,
		},

		{
			.id = MOREINFO_WINDOW_STYLE_MATRIX,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = MOREINFO_STYLE_ITEM_Y(4),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_item_style_matrix),
			.children = gui_item_style_matrix,
		},
};

const gui_layout_list_struct gui_layout_config_moreinfo_style =
	{
		.row_height = GUI_ITEM_HEIGHT,

		.top = GUI_CONTENT_GAP_TOP,
		.bottom = GUI_CONTENT_GAP_BOTTOM,
		.space = GUI_ITEM_SPACE,
		.scroll = 1,
};

const gui_screen_struct app_screen_moreinfo_style =
	{
		.type = TYPE_GUI_LAYOUT_LIST,
		.children = gui_widget_moreinfo_style,
		.child_num = countof(gui_widget_moreinfo_style),
		.layout_config = &gui_layout_config_moreinfo_style,
};
