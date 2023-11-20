
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_hrtest.h"
#include "app_window_hrtest_set_bio.h"

static const gui_font_struct gui_hrtest_text_title =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "HR TEST",
};


static const gui_font_struct gui_hrtest_text1 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "curr: 0",
};

static const gui_font_struct gui_hrtest_text2 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "red: 0",
};

static const gui_font_struct gui_hrtest_text3 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "green: 0",
};

static const gui_font_struct gui_hrtest_text4 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "ir: 0",
};

static const gui_font_struct gui_hrtest_text5 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "LouGuangok",
};
static const gui_font_struct gui_hrtest_text6 =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "HongWaiok",
};
static const gui_canvas_struct factory_ageing_red[] =
{
     {
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
        .penSize = 5,
        .penColor = COLOR_RGB(255, 0, 0),
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_WIDTH,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT,
    },
};
static const gui_canvas_struct factory_ageing_green[] =
{
      {
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
        .penSize = 5,
        .penColor = COLOR_RGB(0, 255, 0),
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_WIDTH,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT,
    },
};
static const gui_widget_struct gui_hrtest_widgets[] =
{
    {   // RED
		.id = 8,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = countof(factory_ageing_red),
        .children = &factory_ageing_red,
    },
    {   // GREEN
		.id = 9,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 0,
        .child_num = countof(factory_ageing_green),
        .children = &factory_ageing_green,
    },
    {
        .id = 5,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 30,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 0,
        .child_num = 1,
        .children = &gui_hrtest_text5,
    },
    {
        .id =6,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 30,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 0,
        .child_num = 1,
        .children = &gui_hrtest_text6,
    },
	{
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = (0*LCD_SIZE_HEIGHT)/5,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT/5,
		.visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_text_title,
	},
    {
        .id = 1,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (1*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_text1,
    },
    {
        .id = 2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (2*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_text2,
    },
    {
        .id = 3,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (3*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_text3,
    },
    {
        .id = 4,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (4*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_hrtest_text4,
    },
};

const gui_screen_struct gui_screen_hrtest =
{
	.children = gui_hrtest_widgets,
	.child_num = countof(gui_hrtest_widgets),
};

static unsigned int m_test_time;

/*-----------------------------系统事件--------------------------------------*/
static void app_window_hrtest_init(void *buf)
{

}

static void app_window_hrtest_load(void *buf)
{
    char temp[48];
    int hr_v1 = 0, hr_v2 = 0, hr_v3 = 0, hr_v4 = 0,hr_v5;
    gui_box_struct*  box;

    hr_get_values(&hr_v1, &hr_v2, &hr_v3, &hr_v4,&hr_v5);
    box = gui_surface_get_box(&gui_screen_hrtest, 1);
    if (box != NULL) {
        sprintf(temp, "pre: %d", hr_v1);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_hrtest, 2);
    if (box != NULL) {
        sprintf(temp, "curr: %d", hr_v2);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_hrtest, 3);
    if (box != NULL) {
        sprintf(temp, "ps: %d", hr_v3);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_hrtest, 4);
    if (box != NULL) {
        sprintf(temp, "SET BIO: %d", hr_v5);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    gui_box_struct* light_leak = gui_surface_get_box(&gui_screen_hrtest, 5);
    gui_box_struct* infrared = gui_surface_get_box(&gui_screen_hrtest, 6);
    gui_box_struct* red = gui_surface_get_box(&gui_screen_hrtest, 8);
    gui_box_struct* green = gui_surface_get_box(&gui_screen_hrtest, 9);
    if((((hr_v5>>0)&1)==1)&&(((hr_v5>>1)&1)==1))
    {
        light_leak->visible = 1;
        infrared->visible = 0;
        red->visible = 0;
        green->visible = 1;
    }else if(((hr_v5>>2)&1)==1)
    {
        light_leak->visible = 0;
        infrared->visible = 1;
        red->visible = 0;
        green->visible = 1;
    }else{
        light_leak->visible = 0;
        infrared->visible = 0;
        red->visible = 1;
        green->visible = 0;
    }
    gui_surface_commit();
}


static void app_window_hrtest_entry(void *buf)
{
    m_test_time = 0;
	hr_close_all();
	send_motor_msg(MOTOR_MSG_LIGHTWEIGHT_VIBRATION);
    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}


static void app_window_hrtest_exit()
{
	close_motor_msg();
	hr_set_cross_test_mode(0);
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_hrtest_destroy()
{

}


static void app_window_hrtest_acttimer_handler(void* buf)
{
    if (m_test_time == 0) {
        hr_set_cross_test_mode(1);
    }
    else if(m_test_time > 60) {
        hr_set_cross_test_mode(0);
        application_goto_main();
    }
    else{
        app_window_hrtest_load(NULL);
    }
    m_test_time ++;
}

static void app_window_hrtest_apptest_handler(void *buf)
{
    m_test_time = 0;
    if(0 == g_app_test.onoff) {
        hr_set_cross_test_mode(0);
        application_goto_main();
    }
    else {
        app_window_hrtest_load(NULL);
    }
}

static void app_window_hrtest_key_handler(void *buf)
{
    hr_set_cross_test_mode(0);
    application_goto_main();
}
static unsigned char app_window_hrtest_click(gui_click_struct *event)
{
	//application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_hrtest_set_bio,NULL);
}
/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_hrtest_static_events[] =
{
	{.id = EVENT_ACT, .handler = app_window_hrtest_acttimer_handler },
    {.id = EVENT_APP_TEST, .handler = app_window_hrtest_apptest_handler},
    {.id = EVENT_KEY1_SHORT, .handler = app_window_hrtest_key_handler},
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_GO_HOME}
};
static const gui_touch_event_struct app_window_hrtest_touch_events[] =
{
	{
		.id =4,	//
		.click = app_window_hrtest_click,
	},

};

static const gui_window_config_struct app_window_hrtest_config =
{
	.entry_back_to_destory = 1,
};


const gui_window_struct app_window_hrtest =
{
	.screen = &gui_screen_hrtest,
	.config = &app_window_hrtest_config,

	.init = app_window_hrtest_init,
	.load = app_window_hrtest_load,
	.entry = app_window_hrtest_entry,
	.exit = app_window_hrtest_exit,
	.destroy = app_window_hrtest_destroy,

    .touch_event_num = countof(app_window_hrtest_touch_events),
	.touch_events = app_window_hrtest_touch_events,

	.event_num = countof(app_window_hrtest_static_events),
	.events = app_window_hrtest_static_events,
};




