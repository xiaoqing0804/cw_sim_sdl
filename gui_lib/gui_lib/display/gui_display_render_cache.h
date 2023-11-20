#ifndef __GUI_DISPLAY_RENDER_CACHE_H__
#define __GUI_DISPLAY_RENDER_CACHE_H__

#include "feature_all.h"
#include "gui_core.h"
#include "gui_display_render.h"

extern gui_render_list_struct* gui_display_render_cache_get_list(void);

#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
extern gui_render_list_struct* gui_display_render_cache_get_list_1(void);
extern gui_render_list_struct* gui_display_render_cache_get_list_2(void);
#endif

extern gui_render_struct* gui_display_render_cache_get(gui_render_list_struct* list);
extern void gui_display_render_cache_clear(gui_render_list_struct* list);

#endif

