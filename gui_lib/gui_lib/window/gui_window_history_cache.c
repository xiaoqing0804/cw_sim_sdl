#include "gui_window_history_cache.h"
#include "feature_all.h"

static gui_window_history_struct g_window_history_cache[GUI_CACHE_WINDOW_HISTORY_TOTAL]={0};
static unsigned short g_window_history_cache_index = 0;

gui_window_history_struct* gui_window_history_cache_get()
{
	gui_window_history_struct* cache = NULL;
	for(unsigned short i = 0; i < GUI_CACHE_WINDOW_HISTORY_TOTAL; i++)
	{
		if(g_window_history_cache_index >= GUI_CACHE_WINDOW_HISTORY_TOTAL)
			g_window_history_cache_index = 0;
		cache = &g_window_history_cache[g_window_history_cache_index++];
		if(cache->cache == 0)
		{
			gui_window_history_cache_remove(cache);
			cache->cache = 1;
			return cache;
		}
	}
	return NULL;
}


void gui_window_history_cache_remove(gui_window_history_struct* history)
{
	memset(history, 0 , sizeof(gui_window_history_struct));
}


void gui_window_history_cache_clear()
{
	memset(g_window_history_cache, 0 , sizeof(g_window_history_cache));
	g_window_history_cache_index = 0;
}






