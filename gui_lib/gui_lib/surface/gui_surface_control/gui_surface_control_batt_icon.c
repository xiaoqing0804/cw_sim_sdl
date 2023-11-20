
#include "data_common.h"
#include "data_receive_package.h"
#include "gui_surface_cache.h"
#include "gui_surface_node.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_batt_icon.h"

static gui_box_struct* g_gui_box_batt_icon = NULL;

static void gui_surface_control_batt_icon_change(gui_box_struct* box, app_battery_info_struct* info)
{
    const gui_widget_struct* widget = box->widget;
    const gui_batt_icon_struct* batt_icon = (gui_batt_icon_struct*)widget->children;

    unsigned int val_gap = 100 / (batt_icon->pics_num);
    unsigned int pic_idx = (info->percent) / val_gap;
	if(pic_idx >= batt_icon->pics_num)
		pic_idx = batt_icon->pics_num -1;
	
    const picture_info_struct* pic = batt_icon->gui_pics[pic_idx].pic_info;

    gui_node_struct* node = box->child;
    if (node != NULL) {
        node->type = TYPE_GUI_DRAW_PICTURE;
        node->id = batt_icon->id;
        node->x = gui_surface_node_check_x(box, batt_icon->align, batt_icon->x, pic->width);
        node->y = gui_surface_node_check_y(box, batt_icon->align, batt_icon->y, pic->height);
        node->width = pic->width;       // Taylor.Le, +
        node->height = pic->height;       // Taylor.Le, +
        node->draw = batt_icon;
        node->data = (void*)pic;  //picture_info_struct*
        gui_surface_node_check_clip(box, node, pic->width, pic->height);
    }
}



//屏幕数组转化---------------------------------------------------------------------

void gui_surface_control_batt_icon_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget->child_num > 0)
	{
	    app_battery_info_struct* info = application_get_battery_info();
        gui_node_struct* node = gui_surface_cache_add_node();
        if (node != NULL) {
            box->child = node;
            gui_surface_control_batt_icon_change(box, info);
            g_gui_box_batt_icon = box;
        }
	}
	else
	{
		box->child = NULL;
    }
}

void gui_surface_control_batt_icon_exit(gui_box_struct* box)
{
    g_gui_box_batt_icon = NULL;
}





//事件响应--------------------------------------------------------------------------

static unsigned char gui_surface_control_batt_icon_enable(void)
{
	return (g_gui_box_batt_icon != NULL);
}

static void gui_surface_control_batt_icon_handler(void *buf)
{
	gui_surface_control_batt_icon_change(g_gui_box_batt_icon, (app_battery_info_struct*)buf);
	gui_surface_commit();
}

const gui_static_event_struct g_gui_control_batt_icon_evt = 
{
	.id = EVENT_BATTERY_CHARGER,
	.enable = gui_surface_control_batt_icon_enable,
	.handler = gui_surface_control_batt_icon_handler,
};




