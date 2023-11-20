#include "app_window_setting_screen_layout.h"
#include "application_config_app_info.h"

#define SETTING_SCREEN_ITEM_Y(index) (GUI_CONTENT_GAP_TOP + (index) * (GUI_ITEM_HEIGHT + GUI_ITEM_SPACE))

static const gui_image_struct gui_setting_screen_item_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_setting_screen_item_arrow =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 23,
		.y = (GUI_ITEM_HEIGHT - 46) / 2,
		.data = &pic_setting_list_hint_arrow_info,
};

static const gui_image_struct gui_setting_screen_item_status =
	{
		.id = APP_SETTING_SCREEN_LAYOUT_ID_OPEN,
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 88,
		.y = (GUI_ITEM_HEIGHT - 52) / 2,
		.data = &pic_setting_list_status_open_info,
};

/**********************************lcd_timeout***************************************/

const gui_font_struct gui_setting_screen_item_lcd_timeout =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.y = 0,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_LCD_TIMEOUT,
};

static const gui_mix_struct gui_setting_screen_lcd_timeout[] =
	{

		{
			.data = &gui_setting_screen_item_bg,
		},
		{
			.data = &gui_setting_screen_item_lcd_timeout,
		},
		{
			.data = &gui_setting_screen_item_arrow,
		},
};

/**********************************always_on_display***************************************/

const gui_font_struct gui_setting_screen_item_always_on_display =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.y = 0,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_STANDBY_DIAL,
};

static const gui_mix_struct gui_setting_screen_always_on_display[] =
	{
		{
			.data = &gui_setting_screen_item_bg,
		},
		{
			.data = &gui_setting_screen_item_always_on_display,
		},
		{
			.data = &gui_setting_screen_item_arrow,
		},
};

/**********************************watchface***************************************/

static const gui_font_struct gui_setting_screen_item_watchface =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.y = 0,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_WATCHFACE_SELECT,
};

static const gui_mix_struct gui_setting_screen_watchface[] =
	{
		{
			.data = &gui_setting_screen_item_bg,
		},
		{
			.data = &gui_setting_screen_item_watchface,
		},
		{
			.data = &gui_setting_screen_item_arrow,
		},
};

/**********************************wrist***************************************/

const gui_font_struct gui_text_screen_wrist =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.y = 0,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_WRIST,
};

static const gui_mix_struct gui_setting_screen_wrist[] =
	{
		{
			.data = &gui_setting_screen_item_bg,
		},
		{
			.data = &gui_text_screen_wrist,
		},
		{
			.data = &gui_setting_screen_item_status,
		},
};

/**********************************brightness***************************************/

static const gui_image_struct gui_setting_screen_pic_sub =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_ITEM_GAP_LEFT,
		.y = (GUI_ITEM_HEIGHT - 48) / 2,
		.data = &pic_screen_brightness_low_info,
};

static const gui_image_struct gui_setting_screen_pic_add =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 56,
		.y = (GUI_ITEM_HEIGHT - 56) / 2,
		.data = &pic_screen_brightness_high_info,
};

static const gui_image_struct gui_setting_screen_pic_progress_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = (GUI_CONTENT_WIDTH - 246) / 2 - 4,
		.y = (GUI_ITEM_HEIGHT - 18) / 2,
		.data = &pic_setting_list_icon_progress_bg_info,
};

static const gui_image_struct gui_setting_screen_pic_progress_bar =
	{
		.id = APP_SETTING_SCREEN_LAYOUT_ID_BRIGHTNESS,
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = (GUI_CONTENT_WIDTH - 246) / 2 - 4,
		.y = (GUI_ITEM_HEIGHT - 18) / 2,
		.data = &pic_setting_list_icon_progress_bar_info,
};

static const gui_mix_struct gui_setting_screen_brightness[] =
	{
		{
			.data = &gui_setting_screen_item_bg,
		},
		{
			.data = &gui_setting_screen_pic_sub,
		},
		{
			.data = &gui_setting_screen_pic_add,
		},
		{
			.data = &gui_setting_screen_pic_progress_bg,
		},
		{
			.data = &gui_setting_screen_pic_progress_bar,
		},
};

/*************************************************************************/

static const gui_widget_struct gui_widget_setting_screen_list[] =
	{
		{
			.id = APP_INFO_ID_BRIGHTNESS,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_SCREEN_ITEM_Y(0),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_screen_brightness),
			.children = gui_setting_screen_brightness,
		},

		{
			.id = APP_INFO_ID_WRIST,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_SCREEN_ITEM_Y(1),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_screen_wrist),
			.children = gui_setting_screen_wrist,
		},

		{
			.id = APP_INFO_ID_WATCHFACE,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_SCREEN_ITEM_Y(2),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_screen_watchface),
			.children = gui_setting_screen_watchface,
		},

		{
			.id = APP_INFO_ID_AOD_DIAL,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_SCREEN_ITEM_Y(3),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_screen_always_on_display),
			.children = gui_setting_screen_always_on_display,
		},

		{
			.id = APP_INFO_ID_LCDTIMEOUT,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_SCREEN_ITEM_Y(4),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_setting_screen_lcd_timeout),
			.children = gui_setting_screen_lcd_timeout,
		},
};

const gui_layout_list_struct gui_layout_config_setting_screen =
	{
		.row_height = GUI_ITEM_HEIGHT,

		.top = GUI_CONTENT_GAP_TOP,
		.bottom = GUI_CONTENT_GAP_BOTTOM,
		.space = GUI_ITEM_SPACE,
		.scroll = 1,
};

const gui_screen_struct gui_screen_setting_screen =
	{
		.type = TYPE_GUI_LAYOUT_LIST,
		.children = gui_widget_setting_screen_list,
		.child_num = countof(gui_widget_setting_screen_list),
		.layout_config = &gui_layout_config_setting_screen,
};
