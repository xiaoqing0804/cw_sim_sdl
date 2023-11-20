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

#include "app_window_call_clog_layout.h"
#include "app_window_call_clog_ui.h"
#include "app_window_call_clog.h"



/*-----------------------------主流程--------------------------------------*/
static void app_window_call_clog_init(void *buf)
{
}

static void app_window_call_clog_load(void *buf)
{
	gui_surface_struct* surface = gui_surface_get_surface(&app_call_clog_screen);
	gui_surface_layout_listview_dynamic_create(surface,app_window_call_clog_refresh);

	application_titlebar_create(&app_call_clog_screen, STRING_ID_CALLLOG);
}

static void app_window_call_clog_entry(void *buf)
{
}

static void app_window_call_clog_exit()
{
}

static void app_window_call_clog_destroy(void)
{
}

/*-----------------------------响应事件--------------------------------------*/

static void app_window_call_clog_item_click(gui_click_layout_struct *event)
{
	app_window_call_clog_item_click_function(event->id);
}

static void app_window_clog_view_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&app_call_clog_screen);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_DOWN);

	}else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_UP);
	}
	gui_surface_commit();
}

/*-----------------------------系统配置--------------------------------------*/

static const app_window_event_struct app_window_call_clog_events[] =
{
    {.id = EVENT_ROLKEY,    .handler = app_window_clog_view_rolkey_handler  },
};

const gui_window_struct app_window_call_clog =
{
	.screen = &app_call_clog_screen,
	.init = app_window_call_clog_init,
	.load = app_window_call_clog_load,
	.entry = app_window_call_clog_entry,
	.exit = app_window_call_clog_exit,
	.destroy = app_window_call_clog_destroy,
	.click_on_layout_item = app_window_call_clog_item_click,
	.event_num = countof(app_window_call_clog_events),
	.events = app_window_call_clog_events,
};
#endif


