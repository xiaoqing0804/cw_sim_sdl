#ifndef __GUI_WINDOW_HISTORY_CACHE_H__
#define __GUI_WINDOW_HISTORY_CACHE_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern gui_window_history_struct* gui_window_history_cache_get(void);
extern void gui_window_history_cache_remove(gui_window_history_struct* history);
extern void gui_window_history_cache_clear(void);

#endif

