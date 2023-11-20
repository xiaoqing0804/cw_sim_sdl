#include "app_window_wear.h"
#include "debug_info.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "gui_window.h"
#include "arithmetic_steps.h"
#include "data_receive_package.h"
#include "application_config_list.h"

static const gui_font_struct gui_wear_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_HEART_NO_TOUCH,
};


static const gui_image_struct gui_wear_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_o2_start_measurement_info,
};


static const gui_widget_struct gui_wear_widget[] =
{
	{
		.id = 1,
		.x = 0,
        .y = 253,  // pic_operator2_ok_info.height,
		.type = TYPE_GUI_CONTROL_LABEL,
		.width = LCD_SIZE_WIDTH,
		.height = 106,
		.visible= 1,
        .child_num = 1,
        .children = &gui_wear_text,
	},

    {
        .id = 3,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 0,
        .y = 110,  // pic_operator2_ok_info.height,
        .width = LCD_SIZE_WIDTH,
        .height = 106,
        .visible= 1,
        .child_num = 1,
        .children = &gui_wear_image,
    },
};

static const gui_screen_struct gui_screen_wear =
{
	.children = gui_wear_widget,
	.child_num = countof(gui_wear_widget),
};



/*-----------------------------系统事件--------------------------------------*/

static void app_window_wear_init(void *buf)
{
}

static void app_window_wear_load(void *buf)
{
}


static void app_window_wear_entry(void *buf)
{
	application_open_act_timer(APPLICATION_TIMER_ACT,3000);
}


static void app_window_wear_exit()
{
	application_close_act_timer(APPLICATION_TIMER_ACT_1);
}

static void app_window_wear_destroy()
{
	application_close_act_timer(APPLICATION_TIMER_ACT_1);
}



/*-----------------------------响应事件--------------------------------------*/
static void app_window_wear_static_event_act(void *buf)
{
	application_goto_main();
}


/*-----------------------------配置--------------------------------------*/

static const app_window_event_struct app_window_wear_touch_events[] =
{
	{
		.id = EVENT_ACT,	//控件ID.
		.handler = app_window_wear_static_event_act,
	},
	{.id = EVENT_BL_TIMEOUT},
};

static const gui_window_config_struct app_window_wear_config =
{
	.forbid_gesture_back = 1,
};


const gui_window_struct app_window_wear =
{
	.screen = &gui_screen_wear,
	.config = &app_window_wear_config,
	.init = app_window_wear_init,
	.load = app_window_wear_load,
	.entry = app_window_wear_entry,
	.exit = app_window_wear_exit,
	.destroy = app_window_wear_destroy,

	.event_num = countof(app_window_wear_touch_events),
	.events = app_window_wear_touch_events,


};

