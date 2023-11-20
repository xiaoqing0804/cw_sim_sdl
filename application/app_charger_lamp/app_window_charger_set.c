#include "picture.h"
#include "language.h"
#include "app_task_main.h"
#include "data_common.h"
#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "app_window_charger_lamp.h"
#include "app_ota/app_window_ota.h"
#include "app_charger/app_window_charger.h"
#include "data_gensor_direction.h"
#include "bsp_lcd/lcd.h"
#include "app_window_charger_set.h"
#include "app_window_charger_set_layout.h"

#include "application_titlebar.h"
#include "data_common.h"

unsigned char charger_flag = 1;
/*-----------------------------系统事件--------------------------------------*/

static void app_window_charger_set_init(void *buf)
{

}

static void app_window_charger_set_load(void *buf)
{
	application_titlebar_create_color(&gui_screen_charger_set, STRING_BED_LAMP,COLOR_RGB(19,154,255));

	gui_box_struct *charger_set_onoff = gui_surface_get_box(&gui_screen_charger_set, CHARGER_SET_ID_PIC);

	if(charger_flag)
		gui_surface_box_image_change(charger_set_onoff,&pic_set_on_info);
	else
		gui_surface_box_image_change(charger_set_onoff,&pic_set_off_info);
}


static void app_window_charger_set_entry(void *buf)
{

}


static void app_window_charger_set_exit()
{
}

static void app_window_charger_set_destroy()
{

}

static void app_window_charger_set_event_touch(gui_click_struct *event)
{
	charger_flag = !charger_flag;
	app_window_charger_set_load(NULL);

	gui_surface_commit();
}


/*-----------------------------响应事件--------------------------------------*/
static const gui_touch_event_struct app_window_charger_set_touch_events[] =
{
	{	.id = CHARGER_SET_ID_MODE_PROGRESS,
		.click = app_window_charger_set_event_touch,
	},
};


/*-----------------------------配置--------------------------------------*/


const gui_window_struct app_window_charger_set =
{
	.screen = &gui_screen_charger_set,
	.init = app_window_charger_set_init,
	.load = app_window_charger_set_load,
	.entry = app_window_charger_set_entry,
	.exit = app_window_charger_set_exit,
	.destroy = app_window_charger_set_destroy,

	.touch_event_num = countof(app_window_charger_set_touch_events),
	.touch_events = app_window_charger_set_touch_events,
};

