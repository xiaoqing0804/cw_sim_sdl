
#include "sys_init.h"
#include "bsp_includes.h"
#include "data_common.h"
#include "data_receive_package.h"

#include "qrencode.h"
#include "srv_alipay.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#if TCFG_PAY_ALIOS_ENABLE
#include "app_window_alipay_barcode.h"
#include "app_window_alipay_qrcode.h"
#include "app_window_alipay_menu.h"
#include "app_window_alipay_common.h"

#define ALIPAY_QRCODE_BG_ID 9
#define ALIPAY_QRCODE_ID    10
#define ALIPAY_DOTS_ID      11
#define ALIPAY_SWT_ID       12
#define ALIPAY_QRCODE_ICON  13
#define ALIPAY_ROUND_ID     15


static const gui_canvas_struct gui_alipay_dots[] =
{
    {
        .type = TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL,
        .penSize = 4,
        .penColor = COLOR_RGB(128, 128, 128),
        .canvas.circle.cx = LCD_SIZE_HALF_WIDTH - PAYCODE_SWT_DOT_R*2,
        .canvas.circle.cy = PAYCODE_SWT_DOT_Y,
        .canvas.circle.r  = PAYCODE_SWT_DOT_R,
    },
    {
        .type = TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL,
        .penSize = 4,
        .penColor = COLOR_RGB(255, 255, 255),
        .canvas.circle.cx = LCD_SIZE_HALF_WIDTH + PAYCODE_SWT_DOT_R*2,
        .canvas.circle.cy = PAYCODE_SWT_DOT_Y,
        .canvas.circle.r  = PAYCODE_SWT_DOT_R,
    }
};


static const gui_font_struct gui_alipay_title =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_PAYCODE,
};

static const gui_font_struct gui_alipay_show_swtcode =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_SWT_BARCODE,
};


static const gui_canvas_struct gui_alipay_scr_bg =
{
    .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
    .penSize = 5,
    .penColor = ALIPAY_COLOR_BG,
    .canvas.rect.x0 = 0,
    .canvas.rect.y0 = 0,
    .canvas.rect.x1 = LCD_SIZE_WIDTH-1,
    .canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
};


static gui_canvas_struct gui_alipay_qrcode_bg =
{
    .id = 1,
    .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
    .penSize = 5,
    .penColor = COLOR_RGB(255, 255, 255),
    .canvas.rect.x0 = QRCODE_X_POS - QRCODE_MARGIN,
    .canvas.rect.y0 = QRCODE_Y_POS - QRCODE_MARGIN,
    .canvas.rect.x1 = QRCODE_X_POS + QRCODE_SIZE+QRCODE_MARGIN-1,
    .canvas.rect.y1 = QRCODE_Y_POS + QRCODE_SIZE+QRCODE_MARGIN-1,
};

