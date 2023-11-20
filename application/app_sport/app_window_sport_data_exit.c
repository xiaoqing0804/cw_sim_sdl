#include "app_window_sport_data_exit.h"
#include "app_window_sport_data_exit_layout.h"
#include "debug_info.h"


/*-----------------------------系统事件--------------------------------------*/

static void app_window_sport_exit_init(void *buf)
{
	
}

static void app_window_sport_exit_load(void *buf)
{
	
}


static void app_window_sport_exit_entry(void *buf)
{
	
}


static void app_window_sport_exit_exit()
{
	
}

static void app_window_sport_exit_destroy()
{
	
}



/*-----------------------------响应事件--------------------------------------*/


const gui_window_struct app_window_sport_exit =
{
	.screen = &gui_screen_sport_exit,
	.init = app_window_sport_exit_init,
	.load = app_window_sport_exit_load,
	.entry = app_window_sport_exit_entry,
	.exit = app_window_sport_exit_exit,
	.destroy = app_window_sport_exit_destroy,
};

