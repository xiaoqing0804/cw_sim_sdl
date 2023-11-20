/*--------------------GUI-------------------*/
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "sys_timer.h"
#include "app_task_main.h"

#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "data_manager_sensor.h"
#include "data_receive_package.h"

#include "gui_window.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"


#include "app_window_bp.h"
#include "app_window_bp_layout.h"
#include "app_window_bp_measur.h"
#include "app_window_bp_measur_layout.h"
#include "data_common.h"

#define BP1_VALUE_ARRAY      g_dbp_history_data

#define BP2_VALUE_ARRAY      g_sbp_history_data
unsigned char bp_get_max(void)
{
	time_struct time;
	int num = 0, idx;
    unsigned char max = 0;

    sys_time_get(&time);
    
    num = (time.hour*60+time.min)/HR_MIN_TIME;

    for (idx=0; idx<num; idx++) {
        if (BP2_VALUE_ARRAY[idx] > max) {
            max = BP2_VALUE_ARRAY[idx];
        }
    }
    return max;
}

unsigned char bp_get_min(void)
{
	time_struct time;
	int num = 0, idx;
    unsigned char min = 255;

	sys_time_get(&time);

    num = (time.hour*60+time.min)/HR_MIN_TIME;

    for (idx=0; idx<num; idx++) {
        if (BP1_VALUE_ARRAY[idx] > 0 && BP1_VALUE_ARRAY[idx] < min) {
            min = BP1_VALUE_ARRAY[idx];
        }
    }
    return (min == 255) ? 0 : min;
}




/*-----------------------------系统事件--------------------------------------*/

static void app_window_bp_measur_init(void *buf)
{


}

static void app_window_bp_measur_load(void *buf)
{
	 gui_box_struct* box;
		unsigned char max, min;

    max = bp_get_max();
    min = bp_get_min();
	
	 box = gui_surface_get_box(&gui_screen_bp_measur, BP_MEASUR_LAYOUT_ID_HR_MAX);
    if (box != NULL) {
        if (max != 0) {
            gui_surface_box_label_change_number(box, max);
        }
    }
    box = gui_surface_get_box(&gui_screen_bp_measur, BP_MEASUR_LAYOUT_ID_HR_MIN);
    if (box != NULL) {
        if (min != 0) {
            gui_surface_box_label_change_number(box, min);
        }
    }
    gui_surface_commit();
	
	
}


static void app_window_bp_measur_entry(void *buf)
{

}


static void app_window_bp_measur_exit()
{

}

static void app_window_bp_measur_destroy()
{
	
}


static void app_window_bp_measur_acttimer_handler(void* buf)
{


}

static void bp_info_window_real_heart(void *buf)
{


}


static void app_window_bp_measur_chart_rolkey_handler(void* buf)
{
    rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
    if (rolkey->rotate == ROTATE_TYPE_FORWARD) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_bp, NULL);
    }
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_bp_measur_static_events[2] =
{
    {
        .id = EVENT_ROLKEY,
        .handler = app_window_bp_measur_chart_rolkey_handler,
    },
};

static const gui_window_config_struct app_window_bp_measur_config =
{
	.entry_back_to_destory = 1,
};


const gui_window_struct app_window_bp_measur =
{
	.screen = &gui_screen_bp_measur,
	.config = &app_window_bp_measur_config,

	.init = app_window_bp_measur_init,
	.load = app_window_bp_measur_load,
	.entry = app_window_bp_measur_entry,
	.exit = app_window_bp_measur_exit,
	.destroy = app_window_bp_measur_destroy,

	.event_num = countof(app_window_bp_measur_static_events),
	.events = app_window_bp_measur_static_events,
	
	
	
};


