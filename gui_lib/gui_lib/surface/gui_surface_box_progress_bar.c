#include "gui_surface_box_image_number.h"
#include "gui_surface_cache.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"
#include "gui_util_text_string.h"
#include "system_util_math.h"

gui_node_struct* gui_surface_box_progress_bar_arrange_children(gui_box_struct* box,unsigned char progress)
{
	gui_widget_struct* widget = box->widget;
	const gui_progress_bar_struct* progress_bar = (const gui_progress_bar_struct*)widget->children;
	
	picture_info_struct* bg_picture = (picture_info_struct*)progress_bar->bg->data;
	gui_node_struct* bg_node = gui_surface_cache_add_node();
	if(bg_picture != NULL)
	{ 
		bg_node->type = TYPE_GUI_DRAW_PICTURE;
		bg_node->id = progress_bar->bg->id;
		bg_node->value = progress;  //把进度条的数值存放在bg的value中
		bg_node->data = (void*)bg_picture;// picture_info_struct
		bg_node->x = progress_bar->bg->x;
		bg_node->y = progress_bar->bg->y;
		bg_node->width = bg_picture->width;
		bg_node->height = bg_picture->height;
		gui_surface_node_check_clip(box,bg_node,bg_picture->width,bg_picture->height);
	}
	else
	{
		bg_node->type = TYPE_GUI_DRAW_PICTURE;
		bg_node->value = progress;  //把进度条的数值存放在bg的value中
		bg_node->visible = 0;
		bg_node->x = 0;
		bg_node->y = 0;
		bg_node->width = box->width;
		bg_node->height = box->height;
	}

	picture_info_struct* bar_picture = (picture_info_struct*)progress_bar->bar->data;
	gui_node_struct* bar_node = gui_surface_cache_add_node();
	bar_node->type = TYPE_GUI_DRAW_PICTURE;
	bar_node->id = progress_bar->bar->id;
	bar_node->value = progress;  //把进度条的数值存放在bg的value中
	bar_node->data = (void*)bar_picture;// picture_info_struct
	bar_node->width = bar_picture->width;
	bar_node->height = bar_picture->height;
	
	if(progress_bar->orientation == ORIENTATION_TYPE_HORIZONTAL)
	{
		short width = bg_node->width - bar_node->width - progress_bar->bar->x * 2;
		bar_node->x = progress_bar->bar->x + width * progress / 100;
	}
	else
	{
		short height = bg_node->height - bar_node->height - progress_bar->bar->y * 2;
		bar_node->y = progress_bar->bar->y + height * progress / 100;
	}
	gui_surface_node_check_clip(box,bar_node,bar_picture->width,bar_picture->height);
	bg_node->brother = bar_node;
	return bg_node;

}

gui_node_struct* gui_surface_box_progress_bar_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const gui_progress_bar_struct* progress_bar = (const gui_progress_bar_struct*)widget->children;
	unsigned char progress = progress_bar->progress;
	return gui_surface_box_progress_bar_arrange_children(box,progress);
}



//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_progress_bar_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget->child_num > 0)
        box->child = gui_surface_box_progress_bar_arrange(box);
	else
		box->child = NULL;
}

unsigned char gui_surface_box_progress_bar_get_value(gui_box_struct* box)
{
	if(box == NULL)
		return 0;
	return box->child->value; //进度条的数值存放在bg的value中
}



//界面改变--------------------------------------------------------------------------

void gui_surface_box_progress_bar_change(gui_box_struct* box,unsigned char progress)
{
	if(box == NULL)
		return;

	gui_surface_cache_remove_nodes(box->child);
	box->child = gui_surface_box_progress_bar_arrange_children(box,progress);
}



