#include "gui_surface_box_image_number.h"
#include "gui_surface_cache.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"
#include "gui_util_text_string.h"

const picture_info_struct* gui_surface_box_image_number_get_picture(const gui_image_number_struct* image_number,unsigned char str)
{
	if(image_number->number_image_list == NULL)
		return NULL;
	
	const picture_info_struct* picture = NULL;
	if(str >= '0' && str <= '9')
	{
		picture = image_number->number_image_list->number[str - '0'];
	}
	else if(str == '.')
	{
		picture = image_number->number_image_list->dot;
	}
	else if(str == ':')
	{
		picture = image_number->number_image_list->colon;
	}
	else if(str == '-')
	{
		picture = image_number->number_image_list->dash;
	}
	else if(str == '/')
	{
		picture = image_number->number_image_list->slash;
	}
	else if(str == '%')
	{
		picture = image_number->number_image_list->percent;
	}
	else
	{
		for(short i = 0; i < NUMBER_IMAGE_LIST_CUSTOM; i++)
		{
			if(image_number->number_image_list->custom_char[i] == str)
			{
				picture = image_number->number_image_list->custom_picture[i];
				break;
			}
		}
	}
	return picture;
}

gui_node_struct* gui_surface_box_image_number_arrange_content(gui_box_struct* box,const gui_image_number_struct* image_number,unsigned char* str)
{
	gui_widget_struct* widget = box->widget;
	unsigned char len = strlen((char*)str);

	//获取总大小
	short width = 0 , height = SHORT_MAX;
	for(unsigned char i = 0;i < len; i++)
	{
		const picture_info_struct* picture = gui_surface_box_image_number_get_picture(image_number,str[i]);
		if(picture != NULL)
		{
			width += picture->width + widget->space_x;
			if(height > picture->height)
				height = picture->height;
		}
	}
	width -= widget->space_x;

	//排版
	short start_x = gui_surface_node_check_x(box,image_number->align,image_number->x,width);
	short start_y = gui_surface_node_check_y(box,image_number->align,image_number->y,height);

	//主节点
	gui_node_struct* boot_node = gui_surface_cache_add_node();
    boot_node->type = TYPE_GUI_DRAW_PICTURE_BOX;    // TYPE_GUI_CONTROL_LABEL => TYPE_GUI_DRAW_TEXT
    boot_node->id = image_number->id;
	boot_node->draw = image_number;
    boot_node->data = NULL;       // gui_font_struct
    boot_node->x = start_x;
    boot_node->y = start_y;
	boot_node->width = width;
    boot_node->height = height;
	boot_node->clip_x = 0;  // start_x;     // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
    boot_node->clip_y = 0;  // start_y;     // 20221026 Taylor.Le, 修改node的clip区域为相对node本身的区域
	boot_node->clip_width = width;
    boot_node->clip_height = height;
	boot_node->scale =  GUI_INIT_SCALE(image_number->scale);
	
	gui_node_struct* node = NULL;
	gui_node_struct* curr_node = boot_node;
	start_x = 0;
	start_y = 0;
	for(unsigned char i = 0; i < len; i++)
	{
		const picture_info_struct* picture = gui_surface_box_image_number_get_picture(image_number,str[i]);
		if(picture != NULL)
		{
		    if (str[i] != ' ') {
    			node = gui_surface_cache_add_node();
        		node->type = TYPE_GUI_DRAW_PICTURE;
    			node->id = image_number->id;
                node->value = str[i];
        		node->data = (void*)picture;// picture_info_struct
                node->x = start_x;
                node->y = start_y;
				node->width = picture->width;
            	node->height = picture->height;
    			gui_surface_node_check_clip(box,node,picture->width,picture->height);
            }
			
			start_x += picture->width + widget->space_x;
			curr_node->child = node;
			curr_node = node;
		}
	}

	return boot_node;
}

gui_node_struct* gui_surface_box_image_number_arrange_children(gui_box_struct* box,const gui_image_number_struct* image_number)
{
	unsigned char buff[16] = {0};
	unsigned char* str = gui_util_text_string_get_string(image_number->value_type,image_number->value.number,buff,16);
	if(str == NULL)
		return NULL;

	return gui_surface_box_image_number_arrange_content(box,image_number,str);
}

gui_node_struct* gui_surface_box_image_number_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const gui_image_number_struct* image_number = (const gui_image_number_struct*)widget->children;
	return gui_surface_box_image_number_arrange_children(box,image_number);
}

//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_image_number_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget->child_num > 0)
        box->child = gui_surface_box_image_number_arrange(box);
	else
		box->child = NULL;
}

//界面改变--------------------------------------------------------------------------

void gui_surface_box_image_number_change_content(gui_box_struct* box,const gui_image_number_struct* image_number,unsigned char* str)
{
	if(box == NULL || image_number == NULL)
		return;

	gui_surface_cache_remove_nodes(box->child);
	box->child = gui_surface_box_image_number_arrange_content(box,image_number,str);
}

void gui_surface_box_image_number_change_string(gui_box_struct* box,unsigned char* str)
{
	if(box == NULL)
		return;

	gui_widget_struct* widget = box->widget;
	const gui_image_number_struct* image_number = (const gui_image_number_struct*)widget->children;
	gui_surface_box_image_number_change_content(box,image_number,str);
}

void gui_surface_box_image_number_change_string_id(gui_box_struct* box,int string_id)
{
	if(box == NULL)
		return;

	unsigned char* str = (unsigned char*)GUI_Get_ID_String((STRING_ID_TYPE)string_id);
	gui_surface_box_image_number_change_string(box,str);
}

void gui_surface_box_image_number_change_number(gui_box_struct* box,int number)
{
	if(box == NULL)
		return;

	unsigned char buff[16] = {0};
	gui_widget_struct* widget = box->widget;
	const gui_image_number_struct* image_number = (const gui_image_number_struct*)widget->children;
    
    if (image_number->number_digits != 0) {
        get_string_from_number_with_len(buff,16,number,image_number->number_digits);
    }
    else {
        get_string_from_number(buff,16,number);
    }
	gui_surface_box_image_number_change_string(box,buff);
}





