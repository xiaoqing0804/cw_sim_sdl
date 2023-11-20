
#include "sys_init.h"
#include "bsp_includes.h"
#include "math.h"

#include "feature_all.h"
#include "data_common.h"
#include "data_receive_package.h"

#include "qrencode.h"
#include "srv_alipay.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#if TCFG_PAY_ALIOS_ENABLE
#include "app_window_alipay_bind.h"
#include "app_window_alipay_menu.h"
#include "app_window_alipay_qrcode.h"
#include "app_window_alipay_barcode.h"
#include "app_window_alipay_common.h"



// -----------------------------------------------------------------------------------------------
static const gui_font_struct gui_alipay_title =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(0, 0, 0),
    .size = SYS_FONT_MEDIUM,
    .scroll = 1,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_APPBIND,
};


static const gui_canvas_struct gui_alipay_qrcode_bg =
{
    .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
    .penSize = 5,
    .penColor = COLOR_RGB(255, 255, 255),
    .canvas.rect.x0 = 0,
    .canvas.rect.y0 = 0,
    .canvas.rect.x1 = LCD_SIZE_WIDTH-1, // QRCODE_SIZE+QRCODE_MARGIN*2-1,
    .canvas.rect.y1 = LCD_SIZE_HEIGHT-1, // QRCODE_SIZE+QRCODE_MARGIN*2-1,
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


// -----------------------------------------------------------------------------------------------
#define ALIPAY_BIND_CYC_R  80
static const gui_canvas_struct gui_alipay_cyc_bg =
{
    .type = TYPE_GUI_DRAW_SHAPE_CIRCLE,
    .penSize = 9,
    .penColor = COLOR_RGB(0, 0, 255),
    .canvas.circle.cx = LCD_SIZE_HALF_WIDTH,
    .canvas.circle.cy = LCD_SIZE_HALF_HEIGHT,
    .canvas.circle.r  = ALIPAY_BIND_CYC_R,
};

static gui_canvas_struct gui_alipay_cyc_ind =
{
    .type = TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL,
    .id   = 1,
    .penSize = 5,
    .penColor = COLOR_RGB(21, 119, 255),
    .canvas.circle.cx = LCD_SIZE_HALF_WIDTH + ALIPAY_BIND_CYC_R,
    .canvas.circle.cy = LCD_SIZE_HALF_HEIGHT,
    .canvas.circle.r  = 8,
};


static const gui_font_struct gui_alipay_bind_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .auto_wrap = 1,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_BINDING,
};

static gui_animation_frame_struct aui_alipay_bind_ani_frams[] =
{
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_02_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_03_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_05_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_07_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_09_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_11_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_13_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_15_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_17_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_19_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_21_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_23_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_25_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_27_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_29_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_31_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_33_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_35_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_37_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_39_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_41_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_43_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_45_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_47_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_49_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_51_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_53_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_55_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_57_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_59_info),
    PIC_ANIMATION_FRAME(70, 0, &pic_alipay_Gif_60_info),
};

static gui_animation_struct gui_alipay_bind_ani =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .frames_num = countof(aui_alipay_bind_ani_frams),
    .frames = aui_alipay_bind_ani_frams,
};



// -----------------------------------------------------------------------------------------------
static const gui_image_struct gui_alipay_term_cancel_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_zhifubao_op2_bg_info,
};
static const gui_font_struct gui_alipay_term_cancel_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(0, 0, 0),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_QUIT,
};

static const gui_image_struct gui_alipay_term_ok_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_zhifubao_op2_h_bg_info,
};
static const gui_font_struct gui_alipay_term_ok_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_REBIND,
};

static const gui_font_struct gui_alipay_term_info_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .auto_wrap = 1,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_TOP),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_TOP),
    .space_y    = 10,
    .color = COLOR_RGB(150, 150, 150),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_BIND_ERR,
};

static const gui_font_struct gui_alipay_term_title_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_BIND_TERM,
};




// -----------------------------------------------------------------------------------------------
enum
{
    ALIPAY_QRCODE_ID = 10,
    ALIPAY_QRCODE_BG,
    ALIPAY_TITLE_TEXT,
    ALIPAY_QRCODE_ICON,

    ALIPAY_BIND_TEXT,
    ALIPAY_BIND_CYC_BG,
    ALIPAY_BIND_CYC_IND,
    ALIPAY_BIND_PROGRESS,

    ALIPAY_TERM_TITLE,
    ALIPAY_TERM_INFO,
    ALIPAY_TERM_C_BG,
    ALIPAY_TERM_CANCEL,
    ALIPAY_TERM_O_BG,
    ALIPAY_TERM_OK,
};

