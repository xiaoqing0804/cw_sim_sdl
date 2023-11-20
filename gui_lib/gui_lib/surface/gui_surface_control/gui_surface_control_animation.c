
#include "sys_timer.h"
#include "sys_timer_thread.h"
#include "debug_info.h"
#include "app_task_main.h"

#include "gui_surface_cache.h"
#include "gui_surface_node.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_animation.h"

static gui_animation_struct* gui_widget_get_animation_by_id(gui_box_struct* box, unsigned int id)
{
    const gui_widget_struct* widget = box->widget;

    gui_animation_struct* animation = (gui_animation_struct*)widget->children;
    unsigned int ani_num = widget->child_num;

    while(ani_num) {
        ani_num --;

        if (animation->id == id) {
            return animation;
        }
        animation ++;
    }
    return NULL;
}

static short gui_surface_ani_check_x(gui_box_struct* box, gui_animation_frame_struct* frame)
{
    short x;
    if(GUI_ALIGN_IS_HCENTER(frame->align))
        x = (box->width - frame->picture->width) / 2;
    else if(GUI_ALIGN_IS_RIGHT(frame->align))
        x = box->width - frame->picture->width - 1;
    else if(GUI_ALIGN_IS_LEFT(frame->align))
        x = 0;
    else
        x = frame->x;
    return x;
}

static short gui_surface_ani_check_y(gui_box_struct* box, gui_animation_frame_struct* frame)
{
    short y;
    if(GUI_ALIGN_IS_VCENTER(frame->align) )
        y = (box->height - frame->picture->height) / 2;
    else if(GUI_ALIGN_IS_BOTTOM(frame->align))
        y = box->height - frame->picture->height - 1;
    else if(GUI_ALIGN_IS_TOP(frame->align))
        y = 0;
    else
        y = frame->y;
	return y;
}

// 20230202 Taylor.Le, +
static void gui_controller_animation_reset_frame(gui_box_struct* ani_box)
{
    gui_node_struct* node = ani_box->child;
    while(node != NULL) {
        // update node's frame
        gui_animation_struct* animation = gui_widget_get_animation_by_id(ani_box, node->id);
        if (animation != NULL) {
            gui_animation_frame_struct* frame = (gui_animation_frame_struct*)&animation->frames[0];
            unsigned int dur_ticks = (frame->duration+49)/50;
            node->x = gui_surface_ani_check_x(ani_box, frame);
            node->y = gui_surface_ani_check_y(ani_box, frame);
            node->width = frame->picture->width;        // 20221122 Taylor.Le,
            node->height = frame->picture->height;      // 20221122 Taylor.Le,
            node->data = (void*)frame->picture;
            node->value = (dur_ticks<<16) + 0; // dur-ticks & frame-index;
            gui_surface_node_check_clip(ani_box, node, frame->picture->width, frame->picture->height);
        }

        // next ani.
        node = node->brother;
    }

}

static void gui_controller_animation_timer_handler(unsigned int timer_id, void* argument)
{
    gui_box_struct* ani_box = (gui_box_struct*)argument;

    //GUI_DEBUG("ani: box=%x\n", (unsigned int)ani_box);

    if ((ani_box == NULL) || (ani_box->visible == 0) || (ani_box->type != TYPE_GUI_CONTROL_ANIMATION)) {
        application_stop_user_timer(timer_id);
        return;
    }

    unsigned int commit = 0;
    gui_node_struct* node = ani_box->child;
    while(node != NULL) {
        // update node's frame
        gui_animation_struct* animation = gui_widget_get_animation_by_id(ani_box, node->id);
        if ((animation != NULL) && (node->value >= 0x00010000)) {
            node->value -= 0x00010000;
            if ((node->value & 0xFFFF0000) == 0) {
                unsigned int frame_idx = node->value + 1;
                if (frame_idx >= animation->frames_num) {
                    frame_idx = 0;
                }
                if (frame_idx != node->value) {
                    gui_animation_frame_struct* frame = (gui_animation_frame_struct*)&animation->frames[frame_idx];
                    unsigned int dur_ticks = (frame->duration+49)/50;
                    if(FLOAT_EQUAL(node->scale,1.0f))//静态位置动画不需要放大
                    {
                        node->x = gui_surface_ani_check_x(ani_box, frame);
                        node->y = gui_surface_ani_check_y(ani_box, frame);
                        node->width = frame->picture->width;        // 20221122 Taylor.Le,
                        node->height = frame->picture->height;      // 20221122 Taylor.Le,
                    }
                    node->data = (void*)frame->picture;
                    node->value = (dur_ticks<<16) + frame_idx; // dur-ticks & frame-index;
                    gui_surface_node_check_clip(ani_box, node, frame->picture->width, frame->picture->height);
                    commit = 1;
                }
            }
        }

        // next ani.
        node = node->brother;
    }

    //GUI_DEBUG("ani: commit=%d\n", commit);
    if (commit) {
        gui_surface_commit();
    }
}


