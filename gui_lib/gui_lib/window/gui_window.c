#include "gui_window.h"
#include "gui_window_history.h"
#include "gui_window_history_cache.h"
#include "gui_surface.h"
#include "gui_surface_layout.h"


/*开机第一个窗口*/
void gui_window_power_on(const gui_window_struct* window)
{
    gui_window_push(window, GUI_WINDOW_TYPE_WINDOW, NULL);
}

/*跳转到主窗口*/
void gui_window_goto_main()
{
	gui_window_history_clear_last_main();
	const gui_window_struct* window = gui_window_history_get_main();
	if(window != NULL){
		gui_surface_clear_all_surface();
		gui_surface_create_main_surface(window);
		gui_window_history_goto_main();
		gui_window_history_entry(NULL);
		gui_surface_load_surface();
	}
}

/*返回上一个窗口*/
void gui_window_go_back()
{
	if(gui_window_history_go_back())
	{
		const gui_window_struct* window = gui_window_history_get_top_window();
		if(window != NULL)
		{
			gui_surface_clear_all_surface();
			gui_surface_create_main_surface(window);
			gui_window_history_entry(NULL);
			gui_surface_load_surface();
		}
		else
		{
			gui_window_goto_main();
		}
	}
}

void gui_window_remove_many_back(char count)
{
	if(gui_window_history_remove_many_back(count))
	{
		const gui_window_struct* window = gui_window_history_get_top_window();
		if(window != NULL)
		{
			gui_surface_clear_all_surface();
			gui_surface_create_main_surface(window);
			gui_window_history_entry(NULL);
			gui_surface_load_surface();
		}
		else
		{
			gui_window_goto_main();
		}
	}
}

/*增加到前一个窗口的后面*/
void gui_window_push(const gui_window_struct* window, GUI_WINDOW_TYPE type, void* data)
{
	if(gui_window_history_push(window,type,data))
	{
		const gui_window_struct* window = gui_window_history_get_top_window();
		if(window != NULL)
		{
			gui_surface_clear_all_surface();
			gui_surface_create_main_surface(window);
			gui_window_history_entry(data);
			gui_surface_load_surface();
		}
		else
		{
			gui_window_goto_main();
		}
	}
}

/*替换前一个窗口*/
void gui_window_replace(const gui_window_struct* window, GUI_WINDOW_TYPE type, void* data)
{
	if(gui_window_history_replace(window,type,data))
	{
		const gui_window_struct* window = gui_window_history_get_top_window();
		if(window != NULL)
		{
			gui_surface_clear_all_surface();
			gui_surface_create_main_surface(window);
			gui_window_history_entry(data);
			gui_surface_load_surface();
		}
		else
		{
			gui_window_goto_main();
		}
	}
}

// 检查window是否有拦截指定的event
int gui_wnidow_check_event(const gui_window_struct *window, int event)
{
    unsigned int idx;
    if (window != NULL) {
        for (idx=0; idx<window->event_num; idx++) {
            if (window->events[idx].id == event) {
                return 1;
            }
        }
    }
    return 0;
}


