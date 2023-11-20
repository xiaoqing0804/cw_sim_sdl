
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "syscfg_id.h"
#include "app_window_hrtest_set_bio.h"

static unsigned char set_bio1_flg =0;
static unsigned char set_bio2_flg =0;
static  unsigned short int set_bio_value = 0;
static unsigned short int set_bio1_value =0;   //对空  注：此值默认值要写入flash
static unsigned short int set_bio2_value =0;	//对手
static unsigned short int set_bio_in_value =0; 	//bio in 参考标准计算

static unsigned short int set_bio_diff_standrd = 95*0.75; // 多个机器的（bio1-bio0）是一个参考标准


static const gui_font_struct gui_hrtest_set_bio_text_title =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "BIO SET",
};


static const gui_font_struct gui_hrtest_set_bio_text1 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(97, 97, 97),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "bio left",
};

static const gui_font_struct gui_hrtest_set_bio_text2 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "bio1",
};

static const gui_font_struct gui_hrtest_set_bio_text3 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(97, 97, 97),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "bio right",
};

static const gui_font_struct gui_hrtest_set_bio_text4 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "bio2",
};

static const gui_font_struct gui_hrtest_set_bio_text5 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(180, 0, 180),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "duikong",
};
static const gui_font_struct gui_hrtest_set_bio_text6 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(180, 0, 180),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "duishou",
};
static const gui_font_struct gui_hrtest_set_bio_text7 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(180, 180, 0),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "ok",
};
static const gui_font_struct gui_hrtest_set_bio_text8 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(0, 180, 180),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "biaozhun",
};
static const gui_widget_struct gui_hrtest_set_bio_widgets[] =
{
	{	//title
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = (0*LCD_SIZE_HEIGHT)/5,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT/5,
		.visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text_title,
	},
    {
        .id = 1,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (1*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH/2,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text1,
    },
    {
        .id = 2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (1*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH/2,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text2,
    },
    {
        .id = 3,
        .type = TYPE_GUI_CONTROL_LABEL,
		.x = LCD_SIZE_WIDTH/2,
        .y = (1*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH/2,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text3,
    },
    {
        .id = 4,
        .type = TYPE_GUI_CONTROL_LABEL,
		.x = LCD_SIZE_WIDTH/2,
        .y = (1*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH/2,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text4,
    },
    {
        .id = 5,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (2*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH/2,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text5,
    },
    {
        .id =6,
        .type = TYPE_GUI_CONTROL_LABEL,
		.x = LCD_SIZE_WIDTH/2,
        .y = (2*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH/2,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text6,
    },
    {
        .id =7,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (3*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text7,
    },
    {
        .id =8,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (4*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_set_bio_text8,
    },

};

const gui_screen_struct gui_screen_hrtest_set_bio =
{
	.children = gui_hrtest_set_bio_widgets,
	.child_num = countof(gui_hrtest_set_bio_widgets),
};

static unsigned int m_test_time;


static int app_window_hrtest_set_bio_update(void)
{
	gui_box_struct* box;
	char temp[100];
	set_bio_value =hr_get_vc9202_bio();

	if(set_bio1_flg&&!set_bio2_flg )
	{
		gui_box_struct* bio_id2 = gui_surface_get_box(&gui_screen_hrtest_set_bio, 1);
		bio_id2->visible =0;
		gui_box_struct* bio_id3 = gui_surface_get_box(&gui_screen_hrtest_set_bio, 4);
		bio_id3->visible =0;

		snprintf(temp, sizeof(temp),"%d", set_bio_value);
		box = gui_surface_get_box(&gui_screen_hrtest_set_bio, 2);
		box->visible = 1;
		if (box != NULL) {
			gui_surface_control_scrolltext_change_string(box, (unsigned char*)temp);
		}

		snprintf(temp, sizeof(temp),"%d", set_bio2_value);
		box = gui_surface_get_box(&gui_screen_hrtest_set_bio, 3);
		box->visible = 1;
		if (box != NULL) {
			gui_surface_control_scrolltext_change_string(box, (unsigned char*)temp);
		}



	}else if(!set_bio1_flg&&set_bio2_flg)
	{
		gui_box_struct* bio_id3 = gui_surface_get_box(&gui_screen_hrtest_set_bio, 2);
		bio_id3->visible =0;
		gui_box_struct* bio_id4 = gui_surface_get_box(&gui_screen_hrtest_set_bio, 3);
		bio_id4->visible =0;


		snprintf(temp, sizeof(temp),"%d", set_bio1_value);
		box = gui_surface_get_box(&gui_screen_hrtest_set_bio, 1);
		box->visible = 1;
		if (box != NULL) {
			gui_surface_control_scrolltext_change_string(box, (unsigned char*)temp);
		}


		snprintf(temp, sizeof(temp),"%d", set_bio_value);
		box = gui_surface_get_box(&gui_screen_hrtest_set_bio, 4);
		box->visible = 1;
		if (box != NULL) {
			gui_surface_control_scrolltext_change_string(box, (unsigned char*)temp);
		}

	}else{

		gui_box_struct* bio_id3 = gui_surface_get_box(&gui_screen_hrtest_set_bio, 2);
		bio_id3->visible =0;
		gui_box_struct* bio_id5 = gui_surface_get_box(&gui_screen_hrtest_set_bio, 4);
		bio_id5->visible =0;

		snprintf(temp, sizeof(temp),"%d", set_bio1_value);
		box = gui_surface_get_box(&gui_screen_hrtest_set_bio, 1);
		box->visible = 1;
		if (box != NULL) {
			gui_surface_control_scrolltext_change_string(box, (unsigned char*)temp);
		}

		snprintf(temp, sizeof(temp),"%d", set_bio2_value);
		box = gui_surface_get_box(&gui_screen_hrtest_set_bio, 3);
		box->visible = 1;
		if (box != NULL) {
			gui_surface_control_scrolltext_change_string(box, (unsigned char*)temp);
		}

		snprintf(temp, sizeof(temp),"%d", set_bio_diff_standrd);
		box = gui_surface_get_box(&gui_screen_hrtest_set_bio, 8);

		if (box != NULL) {
			gui_surface_control_scrolltext_change_string(box, (unsigned char*)temp);
		}




	}
	if(set_bio_in_value>0)
	{
		snprintf(temp, sizeof(temp),"%d", set_bio_in_value);
		box = gui_surface_get_box(&gui_screen_hrtest_set_bio, 7);

		if (box != NULL) {
			gui_surface_control_scrolltext_change_string(box, (unsigned char*)temp);
		}


	}


	gui_surface_commit();


}



/*-----------------------------????t--------------------------------------*/
static void app_window_hrtest_set_bio_init(void *buf)
{
	set_bio1_flg=0;
	set_bio2_flg=0;
}

static void app_window_hrtest_set_bio_load(void *buf)
{
	app_window_hrtest_set_bio_update();
}


static void app_window_hrtest_set_bio_entry(void *buf)
{
    m_test_time = 0;
	hr_close_all();
	send_motor_msg(MOTOR_MSG_LIGHTWEIGHT_VIBRATION);
    application_open_act_timer(APPLICATION_TIMER_ACT, 400);
}


static void app_window_hrtest_set_bio_exit()
{
	close_motor_msg();
	hr_set_cross_test_mode(0);
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_hrtest_set_bio_destroy()
{

}


static void app_window_hrtest_set_bio_acttimer_handler(void* buf)
{
    if (m_test_time == 0) {
        hr_set_cross_test_mode(1);
    }
    else{
       app_window_hrtest_set_bio_update();
    }
    m_test_time ++;
}

static void app_window_hrtest_set_bio_apptest_handler(void *buf)
{
    m_test_time = 0;
    if(0 == g_app_test.onoff) {
        hr_set_cross_test_mode(0);
        application_goto_main();
    }
    else {
        app_window_hrtest_set_bio_update();
    }
}

static void app_window_hrtest_set_bio_key_handler(void *buf)
{
    hr_set_cross_test_mode(0);
    application_goto_main();
}

static unsigned char app_window_hrtest_set_bio_click(gui_click_struct *event)
{

	if(event->x <LCD_SIZE_WIDTH/2&&event->y<LCD_SIZE_HEIGHT*2/5)
	{
		//bio1
		if(!set_bio2_flg)
		{
			set_bio1_flg = !set_bio1_flg;
		}
		if(set_bio1_flg)
		{
			set_bio1_value = set_bio_value;
			syscfg_write(CFG_BSP_HR_BIO, &set_bio1_value, 1);//存储到vm对空值
		}


	}else if((event->x >LCD_SIZE_WIDTH/2 && event->y<LCD_SIZE_HEIGHT*2/5))
	{
		//bio2
		if(!set_bio1_flg)
		{
			set_bio2_flg = !set_bio2_flg;
		}
		if(set_bio2_flg)
		{
			set_bio2_value = set_bio_value;
		}

	}else
	{
		if(set_bio1_flg==0 && set_bio2_flg==0){
            //确认
            set_bio_in_value = (set_bio1_value - set_bio2_value)/2;
            syscfg_write(CFG_BSP_HR_BIO_IN, &set_bio_in_value, 1);//存储到vm bio1-bio0值
        }

	}
	  HR_DEBUG("app_window_hrtest_set_bio_click %d  (%d,%d)",set_bio_in_value,set_bio1_value,set_bio2_value);
	app_window_hrtest_set_bio_update();

}




/*-----------------------------??--------------------------------------*/
static const app_window_event_struct app_window_hrtest_set_bio_static_events[] =
{
	{.id = EVENT_ACT, .handler = app_window_hrtest_set_bio_acttimer_handler },
    {.id = EVENT_APP_TEST, .handler = app_window_hrtest_set_bio_apptest_handler},
    {.id = EVENT_KEY1_SHORT, .handler = app_window_hrtest_set_bio_key_handler},
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_GO_HOME}
};

static const gui_touch_event_struct app_window_hrtest_set_bio_touch_events[] =
{
	{
		.id = 0xFFFF,	//
		.click = app_window_hrtest_set_bio_click,
	},

};

static const gui_window_config_struct app_window_hrtest_set_bio_config =
{
	.entry_back_to_destory = 1,
	.forbid_gesture_back = 1,
};


const gui_window_struct app_window_hrtest_set_bio =
{
	.screen = &gui_screen_hrtest_set_bio,
	.config = &app_window_hrtest_set_bio_config,

	.init = app_window_hrtest_set_bio_init,
	.load = app_window_hrtest_set_bio_load,
	.entry = app_window_hrtest_set_bio_entry,
	.exit = app_window_hrtest_set_bio_exit,
	.destroy = app_window_hrtest_set_bio_destroy,

	.touch_event_num = countof(app_window_hrtest_set_bio_touch_events),
	.touch_events = app_window_hrtest_set_bio_touch_events,

	.event_num = countof(app_window_hrtest_set_bio_static_events),
	.events = app_window_hrtest_set_bio_static_events,
};




