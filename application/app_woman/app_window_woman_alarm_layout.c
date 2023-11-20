#include "app_window_woman_alarm_layout.h"

#include "data_common.h"
#include "gui_surface.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_box_layout_item.h"
#include "bsp_motor/motor.h"

static const gui_image_struct gui_woman_alarm_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.id = 0,
		.x = 0,
		.align = GUI_ALIGN_HCENTER,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_woman_bg_info,
};

static const gui_image_struct gui_woman_alarm_yuejin_pic =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.id = 0,
		.x = 0,
		.y = 0,
		.align = GUI_ALIGN_HCENTER,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_woman_yuejin_info,
};

static const gui_font_struct ggui_woman_alarm_yuejin_time =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 2,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.value_align = GUI_ALIGN_HCENTER,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "[ 00/00 ~ 00/00 ]",
};

static const gui_font_struct gui_woman_alarm_yuejin_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.auto_wrap = 0,
		.value_align = GUI_ALIGN_HCENTER,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_WOMAN_YUEJIN,
};

static const gui_widget_struct gui_widget_woman_alarm[] =
	{
		{
			.id = WOMAN_ALARM_LAYOUT_ID_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = ICON_L_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 240,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_woman_alarm_bg,
		},

		{
			.id = WOMAN_ALARM_LAYOUT_ID_PIC,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.y = ICON_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 240,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_woman_alarm_yuejin_pic,
		},

		{
			.id = WOMAN_ALARM_LAYOUT_ID_TIME,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = VALUE_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 70,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &ggui_woman_alarm_yuejin_time,
		},

		{
			.id = WOMAN_ALARM_LAYOUT_ID_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = NAME_Y,
			.width = LCD_SIZE_WIDTH,
			.height = 240,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_woman_alarm_yuejin_txt,
		},
};

const gui_screen_struct gui_screen_woman_alarm =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_woman_alarm,
		.child_num = countof(gui_widget_woman_alarm),
};
