#include "picture.h"
#include "language.h"
#include "app_window_qr_card_layout.h"

#if defined(GUI_QR_INFO_SUPPORT)&&GUI_QR_INFO_SUPPORT

#define QR_CARD_SIZE			240
#define QR_CARD_XPOS  			((LCD_SIZE_WIDTH-QR_CARD_SIZE)/2)
#define QR_CARD_YPOS  			((LCD_SIZE_HEIGHT-QR_CARD_SIZE)/2 - 10)

#define QR_CARD_FRAME_WIDTH		24
#define QR_CARD_FRAME_SIZE		(QR_CARD_SIZE+QR_CARD_FRAME_WIDTH*2)
#define QR_CARD_FRAME_R0		12


static const gui_qr_code_struct gui_card_qrcode =
{
	.type = TYPE_GUI_DRAW_QR_CODE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .width = QR_CARD_SIZE,
	.string = "",
};
static const gui_font_struct gui_card_name =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.color = COLOR_RGB(255, 255, 255),
	.x = 10,
	.y = 0,
	.width = LCD_SIZE_WIDTH-20,
	.height = 40,
	.size = SYS_FONT_SMALL,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "",
};

static const gui_image_struct gui_card_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.scale = 0.6f,
	.x = QR_CARD_SIZE/2,
	.y = QR_CARD_SIZE/2,
	.anchor_x = ANCHOR_VALUE(0.5f),
	.anchor_y = ANCHOR_VALUE(0.5f),
	.data  = &pic_msg_other_info,
};


static const gui_canvas_struct gui_QR_CARD_qrcode_bg[] =
{
		{
			.id = 1,
			.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
			.penSize = 5,
			.penColor = COLOR_RGB(255, 255, 255),
			.canvas.rect.x0 = 0,
			.canvas.rect.y0 = 0,
			.canvas.rect.x1 = QR_CARD_FRAME_SIZE - 1,
			.canvas.rect.y1 = QR_CARD_FRAME_SIZE - 1,
		},
		{
			.id = 2,
			.type = TYPE_GUI_DRAW_SHAPE_ARC,
			.penSize = 5,
			.penColor = COLOR_RGB(0, 0, 0),
			.canvas.arc.cx = QR_CARD_FRAME_SIZE -1 - QR_CARD_FRAME_R0,
			.canvas.arc.cy = QR_CARD_FRAME_R0,
			.canvas.arc.r  = QR_CARD_FRAME_R0 + 5,
			.canvas.arc.Angle0 = 0,
			.canvas.arc.Angle1 = 90,
		},
		{
			.id = 3,
			.type = TYPE_GUI_DRAW_SHAPE_ARC,
			.penSize = 5,
			.penColor = COLOR_RGB(0, 0, 0),
			.canvas.arc.cx = QR_CARD_FRAME_R0,
			.canvas.arc.cy = QR_CARD_FRAME_R0,
			.canvas.arc.r = QR_CARD_FRAME_R0 + 5,
			.canvas.arc.Angle0 = 90,
			.canvas.arc.Angle1 = 180,
		},
		{
			.id = 4,
			.type = TYPE_GUI_DRAW_SHAPE_ARC,
			.penSize = 5,
			.penColor = COLOR_RGB(0, 0, 0),
			.canvas.arc.cx = QR_CARD_FRAME_R0,
			.canvas.arc.cy = QR_CARD_FRAME_SIZE - 1 - QR_CARD_FRAME_R0,
			.canvas.arc.r = QR_CARD_FRAME_R0 + 5,
			.canvas.arc.Angle0 = 180,
			.canvas.arc.Angle1 = 270,
		},
		{
			.id = 5,
			.type = TYPE_GUI_DRAW_SHAPE_ARC,
			.penSize = 5,
			.penColor = COLOR_RGB(0, 0, 0),
			.canvas.arc.cx = QR_CARD_FRAME_SIZE - 1 - QR_CARD_FRAME_R0,
			.canvas.arc.cy = QR_CARD_FRAME_SIZE - 1 - QR_CARD_FRAME_R0,
			.canvas.arc.r = QR_CARD_FRAME_R0 + 5,
			.canvas.arc.Angle0 = -90,
			.canvas.arc.Angle1 = 0,
		}
};

static const gui_widget_struct gui_widget_qr_card[] =
{
	{
		.type = TYPE_GUI_CONTROL_CANVAS,
		.x = QR_CARD_XPOS - QR_CARD_FRAME_WIDTH,
		.y = QR_CARD_YPOS - QR_CARD_FRAME_WIDTH,
		.width = QR_CARD_SIZE+QR_CARD_FRAME_WIDTH*2,
		.height = QR_CARD_SIZE+QR_CARD_FRAME_WIDTH*2,
		.visible = 1,
		.child_num = countof(gui_QR_CARD_qrcode_bg),
		.children = &gui_QR_CARD_qrcode_bg,
	},

	{
		.id = QR_CARD_ID_CODE,
		.type = TYPE_GUI_CONTROL_QR_CODE,
		.x = QR_CARD_XPOS,
		.y = QR_CARD_YPOS,	// 73 + LCD_SIZE_HEIGHT * 2,
		.width = QR_CARD_SIZE,
		.height = QR_CARD_SIZE,
		.visible = 1,
		.child_num = 1,
		.children = &gui_card_qrcode,
	},

	{
		.id = QR_CARD_TEXT_ID_CODE,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = QR_CARD_YPOS+QR_CARD_SIZE+QR_CARD_FRAME_WIDTH+6,
		.width = LCD_SIZE_WIDTH,
		.height = 39,
		.clip = 1,
		.visible= 1,
		.child_num = 1,
		.children = &gui_card_name,
	},

    {
        .id = QR_CARD_ICON_ID_CODE,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = QR_CARD_XPOS,
        .y = QR_CARD_YPOS,
        .width = QR_CARD_SIZE,
        .height = QR_CARD_SIZE,
        .visible= 0,
        .child_num = 1,
        .children = &gui_card_icon,
    },
};

const gui_screen_struct gui_screen_qr_card =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_widget_qr_card,
	.child_num = countof(gui_widget_qr_card),
};

#endif
