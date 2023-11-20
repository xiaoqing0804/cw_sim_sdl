

#include "debug_info.h"
#include "data_common.h"
#include "ota_updata.h"

#include "application.h"
#include "application_config.h"
#include "application_touch.h"
#include "application_password.h"
#include "application_config_main_window.h"
#include "application_key.h"
#include "application_window_flasherr.h"

#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_event_core.h"
#include "data_gensor_direction.h"
#include "app_window_password_status.h"

#if CHARGER_LAMP_SUPPORT
#include "app_charger_lamp/app_window_charger_lamp.h"
#endif

void application_init()
{
	const app_window_config_struct* application_config = application_config_get_window();
	gui_window_history_set_main(application_config->main_window);
	application_main_window_init();
#if GUI_WIDGET_SUPPORT
	application_widget_update();
#endif

	SYS_DEBUG("application_init(sys_mod: %d), flash_err=%d \n", get_system_mode(), application_flashcrc_check_err());
	if (application_flashcrc_check_err() && (SYS_MODE_LOW_POWER_TYPE != get_system_mode())) {		// 20230831 Taylor.Le, +
		gui_window_power_on(&application_window_flasherr);
		return;
	}

	switch(get_system_mode())
	{
		case SYS_MODE_LOW_POWER_TYPE:
			{
				if (application_config->lowpower_icon_window != NULL)
				{
					gui_window_power_on(application_config->lowpower_icon_window);
				}
			}
			break;

		case SYS_MODE_SHUTDOWN_TYPE:
			{
				if (application_config->lowpower_window != NULL)
				{
		            gui_window_power_on(application_config->lowpower_window);
		        }
			}
			break;

		case SYS_MODE_FACTORY_TEST_TYPE:
			break;

		default:
			{
                app_battery_info_struct* batt_info = application_get_battery_info();

				SYS_DEBUG("application_init(chg: %d)\n", batt_info->charger);
				if(batt_info->charger)
				{
					//SYS_DEBUG("application_init_get_battery_info");
					if(application_config->charger_window != NULL)
					{
						//SYS_DEBUG("application_init_get_battery_info1");
						gui_window_power_on(application_config->charger_window);
						return;
					}
				}

		        if(application_config->logo_window != NULL)
		            gui_window_power_on(application_config->logo_window);
		        else
		            gui_window_goto_main();
			}
			break;
	}
}


void application_switch(GUI_WINDOW_SWITCH_TYPE type, const gui_window_struct* window,void* data)
{
	if(type == GUI_WINDOW_SWITCH_TYPE_PUSH)
		gui_window_push(window,GUI_WINDOW_TYPE_WINDOW,data);
	else if(type == GUI_WINDOW_SWITCH_TYPE_REPLACE)
		gui_window_replace(window,GUI_WINDOW_TYPE_WINDOW,data);
}

void application_remove_many(char count)
{
	gui_window_remove_many_back(count);

}


void application_go_back()
{
	gui_window_go_back();
}

void application_goto_main_int(int force)
{
    if (!gui_window_history_top_is_main() || gui_window_history_is_main_changed()) {
        SYS_DEBUG("app: goto_main, force=%d", force);
        if (force) {
            gui_window_goto_main();
        }
        else {
            gui_window_history_goback_to_home(EVENT_GO_HOME);
        }
    }
}

void application_goto_main()
{
	app_battery_info_struct* batt_info = application_get_battery_info();
	if (batt_info->charger) {
		application_charger();
	}
	else {
	    application_goto_main_int(1);
	}
}

void application_shutdown()
{
	const app_window_config_struct* application_config = application_config_get_window();
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH,application_config->shutdown_window,NULL);
}

void application_password(unsigned int setFlag)     // 0: verify password; 1: turn on/off password
{
#if defined(GUI_PASSWORD_SUPPORT) && GUI_PASSWORD_SUPPORT
    SYS_DEBUG("application_password(%d)", setFlag);
	app_window_password_status_init_for_unlock();
	const app_window_config_struct* application_config = application_config_get_window();
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH,application_config->password_window, &setFlag);
#endif
}

void application_lowpower(void)
{
	const app_window_config_struct* application_config = application_config_get_window();
    if (application_config->lowpower_window != NULL) {
		if(!ota_check())
        	gui_window_power_on(application_config->lowpower_window);
    }
}

