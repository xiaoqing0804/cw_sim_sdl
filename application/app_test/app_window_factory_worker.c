
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"
#include "dev_version.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_factory_worker.h"
#include "app_window_factory_report.h"



#define G_SENSOR_VALUE_HALF     512

#define TP_TEST_GRID_ROW_NUM   (6)      // 行...
#define TP_TEST_GRID_COL_NUM   (5)      // 列...

#define TP_TEST_AREA_X(col)     ((col)*LCD_SIZE_WIDTH/TP_TEST_GRID_COL_NUM)
#define TP_TEST_AREA_Y(row)     ((row)*LCD_SIZE_HEIGHT/TP_TEST_GRID_ROW_NUM)
#define TP_TEST_AREA_W          (LCD_SIZE_WIDTH/TP_TEST_GRID_COL_NUM)
#define TP_TEST_AREA_H          (LCD_SIZE_HEIGHT/TP_TEST_GRID_ROW_NUM)


///////////////////////////////////////////////////////////////////////////////////////////////
#define TP_TEST_DRAW_LINE       0
#if TP_TEST_DRAW_LINE
#include "gui_display_draw_lib.h"
#include "gui_display_draw_lib_aa.h"
static gui_canvas_struct gui_factory_worker_tp_line[] =
{
    {
    	.type = TYPE_GUI_DRAW_SHAPE_LINE,
    	.penSize = 3,
    	.penColor = COLOR_RGB(255, 255, 255),
    	.canvas.rect.x0 = 30,
    	.canvas.rect.y0 = 0,
    	.canvas.rect.x1 = LCD_SIZE_WIDTH-1,
    	.canvas.rect.y1 = LCD_SIZE_HEIGHT-30,
    },
    {
        .type = TYPE_GUI_DRAW_SHAPE_LINE,
        .penSize = 3,
        .penColor = COLOR_RGB(255, 255, 255),
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 30,
        .canvas.rect.x1 = LCD_SIZE_WIDTH-30,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
    },
    {
    	.type = TYPE_GUI_DRAW_SHAPE_LINE,
    	.penSize = 3,
    	.penColor = COLOR_RGB(255, 255, 255),
    	.canvas.rect.x0 = 0,
    	.canvas.rect.y0 = LCD_SIZE_HEIGHT-30,
    	.canvas.rect.x1 = LCD_SIZE_WIDTH-30,
    	.canvas.rect.y1 = 0,
    },
    {
        .type = TYPE_GUI_DRAW_SHAPE_LINE,
        .penSize = 3,
        .penColor = COLOR_RGB(255, 255, 255),
        .canvas.rect.x0 = 30,
        .canvas.rect.y0 = LCD_SIZE_HEIGHT-1,
        .canvas.rect.x1 = LCD_SIZE_WIDTH-1,
        .canvas.rect.y1 = 30,
    },
};
static gui_canvas_struct gui_factory_worker_tp_draw =
{
    .id = 1,
    .type = TYPE_GUI_DRAW_SHAPE_CUSTOM,   // TYPE_GUI_DRAW
    .penSize = 1,
    .penColor = COLOR_RGB(0, 255, 0),
    .canvas.rect.x0 = 0,
    .canvas.rect.y0 = 0,
    .canvas.rect.x1 = LCD_SIZE_WIDTH-1,
    .canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
};
#endif

static gui_canvas_struct gui_factory_worker_bg_rect =
{
	.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,	  // TYPE_GUI_DRAW
	.penSize = 1,
	.penColor = COLOR_RGB(0, 0, 0),
	.canvas.rect.x0 = 0,
	.canvas.rect.y0 = 0,
	.canvas.rect.x1 = LCD_SIZE_WIDTH-1,
	.canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
};

//static const gui_image_struct gui_factory_worker_bg_image =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
//	.data = &pic_imb_bg_info,
//};

static gui_canvas_struct gui_factory_worker_color_rect =
{
	.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,	  // TYPE_GUI_DRAW
	.penSize = 1,
	.penColor = COLOR_RGB(255, 0, 0),
	.canvas.rect.x0 = 0,
	.canvas.rect.y0 = 0,
	.canvas.rect.x1 = LCD_SIZE_WIDTH-1,
	.canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
};

static const gui_canvas_struct gui_factory_worker_tp_rect =
{
	.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,	  // TYPE_GUI_DRAW
	.penSize = 1,
	.penColor = COLOR_RGB(255, 255, 255),
	.canvas.rect.x0 = 1,
	.canvas.rect.y0 = 1,
	.canvas.rect.x1 = TP_TEST_AREA_W-2,
	.canvas.rect.y1 = TP_TEST_AREA_H-2,
};

static gui_canvas_struct gui_factory_worker_lcd_lines[] =
{
    {
    	.type = TYPE_GUI_DRAW_SHAPE_LINE,
    	.penSize = 3,
    	.penColor = COLOR_RGB(0, 0, 255),
    	.canvas.rect.x0 = 0,
    	.canvas.rect.y0 = LCD_SIZE_HALF_HEIGHT,
    	.canvas.rect.x1 = LCD_SIZE_WIDTH-1,
    	.canvas.rect.y1 = LCD_SIZE_HALF_HEIGHT,
    },
    {
        .type = TYPE_GUI_DRAW_SHAPE_LINE,
        .penSize = 3,
        .penColor = COLOR_RGB(0, 0, 255),
        .canvas.rect.x0 = LCD_SIZE_HALF_WIDTH,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_HALF_WIDTH,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT-1,
    }
};



