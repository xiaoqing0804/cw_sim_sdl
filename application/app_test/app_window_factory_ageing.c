
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_factory_ageing.h"
#include "app_window_factory_ageing_test4.h"
/*-----------------------------老化列表--------------------------------------*/

static const gui_font_struct gui_factory_list_ageine1_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= "老化模式1",
};
static const gui_font_struct gui_factory_list_ageine2_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= "老化模式2",
};
static const gui_font_struct gui_factory_list_ageine3_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= "老化模式3",
};
static const gui_font_struct gui_factory_list_ageine4_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= "老化模式4",
};




enum{
	FACTORY_LIST_AGEINE_1=100,
	FACTORY_LIST_AGEINE_2,
	FACTORY_LIST_AGEINE_3,
	FACTORY_LIST_AGEINE_4,

};
static const gui_widget_struct gui_factory_ageing_widgets[] =
{
	//老化选项4种
	{ //老化模式1
		.id = FACTORY_LIST_AGEINE_1,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 50,
		.width = LCD_SIZE_WIDTH,
		.height = 30,
		.visible= 1,
        .child_num = 1,
        .children = &gui_factory_list_ageine1_text,
	},
	{ //老化模式2
		.id = FACTORY_LIST_AGEINE_2,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 130,
		.width = LCD_SIZE_WIDTH,
		.height = 30,
		.visible= 1,
        .child_num = 1,
        .children = &gui_factory_list_ageine2_text,
	},
	{ //老化模式3
		.id = FACTORY_LIST_AGEINE_3,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 210,
		.width = LCD_SIZE_WIDTH,
		.height = 30,
		.visible= 1,
        .child_num = 1,
        .children = &gui_factory_list_ageine3_text,
	},
	{ //老化模式4
		.id = FACTORY_LIST_AGEINE_4,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 0,
		.y = 290,
		.width = LCD_SIZE_WIDTH,
		.height = 30,
		.visible= 1,
        .child_num = 1,
        .children = &gui_factory_list_ageine4_text,
	},


};

const gui_screen_struct gui_screen_factory_ageing =
{
	.children = gui_factory_ageing_widgets,
	.child_num = countof(gui_factory_ageing_widgets),
};


/*-----------------------------主流程--------------------------------------*/
static int app_window_factory_ageing_enter(void) //进入窗口
{

}




/*-----------------------------老化模式--------------------------------------*/
static int app_window_factory_ageing_list(void) //老化选着列表
{
	gui_box_struct*  factory_list_ageine_1 = gui_surface_get_box(&gui_screen_factory_ageing, (unsigned short) FACTORY_LIST_AGEINE_1);
	gui_box_struct*  factory_list_ageine_2 = gui_surface_get_box(&gui_screen_factory_ageing, (unsigned short) FACTORY_LIST_AGEINE_2);
	gui_box_struct*  factory_list_ageine_3 = gui_surface_get_box(&gui_screen_factory_ageing, (unsigned short) FACTORY_LIST_AGEINE_3);
	gui_box_struct*  factory_list_ageine_4 = gui_surface_get_box(&gui_screen_factory_ageing, (unsigned short) FACTORY_LIST_AGEINE_4);
	factory_list_ageine_1->visible = 1;
	factory_list_ageine_2 ->visible = 1;
	factory_list_ageine_3->visible = 1;
	factory_list_ageine_4->visible = 1;
	//老化模式4种状态点击即可
}

/*-----------------------------????t--------------------------------------*/
static void app_window_factory_ageing_init(void *buf)
{

}

static void app_window_factory_ageing_load(void *buf)
{
    app_window_factory_ageing_list();
}


static void app_window_factory_ageing_entry(void *buf)
{

}


static void app_window_factory_ageing_exit()
{

}

static void app_window_factory_ageing_destroy()
{

}


static void app_window_factory_ageing_acttimer_handler(void* buf)
{

}

static void app_window_factory_ageing_key_handler(void *buf)
{
	application_goto_main();
}
static void app_window_factory_ageing_list_0_handler(gui_click_struct *event)
{
    SYS_DEBUG("app_window_factory_ageing_list_0_handler");
	factory_test_ageing(0);
	application_goto_main();
}
static void app_window_factory_ageing_list_1_handler(gui_click_struct *event)
{
     SYS_DEBUG("app_window_factory_ageing_list_1_handler");
	factory_test_ageing(1);
	application_goto_main();
}
static void app_window_factory_ageing_list_2_handler(gui_click_struct *event)
{
	factory_test_ageing(2);
	application_goto_main();
}
static void app_window_factory_ageing_list_3_handler(gui_click_struct *event)
{
	application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE,&app_window_factory_ageing_test_4,NULL);
}
/*-----------------------------??--------------------------------------*/
static const app_window_event_struct app_window_factory_ageing_static_events[] =
{
//	{.id = EVENT_ACT, .handler = app_window_factory_ageing_acttimer_handler },
    {.id = EVENT_KEY1_SHORT, .handler = app_window_factory_ageing_key_handler},
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_GO_HOME},
//	{.id = EVENT_ALL},
};

static const gui_touch_event_struct app_window_factory_ageing_touch_events[] =
{

	{//老化模式1
		.id = FACTORY_LIST_AGEINE_1,
		.click = app_window_factory_ageing_list_0_handler,
		.offset_top = 40,
	},
	{//老化模式2
		.id = FACTORY_LIST_AGEINE_2,
		.click = app_window_factory_ageing_list_1_handler,
		.offset_top = 40,
	},
	{//老化模式3
		.id = FACTORY_LIST_AGEINE_3,
		.click = app_window_factory_ageing_list_2_handler,
		.offset_top = 40,
	},
	{//老化模式4
		.id = FACTORY_LIST_AGEINE_4,
		.click = app_window_factory_ageing_list_3_handler,
		.offset_top = 40,
	},

};

static const gui_window_config_struct app_window_factory_ageing_config =
{
	.entry_back_to_destory = 1,
};


const gui_window_struct app_window_factory_ageing =
{
	.screen = &gui_screen_factory_ageing,
	.config = &app_window_factory_ageing_config,

	.init = app_window_factory_ageing_init,
	.load = app_window_factory_ageing_load,
	.entry = app_window_factory_ageing_entry,
	.exit = app_window_factory_ageing_exit,
	.destroy = app_window_factory_ageing_destroy,

	.touch_event_num = countof(app_window_factory_ageing_touch_events),
	.touch_events = app_window_factory_ageing_touch_events,

	.event_num = countof(app_window_factory_ageing_static_events),
	.events = app_window_factory_ageing_static_events,
};