static const gui_widget_struct gui_alipay_widget_bind[] =
{
    // flag: 0-qr-code -------------------------------
    {
        .id = ALIPAY_QRCODE_BG,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .x = 0, // QRCODE_X_POS - QRCODE_MARGIN,
        .y = 0, // QRCODE_Y_POS - QRCODE_MARGIN,
        .width = LCD_SIZE_WIDTH, // QRCODE_SIZE + QRCODE_MARGIN*2,
        .height = LCD_SIZE_HEIGHT, // QRCODE_SIZE + QRCODE_MARGIN*2,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_qrcode_bg,
    },

    {
        .id = ALIPAY_TITLE_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 100,
        .y = QRCODE_TITLE_TEXT_Y,
        .width = LCD_SIZE_WIDTH-200,
        .height = QRCODE_TITLE_TEXT_H,
        .visible= 1,
        .child_num = 1,
        .clip =1,
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

    // ani
    {
        .id = ALIPAY_BIND_CYC_IND,
        .type = TYPE_GUI_CONTROL_ANIMATION,
        .x = (LCD_SIZE_WIDTH-ALIPAY_ANI_SIZE)/2,
        .y = (LCD_SIZE_HEIGHT-ALIPAY_ANI_SIZE)/2 - 20,
        .width = ALIPAY_ANI_SIZE,
        .height = ALIPAY_ANI_SIZE,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_bind_ani,
    },
    {
        .id = ALIPAY_BIND_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = (LCD_SIZE_HEIGHT-ALIPAY_ANI_SIZE)/2 + ALIPAY_ANI_SIZE + 10,
        .width = LCD_SIZE_WIDTH,
        .height = ALIPAY_TITLE_TEXT_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_bind_text,
    },


    // flag: 2-user-term -------------------------------
    {
        .id = ALIPAY_TERM_TITLE,
        .type = TYPE_GUI_CONTROL_SCROLL_TEXT,
        .y = ALIPAY_TITLE_TEXT_Y_POS,
        .width = LCD_SIZE_WIDTH,
        .height = ALIPAY_TITLE_TEXT_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_term_title_text,
    },

    {
        .id = ALIPAY_TERM_INFO,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = ALIPAY_INFO_TEXT_X_POS,
        .y = ALIPAY_INFO_TEXT_Y_POS,
        .width = LCD_SIZE_WIDTH - ALIPAY_INFO_TEXT_X_POS*2,
        .height = ALIPAY_INFO_TEXT_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_term_info_text,
    },

    {
        .id = ALIPAY_TERM_C_BG,     // quit
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = LCD_SIZE_HALF_WIDTH - ALIPAY_OP2_BAR_W - ALIPAY_OP2_BAR_GAP/2,
        .y = ALIPAY_OP2_BAR_Y_POS,
        .width = ALIPAY_OP2_BAR_W,
        .height = ALIPAY_OP2_BAR_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_term_cancel_bg,
    },
    {
        .id = ALIPAY_TERM_CANCEL,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = LCD_SIZE_HALF_WIDTH - ALIPAY_OP2_BAR_W - ALIPAY_OP2_BAR_GAP/2,
        .y = ALIPAY_OP2_BAR_Y_POS,
        .width = ALIPAY_OP2_BAR_W,
        .height = ALIPAY_OP2_BAR_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_term_cancel_text,
    },

    {
        .id = ALIPAY_TERM_O_BG,     // continue
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = LCD_SIZE_HALF_WIDTH + ALIPAY_OP2_BAR_GAP/2,
        .y = ALIPAY_OP2_BAR_Y_POS,
        .width = ALIPAY_OP2_BAR_W,
        .height = ALIPAY_OP2_BAR_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_term_ok_bg,
    },
    {
        .id = ALIPAY_TERM_OK,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = LCD_SIZE_HALF_WIDTH + ALIPAY_OP2_BAR_GAP/2,
        .y = ALIPAY_OP2_BAR_Y_POS,
        .width = ALIPAY_OP2_BAR_W,
        .height = ALIPAY_OP2_BAR_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_term_ok_text,
    },

};

static const gui_screen_struct gui_alipay_screen_bind =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_alipay_widget_bind,
	.child_num = countof(gui_alipay_widget_bind),
};

/*-----------------------------系统事件--------------------------------------*/
static unsigned short g_alipay_bind_proc;
static unsigned char g_alipay_bind_flag;        // 0: qr-code; 1: binding; 2: user-term
static unsigned char g_alipay_bind_flag_bak;
static unsigned char g_alipay_bind_enter_flag;  // 0: shortcut;  1: menu

#define MY_PII   (-3.1415926f)

static void app_window_alipay_bind_update_qrcode(void)
{
	gui_box_struct* box;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TITLE_TEXT);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_BG);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_ID);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_ICON);
    if (box != NULL) box->visible = 1;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_BG);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_IND);
    if (box != NULL) { box->visible = 0;
                       gui_surface_control_animation_stop(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_IND);
    }
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_TEXT);
    if (box != NULL) box->visible = 0;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_TITLE);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_INFO);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_C_BG);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_CANCEL);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_O_BG);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_OK);
    if (box != NULL) box->visible = 0;
}