static const gui_font_struct gui_factory_worker_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= "LCD",
};

static const gui_font_struct gui_factory_worker_text_warn =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 0, 0),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= "LCD",
};

static const gui_font_struct gui_factory_worker_text_status =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(0, 255, 0),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= " ",
};



static const gui_font_struct gui_factory_worker_text_fail =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(0, 255, 0),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= "fail",
};


static const gui_font_struct gui_factory_worker_text_pass =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(0, 255, 0),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string= "pass",
};




enum{
    FACTORY_WORKER_MODE_BG_RECT = 10,
    FACTORY_WORKER_MODE_TP_RECT0,
    FACTORY_WORKER_MODE_TP_RECT1,
    FACTORY_WORKER_MODE_TP_RECT2,
    FACTORY_WORKER_MODE_TP_RECT3,
    FACTORY_WORKER_MODE_TP_RECT4,
    FACTORY_WORKER_MODE_TP_MAX = (FACTORY_WORKER_MODE_TP_RECT0 + TP_TEST_GRID_ROW_NUM*TP_TEST_GRID_COL_NUM),

    FACTORY_WORKER_MODE_LCD_LINES,

    FACTORY_WORKER_MODE_TITLE_TEXT,
	FACTORY_WORKER_MODE_TEXT1,
    FACTORY_WORKER_MODE_TEXT2,
    FACTORY_WORKER_MODE_TEXT3,
    FACTORY_WORKER_MODE_TEXT4,
    FACTORY_WORKER_MODE_TEXT5,
    FACTORY_WORKER_MODE_TEXT6,

    FACTORY_WORKER_MODE_OP_FAIL,
    FACTORY_WORKER_MODE_OP_PASS
};

#define FACTORY_WORKER_TEXT_ITEM_Y(n)     (LCD_SIZE_HEIGHT*n/9)
#define FACTORY_WORKER_TEXT_ITEM_H        (LCD_SIZE_HEIGHT/8)


#define FACTORY_TOUCH_TEST_AREA(n)              \
    {.id = FACTORY_WORKER_MODE_TP_RECT0 + (n),  \
        .type = TYPE_GUI_CONTROL_CANVAS,        \
        .x = TP_TEST_AREA_X((n)%TP_TEST_GRID_COL_NUM),             \
        .y = TP_TEST_AREA_Y((n)/TP_TEST_GRID_COL_NUM),             \
        .width = TP_TEST_AREA_W,                \
        .height = TP_TEST_AREA_H,               \
        .visible= 0,                            \
        .child_num = 1,                         \
        .children = &gui_factory_worker_tp_rect,    \
    }


