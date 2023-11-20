#include "app_window_breath_start_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_core_screen.h"
#include "gui_surface_control_animation.h"

static const gui_image_struct gui_breath_start_ani_pics[] =
	{
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = LCD_SIZE_HALF_WIDTH,
			.y = LCD_SIZE_HALF_HEIGHT,
			.data = &pic_breath_gif_bg_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = LCD_SIZE_HALF_WIDTH,
			.y = LCD_SIZE_HALF_HEIGHT,
			.data = &pic_breath_gif_bg_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = LCD_SIZE_HALF_WIDTH,
			.y = LCD_SIZE_HALF_HEIGHT,
			.data = &pic_breath_gif_bg_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = LCD_SIZE_HALF_WIDTH,
			.y = LCD_SIZE_HALF_HEIGHT,
			.data = &pic_breath_gif_bg_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = LCD_SIZE_HALF_WIDTH,
			.y = LCD_SIZE_HALF_HEIGHT,
			.data = &pic_breath_gif_bg_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = LCD_SIZE_HALF_WIDTH,
			.y = LCD_SIZE_HALF_HEIGHT,
			.data = &pic_breath_gif_bg_info,
		},
};

// 准备界面
static const gui_image_struct gui_breath_start_countdown =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.data = &pic_break_ountdown_time_03_info,
};

static const gui_font_struct gui_breath_start_hint_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_BREATH_HINT,
};

// 提示“呼/吸”界面
static const gui_font_struct gui_breath_start_status_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_BREATH_IN,
};

static const gui_widget_struct gui_widget_breath_start[] =
	{
		{
			.id = BREATH_START_LAYOUT_ID_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 0,
			.y = 0,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 1,
			.child_num = countof(gui_breath_start_ani_pics),
			.children = gui_breath_start_ani_pics,
		},

		{
			// count down 321
			.id = BREATH_START_LAYOUT_ID_START,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 0,
			.child_num = 1,
			.children = &gui_breath_start_countdown,
		},

		{
			.id = BREATH_START_LAYOUT_ID_HINT, // 保持静止
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = LCD_SIZE_HEIGHT - 90,
			.width = LCD_SIZE_WIDTH,
			.height = 80,
			.visible = 0,
			.child_num = 1,
			.children = &gui_breath_start_hint_text,
		},

		{
			.id = BREATH_START_LAYOUT_ID_STATUS, // 呼气 吸气
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = LCD_SIZE_HEIGHT - 90,
			.width = LCD_SIZE_WIDTH,
			.height = 80,
			.visible = 0,
			.child_num = 1,
			.children = &gui_breath_start_status_text,
		},
};

const gui_screen_struct gui_screen_breath_start =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_breath_start,
		.child_num = countof(gui_widget_breath_start),
};
