#include "debug_info.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "gui_window.h"
#include "app_window_alarm_clock.h"
#include "app_window_alarm_clock_set_time.h"
#include "app_window_alarm_clock_set_data.h"

static const gui_font_struct gui_text_clock_set_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CLOCK_TIME_SET,
};

static const gui_font_struct gui_text_clock_set_date =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CLOCK_DATE_SET,
};

static gui_image_struct g_gui_clock_set_delect =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_timer_add_info,
};

static const gui_font_struct gui_text_clock_set_delect =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CLOCK_SET_DELECT,
};

static gui_image_struct g_gui_clock_set_bg =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_set_bg_info,
};

static const gui_font_struct gui_text_clock_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_20,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00:00",
};

static gui_image_struct g_gui_clock_set_week_sun =     // must with static!
{

	    .type = TYPE_GUI_DRAW_PICTURE,
		.id = 3,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_clock_s_info,
};

static gui_image_struct g_gui_clock_set_week_mon =
{
	    .type = TYPE_GUI_DRAW_PICTURE,
		.id = 4,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_clock_m_info,
};

static gui_image_struct g_gui_clock_set_week_tue =
{
	    .type = TYPE_GUI_DRAW_PICTURE,
		.id = 5,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_clock_t_info,
};

static gui_image_struct g_gui_clock_set_week_wed =
{
    .type = TYPE_GUI_DRAW_PICTURE,
	.id = 6,

	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_w_info,
};

static gui_image_struct g_gui_clock_set_week_thu =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 7,

	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_t_info,
};

static gui_image_struct g_gui_clock_set_week_fri =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 8,

	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_f_info,
};

static gui_image_struct g_gui_cloc_setk_week_sat =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 9,

	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_s_info,
};

enum{
	CLOCK_SET_DELECT = 100,
	CLOCK_SET_TEXT_DELECT,
	CLOCK_SET_TIME,
	CLOCK_SET_TIME_TEXT,
	CLOCK_SET_TIME_BG,
	CLOCK_SET_DATE,
	CLOCK_SET_DATE_TEXT,
	CLOCK_SET_DATE_BG,
	CLOCK_SET_DATE_SUN,
	CLOCK_SET_DATE_MON,
	CLOCK_SET_DATE_TUE,
	CLOCK_SET_DATE_WED,
	CLOCK_SET_DATE_THB,
	CLOCK_SET_DATE_FRI,
	CLOCK_SET_DATE_SAT,
};


static const gui_widget_struct gui_widget_clock_set[] =
{
	{
		.id = CLOCK_SET_DELECT,
		.type = TYPE_GUI_CONTROL_IMAGE,
        .y = 364,
        .width = LCD_SIZE_WIDTH,
        .height = 102,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_delect,
	},
	{
		.id = CLOCK_SET_TEXT_DELECT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 395,
        .width = LCD_SIZE_WIDTH,
        .height = 43,
        .rotate = 0,
        .visible= 1,
        .child_num = 1,
        .children = &gui_text_clock_set_delect,
	},
	{
		.id = CLOCK_SET_TIME_BG,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 365,
        .y = 130,
        .width = LCD_SIZE_WIDTH,
        .height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_bg,
	},

	{
		.id = CLOCK_SET_TIME,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 54,
        .y = 95,
        .width = LCD_SIZE_WIDTH,
        .height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_clock_set_time,
	},


	{
		.id = CLOCK_SET_TIME_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 54,
        .y = 135,
        .width = LCD_SIZE_WIDTH,
        .height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_clock_time,
	},

	{
		.id = CLOCK_SET_DATE_BG,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 365,
		.y = 230,
		.width = LCD_SIZE_WIDTH,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_bg,
	},

	{
		.id = CLOCK_SET_DATE,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 54,
        .y = 205,
        .width = LCD_SIZE_WIDTH,
        .height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_clock_set_date,
	},

	{
		.id = CLOCK_SET_DATE_SUN,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 54,
		.y = 265,
		.width = LCD_SIZE_WIDTH,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_week_sun,
	},

	{
		.id = CLOCK_SET_DATE_MON,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 79,
		.y = 265,
		.width = LCD_SIZE_WIDTH,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_week_mon,
	},

	{
		.id = CLOCK_SET_DATE_TUE,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 104,
		.y = 265,
		.width = LCD_SIZE_WIDTH,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_week_tue,
	},

	{
		.id = CLOCK_SET_DATE_WED,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 129,
		.y = 265,
		.width = LCD_SIZE_WIDTH,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_week_wed,
	},

	{
		.id = CLOCK_SET_DATE_THB,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 154,
		.y = 265,
		.width = LCD_SIZE_WIDTH,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_week_thu,
	},

	{
		.id = CLOCK_SET_DATE_FRI,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 179,
		.y = 265,
		.width = LCD_SIZE_WIDTH,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_week_fri,
	},

	{
		.id = CLOCK_SET_DATE_SAT,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 204,
		.y = 265,
		.width = LCD_SIZE_WIDTH,
		.height = 70,
		.visible= 1,
		.child_num = 1,
		.children = &g_gui_clock_set_week_fri,
	},
};



const gui_screen_struct gui_screen_clock_set=
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_widget_clock_set,
	.child_num = countof(gui_widget_clock_set),
};


/*-----------------------------系统事件--------------------------------------*/

static void app_window_clock_set_init(void *buf)
{
}

