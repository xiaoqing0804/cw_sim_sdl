#include "app_window_sleep_layout.h"
#include "app_window_sleep.h"
#include "app_window_sleep_ui.h"

#include "gui_surface_control_base.h"
#include "picture.h"
#include "language.h"

static const gui_image_struct gui_sleep_bg_01[] =
	{
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = 0,
			.y = 0,
			.data = &pic_sleep_Gif_1_001_info,

		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = 233,
			.y = 0,
			.data = &pic_sleep_Gif_1_003_info,

		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = 0,
			.y = 157,
			.data = &pic_sleep_Gif_1_002_info,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.x = 233,
			.y = 157,
			.data = &pic_sleep_Gif_1_004_info,
		},
};
static const gui_animation_frame_struct gui_sleep_bg_03[] =
	{
		PIC_ANIMATION_FRAME(200, GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_BOTTOM), &pic_sleep_Gif_2_001_info),
		//PIC_ANIMATION_FRAME(200, GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_BOTTOM), &pic_sleep_Gif_3_001_info),
		//PIC_ANIMATION_FRAME(200, GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_BOTTOM), &pic_sleep_Gif_4_001_info),
		//PIC_ANIMATION_FRAME(200, GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_BOTTOM), &pic_sleep_Gif_5_001_info),

};
static const gui_animation_frame_struct gui_sleep_bg_04[] =
	{

		PIC_ANIMATION_FRAME(200, GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_BOTTOM), &pic_sleep_Gif_2_002_info),
		//PIC_ANIMATION_FRAME(200, GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_BOTTOM), &pic_sleep_Gif_3_002_info),
		//PIC_ANIMATION_FRAME(200, GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_BOTTOM), &pic_sleep_Gif_4_002_info),
		//PIC_ANIMATION_FRAME(200, GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT, GUI_ALIGN_BOTTOM), &pic_sleep_Gif_5_002_info),
};

static const gui_animation_struct gui_ani_sleeps1[] =
	{

		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.id = 2,
			.frames_num = countof(gui_sleep_bg_03),
			.frames = gui_sleep_bg_03,
		},
		{
			.type = TYPE_GUI_DRAW_PICTURE,
			.id = 4,
			.frames_num = countof(gui_sleep_bg_04),
			.frames = gui_sleep_bg_04,
		},
};

static const gui_image_struct gui_light_logo =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_sleep_light_info,
};
static const gui_image_struct gui_deep_logo =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_sleep_deep_info,
};

static const gui_image_struct gui_no_sleep_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_no_sleep_data_info,
};

// static const gui_font_struct gui_sleep_total =
// {
// 	.type = TYPE_GUI_DRAW_TEXT,
// 	.id = 0,
// 	.x = 0,
// 	.y = 0,
// 	.anchor_x = 0,
// 	.anchor_y = 0,
// 	.align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT , GUI_ALIGN_VCENTER),
// 	.auto_wrap = 0,
// 	.color = COLOR_RGB(255, 255, 255),
// 	.size = SYS_FONT_NUMBER_50,
// 	.value_type = GUI_FONT_VALUE_TYPE_STRING,
// 	.value.string = "05 H     20 M",
// };

static const gui_font_struct gui_sleep_light =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		//	.align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT , GUI_ALIGN_VCENTER),
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_NUMBER_26,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "0",
};

static const gui_font_struct gui_sleep_deep =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		//	.align = GUI_ALIGN_MERGE(GUI_ALIGN_RIGHT , GUI_ALIGN_VCENTER),
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_NUMBER_26,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "0",
};

static const gui_font_struct gui_sleep_hour_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_NUMBER_50,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "00",
};
static const gui_font_struct gui_sleep_min_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_NUMBER_50,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "00",
};
static const gui_font_struct gui_sleep_hour_H_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "H",
};
static const gui_font_struct gui_sleep_min_m_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.id = 0,
		.x = 0,
		.y = 0,
		.anchor_x = 0,
		.anchor_y = 0,
		.auto_wrap = 0,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "M",
};
static const gui_font_struct gui_no_sleep_txt = // 无睡眠
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_NO_SLEEP_DATA,
		.scroll = 1,
};

static const gui_widget_struct gui_sleep_widget[] =
	{

		{
			.id = SLEEP_LAYOUT_ID_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 0,
			.y = 0,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 1,
			.child_num = countof(gui_sleep_bg_01),
			.children = gui_sleep_bg_01,
		},

		{
			.id = SLEEP_LAYOUT_ID_BG1,
			.type = TYPE_GUI_CONTROL_ANIMATION,
			.x = 0,
			.y = 0,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 1,
			.child_num = countof(gui_ani_sleeps1),
			.children = gui_ani_sleeps1,
		},
		// deep
		{
			.id = SLEEP_LAYOUT_ID_DEEP_LOGO,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 114,
			.y = 310,
			.width = 80,
			.height = 80,
			.visible = 1,
			.child_num = 1,
			.children = &gui_deep_logo,
		},
		// light
		{
			.id = SLEEP_LAYOUT_ID_LIGHT_LOGO,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 114,
			.y = 370,
			.width = 80,
			.height = 80,
			.visible = 1,
			.child_num = 1,
			.children = &gui_light_logo,
		},

		{
			.id = SLEEP_LAYOUT_ID_LIGHT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 180,
			.y = 370,
			.width = 75,
			.height = 38,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_sleep_light,
		},

		{
			.id = SLEEP_LAYOUT_ID_DEEP,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 180,
			.y = 310,
			.width = 72,
			.height = 38,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_sleep_deep,
		},

		{
			.id = SLEEP_LAYOUT_ID_HOUR,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 65,
			.y = 132,
			.width = 155,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_sleep_hour_txt,
		},
		{
			.id = SLEEP_LAYOUT_ID_MIN,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 65,
			.y = 217,
			.width = 155,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_sleep_min_txt,
		},
		{
			.id = SLEEP_LAYOUT_ID_H,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 164,
			.y = 161,
			.width = 155,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_sleep_hour_H_txt,
		},
		{
			.id = SLEEP_LAYOUT_ID_M,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 164,
			.y = 245,
			.width = 155,
			.height = 50,
			.rotate = 0,
			.visible = 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_sleep_min_m_txt,
		},

		/*
		{
			// no sleep data
			.id = SLEEP_LAYOUT_ID_NO_DATA,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 183,
			.y = 160,
			.width = 100,
			.height = 100,
			.visible = 0,
			.child_num = 1,
			.children = &gui_no_sleep_image,
		},
		*/

		{
			.id = SLEEP_LAYOUT_ID_NO_TXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 50,
			.y = 300,
			.width = LCD_SIZE_WIDTH - 50 * 2,
			.height = 100,
			.visible = 0,
			.clip = 1,
			.child_num = 1,
			.children = &gui_no_sleep_txt,
		},

};

const gui_screen_struct gui_screen_sleep =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.order = 0,
		.children = gui_sleep_widget,
		.child_num = countof(gui_sleep_widget),
};
