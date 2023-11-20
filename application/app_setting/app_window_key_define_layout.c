#include "app_window_key_define_layout.h"

#define KEY_DEFINE_ITEM_Y(index) (GUI_CONTENT_GAP_TOP + (index) * (GUI_ITEM_HEIGHT + GUI_ITEM_SPACE))
#define KEY_DEFINE_ITEM_WIDTH (340)

static const gui_image_struct gui_key_define_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_key_define_arrow =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 23,
		.y = (GUI_ITEM_HEIGHT - 46) / 2,
		.data = &pic_setting_list_hint_arrow_info,
};

/*********************restore**********************/
static const gui_font_struct gui_key_define_key_long_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = KEY_DEFINE_ITEM_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_KEY_LONG,
		.scroll = 1,
};

static const gui_mix_struct gui_key_define_key_long[] =
	{
		{
			.data = &gui_key_define_bg,
		},
		{
			.data = &gui_key_define_key_long_title,
		},
		{
			.data = &gui_key_define_arrow,
		},
};

/*********************double**********************/
static const gui_font_struct gui_key_define_double_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = KEY_DEFINE_ITEM_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_KEY_DOUBLE,
		.scroll = 1,
};

static const gui_mix_struct gui_key_define_double[] =
	{
		{
			.data = &gui_key_define_bg,
		},
		{
			.data = &gui_key_define_double_title,
		},
		{
			.data = &gui_key_define_arrow,
		},
};

/*********************click**********************/
static const gui_font_struct gui_key_define_click_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = KEY_DEFINE_ITEM_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_SETTING_CLICK,
		.scroll = 1,
};

static const gui_mix_struct gui_key_define_click[] =
	{
		{
			.data = &gui_key_define_bg,
		},
		{
			.data = &gui_key_define_click_title,
		},
		{
			.data = &gui_key_define_arrow,
		},
};

/***************************************************************************/

static const gui_widget_struct gui_widget_key_define[] =
	{
		/*
		{
			.id = KEY_DEFINE_LAYOUT_ID_CLICK,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = KEY_DEFINE_ITEM_Y(0),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_key_define_click),
			.children = gui_key_define_click,
		},
		*/
		{
			.id = KEY_DEFINE_LAYOUT_ID_DOUBLE,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = KEY_DEFINE_ITEM_Y(0),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_key_define_double),
			.children = gui_key_define_double,
		},
		{
			.id = KEY_DEFINE_LAYOUT_ID_LONG_TOUCH,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = KEY_DEFINE_ITEM_Y(1),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_key_define_key_long),
			.children = gui_key_define_key_long,
		},
};

const gui_layout_list_struct gui_layout_config_key_define =
	{
		.row_height = GUI_ITEM_HEIGHT,

		.top = GUI_CONTENT_GAP_TOP,
		.bottom = GUI_CONTENT_GAP_BOTTOM,
		.space = GUI_ITEM_SPACE,

		.scroll = 1,
};

const gui_screen_struct gui_screen_key_define =
	{
		.type = TYPE_GUI_LAYOUT_LIST,
		.children = gui_widget_key_define,
		.child_num = countof(gui_widget_key_define),
		.layout_config = &gui_layout_config_key_define,
};
