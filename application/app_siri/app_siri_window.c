#include "debug_info.h"
#include "bsp_includes.h"

#include "picture.h"
#include "language.h"
#include "app_task_main.h"

#include "arithmetic_sleep.h"
#include "data_common.h"

#include "system_util_math_geometry.h"

#include "gui_window.h"
#include "gui_surface_box.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_animation.h"

#include "app_siri_window.h"
#include "app_bluetooth_connection_window.h"

#include "application_titlebar.h"

#include "app_widget/app_window_widget_delete.h"


static const gui_image_struct gui_siri_bg_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .x = 0,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .data = &pic_siri_bg_info,
};

// widget ----------------------------------------------------------------------------
enum{
    APP_SIRI_BG_ID = 100,

};
static const gui_widget_struct app_siri_widget[] =
{
    {
        .id = APP_SIRI_BG_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_siri_bg_image,
    },

};

static const gui_screen_struct app_siri_screen =
{
	.order = 0,
	.children = app_siri_widget,
	.child_num = countof(app_siri_widget),
};


/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_siri_init(void *buf)
{
    ext_btaud_onoff_set(1);
}

static void app_siri_load(void *buf)
{
//    application_titlebar_create_by_name(&app_siri_screen, "Siri");
}


static void app_siri_entry(void *buf)
{
//    if (!gui_display_isSuspended()) {
//        gui_surface_control_animation_start(&app_siri_screen, APP_SIRI_BGANI_ID);
//    }
}


static void app_siri_exit()
{

}

static void app_siri_destroy()
{

}

static void app_siri_handler(void* buf)
{
    app_siri_load(buf);
}


static void app_siri_suspend(void* buf)
{
    SYS_DEBUG("app: main 2 suspend");
//    gui_surface_control_animation_stop(&app_siri_screen, APP_SIRI_BGANI_ID);
}

static void app_siri_resume(void* buf)
{
    SYS_DEBUG("app: main 2 resume");
    app_siri_load(NULL);
//    gui_surface_control_animation_start(&app_siri_screen, APP_SIRI_BGANI_ID);
}


/*-----------------------------����--------------------------------------*/


static void app_siri_touch_handler(gui_click_struct *envent)
{
//    SYS_DEBUG("gui: app_siri_touch, type=%d, dir=%d", event->type, event->direction);
	if((ext_btaud_status_get()->dev_status > 0)&&(get_ble_connect_flag() > 0)){
			ext_btaud_send_cmd(AU_CMD_SIRI_ON,NULL,0);//.... wake up siri
	}
	else{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH,&app_bluetooth_connection_window, NULL);
	}

}

static const gui_touch_event_struct app_siri_touch_events[] =
{
    {
        .id = APP_SIRI_BG_ID,   // fullscreen.
        .click = app_siri_touch_handler,
    }
};

static const app_window_event_struct app_siri_static_events[] =
{
    {
        .id = EVENT_GUI_SUSPENDED,
        .handler = app_siri_suspend,
    },
    {
        .id = EVENT_GUI_RESUMED,
        .handler = app_siri_resume,
    },
	{
        .id = EVENT_BL_TIMEOUT,
    },

};

const gui_window_struct app_siri_window =
{
	.screen = &app_siri_screen,

	.init = app_siri_init,
	.load = app_siri_load,
	.entry = app_siri_entry,
	.exit = app_siri_exit,
	.destroy = app_siri_destroy,

    .touch_event_num = countof(app_siri_touch_events),
    .touch_events = app_siri_touch_events,

	.event_num = countof(app_siri_static_events),
	.events = app_siri_static_events,
};

