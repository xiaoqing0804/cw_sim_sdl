
#include "sys_init.h"
#include "bsp_includes.h"
#include "math.h"

#include "data_common.h"
#include "data_receive_package.h"

#include "srv_alipay.h"
#include "application_config_app_info.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#if TCFG_PAY_ALIOS_ENABLE
#include "app_window_alipay_loading.h"
#include "app_window_alipay_bind.h"
#include "app_window_alipay_menu.h"
#include "app_window_alipay_qrcode.h"


extern void app_window_alipay_entry(app_info_struct* app_info);


// -----------------------------------------------------------------------------------------------
static const gui_image_struct gui_alipay_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_zhifubao_startup_info,
};

static const gui_font_struct gui_alipay_pre_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    #if (LCD_SHAPE == LCD_CIRCLE)
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_TOP),
    #else
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    #endif
    .auto_wrap = 1,
    .color = COLOR_RGB(180, 180, 180),
    .size = SYS_FONT_XSMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_APPINFO,
};

static const gui_canvas_struct gui_alipay_cyc_bg =
{
    .type = TYPE_GUI_DRAW_SHAPE_CIRCLE,
    .penSize = 9,
    .penColor = COLOR_RGB(0, 0, 255),
    .canvas.circle.cx = LCD_SIZE_HALF_WIDTH,
    .canvas.circle.cy = LCD_SIZE_HALF_HEIGHT,
    .canvas.circle.r  = LCD_SIZE_HALF_WIDTH-2,
};



// -----------------------------------------------------------------------------------------------
enum
{
    ALIPAY_ICON_ID = 10,
    ALIPAY_PRE_TEXT_ID,
};

static const gui_widget_struct gui_alipay_widget_loading[] =
{
    {
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_cyc_bg,
    },

    // flag: 0 -------------------------------
	{
	    .id = ALIPAY_ICON_ID,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num = 1,
		.children = &gui_alipay_icon,
	},

    {
        .id = ALIPAY_PRE_TEXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
    #if (LCD_SHAPE == LCD_CIRCLE)
        .x = 15,
        .y = LCD_SIZE_HALF_HEIGHT+60,
        .width = LCD_SIZE_WIDTH-30,
        .height = 90,
    #else
        .y = LCD_SIZE_HEIGHT-90,
        .width = LCD_SIZE_WIDTH,
        .height = 90,
    #endif
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_pre_text,
    },
};

static const gui_screen_struct gui_alipay_screen_loading =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_alipay_widget_loading,
	.child_num = countof(gui_alipay_widget_loading),
};

/*-----------------------------系统事件--------------------------------------*/

static void app_window_alipay_loading_init(void *buf)
{
    SYS_DEBUG("app: alipay_loading_init()");
}

static void app_window_alipay_loading_load(void)
{
    SYS_DEBUG("app: alipay_loading_load()");
}


static void app_window_alipay_loading_entry(void)
{
    SYS_DEBUG("app: alipay_loading_entry()");
    application_open_act_timer(APPLICATION_TIMER_ACT_3, 2000);
}


static void app_window_alipay_loading_exit(void)
{
    SYS_DEBUG("app: alipay_loading_exit()");
    application_close_act_timer(APPLICATION_TIMER_ACT_3);
}

static void app_window_alipay_loading_destroy(void)
{
    SYS_DEBUG("app: alipay_loading_destroy()");
}



/*-----------------------------响应事件--------------------------------------*/
static void app_window_alipay_timer_handler(void* buf)
{
    app_window_alipay_entry(NULL);
}

static void app_window_alipay_key_handler(void* buf)
{
    application_go_back();
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_alipay_loading_static_events[] =
{
    {.id = EVENT_ACT,                .handler = app_window_alipay_timer_handler},
    {.id = EVENT_KEY2_SHORT,         .handler = app_window_alipay_key_handler},
    {.id = EVENT_KEY1_SHORT,         .handler = app_window_alipay_key_handler},
};

const gui_window_struct app_window_alipay_loading =
{
	.screen = &gui_alipay_screen_loading,
	.init = app_window_alipay_loading_init,
	.load = app_window_alipay_loading_load,
	.entry = app_window_alipay_loading_entry,
	.exit = app_window_alipay_loading_exit,
	.destroy = app_window_alipay_loading_destroy,

	.event_num = countof(app_window_alipay_loading_static_events),
    .events = app_window_alipay_loading_static_events,
};

#endif
