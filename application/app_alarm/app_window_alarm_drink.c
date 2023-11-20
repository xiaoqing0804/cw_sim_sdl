
#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "bsp_includes.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "application_config_main_window.h"

#include "app_alarm/app_window_alarm_drink.h"


static const gui_image_struct gui_alarm_drink_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_drink_info,
};

static const gui_font_struct gui_drink_txt =   //
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.auto_wrap = 0,
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id =STRING_DRINK_WATER,
};

static const gui_widget_struct gui_alarm_drink_widget[] =
{
    {
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alarm_drink_image,
    },

		{
			.type = TYPE_GUI_CONTROL_LABEL,
			.y = 380,
			.width = LCD_SIZE_WIDTH,
			.height = 50,
			.rotate = 0,
			.visible= 1,
			.clip = 0,
			.space_x = 0,
			.space_y = 0,
			.child_num = 1,
			.children = &gui_drink_txt,
		},


};

static const gui_screen_struct app_alarm_drink_screen =
{
	.children = gui_alarm_drink_widget,
	.child_num = countof(gui_alarm_drink_widget),
};

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_alarm_drink_init(void *buf)
{
}

static void app_window_alarm_drink_load(void *buf)
{
}

static void app_window_alarm_drink_entry(void *buf)
{
    SYS_DEBUG("app_window_alarm_drink_entry()");
	send_motor_msg(MOTOR_MSG_REMIND);
	application_open_act_timer(APPLICATION_TIMER_ACT, 5*1000);
}

static void app_window_alarm_drink_exit()
{
    SYS_DEBUG("app_window_alarm_drink_exit()");
	close_motor_msg();
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_alarm_drink_destroy(void)
{
	close_motor_msg();
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_alarm_drink_timer_handler(void* buf)
{
    application_go_back();
}

/*-----------------------------����--------------------------------------*/

static const app_window_event_struct app_window_alarm_drink_events[] =
{
    {
        .id = EVENT_ACT,
        .handler = app_window_alarm_drink_timer_handler,
    },
    {
        .id = EVENT_BL_TIMEOUT,
        .handler = NULL,
    },
};


const gui_window_struct app_window_alarm_drink =
{
	.screen = &app_alarm_drink_screen,

	.init = app_window_alarm_drink_init,
	.load = app_window_alarm_drink_load,
	.entry = app_window_alarm_drink_entry,
	.exit = app_window_alarm_drink_exit,
	.destroy = app_window_alarm_drink_destroy,

	.event_num = countof(app_window_alarm_drink_events),
	.events = app_window_alarm_drink_events,
};






