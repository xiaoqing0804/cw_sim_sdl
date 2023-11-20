#ifndef __APPLICATION_CONFIG_MAIN_WINDOW_H__
#define __APPLICATION_CONFIG_MAIN_WINDOW_H__

#include "feature_all.h"
#include "gui_core_all.h"
#include "data_common.h"
#include "application.h"

typedef struct{
    const gui_window_struct*    window;

    const picture_info_struct*  pic_info;

}app_watchface_item_struct;


#define WATCH_POINTER360_DUR        (50)      // ms

extern short g_pointer_hour_pos[4];
extern short g_pointer_min_pos[4];
extern short g_pointer_sec_pos[4];
extern unsigned int g_angle_sec_old;
extern time_struct g_sys_time;
extern gui_main_window_struct g_main_window_watchface;


extern void application_main_window_init(void);
extern void application_main_window_switch(unsigned char index);

extern unsigned char application_main_window_set_index(unsigned char index);
extern unsigned char application_main_window_get_index(unsigned char index);
extern unsigned char application_main_window_get_curr_index(void);
extern unsigned char application_main_window_set_index_by_window(gui_window_struct* window);
extern unsigned char application_main_window_get_index_by_window(gui_window_struct* window);

extern const gui_window_struct* application_main_window_get_window(unsigned char index);
extern const gui_window_struct* application_main_window_get_curr_window(void);
extern const gui_window_struct* application_main_window_get_next_window();
extern const gui_window_struct* application_main_window_get_prev_window();


extern unsigned int application_main_window_get_watchface_number(void);
extern const picture_info_struct* application_main_window_get_watchface_picture(unsigned int index);
extern unsigned int application_main_window_get_ang360(time_struct* time);

extern const gui_window_struct* application_main_window_get_idle_watch(void);
extern void application_main_window_set_idle_index(unsigned char set);
extern char application_main_window_get_idle_index(void);

#endif

