#include "app_window_telephone_set_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_base.h"


static const gui_image_struct gui_pic_telephone =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_progress_bar_open_info,
};
	

static const gui_font_struct gui_txt_call =   //name
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
 .value.string_id = STRING_CALL_MUTE,

};

static const gui_font_struct gui_txt_call_vib =   //name
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
 .value.string_id = STRING_CALL_VIB,

};

static const gui_font_struct gui_txt_call_out_vib =   //name
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
 .value.string_id = STRING_CALL_OUT_VIB,
};



static const gui_widget_struct gui_widget_telephone[] =
{
	{
		.id = TELEPHONE_ID_CALL,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 22,
		.y = 75,
		.width = 50,
		.height = 50,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_txt_call,
 	}, 

	{
		.id = TELEPHONE_ID_CALL_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 150,
		.y = 80,
		.width = 85,
		.height = 85,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_telephone,
	},

	{
		.id = TELEPHONE_ID_CALL_VIB,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 22,
		.y = 125,
		.width = 50,
		.height = 50,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_txt_call_vib,
 	}, 

	
	{
		.id = TELEPHONE_ID_CALL_VIB_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 150,
		.y = 130,
		.width = 85,
		.height = 85,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_telephone,
	},

	{
		.id = TELEPHONE_ID_CALL_OUT_VIB,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 22,
		.y = 175,
		.width = 50,
		.height = 50,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_txt_call_out_vib,
 	},

	{
		.id = TELEPHONE_ID_CALL_VIB_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 150,
		.y = 180,
		.width = 85,
		.height = 85,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_telephone,
	},

};

const gui_screen_struct gui_screen_telephone =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_telephone,
	.child_num = countof(gui_widget_telephone),
};


