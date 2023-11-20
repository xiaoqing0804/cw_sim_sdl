
#include "sys_timer.h"
#include "sys_timer_thread.h"
#include "debug_info.h"
#include "app_task_main.h"

#include "gui_surface_cache.h"
#include "gui_surface_node.h"
#include "gui_surface_box_image.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_switch.h"

#define GUI_SWITCH_SLID_FLAG    0x80
#define GUI_SWITCH_FRAME_MSK    0x7F

static void gui_switch_image_arrange(gui_box_struct* box, gui_node_struct* node, const gui_switch_struct* swt)
{
    const picture_info_struct* pic;
    if (box->value == GUI_SWT_ON){
        pic = swt->frame_pics[swt->frame_num - 1];
    }
    else {
        pic = swt->frame_pics[0];
    }
	node->type = TYPE_GUI_DRAW_PICTURE;
	node->id = swt->id;
	node->x = gui_surface_node_check_x(box, swt->align, 0, pic->width);
	node->y = gui_surface_node_check_y(box, swt->align, 0, pic->height);
    node->draw = swt;
	node->data = (void*)pic;
	gui_surface_node_check_clip(box, node, pic->width, pic->height);
}

gui_node_struct* gui_switch_arrange(gui_box_struct* box, const gui_switch_struct* swt)
{
	gui_node_struct* node = gui_surface_cache_add_node();
    gui_switch_image_arrange(box, node, swt);
    return node;
}

// timer event proc
void gui_switch_timer_handler(unsigned int timer, void* param)
{
    const picture_info_struct* pic;
    unsigned int ret = 1, frame;
    gui_box_struct* box = (gui_box_struct*)param;
    gui_widget_struct* widget = box->widget;
    gui_switch_struct* swt = (gui_switch_struct*)widget->children;
    
    if ((box != NULL) && (box->type != TYPE_GUI_CONTROL_SWITCH)) {
        application_stop_user_timer(timer);
        return;
    }

    // .... 
    frame = box->flags & GUI_SWITCH_FRAME_MSK;
    if (box->value == GUI_SWT_ON) {
        frame ++;
        if (frame == swt->frame_num-1) {
            ret = 0;
        }
    }
    else {
        frame --;
        if (frame == 0) {
            ret = 0;
        }
    }

    pic = swt->frame_pics[frame];
    box->child->data = (void*)pic;

    if (ret == 0) {
        application_stop_user_timer((unsigned int)box->data);
        box->data = NULL;
        box->flags = 0;
    }
    else {
        box->flags = frame | GUI_SWITCH_SLID_FLAG;
    }
    
    gui_surface_commit();
}

// touch event proc
void gui_surface_control_switch_on_touch(gui_box_struct* box)
{
    unsigned int frame;
    const picture_info_struct* pic;
    gui_widget_struct* widget = box->widget;
    gui_switch_struct* swt = (gui_switch_struct*)widget->children;
    
    if ((box != NULL) && (box->type != TYPE_GUI_CONTROL_SWITCH)) {
        return;
    }
    
    // .... 
    if (box->flags & GUI_SWITCH_SLID_FLAG) {
        // the switch is sliding.
        return;
    }
    
    if (box->value == GUI_SWT_ON) {
        frame = swt->frame_num-1;
        box->value = GUI_SWT_OFF;
    }
    else {
        frame = 0;
        box->value = GUI_SWT_ON;
    }

    pic = swt->frame_pics[frame];
    box->child->data = (void*)pic;
    
    if (swt->frame_num > 2) {
        box->data = (void*)application_start_user_timer(250, gui_switch_timer_handler, box);
        box->flags = frame | GUI_SWITCH_SLID_FLAG;
    }
    else {
        box->flags = 0;
    }
    gui_surface_commit();
}

void gui_surface_control_switch_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if ((widget != NULL) && (widget->child_num > 0)) {
        gui_switch_struct* swt = (gui_switch_struct*)widget->children;
        if (swt->frame_num >= 2) {
            box->value = swt->init_status;
            box->child = gui_switch_arrange(box, swt);
        }
    }
}

void gui_surface_control_switch_exit(gui_box_struct* box)
{
    if (box->flags & GUI_SWITCH_SLID_FLAG) {
        application_stop_user_timer((unsigned int)box->data);
        box->data = NULL;
        box->flags = 0;
    }
}

void gui_surface_control_switch_on(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    gui_switch_struct* swt = (gui_switch_struct*)widget->children;

    box->value = GUI_SWT_ON;
    gui_switch_image_arrange(box, box->child, swt);
}

void gui_surface_control_switch_off(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    gui_switch_struct* swt = (gui_switch_struct*)widget->children;

    box->value = GUI_SWT_OFF;
    gui_switch_image_arrange(box, box->child, swt);
}

int gui_surface_control_switch_take(gui_box_struct* box)
{
    return box->value;
}


