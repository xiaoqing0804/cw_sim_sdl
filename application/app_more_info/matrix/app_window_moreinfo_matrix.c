#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "debug_info.h"
#include "application_config_app_info.h"

#include "gui_window.h"
#include "app_more_info/app_window_moreinfo.h"
#include "app_window_moreinfo_matrix.h"
#include "app_window_moreinfo_matrix_layout.h"

#include "gui_core_touch.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"
#include "gui_surface_layout_matrix.h"

/*------------------------------------------------------------------*/

static void app_window_matrix_init(void *buf)
{
}

static void app_window_matrix_load(void *buf)
{
}

static void app_window_matrix_entry(void *buf)
{
}

static void app_window_matrix_exit()
{
}

static void app_window_matrix_destroy()
{
}

static void app_window_matrix_touch_item(gui_click_layout_struct *event)
{
    entry_app_by_id((APP_INFO_ID)event->id);
}

/*------------------------------------------------------------------*/
static void app_window_matrix_key2_double_handler(void *buf)
{
    app_window_moreinfo_change();
}

static void app_window_matrix_key_short_handler(void *buf)
{
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_matrix);
    gui_surface_layout_matrix_entry_home_app(surface);
}

static void app_window_matrix_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_matrix);

    if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
    {
        gui_surface_layout_matrix_switch_to_item(surface, DIRECTION_TYPE_DOWN);
    }
    else if (rolkey->rotate == ROTATE_TYPE_FORWARD)
    {
        gui_surface_layout_matrix_switch_to_item(surface, DIRECTION_TYPE_UP);
    }
    gui_surface_commit();
}

static void app_window_matrix_event_handler(void *buf)
{
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_matrix);
    gui_surface_layout_matrix_entry_app(surface);
}

/*------------------------------------------------------------------*/

static const app_window_event_struct app_window_matrix_events[] =
    {
        {
		#if GUI_SINGLE_KEY_SUPPORT
            .id = EVENT_KEY1_DOUBLE,
		#else
            .id = EVENT_KEY2_DOUBLE,
		#endif		
            .handler = app_window_matrix_key2_double_handler,
        },
        {
            .id = EVENT_GUI_EVENT_IND,
            .handler = app_window_matrix_event_handler,
        },
        {
            .id = EVENT_ROLKEY,
            .handler = app_window_matrix_rolkey_handler,
        },
};

static const gui_window_config_struct app_window_matrix_config =
    {
        .disable_scale = 1,
};

const gui_window_struct app_window_moreinfo_matrix =
    {
        .screen = &gui_screen_matrix,
        .config = &app_window_matrix_config,

        .click_on_layout_item = app_window_matrix_touch_item,

        .init = app_window_matrix_init,
        .load = app_window_matrix_load,
        .entry = app_window_matrix_entry,
        .exit = app_window_matrix_exit,
        .destroy = app_window_matrix_destroy,

        .event_num = countof(app_window_matrix_events),
        .events = app_window_matrix_events,
};
