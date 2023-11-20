#include "gui_surface_control_date.h"
#include "gui_surface_control_base.h"
#include "data_common.h"


static unsigned char g_gui_control_date_enable = 0;
static gui_box_struct* g_gui_box_date = NULL;

static void gui_surface_control_date_change(gui_box_struct* box)
{
	time_struct curr_date = { 0 };
	sys_time_get(&curr_date);

	char buf[10] = {0};
	gui_widget_struct* widget = box->widget;
	gui_control_date_number_struct* digital = (gui_control_date_number_struct *)widget->children;

	if(digital->date_type == '-')
	{
		if(g_timeSync.format.bit.mon_day)
			snprintf(buf, sizeof(buf), "%02d-%02d",curr_date.day, curr_date.mon);
		else
			snprintf(buf, sizeof(buf), "%02d-%02d",curr_date.mon, curr_date.day);
	}
	else
	{
		if(g_timeSync.format.bit.mon_day)
			snprintf(buf, sizeof(buf), "%02d/%02d",curr_date.day, curr_date.mon);
		else
			snprintf(buf, sizeof(buf), "%02d/%02d",curr_date.mon, curr_date.day);
	}
	gui_surface_control_digital_change(box,(unsigned char*)buf);
}


//屏幕数组转化---------------------------------------------------------------------

void gui_surface_control_date_create(gui_box_struct* box)
{
    gui_widget_struct* widget = box->widget;
    if (widget->child_num > 0)
	{
		gui_surface_control_date_change(box);
	}
	else
	{
		box->child = NULL;
    }
	g_gui_box_date = box;
	g_gui_control_date_enable++;
}

void gui_surface_control_date_exit(gui_box_struct* box)
{
	g_gui_control_date_enable--;
}



//事件响应--------------------------------------------------------------------------

static unsigned char gui_surface_control_date_enable()
{
	return g_gui_control_date_enable;
}

static void gui_surface_control_date_handler(void *buf)
{
	if(g_gui_box_date != NULL && g_gui_box_date->type == TYPE_GUI_CONTROL_DATE ){
	gui_surface_control_date_change(g_gui_box_date);
	gui_surface_commit();
	}
}

const gui_static_event_struct g_gui_control_date = 
{
	.id = EVENT_RTC_MINUTE_IND,
	.enable = gui_surface_control_date_enable,
	.handler = gui_surface_control_date_handler,
};