static const gui_widget_struct gui_factory_worker_widgets[] =
{
//    {   // bg
//        .type = TYPE_GUI_CONTROL_IMAGE,
//        .width = LCD_SIZE_WIDTH,
//        .height = LCD_SIZE_HEIGHT,
//        .scale  = 1.608f,
//        .visible= 1,
//        .child_num = 1,
//        .children = &gui_factory_worker_bg_image,
//    },

    // lcd color
    {
    	.id = FACTORY_WORKER_MODE_BG_RECT,
    	.type = TYPE_GUI_CONTROL_CANVAS,
    	.width = LCD_SIZE_WIDTH,
    	.height = LCD_SIZE_HEIGHT,
    	.visible= 1,
    	.child_num = 1,
    	.children = &gui_factory_worker_color_rect,
    },

    // lcd lines
    {
        .id = FACTORY_WORKER_MODE_LCD_LINES,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 0,
        .child_num = countof(gui_factory_worker_lcd_lines),
        .children = &gui_factory_worker_lcd_lines,
    },

#if TP_TEST_DRAW_LINE
    {
        .id = FACTORY_WORKER_MODE_TP_RECT0,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 0,
        .child_num = countof(gui_factory_worker_tp_line),
        .children = &gui_factory_worker_tp_line,
    },
    {
        .id = FACTORY_WORKER_MODE_TP_RECT1,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_tp_draw,
    },
#else
    // TP area
    FACTORY_TOUCH_TEST_AREA(0),
    FACTORY_TOUCH_TEST_AREA(1),
    FACTORY_TOUCH_TEST_AREA(2),
    FACTORY_TOUCH_TEST_AREA(3),

    FACTORY_TOUCH_TEST_AREA(4),
    FACTORY_TOUCH_TEST_AREA(5),
    FACTORY_TOUCH_TEST_AREA(6),
    FACTORY_TOUCH_TEST_AREA(7),

    FACTORY_TOUCH_TEST_AREA(8),
    FACTORY_TOUCH_TEST_AREA(9),
    FACTORY_TOUCH_TEST_AREA(10),
    FACTORY_TOUCH_TEST_AREA(11),

    FACTORY_TOUCH_TEST_AREA(12),
    FACTORY_TOUCH_TEST_AREA(13),
    FACTORY_TOUCH_TEST_AREA(14),
    FACTORY_TOUCH_TEST_AREA(15),

    FACTORY_TOUCH_TEST_AREA(16),
    FACTORY_TOUCH_TEST_AREA(17),
    FACTORY_TOUCH_TEST_AREA(18),
    FACTORY_TOUCH_TEST_AREA(19),

    FACTORY_TOUCH_TEST_AREA(20),
    FACTORY_TOUCH_TEST_AREA(21),
    FACTORY_TOUCH_TEST_AREA(22),
    FACTORY_TOUCH_TEST_AREA(23),

    FACTORY_TOUCH_TEST_AREA(24),
    FACTORY_TOUCH_TEST_AREA(25),
    FACTORY_TOUCH_TEST_AREA(26),
    FACTORY_TOUCH_TEST_AREA(27),

    FACTORY_TOUCH_TEST_AREA(28),
    FACTORY_TOUCH_TEST_AREA(29),
#endif

    // title
	{
		.id = FACTORY_WORKER_MODE_TITLE_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = FACTORY_WORKER_TEXT_ITEM_Y(0),
		.width = LCD_SIZE_WIDTH,
		.height = FACTORY_WORKER_TEXT_ITEM_H,
		.visible= 1,
        .child_num = 1,
        .children = &gui_factory_worker_text,
	},

    // text items
	{
		.id = FACTORY_WORKER_MODE_TEXT1,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = FACTORY_WORKER_TEXT_ITEM_Y(1),
		.width = LCD_SIZE_WIDTH,
		.height = FACTORY_WORKER_TEXT_ITEM_H,
		.visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_text,
	},
    {
        .id = FACTORY_WORKER_MODE_TEXT2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = FACTORY_WORKER_TEXT_ITEM_Y(2),
        .width = LCD_SIZE_WIDTH,
        .height = FACTORY_WORKER_TEXT_ITEM_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_text,
    },
    {
        .id = FACTORY_WORKER_MODE_TEXT3,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = FACTORY_WORKER_TEXT_ITEM_Y(3),
        .width = LCD_SIZE_WIDTH,
        .height = FACTORY_WORKER_TEXT_ITEM_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_text,
    },

    {
        .id = FACTORY_WORKER_MODE_TEXT4,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = FACTORY_WORKER_TEXT_ITEM_Y(4),
        .width = LCD_SIZE_WIDTH,
        .height = FACTORY_WORKER_TEXT_ITEM_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_text,
    },

    {
        .id = FACTORY_WORKER_MODE_TEXT5,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = FACTORY_WORKER_TEXT_ITEM_Y(5),
        .width = LCD_SIZE_WIDTH,
        .height = FACTORY_WORKER_TEXT_ITEM_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_text,
    },

    {
        .id = FACTORY_WORKER_MODE_TEXT6,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = FACTORY_WORKER_TEXT_ITEM_Y(6),
        .width = LCD_SIZE_WIDTH,
        .height = FACTORY_WORKER_TEXT_ITEM_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_text,
    },

    // operator
    {
        .id = FACTORY_WORKER_MODE_OP_FAIL,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = FACTORY_WORKER_TEXT_ITEM_Y(7),
        .width = LCD_SIZE_HALF_WIDTH,
        .height = FACTORY_WORKER_TEXT_ITEM_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_text_fail,
    },
    {
        .id = FACTORY_WORKER_MODE_OP_PASS,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = LCD_SIZE_HALF_WIDTH,
        .y = FACTORY_WORKER_TEXT_ITEM_Y(7),
        .width = LCD_SIZE_HALF_WIDTH,
        .height = FACTORY_WORKER_TEXT_ITEM_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_factory_worker_text_pass,
    },
};

const gui_screen_struct gui_screen_factory_worker =
{
	.children = gui_factory_worker_widgets,
	.child_num = countof(gui_factory_worker_widgets),
};

#define TPTEST_CELL_NUM     (sizeof(mTouchRect)/sizeof(geometry_rect))




///////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_factory_worker_set_visible(unsigned int id, unsigned char visible)
{
    gui_box_struct* box;
    box = gui_surface_get_box(&gui_screen_factory_worker, id);
    if (box != NULL) box->visible = visible;
}

static void app_window_factory_worker_set_text(unsigned int id, char* text)
{
    gui_box_struct* box;
    box = gui_surface_get_box(&gui_screen_factory_worker, id);
    if (box != NULL)  gui_surface_box_label_change_string(box, text);
}

static void app_window_factory_worker_set_text_with_style(unsigned int id, gui_font_struct* font, char* text)
{
    gui_box_struct* box;
    box = gui_surface_get_box(&gui_screen_factory_worker, id);
    if (box != NULL)  gui_surface_box_label_change_content(box, font, text);
}

static int app_window_factory_worker_check_touch_position(short x, short y)
{
    unsigned short idx = FACTORY_WORKER_MODE_TP_RECT0;
    gui_box_struct* box;

    for (idx=FACTORY_WORKER_MODE_TP_RECT0; idx<FACTORY_WORKER_MODE_TP_MAX; idx++) {
        box = gui_surface_get_box(&gui_screen_factory_worker, idx);
        if (box != NULL) {
            if (check_rect_contain_xy(box->x, box->y, box->width, box->height, x, y)) {
                box->visible = 0;
                return (idx - FACTORY_WORKER_MODE_TP_RECT0);
            }
        }
    }
    return -1;
}


/////////////////////////////////////////////////////////////////////////////////////////////////
static unsigned char  g_ftest_single_mode;
static unsigned char  g_factory_test_index;
static unsigned char  g_factory_test_count;
static unsigned int   g_factory_test_mask;  // check
static unsigned int   g_factory_test_pass_flags;

