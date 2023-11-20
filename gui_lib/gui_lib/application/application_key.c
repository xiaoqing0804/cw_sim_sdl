#include "application.h"
#include "data_common.h"
#include "application_config.h"
#include "application_password.h"
#include "application_touch.h"
#include "application_config_main_window.h"

#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_event_core.h"

#include "app_main/app_window_main_locker.h"
#include "application_key.h"

static unsigned int key_timer_id = 0;
static unsigned int key2_timer_id = 0;
static unsigned int key3_timer_id = 0;

unsigned char application_event_is_key_done(short event)
{
    switch(event) 
    {
        case EVENT_ROLKEY:
        case EVENT_KEY1_LONG:
        case EVENT_KEY1_SHORT:
        case EVENT_KEY2_LONG:
        case EVENT_KEY2_SHORT:
        case EVENT_KEY3_LONG:
        case EVENT_KEY3_SHORT:
            return 1;
        default:
            return 0;
    }
}

unsigned char application_event_is_all_key(short event)
{
    switch(event) 
    {
        case EVENT_ROLKEY:
        case EVENT_KEY1_PRESS:
        case EVENT_KEY1_LONG:
        case EVENT_KEY1_REPEAT:
        case EVENT_KEY1_SHORT:
        case EVENT_KEY1_RELEASE:
        case EVENT_KEY2_PRESS:
        case EVENT_KEY2_LONG:
        case EVENT_KEY2_REPEAT:
        case EVENT_KEY2_SHORT:
        case EVENT_KEY2_RELEASE:
        case EVENT_KEY3_PRESS:
        case EVENT_KEY3_LONG:
        case EVENT_KEY3_REPEAT:
        case EVENT_KEY3_SHORT:
        case EVENT_KEY3_RELEASE:
            return 1;
        default:
            return 0;
    }
}


static void application_event_goto_main(void)
{
	const gui_window_struct* top_window = gui_window_history_get_top_window();
	if(top_window != NULL
		&&top_window->config != NULL
		&& top_window->config->forbid_key_back)
	{
		return;
	}
	application_goto_main();
}

static int application_event_handler_check(short event)
{
	const gui_window_struct* window = gui_window_history_get_top_window();
    if (window != NULL) {
        for (unsigned int idx = 0; idx < window->event_num; idx++) {
            if (window->events[idx].id == event) {
				return 1;
            }
        }
    }
	return 0;
}

/*
static int application_event_handler_run(short event, void* buf)
{
	const gui_window_struct* window = gui_window_history_get_top_window();
    if (window != NULL) {
        for (unsigned int idx = 0; idx < window->event_num; idx++) {
            if (window->events[idx].id == event) {
                if (window->events[idx].handler != NULL) {
                    window->events[idx].handler(buf, event);
                }
                return 1;
            }
        }
    }
	return 0;
}*/

static void application_event_go_back_handler(void)
{
    if  (!application_event_handler_run(EVENT_GO_BACK, NULL)) {
        application_go_back();
    }
}


static void application_event_handler_key_timer(unsigned int timer, void* param)
{
	application_stop_user_timer(timer);

    if (key_timer_id == timer) {
        key_timer_id = 0;
        if(!application_event_handler_run(EVENT_KEY1_SHORT,NULL)) {
        #if GUI_SINGLE_KEY_SUPPORT
            application_event_go_back_handler();    // application_go_back();
        #else
            application_event_goto_main();
        #endif
        }
    }
	else if (key2_timer_id == timer) {
        key2_timer_id = 0;
        if(!application_event_handler_run(EVENT_KEY2_SHORT,NULL)) {
            application_event_go_back_handler();    // application_go_back();
        }
    }	else if (key3_timer_id == timer) {
        key3_timer_id = 0;
        if(!application_event_handler_run(EVENT_KEY3_SHORT,NULL)) {
            application_event_go_back_handler();    // application_go_back();
        }
    }
}

static int application_event_handler_key_int(short event, void* buf)
{
	if(event == EVENT_KEY1_SHORT)
	{
		if(key_timer_id == 0)
		{
//			if(application_event_handler_check(EVENT_KEY1_DOUBLE))
				key_timer_id = application_start_user_timer(KEY_DOUBLE_TIME, application_event_handler_key_timer, buf);
//			else if(!application_event_handler_run(EVENT_KEY1_SHORT,NULL))
//				application_event_goto_main();
		}
		else
		{
			key_timer_id = application_stop_user_timer(key_timer_id);
			application_event_handler_run(EVENT_KEY1_DOUBLE,buf);
		}
		return 1;
	}
    else if (event == EVENT_KEY2_SHORT) {
        if (key2_timer_id == 0) {
            //if (application_event_handler_check(EVENT_KEY2_DOUBLE)) {
                key2_timer_id = application_start_user_timer(KEY_DOUBLE_TIME, application_event_handler_key_timer, buf);
            //}
            //else if(!application_event_handler_run(EVENT_KEY2_SHORT,NULL)) {
            //    application_event_go_back_handler();    // application_go_back();
            //}
        }
        else {
			key2_timer_id = application_stop_user_timer(key2_timer_id);
			application_event_handler_run(EVENT_KEY2_DOUBLE,buf);
        }
        return 1;
    }
      else if (event == EVENT_KEY3_SHORT) {
        if (key3_timer_id == 0) {
            //if (application_event_handler_check(EVENT_KEY3_DOUBLE)) {
                key3_timer_id = application_start_user_timer(KEY_DOUBLE_TIME, application_event_handler_key_timer, buf);
            //}
            //else if(!application_event_handler_run(EVENT_KEY3_SHORT,NULL)) {
            //    application_event_go_back_handler();    // application_go_back();
            //}
        }
        else {
			key3_timer_id = application_stop_user_timer(key3_timer_id);
			application_event_handler_run(EVENT_KEY3_DOUBLE,buf);
        }
        return 1;
    }
	return 0;
}

int application_event_handler_key(short event, void* buf)
{
    if(!application_event_is_all_key(event))
        return 0;

    if (application_touch_event_is_active())
            return 1;

#if defined(GUI_PASSWORD_SUPPORT) && GUI_PASSWORD_SUPPORT
    if (application_event_is_key_done(event) && application_password_isLocked()) 
    {
        application_password(0);
        return 1;
    }
#endif

	if (is_locked_screen()) 
    {
		if(event == EVENT_KEY1_LONG) 
        {
			set_locked_screen(0);
			application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH,&app_window_main_locker, NULL);
		}
		else if(event == EVENT_KEY1_SHORT) 
        {
			application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH,&app_window_main_locker, NULL);
		}
        return 1;
	}
    else 
    {
        if(application_event_handler_key_int(event, buf)) 
            return 1;
    }
	return 0;
}


void application_key_cancel_all(void)
{
    if (key_timer_id != 0) {
        application_stop_user_timer(key_timer_id);
        key_timer_id = 0;
    }
    if (key2_timer_id != 0) {
        application_stop_user_timer(key2_timer_id);
        key2_timer_id = 0;
    }
    if (key3_timer_id != 0) {
        application_stop_user_timer(key3_timer_id);
        key3_timer_id = 0;
    }
}

