#include "gui_surface_layout_scroll.h"
#include "debug_info.h"
#include "hal_lcd_area.h"
#include "system_util_math.h"
#include "gui_surface_box_layout_item.h"
#include "gui_surface_cache.h"
#include "gui_window_history.h"
#include "gui_touch_layout_rebound.h"

#include "gui_surface_layout.h"
/*******************************************
**
**对scrollview进行排版，移势
**
********************************************/

/*******************************数据接口************************************/

short gui_surface_layout_scrollview_get_item_id(gui_surface_struct* surface,short index)
{
    gui_box_struct* box = gui_surface_layout_scrollview_get_item(surface,index);
    return (box != NULL) ? box->id : 0;
}

gui_box_struct* gui_surface_layout_scrollview_get_item(gui_surface_struct* surface,short index)
{
    gui_box_struct* box = surface->child;
    short count = 0;
    while(box != NULL)
    {
        if(!box->fix && box->visible)
        {
            if(count++ == index)
                return box;
        }
        box = box->brother;
    }
    return NULL;
}

short gui_surface_layout_scrollview_get_item_index(gui_surface_struct* surface,gui_touch_point_struct* touch_point)
{
    //gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    gui_box_struct* box = surface->child;
    geometry_rect rect_box;
    short count = 0;
    while(box != NULL)
    {
        if(!box->fix && box->visible)
        {
            rect_box.x = box->x;
            rect_box.y = box->y;
            rect_box.width = box->width;
            rect_box.height = box->height;
            if(check_rect_contain_point_xy(&rect_box,touch_point->x,touch_point->y))
                return count;
            count++;
        }
        box = box->brother;
    }
    return -1;
}


/*******************************操作接口************************************/

//根据排版类型，进行排牿
void gui_surface_layout_scrollview_arrange(gui_surface_struct* surface)
{
    const gui_layout_scroll_struct* scroll_config = surface->screen->layout_config;
    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    memcpy(scroll, scroll_config, sizeof(gui_layout_scroll_struct));

    gui_surface_layout_scrollview_commit_position(surface);

    scroll->min_offset = LCD_SIZE_HEIGHT - scroll->height;
    scroll->max_offset = 0;
    scroll->item_gap   = ((scroll->item_gap == 0) ? (LCD_SIZE_HALF_HEIGHT/2) : scroll->item_gap);
}

short gui_surface_layout_scrollview_get_progress(gui_surface_struct* surface)
{
    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    short progress;
    if (scroll->height <= LCD_SIZE_HEIGHT)     // 20220519 Taylor.Le,  avoid div0
    {
        progress = 100;
    }
    else
    {
        progress = ABS(scroll->offset_y) * 100 / (scroll->height - LCD_SIZE_HEIGHT);
    }
	return math_range(progress, 0, 100);
}

//对排版中的子元素，使用指定的偏移
void gui_surface_layout_scrollview_offset(gui_surface_struct* surface,short layout_offset_x,short layout_offset_y)
{
    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    int offset_x = scroll->offset_x;
    int offset_y = scroll->offset_y;
    scroll->offset_x = layout_offset_x;
    scroll->offset_y = layout_offset_y;
    scroll->move_x =  scroll->offset_x - offset_x;
    scroll->move_y =  scroll->offset_y - offset_y;

    gui_surface_layout_scrollview_commit_position(surface);

    gui_window_history_struct* top = gui_window_history_get_top();
    gui_layout_value_struct event =
    {
        .scroll.progress = gui_surface_layout_scrollview_get_progress(surface),   //0-100
    };
    if(top != NULL && top->window && top->window->layout_value_changed)
    {
        top->window->layout_value_changed(&event);
    }
}

