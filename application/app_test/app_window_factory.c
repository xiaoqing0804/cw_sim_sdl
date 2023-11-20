
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_factory.h"
#include "app_window_factory_ageing.h"
#include "app_window_factory_worker.h"
#include "app_window_stand_alone.h"

static unsigned char factory_mode_flg = 0; // 模式选着 0：老化模式 1：工厂模式2:单条测试模式

/*-----------------------------主流程--------------------------------------*/
static const gui_font_struct gui_factory_mode_opt_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "模式选择",
};
static const gui_font_struct gui_factory_mode_ageine_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "老化模式",
};
static const gui_font_struct gui_factory_mode_test_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "工厂模式",
};

static const gui_font_struct gui_stand_alone_mode_test_text =
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "单条测试",
};

static const gui_image_struct gui_factory_no_image =
	{
		.type = TYPE_GUI_DRAW_PICTURE,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.data = &pic_operator2_cancel_info,
};

static const gui_image_struct gui_factory_yes_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
	.data = &pic_operator2_ok_info,
};

static const gui_font_struct gui_factory_ageine_enter_text = // 是否进入老化模式
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "是否进入老化模式",
};

static const gui_font_struct gui_factory_test_enter_text = // 是否进入工厂模式
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "是否进入工厂模式",
};

static const gui_font_struct gui_stand_alone_test_enter_text = // 是否进入工厂模式
	{
		.type = TYPE_GUI_DRAW_TEXT,
		.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
		.color = COLOR_RGB(255, 255, 255),
		.size = SYS_FONT_SMALL,
		.value_type = GUI_FONT_VALUE_TYPE_STRING,
		.value.string = "是否进入单条测试模式",
};

enum
{
	FACTORY_MODE_TEXT = 100,
	FACTORY_AGEINE_ENTER_TEXT,
	FACTORY_TEST_ENTER_TEXT,
	FACTORY_STAND_ALONE_TEXT,
	FACTORY_AGEINE_YES_ENTER_TEXT,
	FACTORY_TEST_YES_ENTER_TEXT,
	FACTORY_YES_STAND_ALONE_TEXT,
	FACTORY_YES_IMAGE,
	FACTORY_NO_IMAGE,

};
static const gui_widget_struct gui_factory_widgets[] =
	{

		{
			// 模式选着
			.id = FACTORY_MODE_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 80,
			.width = LCD_SIZE_WIDTH,
			.height = 30,
			.visible = 0,
			.child_num = 1,
			.children = &gui_factory_mode_opt_text,
		},
		{
			// 老化模式
			.id = FACTORY_AGEINE_ENTER_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 200,
			.width = LCD_SIZE_WIDTH / 2,
			.height = 30,
			.visible = 0,
			.child_num = 1,
			.children = &gui_factory_mode_ageine_text,
		},
		{
			// 工厂模式
			.id = FACTORY_TEST_ENTER_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = LCD_SIZE_WIDTH / 2,
			.y = 200,
			.width = LCD_SIZE_WIDTH / 2,
			.height = 30,
			.visible = 0,
			.child_num = 1,
			.children = &gui_factory_mode_test_text,
		},
		{
			// 单条测试模式
			.id = FACTORY_STAND_ALONE_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 265,
			.width = LCD_SIZE_WIDTH,
			.height = 30,
			.visible = 0,
			.child_num = 1,
			.children = &gui_stand_alone_mode_test_text,
		},

		{
			// 是否进入老化模式
			.id = FACTORY_AGEINE_YES_ENTER_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 80,
			.width = LCD_SIZE_WIDTH,
			.height = 30,
			.visible = 0,
			.child_num = 1,
			.children = &gui_factory_ageine_enter_text,
		},
		{
			// 是否进入工厂模式
			.id = FACTORY_TEST_YES_ENTER_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 80,
			.width = LCD_SIZE_WIDTH,
			.height = 30,
			.visible = 0,
			.child_num = 1,
			.children = &gui_factory_test_enter_text,
		},
		{
			// 是否进单条测试
			.id = FACTORY_YES_STAND_ALONE_TEXT,
			.type = TYPE_GUI_CONTROL_LABEL,
			.x = 0,
			.y = 80,
			.width = LCD_SIZE_WIDTH,
			.height = 30,
			.visible = 0,
			.child_num = 1,
			.children = &gui_stand_alone_test_enter_text,
		},

		{
			// 否
			.id = FACTORY_NO_IMAGE,
			.type = TYPE_GUI_CONTROL_IMAGE,
			.x = 0,
			.y = LCD_SIZE_HEIGHT*3/5,
			.width = LCD_SIZE_WIDTH/2,
			.height = LCD_SIZE_HEIGHT / 4,
			.visible = 0,
			.child_num = 1,
			.children = &gui_factory_no_image,
		},
		{//是
		    .id = FACTORY_YES_IMAGE,
		    .type = TYPE_GUI_CONTROL_IMAGE,
		    .x = LCD_SIZE_HALF_WIDTH,
		    .y = LCD_SIZE_HEIGHT*3/5,
		    .width = LCD_SIZE_WIDTH/2,
		    .height = LCD_SIZE_HEIGHT/4,
		    .visible= 0,
		    .child_num = 1,
		    .children = &gui_factory_yes_image,
		},

};

const gui_screen_struct gui_screen_factory =
	{
		.children = gui_factory_widgets,
		.child_num = countof(gui_factory_widgets),
};

