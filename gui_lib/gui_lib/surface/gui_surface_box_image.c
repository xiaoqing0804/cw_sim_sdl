#include "gui_surface_box_image.h"
#include "gui_surface_cache.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"

gui_node_struct* gui_surface_box_image_arrange_content(gui_box_struct* box,const gui_image_struct* image,const picture_info_struct* picture)
{
	gui_node_struct* node = gui_surface_cache_add_node();
	node->type = TYPE_GUI_DRAW_PICTURE;
	node->id = image->id;
	node->x = gui_surface_node_check_x(box,image->align,image->x,picture->width);
	node->y = gui_surface_node_check_y(box,image->align,image->y,picture->height);
	node->width = picture->width;
	node->height = picture->height;
	node->draw = image;
	node->data = (void*)picture;  //picture_info_struct*
	node->scale = GUI_INIT_SCALE(image->scale);
	gui_surface_node_check_clip(box, node, picture->width, picture->height);
	return node;
}

gui_node_struct* gui_surface_box_image_arrange_children(gui_box_struct* box,const gui_image_struct* image)
{
	picture_info_struct* picture = (picture_info_struct*)image->data;
	return gui_surface_box_image_arrange_content(box,image,picture);
}

gui_node_struct* gui_surface_box_image_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const gui_image_struct* image = (const gui_image_struct*)widget->children;
	return gui_surface_box_image_arrange_children(box,image);
}

//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_image_create(gui_box_struct* box)
{
    gui_node_struct* node;
    gui_widget_struct* widget = box->widget;
	const gui_image_struct* image = (const gui_image_struct*)widget->children;
    unsigned int num = widget->child_num;
    if (widget != NULL && num > 0) {
        while(num) {
            node = gui_surface_box_image_arrange_children(box, image);
            gui_surface_box_add_node(box, node);
            num --;
            image ++;
        }
    }
	else {
		box->child = NULL;
    }
}

//界面改变--------------------------------------------------------------------------
void gui_surface_box_image_change(gui_box_struct* box,const picture_info_struct* picture)
{
	if(box == NULL)
		return;
	gui_surface_cache_remove_nodes(box->child);
	gui_widget_struct* widget = box->widget;
	const gui_image_struct* image = (const gui_image_struct*)widget->children;
	box->child = gui_surface_box_image_arrange_content(box,image,picture);
}

void gui_surface_box_image_arrange_refresh(gui_box_struct* box)
{
	if(box == NULL)
		return;
	gui_widget_struct* widget = box->widget;
	const gui_image_struct* image = (const gui_image_struct*)widget->children;
	gui_node_struct* node = (gui_node_struct*)box->child;
	picture_info_struct* picture = (picture_info_struct*)node->data;
	node->x = gui_surface_node_check_x(box,image->align,image->x,picture->width);
	node->y = gui_surface_node_check_y(box,image->align,image->y,picture->height);
	gui_surface_node_check_clip(box, node, picture->width, picture->height);
}