static gui_canvas_struct gui_alipay_code_round[] =
{
    {
        .id = 1,
        .type = TYPE_GUI_DRAW_SHAPE_ARC,
        .penSize = ALIPAY_ROUND_PEN_SIZE,
        .penColor = ALIPAY_COLOR_BG,
        .AA = 1,
        .canvas.arc.cx = QRCODE_X_POS + QRCODE_SIZE+QRCODE_MARGIN-1 - ALIPAY_ROUND_R0,
        .canvas.arc.cy = QRCODE_Y_POS - QRCODE_MARGIN + ALIPAY_ROUND_R0,
        .canvas.arc.r  = ALIPAY_ROUND_R0+ALIPAY_ROUND_PEN_SIZE,
        .canvas.arc.Angle0 = 0,
        .canvas.arc.Angle1 = 90,
    },
    {
        .id = 2,
        .type = TYPE_GUI_DRAW_SHAPE_ARC,
        .penSize = ALIPAY_ROUND_PEN_SIZE,
        .penColor = ALIPAY_COLOR_BG,
        .AA = 1,
        .canvas.arc.cx = QRCODE_X_POS - QRCODE_MARGIN + ALIPAY_ROUND_R0,
        .canvas.arc.cy = QRCODE_Y_POS - QRCODE_MARGIN + ALIPAY_ROUND_R0,
        .canvas.arc.r  = ALIPAY_ROUND_R0+ALIPAY_ROUND_PEN_SIZE,
        .canvas.arc.Angle0 = 90,
        .canvas.arc.Angle1 = 180,
    },
    {
        .id = 3,
        .type = TYPE_GUI_DRAW_SHAPE_ARC,
        .penSize = ALIPAY_ROUND_PEN_SIZE,
        .penColor = ALIPAY_COLOR_BG,
        .AA = 1,
        .canvas.arc.cx = QRCODE_X_POS - QRCODE_MARGIN + ALIPAY_ROUND_R0,
        .canvas.arc.cy = QRCODE_Y_POS + QRCODE_SIZE+QRCODE_MARGIN-1 - ALIPAY_ROUND_R0,
        .canvas.arc.r  = ALIPAY_ROUND_R0+ALIPAY_ROUND_PEN_SIZE,
        .canvas.arc.Angle0 = 180,
        .canvas.arc.Angle1 = 270,
    },
    {
        .id = 4,
        .type = TYPE_GUI_DRAW_SHAPE_ARC,
        .penSize = ALIPAY_ROUND_PEN_SIZE,
        .penColor = ALIPAY_COLOR_BG,
        .AA = 1,
        .canvas.arc.cx = QRCODE_X_POS + QRCODE_SIZE+QRCODE_MARGIN-1 - ALIPAY_ROUND_R0,
        .canvas.arc.cy = QRCODE_Y_POS + QRCODE_SIZE+QRCODE_MARGIN-1 - ALIPAY_ROUND_R0,
        .canvas.arc.r  = ALIPAY_ROUND_R0+ALIPAY_ROUND_PEN_SIZE,
        .canvas.arc.Angle0 = -90,
        .canvas.arc.Angle1 = 0,
    }
};


static const gui_qr_code_struct gui_alipay_qrcode =
{
	.type = TYPE_GUI_DRAW_QR_CODE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .width = QRCODE_SIZE,
	.string = "",
};

static const gui_image_struct gui_alipay_qrcode_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_zhifubao_logo_info,
};


static const gui_widget_struct gui_alipay_widget_qrcode[] =
{
    {
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_scr_bg,
    },

    {
        .id = ALIPAY_DOTS_ID,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 0,
        .child_num = countof(gui_alipay_dots),
        .children = &gui_alipay_dots,
    },

    {
        .id = ALIPAY_QRCODE_BG_ID,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_qrcode_bg,
    },

    {
        .id = ALIPAY_ROUND_ID,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = countof(gui_alipay_code_round),
        .children = &gui_alipay_code_round,
    },

	{
		.type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = QRCODE_TITLE_TEXT_Y,
		.width = LCD_SIZE_WIDTH,
		.height = QRCODE_TITLE_TEXT_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_alipay_title,
	},

	{
		.id = ALIPAY_QRCODE_ID,
		.type = TYPE_GUI_CONTROL_QR_CODE,
		.x = QRCODE_X_POS,
		.y = QRCODE_Y_POS,
		.width = QRCODE_SIZE,
		.height = QRCODE_SIZE,
		.visible= 1,
		.child_num = 1,
		.children = &gui_alipay_qrcode,
	},

    {
        .id = ALIPAY_QRCODE_ICON,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = QRCODE_X_POS,
        .y = QRCODE_Y_POS,
        .width = QRCODE_SIZE,
        .height = QRCODE_SIZE,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_qrcode_icon,
    },

    {
        .id = ALIPAY_SWT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = PAYCODE_SWT_TEXT_Y,
        .width = LCD_SIZE_WIDTH,
        .height = QRCODE_TITLE_TEXT_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_show_swtcode,
    },
};

static const gui_screen_struct gui_alipay_screen_qrcode =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_alipay_widget_qrcode,
	.child_num = countof(gui_alipay_widget_qrcode),
};

/*-----------------------------系统事件--------------------------------------*/
static unsigned char g_alipay_qr_enter_flag;
static void app_window_alipay_qrcode_init(void *buf)
{
    g_alipay_qr_enter_flag = ((buf == NULL) ? 0 : 1);
    if (srv_alipay_start_pay() == -1) {
        application_send_event(EVENT_GO_BACK, NULL);

        window_pop_info_struct pop_info = {0};
        pop_info.str_id = STRING_ALIPAY_BIND_FAIL;
        pop_info.param_p = &pic_zhifubao_no_info;
        application_send_event(EVENT_GUI_POP_WINDOW, &pop_info);
    }
}