/////////////////////////////////////////////////////////////////////////////////////////////////
static void factory_set_touch_visible(unsigned int id, unsigned int vis)
{
    if (id == 0) {
        for (id=FACTORY_WORKER_MODE_TP_RECT0; id<FACTORY_WORKER_MODE_TP_MAX; id++) {
            app_window_factory_worker_set_visible(id, vis);
        }
    }
    else if (id >= FACTORY_WORKER_MODE_TP_RECT0 && id < FACTORY_WORKER_MODE_TP_MAX){
        app_window_factory_worker_set_visible(id, vis);
    }
}

static int factory_key_start(void)
{
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    factory_set_touch_visible(0, 0);

    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT1, "Key1");
    g_factory_test_mask = 1;

#if defined(KEY2_SWITCH) && KEY2_SWITCH
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT2, "Key2");
    g_factory_test_mask |= 0x02;
#else
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 0);
#endif

#if defined(KEY3_SWITCH) && KEY3_SWITCH
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT3, "Key3");
    g_factory_test_mask |= 0x04;
#else
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 0);
#endif

#if TCFG_RDEC_KEY_ENABLE
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT4, "Rol-Up");
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT5, "Rol-Dn");
    g_factory_test_mask |= 0x18;
#else
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
#endif

    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);

    return 0;
}

static int factory_key_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_KEY) {
        if (param < 5) {
            g_factory_test_mask &= ~(1 << param);
            app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1+param, 0);
        }
    }

    if (g_factory_test_mask == 0) {
        return 1;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_version_start(void)
{
    char temp[64];
    unsigned short crc16;
    unsigned char hardware_id;

	hardware_id = g_devInfo.dev_id.hardware_id;
	if(!bsp_gsensor_is_ready())	{
		hardware_id &= ~(1 << 1);
	}

    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 0);

    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);

    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT2, DEV_NAME);

	snprintf(temp, sizeof(temp), "TP:%c-%d-%04X", g_TP_info.type, g_TP_info.id, g_TP_info.checksum);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT3, temp);

    snprintf(temp, sizeof(temp),"%d.%02X.%d.%d.%d",
                g_devInfo.dev_id.customer_id+(g_devInfo.dev_id.customer_id_h<<8), hardware_id,
                g_devInfo.dev_id.code_id, g_devInfo.dev_id.picture_id,
                g_devInfo.dev_id.font_id);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT4, temp);

	snprintf(temp, sizeof(temp),"%02X:%02X:%02X:%02X:%02X:%02X",
					g_devInfo.mac_addr[5],g_devInfo.mac_addr[4],g_devInfo.mac_addr[3],
					g_devInfo.mac_addr[2],g_devInfo.mac_addr[1],g_devInfo.mac_addr[0]);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT5, temp);

	crc16 = calculate_crc16(0, g_devInfo.mac_addr, sizeof(g_devInfo.mac_addr));
	snprintf(temp, sizeof(temp),"ID:%04X", crc16);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 1);
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT6, temp);

    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_lcd_orthogonal_start(void)
{
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_lcd_color_start(void)
{
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 1);
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);
    gui_factory_worker_color_rect.penColor = COLOR_RGB(255, 0, 0);
    return 0;
}

