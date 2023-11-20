
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_battery.h"


static const gui_font_struct gui_battery_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "Battery",
};

static const gui_widget_struct gui_battery_widgets[] =
{
	{
		.type = TYPE_GUI_CONTROL_LABEL,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT/5,
		.visible= 1,
        .child_num = 1,
        .children = &gui_battery_text,
	},
    {
        .id = 1,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (2*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_battery_text,
    },
    {
        .id = 2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (3*LCD_SIZE_HEIGHT)/5,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/5,
        .visible= 1,
        .child_num = 1,
        .children = &gui_battery_text,
    },
};

static const gui_screen_struct gui_screen_battery =
{
	.children = gui_battery_widgets,
	.child_num = countof(gui_battery_widgets),
};

static unsigned int m_test_time;

/*-----------------------------系统事件--------------------------------------*/
static void app_window_battery_update(void)
{
    gui_box_struct*  box;
    char temp[48];

    app_battery_info_struct* batt_info = application_get_battery_info();

    box = gui_surface_get_box(&gui_screen_battery, 1);
    if (box != NULL) {
        sprintf(temp, "volt: %d", batt_info->voltage);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
    box = gui_surface_get_box(&gui_screen_battery, 2);
    if (box != NULL) {
        sprintf(temp, "cap: %d%%", batt_info->percent);
        gui_surface_box_label_change_string(box, (unsigned char*)temp);
    }
}

static void app_window_battery_init(void *buf)
{

}

static void app_window_battery_load(void *buf)
{
    app_window_battery_update();
}


static void app_window_battery_entry(void *buf)
{
}


static void app_window_battery_exit()
{
}

static void app_window_battery_destroy()
{
}


/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_battery_static_events[] =
{
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_GO_HOME}
};

static const gui_window_config_struct app_window_battery_config =
{
	.entry_back_to_destory = 1,
};


const gui_window_struct apptst_window_battery =
{
	.screen = &gui_screen_battery,
	.config = &app_window_battery_config,

	.init = app_window_battery_init,
	.load = app_window_battery_load,
	.entry = app_window_battery_entry,
	.exit = app_window_battery_exit,
	.destroy = app_window_battery_destroy,

	.event_num = countof(app_window_battery_static_events),
	.events = app_window_battery_static_events,
};




