#include "gui_surface.h"
#include "system_util_all.h"
#include "gui_display_render.h"
#include "gui_surface_cache.h"
#include "gui_surface_layout.h"
#include "gui_display.h"
#include "gui_surface_scale.h"


static gui_surface_struct g_surface_1 = {0};
static gui_surface_struct g_surface_2 = {0};
static gui_surface_struct* g_main_surface = &g_surface_1;
static gui_surface_struct* g_vice_surface = &g_surface_2;
static gui_surface_struct* g_surfaces[GUI_SURFACE_LIST_TOTAL] = {0};
static unsigned char g_virtual_update = 0;
static unsigned char g_virtual_load = 1;   //渲染不在同一个线程，所以在控制加载完成后才渲染

static gui_surface_struct* gui_surface_find_surface(const gui_screen_struct* screen)
{
	gui_surface_struct* surface = NULL;
	for(unsigned char i = 0; i < GUI_SURFACE_LIST_TOTAL; i++)
	{
		surface = g_surfaces[i];
		if(surface && surface->screen == screen)
			return surface;
	}
	return NULL;
}

static gui_box_struct* gui_surface_find_box(gui_surface_struct* surface,unsigned short id)
{
	if(surface != NULL)
	{
		gui_box_struct* box = surface->child;
		while(box != NULL)
		{
			if(id == box->id)
				return box;
			box = box->brother;
		}
	}
	return NULL;
}

static gui_box_struct* gui_surface_create_surface(gui_surface_struct* surface, const gui_screen_struct* screen)
{
	if(screen == NULL || screen->child_num == 0 )
		return NULL;

	gui_box_struct* start_box = NULL;
	gui_box_struct* end_box = NULL;
	gui_widget_struct* widget = (gui_widget_struct*)screen->children;
	for(short i = 0; i < screen->child_num; i++)
	{
		if(!gui_surface_layout_is_delay_create_widget(screen,widget))
		{
			gui_box_struct* box = gui_surface_box_create(surface, widget);
			if(start_box == NULL)
				start_box = box;
			else
				end_box->brother = box;
			end_box = box;
		}
		widget++;
	}
	return start_box;
}


void gui_surface_change_order()
{
	unsigned char mainOrderBig = g_main_surface->order > g_vice_surface->order;
	g_surfaces[0] = mainOrderBig ? g_vice_surface : g_main_surface;
	g_surfaces[1] = mainOrderBig ? g_main_surface : g_vice_surface;
}

gui_surface_struct* gui_surface_get_surface_by_index(unsigned char index)
{
	return g_surfaces[index];
}

gui_surface_struct* gui_surface_get_top_surface()
{
	return g_surfaces[1];
}

gui_surface_struct* gui_surface_get_main_surface()
{
	return g_main_surface;
}

gui_surface_struct* gui_surface_get_vice_surface()
{
	return g_vice_surface;
}

unsigned char gui_surface_is_at_orgin()
{
	return (g_main_surface->x == 0) &&(g_main_surface->y == 0);
}

short gui_surface_main_get_offset_x()
{
	return g_main_surface->x;
}

short gui_surface_main_get_offset_y()
{
	return g_main_surface->y;
}

short gui_surface_vice_get_offset_x()
{
	return g_vice_surface->x;
}

short gui_surface_vice_get_offset_y()
{
	return g_vice_surface->y;
}

unsigned char gui_surface_is_update()
{
	return g_virtual_load && g_virtual_update;
}

void gui_surface_clear_update_flag()
{
	g_virtual_update = 0;
}

void gui_surface_set_update_flag()		// 20230612 Taylor.Le, +
{
	g_virtual_update = 1;
}

void gui_surface_force_update()
{
	gui_display_refresh_frame();
	// 20230612 Taylor.Le, -	g_virtual_update = 1;
}




//屏幕数组转化---------------------------------------------------------------------

//把屏幕数组转化为组织结构(主屏的组织结构)
void gui_surface_create_main_surface(const gui_window_struct* window)
{
	const gui_screen_struct* screen = window->screen;
	g_virtual_load = 0;
	g_main_surface->x = 0;
	g_main_surface->y = 0;
	g_main_surface->order = screen->order;
	g_main_surface->scale = 1.0f;
	g_main_surface->screen = (gui_screen_struct*)screen;
	g_main_surface->window = (gui_window_struct*)window;
	g_main_surface->child = gui_surface_create_surface(g_main_surface,screen);
	gui_surface_change_order();   //检查主副屏的Z轴
	gui_surface_layout_arrange(g_main_surface);
	g_virtual_update = 1;
}

