
#include "debug_info.h"
#include "os_mem.h"

#include "gui_display.h"
#include "feature_all.h"
#include "gui_surface.h"
#include "gui_core.h"
#include "gui_display_render.h"
#include "gui_display_screen_part.h"
#include "gui_display_screen_whole.h"
#include "gui_display_screen_g2d.h"
#include "application_touch.h"
#include "gui_surface_node.h"
#include "gui_surface_cache.h"
#include "gui_surface_scale.h"
#include "gui_surface_box_scale.h"
#include "gui_surface_node_scale.h"

static gui_scale_struct g_gui_scale = {0};

// 虚拟树创建---------------------------------------------------------------------
static void gui_display_order_box(gui_surface_struct *surface, gui_box_struct **box_order_map)
{
	short box_count = 0;
	gui_box_struct *box = surface->child;
	while (box != NULL)
	{
		box_order_map[box_count++] = box;
		box = box->brother;
	}
	box_order_map[box_count] = NULL;

	if (box_count > 0)
	{
		gui_box_struct *temp;
		for (short j = 0; j < box_count - 1; j++)
		{
			for (short k = 0; k < box_count - j - 1; k++)
			{
				if (box_order_map[k]->order > box_order_map[k + 1]->order)
				{
					temp = box_order_map[k + 1];
					box_order_map[k + 1] = box_order_map[k];
					box_order_map[k] = temp;
				}
			}
		}
	}
}

// 嵌套的node
static void gui_display_add_compose_render(gui_surface_struct *surface, gui_box_struct *box, gui_node_struct *node)
{
	// 嵌套的第一个node都是范围框
	if (node != NULL)
	{
		geometry_rect rect_node;
		gui_node_struct *compose_node = node->child;
		while (compose_node != NULL)
		{
			if (compose_node->visible)
			{
				if (compose_node->type == TYPE_GUI_DRAW_TEXT && compose_node->value == 0x20)
				{
					compose_node = compose_node->child;
					continue;
				}

				g_gui_scale.compose = compose_node;
				gui_surface_compose_calculate_scale(&g_gui_scale);

				gui_surface_node_compose_get_rect_in_screen_with_scale(&g_gui_scale, &rect_node);
				unsigned char rect_in_screen = gui_util_screen_check_rect_in_screen(&rect_node);
				unsigned char rect_in_surface = gui_surface_node_check_rect_in_surface(&g_gui_scale, &rect_node);
				if (rect_in_screen && rect_in_surface) // 是否在屏幕内可以显示
				{
					gui_display_render_add_compose(&g_gui_scale); // 把node放到屏幕渲染帧去, box是组织用的，不需要渲染
				}
			}
			compose_node = compose_node->child;
		}
	}
}

static void gui_display_add_render(gui_surface_struct *surface, gui_box_struct *box, gui_node_struct *node)
{
	/*****************************
	**当前Node最多支持两层嵌套
	******************************/
	geometry_rect rect_node;
	while (node != NULL)
	{
		if (node->visible)
		{
			g_gui_scale.node = node;
			gui_surface_node_calculate_scale(&g_gui_scale);

			gui_surface_node_get_rect_in_screen_with_scale(&g_gui_scale, &rect_node);
			unsigned char rect_in_screen = gui_util_screen_check_rect_in_screen(&rect_node);
			unsigned char rect_in_surface = gui_surface_node_check_rect_in_surface(&g_gui_scale, &rect_node);
			if (rect_in_screen && rect_in_surface) // 是否在屏幕内可以显示
			{
				gui_display_render_add(&g_gui_scale); // 把node放到屏幕渲染帧去, box是组织用的，不需要渲染
			}

			if (node->child != NULL)
			{
				gui_display_add_compose_render(surface, box, node);
			}
		}
		node = node->brother;
	}
}

/*创建虚拟帧,用于屏幕渲染用,组织用于屏幕渲染的结构*/
static void gui_display_create_virtual_frame()
{
	//SYS_DEBUG("gui: create_virtual_frame, enter");
	if (!gui_display_mutex_lock(0))
	{
		// 获取刷屏信号量失败，直接返回...
		//SYS_DEBUG("gui: create_virtual_frame, exit 0");
		return;
	}

	gui_box_struct **box_order_map = NULL;
	box_order_map = os_mem_alloc(RAM_TYPE_BUFFER_ON, GUI_CACHE_BOX_TOTAL * sizeof(gui_box_struct *));
	if (box_order_map != NULL)
	{
		gui_display_render_clear();
		gui_surface_change_order(); // 检查主副屏的Z轴

		for (unsigned char i = 0; i < GUI_SURFACE_LIST_TOTAL; i++)
		{
			gui_surface_struct *surface = gui_surface_get_surface_by_index(i);

			g_gui_scale.surface = surface;
			gui_surface_calculate_scale(&g_gui_scale);

			gui_display_order_box(surface, box_order_map); // 对所有box，根据Z轴进行一次排序
			gui_box_struct *box = box_order_map[0];
			short count = 0;
			// SYS_DEBUG("surface->x = %d ------------------------", surface->x);
			while (box != NULL)
			{
				if (box->visible)
				{
					g_gui_scale.box = box;
					gui_surface_box_calculate_scale(&g_gui_scale);

					gui_display_add_render(surface, box, box->child);
				}
				box = box_order_map[++count];
			}
		}
		os_mem_free(box_order_map);
	}

#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
	gui_display_render_switch_to_node();
#endif

	gui_surface_set_update_flag(); // 20230612 Taylor.Le, +
	gui_display_mutex_unlock();
	//SYS_DEBUG("gui: create_virtual_frame, exit 1");
}

// 屏幕显示的进程---------------------------------------------------------------------

void gui_display_init()
{
	gui_display_mutex_create();

#if GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_PART
	gui_display_screen_part_init();
#elif (GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_G2D)
	gui_display_screen_g2d_init();
#else
	gui_display_screen_whole_init();
#endif
}

void gui_display_update()
{
	//SYS_DEBUG("gui: display_update");
	// lcd_debug_pinstate(1);
	if (gui_display_mutex_lock(1))
	{
		if (!gui_surface_is_update())
		{
			gui_display_mutex_unlock();
			//SYS_DEBUG("gui: display_update, exit 0");
			return;
		}

#if GUI_RENDER_BUFFER_TOTAL_SUPPORT >= 3
		gui_display_render_switch_to_render();
#endif

		gui_surface_clear_update_flag(); // 虚拟树创建完成后，没有改动时，不需要反复更新

#if (GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_PART)
		gui_display_screen_part_update();
#elif (GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_G2D)
		gui_display_screen_g2d_update();
#else
		gui_display_screen_whole_update();
#endif

		gui_display_mutex_unlock();
	}

	// lcd_debug_pinstate(0);
	//SYS_DEBUG("gui: display_update, exit 1");
}

DATA_RAM_FUNCTION void gui_display_refresh_frame()
{
	gui_display_create_virtual_frame();
}

void gui_display_cache_release(void *window_owner)
{
#if (GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_G2D)
	if (gui_display_mutex_lock(1))
	{
		gui_display_screen_g2d_cache_release((unsigned int)window_owner);
		gui_display_mutex_unlock();
	}
#endif
}
