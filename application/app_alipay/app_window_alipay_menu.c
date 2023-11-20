
#include "sys_init.h"
#include "bsp_includes.h"
#include "data_common.h"
#include "data_receive_package.h"

#include "srv_alipay.h"
#include "srv_aliyun.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"
#include "application_config_app_info.h"

#if TCFG_PAY_ALIOS_ENABLE
#include "app_window_alipay_menu.h"
#include "app_window_alipay_qrcode.h"
#include "app_window_alipay_barcode.h"
#include "app_window_alipay_setting.h"
#include "app_window_alipay_bind.h"
#include "app_window_alipay_helper.h"
#include "app_window_alipay_startup.h"

#if (LCD_SIZE_WIDTH == 412)
#define ALIPAY_LIST_ITEM_W      352
#define ALIPAY_LIST_ITEM_H      100
#elif (LCD_SIZE_WIDTH == 466)
#define ALIPAY_LIST_ITEM_W      389         //pic_zhifubao_round_l_bar_info.width
#define ALIPAY_LIST_ITEM_H      113         //pic_zhifubao_round_l_bar_info.height
#else
#define ALIPAY_LIST_ITEM_W      320
#define ALIPAY_LIST_ITEM_H      100
#endif

static const gui_font_struct gui_alipay_menu_paycode_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_PAYCODE,
};

static const gui_font_struct gui_alipay_menu_setting_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_SETTING,
};

static const gui_font_struct gui_alipay_menu_helper_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_HELPER,
};

static const gui_image_struct gui_alipay_menu_code_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_zhifubao_code_info,
};

static const gui_image_struct gui_alipay_menu_setting_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_zhifubao_setting_info,
};

static const gui_image_struct gui_alipay_menu_helper_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_zhifubao_helper_info,
};

static const gui_image_struct gui_alipay_menu_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_zhifubao_round_l_bar_info,
};

enum
{
    ALIPAY_PAYCODE_ID = 10,
    ALIPAY_SETTING_ID,
    ALIPAY_HELPER_ID,
};

static const gui_widget_struct gui_alipay_widget_menu[] =
{
    // paycode
	{
		.id = ALIPAY_PAYCODE_ID,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = LCD_SIZE_HALF_HEIGHT-ALIPAY_LIST_ITEM_H*3/2,
		.width = LCD_SIZE_WIDTH,
		.height = ALIPAY_LIST_ITEM_H,
		.visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_bg,
	},
    {
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = (LCD_SIZE_WIDTH-ALIPAY_LIST_ITEM_W)/2 + 4,
        .y = LCD_SIZE_HALF_HEIGHT-ALIPAY_LIST_ITEM_H*3/2,
        .width = ALIPAY_LIST_ITEM_H,
        .height = ALIPAY_LIST_ITEM_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_code_icon,
    },
	{
		.type = TYPE_GUI_CONTROL_LABEL,
        .x = (LCD_SIZE_WIDTH-ALIPAY_LIST_ITEM_W)/2 + ALIPAY_LIST_ITEM_H,
        .y = LCD_SIZE_HALF_HEIGHT-ALIPAY_LIST_ITEM_H*3/2,
        .width = ALIPAY_LIST_ITEM_W-ALIPAY_LIST_ITEM_H-10,
		.height = ALIPAY_LIST_ITEM_H,
		.visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_paycode_text,
	},

    // setting
    {
        .id = ALIPAY_SETTING_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .y = LCD_SIZE_HALF_HEIGHT-ALIPAY_LIST_ITEM_H/2,
        .width = LCD_SIZE_WIDTH,
        .height = ALIPAY_LIST_ITEM_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_bg,
    },
    {
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = (LCD_SIZE_WIDTH-ALIPAY_LIST_ITEM_W)/2 + 4,
        .y = LCD_SIZE_HALF_HEIGHT-ALIPAY_LIST_ITEM_H/2,
        .width = ALIPAY_LIST_ITEM_H,
        .height = ALIPAY_LIST_ITEM_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_setting_icon,
    },
    {
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = (LCD_SIZE_WIDTH-ALIPAY_LIST_ITEM_W)/2 + ALIPAY_LIST_ITEM_H,
        .y = LCD_SIZE_HALF_HEIGHT-ALIPAY_LIST_ITEM_H/2,
        .width = ALIPAY_LIST_ITEM_W-ALIPAY_LIST_ITEM_H-10,
        .height = ALIPAY_LIST_ITEM_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_setting_text,
    },

    // helper
    {
        .id = ALIPAY_HELPER_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .y = LCD_SIZE_HALF_HEIGHT+ALIPAY_LIST_ITEM_H/2,
        .width = LCD_SIZE_WIDTH,
        .height = ALIPAY_LIST_ITEM_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_bg,
    },
    {
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = (LCD_SIZE_WIDTH-ALIPAY_LIST_ITEM_W)/2 + 4,
        .y = LCD_SIZE_HALF_HEIGHT+ALIPAY_LIST_ITEM_H/2,
        .width = ALIPAY_LIST_ITEM_H,
        .height = ALIPAY_LIST_ITEM_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_helper_icon,
    },
    {
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = (LCD_SIZE_WIDTH-ALIPAY_LIST_ITEM_W)/2 + ALIPAY_LIST_ITEM_H,
        .y = LCD_SIZE_HALF_HEIGHT+ALIPAY_LIST_ITEM_H/2,
        .width = ALIPAY_LIST_ITEM_W-ALIPAY_LIST_ITEM_H-10,
        .height = ALIPAY_LIST_ITEM_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_menu_helper_text,
    },
};

const gui_screen_struct gui_screen_alipay_menu =
{
	.children = gui_alipay_widget_menu,
	.child_num = countof(gui_alipay_widget_menu),
};


