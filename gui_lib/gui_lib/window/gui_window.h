#ifndef __GUI_WINDOW_H__
#define __GUI_WINDOW_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern void gui_window_power_on(const gui_window_struct* window);
extern void gui_window_goto_main(void);
extern void gui_window_go_back(void);
extern void gui_window_push(const gui_window_struct* window, GUI_WINDOW_TYPE type, void* data);
extern void gui_window_replace(const gui_window_struct* window, GUI_WINDOW_TYPE type, void* data);
extern void gui_window_remove_many_back(char count);

extern int gui_wnidow_check_event(const gui_window_struct *window, int event);

#endif

