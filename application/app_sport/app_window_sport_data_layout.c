#include "app_window_sport_data_layout.h"
#include "picture.h"
#include "language.h"

#include "gui_surface_control_base.h"
static const gui_image_struct gui_pic_sport_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_sport_bg_info,
};


static const gui_image_struct gui_pic_sport_data_steps =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_font_steps_info,
};

static const gui_image_struct gui_pic_sport_data_km =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_font_km_info,
};

static const gui_image_struct gui_pic_sport_data_kcal =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_font_kcal_info,
};


static const gui_image_struct gui_pic_sport_data_bpm =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_font_bpm_info,
};

static const gui_image_struct gui_pic_sport_data_reset =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
//	.data = &pic_operator2_stop_info,
};


static const gui_image_struct gui_pic_sport_data_stop =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
//	.data = &pic_operator2_pause_info,
};


//ÊýÖµ

static const gui_font_struct gui_text_sport_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.auto_wrap = 0,
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_NUMBER_50,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "00:00:00",
};


static const gui_font_struct gui_text_sport_bpm =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
    .y = 0,
    .width = 100,
    .anchor_x = 0,
    .anchor_y = 0,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_NONE),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_NONE),
    .size = SYS_FONT_NUMBER_29,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "000",
};

static const gui_font_struct gui_text_sport_km =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
	.auto_wrap = 0,
    .width = 100,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_NONE),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_29,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00",
};

static const gui_font_struct gui_text_sport_kcal =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
	.auto_wrap = 0,
    .width = 100,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_NONE),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_29,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "0000",
};

static const gui_font_struct gui_text_sport_step =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 0,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
	.auto_wrap = 0,
    .width = 100,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_NONE),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_29,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00000",
};




// pause
static const gui_font_struct gui_text_sport_pause_exit =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_EXIT,
};

static const gui_font_struct gui_text_sport_pause_continue =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_CONTINUE,
};

static const gui_font_struct gui_text_sport_pause_finish =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_FINISH,
};

static const gui_image_struct gui_pic_sport_pause_continue =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_continue_info,
};

static const gui_image_struct gui_pic_sport_pause_finish =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_finish_info,
};



static const gui_image_struct gui_pic_sport_ready_number =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_spor_ready_3_info,
};


static const gui_font_struct gui_text_before_one_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.auto_wrap = 0,
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_NUMBER_35,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "00:00",
};


static const gui_control_digital_struct  gui_before_one_time =
{
 .value_type = GUI_DIGITAL_VALUE_TYPE_FONT,
 .value.font = &gui_text_before_one_time,

};



static const gui_canvas_struct gui_steps_line_shapes[] =
{
     {
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 2,
        .penColor = COLOR_RGB(102, 102, 102),
        .canvas.line.x0 = 22,
        .canvas.line.y0 = 194,
        .canvas.line.x1 = 443,
        .canvas.line.y1 = 195,
    },
	{
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 3,
        .penColor = COLOR_RGB(102, 102, 102),
        .canvas.line.x0 = LCD_SIZE_HALF_WIDTH,
        .canvas.line.y0 = 202,
        .canvas.line.x1 = LCD_SIZE_HALF_WIDTH,
        .canvas.line.y1 = 304,
    },
	{
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 2,
        .penColor = COLOR_RGB(102, 102, 102),
        .canvas.line.x0 = 34,
        .canvas.line.y0 = 310,
        .canvas.line.x1 = 432,
        .canvas.line.y1 = 311,
    },

};


static const gui_canvas_struct gui_swim_line_shapes[] =
{
     {
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 2,
        .penColor = COLOR_RGB(102, 102, 102),
        .canvas.line.x0 = 22,
        .canvas.line.y0 = 200,
        .canvas.line.x1 = 444,
        .canvas.line.y1 = 201,
    },
	{
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 3,
        .penColor = COLOR_RGB(102, 102, 102),
        .canvas.line.x0 = LCD_SIZE_HALF_WIDTH,
        .canvas.line.y0 = 217,
        .canvas.line.x1 = LCD_SIZE_HALF_WIDTH,
        .canvas.line.y1 = 380,
    },


 };

//2???