static void app_window_clock_set_load(void *buf)
{
	time_struct time;
    sys_time_get(&time);
	char temp[20];


//	application_titlebar_create(&gui_screen_clock_set, STRING_CLOCK_SET);
	gui_box_struct*  box = gui_surface_get_box(&gui_screen_clock_set,CLOCK_SET_TIME_TEXT);

	snprintf(temp, sizeof(temp), "%02d:%02d",g_alarm_clock[g_clock_box_id-10].hour,g_alarm_clock[g_clock_box_id-10].min );

	gui_surface_box_label_change_string(box,temp);

	gui_box_struct*  sun = gui_surface_get_box(&gui_screen_clock_set,CLOCK_SET_DATE_SUN);
	gui_box_struct*  sat = gui_surface_get_box(&gui_screen_clock_set,CLOCK_SET_DATE_SAT);
	gui_box_struct*  fri = gui_surface_get_box(&gui_screen_clock_set,CLOCK_SET_DATE_FRI);
	gui_box_struct*  thb = gui_surface_get_box(&gui_screen_clock_set,CLOCK_SET_DATE_THB);
	gui_box_struct*  wed = gui_surface_get_box(&gui_screen_clock_set,CLOCK_SET_DATE_WED);
	gui_box_struct*  tue = gui_surface_get_box(&gui_screen_clock_set,CLOCK_SET_DATE_TUE);
	gui_box_struct*  mon = gui_surface_get_box(&gui_screen_clock_set,CLOCK_SET_DATE_MON);


	if((g_alarm_clock[g_clock_box_id-10].repeat & 0X01) > 0)
		gui_surface_box_image_change(sun,&pic_clock_s1_info);
	else
		gui_surface_box_image_change(sun,&pic_clock_s_info);

	if((g_alarm_clock[g_clock_box_id-10].repeat & 0X40) > 0)
		gui_surface_box_image_change(sat,&pic_clock_s1_info);
	else
		gui_surface_box_image_change(sat,&pic_clock_s_info);

	if((g_alarm_clock[g_clock_box_id-10].repeat & 0X20) > 0)
		gui_surface_box_image_change(fri,&pic_clock_f1_info);
	else
		gui_surface_box_image_change(fri,&pic_clock_f_info);

	if((g_alarm_clock[g_clock_box_id-10].repeat & 0X10) > 0)
		gui_surface_box_image_change(thb,&pic_clock_t1_info);
	else
		gui_surface_box_image_change(thb,&pic_clock_t_info);

	if((g_alarm_clock[g_clock_box_id-10].repeat & 0X08) > 0)
		gui_surface_box_image_change(wed,&pic_clock_w1_info);
	else
		gui_surface_box_image_change(wed,&pic_clock_w_info);

	if((g_alarm_clock[g_clock_box_id-10].repeat & 0X04) > 0)
		gui_surface_box_image_change(tue,&pic_clock_t1_info);
	else
		gui_surface_box_image_change(tue,&pic_clock_t_info);

	if((g_alarm_clock[g_clock_box_id-10].repeat & 0X02) > 0)
		gui_surface_box_image_change(mon,&pic_clock_m1_info);
	else
		gui_surface_box_image_change(mon,&pic_clock_m_info);

	application_titlebar_create(&gui_screen_clock_set,STRING_CLOCK_SET);
}


static void app_window_clock_set_entry(void *buf)
{

}


static void app_window_clock_set_exit()
{
	block_save_user_info(&g_alarm_clock);
}

static void app_window_clock_set_destroy()
{

}



/*-----------------------------响应事件--------------------------------------*/
static void app_window_clock_delect_event_touch(gui_click_struct *event)
{
    unsigned char delect_number = ALARM_CLOCK_MAX_TOTAL-1;
    unsigned char delect_id = g_clock_box_id -10;

	 memset(&g_alarm_clock[delect_id], 0, sizeof(alarm_clock_info_struct));

	if(g_alarm_clock[delect_id+1].offon!=0&&delect_id!=delect_number)
	{
		for (char colck_i = 0; colck_i < delect_number-delect_id; colck_i++)
		{
		    g_alarm_clock[delect_id+ colck_i]= g_alarm_clock[delect_id+ colck_i+1];
			if(colck_i+1==(delect_number-delect_id))
				memset(&g_alarm_clock[delect_id+colck_i+1], 0, sizeof(alarm_clock_info_struct));
		}
	}

	 block_save_user_info(&g_alarm_clock);

	 application_go_back();
}

static void app_window_clock_time_event_touch(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_clock_set_time, NULL);
}

static void app_window_clock_data_event_touch(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_clock_data_list, NULL);
}


/*-----------------------------配置--------------------------------------*/

static const gui_touch_event_struct app_window_clock_set_touch_events[] =
{
	{	.id = CLOCK_SET_DELECT,
		.click = app_window_clock_delect_event_touch,
	},


	{	.id = CLOCK_SET_TIME,
		.click = app_window_clock_time_event_touch,
		.offset_bottom = 70,
	},

	{	.id = CLOCK_SET_DATE,
		.click = app_window_clock_data_event_touch,
		.offset_bottom = 70,
	},
};



const gui_window_struct app_window_clock_set =
{
	.screen = &gui_screen_clock_set,
	.init = app_window_clock_set_init,
	.load = app_window_clock_set_load,
	.entry = app_window_clock_set_entry,
	.exit = app_window_clock_set_exit,
	.destroy = app_window_clock_set_destroy,

	.touch_event_num = countof(app_window_clock_set_touch_events),
	.touch_events = app_window_clock_set_touch_events,
};