/*-----------------------------系统事件--------------------------------------*/
static unsigned char g_app_alipay_renter_flag;
static void app_window_alipay_menu_init(void *buf)
{
    SYS_DEBUG("app: alipay_menu_init");
    g_app_alipay_renter_flag = 0;
}

static void app_window_alipay_menu_load(void)
{
    SYS_DEBUG("app: alipay_menu_load");
}


static void app_window_alipay_menu_entry(void)
{
    if (g_app_alipay_renter_flag) {
        unsigned int sta = srv_alipay_get_bind_status();
        SYS_DEBUG("app: alipay_menu_entry(%d)", sta);
        if (sta != 2) {
            application_send_event(EVENT_GO_BACK, NULL);
        }
    }
}


static void app_window_alipay_menu_exit(void)
{
    SYS_DEBUG("app: alipay_menu_exit");
    g_app_alipay_renter_flag = 1;
}

static void app_window_alipay_menu_destroy(void)
{
    SYS_DEBUG("app: alipay_menu_destroy");
    g_app_alipay_renter_flag = 0;
}

static void app_window_alipay_menu_long_touch_handler(gui_click_struct *event)
{
    if (event->id == ALIPAY_PAYCODE_ID) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_qrcode, &app_window_alipay_menu);
    }
    else if (event->id == ALIPAY_SETTING_ID) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_setting, NULL);
    }
    else if (event->id == ALIPAY_HELPER_ID) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_helper, NULL);
    }
}


/*-----------------------------配置--------------------------------------*/
static const gui_touch_event_struct app_window_alipay_menu_touch_events[] =
{
    {.id = ALIPAY_PAYCODE_ID,  .click = app_window_alipay_menu_long_touch_handler},
    {.id = ALIPAY_SETTING_ID,  .click = app_window_alipay_menu_long_touch_handler},
    {.id = ALIPAY_HELPER_ID,   .click = app_window_alipay_menu_long_touch_handler}
};

const gui_window_struct app_window_alipay_menu =
{
	.screen = &gui_screen_alipay_menu,
	.init = app_window_alipay_menu_init,
	.load = app_window_alipay_menu_load,
	.entry = app_window_alipay_menu_entry,
	.exit = app_window_alipay_menu_exit,
	.destroy = app_window_alipay_menu_destroy,

	.touch_event_num = countof(app_window_alipay_menu_touch_events),
	.touch_events = app_window_alipay_menu_touch_events,
};




// 功能列表入口
void app_window_alipay_entry(app_info_struct* app_info)
{
    if (srv_aliyun_is_actived()) {
        if (srv_alipay_systime_must_sync()) {
            window_pop_info_struct pop_info = {0};
            pop_info.str_id = STRING_ALIPAY_SYNC_TIME;
            application_send_event(EVENT_GUI_POP_WINDOW, &pop_info);
            return;
        }

    #if 1
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_startup, (void*)&app_window_alipay_menu);
    #else
        unsigned int sta = srv_alipay_get_bind_status();
        SYS_DEBUG("app: alipay_entry(%d)", sta);
        if (sta == 2) {
            // ok
            application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_menu, NULL);
        }
        else {
            // 开始绑定
            application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_bind, (void*)&app_window_alipay_menu);
        }
    #endif
    }
    else {
        window_pop_info_struct pop_info = {0};
        if (2 == srv_aliyun_get_ble_appstatus()) {
            // 已经连接app的情况下，还是没有激活设备，则提示 “提示该设备存在安全风险，请联系设备厂商提供技术支持”
            pop_info.str_id = STRING_ALIPAY_APPLINKED;
        }
        else {
            // 提示 “请用G-MOVE APP绑定设备后才可使用”
            pop_info.str_id = STRING_ALIPAY_APPACTIVE;
        }
        application_send_event(EVENT_GUI_POP_WINDOW, &pop_info);
    }
}

// 快捷方式入口
void app_window_alipay_shortcut(void)
{
    if (srv_aliyun_is_actived()) {
        if (srv_alipay_systime_must_sync()) {
            window_pop_info_struct pop_info = {0};
            pop_info.str_id = STRING_ALIPAY_SYNC_TIME;
            application_send_event(EVENT_GUI_POP_WINDOW, &pop_info);
            return;
        }

    #if 1
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_startup, NULL);
    #else
        unsigned int sta = srv_alipay_get_bind_status();
        SYS_DEBUG("app: alipay_shortcut(%d)", sta);
        if (sta == 2) {
            // 显示支付码
            application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_qrcode, NULL);
        }
        else {
            // 开始绑定
            application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_bind, NULL);
        }
    #endif
    }
    else {
        window_pop_info_struct pop_info = {0};
        if (2 == srv_aliyun_get_ble_appstatus()) {
            // 已经连接app的情况下，还是没有激活设备，则提示 “提示该设备存在安全风险，请联系设备)商支持”
            pop_info.str_id = STRING_ALIPAY_APPLINKED;
        }
        else {
            // 提示 “请用G-MOVE APP绑定设备后才可使用”
            pop_info.str_id = STRING_ALIPAY_APPACTIVE;
        }
        application_send_event(EVENT_GUI_POP_WINDOW, &pop_info);
    }
}


static unsigned char g_alipay_bl_level;
void app_window_alipay_backlight_set(void)
{
    g_alipay_bl_level = oled_backlight_setValueUp(80);          // >= 80
    oled_backlight_set();
}

void app_window_alipay_backlight_reset(void)
{
    oled_backlight_setValue(g_alipay_bl_level);
    oled_backlight_set();
}

#else
// 功能列表入口
void app_window_alipay_entry(app_info_struct* app_info)
{

}

// 快捷方式入口
void app_window_alipay_shortcut(void)
{

}

#endif


