#ifndef __GUI_CORE_H__
#define __GUI_CORE_H__

#include "feature_all.h"
#include "system_util_all.h"
#include "gui_core_all.h"

#include "gui_util_screen.h"

extern GUI_COLOR gui_set_color(GUI_COLOR color);
extern GUI_COLOR gui_get_color(void);
extern GUI_COLOR gui_set_bg_color(GUI_COLOR bg_color);
extern GUI_COLOR gui_get_bg_color(void);
extern unsigned char gui_run_time_lock(void);

extern unsigned short gui_get_alpha_color(unsigned char* frame_buf,unsigned char* pic_buf,unsigned char alpha);
extern void gui_draw_alpha_pixel(unsigned char* frame_buf,unsigned char* pic_buf,unsigned char* frame_offset,unsigned char* pic_offset);

extern unsigned char gui_display_mutex_create(void);
extern unsigned char gui_display_mutex_lock(unsigned int wait);
extern unsigned char gui_display_mutex_unlock(void);

#endif


