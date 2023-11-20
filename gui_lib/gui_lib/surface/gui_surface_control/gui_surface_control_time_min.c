#include "gui_surface_control_time.h"
#include "gui_surface_control_base.h"
#include "data_common.h"

static char g_gui_control_time_enable = 0;
static gui_box_struct* g_gui_box_time = NULL;

static void gui_surface_control_time_min_change(gui_box_struct* box)
{
	//const gui_control_digital_struct* digital = (const gui_control_digital_struct *)box->widget->children;

	time_struct curr_time;
	unsigned int m_sys_sec = 0;
	
	char buf[8] = {0};
	//char hour;

	sys_time_get(&curr_time);
	//hour = curr_time.hour;
	if(g_timeSync.format.bit.hour == 0){
		sys_time_get_12h(&curr_time,&m_sys_sec);
		//hour = curr_time.hour;
	}
	
	snprintf(buf, sizeof(buf), "%02d",curr_time.min);

	gui_surface_control_digital_change(box,(unsigned char*)buf);
}


//屏幕数组转化---------------------------------------------------------------------

void gui_surface_control_time_min_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget->child_num > 0)
	{
		gui_surface_control_time_min_change(box);
	}
	else
	{
		box->child = NULL;
    }
	g_gui_box_time = box;
	g_gui_control_time_enable++;

}

void gui_surface_control_time_min_exit(gui_box_struct* box)
{
	g_gui_control_time_enable--;
}



//事件响应--------------------------------------------------------------------------

static unsigned char gui_surface_control_time_min_enable()
{
	return g_gui_control_time_enable;
}

static void gui_surface_control_time_min_handler(void *buf)
{

	if(g_gui_box_time != NULL && g_gui_box_time->type == TYPE_GUI_CONTROL_TIME_MIN ){
		gui_surface_control_time_min_change(g_gui_box_time);
		gui_surface_commit();
	}
}

const gui_static_event_struct g_gui_control_time_min = 
{
	.id = EVENT_RTC_MINUTE_IND,
	.enable = gui_surface_control_time_min_enable,
	.handler = gui_surface_control_time_min_handler,
};


