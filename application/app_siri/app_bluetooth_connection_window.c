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

#include "app_bluetooth_connection_window.h"

#include "application_titlebar.h"



static const gui_image_struct gui_link_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_link_no_info,
};


// str
static const gui_font_struct gui_bluetooth_connection_name_txt =   //
{
	.type = TYPE_GUI_DRAW_TEXT,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_SMALL,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_BLUETOOTH_CONNECTION,
};

// widget ----------------------------------------------------------------------------
enum{
    app_bluetooth_connection_bg_ID = 100,
    app_bluetooth_connection_name_tip_ID,
    app_bluetooth_connection_time_tip_ID,
    app_bluetooth_connection_txt_ID,

};
static const gui_widget_struct app_bluetooth_connection_widget[] =
{
	{
		.id = app_bluetooth_connection_bg_ID,
		.y = 150,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.width = LCD_SIZE_WIDTH,
		.height = 80,
		.visible= 1,
		.child_num = 1,
		.children = &gui_link_image,
	},

    {   // string
        .id = app_bluetooth_connection_txt_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = 270,
        .width = LCD_SIZE_WIDTH,
        .height = 24,
        .visible= 1,
        .child_num = 1,
        .children = &gui_bluetooth_connection_name_txt,
    },
};

static const gui_screen_struct app_bluetooth_connection_screen =
{
	.order = 0,
	.children = app_bluetooth_connection_widget,
	.child_num = countof(app_bluetooth_connection_widget),
};


/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_bluetooth_connection_init(void *buf)
{

}

static void app_bluetooth_connection_load(void *buf)
{
	SYS_DEBUG("siri_btaud_load");
    gui_box_struct* box;
	box = gui_surface_get_box(&app_bluetooth_connection_screen, app_bluetooth_connection_bg_ID);
	if(ext_btaud_onoff_get() > 0){
		if(ext_btaud_status_get()->dev_status  > 0){
			gui_surface_box_image_change(box,(const picture_info_struct*)&pic_link_yes_info);
		}
		else
		{
			gui_surface_box_image_change(box,(const picture_info_struct*)&pic_link_ing_info);
		}
    }
	else
	{
		gui_surface_box_image_change(box,(const picture_info_struct*)&pic_link_no_info);
	}
//    application_titlebar_create_by_name(&app_bluetooth_connection_screen, "Connect");
}


static void app_bluetooth_connection_entry(void *buf)
{
}


static void app_bluetooth_connection_exit()
{

}

static void app_bluetooth_connection_destroy()
{

}

static void app_bluetooth_connection_handler(void* buf)
{
    app_bluetooth_connection_load(buf);
}


static void app_bluetooth_connection_suspend(void* buf)
{
    SYS_DEBUG("app: main 2 suspend");
}

static void app_bluetooth_connection_resume(void* buf)
{
    SYS_DEBUG("app: main 2 resume");
    app_bluetooth_connection_load(NULL);
}
static void app_bluetooth_connection_btaud_status_handler(void* buf)
{
	SYS_DEBUG("btaud link yes");
	if(ext_btaud_status_get()->dev_status  > 0){
		gui_box_struct* link = gui_surface_get_box(&app_bluetooth_connection_screen, app_bluetooth_connection_bg_ID);
		gui_surface_box_image_change(link,(const picture_info_struct*)&pic_link_yes_info);
		gui_surface_commit();
	}
}


/*-----------------------------����--------------------------------------*/


static void app_bluetooth_connection_touch_handler(gui_click_struct *event)
{
    //SYS_DEBUG("gui: app_siri_touch, type=%d, dir=%d", event->type, event->direction);
    gui_box_struct* link = gui_surface_get_box(&app_bluetooth_connection_screen, app_bluetooth_connection_bg_ID);
#if defined(__EXT_BT_AUDIO__)
    if(ext_btaud_onoff_get() > 0){
        return;
    }
    else{
        ext_btaud_onoff_set(1);
        gui_surface_box_image_change(link,(const picture_info_struct*)&pic_link_ing_info);
    }
    gui_surface_commit();
#endif
}

static const gui_touch_event_struct app_bluetooth_connection_touch_events =
{
    .id = app_bluetooth_connection_bg_ID,   // fullscreen.
    .click = app_bluetooth_connection_touch_handler,
};

static const app_window_event_struct app_bluetooth_connection_static_events[] =
{
    {
        .id = EVENT_GUI_SUSPENDED,
        .handler = app_bluetooth_connection_suspend,
    },
    {
        .id = EVENT_GUI_RESUMED,
        .handler = app_bluetooth_connection_resume,
    },
	{
		.id = EVENT_BTAUD_STATUS,
		.handler = 	app_bluetooth_connection_btaud_status_handler,
	},
};

const gui_window_struct app_bluetooth_connection_window =
{
	.screen = &app_bluetooth_connection_screen,

	.init = app_bluetooth_connection_init,
	.load = app_bluetooth_connection_load,
	.entry = app_bluetooth_connection_entry,
	.exit = app_bluetooth_connection_exit,
	.destroy = app_bluetooth_connection_destroy,

    .touch_event_num = 1,
    .touch_events = &app_bluetooth_connection_touch_events,

	.event_num = countof(app_bluetooth_connection_static_events),
	.events = app_bluetooth_connection_static_events,
};