//把屏幕数组转化为组织结构(副屏的组织结构)
void gui_surface_create_vice_surface(const gui_window_struct* window)
{
	const gui_screen_struct* screen = window->screen;
	g_virtual_load = 0;
	g_vice_surface->x = LCD_SIZE_WIDTH;
	g_vice_surface->y = 0;
	g_vice_surface->order = screen == NULL ? 0 : screen->order;
	g_vice_surface->scale = 1.0f;
	g_vice_surface->screen = (gui_screen_struct*)screen;
	g_vice_surface->window = (gui_window_struct*)window;        // Taylor.Le, +
	g_vice_surface->child = gui_surface_create_surface(g_vice_surface,screen);
	gui_surface_change_order();   //检查主副屏的Z轴
	gui_surface_layout_arrange(g_vice_surface);
	g_virtual_update = 1;
}

void gui_surface_exit_surface(gui_surface_struct* surface)
{
	gui_box_struct* box = surface->child;
	while(box != NULL)
	{
		gui_surface_box_exit(box);
		box = box->brother;
	}
}

void gui_surface_swap_surface()
{
	swap_front_back((void**)&g_main_surface,(void**)&g_vice_surface);
}

void gui_surface_clear_main_surface()
{
    if (g_main_surface->window != NULL) {
        gui_display_cache_release(g_main_surface->window);
    }

	gui_surface_exit_surface(g_main_surface);
	gui_surface_cache_remove_surface(g_main_surface);
	memset(g_main_surface, 0 , sizeof(gui_surface_struct));
}

void gui_surface_clear_vice_surface()
{
    if (g_vice_surface->window != NULL) {
        gui_display_cache_release(g_vice_surface->window);
    }

	gui_surface_exit_surface(g_vice_surface);
	gui_surface_cache_remove_surface(g_vice_surface);
	memset(g_vice_surface, 0 , sizeof(gui_surface_struct));
}

void gui_surface_clear_all_surface()
{
    if (g_main_surface->window != NULL) {
        gui_display_cache_release(g_main_surface->window);
    }
    if (g_vice_surface->window != NULL) {
        gui_display_cache_release(g_vice_surface->window);
    }

	gui_surface_exit_surface(g_main_surface);
	gui_surface_exit_surface(g_vice_surface);

	memset(g_main_surface, 0 , sizeof(gui_surface_struct));
	memset(g_vice_surface, 0 , sizeof(gui_surface_struct));

	gui_surface_cache_clear_box();
	gui_surface_cache_clear_node();
}

void gui_surface_load_surface()
{
	gui_display_refresh_frame();
	g_virtual_load = 1;
}



//界面改变--------------------------------------------------------------------------

void gui_surface_main_surface_move(short x,short y)
{
	g_main_surface->x += x;
	g_main_surface->y += y;
}

void gui_surface_main_surface_move_to(short x,short y)
{
	g_main_surface->x = x;
	g_main_surface->y = y;
}


void gui_surface_main_surface_move_x(short x)
{
	g_main_surface->x += x;
}

void gui_surface_main_surface_move_to_x(short x)
{
	g_main_surface->x = x;
}

void gui_surface_main_surface_move_y(short y)
{
	g_main_surface->y += y;
}

void gui_surface_main_surface_move_to_y(short y)
{
	g_main_surface->y = y;
}


void gui_surface_main_surface_order(char order)
{
	g_main_surface->order = order;
	gui_surface_change_order();
}

void gui_surface_main_surface_scale_all(float scale)
{
	g_main_surface->scale = scale;
	//gui_surface_scale(g_main_surface,scale);
}

void gui_surface_main_surface_scale_by(float scale)
{
	g_main_surface->scale *= scale;
	//gui_surface_scale_offset(g_main_surface,scale);
}

void gui_surface_vice_surface_move(short x,short y)
{
	g_vice_surface->x += x;
	g_vice_surface->y += y;
}

void gui_surface_vice_surface_move_to(short x,short y)
{
	g_vice_surface->x = x;
	g_vice_surface->y = y;
}


void gui_surface_vice_surface_move_x(short x)
{
	g_vice_surface->x += x;
}

void gui_surface_vice_surface_move_to_x(short x)
{
	g_vice_surface->x = x;
}


void gui_surface_vice_surface_move_y(short y)
{
	g_vice_surface->y += y;
}

void gui_surface_vice_surface_move_to_y(short y)
{
	g_vice_surface->y = y;
}


void gui_surface_vice_surface_order(char order)
{
	g_vice_surface->order = order;
	gui_surface_change_order();
}

void gui_surface_vice_surface_scale_all(float scale)
{
	g_vice_surface->scale = scale;
    //gui_surface_scale(g_vice_surface, scale);
}

