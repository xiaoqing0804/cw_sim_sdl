#ifndef __GUI_UTIL_SCREEN_H__
#define __GUI_UTIL_SCREEN_H__

#include "feature_all.h"
#include "system_util_all.h"

extern const geometry_rect* gui_util_screen_get_screen_size(void);
extern unsigned char gui_util_screen_check_rect_in_screen(geometry_rect* rect);

#endif


