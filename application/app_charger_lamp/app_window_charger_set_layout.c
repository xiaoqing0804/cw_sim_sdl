#include "app_window_charger_set_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_base.h"


static const gui_image_struct gui_pic_charger_set =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_set_off_info,
};

static const gui_image_struct gui_pic_menu_arrow =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.x  = LCD_SCALE_WIDTH* 10,
	.data = &pic_call_list_bg_info,
};


static const gui_font_struct gui_txt_charger_set =   //name
{
	.type = TYPE_GUI_DRAW_TEXT,
	.auto_wrap = 1,
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.width  = LCD_SCALE_WIDTH* 170,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_BED_LAMP,
};


static const gui_font_struct gui_txt_charger_set_illustrate =   //name
{
	.type = TYPE_GUI_DRAW_TEXT,
	.width  = 220,
	.scroll =1,
    .color = COLOR_RGB(150, 150, 150),
    .size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_BED_LAMP_ILLUSTRATE,
};

static const gui_widget_struct gui_widget_charger_set[] =
{
	{
		.id = CHARGER_SET_ID_MODE_PROGRESS,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y  = LCD_SCALE_HEIGHT* 60,
		.width  = LCD_SCALE_WIDTH* 320,
		.height  = LCD_SCALE_HEIGHT* 90,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_menu_arrow,
	},
	{
		.id = CHARGER_SET_ID_MODE,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x  = LCD_SCALE_WIDTH* 30,
		.y  = LCD_SCALE_HEIGHT* 88,
		.width = LCD_SIZE_WIDTH,
		.height  = LCD_SCALE_HEIGHT* 50,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_txt_charger_set,
 	},

	{
		.id = CHARGER_SET_ID_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x  = LCD_SCALE_WIDTH* 219,
		.y  = LCD_SCALE_HEIGHT* 83,
		.width  = LCD_SCALE_WIDTH* 74,
		.height  = LCD_SCALE_HEIGHT* 40,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_charger_set,
	},

	{
        .type = TYPE_GUI_CONTROL_LABEL,
		.x  = 10,
		.y  = LCD_SCALE_HEIGHT* 155,
		.width = 220,
		.height  = LCD_SCALE_HEIGHT* 100,
		.visible= 1,
		.clip = 0,
		.child_num = 1,
		.children = &gui_txt_charger_set_illustrate,
	},
};

const gui_screen_struct gui_screen_charger_set =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_charger_set,
	.child_num = countof(gui_widget_charger_set),
};


