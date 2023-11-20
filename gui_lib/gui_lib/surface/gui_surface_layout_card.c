
#include "system_util_math.h"
#include "gui_display_draw_lib.h"
#include "gui_surface_node.h"
#include "gui_window_history.h"

#include "gui_surface_layout_card.h"

#define GUI_CARD_LIST_TOP   5

static short gui_surface_layout_card_check_x(short x, short node_width, float scale, short width, short card_width)
{
    short x_ret;
    short x_center_dis = ((width/2) - (x + (node_width/2)))*scale;
    x_center_dis = (card_width/2) - x_center_dis;
    x_ret = x_center_dis - (node_width/2);
    return x_ret;
}

static short gui_surface_layout_card_check_y(short y, short node_height, float scale, short height, short card_height)
{
    short y_ret;
    short y_center_dis = (card_height/2) - ((height/2) - (y + (node_height/2)))*scale;
    y_ret = y_center_dis - (node_height/2);
    return y_ret;
}


// y = func(dx) = a*dx*dx + b*dx
static int gui_surface_layout_card_get_item_position_by_index(gui_layout_card_struct* card, unsigned short index, unsigned short* bot_l)
{
    //if (index == card->total-1 && index == card->curr_index) {
    //    *bot_l = 0;
    //    return GUI_CARD_LIST_TOP;
    //}

    float dx = (float)card->item_gap;
    dx = (index * dx + card->offset_y) / dx;
    if (dx > -1.0f) {
        if (dx < 0.0f) {
            *bot_l = 1;
            return GUI_CARD_LIST_TOP;
        }
        *bot_l = 0;
        return (int)((card->param_a*dx + card->param_b)*dx) + GUI_CARD_LIST_TOP;    // ((56*dx + 14)*dx) + GUI_CARD_LIST_TOP;
    }
    return -1;
}

static int gui_surface_layout_card_get_index_by_offset(gui_layout_card_struct* card, short offset)
{
    int index = 0;
    if (card->total > 2) {
        index = (card->item_gap - offset) / card->item_gap;
    }
    if (index >= card->total) {
        index = card->total-1;
    }
    GUI_DEBUG("gui: card_get_index_by_offset, index=%d, offset=%d", index, offset);
    return index;
}

static unsigned int gui_surface_layout_card_get_size(gui_layout_card_struct* card, unsigned int pos_y, unsigned short bot_lvl, unsigned short index)
{
    //if (index == card->total-1 && index == card->curr_index) {
    //    return card->bg_img_w;
    //}
    
    unsigned int sz = LCD_SIZE_WIDTH * 7 / 10;
    sz = sz + (LCD_SIZE_WIDTH-sz) * pos_y / LCD_SIZE_HEIGHT;
    while(bot_lvl > 0) {
        sz = sz * 9 / 10;
        bot_lvl --;
    }
    return sz;
}

static void gui_surface_layout_card_adjust_position_with_bg_scale(gui_box_struct* box, int card_w, int card_h)
{
    gui_node_struct* bg_node;
    gui_node_struct* node;
    gui_draw_struct* draw;
    int offset_x = 0;

    if (box->scale == 1.0f) return;

	gui_widget_struct* widget = box->widget;
    gui_mix_struct*    mix    = (gui_mix_struct *)widget->children;
    
	if(widget != NULL && widget->child_num > 0 && mix != NULL) {
        node = box->child;
        while (node!=NULL){
            draw = mix->data;
            if (draw->type == TYPE_GUI_DRAW_PICTURE) {
                gui_image_struct* img = (gui_image_struct*)draw;
                picture_info_struct* pic = (picture_info_struct*)img->data;
                //GUI_DEBUG("gui: card_i, node_x=%d, node_y=%d", img->x, img->y);
                node->x = gui_surface_layout_card_check_x(img->x, node->width, box->scale, widget->width, card_w);
                node->y = gui_surface_layout_card_check_y(img->y, node->height, box->scale, widget->height, card_h);
            }
            else if (draw->type == TYPE_GUI_DRAW_TEXT) {
                gui_font_struct* txt = (gui_font_struct*)draw;
                //GUI_DEBUG("gui: card_t, node_x=%d, node_y=%d", txt->x, txt->y);
                node->x = gui_surface_layout_card_check_x(txt->x, txt->width, box->scale, widget->width, card_w);
                node->y = gui_surface_layout_card_check_y(txt->y, txt->height, box->scale, widget->height, card_h);
            }
            //GUI_DEBUG("gui: card_o, node_x=%d, node_y=%d", node->x, node->y);
            node = node->brother;
            mix ++;
        }
    }
}

