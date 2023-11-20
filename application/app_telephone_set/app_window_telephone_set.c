#include "app_window_telephone_set.h"
#include "app_window_telephone_set_layout.h"
#include "application_titlebar.h"

/*-----------------------------系统事件--------------------------------------*/

static void app_window_telephone_init(void *buf)
{
	
}

static void app_window_telephone_load(void *buf)
{
	application_titlebar_create(&gui_screen_telephone, STRING_TELEPHONE);
}


static void app_window_telephone_entry(void *buf)
{
	
}


static void app_window_telephone_exit()
{
	
}

static void app_window_telephone_destroy()
{
	
}



/*-----------------------------响应事件--------------------------------------*/


/*-----------------------------配置--------------------------------------*/


const gui_window_struct app_window_telephone =
{
	.screen = &gui_screen_telephone,
	.init = app_window_telephone_init,
	.load = app_window_telephone_load,
	.entry = app_window_telephone_entry,
	.exit = app_window_telephone_exit,
	.destroy = app_window_telephone_destroy,

};

