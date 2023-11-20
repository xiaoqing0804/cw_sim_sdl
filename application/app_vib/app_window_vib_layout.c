#include "app_window_vib.h"
#include "app_window_vib_layout.h"
#include "app_window_vib_ui.h"

#include "picture.h"
#include "language.h"
#include "gui_surface_control_base.h"


static const gui_image_struct gui_pic_vib =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_on_info,
};


static const gui_font_struct gui_txt_vib =   //name
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
 .value.string_id = STRING_VIB_MODE,
};

static const gui_font_struct gui_vib_txt =   //name
{
 .type = TYPE_GUI_DRAW_TEXT,
 .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .auto_wrap = 0,
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_MEDIUM,
 .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
 .value.string_id = STRING_VIB,
};


static const gui_widget_struct gui_widget_vib[] =
{
	{
		.id = VIB_ID_MODE,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 22,
		.y = 100,
		.width = 50,
		.height = 50,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_txt_vib,
 	},

	{
		.id = VIB_ID_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 230,
		.y = 105,
		.width = 85,
		.height = 85,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_vib,
	},

    {
		.id = VIB_ID_TXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 30,
		.width = LCD_SIZE_WIDTH,
		.height = 85,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_vib_txt,
	},
};

const gui_screen_struct gui_screen_vib =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_vib,
	.child_num = countof(gui_widget_vib),
};


