#include "gui_display_render_cache.h"
#include "gui_display_render.h"
#include "feature_all.h"

#ifdef __CW_JL_VLT_MEM__
#include "os_mem.h"

static gui_render_list_struct g_render_list = {0};
#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
static gui_render_list_struct g_render_list_1 = {0};
static gui_render_list_struct g_render_list_2 = {0};
#endif

void gui_display_render_memory_init_cache(void)
{
	gui_render_struct *render_cache = os_mem_alloc(RAM_TYPE_BUFFER_ON, GUI_CACHE_RENDER_TOTAL * sizeof(gui_render_struct));
	if (render_cache == NULL)
		DBG_DIRECT("gui: gui_display_render_memory_init_cache, error!!!");
	else
		memset(render_cache, 0, (GUI_CACHE_RENDER_TOTAL * sizeof(gui_render_struct)));
	g_render_list.index = 0;
	g_render_list.buff = render_cache;
}

#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
void gui_display_render_memory_init_cache_1(void)
{
	gui_render_struct *render_cache = os_mem_alloc(RAM_TYPE_BUFFER_ON, GUI_CACHE_RENDER_TOTAL * sizeof(gui_render_struct));
	if (render_cache == NULL)
		DBG_DIRECT("gui: gui_display_render_memory_init_cache_1, error!!!");
	else
		memset(render_cache, 0, (GUI_CACHE_RENDER_TOTAL * sizeof(gui_render_struct)));
	g_render_list_1.index = 0;
	g_render_list_1.buff = render_cache;
}
void gui_display_render_memory_init_cache_2(void)
{
	gui_render_struct *render_cache = os_mem_alloc(RAM_TYPE_BUFFER_ON, GUI_CACHE_RENDER_TOTAL * sizeof(gui_render_struct));
	if (render_cache == NULL)
		DBG_DIRECT("gui: gui_display_render_memory_init_cache_2, error!!!");
	else
		memset(render_cache, 0, (GUI_CACHE_RENDER_TOTAL * sizeof(gui_render_struct)));
	g_render_list_2.index = 0;
	g_render_list_2.buff = render_cache;
}
#endif

void gui_display_render_memory_init(void)
{
	gui_display_render_memory_init_cache();
#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
	gui_display_render_memory_init_cache_1();
	gui_display_render_memory_init_cache_2();
#endif
}
void gui_display_render_memory_deinit(void)
{
	os_mem_free(g_render_list.buff);
#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
	os_mem_free(g_render_list_1.buff);
	os_mem_free(g_render_list_2.buff);
#endif
}
#else

static gui_render_struct g_render_list[GUI_CACHE_RENDER_TOTAL] = {0};

#endif

gui_render_list_struct *gui_display_render_cache_get_list()
{
	return &g_render_list;
}

#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
gui_render_list_struct *gui_display_render_cache_get_list_1()
{
	return &g_render_list_1;
}
gui_render_list_struct *gui_display_render_cache_get_list_2()
{
	return &g_render_list_2;
}
#endif

gui_render_struct *gui_display_render_cache_get(gui_render_list_struct *list)
{
	if (list == NULL || list->buff == NULL)
		return NULL;

	gui_render_struct *render = NULL;
	for (unsigned short i = 0; i < GUI_CACHE_RENDER_TOTAL; i++)
	{
		if (list->index >= GUI_CACHE_RENDER_TOTAL)
			list->index = 0;

		render = &list->buff[list->index++];
		if (render->cache == 0)
		{
			render->cache = 1;
			render->next = NULL;
			return render;
		}
	}
	SYS_DEBUG("gui: render cache error!!!");
	return NULL;
}

void gui_display_render_cache_clear(gui_render_list_struct *list)
{
	if (list == NULL || list->buff == NULL)
		return;
	memset(list->buff, 0, (GUI_CACHE_RENDER_TOTAL * sizeof(gui_render_struct)));
	list->index = 0;
}
