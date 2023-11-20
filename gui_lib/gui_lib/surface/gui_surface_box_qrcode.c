#include "gui_surface_box_image.h"
#include "gui_surface_cache.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"

gui_node_struct* gui_surface_box_qrcode_arrange_content(gui_box_struct* box,const gui_qr_code_struct* qr_code,unsigned char* string)
{
	gui_node_struct* node = gui_surface_cache_add_node();
	node->type = TYPE_GUI_DRAW_QR_CODE;
	node->id = qr_code->id;
	if(qr_code->width == 0)
	{
		node->width = LCD_SIZE_WIDTH;
		node->height = LCD_SIZE_WIDTH;
	}
	else
	{
		node->width = qr_code->width;
		node->height = qr_code->width;
	}

	node->x = (box->width - node->width)/2 ;
 	node->y = (box->height - node->height)/2 ;
 
	node->draw = qr_code;
	node->data = (void*)string;
	gui_surface_node_check_clip(box, node, box->width, box->height);
	return node;
}

gui_node_struct* gui_surface_box_qrcode_arrange_children(gui_box_struct* box,const gui_qr_code_struct* qr_code)
{
	unsigned char* string = (unsigned char*)qr_code->string;
	return gui_surface_box_qrcode_arrange_content(box,qr_code,string);
}

gui_node_struct* gui_surface_box_qrcode_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const gui_qr_code_struct* qr_code = (const gui_qr_code_struct*)widget->children;
	return gui_surface_box_qrcode_arrange_children(box,qr_code);
}

//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_qrcode_create(gui_box_struct* box)
{
    //gui_node_struct* node;
    gui_widget_struct* widget = box->widget;
	const gui_qr_code_struct* qr_code = (const gui_qr_code_struct*)widget->children;
    unsigned int num = widget->child_num;
    if (widget != NULL && num > 0) {
        box->child = gui_surface_box_qrcode_arrange_children(box, qr_code);
    }else {
		box->child = NULL;
    }
}

//界面改变--------------------------------------------------------------------------
void gui_surface_box_qrcode_change(gui_box_struct* box,unsigned char* string)
{
	if(box == NULL)
		return;
	gui_surface_cache_remove_nodes(box->child);
	gui_widget_struct* widget = box->widget;
	const gui_qr_code_struct* qr_code = (const gui_qr_code_struct*)widget->children;
	box->child = gui_surface_box_qrcode_arrange_content(box,qr_code,string);
}

void gui_surface_box_qrcode_arrange_refresh(gui_box_struct* box)
{
	if(box == NULL)
		return;
	//gui_widget_struct* widget = box->widget;
	gui_node_struct* node = (gui_node_struct*)box->child;
	node->x = 0;
	node->y = 0;
	gui_surface_node_check_clip(box, node, box->width, box->height);
}




