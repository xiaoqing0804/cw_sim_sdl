
#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "data_manager_message.h"

#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "app_window_moreinfo.h"
#include "app_window_moreinfo_ring.h"
#include "app_window_moreinfo_ring_layout.h"
#include "application_config_app_info.h"
#include "gui_surface_layout_ring.h"


/*-----------------------------ϵͳʂ¼þ--------------------------------------*/
static void app_window_more_info_ring_update_item(unsigned short app_id)
{
    gui_box_struct*     box;
    app_info_struct* app_info = get_app_info_by_id((APP_INFO_ID)app_id);
    if (app_info != NULL) {
        box = gui_surface_get_box(&gui_screen_moreinfo_ring,RING_LAYOUT_ID_TEXT);
        if (box != NULL)    gui_surface_box_label_change_string_id(box,app_info->name);
    }
}


static void app_window_more_info_ring_init(void *buf)
{
}

static void app_window_more_info_ring_load()
{
}

static void app_window_more_info_ring_entry()
{
	SYS_DEBUG("app_window_more_info_ring_entry");
    gui_box_struct*     box;

	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_moreinfo_ring);
    if (surface != NULL) {
        box     = gui_surface_layout_ring_get_current_item(surface);
        if (box != NULL) {
            app_window_more_info_ring_update_item(box->id);
        }
    }
}

static void app_window_more_info_ring_exit()
{
}

static void app_window_more_info_ring_destroy()
{
}

static void app_window_more_info_ring_touch_item(gui_click_layout_struct *event)
{
    app_info_struct* app_info = get_app_info_by_id((APP_INFO_ID)event->id);
    //SYS_DEBUG("app: more_info_ring_touch_item(idx: %d, id: %d)", event->index, event->id);
    if (app_info != NULL) {
        entry_app_by_info(app_info);
    }
}

static void app_window_more_info_ring_value_changed(gui_layout_value_struct* event)
{
    //SYS_DEBUG("app: more_info_ring_value_changed(idx: %d, id: %d)", event->ring.index, event->ring.id);
    app_window_more_info_ring_update_item(event->ring.id);
}

static void app_window_ring_rolkey_handler(void* buf)
{
    if (buf == NULL) return;

    rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
    gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_moreinfo_ring);
    if (surface != NULL) {
        if (rolkey->rotate == ROTATE_TYPE_BACKWARD) {
            gui_surface_layout_ring_switch_to_item(surface, 1);
        }
        else if(rolkey->rotate == ROTATE_TYPE_FORWARD){
            gui_surface_layout_ring_switch_to_item(surface, -1);
        }
        gui_surface_commit();
    }
}


static void app_window_moreinfo_ring_key1_handler(void* buf)
{
    app_window_moreinfo_change();
}

static void app_window_moreinfo_ring_click_handler(void* buf)
{
	SYS_DEBUG("app_window_moreinfo_ring_click_handler");
    gui_box_struct*     box;

	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_moreinfo_ring);
    if (surface != NULL) {
        box     = gui_surface_layout_ring_get_current_item(surface);
        if (box != NULL) {
            app_info_struct* app_info = get_app_info_by_id((APP_INFO_ID)box->id);
            if (app_info != NULL) {
                entry_app_by_info(app_info);
            }
        }
    }
}

/*-----------------------------Ťփ--------------------------------------*/
static const app_window_event_struct app_window_moreinfo_ring_events[] =
{
	 {
		#if GUI_SINGLE_KEY_SUPPORT
            .id = EVENT_KEY1_DOUBLE,
		#else
            .id = EVENT_KEY2_DOUBLE,
		#endif		
        .handler = app_window_moreinfo_ring_key1_handler,
    },
    {
        .id = EVENT_ROLKEY,
        .handler = app_window_ring_rolkey_handler,
    },
};

static const gui_touch_event_struct app_window_moreinfo_ring_touch_events[] =
{
    {.id = RING_LAYOUT_ID_TEXT, .click = app_window_moreinfo_ring_click_handler}
};



const gui_window_struct app_window_moreinfo_ring =
{
	.screen = &gui_screen_moreinfo_ring,

	.click_on_layout_item = app_window_more_info_ring_touch_item,
	.layout_value_changed = app_window_more_info_ring_value_changed,

	.init = app_window_more_info_ring_init,
	.load = app_window_more_info_ring_load,
	.entry = app_window_more_info_ring_entry,
	.exit = app_window_more_info_ring_exit,
	.destroy = app_window_more_info_ring_destroy,

	.event_num = countof(app_window_moreinfo_ring_events),
	.events = app_window_moreinfo_ring_events,

    .touch_event_num = countof(app_window_moreinfo_ring_touch_events),
    .touch_events = app_window_moreinfo_ring_touch_events,
};





