
#include "sys_init.h"
#include "data_common.h"
#include "bsp_includes.h"

#include "gui_surface_box_label.h"
#include "data_receive_package.h"
#include "gui_surface_box_image.h"

#include "app_window_game_dadishu.h"

#include "game_dadishu_ui.h"


extern const gui_screen_struct gui_screen_game_dadishu;

/*-----------------------------系统事件--------------------------------------*/

static void app_window_game_dadishu_init(void *buf)
{
}

static void app_window_game_dadishu_load(void *buf)
{
	game_ui_dadishu_init();
}


static void app_window_game_dadishu_entry(void *buf)
{

}


static void app_window_game_dadishu_exit()
{
	game_ui_dadishu_end();
}

static void app_window_game_dadishu_destroy()
{
	
}

static unsigned char app_window_game_dadishu_touch_event_handler(gui_touch_struct* touch)
{
    game_ui_dadishu_touch_handler(touch);
    return 1;
}


static void app_window_game_dadishu_window_act(void* buf)
{
    game_ui_dadishu_enable();
}


/*-----------------------------响应事件--------------------------------------*/

static const gui_touch_event_struct app_game_dadishu_touch_events[] =
{
    {.id = 0xFFFF, .touch = app_window_game_dadishu_touch_event_handler},
};


static const app_window_event_struct app_window_game_dadishu_static_events[] = 
{
    {.id = EVENT_ACT, .handler = app_window_game_dadishu_window_act},
	{.id = EVENT_BL_TIMEOUT,	.handler = NULL	}
};


/*-----------------------------配置--------------------------------------*/
const gui_window_struct app_window_game_dadishu =
{
	.screen = &gui_screen_game_dadishu,
	.init = app_window_game_dadishu_init,
	.load = app_window_game_dadishu_load,
	.entry = app_window_game_dadishu_entry,
	.exit = app_window_game_dadishu_exit,
	.destroy = app_window_game_dadishu_destroy,

    .touch_event_num = countof(app_game_dadishu_touch_events),
    .touch_events = app_game_dadishu_touch_events,

	.event_num = countof(app_window_game_dadishu_static_events),
    .events = app_window_game_dadishu_static_events,
};