static int factory_lcd_color_check(fact_check_type type, int param, void* param_p)
{
    // R, G, B, W, B
    if (type == FACT_CHECK_TYPE_TIMER) {
        g_factory_test_count ++;
        switch(g_factory_test_count)  {
            case 1:
                gui_factory_worker_color_rect.penColor = COLOR_RGB(0, 255, 0);
                break;
            case 2:
                gui_factory_worker_color_rect.penColor = COLOR_RGB(0, 0, 255);
                break;
            case 3:
                gui_factory_worker_color_rect.penColor = COLOR_RGB(255, 255, 0);
                break;
            case 4:
                gui_factory_worker_color_rect.penColor = COLOR_RGB(255, 0, 255);
                break;
            case 5:
                gui_factory_worker_color_rect.penColor = COLOR_RGB(0, 255, 255);
                break;
            case 6:
                gui_factory_worker_color_rect.penColor = COLOR_RGB(255, 255, 255);
                break;
            case 7:
                gui_factory_worker_color_rect.penColor = COLOR_RGB(0, 0, 0);
                break;
            default:
                break;
        }
    }
    else if (type == FACT_CHECK_TYPE_KEY) {
        return -1;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static short g_tp_tst_status;       // 0 - idle; 1 - active;
#if TP_TEST_DRAW_LINE
#define TP_DRAW_DLT_VAL     (LCD_SIZE_WIDTH/20)
#define TP_DRAW_POINTS_MAX  100
static short g_tp_pre_x;
static short g_tp_pre_y;
static short g_tp_rec_idx;
static gdi_point* g_tp_draw_points;
static void factory_touch_panel_init(void)
{
    g_tp_draw_points = (gdi_point*)os_mem_alloc(RAM_TYPE_DATA_ON, TP_DRAW_POINTS_MAX*sizeof(gdi_point));
    if (g_tp_draw_points != NULL) {
        g_tp_pre_x = -1;
        g_tp_pre_y = -1;
        g_tp_rec_idx = 0;
        memset(g_tp_draw_points, 0xFF, TP_DRAW_POINTS_MAX**sizeof(gdi_point));
        gui_surface_box_canvas_set_custom_draw(FACTORY_WORKER_MODE_TP_RECT1, 1, factory_touch_panel_draw);
    }
}
static void factory_touch_panel_deinit(void)
{
    if (g_tp_draw_points != NULL) {
        os_mem_free(g_tp_draw_points);
        g_tp_draw_points = NULL;
    }
    gui_surface_box_canvas_set_custom_draw(FACTORY_WORKER_MODE_TP_RECT1, 1, NULL);
}
static unsigned char factory_touch_record_point(gui_touch_struct *event)
{
    if (g_tp_tst_status) {
        if (event->type == TOUCH_EVENT_TYPE_DOWN) {
            g_tp_draw_points[g_tp_rec_idx].x = event->x;
            g_tp_draw_points[g_tp_rec_idx].y = event->y;
            g_tp_pre_x = event->x;
            g_tp_pre_y = event->y;
        }
        else if ((event->type == TOUCH_EVENT_TYPE_UP) || (event->type == TOUCH_EVENT_TYPE_MOVE)) {
            short dlt_x = event->x - g_tp_pre_x;
            short dlt_y = event->y - g_tp_pre_y;
            if (ABS(dlt_x) > TP_DRAW_DLT_VAL || ABS(dlt_y) > TP_DRAW_DLT_VAL) {
                g_tp_rec_idx ++;
                g_tp_draw_points[g_tp_rec_idx].x = event->x;
                g_tp_draw_points[g_tp_rec_idx].y = event->y;
                g_tp_pre_x = event->x;
                g_tp_pre_y = event->y;

                if (event->type == TOUCH_EVENT_TYPE_UP) {
                    g_tp_rec_idx ++;
                }
            }
        }
    }
    return 0;
}
static void factory_touch_panel_draw(void)
{
    unsigned short x0 = -1, y0 = -1, idx;
    for (idx=0; idx<TP_DRAW_POINTS_MAX; idx++) {
        if ((x0 != -1) && (g_tp_draw_points[idx].x != -1)) {
            GUI_DrawLine(x0, y0, g_tp_draw_points[idx].x, g_tp_draw_points[idx].y);
        }
        x0 = g_tp_draw_points[idx].x;
        y0 = g_tp_draw_points[idx].y;
    }
}
#endif
static int factory_touch_panel_start(void)
{
    unsigned int count = (TP_TEST_GRID_ROW_NUM*TP_TEST_GRID_COL_NUM);

    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 0);
#if TP_TEST_DRAW_LINE
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TP_RECT0, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TP_RECT1, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);
    factory_touch_panel_init();
#else
    g_factory_test_mask = (1 << count) - 1;
    #if (LCD_SHAPE == LCD_CIRCLE)
    g_factory_test_mask &= ~(1 << 0);
    g_factory_test_mask &= ~(1 << (TP_TEST_GRID_COL_NUM-1));
    g_factory_test_mask &= ~(1 << (count-TP_TEST_GRID_COL_NUM));
    g_factory_test_mask &= ~(1 << (count-1));
    #endif

    factory_set_touch_visible(0, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 0);

    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT2, "X: ");
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT3, "Y: ");
#endif

    g_tp_tst_status = 1;
    return 0;
}

static int factory_touch_panel_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_TP) {
        #if TP_TEST_DRAW_LINE
        return factory_touch_record_point(param_p);
        #else

        if (g_tp_tst_status) {
            gui_touch_struct* event = (gui_touch_struct*)param_p;
            char temp[16];
            int idx = app_window_factory_worker_check_touch_position(event->x, event->y);
            if (idx >= 0) {
                g_factory_test_mask &= ~(1 << idx);
            }
            SYS_DEBUG("app: fact_test_tp, mask = %x", g_factory_test_mask);

            if ((g_factory_test_mask == 0)) {
                #if TP_TEST_DRAW_LINE
                factory_touch_panel_deinit();
                #endif
                g_tp_tst_status = 0;
                return 1;   // pass
            }
            sprintf(temp, "X: %d", event->x);
            app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT2, temp);
            sprintf(temp, "Y: %d", event->y);
            app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT3, temp);
            return 0;
        }
        #endif
    }
    else if (type == FACT_CHECK_TYPE_KEY) {
        #if TP_TEST_DRAW_LINE
        factory_touch_panel_deinit();
        #endif
        g_tp_tst_status = 0;
        return -1;
    }
    //#if TP_TEST_DRAW_LINE
    else if ((type == FACT_CHECK_TYPE_EXIT) || (type == FACT_CHECK_TYPE_PASS)) {
        #if TP_TEST_DRAW_LINE
        factory_touch_panel_deinit();
        #endif
        g_tp_tst_status = 0;
    }
    //#endif
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_gsensor_start(void)
{
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);

    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT2, "X: ");
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT3, "Y: ");
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT4, "Z: ");
    g_factory_test_mask = 0x3F;
    bsp_gsensor_set_mode_test(1);
    return 0;
}

