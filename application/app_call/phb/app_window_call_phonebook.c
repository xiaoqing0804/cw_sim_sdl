#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "data_manager_message.h"

#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#include "data_manager_contact.h"

#include "srv_call.h"

#include "gui_drivers_display.h"
#include "gui_surface.h"
#include "gui_surface_cache.h"
#include "gui_surface_layout.h"
#include "gui_surface_box_layout_item.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_base.h"
#include "gui_surface_layout_listview.h"

#include "application_config_main_window.h"
#include "application_titlebar.h"

#include "app_call/app_window_call.h"
#include "app_window_call_phonebook_layout.h"
#include "app_window_call_phonebook_ui.h"
#include "app_window_call_phonebook.h"

/*-----------------------------主流程--------------------------------------*/

static void app_window_call_phb_init(void *buf)
{
}

static void app_window_call_phb_load(void *buf)
{
	gui_surface_struct *surface = gui_surface_get_surface(&app_call_phb_screen);
	gui_surface_layout_listview_dynamic_create(surface, app_window_call_phone_book_refrsh);

	application_titlebar_create(&app_call_phb_screen, STRING_CONTACT);
}

static void app_window_call_phb_entry(void *buf)
{
}

static void app_window_call_phb_exit()
{
	SYS_DEBUG("call_exit");
}

static void app_window_call_phb_destroy(void)
{
}

/*-----------------------------响应事件--------------------------------------*/
static void app_window_call_phb_item_click(gui_click_layout_struct *event)
{
	app_window_call_phb_item_click_function(event->id);
}

static void app_window_call_phb_timer_handler(void *buf)
{
	unsigned int timer_index = *((unsigned int *)buf);
	time_struct time;
	unsigned char time_buf[20] = {0};

	if (APPLICATION_TIMER_ACT == timer_index)
	{
		application_close_act_timer(APPLICATION_TIMER_ACT);
	}
}

static void app_window_phonebook_view_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&app_call_phb_screen);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface, DIRECTION_TYPE_DOWN);
	}
	else if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface, DIRECTION_TYPE_UP);
	}

	gui_surface_commit();
}

/*-----------------------------系统配置--------------------------------------*/
static const app_window_event_struct app_window_call_phb_events[] =
	{
		{
			.id = EVENT_ACT,
			.handler = app_window_call_phb_timer_handler,
		},

		{
			.id = EVENT_ROLKEY,
			.handler = app_window_phonebook_view_rolkey_handler,
		},
		{.id = EVENT_UPDATE_CONTACT, .handler = app_window_call_phb_load}, // APP上删除电话本时，实时刷新列表
};

const gui_window_struct app_window_call_phonebook =
	{
		.screen = &app_call_phb_screen,

		.init = app_window_call_phb_init,
		.load = app_window_call_phb_load,
		.entry = app_window_call_phb_entry,
		.exit = app_window_call_phb_exit,
		.destroy = app_window_call_phb_destroy,

		.click_on_layout_item = app_window_call_phb_item_click,

		.event_num = countof(app_window_call_phb_events),
		.events = app_window_call_phb_events,
};

#endif
