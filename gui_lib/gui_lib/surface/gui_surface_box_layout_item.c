#include "gui_surface_box_image.h"
#include "gui_surface_cache.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"
#include "gui_surface_box_layout_item.h"


const gui_draw_struct* gui_surface_box_layout_item_find_by_id(gui_box_struct* box,unsigned short id)
{
	gui_widget_struct* widget = box->widget;
	if(widget->child_num > 0)
	{
		const gui_mix_struct *mix = (const gui_mix_struct *)widget->children;
		const gui_draw_struct *draw = NULL;
		for(unsigned char i = 0; i < widget->child_num; i++)
		{
			draw = (const gui_draw_struct *)mix->data;
			if(draw->id > 0 && draw->id == id)
				return draw;
			mix++;
		}
	}
	return NULL;
}


//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_layout_item_create(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;

	if(widget->child_num > 0)
	{
		gui_node_struct* node = NULL,*start_node = NULL,*end_node = NULL;

		const gui_mix_struct *mix = (const gui_mix_struct *)widget->children;
		const gui_draw_struct *draw = NULL;
		for(unsigned char i = 0; i < widget->child_num; i++)
		{
			draw = (const gui_draw_struct *)mix->data;
			if(draw->type == TYPE_GUI_DRAW_PICTURE)
			{
				const gui_image_struct* image = (const gui_image_struct*)draw;
				node = gui_surface_box_image_arrange_children(box,image);
			}
			else if(draw->type == TYPE_GUI_DRAW_TEXT)
			{
				const gui_font_struct* text = (const gui_font_struct*)draw;
				node = gui_surface_box_label_arrange_children(box,text);
			}

			if(start_node == NULL)
				start_node = node;
			if(end_node != NULL)
				end_node->brother = node;
			end_node = node;

			mix++;
		}
		box->child = start_node;
	}
	else
	{
		box->child = NULL;
	}
}

//界面改变--------------------------------------------------------------------------

void gui_surface_box_layout_item_change_image(gui_box_struct* box,unsigned char node_id,picture_info_struct* picture)
{
	if(picture == NULL)
	{
		box->child = NULL;
		return;
	}

	gui_node_struct* node = gui_surface_node_find_by_id(box,node_id);
	if(node == NULL)
		return;

	const gui_draw_struct* draw = gui_surface_box_layout_item_find_by_id(box,node_id);
	if(draw->type == TYPE_GUI_DRAW_PICTURE)
	{
		const gui_image_struct* image = (const gui_image_struct*)draw;
		gui_node_struct* new_node = gui_surface_box_image_arrange_content(box,image,picture);
		gui_surface_node_replace_brother(box,node,new_node);
	}

}

void gui_surface_box_layout_item_change_visible(gui_box_struct* box,unsigned char node_id,unsigned char visible)
{

	gui_node_struct* node = gui_surface_node_find_by_id(box,node_id);
	if(node == NULL)
		return;
	node->visible = visible;

}

void gui_surface_box_layout_item_change_string(gui_box_struct* box,unsigned char node_id, unsigned char* str)
{
	if(box == NULL)
		return;

	gui_node_struct* node = gui_surface_node_find_by_id(box,node_id);
	if(node == NULL)
		return;

	const gui_draw_struct* draw = gui_surface_box_layout_item_find_by_id(box,node_id);
	if(draw->type == TYPE_GUI_DRAW_TEXT)
	{
		const gui_font_struct* text = (const gui_font_struct*)draw;
		gui_node_struct* new_node = gui_surface_box_label_arrange_content(box,text,str);
		gui_surface_node_replace_brother(box,node,new_node);
	}
}

void gui_surface_box_layout_item_change_string_id(gui_box_struct* box,unsigned char node_id,int string_id)
{
	if(box == NULL)
		return;

	gui_node_struct* node = gui_surface_node_find_by_id(box,node_id);
	if(node == NULL)
		return;

	const gui_draw_struct* draw = gui_surface_box_layout_item_find_by_id(box,node_id);
	if(draw->type == TYPE_GUI_DRAW_TEXT)
	{
		const gui_font_struct* text = (const gui_font_struct*)draw;
		unsigned char* str = (unsigned char*)GUI_Get_ID_String((STRING_ID_TYPE)string_id);
		gui_node_struct* new_node = gui_surface_box_label_arrange_content(box,text,str);
		gui_surface_node_replace_brother(box,node,new_node);
	}
}

void gui_surface_box_layout_item_change_number(gui_box_struct* box,unsigned char node_id,int number)
{
	if(box == NULL)
		return;

	gui_node_struct* node = gui_surface_node_find_by_id(box,node_id);
	if(node == NULL)
		return;

	const gui_draw_struct* draw = gui_surface_box_layout_item_find_by_id(box,node_id);
	if(draw->type == TYPE_GUI_DRAW_TEXT)
	{
		const gui_font_struct* text = (const gui_font_struct*)draw;
		unsigned char buff[16] = {0};
		get_string_from_number(buff,16,number);
		gui_node_struct* new_node = gui_surface_box_label_arrange_content(box,text,buff);
		gui_surface_node_replace_brother(box,node,new_node);
	}
}







