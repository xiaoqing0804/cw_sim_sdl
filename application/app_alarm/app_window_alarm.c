
#include "bsp_includes.h"
#include "picture.h"
#include "language.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"


#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_base.h"

#include "application_config_main_window.h"

#include "app_window_alarm.h"


#define UI_PI		3.14159265358979f

static const gui_image_struct gui_alarm_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .scale = 1.5f,
    .anchor_x = ANCHOR_VALUE(0.5f),
    .anchor_y = ANCHOR_VALUE(0.5f),
    .x = LCD_SIZE_HALF_WIDTH,
    .y = LCD_SIZE_HALF_HEIGHT,
    .data = &pic_alarm_info,
};


// time ----------------------------------------------------------------------------
static const gui_number_image_list_struct gui_alarm_time_image =
{
	.number =
	{
		&pic_alarm_0_info,
		&pic_alarm_1_info,
		&pic_alarm_2_info,
		&pic_alarm_3_info,
		&pic_alarm_4_info,
		&pic_alarm_5_info,
		&pic_alarm_6_info,
		&pic_alarm_7_info,
		&pic_alarm_8_info,
		&pic_alarm_9_info,
	},
	.colon = &pic_alarm_two_point_info,
};

static const gui_image_number_struct gui_alarm_time_number =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.number_image_list = &gui_alarm_time_image,
	.value.string = "00:00",
};

static const gui_control_digital_struct  gui_alarm_time =
{
	.value_type = GUI_DIGITAL_VALUE_TYPE_IMAGE,
	.value.image_number = &gui_alarm_time_number,
};


static const gui_widget_struct gui_alarm_widget[] =
{
    {
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alarm_image,
    },
    {
        .type = TYPE_GUI_CONTROL_TIME,
        .y = LCD_SIZE_HEIGHT*2/3,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/3,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alarm_time,
    },
};

static const gui_screen_struct app_alarm_screen =
{
	.children = gui_alarm_widget,
	.child_num = countof(gui_alarm_widget),
};

/*-----------------------------ϵͳ�¼�--------------------------------------*/
static void app_window_alarm_init(void *buf)
{
}

static void app_window_alarm_load(void *buf)
{
}

static void app_window_alarm_entry(void *buf)
{
    SYS_DEBUG("app_window_alarm_entry()");
	send_motor_msg(MOTOR_MSG_ALARM);
	application_open_act_timer(APPLICATION_TIMER_ACT, 10*1000);
}

static void app_window_alarm_exit()
{
    SYS_DEBUG("app_window_alarm_exit()");
	close_motor_msg();
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_alarm_destroy(void)
{
}

static void app_window_alarm_ble_status(void* buf)
{
    SYS_DEBUG("app_window_main_ota_ble_status()");
    application_go_back();
}

static void app_window_alarm_timer_handler(void* buf)
{
    application_go_back();
}

/*-----------------------------����--------------------------------------*/

static const app_window_event_struct app_window_alarm_events[] =
{
    {
        .id = EVENT_BLE_CONNECT_STATUS,
        .handler = app_window_alarm_ble_status,
    },
    {
        .id = EVENT_ACT,
        .handler = app_window_alarm_timer_handler,
    },
    {
        .id = EVENT_BL_TIMEOUT,
        .handler = NULL,
    },
};


const gui_window_struct app_window_alarm =
{
	.screen = &app_alarm_screen,

	.init = app_window_alarm_init,
	.load = app_window_alarm_load,
	.entry = app_window_alarm_entry,
	.exit = app_window_alarm_exit,
	.destroy = app_window_alarm_destroy,

	.event_num = countof(app_window_alarm_events),
	.events = app_window_alarm_events,
};





