
#include "picture.h"
#include "language.h"

#include "app_task_main.h"
#include "data_common.h"
#include "data_manager.h"
#include "data_manager_flash.h"
#include "watchface.h"
#include "arithmetic_common.h"
#include "arithmetic_sleep.h"

#include "font_convert.h"
#include "gui_surface_cache.h"
#include "gui_surface_box_pointer.h"
#include "gui_drivers_display.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_animation.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_node.h"


#define IDLE_POINT_DRAW_LINE        1

static short g_idle_pointer_hour_pos[4];
static short g_idle_pointer_min_pos[4];

// text ----------------------------------------------------------------------------
/*
static const gui_font_struct gui_idle_watch_time_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_45,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00:00",
};*/


// pointer ----------------------------------------------------------------------------
static const gui_pointer_struct gui_idle_watch_pointer_hour =
{
    .type = TYPE_GUI_DRAW_POINTER_LINE_60,
    .center_x = LCD_SIZE_WIDTH/2,
    .center_y = LCD_SIZE_HEIGHT/2,
    .hand_lenth = LCD_SIZE_WIDTH*75/200,
    .hilt_lenth = 10,
    .hand_width = 8,
    .shape.line.color = COLOR_RGB(255, 255, 255),
    .shape.line.position = g_idle_pointer_hour_pos,
};

static const gui_pointer_struct gui_idle_watch_pointer_minute =
{
    .type = TYPE_GUI_DRAW_POINTER_LINE_60,
    .center_x = LCD_SIZE_WIDTH/2,
    .center_y = LCD_SIZE_HEIGHT/2,
    .hand_lenth = LCD_SIZE_WIDTH*90/200,
    .hilt_lenth = 20,
    .hand_width = 5,
    .shape.line.color = COLOR_RGB(255, 255, 255),
    .shape.line.position = g_idle_pointer_min_pos,
};

// widget ----------------------------------------------------------------------------
enum{
    IDLE_WATCH_NUMBER_BASE_ID = 50,
    IDLE_WATCH_NUMBER_TIME_ID,

    IDLE_WATCH_POINT_BASE_ID = 100,
    IDLE_WATCH_POINT_HOUR_ID,
    IDLE_WATCH_POINT_MIN_ID,
};

static const gui_widget_struct gui_idle_watch_widget[] =
{
    // time text
	/*{
		.id = IDLE_WATCH_NUMBER_TIME_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 0,
        .child_num = 1,
        .children = &gui_idle_watch_time_text,
	},*/

    // point
    {
        .id = IDLE_WATCH_POINT_HOUR_ID,
        .type = TYPE_GUI_CONTROL_POINTER,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_idle_watch_pointer_hour,
    },

    {
        .id = IDLE_WATCH_POINT_MIN_ID,
        .type = TYPE_GUI_CONTROL_POINTER,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_idle_watch_pointer_minute,
    },
};

static const gui_screen_struct gui_dft_idle_watch_screen =
{
	.order = 0,
	.children = gui_idle_watch_widget,
	.child_num = countof(gui_idle_watch_widget),
};


/*-----------------------------系统事件--------------------------------------*/

static void app_window_idle_watch_init(void *buf)
{
}

static void app_window_idle_watch_load(void *buf)
{
    gui_surface_struct* surface = gui_surface_get_surface(&gui_dft_idle_watch_screen);
    gui_box_struct* box;
    time_struct time;
    char buff[8];

    sys_time_get(&time);
    SYS_DEBUG("gui: idle_watch_load, h=%d, m=%d\n", time.hour, time.min);

    box = gui_surface_get_box(&gui_dft_idle_watch_screen, IDLE_WATCH_NUMBER_TIME_ID);
    if (box != NULL) {
        sprintf(buff, "%02d:%02d", time.hour,time.min);
        gui_surface_box_label_change_string(box, (unsigned char*)buff);
        box->visible = !IDLE_POINT_DRAW_LINE;
    }

    box = gui_surface_get_box(&gui_dft_idle_watch_screen, IDLE_WATCH_POINT_HOUR_ID);
    if (box != NULL) {
        unsigned int angle_hour = (time.hour % 12)*5 + time.min/12;
        gui_surface_box_pointer_change(box, angle_hour);  // hour
        box->visible = IDLE_POINT_DRAW_LINE;
    }

    box = gui_surface_get_box(&gui_dft_idle_watch_screen, IDLE_WATCH_POINT_MIN_ID);
    if (box != NULL) {
        unsigned int angle_min  = time.min;
        gui_surface_box_pointer_change(box, angle_min);  // minute
        box->visible = IDLE_POINT_DRAW_LINE;
    }
}


static void app_window_idle_watch_entry(void *buf)
{
    SYS_DEBUG("app_window_idle_watch_entry()");
}


static void app_window_idle_watch_exit()
{
    SYS_DEBUG("app_window_idle_watch_exit()");
}

static void app_window_idle_watch_destroy()
{
}

static void app_window_idle_watch_minute_ind_handler(void* buf)
{
    SYS_DEBUG("app_window_idle_watch_minute_ind_handler()");
    app_window_idle_watch_load(buf);
    gui_surface_commit();
}


/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_idle_watch_static_events[] =
{
	{.id = EVENT_RTC_MINUTE_IND, .handler = app_window_idle_watch_minute_ind_handler},

    {.id = EVENT_GO_HOME},
};


static const gui_window_config_struct app_window_idle_watch_config =
{
	.forbid_gesture_back = 1,
};

const gui_window_struct app_window_default_idle =
{
	.screen = &gui_dft_idle_watch_screen,
	.config = &app_window_idle_watch_config,

	.init = app_window_idle_watch_init,
	.load = app_window_idle_watch_load,
	.entry = app_window_idle_watch_entry,
	.exit = app_window_idle_watch_exit,
	.destroy = app_window_idle_watch_destroy,

    //.touch_event_num = 1,
    //.touch_events = &app_window_idle_watch_touch_events,

	.event_num = countof(app_window_idle_watch_static_events),
	.events = app_window_idle_watch_static_events,
};




