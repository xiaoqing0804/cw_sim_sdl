#ifndef __GUI_SURFACE_CONTROL_BASE_H__
#define __GUI_SURFACE_CONTROL_BASE_H__

#include "feature_all.h"
#include "picture.h"
#include "gui_core.h"

/*
**本文件是业务控件配置的静态结构
*/

typedef enum
{
	GUI_DIGITAL_VALUE_TYPE_IMAGE,     	//图片
	GUI_DIGITAL_VALUE_TYPE_FONT,		//文本
}GUI_DIGITAL_VALUE_TYPE;

typedef enum
{
	GUI_DIGITAL_TIME_HHMM,
	GUI_DIGITAL_TIME_HH,
	GUI_DIGITAL_TIME_MM,
	GUI_DIGITAL_TIME_MMHH,
	
}GUI_DIGITAL_TIME_FMT;

typedef struct
{
	unsigned char value_type;  //GUI_DIGITAL_VALUE_TYPE  0,image   1,font  
	unsigned char time_format;	// 
	union 
	{
		const gui_font_struct* font;
		const gui_image_number_struct* image_number;
	}value;

}gui_control_digital_struct;


extern void gui_surface_control_digital_change(gui_box_struct* box, unsigned char* str);


#endif
