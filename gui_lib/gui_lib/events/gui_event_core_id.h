#ifndef __GUI_EVENT_CORE_ID_H__
#define __GUI_EVENT_CORE_ID_H__

#include "feature_all.h"
#include "app_task_main.h"

typedef enum
{
	GUI_EVENT_NULL = EVENT_ALL,
		
	GUI_EVENT_WINDOW_EXIT,
	GUI_EVENT_GESTURE_BACK,
	
	GUI_EVENT_ALL
}GUI_EVENT_TYPE;


typedef struct
{
	short id; //APPLICATION_EVENT_TYPE  &  GUI_EVENT_TYPE
	unsigned char (*enable)(void);
	void (*handler)(void *buf);
}gui_static_event_struct;


typedef struct
{
	short id;  //APPLICATION_EVENT_TYPE  &  GUI_EVENT_TYPE
	unsigned char event_num;
	const gui_static_event_struct* const * events;
}gui_static_event_map_struct;


#endif

