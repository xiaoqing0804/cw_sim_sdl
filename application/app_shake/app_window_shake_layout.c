#include "app_window_shake_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_base.h"


static const gui_image_struct gui_pic_shake =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_shake_open_info,
};
	


static const gui_font_struct gui_txt_watchface =   //name
{
 .type = TYPE_GUI_DRAW_TEXT,
 .id = 0,
 .x = 0,
 .y = 0,
 .anchor_x = 0,
 .anchor_y = 0,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .auto_wrap = 0, 
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_MEDIUM,
 .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
 .value.string_id = STRING_WATCHFACE_STYLE,

};

static const gui_font_struct gui_txt_menu =   //name
{
 .type = TYPE_GUI_DRAW_TEXT,
 .id = 0,
 .x = 0,
 .y = 0,
 .anchor_x = 0,
 .anchor_y = 0,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .auto_wrap = 0, 
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_MEDIUM,
 .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
 .value.string_id = STRING_MENU_STYLE,
};


static const gui_widget_struct gui_widget_shake[] =
{
	{
		.id = SHAKE_LAYOUT_ID_WATCHFACE,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 22,
		.y = 80,
		.width = 50,
		.height = 50,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_txt_watchface,
 	}, 

	{
		.id = SHAKE_LAYOUT_ID_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 170,
		.y = 80,
		.width = 85,
		.height = 85,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_shake,
	},

	{
		.id = SHAKE_LAYOUT_ID_MENU,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 22,
		.y = 130,
		.width = 50,
		.height = 50,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_txt_menu,
 	}, 

	
	{
		.id = SHAKE_LAYOUT_ID_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 170,
		.y = 130,
		.width = 85,
		.height = 85,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_shake,
	},
};

const gui_screen_struct gui_screen_shake =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_shake,
	.child_num = countof(gui_widget_shake),
};


