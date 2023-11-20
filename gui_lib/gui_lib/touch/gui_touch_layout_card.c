
#include "gui_touch.h"
#include "gui_window_history.h"
#include "gui_surface_layout.h"
#include "gui_surface_layout_card.h"

#include "gui_touch_layout_card.h"


void gui_touch_layout_card_click_on_item(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
    GUI_DEBUG("gui: card_click_item");
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

	short index = gui_surface_layout_card_get_item_index(surface, touch_point);
	if(index >= 0) {
		gui_box_struct* item = gui_surface_layout_card_get_item(surface, index);
        if (item != NULL) {
            gui_click_layout_struct event;
            event.id = (unsigned short)item->id;
            event.index = item->value;
            event.x = touch_point->x;
            event.y = touch_point->y;
            if(top_window->click_on_layout_item) {
                top_window->click_on_layout_item(&event);
            }
        }
	}
}

void gui_touch_layout_card_touch_start(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
    GUI_DEBUG("gui: card_touch_start");
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface != NULL)
	{
	    gui_layout_card_struct* card = &surface->layout.card;
        card->last_offset_x = card->offset_x;
        card->last_offset_y = card->offset_y;
	}
}

void gui_touch_layout_card_touch_move(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
    GUI_DEBUG("gui: card_touch_move");
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL) return;

    gui_layout_card_struct* card = &surface->layout.card;
	if(card->total > 1)
	{
		short delta_y = touch_point->y - touch_point->down_y;
		short offset_y = card->last_offset_y + delta_y;
		
		if(offset_y > card->max_offset + 20)
			offset_y = card->max_offset + 20;
		else if(offset_y < card->min_offset)
			offset_y = card->min_offset;// +  (offset_y - card->min_offset) / TOUCH_EMPTY_PULL_SLOW_SPEED;
		
		gui_surface_layout_card_set_offset(surface, 0, offset_y);
        gui_surface_force_update();
	}
}

void gui_touch_layout_card_touch_end(const gui_window_struct* top_window,gui_touch_point_struct* touch_point)
{
    GUI_DEBUG("gui: card_touch_end");
	if(touch_point->curr_direction == DIRECTION_TYPE_NONE)
		return;
		
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface == NULL)
		return;
	
    gui_layout_card_struct* card = &surface->layout.card;
    if (card->total > 1) {
        if(card->offset_y < card->min_offset ) {
    		gui_surface_layout_card_set_offset(surface, 0, card->min_offset);
            gui_surface_force_update();
        }
        else {
            int speed_offset = touch_point->speed_y * TOUCH_REBOUND_MAX_TIME / 1000;
            int offset_y = card->offset_y + speed_offset;
            if(offset_y <= card->min_offset)
            {
                gui_surface_layout_card_set_offset(surface, 0, card->min_offset);
                gui_surface_force_update();
            }
            else
            {
                gui_touch_layout_rebound_auto_moving(top_window, (DIRECTION_TYPE)touch_point->curr_direction, 0, touch_point->speed_y);
            }   
        }
    }
}

void gui_touch_layout_card_touch_cancle(const gui_window_struct* top_window)
{
    GUI_DEBUG("gui: card_touch_cancle");
	gui_surface_struct* surface = gui_surface_get_surface(top_window->screen);
	if(surface)
	{
        gui_layout_card_struct* card = &surface->layout.card;
        card->last_offset_y = (card->last_offset_y / card->item_gap) * card->item_gap;
		gui_surface_layout_card_set_offset(surface, 0, card->last_offset_y);
	}
	gui_surface_force_update();
}



