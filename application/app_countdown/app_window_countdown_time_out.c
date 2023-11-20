#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager.h"
#include "data_manager_flash.h"
#include "watchface.h"
#include "arithmetic_common.h"
#include "arithmetic_sleep.h"

#include "application_config_app_info.h"

#include "system_util_math_geometry.h"
#include "font_convert.h"
#include "gui_surface_cache.h"
#include "gui_surface_box_pointer.h"
#include "gui_drivers_display.h"
#include "gui_surface_control_base.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_node.h"

#include "bsp_motor/motor.h"

#include "app_window_countdown_time_out.h"
#include "app_window_countdown_time_out_layout.h"

/*-----------------------------主流程--------------------------------------*/
static void app_window_main_time_out_init(void *buf)
{
    send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
}

static void app_window_main_time_out_load(void *buf)
{

}


static void app_window_main_time_out_entry(void *buf)
{
    SYS_DEBUG("app_window_main_time_out_entry()");
	application_open_act_timer(APPLICATION_TIMER_ACT, 2000);
}


static void app_window_main_time_out_exit()
{
    SYS_DEBUG("app_window_main_time_out_exit()");
}

static void app_window_main_time_out_destroy()
{
}
/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_main_time_out_timer_handler(void* buf)
{
    if (APPLICATION_TIMER_ACT == *((unsigned int*)buf)) {
        application_go_back();
    }
}

/*-----------------------------系统配置--------------------------------------*/
static const app_window_event_struct app_window_main_time_out_static_events[] =
{
    {
    .id = EVENT_ACT,
    .handler = app_window_main_time_out_timer_handler,
    },
};


const gui_window_struct app_window_main_time_out =
{
	.screen = &gui_main_time_out_screen,

	.init = app_window_main_time_out_init,
	.load = app_window_main_time_out_load,
	.entry = app_window_main_time_out_entry,
	.exit = app_window_main_time_out_exit,
	.destroy = app_window_main_time_out_destroy,

	.event_num = countof(app_window_main_time_out_static_events),
	.events = app_window_main_time_out_static_events,
};




