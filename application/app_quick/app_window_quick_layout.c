#include "picture.h"
#include "language.h"
#include "app_window_quick_layout.h"
#include "app_window_quick.h"
#include "app_window_quick_ui.h"




// --------------------------------------------------------------------------------
static const gui_image_struct gui_pic_quick_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_quick_bg_info,
};
// batt icon
static const picture_info_struct *const gui_pic_power_pics[] = {
	&pic_quick_power_10_info,
	&pic_quick_power_20_info,
	&pic_quick_power_30_info,
	&pic_quick_power_40_info,
	&pic_quick_power_50_info,
	&pic_quick_power_60_info,
	&pic_quick_power_70_info,
	&pic_quick_power_80_info,
	&pic_quick_power_90_info,
	&pic_quick_power_100_info,
};

static const gui_batt_icon_struct gui_pic_quick_battery =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .pics_num = countof(gui_pic_power_pics),
    .gui_pics = gui_pic_power_pics,
};

static const gui_image_struct gui_pic_quic_alarm =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_quic_alarm_info,
};


static const gui_image_struct gui_pic_quick_findphone =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_quick_hfp_no_info,
};


static const gui_image_struct gui_pic_quick_more =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_quick_more_info,
};


static const gui_image_struct gui_pic_quick_disturb_off =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_quick_disturb_off_info,
};

static const gui_image_struct gui_pic_quick_bright =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_quick_bright_off_info,
};
static const gui_image_struct gui_pic_quick_ble =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_quick_all_no_info,
};
//// DATA ----------------------------------------------------------------------------

static const gui_font_struct gui_quick_date_txt =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.auto_wrap = 0,
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_NUMBER_20,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "10/10",
};

static const gui_control_digital_struct  gui_quick_time =
{
 .value_type = GUI_DIGITAL_VALUE_TYPE_FONT,
 .value.font = &gui_quick_date_txt,
};


static const gui_font_struct gui_batt_txt =   //nunber
{
 .type = TYPE_GUI_DRAW_TEXT,
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_NUMBER_20,
 .value_type = GUI_FONT_VALUE_TYPE_STRING,
 .value.string = "00%",
};
static const gui_font_struct gui_quick_week =   //week
{
 .type = TYPE_GUI_DRAW_TEXT,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_XSMALL,
 .value_type = GUI_FONT_VALUE_TYPE_STRING,
 .value.string = "SUN",
};

static const gui_font_struct gui_quick_disturb_txt =
{
 .type = TYPE_GUI_DRAW_TEXT,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
 .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
 .color = COLOR_RGB(255, 255, 255),
 .scroll = 1,
 .size = SYS_FONT_XSMALL,
 .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
 .value.string_id = STRING_DISTURB,
};

static const gui_font_struct gui_quick_bright_txt =
{
 .type = TYPE_GUI_DRAW_TEXT,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_XSMALL,
 .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
 .value.string_id = STRING_WAKEY,
};

static const gui_font_struct gui_quick_bright_on_txt =
{
 .type = TYPE_GUI_DRAW_TEXT,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_XSMALL,
 .value_type = GUI_FONT_VALUE_TYPE_STRING,
 .value.string = "5min",
};

static const gui_font_struct gui_quick_findphone_txt =
{
 .type = TYPE_GUI_DRAW_TEXT,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
 .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_XSMALL,
 .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
 .value.string_id = STRING_BHFP,
};

static const gui_font_struct gui_quick_alarm_txt =
{
 .type = TYPE_GUI_DRAW_TEXT,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_XSMALL,
 .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
 .value.string_id = STRING_ALARM,
};