static int factory_gsensor_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_GSENSOR) {
        short* xyz = (short*)param_p;

        if (xyz[0] >= G_SENSOR_VALUE_HALF) {
            g_factory_test_mask &= ~(0x01);
        }
        else if (xyz[0] <= -G_SENSOR_VALUE_HALF) {
            g_factory_test_mask &= ~(0x02);
        }

        if (xyz[1] >= G_SENSOR_VALUE_HALF) {
            g_factory_test_mask &= ~(0x04);
        }
        else if (xyz[1] <= -G_SENSOR_VALUE_HALF) {
            g_factory_test_mask &= ~(0x08);
        }

        if (xyz[2] >= G_SENSOR_VALUE_HALF) {
            g_factory_test_mask &= ~(0x10);
        }
        else if (xyz[2] <= -G_SENSOR_VALUE_HALF) {
            g_factory_test_mask &= ~(0x20);
        }

        if (g_factory_test_mask == 0) {
            bsp_gsensor_set_mode_test(0);
            return 1;   // pass
        }

        char temp[32];
        sprintf(temp, "X: %d, %d", xyz[0], (g_factory_test_mask>>0) & 0x03);
        app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT2, temp);
        sprintf(temp, "Y: %d, %d", xyz[1], (g_factory_test_mask>>2)&0x03);
        app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT3, temp);
        sprintf(temp, "Z: %d, %d", xyz[2], (g_factory_test_mask>>4)&0x03);
        app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT4, temp);
    }
    else if (type == FACT_CHECK_TYPE_KEY) {
        bsp_gsensor_set_mode_test(0);
        return -1;
    }
    else if ((type == FACT_CHECK_TYPE_EXIT)||(type == FACT_CHECK_TYPE_PASS)) {
        bsp_gsensor_set_mode_test(0);
    }
    return 0;
}


//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_vib_motor_start(void)
{
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);

    app_window_factory_worker_set_text_with_style(FACTORY_WORKER_MODE_TEXT3, &gui_factory_worker_text_status, "马达是否有震动");

    send_motor_msg(MOTOR_MSG_MESSAGE);
    g_factory_test_count = 1;
    return 0;
}
static int factory_vib_motor_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_ONOFF) {
        if (g_factory_test_count == 0) {
            send_motor_msg(MOTOR_MSG_MESSAGE);
        }
        else {
            close_motor_msg();
        }
        g_factory_test_count = !g_factory_test_count;
    }
    else if (type == FACT_CHECK_TYPE_PASS) {
        g_factory_test_count = 0;
        close_motor_msg();
        app_window_factory_worker_set_text_with_style(FACTORY_WORKER_MODE_TEXT3, &gui_factory_worker_text, " ");
        return 1;
    }
    else if (type == FACT_CHECK_TYPE_KEY) {
        return -1;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_hr_start(void)
{
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);

    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT2, "HR: ");
    app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT3, "Pre: Cur: ");

    hr_set_real_mode(1);    // hr_set_cross_test_mode(1);
    return 0;
}

static int factory_hr_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_TIMER) {
        char temp[32];

        sprintf(temp, "HR: %d", last_hr_result.hr);
        app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT2, (unsigned char*)temp);

        int hr_v1 = 0, hr_v2 = 0, hr_v3 = 0, hr_v4 = 0,hr_v5=0;
        hr_get_values(&hr_v1, &hr_v2, &hr_v3, &hr_v4,&hr_v5);
        sprintf(temp, "curr: %d, red: %d", hr_v1, hr_v2);
        app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TEXT3, (unsigned char*)temp);
    }
    else if (type == FACT_CHECK_TYPE_KEY) {
        hr_set_real_mode(0);    // hr_set_cross_test_mode(0);
        return -1;
    }
    else if (type == FACT_CHECK_TYPE_PASS) {
        hr_set_real_mode(0);    // hr_set_cross_test_mode(0);
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_bp_start(void)
{
    return 0;
}

static int factory_bp_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_KEY) {
        return -1;
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_o2_start(void)
{
    return 0;
}

static int factory_o2_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_KEY) {
        return -1;
    }
    return 0;
}

#if defined(__EXT_BT_AUDIO__)
//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_mic_test_start(void)
{
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);
    app_window_factory_worker_set_text_with_style(FACTORY_WORKER_MODE_TEXT3, &gui_factory_worker_text_status, "对MIC吹气可以听到回声");

    ext_btaud_test_speaker_mic(1);
    return 0;
}

static int factory_mic_test_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_KEY) {
        // stop
        ext_btaud_test_speaker_mic(0);
        return -1;
    }
    else if (type == FACT_CHECK_TYPE_PASS) {
        // stop
        ext_btaud_test_speaker_mic(0);
        app_window_factory_worker_set_text_with_style(FACTORY_WORKER_MODE_TEXT3, &gui_factory_worker_text, " ");
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////
static int factory_spk_test_start(void)
{
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_BG_RECT, 0);
    factory_set_touch_visible(0, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_LCD_LINES, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT1, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT2, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT3, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT4, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT5, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_TEXT6, 0);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_FAIL, 1);
    app_window_factory_worker_set_visible(FACTORY_WORKER_MODE_OP_PASS, 1);
    app_window_factory_worker_set_text_with_style(FACTORY_WORKER_MODE_TEXT3, &gui_factory_worker_text_status, "是否听到播放音乐");

    ext_btaud_test_speaker_music(1);
    return 0;
}

static int factory_spk_test_check(fact_check_type type, int param, void* param_p)
{
    if (type == FACT_CHECK_TYPE_KEY) {
        // stop
        ext_btaud_test_speaker_music(0);
        return -1;
    }
    else if (type == FACT_CHECK_TYPE_PASS) {
        // stop
        ext_btaud_test_speaker_music(0);
        app_window_factory_worker_set_text_with_style(FACTORY_WORKER_MODE_TEXT3, &gui_factory_worker_text, " ");
    }
    return 0;
}
#endif



