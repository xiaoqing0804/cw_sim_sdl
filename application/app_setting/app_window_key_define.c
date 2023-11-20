#include "app_window_key_define.h"
#include "app_window_key_define_ui.h"
#include "app_window_key_define_layout.h"
#include "app_window_key_setting_click.h"
#include "config_key_define.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_key_define_click_on_layout_item(gui_click_layout_struct *event)
{
	if (event->id == KEY_DEFINE_LAYOUT_ID_CLICK)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_key_setting_click, (unsigned char)KEY_DEFINE_TYPE_CLICK);
	}
	else if (event->id == KEY_DEFINE_LAYOUT_ID_DOUBLE)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_key_setting_click, (unsigned char)KEY_DEFINE_TYPE_DOUBLE);
	}
	else if (event->id == KEY_DEFINE_LAYOUT_ID_LONG_TOUCH)
	{
		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_key_setting_click, (unsigned char)KEY_DEFINE_TYPE_LONG);
	}
}

/*-----------------------------主流程--------------------------------------*/
static void app_window_key_define_init(void *buf)
{
}

static void app_window_key_define_load(void *buf)
{
	app_window_key_defint_show();
}

static void app_window_key_define_entry(void *buf)
{
}

static void app_window_key_define_exit()
{
}

static void app_window_key_define_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

const gui_window_struct app_window_key_define =
	{
		.screen = &gui_screen_key_define,

		.init = app_window_key_define_init,
		.load = app_window_key_define_load,
		.entry = app_window_key_define_entry,
		.exit = app_window_key_define_exit,
		.destroy = app_window_key_define_destroy,

		.click_on_layout_item = app_window_key_define_click_on_layout_item,
};
