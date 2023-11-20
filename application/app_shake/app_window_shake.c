#include "app_window_shake.h"
#include "app_window_shake_layout.h"
#include "application_titlebar.h"

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_shake_init(void *buf)
{
}

static void app_window_shake_load(void *buf)
{
	app_window_shake_ui_show();
}

static void app_window_shake_entry(void *buf)
{
}

static void app_window_shake_exit()
{
}

static void app_window_shake_destroy()
{
}

/*-----------------------------��Ӧ�¼�--------------------------------------*/

/*-----------------------------����--------------------------------------*/

const gui_window_struct app_window_shake =
	{
		.screen = &gui_screen_shake,
		.init = app_window_shake_init,
		.load = app_window_shake_load,
		.entry = app_window_shake_entry,
		.exit = app_window_shake_exit,
		.destroy = app_window_shake_destroy,

};
