
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_gsensor.h"


static const gui_font_struct gui_gsensor_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "g-Sensor",
};

static const gui_widget_struct gui_gsensor_widgets[] =
{
	{
		.type = TYPE_GUI_CONTROL_LABEL,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT/6,
		.visible= 1,
        .child_num = 1,
        .children = &gui_gsensor_text,
	},
    {
        .id = 1,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (2*LCD_SIZE_HEIGHT)/6,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/6,
        .visible= 1,
        .child_num = 1,
        .children = &gui_gsensor_text,
    },
    {
        .id = 2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (3*LCD_SIZE_HEIGHT)/6,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/6,
        .visible= 1,
        .child_num = 1,
        .children = &gui_gsensor_text,
    },
    {
        .id = 3,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (4*LCD_SIZE_HEIGHT)/6,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/6,
        .visible= 1,
        .child_num = 1,
        .children = &gui_gsensor_text,
    },
};

const gui_screen_struct gui_screen_gsensor =
{
	.children = gui_gsensor_widgets,
	.child_num = countof(gui_gsensor_widgets),
};

static unsigned int m_test_time;

/*-----------------------------系统事件--------------------------------------*/
static void app_window_gsensor_update(short x, short y, short z)
{
    gui_box_struct*  box;
    char temp[48];

    box = gui_surface_get_box(&gui_screen_gsensor, 1);
    if (box != NULL) {
        sprintf(temp, "x: %d", x);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_gsensor, 2);
    if (box != NULL) {
        sprintf(temp, "y: %d", y);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_gsensor, 3);
    if (box != NULL) {
        sprintf(temp, "z: %d", z);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }

}

static void app_window_gsensor_init(void *buf)
{

}

static void app_window_gsensor_load(void *buf)
{
    app_window_gsensor_update(0, 0, 0);
}


static void app_window_gsensor_entry(void *buf)
{
    bsp_gsensor_set_mode_test(1);
}


static void app_window_gsensor_exit()
{
    bsp_gsensor_set_mode_test(0);
}

static void app_window_gsensor_destroy()
{
}



static void app_window_gsensor_data_handler(void* buf)
{
    short* xyz = (short*)buf;
    app_window_gsensor_update(xyz[0], xyz[1], xyz[2]);
    gui_surface_commit();
}


/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_gsensor_static_events[] =
{
    {.id = EVENT_G_SENSOR_DATA, .handler = app_window_gsensor_data_handler},
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_GO_HOME}
};

static const gui_window_config_struct app_window_gsensor_config =
{
	.entry_back_to_destory = 1,
};


const gui_window_struct app_window_gsensor =
{
	.screen = &gui_screen_gsensor,
	.config = &app_window_gsensor_config,

	.init = app_window_gsensor_init,
	.load = app_window_gsensor_load,
	.entry = app_window_gsensor_entry,
	.exit = app_window_gsensor_exit,
	.destroy = app_window_gsensor_destroy,

	.event_num = countof(app_window_gsensor_static_events),
	.events = app_window_gsensor_static_events,
};




