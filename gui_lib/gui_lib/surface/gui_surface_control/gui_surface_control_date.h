#ifndef __GUI_SURFACE_CONTROL_DATE_H__
#define __GUI_SURFACE_CONTROL_DATE_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"
#include "gui_event_core_list.h"

typedef struct
{
	unsigned char value_type;  //GUI_DIGITAL_VALUE_TYPE  0,image   1,font  
	unsigned char date_type;  // - / .
	union 
	{
		const gui_font_struct* font;
		const gui_image_number_struct* image_number;
	}value;

}gui_control_date_number_struct;


//屏幕数组转化---------------------------------------------------------------------
extern void gui_surface_control_date_create(gui_box_struct* box);
extern void gui_surface_control_date_exit(gui_box_struct* box);

//事件响应--------------------------------------------------------------------------
extern const gui_static_event_struct g_gui_control_date;


#endif
