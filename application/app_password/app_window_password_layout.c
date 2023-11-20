#include "app_window_password_layout.h"

#define PASSWORD_ITEM_LEFT (38)
#define PASSWORD_ITEM_TOP (GUI_CONTENT_GAP_TOP)
#define PASSWORD_ITEM_WIDTH (126)
#define PASSWORD_ITEM_HEIGHT (86)
#define PASSWORD_ITEM_GAP (7)

#define PASSWORD_ITEM_X(row, col) (PASSWORD_ITEM_LEFT + (col) * (PASSWORD_ITEM_WIDTH + PASSWORD_ITEM_GAP))
#define PASSWORD_ITEM_Y(row, col) (PASSWORD_ITEM_TOP + (row) * (PASSWORD_ITEM_HEIGHT + PASSWORD_ITEM_GAP))

#if (LCD_SHAPE == LCD_CIRCLE)
#define PASSWORD_ITEM_DELETE_X (310 - (PASSWORD_ITEM_WIDTH + PASSWORD_ITEM_GAP)/2)
#else
#define PASSWORD_ITEM_DELETE_X (310)
#endif
#define PASSWORD_ITEM_DELETE_Y (383)

#define PASSWORD_DOT_WIDTH (26)
#define PASSWORD_DOT_HEIGHT (26)
#define PASSWORD_DOT_GAP (10)

#define PASSWORD_DOT_START_X ((LCD_SIZE_WIDTH - 4 * (PASSWORD_DOT_WIDTH + PASSWORD_DOT_GAP) + PASSWORD_DOT_GAP) / 2)
#define PASSWORD_DOT_X(index) (PASSWORD_DOT_START_X + (index) * (PASSWORD_DOT_WIDTH + PASSWORD_DOT_GAP))
#define PASSWORD_DOT_Y (47)

static const gui_image_struct gui_password_bg_0 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_0_info,
};
static const gui_image_struct gui_password_bg_1 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_1_info,
};
static const gui_image_struct gui_password_bg_2 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_2_info,
};
static const gui_image_struct gui_password_bg_3 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_3_info,
};
static const gui_image_struct gui_password_bg_4 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_4_info,
};
static const gui_image_struct gui_password_bg_5 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_5_info,
};
static const gui_image_struct gui_password_bg_6 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_6_info,
};
static const gui_image_struct gui_password_bg_7 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_7_info,
};
static const gui_image_struct gui_password_bg_8 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_8_info,
};
static const gui_image_struct gui_password_bg_9 =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_bg_9_info,
};

static const gui_image_struct gui_password_delect =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER,GUI_ALIGN_VCENTER),
		.data = &pic_password_delect_info,
};

static const gui_image_struct gui_password_no =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_password_no_info,
};

static const gui_font_struct gui_text_password_info =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_XSMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value.string_id = STRING_PASSWORD_ERR,
		.scroll = 1,
};

static const gui_widget_struct gui_widget_password[] =
	{

		{
			.id = PASSWORD_INFO,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 100,
			.y = 10,
			.width = LCD_SIZE_WIDTH - 200,
			.height = PASSWORD_ITEM_TOP - 10,
			.visible = 0,
			.child_num = 1,
			.clip = 1,
			.children = &gui_text_password_info,
		},

		/***********************************NUMBER************************************************/

		{
			.id = PASSWORD_BG_1,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(0, 0),
			.y = PASSWORD_ITEM_Y(0, 0),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_1,
		},

		{
			.id = PASSWORD_BG_4,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(1, 0),
			.y = PASSWORD_ITEM_Y(1, 0),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_4,
		},

		{
			.id = PASSWORD_BG_7,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(2, 0),
			.y = PASSWORD_ITEM_Y(2, 0),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_7,
		},

		{
			.id = PASSWORD_BG_2,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(0, 1),
			.y = PASSWORD_ITEM_Y(0, 1),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_2,
		},

		{
			.id = PASSWORD_BG_5,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(1, 1),
			.y = PASSWORD_ITEM_Y(1, 1),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_5,
		},

		{
			.id = PASSWORD_BG_8,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(2, 1),
			.y = PASSWORD_ITEM_Y(2, 1),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_8,
		},

		{
			.id = PASSWORD_BG_3,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(0, 2),
			.y = PASSWORD_ITEM_Y(0, 2),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_3,
		},

		{
			.id = PASSWORD_BG_6,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(1, 2),
			.y = PASSWORD_ITEM_Y(1, 2),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_6,
		},

		{
			.id = PASSWORD_BG_9,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_X(2, 2),
			.y = PASSWORD_ITEM_Y(2, 2),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_9,
		},

		{
			.id = PASSWORD_BG_0,
			.type = TYPE_GUI_CONTROL_IMAGE,
		#if (LCD_SHAPE == LCD_CIRCLE)
			.x = PASSWORD_ITEM_X(3, 0.5),
		#else
			.x = PASSWORD_ITEM_X(3, 1),
		#endif
			.y = PASSWORD_ITEM_Y(3, 1),
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_bg_0,
		},

		{
			.id = PASSWORD_BG_DELECL,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_ITEM_DELETE_X,
			.y = PASSWORD_ITEM_DELETE_Y,
			.width = PASSWORD_ITEM_WIDTH,
			.height = PASSWORD_ITEM_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_delect,
		},

		/***********************************PASSWORD NO************************************************/
		{
			.id = PASSWORD_NO_0,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_DOT_X(0),
			.y = PASSWORD_DOT_Y,
			.width = PASSWORD_DOT_WIDTH,
			.height = PASSWORD_DOT_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_no,
		},
		{
			.id = PASSWORD_NO_1,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_DOT_X(1),
			.y = PASSWORD_DOT_Y,
			.width = PASSWORD_DOT_WIDTH,
			.height = PASSWORD_DOT_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_no,
		},
		{
			.id = PASSWORD_NO_2,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_DOT_X(2),
			.y = PASSWORD_DOT_Y,
			.width = PASSWORD_DOT_WIDTH,
			.height = PASSWORD_DOT_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_no,
		},
		{
			.id = PASSWORD_NO_3,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = PASSWORD_DOT_X(3),
			.y = PASSWORD_DOT_Y,
			.width = PASSWORD_DOT_WIDTH,
			.height = PASSWORD_DOT_HEIGHT,
			.visible = 1,
			.child_num = 1,
			.children = &gui_password_no,
		},

};

const gui_screen_struct gui_screen_password =
	{
		.type = TYPE_GUI_LAYOUT_PANNEL,
		.children = gui_widget_password,
		.child_num = countof(gui_widget_password),
};
