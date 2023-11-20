
#include "sys_init.h"
#include "bsp_includes.h"
#include "data_common.h"
#include "data_receive_package.h"

#include "barcode_code128.h"
#include "srv_alipay.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#if TCFG_PAY_ALIOS_ENABLE
#include "app_window_alipay_qrcode.h"
#include "app_window_alipay_barcode.h"
#include "app_window_alipay_menu.h"
#include "app_window_alipay_common.h"

#define ALIPAY_BARCODE_BG_ID 9
#define ALIPAY_BARCODE_ID    10
#define ALIPAY_BARNUMBER_ID  11
#define ALIPAY_DOTS_ID      12
#define ALIPAY_SWT_ID       13
#define ALIPAY_ROUND_ID     15

#define BARCODE_X_POS       ((LCD_SIZE_WIDTH-BARCODE_SIZE_W)/2)
#define BARCODE_Y_POS       ((LCD_SIZE_HEIGHT-BARCODE_SIZE_H)/2)


static const gui_canvas_struct gui_alipay_dots[] =
{
    {
        .type = TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL,
        .penSize = 4,
        .penColor = COLOR_RGB(255, 255, 255),
        .canvas.circle.cx = LCD_SIZE_HALF_WIDTH - PAYCODE_SWT_DOT_R*2,
        .canvas.circle.cy = PAYCODE_SWT_DOT_Y,
        .canvas.circle.r  = PAYCODE_SWT_DOT_R,
    },
    {
        .type = TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL,
        .penSize = 4,
        .penColor = COLOR_RGB(128, 128, 128),
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

static gui_canvas_struct gui_alipay_barcode_bg =        // 要是可变宽度 .....
{
    .id = 1,
    .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
    .penSize = 5,
    .penColor = COLOR_RGB(255, 255, 255),
    .canvas.rect.x0 = BARCODE_X_POS-BARCODE_MARGIN,
    .canvas.rect.y0 = BARCODE_Y_POS-BARCODE_MARGIN_V,
    .canvas.rect.x1 = BARCODE_X_POS+BARCODE_SIZE_W+BARCODE_MARGIN-1,
    .canvas.rect.y1 = BARCODE_Y_POS+BARCODE_SIZE_H+BARCODE_MARGIN_V-1,
};

static gui_canvas_struct gui_alipay_code_round[] =
{
    {
        .id = 1,
        .type = TYPE_GUI_DRAW_SHAPE_ARC,
        .penSize = ALIPAY_ROUND_PEN_SIZE,
        .penColor = ALIPAY_COLOR_BG,
        .AA = 1,
        .canvas.arc.cx = BARCODE_X_POS+BARCODE_SIZE_W+BARCODE_MARGIN-1 - ALIPAY_ROUND_R0,
        .canvas.arc.cy = BARCODE_Y_POS-BARCODE_MARGIN_V + ALIPAY_ROUND_R0,
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
        .canvas.arc.cx = BARCODE_X_POS-BARCODE_MARGIN + ALIPAY_ROUND_R0,
        .canvas.arc.cy = BARCODE_Y_POS-BARCODE_MARGIN_V + ALIPAY_ROUND_R0,
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
        .canvas.arc.cx = BARCODE_X_POS-BARCODE_MARGIN + ALIPAY_ROUND_R0,
        .canvas.arc.cy = BARCODE_Y_POS+BARCODE_SIZE_H+BARCODE_MARGIN_V-1 - ALIPAY_ROUND_R0,
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
        .canvas.arc.cx = BARCODE_X_POS+BARCODE_SIZE_W+BARCODE_MARGIN-1 - ALIPAY_ROUND_R0,
        .canvas.arc.cy = BARCODE_Y_POS+BARCODE_SIZE_H+BARCODE_MARGIN_V-1 - ALIPAY_ROUND_R0,
        .canvas.arc.r  = ALIPAY_ROUND_R0+ALIPAY_ROUND_PEN_SIZE,
        .canvas.arc.Angle0 = -90,
        .canvas.arc.Angle1 = 0,
    }
};


static const gui_bar_code_struct gui_alipay_barcode =
{
	.type = TYPE_GUI_DRAW_QR_CODE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.string = "",
};

static const gui_font_struct gui_alipay_number =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .auto_wrap = 1,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_20,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = " ",
};

static const gui_font_struct gui_alipay_show_swtcode =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_SWT_QRCODE,
};