void application_lowpower_icon(void)
{
	const app_window_config_struct* application_config = application_config_get_window();
    if (application_config->lowpower_icon_window != NULL) {
        gui_window_power_on(application_config->lowpower_icon_window);
    }
}

void application_flasherr_window(void)	// 20230831 Taylor.Le, +
{
	const app_window_config_struct* application_config = application_config_get_window();
    if (application_config->flasherr_window != NULL) {
       	gui_window_power_on(application_config->flasherr_window);
    }
}

void application_charger(void)
{
	const app_window_config_struct* application_config = application_config_get_window();
    if (application_config->charger_window != NULL) {
		if(!ota_check())
		{
	#if CHARGER_LAMP_SUPPORT
			if(data_gsensor_direction_get_type() == DIRECTION_TYPE_NONE)
			{
				gui_window_power_on(application_config->charger_window);
			}
			else
			{
				gui_window_power_on(&app_window_charger_lamp);
			}
	#else
			gui_window_power_on(application_config->charger_window);
	#endif
		}
    }

}

void application_press_key1()
{
	const app_window_config_struct* application_config = application_config_get_window();
	if(application_config->key1_window != NULL)
		gui_window_push(application_config->key1_window,GUI_WINDOW_TYPE_WINDOW, NULL);
}

void application_double_key1()
{
	const app_window_config_struct* application_config = application_config_get_window();
	if(application_config->key1_double_window != NULL)
		gui_window_push(application_config->key1_double_window,GUI_WINDOW_TYPE_WINDOW, NULL);
}

void application_long_key1()
{
	const app_window_config_struct* application_config = application_config_get_window();
	if(application_config->key1_long_window != NULL)
		gui_window_push(application_config->key1_long_window,GUI_WINDOW_TYPE_WINDOW, NULL);
}


void application_press_key2()
{
	const app_window_config_struct* application_config = application_config_get_window();
	if(application_config->key2_window != NULL)
		gui_window_push(application_config->key2_window,GUI_WINDOW_TYPE_WINDOW, NULL);
}

void application_double_key2()
{
	const app_window_config_struct* application_config = application_config_get_window();
	if(application_config->key2_double_window != NULL)
		gui_window_push(application_config->key2_double_window,GUI_WINDOW_TYPE_WINDOW, NULL);
}

void application_long_key2()
{
	const app_window_config_struct* application_config = application_config_get_window();
	if(application_config->key2_long_window != NULL)
		gui_window_push(application_config->key2_long_window,GUI_WINDOW_TYPE_WINDOW, NULL);
}

int application_event_handler_all(short event)
{
    short is_find_all = 0;
	const gui_window_struct *window = gui_window_history_get_top_window();
	if (window != NULL)  {
		if (window->config && window->config->enable_touch && (event == EVENT_TOUCH_DOWN || event == EVENT_TOUCH_UP))  {
			return 0;
		}
		for (unsigned int idx = 0; idx < window->event_num; idx++) {
			if ((window->events[idx].id == EVENT_ALL) && (window->events[idx].handler == NULL)) {
				is_find_all = 1;
			}
			if (window->events[idx].id == event) {
				return 0;
			}
		}
	}
	return is_find_all;
}

int application_event_handler_run(short event, void* buf)
{
    const gui_window_struct* window = gui_window_history_get_top_window();
    if (window != NULL) {
        unsigned int all_idx = 0xFFFFFFFF;
        unsigned int idx;
        for (idx=0; idx<window->event_num; idx++) {
            if (window->events[idx].id == event) {
                if (window->events[idx].handler != NULL) {
                    window->events[idx].handler(buf, event);
                }
				return 1;
            }
			else if ((window->events[idx].id == EVENT_ALL) && (window->events[idx].handler != NULL)) {
				all_idx = idx;
			}
        }
		
		if (all_idx != 0xFFFFFFFF) {
            return window->events[all_idx].handler(buf, event);
		}
    }
    return 0;
}

static int application_event_handler_window(short event, void* buf)
{
	if(application_event_handler_key(event,buf))
		return 1;
	return application_event_handler_run(event, buf);
}

static int application_event_handler_control(short event, void* buf)
{
	//SYS_DEBUG("application_event_handler_control=%d",event);
	return (int)gui_event_sent_by_id((APPLICATION_EVENT_TYPE)event,buf);
}

int application_window_event_handler(short event, void* buf)
{
	application_event_handler_control(event,buf);
	if (application_event_handler_window(event,buf)) {
        return 1;
    }
    return 0;
}