static void gui_surface_layout_card_commit_position(gui_surface_struct* surface)
{
	gui_layout_card_struct* card = &surface->layout.card;
    int card_y;
    unsigned short bot_l = 0;
    unsigned short card_width;
    unsigned short card_height;
	unsigned short index = 0;
	gui_box_struct* box = surface->child;

    if (card->total == 0) return;
    //GUI_DEBUG("gui: card_commit, index=%d, offset=%d", card->curr_index, card->offset_y);
	while(box != NULL)
	{
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
		{
		    card_y = gui_surface_layout_card_get_item_position_by_index(card, index, &bot_l);
            if (card_y >= 0 && card_y < LCD_SIZE_HEIGHT) {
                GUI_DEBUG("gui: card[%d], x=%d, y=%d, w=%d, h=%d", index, box->x, box->y, box->width, box->height);
                card_width = gui_surface_layout_card_get_size(card, card_y, bot_l, index);
                box->scale = ((float)card_width) / ((float)card->bg_img_w);
                card_height = (unsigned short)(box->scale * card->bg_img_h);
                gui_surface_layout_card_adjust_position_with_bg_scale(box, card_width, card_height);

                gui_widget_struct* widget = box->widget;
                box->x = widget->x + (widget->width - card_width)/2;
                box->y = card_y;
                box->width = card_width;
                box->height = card_height;
                //box->visible = 1;
                GUI_DEBUG("gui: card[%d], x=%d, y=%d, w=%d, h=%d, cw=%d, ch=%d", index, box->x, box->y, box->width, box->height, card_width, card_height);
            }
            else {
                //box->visible = 0;
                box->y = LCD_SIZE_HEIGHT*2;
            }
			index++;
		}
		box = box->brother;
	}
	card->total = index;
}


static void gui_suyrface_layout_card_init(gui_surface_struct* surface)
{
	gui_layout_card_struct* card = &surface->layout.card;
    card->total     = gui_surface_layout_card_count(surface);
    card->min_offset = -(card->item_gap * (card->total-1));
    card->max_offset = card->item_gap;
}


/*******************************操作接口************************************/
//根据排版类型，进行排版
void gui_surface_layout_card_arrange(gui_surface_struct* surface)
{
	const gui_layout_card_struct* layout_config = (const gui_layout_card_struct*)surface->screen->layout_config;
	gui_layout_card_struct* card = &surface->layout.card;

    memset(card, 0, sizeof(gui_layout_card_struct));
    card->bg_img_w  = layout_config->bg_img_w;
    card->bg_img_h  = layout_config->bg_img_h;
    card->param_a   = LCD_SIZE_HALF_HEIGHT * 0.3f;
    card->param_b   = LCD_SIZE_HALF_HEIGHT * 0.1f;
    card->total     = gui_surface_layout_card_count(surface);
    card->item_gap  = 50;
    card->min_offset = -(card->item_gap * (card->total-1));
    card->max_offset = card->item_gap;

    if (card->total == 1) {
        card->curr_index = 0;
        card->offset_y = card->item_gap;     // 0;
    }
    else if (card->total == 2) {
        card->curr_index = 0;
        card->offset_y = card->item_gap;
    }
    else {
        card->curr_index = 1;
        card->offset_y = 0;
    }
    gui_surface_layout_card_commit_position(surface);
}

//对排版中的子元素，进行指定的偏移
void gui_surface_layout_card_move(gui_surface_struct* surface, int move)
{
	gui_layout_card_struct* card = &surface->layout.card;
    if (card->total > 1) {
        //GUI_DEBUG("gui: card_move, move=%d, min=%d, max=%d", move, card->min_offset, card->max_offset);

        card->offset_y += move;
        if (card->offset_y < card->min_offset) card->offset_y = card->min_offset;
        if (card->offset_y > card->max_offset) card->offset_y = card->max_offset;
        // ...
        card->curr_index = gui_surface_layout_card_get_index_by_offset(card, card->offset_y);
        gui_surface_layout_card_commit_position(surface);
        gui_surface_commit();
    }
}