static void app_window_alipay_bind_update_process(void)
{
	gui_box_struct* box;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TITLE_TEXT);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_BG);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_ID);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_ICON);
    if (box != NULL) box->visible = 0;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_BG);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_IND);
    if (box != NULL) { box->visible = 1;
                       gui_surface_control_animation_start(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_IND);
    }
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_TEXT);
    if (box != NULL) box->visible = 1;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_TITLE);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_INFO);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_C_BG);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_CANCEL);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_O_BG);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_OK);
    if (box != NULL) box->visible = 0;
}

static void app_window_alipay_bind_update_term(void)
{
	gui_box_struct* box;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TITLE_TEXT);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_BG);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_ID);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_ICON);
    if (box != NULL) box->visible = 0;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_BG);
    if (box != NULL) box->visible = 0;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_IND);
    if (box != NULL) { box->visible = 0;
                       gui_surface_control_animation_stop(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_IND);
    }
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_TEXT);
    if (box != NULL) box->visible = 0;

    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_TITLE);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_INFO);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_C_BG);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_CANCEL);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_O_BG);
    if (box != NULL) box->visible = 1;
    box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_TERM_OK);
    if (box != NULL) box->visible = 1;
}


//--------------------------------------------------------------------------------------------------------
static void app_window_alipay_bind_init(void *buf)
{
    g_alipay_bind_flag = 0;
    g_alipay_bind_flag_bak = 0;
    g_alipay_bind_proc = 0;
    g_alipay_bind_enter_flag = ((buf == NULL) ? 0 : 1);
    SYS_DEBUG("app: alipay_bind_init(%d)", g_alipay_bind_enter_flag);

    srv_alipay_start_bind();
}

static void app_window_alipay_bind_load(void)
{
    gui_box_struct* box;

    SYS_DEBUG("app: alipay_bind_load()");

    // prepare qr-code
    unsigned char* payCode = srv_alipay_get_code();
    gui_box_struct* qr = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_QRCODE_ID);
    if (qr != NULL && payCode != NULL) gui_surface_box_qrcode_change(qr, payCode);
    app_window_alipay_bind_update_qrcode();
}


static void app_window_alipay_bind_entry(void)
{
    SYS_DEBUG("app: alipay_bind_entry()");
    app_window_alipay_backlight_set();
}


static void app_window_alipay_bind_exit(void)
{
    SYS_DEBUG("app: alipay_bind_exit()");

    app_window_alipay_backlight_reset();
    srv_alipay_cancel_bind(0);
    application_close_act_timer(APPLICATION_TIMER_ACT_3);
}

static void app_window_alipay_bind_destroy(void)
{
    SYS_DEBUG("app: alipay_bind_destroy()");
}



/*-----------------------------响应事件--------------------------------------*/
static int  app_window_alipay_bind_ok_pop_cb(void)
{
    SYS_DEBUG("app: alipay_bind_ok, callback, %d", g_alipay_bind_enter_flag);
    if (g_alipay_bind_enter_flag) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_menu, NULL);
    }
    else {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_qrcode, NULL);
    }
    return 1;
}

static int  app_window_alipay_bind_fail_pop_cb(void)
{
    void* param = ((g_alipay_bind_enter_flag == 0) ? NULL : &app_window_alipay_menu);
    SYS_DEBUG("app: alipay_bind_fail, callback");
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_alipay_bind, param);
    return 1;
}

static void app_window_alipay_bind_handler(void* buf)
{
    window_pop_info_struct pop_info = {0};
    unsigned int proc, sta = srv_alipay_get_bind_status();

    SYS_DEBUG("app: alipay_bind_handler(%d)", sta);
    switch(sta) {
        case 1:  // binding
            proc = srv_alipay_get_bind_process();
            SYS_DEBUG("app: proc = %d", proc);
            if ((proc >= 0) && (g_alipay_bind_flag < 1)) {
                g_alipay_bind_flag = 1;
                app_window_alipay_bind_update_process();
                gui_surface_commit();
                application_open_act_timer(APPLICATION_TIMER_ACT_3, 50);
            }
            break;
        case 2:  // bind ok
            srv_alipay_cancel_bind(1);
            pop_info.str_id = STRING_ALIPAY_BIND_OK;
            pop_info.param_p = &pic_zhifubao_yes_info,
            pop_info.time_out = 3000;   // 3s
            pop_info.onDestory = app_window_alipay_bind_ok_pop_cb;
            application_send_event(EVENT_GUI_POP_WINDOW, &pop_info);
            break;
        case 3: // bind fail
            srv_alipay_cancel_bind(1);
            app_window_alipay_bind_update_qrcode();
            pop_info.str_id = STRING_ALIPAY_BIND_FAIL;
            pop_info.param_p = &pic_zhifubao_no_info;
            pop_info.time_out = 7500;       // 8s
            pop_info.onDestory = app_window_alipay_bind_fail_pop_cb;
            application_send_event(EVENT_GUI_POP_WINDOW, &pop_info);
            break;
        default:    // idle
            break;
    }
}


