#include "gui_util_screen.h"

static const geometry_rect g_full_screen_rect = {
	.x = 0,
	.y = 0,
	.width = LCD_SIZE_WIDTH,
	.height = LCD_SIZE_HEIGHT,
};


const geometry_rect* gui_util_screen_get_screen_size()
{
    return &g_full_screen_rect;
}

unsigned char gui_util_screen_check_rect_in_screen(geometry_rect* rect)
{
    return check_rect_intersect_rect((geometry_rect*)&g_full_screen_rect,rect);
}




