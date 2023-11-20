#ifndef __GUI_WINDOW_HISTORY_H__
#define __GUI_WINDOW_HISTORY_H__

#include "feature_all.h"
#include "gui_core_all.h"

extern void gui_window_history_set_main(gui_main_window_struct* window);

extern void gui_window_history_set_loaded_window(const gui_window_struct* window);
extern void gui_window_history_set_inited_window(const gui_window_struct* window);
extern void gui_window_history_rentry_top_window(void);

extern const gui_window_struct* gui_window_history_get_main(void);
extern const gui_window_struct* gui_window_history_get_top_window(void);
extern gui_window_history_struct* gui_window_history_get_top(void);
extern gui_window_history_struct* gui_window_history_get_root(void);
extern unsigned char gui_window_history_top_is_main(void);
extern unsigned char gui_window_history_is_main(const gui_window_struct* window);
extern unsigned char gui_window_history_is_top(const gui_window_struct* window);
extern unsigned char gui_window_history_is_main_changed(void);
extern gui_window_history_struct* gui_window_history_find(const gui_window_struct* window);
extern void gui_window_history_clear_last_main(void);

extern unsigned char gui_window_history_push(const gui_window_struct* window,GUI_WINDOW_TYPE type,void *buf);
extern unsigned char gui_window_history_replace(const gui_window_struct* window,GUI_WINDOW_TYPE type,void *buf);
extern unsigned char gui_window_history_goto_main(void);
extern unsigned char gui_window_history_go_back(void);
extern void gui_window_history_entry(void *buf);
extern unsigned char gui_window_history_remove_many_back(char count);
extern unsigned char gui_window_history_remove_window(const gui_window_struct* window);
extern void gui_window_history_change_switch_mode(GUI_WINDOW_SWITCH_MODE mode);

extern unsigned short gui_window_history_get_total(void);

// 回溯到指定window
extern void gui_window_history_goback_to_window(const gui_window_struct* window);

// 跳转到home，如遇到有某个windo，它禁止跳转到home或者有拦截指定的event，则回溯到那个window。
extern void gui_window_history_goback_to_home(int event_id);

#endif