static const gui_font_struct gui_quick_more_txt =
{
 .type = TYPE_GUI_DRAW_TEXT,
 .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
 .color = COLOR_RGB(255, 255, 255),
 .size = SYS_FONT_XSMALL,
 .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
 .value.string_id = STRING_QUICK_SETTING,
};
///////////////////////////////////////////////////////////////////////////////////
static const gui_widget_struct gui_widget_quick[] =
{
	{   // time
        .type = TYPE_GUI_CONTROL_DATE,
		.x = 156,
        .y = 417,
        .width = 90,
        .height = 30,
        .visible= 1,
        .child_num = 1,
        .children = &gui_quick_time,
    },

	{   // time
		.id = QUICK_ID_BATTERY_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 244,
        .y = 370,
        .width = 90,
        .height = 30,
        .visible= 1,
        .child_num = 1,
        .children = &gui_batt_txt,
    },
    {
		.id = QUICK_ID_BLE,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 120,
		.y = 370,
		.width = 40,
		.height = 40,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_quick_ble,
	},

	{   // batt-icon
		.id = QUICK_ID_BATTERY,
		.type = TYPE_GUI_CONTROL_BATT_ICON,
		.x = 178,
		.y = 376,
		.width = 51,
		.height = 24,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_quick_battery,
	},


	{
		.id = QUICK_ID_SYS_ALARM,
		.type = TYPE_GUI_CONTROL_IMAGE,
        .x = 182,
        .y = 201,
        .width = 100,
        .height = 100,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_quic_alarm,
	},

    {
		.id = QUICK_ID_SYS_HFP,
		.type = TYPE_GUI_CONTROL_IMAGE,
        .x = 35,
        .y = 201,
        .width = 100,
        .height = 100,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_quick_findphone,
	},

	{
		.id = QUICK_ID_SYS_MORE,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 331,
		.y = 201,
		.width = 100,
		.height = 100,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_quick_more,
	},

	{
		.id = QUICK_ID_SYS_DISTURB,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 109,
		.y = 36,
		.width = 100,
		.height = 100,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_quick_disturb_off,
	},

	{
		.id = QUICK_ID_SYS_BRIGHT,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 257,
		.y = 36,
		.width = 100,
		.height = 100,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_quick_bright,
	},


    {
        .id = QUICK_ID_WEEK,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 258,
        .y = 422,
        .width = 93,
        .height = 31,
        .rotate = 0,
        .visible= 1,
        .clip = 0,
        .space_x = 0,
        .space_y = 0,
        .child_num = 1,
        .children = &gui_quick_week,
	},


	{
        .id = QUICK_ID_SYS_DISTURB_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 110,
        .y = 147,
        .width = 100,
        .height = 35,
        .rotate = 0,
        .visible= 1,
        .clip = 1,
        .space_x = 0,
        .space_y = 0,
        .child_num = 1,
        .children = &gui_quick_disturb_txt,
	},

	{
        .id = QUICK_ID_SYS_BRIGHT_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 257,
        .y = 147,
        .width = 100,
        .height = 35,
        .rotate = 0,
        .visible= 1,
        .clip = 0,
        .space_x = 0,
        .space_y = 0,
        .child_num = 1,
        .children = &gui_quick_bright_txt,
	},

	{
        .id = QUICK_ID_SYS_BRIGHT_ON_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 257,
        .y = 147,
        .width = 100,
        .height = 35,
        .rotate = 0,
        .visible= 0,
        .clip = 0,
        .space_x = 0,
        .space_y = 0,
        .child_num = 1,
        .children = &gui_quick_bright_on_txt,
	},

	{
        .id = QUICK_ID_SYS_HFP_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 35,
        .y = 314,
        .width = 100,
        .height = 100,
        .rotate = 0,
        .visible= 1,
        .clip = 0,
        .space_x = 0,
        .space_y = 0,
        .child_num = 1,
        .children = &gui_quick_findphone_txt,
	},

	{
        .id = QUICK_ID_SYS_ALARM_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 182,
        .y = 314,
        .width = 100,
        .height = 35,
        .rotate = 0,
        .visible= 1,
        .clip = 0,
        .space_x = 0,
        .space_y = 0,
        .child_num = 1,
        .children = &gui_quick_alarm_txt,
	},



	{
        .id = QUICK_ID_SYS_MORE_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 328,
        .y = 314,
        .width = 100,
        .height = 35,
        .rotate = 0,
        .visible= 1,
        .clip = 0,
        .space_x = 0,
        .space_y = 0,
        .child_num = 1,
        .children = &gui_quick_more_txt,
	},
};
const gui_layout_scroll_struct gui_layout_quick =
{
	.height = 510,		//�߶�
	.scroll = 1,//�Ƿ�������¹���
	.can_swipe = 1,
};
const gui_screen_struct gui_screen_quick =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_widget_quick,
	.child_num = countof(gui_widget_quick),
	.layout_config = &gui_layout_quick,
};


