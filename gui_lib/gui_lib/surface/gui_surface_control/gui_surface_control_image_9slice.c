
#include "debug_info.h"
#include "math.h"
#include "feature_gui.h"

#include "gui_surface_cache.h"
#include "gui_surface_control_image_9slice.h"

static gui_node_struct* gui_surface_box_9slice_add_node(gui_node_struct* pre_node, picture_info_struct* pic, int id)
{
    if (pic != NULL) {
        gui_node_struct* node = gui_surface_cache_add_node();
        if (node != NULL) {
            node->type = TYPE_GUI_DRAW_PICTURE;
            node->id = id;
            node->x = 0;
            node->y = 0;
            node->width = pic->width;
            node->height = pic->height;

            node->clip_width = node->clip_width;
            node->clip_height = node->clip_height;

            node->data = (void*)pic;

            if (pre_node != NULL)   pre_node->child = node;
            return node;
        }
    }
    return pre_node;
}

static void gui_surface_box_9slice_set_clip(gui_node_struct* node)
{
    if (node != NULL) {
        node->clip_width = node->width;
        node->clip_height = node->height;
    }
}

static void gui_surface_box_9slice_update(gui_node_struct* img_box, int w, int h)
{
    gui_image_9slice_struct* img_9slice = (gui_image_9slice_struct*)img_box->data;
    if (img_9slice != NULL) {
        gui_node_struct* lf_top = NULL;
        gui_node_struct* rt_top = NULL;
        gui_node_struct* lf_bot = NULL;
        gui_node_struct* rt_bot = NULL;

        gui_node_struct* node = NULL;
        int max_w, max_h;
        int min_w, min_h;

        min_w = img_9slice->left_top->width + img_9slice->right_top->width;
        max_w = min_w + img_9slice->top->width;
        min_h = img_9slice->left_top->height + img_9slice->left_bot->height;
        max_h = min_h + img_9slice->left->height;
        if (w < min_w)  w = min_w;
        if (w > max_w)  w = max_w;
        if (h < min_h)  h = min_h;
        if (h > max_h)  h = max_h;

        img_box->width = w;
        img_box->height = h;

        lf_top = gui_surface_node_find_child(img_box, 1);       // left-top
        if (rt_top == NULL) return;

        rt_top = gui_surface_node_find_child(img_box, 3);       // right-top
        if (rt_top == NULL) return;
        rt_top->x = img_box->width - rt_top->width;

        lf_bot = gui_surface_node_find_child(img_box, 7);       // left-bot
        if (lf_bot == NULL) return;
        lf_bot->y = img_box->height - lf_bot->height;

        rt_bot = gui_surface_node_find_child(img_box, 9);       // right-bot
        if (rt_bot == NULL) return;
        rt_bot->x = img_box->width  - rt_bot->width;
        rt_bot->y = img_box->height - rt_bot->height;

        if (min_w < w) {
            node = gui_surface_node_find_child(img_box, 2);   // top
            if (node == NULL) return;
            node->visible = 1;
            node->x = lf_top->width;
            node->width = rt_top->x - node->x;
            gui_surface_box_9slice_set_clip(node);

            node = gui_surface_node_find_child(img_box, 8);   // bot
            if (node == NULL) return;
            node->visible = 1;
            node->x = lf_bot->width;
            node->y = img_box->height - node->height;
            node->width = rt_bot->x - node->x;
            gui_surface_box_9slice_set_clip(node);
        }
        else {
            node = gui_surface_node_find_child(img_box, 2);   // top
            if (node == NULL) return;
            node->visible = 0;

            node = gui_surface_node_find_child(img_box, 8);   // bot
            if (node == NULL) return;
            node->visible = 0;
        }

        if (min_h < h) {
            node = gui_surface_node_find_child(img_box, 4);   // left
            if (node == NULL) return;
            node->visible = 1;
            node->y = lf_top->height;
            node->height = lf_bot->y - node->y;
            gui_surface_box_9slice_set_clip(node);

            node = gui_surface_node_find_child(img_box, 6);   // right
            if (node == NULL) return;
            node->visible = 1;
            node->x = img_box->width - node->width;
            node->y = lf_top->height;
            node->height = lf_bot->y - node->y;
            gui_surface_box_9slice_set_clip(node);
        }
        else {
            node = gui_surface_node_find_child(img_box, 4);   // left
            if (node == NULL) return;
            node->visible = 0;

            node = gui_surface_node_find_child(img_box, 6);   // right
            if (node == NULL) return;
            node->visible = 0;
        }

        if (min_w == w || min_h == h) {
            node = gui_surface_node_find_child(img_box, 5);   // mid
            if (node == NULL) return;
            node->visible = 0;
        }
        else {
            node = gui_surface_node_find_child(img_box, 5);   // mid
            if (node == NULL) return;
            node->visible = 1;
            node->x = lf_top->width;
            node->y = lf_top->height;
            node->width = rt_top->x  - node->x;
            node->height = lf_bot->y - node->y;
            gui_surface_box_9slice_set_clip(node);
        }
    }
}

gui_node_struct* gui_surface_box_9slice_arrange_children(gui_box_struct* box, gui_image_9slice_struct* img_9slice)
{
    gui_node_struct* root_node = NULL;
    gui_node_struct* node = NULL;

    root_node = gui_surface_cache_add_node();
    if (root_node == NULL) return root_node;

    root_node->type = TYPE_GUI_DRAW_PICTURE_9SCLICE;
    root_node->data = img_9slice;
    root_node->id   = 0;
    root_node->x = box->x;
    root_node->y = box->y;
    root_node->width = box->width;
    root_node->height = box->height;

    node = gui_surface_box_9slice_add_node(root_node, img_9slice->left_top, 1);
    node = gui_surface_box_9slice_add_node(node, img_9slice->top, 2);
    node = gui_surface_box_9slice_add_node(node, img_9slice->right_top, 3);

    node = gui_surface_box_9slice_add_node(node, img_9slice->left, 4);
    node = gui_surface_box_9slice_add_node(node, img_9slice->mid, 5);
    node = gui_surface_box_9slice_add_node(node, img_9slice->right, 6);

    node = gui_surface_box_9slice_add_node(node, img_9slice->left_bot, 7);
    node = gui_surface_box_9slice_add_node(node, img_9slice->bot, 8);
    node = gui_surface_box_9slice_add_node(node, img_9slice->right_bot, 9);

    gui_surface_box_9slice_update(root_node, box->width, box->height);
    return root_node;
}

void gui_surface_box_image_9slice_create(gui_box_struct* box)
{
    if (box->type != TYPE_GUI_CONTROL_IMAGE_9SLICE) return;

    gui_image_9slice_struct* img_9slice = (gui_image_9slice_struct*)box->widget;

    if (img_9slice != NULL) {
        box->child = gui_surface_box_9slice_arrange_children(box, img_9slice);
    }
}


void gui_surface_box_image_9slice_change(gui_box_struct* box, int id, int x, int y, int w, int h)
{
    gui_node_struct* img_box = gui_surface_node_find_by_id(box, id);
    if (img_box != NULL && img_box->type == TYPE_GUI_DRAW_PICTURE_9SCLICE) {
        img_box->x = x;
        img_box->y = y;
        gui_surface_box_9slice_update(img_box, w, h);
    }
}