static void gui_surface_control_animation_init(gui_box_struct* box)
{
    gui_node_struct* last_node;

    const gui_widget_struct* widget = box->widget;

    gui_animation_struct* animation = (gui_animation_struct*)widget->children;

    unsigned int num = widget->child_num;

    box->child = NULL;
    while(num) {
        num --;

        gui_node_struct* node = gui_surface_cache_add_node();
        if (node != NULL) {
            gui_animation_frame_struct* frame = (gui_animation_frame_struct*)&animation->frames[0];
            unsigned int dur_ticks = (frame->duration+49)/50;
            node->type = TYPE_GUI_DRAW_PICTURE;
            node->id = animation->id;
            node->x = gui_surface_ani_check_x(box, frame);
            node->y = gui_surface_ani_check_y(box, frame);
            node->width = frame->picture->width;        // 20221122 Taylor.Le,
            node->height = frame->picture->height;      // 20221122 Taylor.Le,
            node->draw = frame;
            node->data = (void*)frame->picture;
            node->value = (dur_ticks << 16) + 0;    // dur-ticks & frame-index;
            gui_surface_node_check_clip(box, node, frame->picture->width, frame->picture->height);

            if (box->child == NULL) {
                box->child = node;
            }
            else {
                last_node->brother = node;
            }
            last_node = node;
        }

        animation ++;
    }
}


//屏幕数组转化---------------------------------------------------------------------

void gui_surface_control_animation_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    GUI_DEBUG("ani: creat, id=%d, box=%x\n", box->id, (unsigned int)box);
    box->data = NULL;
    if (widget->child_num > 0) {
        gui_surface_control_animation_init(box);
    }
    else {
        box->child = NULL;
    }
}

void gui_surface_control_animation_exit(gui_box_struct* box)
{
    if (box != NULL && box->type == TYPE_GUI_CONTROL_ANIMATION) {
        GUI_DEBUG("ani: exit, id=%d, box=%x\n", box->id, (unsigned int)box);
        if (box->data != NULL) {
            application_stop_user_timer((unsigned int)box->data);
            box->data = NULL;
        }
    }
}


void gui_surface_control_animation_start(const gui_screen_struct* screen, unsigned int box_id)
{
    gui_box_struct* ani_box = gui_surface_get_box(screen, box_id);
    GUI_DEBUG("ani: start, id=%d, box=%x\n", box_id, (unsigned int)ani_box);
    if ((ani_box != NULL) && (ani_box->type == TYPE_GUI_CONTROL_ANIMATION) && (ani_box->data == NULL)) {
		GUI_DEBUG("gui_surface_control_animation_start");
        ani_box->data = (void*)application_start_user_timer(50, gui_controller_animation_timer_handler, ani_box);
    }
}

void gui_surface_control_animation_stop(const gui_screen_struct* screen, unsigned int box_id)
{
    gui_box_struct* ani_box = gui_surface_get_box(screen, box_id);
    GUI_DEBUG("ani: stop, id=%d, box=%x\n", box_id, (unsigned int)ani_box);
    if ((ani_box != NULL) && (ani_box->type == TYPE_GUI_CONTROL_ANIMATION)) {
        if (ani_box->data != NULL) {
            application_stop_user_timer((unsigned int)ani_box->data);
            ani_box->data = NULL;
        }
        gui_controller_animation_reset_frame(ani_box);  // 20230202 Taylor.Le, +
    }
}

// 20230202 Taylor.Le, +
void gui_surface_control_animation_set_frame(const gui_screen_struct* screen, unsigned int box_id, unsigned int ani_id, unsigned int frame_idx)
{
    gui_box_struct* ani_box = gui_surface_get_box(screen, box_id);
    GUI_DEBUG("ani: stop, id=%d, box=%x\n", box_id, (unsigned int)ani_box);
    if ((ani_box != NULL) && (ani_box->type == TYPE_GUI_CONTROL_ANIMATION)) {
        gui_animation_struct* animation = gui_widget_get_animation_by_id(ani_box, ani_id);
        gui_node_struct* node           = gui_surface_box_find_node(ani_box, ani_id);
        if (animation != NULL && node != NULL) {
            if (frame_idx >= animation->frames_num) {
                frame_idx = 0;
            }
            if (frame_idx != node->value) {
                gui_animation_frame_struct* frame = (gui_animation_frame_struct*)&animation->frames[frame_idx];
                unsigned int dur_ticks = (frame->duration+49)/50;
                node->x = gui_surface_ani_check_x(ani_box, frame);
                node->y = gui_surface_ani_check_y(ani_box, frame);
                node->width = frame->picture->width;        // 20221122 Taylor.Le,
                node->height = frame->picture->height;      // 20221122 Taylor.Le,
                node->data = (void*)frame->picture;
                node->value = (dur_ticks<<16) + frame_idx; // dur-ticks & frame-index;
                gui_surface_node_check_clip(ani_box, node, frame->picture->width, frame->picture->height);
            }
        }
    }
}



