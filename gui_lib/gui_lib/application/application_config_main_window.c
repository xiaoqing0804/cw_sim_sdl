
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "watchface.h"

#include "application.h"
#include "application_config.h"
#include "application_config_main_window.h"
#include "application_touch.h"
#include "gui_window.h"
#include "gui_window_history.h"

// watchface's header files.
#include "gui_event_core_id.h"

extern unsigned int app_window_main_get_count(void);
extern const gui_window_struct* app_window_main_get_watchface(unsigned int index);
extern const picture_info_struct* app_window_main_get_picture(unsigned int index);
extern const picture_info_struct* watchface_setting_get_zoom_pic(void);
extern const picture_info_struct* watchface_user_define_get_zoom_pic(void);


short g_pointer_hour_pos[4];
short g_pointer_min_pos[4];
short g_pointer_sec_pos[4];
unsigned int g_angle_sec_old;
time_struct g_sys_time;


gui_main_window_struct g_main_window_watchface =
{
	.window_index = 0,
    .idle_index = 0,
};


#if defined(GUI_IDLE_CLOCK_SUPPORT)&&GUI_IDLE_CLOCK_SUPPORT
extern const gui_window_struct* app_window_main_get_idle(unsigned int index);
const gui_window_struct* application_main_window_get_idle_watch(void)
{
    return app_window_main_get_idle(g_main_window_watchface.idle_index);
}

void application_main_window_set_idle_index(unsigned char set){
    g_main_window_watchface.idle_index = set;
}
char application_main_window_get_idle_index(void){

    return g_main_window_watchface.idle_index;
}
#endif


void application_main_window_init()
{
	unsigned char index = 0;

	// code
	index = g_watch_face.index;

	if(index == 0xFF)
	{
		index = g_main_window_watchface.window_index;
	}
	application_main_window_switch(index);
}

void application_main_window_rolkey(unsigned char isAdd)
{
	unsigned char index = g_watch_face.index; //0 - n

	if (isAdd) {

		index ++;

	}
	else {
		if (index == 0) {
			index = application_main_window_get_watchface_number();
		}
		index --;
	}
	SYS_DEBUG("bp_index = %d",index);

	application_main_window_switch(index);
	g_watch_face.index = application_main_window_get_curr_index();

	SYS_DEBUG("g_watch_face.index = %d",g_watch_face.index);

	block_save_user_info(&g_watch_face);
}


void application_main_window_switch(unsigned char index)
{
	index = application_main_window_get_index(index);
	g_main_window_watchface.window_index = index;
	if(g_main_window_watchface.window_changed == 0)
	{
		g_main_window_watchface.window_changed = 1;
		g_main_window_watchface.last_window = g_main_window_watchface.window;
	}
	g_main_window_watchface.window = application_main_window_get_window(index);

	if(g_main_window_watchface.window_inited && gui_window_history_top_is_main())
    {
        gui_event_sent_by_id(GUI_EVENT_WINDOW_EXIT, NULL);
		gui_window_goto_main();
}
}

unsigned char application_main_window_set_index(unsigned char index)
{
    if (index < application_main_window_get_watchface_number())
    {
        g_main_window_watchface.window_index = index;
        g_main_window_watchface.window = application_main_window_get_window(index);
    }
    return g_main_window_watchface.window_index;
}

unsigned char application_main_window_get_index(unsigned char index)
{
	if(index >= application_main_window_get_watchface_number())
		index = 0;
	return index;
}

unsigned char application_main_window_get_curr_index()
{
	return application_main_window_get_index(g_main_window_watchface.window_index);
}

const gui_window_struct* application_main_window_get_window(unsigned char index)
{
	index = application_main_window_get_index(index);
	return app_window_main_get_watchface(index);
}

const gui_window_struct* application_main_window_get_curr_window()
{
	return application_main_window_get_window(g_main_window_watchface.window_index);
}

const gui_window_struct* application_main_window_get_next_window()
{
    unsigned int index = application_main_window_get_index(g_main_window_watchface.window_index+1);
	return application_main_window_get_window(index);
}

