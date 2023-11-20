#include "data_common.h"
#include "data_receive_package.h"
#include "gui_surface_cache.h"
#include "gui_surface_node.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_batt_label.h"

static gui_box_struct* g_gui_box_batt_label = NULL;

static void gui_surface_control_batt_label_change(gui_box_struct* box)
{
    app_battery_info_struct* batt_info = application_get_battery_info();
	char buff[8] = {0};
    
    sprintf(buff, "%d%%", batt_info->percent);

	gui_surface_control_digital_change(box,(unsigned char*)buff);
}

//屏幕数组转化---------------------------------------------------------------------
void gui_surface_control_batt_label_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget->child_num > 0) {
        gui_surface_control_batt_label_change(box);
        g_gui_box_batt_label = box;
    }
	else {
		box->child = NULL;
        g_gui_box_batt_label = NULL;
   }
}

void gui_surface_control_batt_label_exit(gui_box_struct* box)
{
    g_gui_box_batt_label = NULL;
}


//事件响应--------------------------------------------------------------------------

static unsigned char gui_surface_control_batt_label_enable(void)
{
	return (g_gui_box_batt_label != NULL);
}

static void gui_surface_control_batt_label_handler(void *buf)
{
    if (g_gui_box_batt_label != NULL) {
        app_battery_info_struct* batt_info = (app_battery_info_struct*)buf;
        char buff[8];
        
        sprintf(buff, "%d%%", batt_info->percent);
        
        gui_surface_control_digital_change(g_gui_box_batt_label, (unsigned char*)buff);
        gui_surface_commit();
    }
}

const gui_static_event_struct g_gui_control_batt_label_evt = 
{
	.id = EVENT_BATTERY_CHARGER,
	.enable = gui_surface_control_batt_label_enable,
	.handler = gui_surface_control_batt_label_handler,
};




