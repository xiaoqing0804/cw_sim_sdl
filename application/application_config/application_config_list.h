#ifndef __APPLICATION_CONFIG_LIST_H__
#define __APPLICATION_CONFIG_LIST_H__

#include "feature_all.h"
#include "gui_core_all.h"

#define C_WINDOW_SWIPE_LIST_SZ      20

#define APP_MAIN_WINDOW_MAGIC       ((const gui_window_struct*)0xFF4D4149) // .main
#define APP_MAIN_WINDOW_NEXT_MAGIC  ((const gui_window_struct*)0xFF4D2D4E) // .main-Next
#define APP_MAIN_WINDOW_PREV_MAGIC  ((const gui_window_struct*)0xFF4D2D50) // .main-Prev
#define APP_FUNC_WINDOW_MAGIC       ((const gui_window_struct*)0xFF46554E) // .func

extern const gui_window_swipe_struct* application_list_get_swipe_window(const gui_window_struct* window);
extern void application_list_change(const gui_window_struct* window,
                                            const gui_window_struct* up,
                                            const gui_window_struct* down,
                                            const gui_window_struct* left,
                                            const gui_window_struct* right);

extern void application_list_clean_window(const gui_window_struct* window);

#endif

