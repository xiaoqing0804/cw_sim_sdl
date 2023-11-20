
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_aging_test.h"

static const gui_canvas_struct gui_aging_test_line[] =
{
	 {
    	.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,     // TYPE_GUI_DRAW
        .penSize = 5,
        .penColor = COLOR_RGB(255, 255, 255),
    	.canvas.rect.x0 = 0,
    	.canvas.rect.y0 = 0,
    	.canvas.rect.x1 = LCD_SIZE_WIDTH,
    	.canvas.rect.y1 = LCD_SIZE_HEIGHT,
    },
};

static const gui_widget_struct gui_aging_test_widgets[] =
{
	{
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num =countof(gui_aging_test_line),
        .children = gui_aging_test_line,
    },
};

const gui_screen_struct gui_screen_aging_test =
{
	.children = gui_aging_test_widgets,
	.child_num = countof(gui_aging_test_widgets),
};


/*-----------------------------系统事件--------------------------------------*/
static void app_window_aging_test_init(void *buf)
{

}

static void app_window_aging_test_load(void *buf)
{
}


static void app_window_aging_test_entry(void *buf)
{
	hr_set_real_mode(true);
	send_motor_msg(MOTOR_MSG_MESSAGE);
	ext_btaud_test_speaker_music(1);
	application_open_act_timer(APPLICATION_TIMER_ACT, 60 * 1000);
	application_open_act_timer(APPLICATION_TIMER_ACT_1, 10 * 1000);
	application_open_act_timer(APPLICATION_TIMER_ACT_2, 8 * 1000);
}


static void app_window_aging_test_exit()
{
	application_close_act_timer(APPLICATION_TIMER_ACT);
	application_close_act_timer(APPLICATION_TIMER_ACT_1);
	application_close_act_timer(APPLICATION_TIMER_ACT_2);
}

static void app_window_aging_test_destroy()
{

}

static void app_window_aging_test_act_handle(void* buf)
{
	if (APPLICATION_TIMER_ACT == *((unsigned int*)buf))
	{
		hr_set_real_mode(true);
	}
	else if(APPLICATION_TIMER_ACT_1 == *((unsigned int*)buf))
	{
		ext_btaud_test_speaker_music(1);
	}
	else if(APPLICATION_TIMER_ACT_2 == *((unsigned int*)buf))
	{
		send_motor_msg(MOTOR_MSG_MESSAGE);
	}
}

static void app_window_aging_test_heartrate_handler(void* buf)
{
	hr_set_real_mode(false);
}

static const app_window_event_struct app_window_aging_test_static_events[] =
{
	{
		.id = EVENT_BL_TIMEOUT,	//�ؼ�ID.
		.handler = NULL,
	},

	{
		.id = EVENT_REAL_HEART,
		.handler = app_window_aging_test_heartrate_handler
	},

	{
		.id = EVENT_ACT,	//�ؼ�ID.
		.handler = app_window_aging_test_act_handle,
	}
};

/*-----------------------------配置--------------------------------------*/
const gui_window_struct app_window_aging_test =
{
	.screen = &gui_screen_aging_test,

	.init = app_window_aging_test_init,
	.load = app_window_aging_test_load,
	.entry = app_window_aging_test_entry,
	.exit = app_window_aging_test_exit,
	.destroy = app_window_aging_test_destroy,

	.event_num = countof(app_window_aging_test_static_events),
	.events = app_window_aging_test_static_events,
};




