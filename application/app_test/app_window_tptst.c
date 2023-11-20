
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

#include "app_window_tptst.h"
#include "srv_apptst_main.h"

#define TP_TEST_BOX_BASE_ID    10
#define TP_TEST_GRID_ROW_NUM   (3)      // 行...
#define TP_TEST_GRID_COL_NUM   (3)      // 列...

#define TP_TEST_AREA_X(col)     ((col)*LCD_SIZE_WIDTH/TP_TEST_GRID_COL_NUM)
#define TP_TEST_AREA_Y(row)     ((row)*LCD_SIZE_HEIGHT/TP_TEST_GRID_ROW_NUM)
#define TP_TEST_AREA_W          (LCD_SIZE_WIDTH/TP_TEST_GRID_COL_NUM)
#define TP_TEST_AREA_H          (LCD_SIZE_HEIGHT/TP_TEST_GRID_ROW_NUM)

#define FACTORY_TOUCH_TEST_AREA(n)              \
    {.id = TP_TEST_BOX_BASE_ID + (n),  \
        .type = TYPE_GUI_CONTROL_CANVAS,        \
        .x = TP_TEST_AREA_X((n)%TP_TEST_GRID_COL_NUM),             \
        .y = TP_TEST_AREA_Y((n)/TP_TEST_GRID_COL_NUM),             \
        .width = TP_TEST_AREA_W,                \
        .height = TP_TEST_AREA_H,               \
        .visible= 1,                            \
        .child_num = 1,                         \
        .children = &gui_tptst_fill_rect,    \
    }

static const gui_canvas_struct gui_tptst_rect =
{
    .id = 1,
    .type = TYPE_GUI_DRAW_SHAPE_RECT,
    .penSize = 1,
    .penColor = COLOR_RGB(0, 0, 255),
    .canvas.rect.x0 = 0,
    .canvas.rect.y0 = 0,
    .canvas.rect.x1 = TP_TEST_AREA_W-1,
    .canvas.rect.y1 = TP_TEST_AREA_H-1,
};

static const gui_canvas_struct gui_tptst_fill_rect =
{
    .id = 1,
    .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
    .penSize = 1,
    .penColor = COLOR_RGB(0, 0, 255),
    .canvas.rect.x0 = 1,
    .canvas.rect.y0 = 1,
    .canvas.rect.x1 = TP_TEST_AREA_W-2,
    .canvas.rect.y1 = TP_TEST_AREA_H-2,
};

static const gui_widget_struct gui_tptst_widgets[] =
{
    FACTORY_TOUCH_TEST_AREA(0),
    FACTORY_TOUCH_TEST_AREA(1),
    FACTORY_TOUCH_TEST_AREA(2),
    FACTORY_TOUCH_TEST_AREA(3),

    FACTORY_TOUCH_TEST_AREA(4),
    FACTORY_TOUCH_TEST_AREA(5),
    FACTORY_TOUCH_TEST_AREA(6),
    FACTORY_TOUCH_TEST_AREA(7),

    FACTORY_TOUCH_TEST_AREA(8),
    FACTORY_TOUCH_TEST_AREA(9),
    FACTORY_TOUCH_TEST_AREA(10),
    FACTORY_TOUCH_TEST_AREA(11),

    FACTORY_TOUCH_TEST_AREA(12),
    FACTORY_TOUCH_TEST_AREA(13),
    FACTORY_TOUCH_TEST_AREA(14),
    FACTORY_TOUCH_TEST_AREA(15),
};

static const gui_screen_struct gui_screen_tptst =
{
	.children = gui_tptst_widgets,
	.child_num = countof(gui_tptst_widgets),
};

/////////////////////////////////////////////////////////////////////////////////////////////
static unsigned int g_tptst_check_bits;
static unsigned int app_window_tptst_check_completed(unsigned int box_id)
{
    if (box_id >= TP_TEST_BOX_BASE_ID) {
        box_id -= TP_TEST_BOX_BASE_ID;

        g_tptst_check_bits &= ~(1 << box_id);
        if (g_tptst_check_bits == 0) {
            return 1;       // completed!!!
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_tptst_init(void* buf)
{
    g_tptst_check_bits = (1 << (TP_TEST_GRID_ROW_NUM*TP_TEST_GRID_COL_NUM)) - 1;
}

static void app_window_tptst_load(void *buf)
{
}

static void app_window_tptst_entry(void *buf)
{
}


static void app_window_tptst_exit()
{
}

static void app_window_tptst_destroy()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_tptst_click(gui_click_struct *event)
{
    SYS_DEBUG("app: window_tptst_click(x: %d, y: %d)", event->x, event->y);
    gui_box_struct* box = gui_surface_get_by_position(gui_surface_get_surface(&gui_screen_tptst), event->x, event->y);
    if (box != NULL) {
        SYS_DEBUG("box->id = %d", box->id);
        if (box->id >= TP_TEST_BOX_BASE_ID) {
            apptst_upload_common_result(APP_TEST_TP, 1, box->id-TP_TEST_BOX_BASE_ID+1);       // notify-app
            if (app_window_tptst_check_completed(box->id)) {
                application_go_back();
            }
            else {
                gui_surface_box_canvas_change(box, 1, &gui_tptst_rect);
                box->id = 0;
                gui_surface_commit();
            }
        }
    }
    else {
        SYS_DEBUG("11111111111111");
    }
}


/////////////////////////////////////////////////////////////////////////////////
static void app_window_tptst_exit_handler(void* buf)
{
    application_go_back();
}

/*-----------------------------����--------------------------------------*/
static const app_window_event_struct app_window_tptst_static_events[] =
{
    {.id = EVENT_APPTEST_TP_OFF, .handler = app_window_tptst_exit_handler},
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_GO_HOME},
};

static const gui_touch_event_struct app_window_tptst_touch_events[] =
{
    {.id = 0xFFFF,     .click = app_window_tptst_click},
};


static const gui_window_config_struct app_window_tptst_config =
{
	.entry_back_to_destory = 1,
};


const gui_window_struct app_window_tptst =
{
	.screen = &gui_screen_tptst,
	.config = &app_window_tptst_config,

	.init = app_window_tptst_init,
	.load = app_window_tptst_load,
	.entry = app_window_tptst_entry,
	.exit = app_window_tptst_exit,
	.destroy = app_window_tptst_destroy,

    .touch_event_num = countof(app_window_tptst_touch_events),
    .touch_events = app_window_tptst_touch_events,

	.event_num = countof(app_window_tptst_static_events),
	.events = app_window_tptst_static_events,
};