/*-----------------------------主流程--------------------------------------*/

static int app_window_factory_enter(void) // 进入窗口
{
	gui_box_struct *box;

	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_MODE_TEXT);
	if (box != NULL)
		box->visible = 1;
	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_AGEINE_ENTER_TEXT);
	if (box != NULL)
		box->visible = 1;
	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_TEST_ENTER_TEXT);
	if (box != NULL)
		box->visible = 1;
	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_STAND_ALONE_TEXT);
	if (box != NULL)
		box->visible = 1;

	// 模式选着  //老化模式&&工厂模式
}

static int app_window_factory_yes_no(void) // 是否进入老化或者工厂模式
{
	gui_box_struct *box;

	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_MODE_TEXT);
	if (box != NULL)
		box->visible = 0;
	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_AGEINE_ENTER_TEXT);
	if (box != NULL)
		box->visible = 0;
	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_TEST_ENTER_TEXT);
	if (box != NULL)
		box->visible = 0;
	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_STAND_ALONE_TEXT);
	if (box != NULL)
		box->visible = 0;

	if (factory_mode_flg == 2)
	{
		box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_YES_STAND_ALONE_TEXT);
		if (box != NULL)
			box->visible = 1;
	}
	else if (factory_mode_flg == 1)
	{
		box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_TEST_YES_ENTER_TEXT);
		if (box != NULL)
			box->visible = 1;
	}
	else
	{
		box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_AGEINE_YES_ENTER_TEXT);
		if (box != NULL)
			box->visible = 1;
	}

	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_NO_IMAGE);
	if (box != NULL)
		box->visible = 1;
	box = gui_surface_get_box(&gui_screen_factory, (unsigned short)FACTORY_YES_IMAGE);
	if (box != NULL)
		box->visible = 1;
}
/*-----------------------------????t--------------------------------------*/
static void app_window_factory_init(void *buf)
{
	factory_mode_flg = 0;
}

static void app_window_factory_load(void *buf)
{
	app_window_factory_enter(); // 首次进入必然是开始界面
	//	app_window_factory_yes_no();
}

static void app_window_factory_entry(void *buf)
{
}

static void app_window_factory_exit()
{
}

static void app_window_factory_destroy()
{
}

static void app_window_factory_acttimer_handler(void *buf)
{
}

static void app_window_factory_key_handler(void *buf)
{
	application_goto_main();
}

static void app_window_factory_ageing_handler(gui_click_struct *event)
{
	factory_mode_flg = 0;
	app_window_factory_yes_no();
	gui_surface_commit();
}
static void app_window_factory_test_handler(gui_click_struct *event)
{
	factory_mode_flg = 1;
	app_window_factory_yes_no();
	gui_surface_commit();
}
static void app_window_stand_alone_test_handler(gui_click_struct *event)
{
	factory_mode_flg = 2;
	app_window_factory_yes_no();
	gui_surface_commit();
}

static void app_window_factory_list_handler(gui_click_struct *event)
{
	if (event->x < (LCD_SIZE_WIDTH / 2))
	{
		application_goto_main();
	}
	else
	{
		SYS_DEBUG("app_window_factory_list_handler");
		if (factory_mode_flg == 0)
			application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_factory_ageing, NULL);
		else if (factory_mode_flg == 1)
			application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_factory_worker, NULL);
		else
			application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_stand_alone, NULL);
	}
}
/*-----------------------------??--------------------------------------*/
static const app_window_event_struct app_window_factory_static_events[] =
	{
		//	{.id = EVENT_ACT, .handler = app_window_factory_acttimer_handler },
		{.id = EVENT_KEY1_SHORT, .handler = app_window_factory_key_handler},
		{.id = EVENT_BL_TIMEOUT},
		{.id = EVENT_GO_HOME},
		//	{.id = EVENT_ALL},
};

static const gui_touch_event_struct app_window_factory_touch_events[] =
	{
		{
			// 进入老化
			.id = FACTORY_AGEINE_ENTER_TEXT,
			.click = app_window_factory_ageing_handler,
			.offset_top = 40,
		},
		{
			// 进入工厂
			.id = FACTORY_TEST_ENTER_TEXT,
			.click = app_window_factory_test_handler,
			.offset_top = 40,
		},
		{
			// 单条测试
			.id = FACTORY_STAND_ALONE_TEXT,
			.click = app_window_stand_alone_test_handler,
			.offset_top = 40,
		},
		{//确认进入测试
			.id = FACTORY_YES_IMAGE,
			.click = app_window_factory_list_handler,
			.offset_top = 20,
		},
		{
			// 退出测试
			.id = FACTORY_NO_IMAGE,
			.click = app_window_factory_list_handler,
			.offset_top = 20,
		},

};

static const gui_window_config_struct app_window_factory_config =
	{
		.entry_back_to_destory = 1,
};

const gui_window_struct app_window_factory =
	{
		.screen = &gui_screen_factory,
		.config = &app_window_factory_config,

		.init = app_window_factory_init,
		.load = app_window_factory_load,
		.entry = app_window_factory_entry,
		.exit = app_window_factory_exit,
		.destroy = app_window_factory_destroy,

		.touch_event_num = countof(app_window_factory_touch_events),
		.touch_events = app_window_factory_touch_events,

		.event_num = countof(app_window_factory_static_events),
		.events = app_window_factory_static_events,
};
