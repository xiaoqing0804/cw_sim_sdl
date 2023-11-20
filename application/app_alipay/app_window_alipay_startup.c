
#include "sys_init.h"
#include "bsp_includes.h"
#include "math.h"

#include "data_common.h"
#include "data_receive_package.h"

#include "srv_alipay.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#if TCFG_PAY_ALIOS_ENABLE
#include "app_window_alipay_bind.h"
#include "app_window_alipay_menu.h"
#include "app_window_alipay_qrcode.h"
#include "app_window_alipay_barcode.h"
#include "app_window_alipay_startup.h"


// -----------------------------------------------------------------------------------------------
static const gui_image_struct gui_alipay_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_zhifubao_startup_info,
};

/*
static const gui_font_struct gui_alipay_pre_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_TOP),
    .auto_wrap = 1,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY,
};
*/


// -----------------------------------------------------------------------------------------------
enum
{
    ALIPAY_ICON_ID = 10,
    ALIPAY_PRE_TEXT_ID,
};

static const gui_widget_struct gui_alipay_widget_startup[] =
{
	{
	    .id = ALIPAY_ICON_ID,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_alipay_icon,
	},

    /*
    {
        .id = ALIPAY_PRE_TEXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 15,
        .y = LCD_SIZE_HALF_HEIGHT+60,
        .width = LCD_SIZE_WIDTH-30,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_pre_text,
    },*/
};

static const gui_screen_struct gui_alipay_screen_startup =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_alipay_widget_startup,
	.child_num = countof(gui_alipay_widget_startup),
};

/*-----------------------------系统事件--------------------------------------*/
static unsigned char g_alipay_startup_enter_flag;  // 0: shortcut;  1: menu

static void app_window_alipay_startup_init(void *buf)
{
    SYS_DEBUG("app: alipay_startup_init()");
    g_alipay_startup_enter_flag = ((buf == NULL) ? 0 : 1);
}

static void app_window_alipay_startup_load(void)
{
    gui_box_struct* box;
    SYS_DEBUG("app: alipay_startup_load()");

    box = gui_surface_get_box(&gui_alipay_screen_startup, ALIPAY_PRE_TEXT_ID);
    if (box != NULL) {
        gui_surface_box_change_y(box, LCD_SIZE_HALF_HEIGHT + pic_zhifubao_startup_info.height/2 + 10);
    }
}


static void app_window_alipay_startup_entry(void)
{
    SYS_DEBUG("app: alipay_startup_entry()");
    application_open_act_timer(APPLICATION_TIMER_ACT_3, 1500);
}


static void app_window_alipay_startup_exit(void)
{
    SYS_DEBUG("app: alipay_startup_exit()");
    application_close_act_timer(APPLICATION_TIMER_ACT_3);
}

static void app_window_alipay_startup_destroy(void)
{
    SYS_DEBUG("app: alipay_startup_destroy()");
}



/*-----------------------------响应事件--------------------------------------*/
static void app_window_alipay_timer_handler(void* buf)
{
    void* param = ((g_alipay_startup_enter_flag != 0) ? &app_window_alipay_startup : NULL);
    unsigned int sta = srv_alipay_get_bind_status();
    SYS_DEBUG("app: alipay_timer_handler(%d), sta=%d", g_alipay_startup_enter_flag, sta);

    if (sta == 2) {
        if (g_alipay_startup_enter_flag) {
            // menu
            application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_menu, NULL);
        }
        else {
            // paycode
            application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_qrcode, NULL);
        }
    }
    else {
        // bind
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_bind, param);
    }
}


/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_alipay_startup_static_events[] =
{
    {.id = EVENT_ACT,                .handler = app_window_alipay_timer_handler},
    {.id = EVENT_BL_TIMEOUT},       // 不允许灭屏 ...
    {.id = EVENT_ALL},              // 不允许灭屏 ...
};


static const gui_window_config_struct app_window_alipay_startup_cfg =
{
    .forbid_gesture_back = 1,
    .entry_back_to_destory = 1,
};

const gui_window_struct app_window_alipay_startup =
{
	.screen = &gui_alipay_screen_startup,
    .config = &app_window_alipay_startup_cfg,
	.init = app_window_alipay_startup_init,
	.load = app_window_alipay_startup_load,
	.entry = app_window_alipay_startup_entry,
	.exit = app_window_alipay_startup_exit,
	.destroy = app_window_alipay_startup_destroy,

	.event_num = countof(app_window_alipay_startup_static_events),
    .events = app_window_alipay_startup_static_events,
};

#endif
