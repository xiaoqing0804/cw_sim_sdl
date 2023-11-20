#include "gui_surface_cache.h"
#include "feature_all.h"

static gui_box_struct g_box_cache[GUI_CACHE_BOX_TOTAL] ={0};	
static gui_node_struct g_node_cache[GUI_CACHE_NODE_TOTAL]={0};

static unsigned short g_box_cache_index = 0;
static unsigned short g_node_cache_index = 0;

gui_box_struct* gui_surface_cache_add_box()
{
	gui_box_struct* cache = NULL;
	for(unsigned short i = 0; i < GUI_CACHE_BOX_TOTAL; i++)
	{
		if(g_box_cache_index >= GUI_CACHE_BOX_TOTAL)
			g_box_cache_index = 0;

		cache = &g_box_cache[g_box_cache_index++];
		if(cache->cache == 0)
		{
			cache->id = 0;
			cache->visible = 1;
			cache->scale = 1.0f;
			cache->alpha = 255;
			cache->cache = 1;
			cache->update = 0;
			cache->order = 0;
			cache->brother = NULL;
			cache->child = NULL;
			cache->widget = NULL;
			return cache;
		}
	}
    DBG_DIRECT("gui: box cache error!!!");
	return NULL;
}

void gui_surface_cache_remove_box(gui_box_struct* box)
{
    memset(box, 0, sizeof(gui_box_struct));
}

void gui_surface_cache_remove_box_and_children(gui_box_struct* box)
{
	gui_surface_cache_remove_nodes(box->child);
    gui_surface_cache_remove_box(box);
}


void gui_surface_cache_clear_box()
{
	g_box_cache_index = 0;
	memset(g_box_cache, 0 , sizeof(g_box_cache));
}


short gui_surface_cache_count_box()
{
	short count = 0;
	gui_box_struct* cache = NULL;
	for(unsigned short i = 0; i < GUI_CACHE_BOX_TOTAL; i++)
	{
		cache = &g_box_cache[i];
		if(cache->cache == 1)
			count++;
	}
	return count;
}



gui_node_struct* gui_surface_cache_add_node()
{
	gui_node_struct* cache = NULL;
	for(unsigned short i = 0; i < GUI_CACHE_NODE_TOTAL; i++)
	{
		if(g_node_cache_index >= GUI_CACHE_NODE_TOTAL)
			g_node_cache_index = 0;
		cache = &g_node_cache[g_node_cache_index++];
			
		if(cache->cache == 0)
		{
			cache->cache = 1;
			cache->visible= 1;
			cache->brother = NULL;
			cache->child = NULL;
			cache->scale = 1.0f;
			cache->tag = 0;
			return cache;
		}
	}
    DBG_DIRECT("gui: node cache error!!!");
	return NULL;
}

void gui_surface_cache_remove_node_from_list(gui_box_struct* box, gui_node_struct* node)
{
	gui_node_struct* pre_node = NULL;
	gui_node_struct* curr_node = box->child;
	while(curr_node)
	{
		if(curr_node == node)
		{
			if(pre_node == NULL)
				box->child = node->brother;
			else
				pre_node->brother = node->brother;
			return;
		}
		pre_node = curr_node;
		curr_node = curr_node->brother;
	}
}

void gui_surface_cache_remove_node(gui_node_struct* node)
{
	gui_node_struct* next_node = NULL;
	gui_node_struct* compose_node = NULL;

    compose_node = node->child;
    while(compose_node != NULL)
    {
        next_node = compose_node->child;
        memset(compose_node, 0, sizeof(gui_node_struct));
        compose_node = next_node;
    }
    memset(node, 0, sizeof(gui_node_struct));
}

void gui_surface_cache_remove_nodes(gui_node_struct* node)
{
	gui_node_struct* next_node = NULL;
	while(node)
	{
		next_node = node->brother;
		gui_surface_cache_remove_node(node);
		node = next_node;
	}
}


void gui_surface_cache_clear_node()
{
	g_node_cache_index = 0;
	memset(g_node_cache, 0 , sizeof(g_node_cache));
}

gui_node_struct* gui_surface_cache_find_front(gui_node_struct* root_node,gui_node_struct* node)
{
	gui_node_struct* front_node = NULL;
	gui_node_struct* curr_node = root_node;
	while(1)
	{
		if(curr_node == NULL)
			return NULL;
		if(curr_node == node)
			return front_node;
		front_node = curr_node;
		curr_node = curr_node->brother;
	}
}

gui_node_struct* gui_surface_cache_find_front_in_child(gui_node_struct* root_node,gui_node_struct* node)
{
	gui_node_struct* front_node = NULL;
	gui_node_struct* curr_node = root_node;
	while(1)
	{
		if(curr_node == NULL)
			return NULL;
		if(curr_node == node)
			return front_node;
		front_node = curr_node;
		curr_node = curr_node->child;
	}
}


void gui_surface_cache_remove_surface(gui_surface_struct* surface)
{
	gui_box_struct* box = surface->child;
	gui_box_struct* next_box = NULL;

	gui_node_struct* node = NULL;
	gui_node_struct* compose_node = NULL;
	gui_node_struct* next_node = NULL;

	while(box != NULL)
	{
		node = box->child;
		while(node != NULL)
		{
			compose_node = node->child;
			while(compose_node != NULL)
			{
				next_node = compose_node->child;
				gui_surface_cache_remove_node(compose_node);
				compose_node = next_node;
			}

			next_node = node->brother;
			gui_surface_cache_remove_node(node);
			node = next_node;
		}

		next_box = box->brother;
		gui_surface_cache_remove_box(box);
		box = next_box;
	}
	surface->child = NULL;
}

short gui_surface_cache_count_node()
{
	short count = 0;
	gui_node_struct* cache = NULL;
	for(unsigned short i = 0; i < GUI_CACHE_NODE_TOTAL; i++)
	{
		cache = &g_node_cache[i];
		if(cache->cache == 1)
			count++;
	}
	return count;
}

