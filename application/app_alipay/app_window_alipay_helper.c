
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
#include "app_window_alipay_helper.h"
#include "app_window_alipay_menu.h"
#include "app_window_alipay_common.h"

#define ALIPAY_QRCODE_ID    10
#define ALIPAY_QRCODE_ICON  11
#define ALIPAY_QRCODE_BG_ID 12
#define ALIPAY_HELPER_ID    13




static const gui_font_struct gui_alipay_helper_title =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_APPHELPER,
};


static gui_canvas_struct gui_alipay_helper_bg[] =
{
    {
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
        .penSize = 5,
        .penColor = ALIPAY_COLOR_BG,
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_WIDTH-1,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
    },
    {
        .id = 10,
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
        .penSize = 5,
        .penColor = COLOR_RGB(255, 255, 255),
        .canvas.rect.x0 = QRCODE_X_POS - QRCODE_MARGIN,
        .canvas.rect.y0 = QRCODE_Y_POS - QRCODE_MARGIN,
        .canvas.rect.x1 = QRCODE_X_POS + QRCODE_SIZE+QRCODE_MARGIN-1,
        .canvas.rect.y1 = QRCODE_Y_POS + QRCODE_SIZE+QRCODE_MARGIN-1,
    },
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

static const gui_qr_code_struct gui_alipay_helper =
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


static const gui_widget_struct gui_alipay_widget_helper[] =
{
    {
        .id   = ALIPAY_QRCODE_BG_ID,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = countof(gui_alipay_helper_bg),
        .children = gui_alipay_helper_bg,
    },

	{
	    .id = ALIPAY_HELPER_ID,
		.type = TYPE_GUI_CONTROL_SCROLL_TEXT,
        .x = QRCODE_X_POS,//-10,
        .y = QRCODE_Y_POS-QRCODE_MARGIN-40,
        .width = LCD_SIZE_WIDTH-QRCODE_X_POS*2,//+20,
        .height = QRCODE_TITLE_TEXT_H,
		.visible= 1,
		.child_num = 1,
		.children = &gui_alipay_helper_title,
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
		.children = &gui_alipay_helper,
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
};

static const gui_screen_struct gui_alipay_screen_helper =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_alipay_widget_helper,
	.child_num = countof(gui_alipay_widget_helper),
};

/*-----------------------------系统事件--------------------------------------*/
static void app_window_alipay_helper_init(void *buf)
{
}

static void app_window_alipay_helper_load(void)
{
    gui_box_struct* box;
    unsigned char*  helperCode = srv_alipay_get_helper_code();
    unsigned int    isEmpty = ((strlen(helperCode) == 0) ? 1 : 0);

	box = gui_surface_get_box(&gui_alipay_screen_helper, ALIPAY_QRCODE_ID);
	if(box!=NULL) {
        if (isEmpty) {
            box->visible = 0;       // 没有支付码时，显示空白.
        }
        else {
            box->visible = 1;
            gui_surface_box_qrcode_change(box, helperCode);
        }
    }

    // 按照条形码的实际宽度，调整背景的宽度...
    box = gui_surface_get_box(&gui_alipay_screen_helper, ALIPAY_QRCODE_BG_ID);
    if (box != NULL) {
        unsigned int    qr_w;
        unsigned short  scale, cx, cy;

        qr_w = isEmpty ? 100 : QRcode_get_width(helperCode, QR_ECLEVEL_H);
        scale = QRCODE_SIZE / qr_w;
        scale = scale <= 1 ? 1 : scale;
        qr_w = qr_w * scale;

        // qr-bg
        cx = QRCODE_X_POS + QRCODE_SIZE/2;
        cy = QRCODE_Y_POS + QRCODE_SIZE/2;
        gui_alipay_helper_bg[1].canvas.rect.x0 = cx-qr_w/2 - QRCODE_MARGIN;
        gui_alipay_helper_bg[1].canvas.rect.x1 = cx+qr_w/2 + QRCODE_MARGIN - 1;
        gui_alipay_helper_bg[1].canvas.rect.y0 = cy-qr_w/2 - QRCODE_MARGIN;
        gui_alipay_helper_bg[1].canvas.rect.y1 = cy+qr_w/2 + QRCODE_MARGIN - 1;
        gui_surface_box_canvas_flush(box, 10);

        // rq-roun
        gui_alipay_helper_bg[2].canvas.arc.cx = gui_alipay_helper_bg[1].canvas.rect.x1 - ALIPAY_ROUND_R0;
        gui_alipay_helper_bg[2].canvas.arc.cy = gui_alipay_helper_bg[1].canvas.rect.y0 + ALIPAY_ROUND_R0;
        gui_alipay_helper_bg[3].canvas.arc.cx = gui_alipay_helper_bg[1].canvas.rect.x0 + ALIPAY_ROUND_R0;
        gui_alipay_helper_bg[3].canvas.arc.cy = gui_alipay_helper_bg[1].canvas.rect.y0 + ALIPAY_ROUND_R0;
        gui_alipay_helper_bg[4].canvas.arc.cx = gui_alipay_helper_bg[1].canvas.rect.x0 + ALIPAY_ROUND_R0;
        gui_alipay_helper_bg[4].canvas.arc.cy = gui_alipay_helper_bg[1].canvas.rect.y1 - ALIPAY_ROUND_R0;
        gui_alipay_helper_bg[5].canvas.arc.cx = gui_alipay_helper_bg[1].canvas.rect.x1 - ALIPAY_ROUND_R0;
        gui_alipay_helper_bg[5].canvas.arc.cy = gui_alipay_helper_bg[1].canvas.rect.y1 - ALIPAY_ROUND_R0;
        gui_surface_box_canvas_flush(box, 1);
        gui_surface_box_canvas_flush(box, 2);
        gui_surface_box_canvas_flush(box, 3);
        gui_surface_box_canvas_flush(box, 4);
    }

    box = gui_surface_get_box(&gui_alipay_screen_helper, ALIPAY_HELPER_ID);
    if (box != NULL) {
        box->y = gui_alipay_helper_bg[1].canvas.rect.y0 - 40;
    }
    box = gui_surface_get_box(&gui_alipay_screen_helper, ALIPAY_QRCODE_ICON);
    if (box != NULL) box->visible = (isEmpty ? 0 : 1);
}


static void app_window_alipay_helper_entry(void)
{
    app_window_alipay_backlight_set();
}


static void app_window_alipay_helper_exit(void)
{
    app_window_alipay_backlight_reset();
}

static void app_window_alipay_helper_destroy(void)
{
}

static void app_window_alipay_key_handler(void* buf)
{
    application_go_back();
}


/*-----------------------------响应事件--------------------------------------*/
static const app_window_event_struct app_window_alipay_helper_static_events[] =
{
    {.id = EVENT_KEY2_SHORT,          .handler = app_window_alipay_key_handler},
    //{.id = EVENT_KEY1_SHORT,          .handler = app_window_alipay_key_handler},
    {.id = EVENT_BL_TIMEOUT},       // 不允许灭屏 ...
};


/*-----------------------------配置--------------------------------------*/
const gui_window_struct app_window_alipay_helper =
{
	.screen = &gui_alipay_screen_helper,
	.init = app_window_alipay_helper_init,
	.load = app_window_alipay_helper_load,
	.entry = app_window_alipay_helper_entry,
	.exit = app_window_alipay_helper_exit,
	.destroy = app_window_alipay_helper_destroy,

	.event_num = countof(app_window_alipay_helper_static_events),
    .events = app_window_alipay_helper_static_events,
};

#endif