static const gui_widget_struct gui_alipay_widget_barcode[] =
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
        .id = ALIPAY_BARCODE_BG_ID,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_barcode_bg,
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
        .y = BARCODE_TITLE_TEXT_Y,
		.width = LCD_SIZE_WIDTH,
		.height = BARCODE_TITLE_TEXT_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_alipay_title,
	},

	{
		.id = ALIPAY_BARCODE_ID,
		.type = TYPE_GUI_CONTROL_BAR_CODE_128C,
		.x = BARCODE_X_POS,
		.y = BARCODE_Y_POS,
		.width = BARCODE_SIZE_W,
		.height = BARCODE_SIZE_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_alipay_barcode,
	},

    {
        .id = ALIPAY_BARNUMBER_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = BARCODE_Y_POS+BARCODE_SIZE_H+BARCODE_MARGIN_V+10,
        .width = LCD_SIZE_WIDTH,
        .height = 20,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_number,
    },

    {
        .id = ALIPAY_SWT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = PAYCODE_SWT_TEXT_Y,
        .width = LCD_SIZE_WIDTH,
        .height = ALIPAY_TITLE_TEXT_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_show_swtcode,
    },
};

static const gui_screen_struct gui_alipay_screen_barcode =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_alipay_widget_barcode,
	.child_num = countof(gui_alipay_widget_barcode),
};


///////////////////////////////////////////////////////////////////////////////////////////
/*-----------------------------系统事件--------------------------------------*/
static unsigned char g_alipay_bar_enter_flag;

static void app_window_alipay_barcode_init(void *buf)
{
    g_alipay_bar_enter_flag = ((buf == NULL) ? 0 : 1);
    if (srv_alipay_start_pay() == -1) {
        application_send_event(EVENT_GO_BACK, NULL);

        window_pop_info_struct pop_info = {0};
        pop_info.str_id = STRING_ALIPAY_BIND_FAIL;
        pop_info.param_p = &pic_zhifubao_no_info;
        application_send_event(EVENT_GUI_POP_WINDOW, &pop_info);
    }
}

static void app_window_alipay_barcode_load(void)
{
    gui_box_struct* box;
    unsigned char*  payCode = srv_alipay_get_code();
    unsigned int    isEmpty = ((strlen(payCode) == 0) ? 1 : 0);
    printf("app: payCode = %s\n", payCode);

	box = gui_surface_get_box(&gui_alipay_screen_barcode, ALIPAY_BARCODE_ID);
	if (box!=NULL) {
        if (isEmpty) {
            box->visible = 0;   // 没有支付码时，显示空白.
        }
        else {
            box->visible = 1;
            gui_surface_box_barcode_change(box, payCode);
        }
    }
    // 按照条形码的实际宽度，调整背景的宽度...
	box = gui_surface_get_box(&gui_alipay_screen_barcode, ALIPAY_BARCODE_BG_ID);
    if (box != NULL) {
        unsigned int    bar_w;
        unsigned short  scale;

        bar_w = isEmpty ? 106 : barcode_code128_get_width(payCode);
        printf("app: bar_w = %d\n", bar_w);
        scale = BARCODE_SIZE_W / bar_w;
        scale = scale <= 1 ? 1 : scale;
        bar_w = bar_w * scale;

        gui_alipay_barcode_bg.canvas.rect.x0 = (LCD_SIZE_WIDTH-bar_w)/2 - BARCODE_MARGIN;
        gui_alipay_barcode_bg.canvas.rect.x1 = (LCD_SIZE_WIDTH+bar_w)/2 + BARCODE_MARGIN - 1;
        gui_surface_box_canvas_flush(box, 1);
    }
    box = gui_surface_get_box(&gui_alipay_screen_barcode, ALIPAY_ROUND_ID);
    if (box != NULL) {
        gui_alipay_code_round[0].canvas.arc.cx = gui_alipay_barcode_bg.canvas.rect.x1 - ALIPAY_ROUND_R0;
        gui_alipay_code_round[0].canvas.arc.cy = gui_alipay_barcode_bg.canvas.rect.y0 + ALIPAY_ROUND_R0;
        gui_alipay_code_round[1].canvas.arc.cx = gui_alipay_barcode_bg.canvas.rect.x0 + ALIPAY_ROUND_R0;
        gui_alipay_code_round[1].canvas.arc.cy = gui_alipay_barcode_bg.canvas.rect.y0 + ALIPAY_ROUND_R0;
        gui_alipay_code_round[2].canvas.arc.cx = gui_alipay_barcode_bg.canvas.rect.x0 + ALIPAY_ROUND_R0;
        gui_alipay_code_round[2].canvas.arc.cy = gui_alipay_barcode_bg.canvas.rect.y1 - ALIPAY_ROUND_R0;
        gui_alipay_code_round[3].canvas.arc.cx = gui_alipay_barcode_bg.canvas.rect.x1 - ALIPAY_ROUND_R0;
        gui_alipay_code_round[3].canvas.arc.cy = gui_alipay_barcode_bg.canvas.rect.y1 - ALIPAY_ROUND_R0;
        gui_surface_box_canvas_flush(box, 1);
        gui_surface_box_canvas_flush(box, 2);
        gui_surface_box_canvas_flush(box, 3);
        gui_surface_box_canvas_flush(box, 4);
    }

    box = gui_surface_get_box(&gui_alipay_screen_barcode, ALIPAY_BARNUMBER_ID);
    if (box != NULL && isEmpty == 0) {
        unsigned char temp[32];
        memcpy(&temp[0], payCode, 4);
        temp[4] = 0x20;
        memcpy(&temp[5], payCode+4, 4);
        temp[9] = 0x20;
        memcpy(&temp[10], payCode+8, 4);
        temp[14] = 0x20;
        strcpy(&temp[15], payCode+12);
        gui_surface_box_label_change_string(box, temp);
    }

    box = gui_surface_get_box(&gui_alipay_screen_barcode, ALIPAY_DOTS_ID);
    if (box != NULL) {
        box->visible = g_alipay_bar_enter_flag;
    }
    box = gui_surface_get_box(&gui_alipay_screen_barcode, ALIPAY_SWT_ID);
    if (box != NULL) {
        box->visible = g_alipay_bar_enter_flag;
    }
}


