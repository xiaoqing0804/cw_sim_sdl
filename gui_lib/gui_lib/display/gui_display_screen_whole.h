#ifndef __GUI_DISPLAY_SCREEN_WHOLE_H__
#define __GUI_DISPLAY_SCREEN_WHOLE_H__

#include "feature_all.h"
#include "gui_core.h"
#include "gui_display_render.h"


#if(GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_WHOLE)

#define GUI_SCREEN_WHOLE_BUF_SIZE	(LCD_SIZE_WIDTH*LCD_SIZE_HEIGHT*COLOR_RGB_PIXEL)

extern void gui_display_screen_whole_init(void);
extern void gui_display_screen_whole_update(void);

#endif
#endif

