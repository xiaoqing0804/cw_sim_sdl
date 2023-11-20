#include "app_window_battery_layout.h"
#include "app_window_battery_chart.h"

/************progress*************/
static const picture_info_struct *const gui_battery_pics[] = {
	&pic_battery_schedule_0_info,
	&pic_battery_schedule_1_info,
	&pic_battery_schedule_2_info,
	&pic_battery_schedule_3_info,
	&pic_battery_schedule_4_info,
};

const gui_batt_icon_struct gui_battery_bat_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.id = 0,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.x = 0,
		.y = 0,
		.pics_num = countof(gui_battery_pics),
		.gui_pics = gui_battery_pics,
};

/************battery data*************/
static const gui_number_image_list_struct gui_battery_num_image =
	{
		.number = {
			&pic_charger_txt_0_info,
			&pic_charger_txt_1_info,
			&pic_charger_txt_2_info,
			&pic_charger_txt_3_info,
			&pic_charger_txt_4_info,
			&pic_charger_txt_5_info,
			&pic_charger_txt_6_info,
			&pic_charger_txt_7_info,
			&pic_charger_txt_8_info,
			&pic_charger_txt_9_info,
		},
		.percent = &pic_charger_txt_10_info,
};

static const gui_image_number_struct gui_battery_num =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.number_image_list = &gui_battery_num_image,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value.string = "100%",
};

static const gui_control_digital_struct gui_battery_data =
	{
		.value_type = GUI_DIGITAL_VALUE_TYPE_IMAGE,
		.value.image_number = &gui_battery_num,
};

static const gui_font_struct gui_battery_label_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "100%",
};

static const gui_control_digital_struct gui_battery_batt_label =
	{
		.value_type = GUI_DIGITAL_VALUE_TYPE_FONT,
		.value.font = &gui_battery_label_text,
};

static const gui_image_struct gui_data_bg =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.data = &pic_battery_data_bg_info,
};

static const gui_font_struct gui_public_battery_scan_last = // 上次充电
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
		.value.string_id = STRING_LAST_CHARGED,
};

static const gui_font_struct gui_text_battery_txt =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value.string = "100%",
};

static const gui_font_struct gui_text_battery_time =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.color = COLOR_RGB(128, 128, 128),
		.size = SYS_FONT_MEDIUM,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
		.value.string = "12/1/20",
};

static const gui_widget_struct gui_widget_battery_list[] =
	{
		{
			.id = BATTERY_LAYOUT_ID_SCHEDULE,
			.type = TYPE_GUI_CONTROL_BATT_ICON,
			.y = GUI_CONTENT_GAP_TOP,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SCALE_HEIGHT * 266,
			.visible = 1,
			.child_num = 1,
			.children = &gui_battery_bat_image,
		},

		{
			.id = BATTERY_LAYOUT_ID_NUM,
			.type = TYPE_GUI_CONTROL_BATT_LABEL,
			.y = GUI_CONTENT_GAP_TOP + LCD_SCALE_HEIGHT * 122,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SCALE_HEIGHT * 50,
			.visible = 1,
			.child_num = 1,
			.children = &gui_battery_data,
		},

		{
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = LCD_SCALE_WIDTH * 15,
			.y = GUI_CONTENT_GAP_TOP + LCD_SCALE_HEIGHT * 300,
			.width = LCD_SCALE_WIDTH * 422,
			.height = LCD_SCALE_HEIGHT * 310,
			.visible = 1,
			.child_num = 1,
			.children = &gui_data_bg,
		},
		{
			.id = BATTERY_LAYOUT_ID_FORM,
			.type = TYPE_GUI_CONTROL_CHART,
			.x = LCD_SCALE_WIDTH * 64,
			.y = GUI_CONTENT_GAP_TOP + LCD_SCALE_HEIGHT * 318,
			.width = LCD_SCALE_WIDTH * 380,
			.height = LCD_SCALE_HEIGHT * 256,
			.visible = 1,
			.child_num = 1,
			.children = &g_battery_ext_chart,
		},

		{
			.id = BATTERY_LAYOUT_ID_LAST_NUM,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = GUI_CONTENT_GAP_TOP + LCD_SCALE_HEIGHT * 628,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SCALE_HEIGHT * 30,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_battery_txt,
		},

		{
			.id = BATTERY_LAYOUT_ID_TIME,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = GUI_CONTENT_GAP_TOP + LCD_SCALE_HEIGHT * 676,
			.width = LCD_SIZE_WIDTH,
			.height = LCD_SCALE_HEIGHT * 30,
			.visible = 1,
			.child_num = 1,
			.children = &gui_text_battery_time,
		},
};

const gui_layout_scroll_struct gui_layout_scroll_battery =
	{
		.height = LCD_SCALE_HEIGHT * 880, // 高度
		.scroll = 1,					  // 是否可以上下滚动
};

const gui_screen_struct gui_screen_battery =
	{
		.type = TYPE_GUI_LAYOUT_SCROLL,
		.children = gui_widget_battery_list,
		.child_num = countof(gui_widget_battery_list),
		.layout_config = &gui_layout_scroll_battery,
};