//对排版中的子元素，进行指定的偏移
void gui_surface_layout_scrollview_move(gui_surface_struct* surface,short offset_x,short offset_y)
{
    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    scroll->offset_x += offset_x;
    scroll->offset_y += offset_y;
    scroll->move_x =  offset_x;
    scroll->move_y =  offset_y;

    gui_surface_layout_scrollview_commit_position(surface);

    gui_window_history_struct* top = gui_window_history_get_top();
    gui_layout_value_struct event =
    {
        .scroll.progress = gui_surface_layout_scrollview_get_progress(surface),   //0-100
    };
    if(top != NULL && top->window && top->window->layout_value_changed)
    {
        top->window->layout_value_changed(&event);
    }
}


void gui_surface_layout_scrollview_switch_to_y(gui_surface_struct* surface, short progress)
{
    if(gui_touch_layout_rebound_is_moving())
        return;

    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    if(scroll->height <= LCD_SIZE_HEIGHT)
        return;

    int offset_y = scroll->offset_y;
    scroll->offset_y = -(scroll->height - LCD_SIZE_HEIGHT) * progress / 100;
    scroll->move_y =  scroll->offset_y - offset_y;
    gui_surface_layout_scrollview_commit_position(surface);

    gui_window_history_struct* top = gui_window_history_get_top();
    gui_layout_value_struct event =
    {
        .scroll.progress = gui_surface_layout_scrollview_get_progress(surface),   //0-100
    };
    if(top != NULL && top->window && top->window->layout_value_changed)
    {
        top->window->layout_value_changed(&event);
    }


}

void gui_surface_layout_scrollview_switch_to_direction(gui_surface_struct* surface, DIRECTION_TYPE direction)
{
    if(gui_touch_layout_rebound_is_moving())
        return;

    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    if(scroll->height <= LCD_SIZE_HEIGHT)
        return;

    int offset_y = scroll->offset_y;
    if(direction == DIRECTION_TYPE_UP)
    {
        if(scroll->offset_y > 0)
        {
            scroll->offset_y = 0;
        }
        else
            scroll->offset_y += (scroll->height - LCD_SIZE_HEIGHT - 40) /10;

        if(scroll->offset_y >= 0)
            scroll->offset_y = 0;
    }

    else
    {
        if(scroll->offset_y < -scroll->height + LCD_SIZE_HEIGHT)
            scroll->offset_y = -scroll->height + LCD_SIZE_HEIGHT;
        else
            scroll->offset_y -= (scroll->height - LCD_SIZE_HEIGHT - 40)/10;;

        if(scroll->offset_y <= -scroll->height + LCD_SIZE_HEIGHT)
            scroll->offset_y = -scroll->height + LCD_SIZE_HEIGHT;
    }

    scroll->move_y =  scroll->offset_y - offset_y;

    gui_surface_layout_scrollview_commit_position(surface);

    gui_window_history_struct* top = gui_window_history_get_top();
    gui_layout_value_struct event =
    {
        .scroll.progress = gui_surface_layout_scrollview_get_progress(surface),   //0-100
    };
    if(top != NULL && top->window && top->window->layout_value_changed)
    {
        top->window->layout_value_changed(&event);
    }
}



short gui_surface_layout_scrollview_check_max_height(gui_box_struct* box)
{
    if(box == NULL)
        return 0;

    gui_node_struct* node = box->child;
    short height = 0;

    while(node != NULL)
    {

        if(height < (node->y + node->clip_y + node->clip_height))   // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
        {
            height = node->y + node->clip_y + node->clip_height;    // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
        }

        node = node->child;
    }

    return height;

}

void gui_surface_layout_scrollview_commit_position(gui_surface_struct* surface)
{
    gui_layout_scroll_struct* scroll = &surface->layout.scroll;
    gui_box_struct* box = surface->child;
    short /*count = 0, org_y = 0,*/ height = 0;
    while(box != NULL)
    {
        if(!box->fix /* Taylor.Le,-- && box->visible*/)
        {
            box->y += scroll->move_y;
            height = gui_surface_layout_scrollview_check_max_height(box);
        }
        box = box->brother;
    }
    if(scroll->dynamic_height)
    {
        scroll->height = height +scroll->bottom + scroll->top;
    }
    scroll->move_y = 0;
    scroll->move_x = 0;
}

