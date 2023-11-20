#include "app_window_about_layout.h"
#include "picture.h"
#include "language.h"
#include "dev_version.h"

static const gui_font_struct gui_text_about_devicename_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_BLUETOOTH_NAME,
};

static const gui_font_struct gui_text_about_devicename =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(105, 105, 105),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = DEV_NAME,
};

static const gui_font_struct gui_text_about_id_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_ID,
};

static const gui_font_struct gui_text_about_id =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(105, 105, 105),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "",
};

static const gui_font_struct gui_text_about_mac_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_BLUETOOTH_MAC,
};

static const gui_font_struct gui_text_about_mac =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(105, 105, 105),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "",
};

static const gui_font_struct gui_text_about_tp_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_TP,
};

static const gui_font_struct gui_text_about_tp =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(105, 105, 105),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "",
};

static const gui_font_struct gui_text_about_version_title =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_FIRMWAREi_VERSION,
};

static const gui_font_struct gui_text_about_version =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(105, 105, 105),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "",
};

static const gui_widget_struct gui_widget_about_list[] =
	{	
		//设备名称标题
		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,	
			.y = 142,
			.width = LCD_SIZE_WIDTH,
			.height = 58,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_devicename_title,
		},
		//型号标题
		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 285,
			.width = LCD_SIZE_WIDTH,
			.height = 58,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_id_title,
		},
		//蓝牙地址标题
		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 428,
			.width = LCD_SIZE_WIDTH,
			.height = 58,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_mac_title,
		},
		
		//tp标题
		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 571,
			.width = LCD_SIZE_WIDTH,
			.height = 58,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_tp_title,
		},
		//版本信息标题
		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 714,
			.width = LCD_SIZE_WIDTH,
			.height = 58,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_version_title,
		},
		//设备名称信息
		{

			.type = TYPE_GUI_CONTROL_LABEL,
			.id = ABOUT_LAYOUT_ID_DEVSION,
			.x = 0,
			.y = 142 + 58,
			.width = LCD_SIZE_WIDTH,
			.height = 35,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_devicename,
		},
		//型号信息
		{

			.type = TYPE_GUI_CONTROL_LABEL,
			.id = ABOUT_LAYOUT_ID_CRC_ID,
			.x = 0,
			.y = 285 + 58,
			.width = LCD_SIZE_WIDTH,
			.height = 35,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_id,
		},
		//蓝牙地址
		{

			.type = TYPE_GUI_CONTROL_LABEL,
			.id = ABOUT_LAYOUT_ID_MAC,
			.x = 0,
			.y = 428 + 58,
			.width = LCD_SIZE_WIDTH,
			.height = 35,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_mac,
		},
		//tp信息
		{

			.type = TYPE_GUI_CONTROL_LABEL,
			.id = ABOUT_LAYOUT_ID_TP,
			.x = 0,
			.y = 571 + 58,
			.width = LCD_SIZE_WIDTH,
			.height = 35,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_tp,
		},
		//版本信息
		{
			
			.type = TYPE_GUI_CONTROL_LABEL,
			.id = ABOUT_LAYOUT_ID_BLUETOOTH,
			.x = 0,
			.y = 714 + 58,
			.width = LCD_SIZE_WIDTH,
			.height = 35,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_about_version,
		},

};
const gui_layout_scroll_struct gui_layout_about_list =
	{
		.height = 900,
		.scroll = 1,
};

const gui_screen_struct gui_screen_about =
	{
		.type = TYPE_GUI_LAYOUT_SCROLL,
		.layout_config = &gui_layout_about_list,
		.child_num = countof(gui_widget_about_list),
		.children = gui_widget_about_list,
};
