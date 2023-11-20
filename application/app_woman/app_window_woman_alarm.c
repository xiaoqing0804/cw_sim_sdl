#include "app_window_woman_alarm.h"
#include "app_window_woman_alarm_ui.h"
#include "app_window_woman_alarm_layout.h"

#include "data_common.h"
#include "gui_surface.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_layout_pageview.h"
#include "gui_surface_box_layout_item.h"
#include "bsp_motor/motor.h"

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_woman_alarm_timer_hander(void *buf)
{
	application_go_back();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_woman_alarm_init(void *buf)
{
}

static void app_window_woman_alarm_load(void *buf)
{
	switch (g_woman_stage)
	{
	case WOMAN_ALARM_YUEJIN_START:
		app_window_woman_alarm_ui_show_yuejin(&g_woman_data);
		break;

	case WOMAN_ALARM_PAILUAN_START:
		app_window_woman_alarm_ui_show_pailuan_start(&g_woman_data);
		break;

	case WOMAN_ALARM_PAILUAN_DAY:
		app_window_woman_alarm_ui_show_pailuan(&g_woman_data);
		break;

	case WOMAN_ALARM_PAILUAN_END:
		app_window_woman_alarm_ui_show_pailuan_end(&g_woman_data);
		break;
	}
}

static void app_window_woman_alarm_entry(void *buf)
{
	send_motor_msg(MOTOR_MSG_REMIND);
	application_open_act_timer(APPLICATION_TIMER_ACT, 5000);
}

static void app_window_woman_alarm_exit()
{
}

static void app_window_woman_alarm_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/
static const gui_touch_event_struct app_window_woman_alarm_touch_events[] =
	{

};

static const app_window_event_struct app_window_woman_alarm_static_events[] =
	{
		{
			.id = EVENT_ACT,
			.handler = app_window_woman_alarm_timer_hander,
		},
};

const gui_window_struct app_window_woman_alarm =
	{
		.screen = &gui_screen_woman_alarm,
		.init = app_window_woman_alarm_init,
		.load = app_window_woman_alarm_load,
		.entry = app_window_woman_alarm_entry,
		.exit = app_window_woman_alarm_exit,
		.destroy = app_window_woman_alarm_destroy,

		.touch_event_num = countof(app_window_woman_alarm_touch_events),
		.touch_events = app_window_woman_alarm_touch_events,

		.event_num = countof(app_window_woman_alarm_static_events),
		.events = app_window_woman_alarm_static_events,
};
