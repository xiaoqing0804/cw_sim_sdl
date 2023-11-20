#include "app_window_charger_lamp_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_base.h"

#if CHARGER_LAMP_SUPPORT

const gui_picture_struct gui_charger_lamp_bat_image_list[] =
{
	&pic_charger_lamp_left_info,
	&pic_charger_lamp_left_40_info,
	&pic_charger_lamp_left_60_info,
	&pic_charger_lamp_left_80_info,
	&pic_charger_lamp_left_100_info,
};

const gui_batt_icon_struct gui_charger_lamp_bat_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
	.x = 0,
	.y = 0,
	.pics_num = countof(gui_charger_lamp_bat_image_list),
	.gui_pics = gui_charger_lamp_bat_image_list,
};

static const gui_image_struct gui_charger_lamp_time_1_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_time_0_info,
};

static const gui_image_struct gui_charger_lamp_time_2_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_time_0_info,
};
static const gui_image_struct gui_charger_lamp_time_dot_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_time_dot_info,
};
static const gui_image_struct gui_charger_lamp_time_3_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_time_0_info,
};
static const gui_image_struct gui_charger_lamp_time_4_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_time_0_info,
};
static const gui_image_struct gui_charger_lamp_date_1_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_date_0_info,
};
static const gui_image_struct gui_charger_lamp_date_2_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_date_0_info,
};
static const gui_image_struct gui_charger_lamp_date_dot_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_date_dot_info,
};
static const gui_image_struct gui_charger_lamp_date_3_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_date_0_info,
};
static const gui_image_struct gui_charger_lamp_date_4_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_date_0_info,
};
static const gui_image_struct gui_charger_lamp_week_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_charger_lamp_left_week_1_info,
};


static const gui_widget_struct gui_charger_lamp_widget[] =
{
	{
		.id = CHARGER_LAMP_ID_BAT,
		.type = TYPE_GUI_CONTROL_BATT_ICON,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 83,
		.height  = LCD_SCALE_HEIGHT* 83,
		.visible= 1,
		.clip = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_bat_image,
	},

	{
		.id = CHARGER_LAMP_ID_TIME_1,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 101,
		.height  = LCD_SCALE_HEIGHT* 76,
		.visible= 1,
		.clip = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_time_1_image,
	},
	{
		.id = CHARGER_LAMP_ID_TIME_2,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 101,
		.height  = LCD_SCALE_HEIGHT* 76,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_time_2_image,
	},
	{
		.id = CHARGER_LAMP_ID_TIME_DOT,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 101,
		.height  = LCD_SCALE_HEIGHT* 35,
		.visible= 1,
		.clip = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_time_dot_image,
	},
	{
		.id = CHARGER_LAMP_ID_TIME_3,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 101,
		.height  = LCD_SCALE_HEIGHT* 76,
		.visible= 1,
		.clip = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_time_3_image,
	},
	{
		.id = CHARGER_LAMP_ID_TIME_4,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 101,
		.height  = LCD_SCALE_HEIGHT* 76,
		.visible= 1,
		.clip = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_time_4_image,
	},


	// {
	// 	.id = CHARGER_LAMP_ID_DATE_1,
	// 	.type = TYPE_GUI_CONTROL_IMAGE,
	// 	.x = 0,
	// 	.y = 0,
	// 	.width  = LCD_SCALE_WIDTH* 25,
	// 	.height  = LCD_SCALE_HEIGHT* 18,
	// 	.rotate = 0,
	// 	.visible= 1,
	// 	.clip = 0,
	// 	.space_x = 0,
	// 	.space_y = 0,
    //     .child_num = 1,
    //     .children = &gui_charger_lamp_date_1_image,
	// },
	// {
	// 	.id = CHARGER_LAMP_ID_DATE_2,
	// 	.type = TYPE_GUI_CONTROL_IMAGE,
	// 	.x = 0,
	// 	.y = 0,
	// 	.width  = LCD_SCALE_WIDTH* 25,
	// 	.height  = LCD_SCALE_HEIGHT* 18,
	// 	.visible= 1,
	// 	.clip = 0,
    //     .child_num = 1,
    //     .children = &gui_charger_lamp_date_2_image,
	// },
	// {
	// 	.id = CHARGER_LAMP_ID_DATE_DOT,
	// 	.type = TYPE_GUI_CONTROL_IMAGE,
	// 	.x = 0,
	// 	.y = 0,
	// 	.width  = LCD_SCALE_WIDTH* 15,
	// 	.height  = LCD_SCALE_HEIGHT* 15,
	// 	.visible= 1,
	// 	.clip = 0,
    //     .child_num = 1,
    //     .children = &gui_charger_lamp_date_dot_image,
	// },
	{
		.id = CHARGER_LAMP_ID_DATE_3,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 25,
		.height  = LCD_SCALE_HEIGHT* 18,
		.visible= 1,
		.clip = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_date_3_image,
	},
	{
		.id = CHARGER_LAMP_ID_DATE_4,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 25,
		.height  = LCD_SCALE_HEIGHT* 18,
		.visible= 1,
		.clip = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_date_4_image,
	},


	{
		.id = CHARGER_LAMP_ID_WEEK,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width  = LCD_SCALE_WIDTH* 25,
		.height  = LCD_SCALE_HEIGHT* 75,
		.visible= 1,
		.clip = 0,
        .child_num = 1,
        .children = &gui_charger_lamp_week_image,
	},
};

const gui_screen_struct gui_screen_charger_lamp =
{
	.order = 0,
	.children = gui_charger_lamp_widget,
	.child_num = countof(gui_charger_lamp_widget),
};

#endif

