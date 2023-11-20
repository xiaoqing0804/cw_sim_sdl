#include "gui_surface_box_image.h"
#include "gui_surface_cache.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"
#include "gui_surface_box_layout_cellular.h"


gui_node_struct* gui_surface_box_layout_cellular_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const picture_info_struct** picture_arr = (const picture_info_struct**)widget->children;
	const picture_info_struct* picture = (const picture_info_struct*)(*picture_arr);

	gui_node_struct* node = gui_surface_cache_add_node();
	node->type = TYPE_GUI_DRAW_PICTURE;
	node->id = widget->id;
	node->x = 0;
	node->y = 0;
	node->width = picture->width;
	node->height = picture->height;
	node->draw = NULL;
	node->data = (void *)picture; // picture_info_struct*

	box->width = picture->width;
	box->height = picture->height;
	box->scale =  GUI_INIT_SCALE(widget->scale);
	gui_surface_node_check_clip(box, node, box->width, box->height);
	return node;
}


//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_layout_cellular_create(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	if(widget->child_num > 0)
	{
		box->child = gui_surface_box_layout_cellular_arrange(box);
	}
	else
	{
		box->child = NULL;
	}
}





