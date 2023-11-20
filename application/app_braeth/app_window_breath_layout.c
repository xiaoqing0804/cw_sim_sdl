#include "app_window_breath_layout.h"
#include "gui_surface_control_base.h"
#include "picture.h"
#include "language.h"

#define BR_ANI_TIME_GAP (150)

static const gui_image_struct gui_breathe_ani_pics[] =
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

static const gui_image_struct gui_breath_start_button =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_breath_start_info,
};

static const gui_image_struct gui_breath_speed_button =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_breath_speed_info,
};

static const gui_image_struct gui_breath_time_button =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_breath_time_info,
};

static const gui_widget_struct gui_widget_breath[] =
	{
		{
			.id = BREATH_LAYOUT_ID_BG,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 0,
			.y = 0,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SIZE_HEIGHT,
			.visible = 1,
			.child_num = countof(gui_breathe_ani_pics),
			.children = gui_breathe_ani_pics,
		},

		{
			.id = BREATH_LAYOUT_ID_TIME,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 231,
			.y = 330,
			.width = 132,
			.height = 90,
			.visible = 1,
			.child_num = 1,
			.children = &gui_breath_time_button,
		},

		{
			.id = BREATH_LAYOUT_ID_SPEED,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 101,
			.y = 330,
			.width = 132,
			.height = 90,
			.visible = 1,
			.child_num = 1,
			.children = &gui_breath_speed_button,
		},

		{
			.id = BREATH_LAYOUT_ID_START,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 182,
			.y = 182,
			.width = 80,
			.height = 80,
			.visible = 1,
			.child_num = 1,
			.children = &gui_breath_start_button,
		},

};

const gui_screen_struct gui_screen_breath =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_breath,
		.child_num = countof(gui_widget_breath),
};