static void app_window_alipay_qrcode_load(void)
{
    gui_box_struct* box;

    unsigned char*  payCode = srv_alipay_get_code();
    unsigned int    isEmpty = ((strlen(payCode) == 0) ? 1 : 0);
	box = gui_surface_get_box(&gui_alipay_screen_qrcode, ALIPAY_QRCODE_ID);
	if(box != NULL) {
        if (isEmpty) {
            box->visible = 0;       // 没有支付码时，显示空白.
        }
        else {
            box->visible = 1;
            gui_surface_box_qrcode_change(box, payCode);
        }
    }

    // 按照条形码的实际宽度，调整背景的宽度...
    box = gui_surface_get_box(&gui_alipay_screen_qrcode, ALIPAY_QRCODE_BG_ID);
    if (box != NULL) {
        unsigned int    qr_w;
        unsigned short  scale, cx, cy;

        qr_w = isEmpty ? 100 : QRcode_get_width(payCode, QR_ECLEVEL_H);
        scale = QRCODE_SIZE / qr_w;
        scale = scale <= 1 ? 1 : scale;
        qr_w = qr_w * scale;

        cx = QRCODE_X_POS + QRCODE_SIZE/2;
        cy = QRCODE_Y_POS + QRCODE_SIZE/2;
        gui_alipay_qrcode_bg.canvas.rect.x0 = cx-qr_w/2 - QRCODE_MARGIN;
        gui_alipay_qrcode_bg.canvas.rect.x1 = cx+qr_w/2 + QRCODE_MARGIN - 1;
        gui_alipay_qrcode_bg.canvas.rect.y0 = cy-qr_w/2 - QRCODE_MARGIN;
        gui_alipay_qrcode_bg.canvas.rect.y1 = cy+qr_w/2 + QRCODE_MARGIN - 1;
        gui_surface_box_canvas_flush(box, 1);
    }

    box = gui_surface_get_box(&gui_alipay_screen_qrcode, ALIPAY_ROUND_ID);
    if (box != NULL) {
        gui_alipay_code_round[0].canvas.arc.cx = gui_alipay_qrcode_bg.canvas.rect.x1 - ALIPAY_ROUND_R0;
        gui_alipay_code_round[0].canvas.arc.cy = gui_alipay_qrcode_bg.canvas.rect.y0 + ALIPAY_ROUND_R0;
        gui_alipay_code_round[1].canvas.arc.cx = gui_alipay_qrcode_bg.canvas.rect.x0 + ALIPAY_ROUND_R0;
        gui_alipay_code_round[1].canvas.arc.cy = gui_alipay_qrcode_bg.canvas.rect.y0 + ALIPAY_ROUND_R0;
        gui_alipay_code_round[2].canvas.arc.cx = gui_alipay_qrcode_bg.canvas.rect.x0 + ALIPAY_ROUND_R0;
        gui_alipay_code_round[2].canvas.arc.cy = gui_alipay_qrcode_bg.canvas.rect.y1 - ALIPAY_ROUND_R0;
        gui_alipay_code_round[3].canvas.arc.cx = gui_alipay_qrcode_bg.canvas.rect.x1 - ALIPAY_ROUND_R0;
        gui_alipay_code_round[3].canvas.arc.cy = gui_alipay_qrcode_bg.canvas.rect.y1 - ALIPAY_ROUND_R0;
        gui_surface_box_canvas_flush(box, 1);
        gui_surface_box_canvas_flush(box, 2);
        gui_surface_box_canvas_flush(box, 3);
        gui_surface_box_canvas_flush(box, 4);
    }

    box = gui_surface_get_box(&gui_alipay_screen_qrcode, ALIPAY_QRCODE_ICON);
    if (box != NULL) box->visible = (isEmpty ? 0 : 1);

    box = gui_surface_get_box(&gui_alipay_screen_qrcode, ALIPAY_DOTS_ID);
    if (box != NULL) {
        box->visible = g_alipay_qr_enter_flag;
    }
    box = gui_surface_get_box(&gui_alipay_screen_qrcode, ALIPAY_SWT_ID);
    if (box != NULL) {
        box->visible = g_alipay_qr_enter_flag;
    }
}


