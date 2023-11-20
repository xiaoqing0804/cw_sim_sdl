#ifndef __GUI_EVENT_CORE_LIST_H__
#define __GUI_EVENT_CORE_LIST_H__

#include "feature_all.h"
#include "app_task_main.h"
#include "gui_event_core_id.h"

extern const gui_static_event_map_struct* get_gui_event_by_index(short index);
extern const gui_static_event_map_struct* get_gui_event_by_id(short id);

#endif

