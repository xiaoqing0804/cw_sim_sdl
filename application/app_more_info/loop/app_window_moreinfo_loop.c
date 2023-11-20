
#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "debug_info.h"
#include "application_config_app_info.h"

#include "gui_window.h"
//#include "app_window_moreinfo.h"
#include "app_window_moreinfo_loop.h"
#include "app_window_moreinfo_loop_layout.h"

#include "gui_core_touch.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"
#include "gui_surface_layout_loop.h"

#include "application_config_app_info.h"

/*-----------------------------系统事件--------------------------------------*/
static void app_window_loop_init(void *buf)
{
}

static void app_window_loop_load(void *buf)
{
}

static void app_window_loop_entry(void *buf)
{
}

static void app_window_loop_exit()
{
}

static void app_window_loop_destroy()
{
}

static void app_window_loop_touch_item(gui_click_layout_struct *event)
{
	app_info_struct* app_info = get_app_info_by_id((APP_INFO_ID)event->id);
    SYS_DEBUG("app: loop_touch_item(id: %d, idx; %d)", event->id, event->index);
    if (app_info != NULL) {
        entry_app_by_info(app_info);
    }
}

/*-----------------------------配置--------------------------------------*/
static void app_window_moreinfo_loop_key1_handler(void* buf)
{
	app_window_moreinfo_change();
}

static void app_window_moreinfo_loop_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_loop);
	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_loop_switch_to_item(surface,DIRECTION_TYPE_DOWN);

	}
    else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_loop_switch_to_item(surface,DIRECTION_TYPE_UP);
	}
	gui_surface_commit();
}


static const app_window_event_struct app_window_moreinfo_loop_events[] =
{
    {
		#if GUI_SINGLE_KEY_SUPPORT
            .id = EVENT_KEY1_DOUBLE,
		#else
            .id = EVENT_KEY2_DOUBLE,
		#endif		
        .handler = app_window_moreinfo_loop_key1_handler,
    },
    {
        .id = EVENT_ROLKEY,
        .handler = app_window_moreinfo_loop_rolkey_handler,
    },

};

static const gui_window_config_struct app_window_loop_config =
{
	.disable_scale = 1,
};

const gui_window_struct app_window_moreinfo_loop =
{
	.screen = &gui_screen_loop,
	.config = &app_window_loop_config,

	.click_on_layout_item = app_window_loop_touch_item,

	.init = app_window_loop_init,
	.load = app_window_loop_load,
	.entry = app_window_loop_entry,
	.exit = app_window_loop_exit,
	.destroy = app_window_loop_destroy,

	.event_num = countof(app_window_moreinfo_loop_events),
	.events = app_window_moreinfo_loop_events,
};


