#include "picture.h"
#include "language.h"
#include "bsp_includes.h"

#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "app_window_shutdown.h"
#include "app_window_goodbye.h"


static const gui_font_struct gui_shutdown_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SHUTDOWN_HINT,
};

static const gui_image_struct gui_cancel_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_operator2_cancel_info,
};

// static const gui_image_struct gui_cancel_bg_image =
// {
// 	.type = TYPE_GUI_DRAW_PICTURE,
// 	.data = &pic_operator2_stop_bg_info,
// };

static const gui_image_struct gui_ok_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_operator2_ok_info,
};

// static const gui_image_struct gui_ok_bg_image =
// {
// 	.type = TYPE_GUI_DRAW_PICTURE,
// 	.data = &pic_operator2_start_bg_info,
// };

static const gui_widget_struct gui_shutdown_widget[] =
{
	{
		.id = 1,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 153,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT*3/4,
		.visible= 1,
        .child_num = 1,
        .children = &gui_shutdown_text,
	},


    {
        .id = 3,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 270,
        .y = 306,  // pic_operator2_ok_info.height,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_ok_image,
    },

    {
        .id = 2,
        .type = TYPE_GUI_CONTROL_IMAGE,
		.x = 91,
        .y = 306,  // pic_operator2_cancel_info.height,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_cancel_image,
    },

};

static const gui_screen_struct gui_shutdown_screen =
{
	.children = gui_shutdown_widget,
	.child_num = countof(gui_shutdown_widget),
};



/*-----------------------------系统事件--------------------------------------*/
static void app_window_shutdown_init(void *buf)
{

}

static void app_window_shutdown_load(void *buf)
{
}


static void app_window_shutdown_entry(void *buf)
{
}


static void app_window_shutdown_exit()
{

}

static void app_window_shutdown_destroy()
{
}

static void app_window_shutdown_touch_event_click_cancel(gui_click_struct *event)
{
	application_go_back();
}

static void app_window_shutdown_touch_event_click_ok(gui_click_struct *event)
{
	// bye
    g_goodbye_type = GOODBYE_SHUTDOWN;
	ext_btaud_onoff_set(0);
    application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_goodbye, NULL);
}

static void app_window_shutdown_actimer_handler(void* buf)
{
    //app_window_shutdown_touch_event_click_ok(NULL);
}

static void app_window_shutdown_key1_short(void* buf)
{
    application_go_back();
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_shutdown_static_events[] =
{
	{
		.id = EVENT_ACT,
		.handler = app_window_shutdown_actimer_handler,
	},

    {
		.id = EVENT_KEY1_SHORT,
		.handler = app_window_shutdown_key1_short,
	},
};

static const gui_touch_event_struct app_window_shutdown_touch_events[] =
{
	{
		.id = 2,
		.click = app_window_shutdown_touch_event_click_cancel,
		.offset_left = 25,
		.offset_top= 25,
	},

    {
        .id = 3,
        .click = app_window_shutdown_touch_event_click_ok,
        .offset_left = 25,
		.offset_top= 25,
    },
};


const gui_window_struct app_window_shutdown =
{
	.screen = &gui_shutdown_screen,
	.config = NULL,

	.init = app_window_shutdown_init,
	.load = app_window_shutdown_load,
	.entry = app_window_shutdown_entry,
	.exit = app_window_shutdown_exit,
	.destroy = app_window_shutdown_destroy,

	.touch_event_num = countof(app_window_shutdown_touch_events),
	.touch_events = app_window_shutdown_touch_events,

    .event_num = countof(app_window_shutdown_static_events),
    .events = app_window_shutdown_static_events,
};






