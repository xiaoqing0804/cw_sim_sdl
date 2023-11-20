#include "app_window_vib.h"
#include "app_window_vib_layout.h"
#include "app_window_vib_ui.h"

#include "application_titlebar.h"
#include "data_common.h"

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_vib_init(void *buf)
{

}

static void app_window_vib_load(void *buf)
{
	app_window_vib_ui_show();
}


static void app_window_vib_entry(void *buf)
{

}


static void app_window_vib_exit()
{
	block_save_user_info(&g_vib_mode);
}

static void app_window_vib_destroy()
{

}

static void app_window_vib_event_touch(gui_click_struct *event)
{
	g_vib_mode.vib_onoff = !g_vib_mode.vib_onoff;
	app_window_vib_load(NULL);

	gui_surface_commit();
}


/*-----------------------------��Ӧ�¼�--------------------------------------*/
static const gui_touch_event_struct app_window_vib_touch_events[] =
{
	{	.id = VIB_ID_PIC,
		.click = app_window_vib_event_touch,
	},
};


/*-----------------------------����--------------------------------------*/


const gui_window_struct app_window_vib =
{
	.screen = &gui_screen_vib,
	.init = app_window_vib_init,
	.load = app_window_vib_load,
	.entry = app_window_vib_entry,
	.exit = app_window_vib_exit,
	.destroy = app_window_vib_destroy,

	.touch_event_num = countof(app_window_vib_touch_events),
	.touch_events = app_window_vib_touch_events,
};

