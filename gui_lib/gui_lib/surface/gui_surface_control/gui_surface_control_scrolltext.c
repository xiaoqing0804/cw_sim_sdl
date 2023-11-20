
#include "sys_timer.h"
#include "sys_timer_thread.h"
#include "debug_info.h"
#include "app_task_main.h"
#include "font_convert.h"

#include "gui_util_text_string.h"
#include "gui_surface.h"
#include "gui_surface_cache.h"
#include "gui_surface_node.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_scrolltext.h"

#define GUI_SCROLLTEXT_SKIP     16      // x - slide.
#define GUI_SCROLLTEXT_TOUT     500     // timer dur.

// timer event proc
void gui_scrolltext_timer_handler(unsigned int timer, void* param)
{
    gui_box_struct* box = (gui_box_struct*)param;
    int value = box->width/2 - box->value;

    //SYS_DEBUG("scrolltext: timer_handler, bv=%d, bw=%d\n", box->value, box->width);

    if ((box != NULL) && (box->type != TYPE_GUI_CONTROL_SCROLL_TEXT)) {
        application_stop_user_timer(timer);
        return;
    }

    /// ...
    if (box->flags & 0x80) {    // first on timer, change timeout.
        application_restart_user_timer((unsigned int)box->data, GUI_SCROLLTEXT_TOUT);
        box->flags &= 0x7F;
    }
    else {
        // change node's position.
        gui_node_struct* node = box->child;
        if (node != NULL)  node = node->child;

        while(node != NULL) {
            node->x -= GUI_SCROLLTEXT_SKIP;
            if (node->x < value) {
                node->x = node->x + box->value + box->width/2 + 10;
            }
            //20221026 Taylor.Le, - node->clip_x = node->x;     // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
            node = node->child;
        }
        gui_surface_commit();
    }
}

static void gui_surface_control_scrolltext_arrange_string(gui_box_struct* box, unsigned char* str)
{
    gui_widget_struct* widget = box->widget;
    unsigned int tw, th, tl;//, tx;
    gui_font_struct* text = (gui_font_struct*)widget->children;

    set_font_size(text->size);
    get_font_string_meastrue(str, &tw, &th, &tl);
    //SYS_DEBUG("scrolltext: create, tw=%d, bw=%d\n", tw, box->width);

    if (tw > box->width) {
        box->data = (void*)application_start_user_timer(1000, gui_scrolltext_timer_handler, box);
        box->flags |= 0x80;
    }
	else {
		box->flags &= 0x7F;
	}
    box->child = gui_surface_box_label_arrange_textbox(box,text,str,0, 0,box->width,box->height);
    box->value = tw;

    // re arrang
    if (box->flags & 0x80) {
        gui_node_struct* node = box->child;
        if (node != NULL) node = node->child;
        if (node != NULL) {
            short lay_x = node->x;
            while(node != NULL) {
                node->x = node->x - lay_x + GUI_SCROLLTEXT_SKIP;
                node = node->child;
            }
        }
    }
}


void gui_surface_control_scrolltext_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;

    if (widget != NULL && widget->child_num > 0) {
        unsigned int tw, th, tl;//, tx;
        gui_font_struct* text = (gui_font_struct*)widget->children;
        unsigned char buff[16] = {0};
        unsigned char* str = gui_util_text_string_get_string_from_font(text,buff,16);
        if(str == NULL) return;

        gui_surface_control_scrolltext_arrange_string(box, str);
    }
}


void gui_surface_control_scrolltext_exit(gui_box_struct* box)
{
    box->data = (void*)application_stop_user_timer((unsigned int)box->data);
}

void gui_surface_control_scrolltext_change_string(gui_box_struct* box, unsigned char* string)
{
    if (box != NULL){
        gui_widget_struct* widget = box->widget;
        if (widget != NULL && widget->child_num > 0) {
            unsigned int tw, th, tl;//, tx;
            gui_font_struct* text = (gui_font_struct*)widget->children;
            if(string == NULL)  return;

            //
            gui_surface_cache_remove_nodes(box->child);
            box->child = NULL;
            box->data = (void*)application_stop_user_timer((unsigned int)box->data);

            gui_surface_control_scrolltext_arrange_string(box, string);
        }
    }
}



