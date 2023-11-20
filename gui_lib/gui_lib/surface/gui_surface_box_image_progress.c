#include "gui_surface_box_image_number.h"
#include "gui_surface_cache.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"
#include "gui_util_text_string.h"
#include "system_util_math.h"

gui_node_struct* gui_surface_box_image_progress_arrange_children(gui_box_struct* box,unsigned char progress)
{
	gui_widget_struct* widget = box->widget;
	const gui_image_progress_struct* image_progress = (const gui_image_progress_struct*)widget->children;

	int value = (int)image_progress->child_num * (int)progress / 100;
	value = math_range(value,0,image_progress->child_num);

	picture_info_struct* picture = (picture_info_struct*)image_progress->bg->data;
	gui_node_struct* bg_node = gui_surface_cache_add_node();
	 if(picture != NULL)
	 { 
		bg_node->type = TYPE_GUI_DRAW_PICTURE;
		bg_node->id = image_progress->bg->id;
		bg_node->value = progress;  //把进度条的数值存放在bg的value中
		bg_node->draw = (void*)image_progress;// picture_info_struct
		bg_node->data = (void*)picture;// picture_info_struct
		bg_node->x = image_progress->bg->x;
		bg_node->y = image_progress->bg->y;
		bg_node->width = picture->width;
		bg_node->height = picture->height;
		gui_surface_node_check_clip(box,bg_node,picture->width,picture->height);
	 }
	 else
	 {
		bg_node->type = TYPE_GUI_DRAW_PICTURE;
		bg_node->value = progress;  //把进度条的数值存放在bg的value中
		bg_node->visible = 0;
	 }
	gui_node_struct* node = NULL,*start_node = NULL,*end_node = NULL;
	const gui_image_struct* image = image_progress->children;
	for(unsigned char i = 0; i < value; i++)
	{
		picture = (picture_info_struct*)image->data;
		
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

		image++;
	}
	bg_node->brother = start_node;
	return bg_node;

}

gui_node_struct* gui_surface_box_image_progress_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const gui_image_progress_struct* image_progress = (const gui_image_progress_struct*)widget->children;
	unsigned char progress = image_progress->progress;
	return gui_surface_box_image_progress_arrange_children(box,progress);
}



//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_image_progress_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget->child_num > 0)
        box->child = gui_surface_box_image_progress_arrange(box);
	else
		box->child = NULL;
}

unsigned char gui_surface_box_image_progress_get_value(gui_box_struct* box)
{
	if(box == NULL)
		return 0;
	return box->child->value; //进度条的数值存放在bg的value中
}



//界面改变--------------------------------------------------------------------------

void gui_surface_box_image_progress_change(gui_box_struct* box,unsigned char progress)
{
	if(box == NULL)
		return;

	gui_surface_cache_remove_nodes(box->child);
	box->child = gui_surface_box_image_progress_arrange_children(box,progress);
}