//////////////////////////////////////////////////////////////////////////////////////////////////
static const factory_test_item_struct g_factory_test_map[] =
{
    {"Version",     factory_version_start, NULL},
    {"LCD org.",    factory_lcd_orthogonal_start, NULL},       // orthogonal
    {"LCD color",   factory_lcd_color_start,    factory_lcd_color_check},
    {"Key",         factory_key_start,          factory_key_check},
    {"Toch Panel",  factory_touch_panel_start,  factory_touch_panel_check},
    {"HR",          factory_hr_start,           factory_hr_check},
    //{"BP",          factory_bp_start,           factory_bp_check},
    //{"O2",          factory_o2_start,           factory_o2_check},
    {"G-Sensor",    factory_gsensor_start, factory_gsensor_check},
    {"Vib motor",   factory_vib_motor_start, factory_vib_motor_check},
#if defined(__EXT_BT_AUDIO__)
    {"Speaker",     factory_spk_test_start, factory_spk_test_check},
    {"MIC",         factory_mic_test_start, factory_mic_test_check},
#endif
    //{"Charger", NULL, NULL},
};
#define FACTORY_TEST_MAP_SZ     (sizeof(g_factory_test_map)/sizeof(g_factory_test_map[0]))
#define FACTORY_TEST_COMP_MASK  ((1 << FACTORY_TEST_MAP_SZ) - 1)

unsigned short factory_test_get_count(void)
{
    return FACTORY_TEST_MAP_SZ;
}

factory_test_item_struct* factory_test_get_item(int index)
{
    if (index < FACTORY_TEST_MAP_SZ) {
        return &g_factory_test_map[index];
    }
    return NULL;
}

unsigned int factory_test_get_pass_flags(void)
{
    return g_factory_test_pass_flags;
}



//////////////////////////////////////////////////////////////////////////////////////////////////
static int app_window_factory_worker_update(void)
{
    char title_text[48];
    gui_box_struct* box;

    if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
        sprintf(title_text, " %s (%d/%d)", g_factory_test_map[g_factory_test_index].name, g_factory_test_index+1, FACTORY_TEST_MAP_SZ);
        app_window_factory_worker_set_text(FACTORY_WORKER_MODE_TITLE_TEXT, title_text);

        g_factory_test_count = 0;
        g_factory_test_mask  = 0;
        if (g_factory_test_map[g_factory_test_index].start != NULL) {
            g_factory_test_map[g_factory_test_index].start();
        }
        gui_surface_commit();
        return 0;
    }
    return -1;
}


static int app_window_factory_worker_check_fail(void)
{
    SYS_DEBUG("app: fact_test_fail, index=%d, count=%d, mask=%x", g_factory_test_index, g_factory_test_count, g_factory_test_mask);

    if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
        if (g_factory_test_map[g_factory_test_index].check != NULL) {
            g_factory_test_map[g_factory_test_index].check(FACT_CHECK_TYPE_EXIT, 0, NULL);
        }
    }

    if (g_ftest_single_mode) {
        application_go_back();
        return 0;
    }

    g_factory_test_index ++;
    if (app_window_factory_worker_update() < 0) {
        // show report
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_factory_report, NULL);
    }
    return 0;
}

static int app_window_factory_worker_check_pass(fact_check_type type, int param, void* param_p)
{
    int ret = 0;

    SYS_DEBUG("app: fact_test_pass, type=%d, index=%d, count=%d, mask=%x", type, g_factory_test_index, g_factory_test_count, g_factory_test_mask);

    if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
        if (g_factory_test_map[g_factory_test_index].check != NULL) {
            ret = g_factory_test_map[g_factory_test_index].check(type, param, param_p);
            if (ret > 0) {
                g_factory_test_pass_flags |= (1 << g_factory_test_index);

                if (g_ftest_single_mode) {
                    //application_go_back();
                    application_send_event(EVENT_GO_BACK, NULL);
                    return 0;
                }
            }
            else if (ret < 0) {
                application_go_back();
                return 0;
            }
            else {
                gui_surface_commit();
            }
        }
        else if (type == FACT_CHECK_TYPE_KEY) {
            application_go_back();
            return 0;
        }

        if ((type == FACT_CHECK_TYPE_PASS) || (g_factory_test_pass_flags & (1 << g_factory_test_index))) {
            g_factory_test_index ++;
            if (app_window_factory_worker_update() < 0) {
                // show report
                application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_factory_report, NULL);
                return 0;
            }
        }
    }
    return ret;
}

static int app_window_factory_worker_check_exit(void)
{
    if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
        if (g_factory_test_map[g_factory_test_index].check != NULL) {
            g_factory_test_map[g_factory_test_index].check(FACT_CHECK_TYPE_EXIT, 0, NULL);
        }
    }
}


///////////////////////////////////////////////////////////////////////////////////////////////

static void app_window_factory_worker_init(void *buf)
{
    if (buf != NULL)  {
        g_ftest_single_mode = 1;
    	g_factory_test_index = *((unsigned char*)buf);
    }
    else {
        g_ftest_single_mode = 0;
    	g_factory_test_index = 0;
    }
    g_factory_test_count = 0;
    g_factory_test_pass_flags = 0;
}

static void app_window_factory_worker_load(void *buf)
{
    app_window_factory_worker_update();
}


static void app_window_factory_worker_entry(void *buf)
{
    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}


