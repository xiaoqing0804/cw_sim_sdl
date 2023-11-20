#include "app_window_cover_bg_layout.h"

gui_canvas_struct gui_canvas_cover_bg_rect =
    {
        .id = GUI_IDS_COVER_BG,
        .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL, // TYPE_GUI_DRAW
        .penSize = 1,
        .opacity = 50,
        .penColor = COLOR_RGB(0, 0, 0),
        .canvas.rect.x0 = 0,
        .canvas.rect.y0 = 0,
        .canvas.rect.x1 = LCD_SIZE_WIDTH - 1,
        .canvas.rect.y1 = LCD_SIZE_HEIGHT - 1,
};

const gui_widget_struct gui_widget_cover_bg =
    {
        .id = GUI_IDS_COVER_BG,
        .type = TYPE_GUI_CONTROL_CANVAS,
        .x = 0,
        .y = 0,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible = 1,
        .child_num = 1,
        .children = &gui_canvas_cover_bg_rect,
};
