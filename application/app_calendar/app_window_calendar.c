#include "app_window_calendar.h"
#include "app_window_calendar_layout.h"
#include "app_window_calendar_ui.h"

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

#include "app_window_calendar.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_date.h"
#include "gui_surface_control_time.h"

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_calendar_update_handler(void)
{
	app_window_caledar_ui_show();
	gui_surface_commit();
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_calendar_init(void *buf)
{
}

static void app_window_calendar_load(void *buf)
{
	app_window_caledar_ui_show();
}

static void app_window_calendar_entry(void *buf)
{
}

static void app_window_calendar_exit()
{
}

static void app_window_calendar_destroy(void)
{
}

/*-----------------------------配置--------------------------------------*/

static const app_window_event_struct app_window_calendar_events[] =
	{
		{
			.id = EVENT_UPDATE_SYS_TIME,
			.handler = app_window_calendar_update_handler,
		},
};

const gui_window_struct app_window_calendar =
	{
		.screen = &app_calendar_screen,

		.init = app_window_calendar_init,
		.load = app_window_calendar_load,
		.entry = app_window_calendar_entry,
		.exit = app_window_calendar_exit,
		.destroy = app_window_calendar_destroy,

		.event_num = countof(app_window_calendar_events),
		.events = app_window_calendar_events,
};