static void app_window_factory_worker_exit()
{
    app_window_factory_worker_check_exit();
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_factory_worker_destroy()
{

}


///////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_factory_worker_acttimer_handler(void* buf)
{
    SYS_DEBUG("app: fact_test, timer");
    app_window_factory_worker_check_pass(FACT_CHECK_TYPE_TIMER, 0, NULL);
}

static void app_window_factory_worker_key1_handler(void *buf)
{
    SYS_DEBUG("app: fact_test, key1");
    app_window_factory_worker_check_pass(FACT_CHECK_TYPE_KEY, 0, NULL);
}

static void app_window_factory_worker_key2_handler(void *buf)
{
    SYS_DEBUG("app: fact_test, key2");
    if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
        if (0 == strcmp("Key", g_factory_test_map[g_factory_test_index].name)) {
            app_window_factory_worker_check_pass(FACT_CHECK_TYPE_KEY, 1, NULL);
        }
    }
}

static void app_window_factory_worker_key3_handler(void *buf)
{
    SYS_DEBUG("app: fact_test, key3");
    if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
        if (0 == strcmp("Key", g_factory_test_map[g_factory_test_index].name)) {
            app_window_factory_worker_check_pass(FACT_CHECK_TYPE_KEY, 2, NULL);
        }
    }
}

static void app_window_factory_worker_rolkey_handler(void* buf)
{
    rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
    SYS_DEBUG("app: fact_test, rol-key, %d", rolkey->rotate);
    if (rolkey->rotate == ROTATE_TYPE_FORWARD) {
        if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
            if (0 == strcmp("Key", g_factory_test_map[g_factory_test_index].name)) {
                app_window_factory_worker_check_pass(FACT_CHECK_TYPE_KEY, 3, NULL);
            }
        }
    }
    else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
        if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
            if (0 == strcmp("Key", g_factory_test_map[g_factory_test_index].name)) {
                app_window_factory_worker_check_pass(FACT_CHECK_TYPE_KEY, 4, NULL);
            }
        }
    }
}

static void app_window_factory_worker_g_sensor_handler(void* buf)
{
    short* xyz = (short*)buf;
    SYS_DEBUG("app: fact_test, gsensor, %d, %d, %d", xyz[0], xyz[1], xyz[2]);
    app_window_factory_worker_check_pass(FACT_CHECK_TYPE_GSENSOR, 0, buf);
}

static unsigned char app_window_factory_worker_touch_handler(gui_touch_struct *event)
{
    SYS_DEBUG("app: fact_test, touch, %d, %d, %d", event->type, event->x, event->y);
    app_window_factory_worker_check_pass(FACT_CHECK_TYPE_TP, 0, event);
    return g_tp_tst_status;
}

static void app_window_factory_worker_click_fail(gui_click_struct *event)
{
    if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
        app_window_factory_worker_check_fail();
    }
}

static void app_window_factory_worker_click_pass(gui_click_struct *event)
{
    if (g_factory_test_index < FACTORY_TEST_MAP_SZ) {
        g_factory_test_pass_flags |= (1 << g_factory_test_index);
        app_window_factory_worker_check_pass(FACT_CHECK_TYPE_PASS, 0, NULL);
    }
}

static void app_window_factory_worker_click_onoff(gui_click_struct *event)
{
    app_window_factory_worker_check_pass(FACT_CHECK_TYPE_ONOFF, 0, event);
}



/*-----------------------------����--------------------------------------*/
static const app_window_event_struct app_window_factory_worker_static_events[] =
{
	{.id = EVENT_ACT, .handler = app_window_factory_worker_acttimer_handler },

    {.id = EVENT_KEY1_SHORT, .handler = app_window_factory_worker_key1_handler},

#if defined(KEY2_SWITCH) && KEY2_SWITCH
    {.id = EVENT_KEY2_SHORT, .handler = app_window_factory_worker_key2_handler},
#endif

#if defined(KEY3_SWITCH) && KEY3_SWITCH
    {.id = EVENT_KEY3_SHORT, .handler = app_window_factory_worker_key3_handler},
#endif

    {.id = EVENT_ROLKEY,     .handler = app_window_factory_worker_rolkey_handler},

    {.id = EVENT_G_SENSOR_DATA, .handler = app_window_factory_worker_g_sensor_handler},

    {.id = EVENT_BL_TIMEOUT},
    {.id = EVENT_GO_HOME},
	{.id = EVENT_ALL}
};

static const gui_touch_event_struct app_window_factory_worker_touch_events[] =
{
    {.id = FACTORY_WORKER_MODE_TEXT3,   .click = app_window_factory_worker_click_onoff},
    {.id = FACTORY_WORKER_MODE_OP_FAIL, .click = app_window_factory_worker_click_fail},
    {.id = FACTORY_WORKER_MODE_OP_PASS, .click = app_window_factory_worker_click_pass},
	{.id = 0xFFFF,	                    .touch = app_window_factory_worker_touch_handler }
};

static const gui_window_config_struct app_window_factory_worker_config =
{
	.forbid_gesture_back = 1,
	.forbid_key_back = 1,
	.entry_back_to_destory = 1,
    .enable_touch = 1,
};


const gui_window_struct app_window_factory_worker =
{
	.screen = &gui_screen_factory_worker,
	.config = &app_window_factory_worker_config,

	.init = app_window_factory_worker_init,
	.load = app_window_factory_worker_load,
	.entry = app_window_factory_worker_entry,
	.exit = app_window_factory_worker_exit,
	.destroy = app_window_factory_worker_destroy,

	.touch_event_num = countof(app_window_factory_worker_touch_events),
	.touch_events = app_window_factory_worker_touch_events,

	.event_num = countof(app_window_factory_worker_static_events),
	.events = app_window_factory_worker_static_events,
};




