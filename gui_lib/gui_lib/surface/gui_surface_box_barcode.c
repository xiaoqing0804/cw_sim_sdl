#include "gui_surface_box_image.h"
#include "gui_surface_cache.h"
#include "gui_surface_box.h"
#include "gui_surface_node.h"
#include "gui_surface_box_barcode.h"

gui_node_struct* gui_surface_box_barcode_arrange_content(gui_box_struct* box,const gui_bar_code_struct* bar_code,unsigned char* string)
{
	gui_node_struct* node = gui_surface_cache_add_node();
	node->type = TYPE_GUI_DRAW_BAR_CODE_128;
	node->width = box->width;
	node->height = box->height;
	node->x = 0;
 	node->y = 0;
	node->draw = bar_code;
	node->data = (void*)string;
	gui_surface_node_check_clip(box, node, box->width, box->height);
	return node;
}

gui_node_struct* gui_surface_box_barcode_arrange_children(gui_box_struct* box,const gui_bar_code_struct* bar_code)
{
	unsigned char* string = (unsigned char*)bar_code->string;
	return gui_surface_box_barcode_arrange_content(box,bar_code,string);
}

gui_node_struct* gui_surface_box_barcode_arrange(gui_box_struct* box)
{
	gui_widget_struct* widget = box->widget;
	const gui_bar_code_struct* bar_code = (const gui_bar_code_struct*)widget->children;
	return gui_surface_box_barcode_arrange_children(box,bar_code);
}

//屏幕数组转化---------------------------------------------------------------------

void gui_surface_box_barcode_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
	const gui_bar_code_struct* bar_code = (const gui_bar_code_struct*)widget->children;
    unsigned int num = widget->child_num;
    if (widget != NULL && num > 0) {
        box->child = gui_surface_box_barcode_arrange_children(box, bar_code);
    }else {
		box->child = NULL;
    }
}

//界面改变--------------------------------------------------------------------------
void gui_surface_box_barcode_change(gui_box_struct* box,unsigned char* string)
{
	if(box == NULL)
		return;
	gui_surface_cache_remove_nodes(box->child);
	gui_widget_struct* widget = box->widget;
	const gui_bar_code_struct* bar_code = (const gui_bar_code_struct*)widget->children;
	box->child = gui_surface_box_barcode_arrange_content(box, bar_code, string);
}

void gui_surface_box_barcode_arrange_refresh(gui_box_struct* box)
{
	if(box == NULL)
		return;
	gui_node_struct* node = (gui_node_struct*)box->child;
	node->x = 0;
	node->y = 0;
	gui_surface_node_check_clip(box, node, box->width, box->height);
}