static void app_window_alipay_qrcode_entry(void)
{
    app_window_alipay_backlight_set();
    application_lift_wrist_disable();
    application_open_act_timer(APPLICATION_TIMER_ACT_3, 60000);
}


static void app_window_alipay_qrcode_exit(void)
{
    application_lift_wrist_enable();
    app_window_alipay_backlight_reset();
    application_close_act_timer(APPLICATION_TIMER_ACT_3);
}

static void app_window_alipay_qrcode_destroy(void)
{
    srv_alipay_cancel_pay();
    g_alipay_qr_enter_flag = 0;
}



/*-----------------------------响应事件--------------------------------------*/
static void app_window_alipay_qrcode_handler(void* buf)
{
    app_window_alipay_qrcode_load();
    gui_surface_commit();
}

static void app_window_alipay_qrcode_resume_handler(void* buf)
{
    app_window_alipay_qrcode_load();
}

static void app_window_alipay_qrcode_timer_handler(void* buf)
{
    //application_go_back();
}

static void app_window_alipay_key_handler(void* buf)
{
    application_go_back();
}

static void app_window_alipay_rolkey_handler(void* buf)
{
    void* param = NULL;
    if (g_alipay_qr_enter_flag) {
        param = &app_window_alipay_qrcode;
    }
    application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_barcode, param);
}

static const app_window_event_struct app_window_alipay_qrcode_static_events[] =
{
    {.id = EVENT_ALIPAY_CODE_CHANGED, .handler = app_window_alipay_qrcode_handler},
    {.id = EVENT_GUI_RESUMED,         .handler = app_window_alipay_qrcode_resume_handler},
    {.id = EVENT_ACT,                 .handler = app_window_alipay_qrcode_timer_handler},
    {.id = EVENT_KEY2_SHORT,          .handler = app_window_alipay_key_handler},
    //{.id = EVENT_KEY1_SHORT,          .handler = app_window_alipay_key_handler},
    {.id = EVENT_ROLKEY,              .handler = app_window_alipay_rolkey_handler},
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_ALL},
};


static void app_window_alipay_qrcode_click_handler(gui_click_struct *event)
{
    if (g_alipay_qr_enter_flag) {
        //application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_barcode, &app_window_alipay_qrcode);
    }
}

static unsigned char app_window_alipay_qrcode_touch_handler(gui_touch_struct *envent)
{
    void* param = NULL;
    if (g_alipay_qr_enter_flag) {
        param = &app_window_alipay_qrcode;
    }

	if(envent->type == TOUCH_EVENT_TYPE_UP)
	{
		if(envent->direction == DIRECTION_TYPE_LEFT)
		{
		    srv_alipay_reflash_paycode();
		    application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_barcode, param);
		}
		else if(envent->direction == DIRECTION_TYPE_RIGHT)
		{
		    //if (!g_alipay_qr_enter_flag) {
		        srv_alipay_reflash_paycode();
                application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_barcode, param);
            //}
		}
		return 1;
	}
	else if(envent->type == TOUCH_EVENT_TYPE_DOWN)
	{
		return 1;
	}
	else if(envent->type == TOUCH_EVENT_TYPE_MOVE)
	{
		return 1;
	}

	return 0;
}


static const gui_touch_event_struct app_window_alipay_qrcode_touch_events[] =
{
    {.id = ALIPAY_QRCODE_ID,  .click = app_window_alipay_qrcode_click_handler},
    {.id = 0xFFFF,            .touch = app_window_alipay_qrcode_touch_handler},
};


/*-----------------------------配置--------------------------------------*/
static const gui_window_config_struct app_window_alipay_qrcode_cfg =
{
    .enable_touch = 1,
};


const gui_window_struct app_window_alipay_qrcode =
{
	.screen = &gui_alipay_screen_qrcode,
    .config = &app_window_alipay_qrcode_cfg,
	.init = app_window_alipay_qrcode_init,
	.load = app_window_alipay_qrcode_load,
	.entry = app_window_alipay_qrcode_entry,
	.exit = app_window_alipay_qrcode_exit,
	.destroy = app_window_alipay_qrcode_destroy,

	.event_num = countof(app_window_alipay_qrcode_static_events),
    .events = app_window_alipay_qrcode_static_events,

	.touch_event_num = countof(app_window_alipay_qrcode_touch_events),
	.touch_events = app_window_alipay_qrcode_touch_events,
};

#endif