static const gui_widget_struct gui_widget_sport_data[] =
{
	{
		.id = SPORT_DATA_LAYOUT_ID_BG,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_sport_bg,
	},

	//µ¥Î»
	{
		.id = SPORT_DATA_LAYOUT_ID_STEPS,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 100,
		.y = 260,
		.width = 74,
		.height = 21,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_sport_data_steps,
	},



	{
		.id = SPORT_DATA_LAYOUT_ID_KCAL,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 110,
		.y = 370,
		.width = 58,
		.height = 21,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_sport_data_kcal,
	},



	{
		.id = SPORT_DATA_LAYOUT_ID_KM,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 290,
		.y = 260,
		.width = 33,
		.height = 21,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_sport_data_km,
	},




	{
		.id = SPORT_DATA_LAYOUT_ID_BPM,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 280,
		.y = 370,
		.width = 49,
		.height = 20,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_sport_data_bpm,
	},

	//ÊýÖµ
		{
		.id = SPORT_DATA_LAYOUT_ID_BPM_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 280,
		.y = 324,
		.width = 53,
		.height = 35,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_text_sport_bpm,
	},
	{
		.id = SPORT_DATA_LAYOUT_ID_KM_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 290,
		.y = 215,
		.width = 81,
		.height = 35,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_text_sport_km,
	},
	{
		.id = SPORT_DATA_LAYOUT_ID_KCAL_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 110,
		.y = 324,
		.width = 72,
		.height = 35,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_text_sport_kcal,
	},

	{
		.id = SPORT_DATA_LAYOUT_ID_STEPS_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 100,
		.y = 215,
		.width = 90,
		.height = 35,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_text_sport_step,
	},

	{
		.id = SPORT_DATA_LAYOUT_ID_TIME,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = 100,
		.width = LCD_SIZE_WIDTH,
		.height = 50,
		.rotate = 0,
		.visible= 1,
		.child_num = 1,
		.children = &gui_text_sport_time,
	},


   {
        .id = SPORT_DATA_LAYOUT_ID_PAUSE_EXIT_TXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = 120,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_text_sport_pause_exit,
    },
/*
    {
        .id = SPORT_DATA_LAYOUT_ID_PAUSE_CONTINUE_TXT,
        .type = TYPE_GUI_CONTROL_LABEL,     // 8, 155, 111, 50
        .x = 0,
        .y = 290,
        .width = LCD_SIZE_HALF_HEIGHT,
        .height = 50,
        .visible= 1,
        .child_num = 1,
        .children = &gui_text_sport_pause_continue,
    },

    {
        .id = SPORT_DATA_LAYOUT_ID_PAUSE_FINISH_TXT,
        .type = TYPE_GUI_CONTROL_LABEL, // 122, 155, 111, 50
        .x = LCD_SIZE_HALF_HEIGHT,
        .y = 290,
        .width = LCD_SIZE_HALF_HEIGHT,
        .height = 50,
        .visible= 1,
        .child_num = 1,
        .children = &gui_text_sport_pause_finish,
    },
*/

    {
        .id = SPORT_DATA_LAYOUT_ID_PAUSE_CONTINUE_PIC,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 91,
        .y = 308,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_pic_sport_pause_continue,
    },

    {
        .id = SPORT_DATA_LAYOUT_ID_PAUSE_EXIT_PIC,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 272,
        .y = 308,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_pic_sport_pause_finish,
    },

     {
        .id = SPORT_DATA_LAYOUT_ID_READY_NUMBER,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible = 1,
		.scale = 1.0f,
        .child_num = 1,
        .children = &gui_pic_sport_ready_number,
     },


	{   // time
        .type = TYPE_GUI_CONTROL_TIME,
		.y = 400,
        .width = LCD_SIZE_WIDTH,
        .height = 54,
        .visible= 1,
        .child_num = 1,
        .children = &gui_before_one_time,
    },

	{   // line
		.id =SPORT_DATA_LAYOUT_ID_STEPS_LINE,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = countof(gui_steps_line_shapes),
        .children = &gui_steps_line_shapes,
    },

    {   // line
		.id =SPORT_DATA_LAYOUT_ID_SWIM_LINE,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 0,
        .child_num = countof(gui_swim_line_shapes),
        .children = &gui_swim_line_shapes,
    },
};


const gui_screen_struct gui_screen_sport_data =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_sport_data,
	.child_num = countof(gui_widget_sport_data),
};