static void app_window_alipay_timer_handler(void* buf)
{
    //SYS_DEBUG("app: alipay_timer_handler(%d)", g_alipay_bind_flag);
    if (g_alipay_bind_flag == 1) {
        /*
        gui_box_struct* box = gui_surface_get_box(&gui_alipay_screen_bind, ALIPAY_BIND_CYC_IND);
        if (box != NULL) {
            g_alipay_bind_proc += 10;
            if (g_alipay_bind_proc >= 360) {
                g_alipay_bind_proc = 0;
            }
            float angl = g_alipay_bind_proc * MY_PII / 180.0f;
            float fcos = cosf(angl);
            float fsin = sinf(angl);
            gui_alipay_cyc_ind.canvas.circle.cx = LCD_SIZE_HALF_WIDTH  + ALIPAY_BIND_CYC_R * fcos;
            gui_alipay_cyc_ind.canvas.circle.cy = LCD_SIZE_HALF_HEIGHT - ALIPAY_BIND_CYC_R * fsin;
            gui_surface_box_canvas_flush(box, 1);
            gui_surface_commit();
        }
        */
    }
}

static void app_window_alipay_key_handler(void* buf)
{
    if (g_alipay_bind_flag != 2) {
        application_close_act_timer(APPLICATION_TIMER_ACT_3);

        g_alipay_bind_flag_bak = g_alipay_bind_flag;
        g_alipay_bind_flag = 2;
        app_window_alipay_bind_update_term();
        gui_surface_commit();
    }
    else {
        //application_go_back();
    }
}

static void app_window_alipay_click_handler(gui_click_struct *event)
{
    SYS_DEBUG("app: alipay_click_handler(id: %d) flag=%d", event->id, g_alipay_bind_flag);
    if (g_alipay_bind_flag == 2) {
        if (event->id == ALIPAY_TERM_C_BG) {
            application_go_back();
        }
        else if (event->id == ALIPAY_TERM_O_BG) {
            g_alipay_bind_flag = g_alipay_bind_flag_bak;
            if (g_alipay_bind_flag < 1) {
                g_alipay_bind_flag = 0;
                application_close_act_timer(APPLICATION_TIMER_ACT_3);

                // show qr-code
                app_window_alipay_bind_update_qrcode();
                gui_surface_commit();
            }
            else {
                g_alipay_bind_flag = 1;
                app_window_alipay_bind_update_process();
                gui_surface_commit();

                application_open_act_timer(APPLICATION_TIMER_ACT_3, 100);
            }
        }
    }
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_alipay_bind_static_events[] =
{
    {.id = EVENT_ACT,                .handler = app_window_alipay_timer_handler},
    {.id = EVENT_ALIPAY_BIND_STATUS, .handler = app_window_alipay_bind_handler},
    {.id = EVENT_KEY2_SHORT,         .handler = app_window_alipay_key_handler},
    {.id = EVENT_KEY1_SHORT,         .handler = app_window_alipay_key_handler},
    {.id = EVENT_BL_TIMEOUT},       // 不允许灭屏 ...
    {.id = EVENT_ALL},              // 不允许灭屏 ...
};

static const gui_touch_event_struct app_window_alipay_bind_touch_events[] =
{
    {.id = ALIPAY_TERM_C_BG,        .click = app_window_alipay_click_handler},
    {.id = ALIPAY_TERM_O_BG,        .click = app_window_alipay_click_handler},
};


static const gui_window_config_struct app_window_alipay_bind_cfg =
{
    .forbid_gesture_back = 1,
    .entry_back_to_destory = 1,
    .enable_touch = 1,
};


const gui_window_struct app_window_alipay_bind =
{
	.screen = &gui_alipay_screen_bind,
    .config = &app_window_alipay_bind_cfg,
	.init = app_window_alipay_bind_init,
	.load = app_window_alipay_bind_load,
	.entry = app_window_alipay_bind_entry,
	.exit = app_window_alipay_bind_exit,
	.destroy = app_window_alipay_bind_destroy,

	.event_num = countof(app_window_alipay_bind_static_events),
    .events = app_window_alipay_bind_static_events,

    .touch_event_num = countof(app_window_alipay_bind_touch_events),
    .touch_events = app_window_alipay_bind_touch_events,
};

#endif
