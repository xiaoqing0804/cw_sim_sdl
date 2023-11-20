#ifndef __GUI_DISPLAY_H__
#define __GUI_DISPLAY_H__

#include "feature_all.h"

//--фад╩отй╬╣д╫ЬЁл-----------------------------------------------------------------
extern void gui_display_init(void);
extern void gui_display_update(void);
extern void gui_display_refresh_frame(void);
extern void gui_display_cache_release(void* window_owner);

#endif

