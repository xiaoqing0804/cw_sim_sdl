
#include "picture.h"
#include "language.h"

#include "app_window_appSport_layout.h"



static const gui_canvas_struct gui_appsport_lines[] =
{
    {
    	.type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(255, 255, 255),
    	.canvas.line.x0 = 0,
    	.canvas.line.y0 = (1*LCD_SIZE_HEIGHT)/4,
    	.canvas.line.x1 = LCD_SIZE_WIDTH-1,
    	.canvas.line.y1 = (1*LCD_SIZE_HEIGHT)/4,
    },

	 {
    	.type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(255, 255, 255),
    	.canvas.line.x0 = 0,
    	.canvas.line.y0 = (2*LCD_SIZE_HEIGHT)/4,
    	.canvas.line.x1 = LCD_SIZE_WIDTH-1,
    	.canvas.line.y1 = (2*LCD_SIZE_HEIGHT)/4,
    },

	{
    	.type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(255, 255, 255),
    	.canvas.line.x0 = 0,
    	.canvas.line.y0 = (3*LCD_SIZE_HEIGHT)/4,
    	.canvas.line.x1 = LCD_SIZE_WIDTH-1,
    	.canvas.line.y1 = (3*LCD_SIZE_HEIGHT)/4,
    },
};

static const gui_font_struct gui_appsport_title =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_APP_SPORT,
};


static const gui_font_struct gui_appsport_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.auto_wrap = 0,
    .color = COLOR_RGB(0,255,255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00:00:00",
};

static const gui_font_struct gui_appsport_bpm =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.auto_wrap = 0,
    .color = COLOR_RGB(0,255,0),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "78 BPM",
};

static const gui_font_struct gui_appsport_km =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.auto_wrap = 0,
    .color = COLOR_RGB(255,255,0),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "123.4 KM",
};

// pause
static const gui_font_struct gui_text_sport_pause_exit =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_EXIT,
};

static const gui_font_struct gui_text_sport_pause_continue =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_CONTINUE,
};

static const gui_font_struct gui_text_sport_pause_finish =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_FINISH,
};

static const gui_image_struct gui_pic_sport_pause_continue =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_continue_info,
};

static const gui_image_struct gui_pic_sport_pause_finish =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_finish_info,
};


static const gui_widget_struct gui_widget_appsport_data[] =
{
    {
        .id = APPSPORT_DATA_LAYOUT_ID_LINES,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = countof(gui_appsport_lines),
        .children = &gui_appsport_lines,
    },

    {
        .id = APPSPORT_DATA_LAYOUT_ID_TITLE,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = 0,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/4,
        .visible= 1,
        .child_num = 1,
        .children = &gui_appsport_title,
    },

    {
        .id = APPSPORT_DATA_LAYOUT_ID_TIME,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = (1*LCD_SIZE_HEIGHT/4),
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/4,
        .visible= 1,
        .child_num = 1,
        .children = &gui_appsport_time,
    },

    {
        .id = APPSPORT_DATA_LAYOUT_ID_BPM_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = (2*LCD_SIZE_HEIGHT/4)+40,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/4,
        .visible= 1,
        .child_num = 1,
        .children = &gui_appsport_bpm,
    },

    {
        .id = APPSPORT_DATA_LAYOUT_ID_KM_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = (3*LCD_SIZE_HEIGHT/4)+40,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT/4,
        .visible= 1,
        .child_num = 1,
        .children = &gui_appsport_km,
    },


    // pause
    {
        .id = APPSPORT_DATA_LAYOUT_ID_PAUSE_EXIT_TXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = 0,
        .y = 120,
        .width = LCD_SIZE_WIDTH,
        .height = 40,
        .visible= 1,
        .child_num = 1,
        .children = &gui_text_sport_pause_exit,
    },



    {
        .id = APPSPORT_DATA_LAYOUT_ID_PAUSE_CONTINUE_PIC,
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
        .id = APPSPORT_DATA_LAYOUT_ID_PAUSE_EXIT_PIC,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 272,
        .y = 308,
        .width = 102,
        .height = 102,
        .visible= 1,
        .child_num = 1,
        .children = &gui_pic_sport_pause_finish,
    },
};

const gui_screen_struct gui_screen_appsport =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_appsport_data,
	.child_num = countof(gui_widget_appsport_data),
};