//更新排版
void gui_surface_layout_card_updata_arrange(gui_surface_struct* surface)
{
    gui_surface_layout_card_commit_position(surface);
}

//对排版中的子元素，使用指定的偏移
void gui_surface_layout_card_set_offset(gui_surface_struct* surface, short layout_offset_x, short layout_offset_y)
{
    GUI_DEBUG("gui: card_offset");
	gui_layout_card_struct* card = &surface->layout.card;
	card->offset_x = layout_offset_x;
	card->offset_y = layout_offset_y;
    card->curr_index = gui_surface_layout_card_get_index_by_offset(card, card->offset_y);
    gui_surface_layout_card_commit_position(surface);

	gui_window_history_struct* top = gui_window_history_get_top();
	if(top != NULL && top->window && top->window->layout_value_changed)
	{
	    gui_layout_value_struct event = {.card.id=0, .card.index=card->curr_index};
		top->window->layout_value_changed(&event);
	}
}

void gui_surface_layout_card_move_end(gui_surface_struct* surface)
{
    GUI_DEBUG("gui: card_move_end");
	gui_layout_card_struct* card = &surface->layout.card;
    if (card->total > 1) {
        // ...
    }
}

void gui_surface_layout_card_exit(void)
{
    GUI_DEBUG("gui: card_exit");
}

short gui_surface_layout_card_get_item_index(gui_surface_struct* surface, gui_touch_point_struct* touch_point)
{
	gui_layout_card_struct* card = &surface->layout.card;
    GUI_DEBUG("gui: card_get_item_index, total=%d, curr=%d", card->total, card->curr_index);
    if (card->total) {
        if (card->curr_index == card->total-1) {
            float scale;
            int card_y;
            unsigned short card_width;
            unsigned short card_height;
            unsigned short bot_l;
            
            card_y = gui_surface_layout_card_get_item_position_by_index(card, card->curr_index, &bot_l);
            card_width = gui_surface_layout_card_get_size(card, card_y, bot_l, card->curr_index);
            scale = ((float)card_width) / ((float)card->bg_img_w);
            card_height = (unsigned short)(scale * card->bg_img_h);
            if (touch_point->y > (card_y+card_height)) {
                GUI_DEBUG("gui: card_get_item_index, error! %d, %d", card_y, card_height);
                return -1;
            }
        }
        return card->curr_index;
    }
    return -1;
}

gui_box_struct* gui_surface_layout_card_get_item(gui_surface_struct* surface, short index)
{
	gui_box_struct* box = surface->child;
	short count = 0;
	while(box != NULL) {
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM) {
			if(count == index && box->visible) {
				return box;
            }
            count ++;
		}
		box = box->brother;
	}
	return NULL;
}

unsigned short gui_surface_layout_card_count(gui_surface_struct* surface)
{
	gui_layout_card_struct* card = &surface->layout.card;
	unsigned short count = 0;
	gui_box_struct* box = surface->child;
	while(box != NULL) {
		if(box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM) {
			count++;
		}
		box = box->brother;
	}
	card->total = count;
}

void gui_surface_layout_card_set_index(gui_surface_struct* surface, short index)
{
	gui_layout_card_struct* card = &surface->layout.card;
    if (index < card->total) {
        short offset = card->item_gap * index;
        gui_surface_layout_card_set_offset(surface, 0, offset);
    }
}

void gui_surface_layout_card_rolkey_handler(gui_surface_struct* surface, short dir) // dir: 1 inc; -1 dec
{
    short index = -1;
	gui_layout_card_struct* card = &surface->layout.card;
    if (dir == 1) {
        if (card->curr_index < card->total-1) {
            index = card->curr_index + 1;
        }
    }
    else if (dir == -1) {
        if (card->curr_index > 0) {
            index = card->curr_index - 1;
        }
    }
    if (index != -1) {
        gui_surface_layout_card_set_index(surface, index);
    }
}


