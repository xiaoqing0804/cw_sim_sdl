#include "app_window_aod_dial_layout.h"
#include "application_config_app_info.h"

#define SETTING_SCREEN_ITEM_Y(index) (GUI_CONTENT_GAP_TOP + (index) * (GUI_ITEM_HEIGHT + GUI_ITEM_SPACE))

static const gui_image_struct gui_aod_dial_item_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = 0,
		.y = 0,
		.data = &pic_setting_list_icon_bg_2_info,
};

static const gui_image_struct gui_aod_dial_item_arrow =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 23,
		.y = (GUI_ITEM_HEIGHT - 46) / 2,
		.data = &pic_setting_list_hint_arrow_info,
};

static const gui_image_struct gui_aod_dial_item_status =
	{
		.id = AOD_DIAL_LAYOUT_ID_OPEN_STATUS,
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 88,
		.y = (GUI_ITEM_HEIGHT - 52) / 2,
		.data = &pic_setting_list_status_open_info,
};

static const gui_image_struct gui_aod_dial_item_checked =
	{
		.id = AOD_DIAL_LAYOUT_ID_CHECKED,
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = GUI_CONTENT_WIDTH - GUI_ITEM_GAP_RIGHT - 44,
		.y = (GUI_ITEM_HEIGHT - 44) / 2,
		.data = &pic_setting_list_status_checked_info,
};

/**********************************watchface_pointer***************************************/

const gui_font_struct gui_aod_dial_item_watchface_pointer =
	{
		.id = AOD_DIAL_LAYOUT_ID_TITLE,
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
		.value.string_id = STRING_WATCHFACE_IDLE_POINTER,
};

const gui_font_struct gui_aod_dial_item_watchface_pointer_gray =
	{
		.id = AOD_DIAL_LAYOUT_ID_TITLE_GRAY,
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.y = 0,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(128, 128, 128),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_WATCHFACE_IDLE_POINTER,
};

static const gui_mix_struct gui_aod_dial_watchface_pointer[] =
	{
		{
			.data = &gui_aod_dial_item_bg,
		},
		{
			.data = &gui_aod_dial_item_watchface_pointer,
		},
		{
			.data = &gui_aod_dial_item_watchface_pointer_gray,
		},
		{
			.data = &gui_aod_dial_item_checked,
		},
};

/**********************************watchface_number***************************************/

static const gui_font_struct gui_aod_dial_item_watchface_number =
	{
		.id = AOD_DIAL_LAYOUT_ID_TITLE,
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
		.value.string_id = STRING_WATCHFACE_IDLE_NUMBER,
};

static const gui_font_struct gui_aod_dial_item_watchface_number_gray =
	{
		.id = AOD_DIAL_LAYOUT_ID_TITLE_GRAY,
		.type = TYPE_GUI_DRAW_TEXT,
		.x = GUI_ITEM_GAP_LEFT,
		.y = 0,
		.width = GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH,
		.height = GUI_ITEM_HEIGHT,
		.scroll = 1,
		.color = COLOR_RGB(128, 128, 128),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_VCENTER,
		.value.string_id = STRING_WATCHFACE_IDLE_NUMBER,
};

static const gui_mix_struct gui_aod_dial_watchface_number[] =
	{
		{
			.data = &gui_aod_dial_item_bg,
		},
		{
			.data = &gui_aod_dial_item_watchface_number,
		},
		{
			.data = &gui_aod_dial_item_watchface_number_gray,
		},
		{
			.data = &gui_aod_dial_item_checked,
		},
};

/**********************************on_off***************************************/

const gui_font_struct gui_text_screen_on_off =
	{
		.id = AOD_DIAL_LAYOUT_ID_TITLE,
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
		.value.string_id = STRING_SCREEN_OFF_CLOCK,
};

static const gui_mix_struct gui_aod_dial_on_off[] =
	{
		{
			.data = &gui_aod_dial_item_bg,
		},
		{
			.data = &gui_text_screen_on_off,
		},
		{
			.data = &gui_aod_dial_item_status,
		},
};

/*************************************************************************/

static const gui_widget_struct gui_widget_aod_dial_list[] =
	{
		{
			.id = AOD_DIAL_LAYOUT_ID_OPEN,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_SCREEN_ITEM_Y(0),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_aod_dial_on_off),
			.children = gui_aod_dial_on_off,
		},

		{
			.id = AOD_DIAL_LAYOUT_ID_NUMBER,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_SCREEN_ITEM_Y(1),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_aod_dial_watchface_number),
			.children = gui_aod_dial_watchface_number,
		},

		{
			.id = AOD_DIAL_LAYOUT_ID_POINTER,
			.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
			.x = GUI_CONTENT_GAP_LEFT,
			.y = SETTING_SCREEN_ITEM_Y(2),
			.width = GUI_CONTENT_WIDTH,
			.height = GUI_ITEM_HEIGHT,
			.visible = 1,
			.clip = 1,
			.child_num = countof(gui_aod_dial_watchface_pointer),
			.children = gui_aod_dial_watchface_pointer,
		},
};

const gui_layout_list_struct gui_layout_config_aod_dial =
	{
		.row_height = GUI_ITEM_HEIGHT,

		.top = GUI_CONTENT_GAP_TOP,
		.bottom = GUI_CONTENT_GAP_BOTTOM,
		.space = GUI_ITEM_SPACE,
		.scroll = 1,
};

const gui_screen_struct gui_screen_aod_dial =
	{
		.type = TYPE_GUI_LAYOUT_LIST,
		.children = gui_widget_aod_dial_list,
		.child_num = countof(gui_widget_aod_dial_list),
		.layout_config = &gui_layout_config_aod_dial,
};