const gui_window_struct* application_main_window_get_prev_window()
{
    unsigned int index = g_main_window_watchface.window_index;
    if (index > 0) {
        index --;
    }
    else {
        index = application_main_window_get_watchface_number();
        index --;
    }
	return application_main_window_get_window(index);
}

unsigned char application_main_window_set_index_by_window(gui_window_struct* window)
{
    unsigned int index = application_main_window_get_index_by_window(window);
    return application_main_window_set_index(index);
}

unsigned char application_main_window_get_index_by_window(gui_window_struct* window)
{
    unsigned int index, max = application_main_window_get_watchface_number();
    for (index=0; index<max; index++) {
        if (app_window_main_get_watchface(index) == window) {
            return index;
        }
    }
    return 0;
}

unsigned int application_main_window_get_watchface_number(void)
{
    unsigned int count = app_window_main_get_count();
    if (watchface_user_define_flag_check()) {
        return count;
    }
    else {
        return count-1;
    }
}

const picture_info_struct* application_main_window_get_watchface_picture(unsigned int index)
{
    unsigned int count = app_window_main_get_count();
    if (index < (count-2)) {
        return app_window_main_get_picture(index);
    }
    else if (index == (count-2)) {
        // diy
        const picture_info_struct* pic = watchface_setting_get_zoom_pic();
        if (pic != NULL) {
            return pic;
        }
        else {
            return app_window_main_get_picture(index);
        }
    }
    else if (index == (count-1)) {
        // download
        if (watchface_user_define_flag_check()) {
            // change download item's picture.
            const picture_info_struct* pic = watchface_user_define_get_zoom_pic();
            if (pic != NULL) {
                return pic;
            }
            else {
                return app_window_main_get_picture(index);
            }
        }
    }
    return NULL;
}

// 0 ~ 3600
unsigned int application_main_window_get_ang360(time_struct* time)
{
#ifdef __CW_JL__
    static unsigned int base_tick = 0;
    static unsigned int base_angl = 0xFFFFFFFF;
    static unsigned int prev_angl = 0;
    unsigned int value, angle_sec = (time->sec*6*10);    // 60 ps
    unsigned int tick,  dur = 0;

    //printf("base_angl = %d\n", base_angl);
    //printf("angle_sec = %d\n", angle_sec);
    //printf("prev_angl = %d\n", prev_angl);

    tick = sys_timer_get_tick();
    if (base_angl != angle_sec) {
        base_tick = tick;
        base_angl = angle_sec;
        // calibration
        if (angle_sec == 0) {
            prev_angl = base_angl;
        }
        else if (base_angl <= prev_angl) {
            // 鍓嶄竴绉掓椂鍩烘粸鍚庝簡锛屽噺鍘讳竴涓猚yc...
            //base_tick -= WATCH_POINTER360_DUR;
        }
        else if (base_angl > (prev_angl+3)) {
            // 鍓嶄竴绉掓椂鍩鸿秴鍓嶄簡锛屽鍔犱竴涓猚yc...
            //base_tick += WATCH_POINTER360_DUR;
            //tick = base_tick;
        }
        //
    }
    dur = sys_timer_get_dur(base_tick, tick);
    value = dur * 3 / 50;   // count * 3600 / 60000;

    prev_angl = base_angl + value;
    if (prev_angl > angle_sec+60) {
        prev_angl = angle_sec + 60;
    }
    //printf("angle_ret = %d\n", prev_angl);
    return prev_angl;
#else
    unsigned int angle_sec = (time->sec*6*10);          // 60 ps
    unsigned int tick      = sys_timer_get_tick() % 32000;
    angle_sec  = time.sec*6*10;                         // 涓轰簡淇濈暀涓?浣嶅皬鏁帮紝鍒濆瑙掑害鏀惧ぇ鍗佸??...
    angle_sec += tick * 60 / 32000;
    return angle_sec;
#endif
}





