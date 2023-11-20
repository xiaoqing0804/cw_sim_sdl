#ifndef __GUI_DISPLAY_SCREEN_PART_H__
#define __GUI_DISPLAY_SCREEN_PART_H__

#include "feature_all.h"
#include "system_util_all.h"
#include "gui_core.h"
#include "gui_display_render.h"


#if(GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_PART)

#define GUI_SCREEN_PART_BUF_SIZE	(LCD_SIZE_WIDTH*GUI_SCREEN_PART_BUF_ROW*COLOR_RGB_PIXEL)

extern void gui_display_screen_part_init(void);
extern void gui_display_screen_part_update(void);
extern void gui_display_screen_part_frame(short y_start,short y_end);
extern void gui_display_screen_part_draw(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);
extern void gui_display_screen_part_push_buf_to_lcd(short y_start,short y_end);

#endif
#endif


