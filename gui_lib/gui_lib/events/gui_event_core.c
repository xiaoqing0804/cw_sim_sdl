#include "gui_event_core.h"
#include "gui_event_core_list.h"
#include "app_task_main.h"

//id: APPLICATION_EVENT_TYPE  &  GUI_EVENT_TYPE
short gui_event_sent_by_id(short id,void *buf)
{
	short result = 0;
	const gui_static_event_map_struct* map = get_gui_event_by_id(id);
	if(map != NULL)
	{
		const gui_static_event_struct* static_event = NULL;
		for(short i = 0 ;i < map->event_num; i++)
		{
			static_event = map->events[i];
			if(static_event->id == id)
			{
				if(static_event->enable != NULL && static_event->enable())
				{
					if(static_event->handler != NULL)
					{
						static_event->handler(buf);
						result = 1;
					}
				}
			}
		}		
	}
	return result;
}