void gui_surface_vice_surface_scale_by(float scale)
{
	g_vice_surface->scale *= scale;
	//gui_surface_scale_offset(g_vice_surface,scale);
}

//当改变结束时，需要保存改变，才会显示到屏幕上
void gui_surface_commit()
{
	gui_box_struct* box = NULL;
	for(unsigned char i = 0; i < GUI_SURFACE_LIST_TOTAL; i++)
	{
		box = g_surfaces[i]->child;
		while(box != NULL)
		{
			if(box->update)
			{
				box->update = 0;
				gui_surface_box_commit(box);
			}
			box = box->brother;
		}
	}
	gui_surface_force_update();
}


//查找屏幕内的组织,但发生改变时，需要改变的是组织
gui_box_struct* gui_surface_get_box(const gui_screen_struct* screen,unsigned short id)
{
	return gui_surface_find_box(gui_surface_find_surface(screen),id);
}

gui_box_struct* gui_surface_get_box_by_id(gui_surface_struct* surface,unsigned short id)
{
	return gui_surface_find_box(surface,id);
}

gui_box_struct* gui_surface_get_box_from_main_surface(unsigned short id)
{
	return gui_surface_find_box(g_main_surface,id);
}

gui_box_struct* gui_surface_get_box_by_type(gui_surface_struct* surface, unsigned char box_type)
{
	gui_box_struct* box = surface->child;
	while(box != NULL) {
		if(box->type == box_type)
		{
            return box;
		}
        box = box->brother;
	}
    return NULL;
}


gui_box_struct* gui_surface_get_box_by_index(const gui_screen_struct* screen,short index)
{
	gui_surface_struct* surface = gui_surface_find_surface(screen);
	if(surface != NULL)
	{
		gui_box_struct* box = surface->child;
		while(box != NULL)
		{
			if(index-- <= 0)
				return box;
			box = box->brother;
		}
	}
	return NULL;
}

gui_box_struct* gui_surface_get_by_position(gui_surface_struct* surface, short x, short y)
{
	gui_box_struct* top_box = NULL;
    gui_box_struct* box = surface->child;
    geometry_rect rect_box;
    while(box != NULL)
    {
        if(box->visible && box->id > 0)
        {
            rect_box.x = box->x;
            rect_box.y = box->y;
            rect_box.width = box->width;
            rect_box.height = box->height;
            if(check_rect_contain_point_xy(&rect_box, x, y)) {
                top_box = box;
			}
        }
        box = box->brother;
    }
    return top_box;
}



gui_surface_struct* gui_surface_get_surface(const gui_screen_struct* screen)
{
	return gui_surface_find_surface(screen);
}

gui_surface_struct* gui_surface_get_surface_by_window(gui_window_struct* window)
{
	gui_surface_struct* surface = NULL;
	for(unsigned char i = 0; i < GUI_SURFACE_LIST_TOTAL; i++)
	{
		surface = g_surfaces[i];
		if(surface && surface->window == window)
			return surface;
	}
	return NULL;
}


void gui_surface_add_box(gui_surface_struct* surface, gui_box_struct* box)
{
    if (surface == NULL || box == NULL) return;

    if (surface->child == NULL) {
        surface->child = box;
    }
    else {
        gui_box_struct* pre_box = surface->child;
        while(pre_box->brother != NULL) {
            pre_box = pre_box->brother;
        }
        pre_box->brother = box;
    }
    box->brother = NULL;
}

void gui_surface_remove_box(gui_surface_struct* surface, gui_box_struct* box)
{
    if (surface == NULL || surface->child == NULL || box == NULL) return;

    if (surface->child == box) {
        surface->child = box->brother;
    }
    else {
        gui_box_struct* pre_box = surface->child;
        while(pre_box->brother != NULL) {
            if (pre_box->brother == box) {
                pre_box->brother = box->brother;
                break;
            }
            pre_box = pre_box->brother;
        }
    }
	box->brother = NULL;
}

void gui_surface_take_box_to_finally(gui_surface_struct* surface, gui_box_struct* box)
{
    if (surface == NULL || surface->child == NULL) return;
    if (box == NULL || box->brother == NULL) return;

    if (surface->child == box) {
        // at first
        surface->child = box->brother;
        box->brother = NULL;
    }
    else {
        gui_box_struct* pre_box = surface->child;

        while(pre_box != NULL && pre_box->brother != box) {
            pre_box = pre_box->brother;
        }
        if (pre_box == NULL) {
            SYS_DEBUG("box not fond!");
            return; // error.
        }
        pre_box->brother = box->brother;
        box->brother = NULL;
    }
    gui_surface_add_box(surface, box);
}


