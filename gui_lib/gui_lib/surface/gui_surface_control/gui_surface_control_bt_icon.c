
#include "data_common.h"
#include "data_receive_package.h"
#include "gui_surface_cache.h"
#include "gui_surface_node.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_bt_icon.h"

static gui_box_struct* g_gui_box_bt_icon = NULL;


static void gui_surface_control_bt_icon_change(gui_box_struct* box)
{
    const gui_widget_struct* widget = box->widget;
    const gui_bt_icon_struct* bt_icon = (gui_bt_icon_struct*)widget->children;
    const picture_info_struct* pic = (0 == get_ble_appconnect()) ? bt_icon->pic_unlink : bt_icon->pic_linked;

    gui_node_struct* node = box->child;
    if (node != NULL) {
        node->type = TYPE_GUI_DRAW_PICTURE;
        node->id = bt_icon->id;
        node->x = gui_surface_node_check_x(box, bt_icon->align, bt_icon->x, pic->width);
        node->y = gui_surface_node_check_y(box, bt_icon->align, bt_icon->y, pic->height);
        node->data = (void*)pic;  //picture_info_struct*
        gui_surface_node_check_clip(box, node, pic->width, pic->height);
    }
}


//屏幕数组转化---------------------------------------------------------------------

void gui_surface_control_bt_icon_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget->child_num > 0)
	{
        gui_node_struct* node = gui_surface_cache_add_node();
        if (node != NULL) {
            box->child = node;
            gui_surface_control_bt_icon_change(box);
            g_gui_box_bt_icon = box;
        }
	}
	else
	{
		box->child = NULL;
    }
}

void gui_surface_control_bt_icon_exit(gui_box_struct* box)
{
    g_gui_box_bt_icon = NULL;
}





//事件响应--------------------------------------------------------------------------

static unsigned char gui_surface_control_bt_icon_enable(void)
{
	return (g_gui_box_bt_icon != NULL);
}

static void gui_surface_control_bt_icon_handler(void *buf)
{
	gui_surface_control_bt_icon_change(g_gui_box_bt_icon);
	gui_surface_commit();
}

const gui_static_event_struct g_gui_control_bt_icon = 
{
	.id = EVENT_BLE_CONNECT_STATUS,
	.enable = gui_surface_control_bt_icon_enable,
	.handler = gui_surface_control_bt_icon_handler,
};



