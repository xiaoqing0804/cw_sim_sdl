
#include "app_window_brightness_layout.h"

#include "picture.h"
#include "language.h"
#include "gui_surface_control_animation.h"


static const gui_image_struct gui_pic_brightness_ok =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_timer_add_info,
};

static const gui_font_struct gui_public_brightness_title =   //ʱ��
{
    .type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_BRIGHTNESS,
};

static const gui_font_struct gui_public_brightness_ok =   //ʱ��
{
    .type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_YES,
};

static const gui_font_struct gui_public_brightness_line =   //ʱ��
{
    .type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(76, 76, 76),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_NUMBER_32,
    .value_type = GUI_FONT_VALUE_TYPE_NUMBER,
    .value.number = 3,
};

static const gui_font_struct gui_public_brightness_line2 =   //ʱ��
{
    .type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_NUMBER_45,
    .value_type = GUI_FONT_VALUE_TYPE_NUMBER,
    .value.number = 3,
};

static const gui_canvas_struct gui_brightness_bg =
{
	.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,	  // TYPE_GUI_DRAW
	.penSize = 2,
	.penColor = COLOR_RGB(0, 0, 0),
	.opacity  = 50,
	.canvas.rect.x0 = 0,
	.canvas.rect.y0 = 0,
	.canvas.rect.x1 = 466,
	.canvas.rect.y1 = 360,
};

static const gui_widget_struct gui_widget_light[] =
{
    //亮度标题
	{
		.id = LIGHT_LAYOUT_ID_TITLE,
		.type = TYPE_GUI_CONTROL_LABEL,
        .y = 39,
        .width = LCD_SIZE_WIDTH,
        .height = 43,
        .rotate = 0,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_brightness_title,
	},
	{   
		.id = LIGHT_LAYOUT_BG_ID,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = 466,
        .height = 360,
        .visible= 1,
        .child_num = 1,
        .children = &gui_brightness_bg,
    },

    //上方数字
	 {
        .id = LIGHT_LAYOUT_ID_LINE_0,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 121,
        .width = LCD_SIZE_WIDTH,
        .height = 24,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_brightness_line,
    },
    //中间数字
    {
        .id = LIGHT_LAYOUT_ID_LINE_2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y =191,
        .width = LCD_SIZE_WIDTH,
        .height = 33,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_brightness_line2,
    },
    //下方数字
    {
        .id = LIGHT_LAYOUT_ID_LINE_1,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 281,
        .width = LCD_SIZE_WIDTH,
        .height = 24,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_brightness_line,
    },
    
    //确认按钮图片
	{
		.id = LIGHT_LAYOUT_ID_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 364,
		.width = LCD_SIZE_WIDTH,
		.height = 102,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_brightness_ok,
	},

    
	{
		.id = LIGHT_LAYOUT_ID_PIC_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 395,
        .width = LCD_SIZE_WIDTH,
        .height = 43,
        .rotate = 0,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_brightness_ok,
	},

};


const gui_screen_struct gui_screen_light =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_widget_light,
	.child_num = countof(gui_widget_light),
};


