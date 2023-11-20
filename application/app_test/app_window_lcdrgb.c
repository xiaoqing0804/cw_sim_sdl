
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"
#include "dev_version.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"

#include "app_window_lcdrgb.h"


static const gui_canvas_struct gui_lcdrgb_color_rect[3] =
{
    {
        .id = 1,
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,	  // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(255, 0, 0),
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_WIDTH-1,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
    },
    {
        .id = 1,
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,	  // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(0, 255, 0),
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_WIDTH-1,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
    },
    {
        .id = 1,
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,	  // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(0, 0, 255),
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_WIDTH-1,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
    }
};

static const gui_widget_struct gui_lcdrgb_widgets[] =
{
    {
    	.id = 10,
    	.type = TYPE_GUI_CONTROL_CANVAS,
    	.width = LCD_SIZE_WIDTH,
    	.height = LCD_SIZE_HEIGHT,
    	.visible= 1,
    	.child_num = 1,
    	.children = gui_lcdrgb_color_rect,
    }
};

static const gui_screen_struct gui_screen_lcdrgb =
{
	.children = gui_lcdrgb_widgets,
	.child_num = countof(gui_lcdrgb_widgets),
};

static void app_window_lcdrgb_init(void* buf)
{
}

static void app_window_lcdrgb_load(void *buf)
{
}

static void app_window_lcdrgb_entry(void *buf)
{
    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}


static void app_window_lcdrgb_exit()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_lcdrgb_destroy()
{

}


///////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_lcdrgb_acttimer_handler(void* buf)
{
    SYS_DEBUG("app: fact_test, timer");
    gui_box_struct* box = gui_surface_get_box(&gui_screen_lcdrgb, 10);
    if (box != NULL) {
        box->layout_index ++;
        if (box->layout_index > 2) {
            box->layout_index = 0;
        }
        gui_surface_box_canvas_change(box, 1, &gui_lcdrgb_color_rect[box->layout_index]);
        gui_surface_commit();
    }
}

static void app_window_lcdrgb_turnoff_handler(void* buf)
{
    application_go_back();
}



/*-----------------------------����--------------------------------------*/
static const app_window_event_struct app_window_lcdrgb_static_events[] =
{
	{.id = EVENT_ACT,               .handler = app_window_lcdrgb_acttimer_handler },
    {.id = EVENT_APPTEST_LCD_RGB_OFF, .handler = app_window_lcdrgb_turnoff_handler},
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_GO_HOME},
};

static const gui_window_config_struct app_window_lcdrgb_config =
{
	.entry_back_to_destory = 1,
};


const gui_window_struct app_window_lcdrgb =
{
	.screen = &gui_screen_lcdrgb,
	.config = &app_window_lcdrgb_config,

	.init = app_window_lcdrgb_init,
	.load = app_window_lcdrgb_load,
	.entry = app_window_lcdrgb_entry,
	.exit = app_window_lcdrgb_exit,
	.destroy = app_window_lcdrgb_destroy,

	.event_num = countof(app_window_lcdrgb_static_events),
	.events = app_window_lcdrgb_static_events,
};





