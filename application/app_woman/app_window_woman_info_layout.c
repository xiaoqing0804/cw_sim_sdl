#include "app_window_woman_info_layout.h"

#include "data_common.h"
#include "gui_surface.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_box_layout_item.h"

static const gui_font_struct ggui_woman_alarm_yuejin_time =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "[ 00/00 ~ 00/00 ]",
};

static const gui_font_struct gui_text_woman_anquan_time =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "[ 00/00 ~ 00/00 ]",
};

static const gui_font_struct gui_text_woman_pairuan_time =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "[ 00/00 ~ 00/00 ]",
};

static const gui_image_struct gui_woman_alarm_yuejin_pic =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.x = LCD_SIZE_HALF_WIDTH,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_woman_yuejin_info,
};

static gui_image_struct gui_woman_alarm_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_woman_bg_info,
};

static const gui_font_struct gui_woman_alarm_yuejin_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_WOMAN_YUEJIN,
};

static const gui_image_struct gui_pic_woman_anquan =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_woman_anquan_info,
};

static const gui_font_struct gui_text_woman_anquan =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_WOMAN_ANQUAN,
};

static const gui_image_struct gui_pic_woman_pairuan =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_woman_pailuan_info,
};

static const gui_font_struct gui_text_woman_pairuan =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_WOMAN_PAILUAN,
};

static const gui_widget_struct gui_widget_woman_info[] =
	{
		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = ICON_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_woman_alarm_yuejin_pic,
		},

		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = NAME_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_woman_alarm_yuejin_txt,
		},

		{
			.id = WOMAN_INFO_LAYOUT_ID_YUEJIN,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = VALUE_Y,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &ggui_woman_alarm_yuejin_time,
		},

		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = ICON_L_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_woman_alarm_bg,
		},

		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = LCD_SIZE_HEIGHT + ICON_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_pic_woman_anquan,
		},

		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = LCD_SIZE_HEIGHT + NAME_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_woman_anquan,
		},

		{
			.id = WOMAN_INFO_LAYOUT_ID_ANQUAN,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = LCD_SIZE_HEIGHT + VALUE_Y,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_text_woman_anquan_time,
		},

		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = LCD_SIZE_HEIGHT + ICON_L_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_woman_alarm_bg,
		},

		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = LCD_SIZE_HEIGHT * 2 + ICON_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_pic_woman_pairuan,
		},

		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = LCD_SIZE_HEIGHT * 2 + NAME_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_woman_pairuan,
		},

		{
			.id = WOMAN_INFO_LAYOUT_ID_PAIRUAN,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = LCD_SIZE_HEIGHT * 2 + VALUE_Y,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_text_woman_pairuan_time,
		},

		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = LCD_SIZE_HEIGHT * 2 + ICON_L_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 60,
			.visible = 1,
			.child_num = 1,
			.children = &gui_woman_alarm_bg,
		},

};

const gui_layout_scroll_struct gui_woman_info =
	{
		.height = LCD_SIZE_HEIGHT * 3,
		.scroll = 1,
};

const gui_screen_struct gui_screen_woman_info =
	{
		.type = TYPE_GUI_LAYOUT_SCROLL,
		.children = gui_widget_woman_info,
		.child_num = countof(gui_widget_woman_info),
		.layout_config = &gui_woman_info,
};
