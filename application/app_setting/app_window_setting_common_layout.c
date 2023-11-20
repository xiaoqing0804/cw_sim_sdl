#include "app_window_setting_common_layout.h"

#define SETTING_COMMON_ITEM_Y(index) (GUI_CONTENT_GAP_TOP + (index) * (GUI_ITEM_HEIGHT + GUI_ITEM_SPACE))

static const gui_image_struct gui_setting_common_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_setting_common_arrow =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 23,
		.y = (GUI_ITEM_HEIGHT - 46) / 2,
		.data = &pic_setting_list_hint_arrow_info,
};

/*************************about********************************/

static const gui_font_struct gui_setting_common_about_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_ABOUT,
		.scroll = 1,
};

static const gui_mix_struct gui_setting_common_about[] =
	{
		{
			.data = &gui_setting_common_bg,
		},
		{
			.data = &gui_setting_common_about_title,
		},
		{
			.data = &gui_setting_common_arrow,
		},
};

/********************language**********************/
static const gui_font_struct gui_setting_common_language_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_LANGUAGE,
		.scroll = 1,
};

static const gui_mix_struct gui_setting_common_language[] =
	{
		{
			.data = &gui_setting_common_bg,
		},
		{
			.data = &gui_setting_common_language_title,
		},
		{
			.data = &gui_setting_common_arrow,
		},
};

/*************************QR*************************/
static const gui_font_struct gui_setting_common_qr_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_CONNECT_PHONE,
		.scroll = 1,
};

static const gui_mix_struct gui_setting_common_connect_phone[] =
	{
		{
			.data = &gui_setting_common_bg,
		},
		{
			.data = &gui_setting_common_qr_title,
		},
		{
			.data = &gui_setting_common_arrow,
		},
};

/*********************restore**********************/
static const gui_font_struct gui_setting_common_restore_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_RESET_FACTORY,
		.scroll = 1,
};

static const gui_mix_struct gui_setting_common_restore[] =
	{
		{
			.data = &gui_setting_common_bg,
		},
		{
			.data = &gui_setting_common_restore_title,
		},
		{
			.data = &gui_setting_common_arrow,
		},
};

/*********************reboot**********************/
static const gui_font_struct gui_setting_common_reboot_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_REBOOT,
		.scroll = 1,
};

static const gui_mix_struct gui_setting_common_reboot[] =
	{
		{
			.data = &gui_setting_common_bg,
		},
		{
			.data = &gui_setting_common_reboot_title,
		},
		{
			.data = &gui_setting_common_arrow,
		},
};

/*********************shutdown**********************/
static const gui_font_struct gui_setting_common_shutdown_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_SHUTDOWN,
		.scroll = 1,
};

static const gui_mix_struct gui_setting_common_shutdown[] =
	{
		{
			.data = &gui_setting_common_bg,
		},
		{
			.data = &gui_setting_common_shutdown_title,
		},
		{
			.data = &gui_setting_common_arrow,
		},
};

/***************************************************************************/

static const gui_widget_struct gui_widget_setting_common[] =
	{
		{
			.id = APP_INFO_ID_ABOUT,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_COMMON_ITEM_Y(0),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_common_about),
			.children = gui_setting_common_about,
		},
		{
			.id = APP_INFO_ID_LANGUAGE,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_COMMON_ITEM_Y(1),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_common_language),
			.children = gui_setting_common_language,
		},
		{
			.id = APP_INFO_ID_QR,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_COMMON_ITEM_Y(2),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_common_connect_phone),
			.children = gui_setting_common_connect_phone,
		},

#if (LCD_SHAPE != LCD_CIRCLE)
		{
			.id = APP_INFO_ID_BED,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_COMMON_ITEM_Y(0),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_common_connect_phone),
			.children = gui_setting_common_connect_phone,
		},
#endif

		{
			.id = APP_INFO_ID_RESTORE,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_COMMON_ITEM_Y(3),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_common_restore),
			.children = gui_setting_common_restore,
		},
		{
			.id = APP_INFO_ID_REBOOT,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_COMMON_ITEM_Y(4),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_common_reboot),
			.children = gui_setting_common_reboot,
		},
		{
			.id = APP_INFO_ID_SHUTDOWN,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_COMMON_ITEM_Y(5),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_common_shutdown),
			.children = gui_setting_common_shutdown,
		},
};

const gui_layout_list_struct gui_layout_config_setting_common =
	{
		.row_height = GUI_ITEM_HEIGHT,

		.top = GUI_CONTENT_GAP_TOP,
		.bottom = GUI_CONTENT_GAP_BOTTOM,
		.space = GUI_ITEM_SPACE,

		.scroll = 1,
};

const gui_screen_struct gui_screen_setting_common =
	{
		.type = TYPE_GUI_LAYOUT_LIST,
		.children = gui_widget_setting_common,
		.child_num = countof(gui_widget_setting_common),
		.layout_config = &gui_layout_config_setting_common,
};