static void app_window_alipay_barcode_entry(void)
{
    app_window_alipay_backlight_set();
    application_lift_wrist_disable();
    application_open_act_timer(APPLICATION_TIMER_ACT_3, 60000);
}


static void app_window_alipay_barcode_exit(void)
{
    application_close_act_timer(APPLICATION_TIMER_ACT_3);
    application_lift_wrist_enable();
    app_window_alipay_backlight_reset();
}

static void app_window_alipay_barcode_destroy(void)
{
    srv_alipay_cancel_pay();
    g_alipay_bar_enter_flag = 0;
}



/*-----------------------------响应事件--------------------------------------*/
static void app_window_alipay_barcode_handler(void* buf)
{
    app_window_alipay_barcode_load();
    gui_surface_commit();
}

static void app_window_alipay_barcode_resume_handler(void* buf)
{
    app_window_alipay_barcode_load();
}

static void app_window_alipay_barcode_timer_handler(void* buf)
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
    if (g_alipay_bar_enter_flag) {
        param = &app_window_alipay_barcode;
    }
    application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_barcode, param);
}

static const app_window_event_struct app_window_alipay_barcode_static_events[] =
{
    {.id = EVENT_ALIPAY_CODE_CHANGED, .handler = app_window_alipay_barcode_handler},
    {.id = EVENT_GUI_RESUMED,         .handler = app_window_alipay_barcode_resume_handler},
    {.id = EVENT_ACT,                 .handler = app_window_alipay_barcode_timer_handler},
    {.id = EVENT_KEY2_SHORT,          .handler = app_window_alipay_key_handler},
    //{.id = EVENT_KEY1_SHORT,          .handler = app_window_alipay_key_handler},
    {.id = EVENT_ROLKEY,              .handler = app_window_alipay_rolkey_handler},
    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_ALL},
};


static void app_window_alipay_barcode_click_handler(gui_click_struct *event)
{
    if (g_alipay_bar_enter_flag) {
        //application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_qrcode, &app_window_alipay_barcode);
    }
}

static unsigned char app_window_alipay_barcode_touch_handler(gui_touch_struct *envent)
{
    void* param = NULL;
    if (g_alipay_bar_enter_flag) {
        param = &app_window_alipay_barcode;
    }

	if(envent->type == TOUCH_EVENT_TYPE_UP)
	{
		if(envent->direction == DIRECTION_TYPE_LEFT)
		{
		    //if (!g_alipay_bar_enter_flag) {
		        srv_alipay_reflash_paycode();
                application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_qrcode, param);
            //}
		}
		else if(envent->direction == DIRECTION_TYPE_RIGHT)
		{
		    srv_alipay_reflash_paycode();
		    application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_qrcode, param);
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

static const gui_touch_event_struct app_window_alipay_barcode_touch_events[] =
{
    {.id = ALIPAY_BARCODE_ID,   .click = app_window_alipay_barcode_click_handler},
    {.id = 0xFFFF,              .touch = app_window_alipay_barcode_touch_handler},
};


/*-----------------------------配置--------------------------------------*/
static const gui_window_config_struct app_window_alipay_barcode_cfg =
{
    .enable_touch = 1,
};

const gui_window_struct app_window_alipay_barcode =
{
	.screen = &gui_alipay_screen_barcode,
    .config = &app_window_alipay_barcode_cfg,
	.init = app_window_alipay_barcode_init,
	.load = app_window_alipay_barcode_load,
	.entry = app_window_alipay_barcode_entry,
	.exit = app_window_alipay_barcode_exit,
	.destroy = app_window_alipay_barcode_destroy,

	.event_num = countof(app_window_alipay_barcode_static_events),
    .events = app_window_alipay_barcode_static_events,

	.touch_event_num = countof(app_window_alipay_barcode_touch_events),
	.touch_events = app_window_alipay_barcode_touch_events,
};

#endif
