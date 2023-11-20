#include "app_window_sleep.h"
#include "app_window_sleep_layout.h"
#include "app_window_sleep_ui.h"

#include "picture.h"
#include "language.h"
#include "debug_info.h"

#include "app_task_main.h"
#include "arithmetic_sleep.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "application_titlebar.h"



#include "app_widget/app_window_widget_delete.h"

/*-----------------------------����--------------------------------------*/
static void app_window_sleep_long_touch_handler(gui_click_struct *event)
{
   if (is_exist_widget_app(APP_INFO_ID_SLEEP)) {
       application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void*)APP_INFO_ID_SLEEP);
   }
   app_window_sleep_ui_show();
}

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_sleep_box_visible(unsigned char flag)
{
   
}

static void app_no_sleep_data_box_visible(unsigned char flag)
{
   
}

static void app_window_sleep_init(void *buf)
{
	
}

static void app_window_sleep_load(void *buf)
{
	app_window_sleep_ui_show();
}


static void app_window_sleep_entry(void *buf)
{
    gui_surface_control_animation_start(&gui_screen_sleep, SLEEP_LAYOUT_ID_BG1);

}


static void app_window_sleep_exit()
{
    gui_surface_control_animation_start(&gui_screen_sleep, SLEEP_LAYOUT_ID_BG1);

}

static void app_window_sleep_destroy()
{

}




/*----------------------------------------------------------------------------*/

static const gui_touch_event_struct app_window_sleep_touch_events =
{
   .id = 0xFFFF,  // fullscreen.
   .long_touch = app_window_sleep_long_touch_handler,
};


static const app_window_event_struct app_window_sleep_static_events[] =
{

};


const gui_window_struct app_window_sleep =
{
	.screen = &gui_screen_sleep,

	.init = app_window_sleep_init,
	.load = app_window_sleep_load,
	.entry = app_window_sleep_entry,
	.exit = app_window_sleep_exit,
	.destroy = app_window_sleep_destroy,

   .touch_event_num = 1,
   .touch_events = &app_window_sleep_touch_events,

	.event_num = countof(app_window_sleep_static_events),
	.events = app_window_sleep_static_events,
};


