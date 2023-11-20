#include "gui_surface_box_image_number.h"
#include "gui_surface_cache.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"
#include "gui_util_text_string.h"
#include "gui_surface_box_image.h"

static const gui_image_struct* gui_surface_box_image_list_find_by_id(gui_box_struct* box,unsigned short id)
{
	gui_widget_struct* widget = box->widget;
	if(widget->child_num > 0)
	{
		const gui_image_struct* image = (const gui_image_struct*)widget->children;
		for(unsigned char i = 0; i < widget->child_num; i++)
		{
			if(image->id > 0 && image->id == id)
				return image;
			image++;
		}
	}
	return NULL;
}


gui_node_struct* gui_surface_box_image_list_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	
	//排版
	gui_node_struct* node = NULL, *start_node = NULL, *end_node = NULL;
	const gui_image_struct* image = (const gui_image_struct*)widget->children;
	for(unsigned char i = 0; i < widget->child_num; i++)
	{
		const picture_info_struct* picture = (const picture_info_struct*)image->data;
		if(picture != NULL)
		{
			node = gui_surface_cache_add_node();
    		node->type = TYPE_GUI_DRAW_PICTURE;
			node->id = image->id;
            node->value = 0;
    		node->data = (void*)picture;// picture_info_struct
            node->x = image->x;
            node->y = image->y;
			node->width = picture->width;
			node->height = picture->height;
			gui_surface_node_check_clip(box,node,picture->width,picture->height);

			if(start_node == NULL)
				start_node = node;
			if(end_node != NULL)
    			end_node->child = node;
    		end_node = node;
		}
		image++;
	}

	return start_node;

}



//屏幕数组转化---------------------------------------------------------------------
void gui_surface_box_image_list_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget != NULL && widget->child_num > 0)
        box->child = gui_surface_box_image_list_arrange(box);
	else
		box->child = NULL;
}

//界面改变--------------------------------------------------------------------------

void gui_surface_box_image_list_change(gui_box_struct* box,unsigned short node_id,const picture_info_struct* picture)
{
	if(picture == NULL)
	{
		box->child = NULL;
		return;
	}

	gui_node_struct* node = gui_surface_node_find_by_id(box,node_id);
	if(node == NULL)
		return;
	const gui_image_struct* image = gui_surface_box_image_list_find_by_id(box,node_id);
	gui_node_struct* new_node = gui_surface_box_image_arrange_content(box,image,picture);
	gui_surface_node_replace_child(box,node,new_node);	
}






