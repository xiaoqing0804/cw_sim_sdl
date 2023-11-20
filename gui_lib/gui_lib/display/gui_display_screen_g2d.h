#ifndef __GUI_DISPLAY_SCREEN_PART_H__
#define __GUI_DISPLAY_SCREEN_PART_H__

#include "feature_all.h"
#include "system_util_all.h"
#include "gui_core.h"
#include "gui_display_render.h"


#if(GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_G2D)

#define GUI_SCREEN_G2D_BUF_SIZE	(LCD_SIZE_WIDTH*LCD_SIZE_HEIGHT*COLOR_RGB_PIXEL)

extern void gui_display_screen_g2d_init(void);
extern void gui_display_screen_g2d_update(void);
extern void gui_display_screen_g2d_cache_release(unsigned int wnd_owner);

#endif
#endif


