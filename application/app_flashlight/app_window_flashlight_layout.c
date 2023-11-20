#include "app_window_flashlight_layout.h"
#include "picture.h"
#include "language.h"

static const gui_canvas_struct gui_flashlight_line[] =
{
	 {
    	.type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,     // TYPE_GUI_DRAW
        .penSize = 5,
        .penColor = COLOR_RGB(255, 255, 255),
    	.canvas.line.x0 = 0,
    	.canvas.line.y0 = 0,
    	.canvas.line.x1 = LCD_SIZE_WIDTH,
    	.canvas.line.y1 = LCD_SIZE_HEIGHT,
    },
};

static const gui_widget_struct gui_widget_flashlight[] =
{
	{
            .id = FLASHLIGHT_ID_PIC,
            .type = TYPE_GUI_CONTROL_CANVAS,
            .x = 0,
            .y = 0,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .rotate = 0,
            .visible= 1,
            .clip = 0,
            .space_x = 0,
            .space_y = 0,
            .child_num =countof(gui_flashlight_line),
            .children = gui_flashlight_line,
        },
};

const gui_screen_struct gui_screen_flashlight =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_flashlight,
	.child_num = countof(gui_widget_flashlight),
};


