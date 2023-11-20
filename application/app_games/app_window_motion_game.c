

#include "sys_init.h"
#include "data_common.h"
#include "bsp_includes.h"
#include "srv_motion_game.h"

#include "gui_surface_box_label.h"
#include "data_receive_package.h"
#include "gui_surface_box_image.h"

#include "app_window_motion_game.h"

#if GUI_MOTION_GAME_SUPPORT
extern void bt_ble_set_fast_conn_params(void);

static const gui_font_struct gui_text_motion_game =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER,GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER,GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "Motion game",
};

static const gui_widget_struct gui_widget_motion_game_list[] =
{
	{
		.type = TYPE_GUI_CONTROL_LABEL,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_motion_game,
	},
};

const gui_screen_struct gui_screen_motion_game =
{
	.children = gui_widget_motion_game_list,
	.child_num = countof(gui_widget_motion_game_list),
};


/*-----------------------------系统事件--------------------------------------*/

static void app_window_motion_game_init(void *buf)
{
    bt_ble_set_fast_conn_params();
}

static void app_window_motion_game_load(void *buf)
{
}


static void app_window_motion_game_entry(void *buf)
{
	SYS_DEBUG("app: window_motion_game_entry()");
    srv_motion_game_start();
}


static void app_window_motion_game_exit()
{
	SYS_DEBUG("app: window_motion_game_exit()");
}

static void app_window_motion_game_destroy()
{

}

static void app_window_motion_game_ind(void* buf)
{
    unsigned char* ind = (unsigned char*)buf;
    if (ind[0] == 0) {
        //
        srv_motion_game_stop(0);
        application_go_back();
    }
}

static void app_window_motion_key_handler(void* buf)
{
	srv_motion_game_stop(1);
	application_go_back();
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_motion_game_static_events[] =
{
    {.id = EVENT_KEY1_SHORT, .handler = app_window_motion_key_handler},
    {.id = EVENT_MOTION_GAME_IND, .handler = app_window_motion_game_ind},
	{.id = EVENT_BL_TIMEOUT, .handler = NULL},
	{.id = EVENT_BACKLIGHT_OFF, .handler = NULL},
	{.id = EVENT_CTP_COVER_LCD_TURNOFF, .handler = NULL},
	{.id = EVENT_GUI_POP_WINDOW, .handler = NULL},
	{.id = EVENT_ALL,	.handler = NULL	}
};

const gui_window_struct app_window_motion_game =
{
	.screen = &gui_screen_motion_game,
	.init = app_window_motion_game_init,
	.load = app_window_motion_game_load,
	.entry = app_window_motion_game_entry,
	.exit = app_window_motion_game_exit,
	.destroy = app_window_motion_game_destroy,

    .event_num = countof(app_window_motion_game_static_events),
    .events = app_window_motion_game_static_events,
};

#endif

