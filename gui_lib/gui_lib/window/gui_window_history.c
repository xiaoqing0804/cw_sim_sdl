#include "gui_window_history.h"
#include "gui_window_history_cache.h"
#include "gui_surface_box_label_scroll.h"
#include "gui_surface_layout.h"
#include "gui_event_core.h"
#include "gui_surface_layout_tween_position.h"

static gui_window_history_struct* gui_window_history_root = NULL;
static gui_window_history_struct* gui_window_history_top = NULL;

static gui_main_window_struct* g_window_history_main_window = NULL;/*主窗口*/
static const gui_window_struct* g_gui_window_inited_window = NULL;
static const gui_window_struct* g_gui_window_loaded_window = NULL;

static void gui_window_history_exit_window(const gui_window_struct *window)
{
	//SYS_DEBUG("gui_window_history_exit_window");
	gui_surface_box_label_scroll_end();
    gui_surface_layout_tween_position_stop();
    gui_surface_layout_tween_angle_stop();
	gui_event_sent_by_id(GUI_EVENT_WINDOW_EXIT,NULL);
	if(window && window->exit)
	{
		//SYS_DEBUG("gui_window_history_exit_window 1");
		for(int i =APPLICATION_TIMER_ACT;i<APPLICATION_TIMER_ACT_ALL;i++){ /*窗口退出关闭所有窗口定时器*/
            application_close_act_timer(i);
		}		
		gui_surface_layout_exit(window);
		window->exit();
	}

}

static void gui_window_history_destroy_window(const gui_window_struct *window)
{
    if(window && window->destroy)
    {
        window->destroy();
    }
}


#if 0 //暂时用不上
//如果存在此窗口，则将该窗口移动到最后
//0，不需要移动,  1成功地移动到最后
static unsigned char gui_window_history_move_to_back(const gui_window_struct* window)
{
    if(gui_window_history_is_top(window))
        return 0;

    gui_window_history_struct* history = gui_window_history_find(window);
    if(history == NULL)
        return 0;

    gui_window_history_struct* front = history->front;
    gui_window_history_struct* next = history->next;

    if(front != NULL) front->next = next;
    if(next != NULL) next->front = front;

    if(gui_window_history_top->window->exit)
        gui_window_history_top->window->exit();

    gui_window_history_top->next = history;
    history->front = gui_window_history_top;
    history->next = NULL;

    gui_window_history_top = history;

    return 1;
}
#endif

//删除最后一个界面
static unsigned char gui_window_history_remove_back()
{
    gui_window_history_struct* history = gui_window_history_top;
    if(history != NULL)
    {
        gui_window_history_struct* front = history->front;

        gui_window_history_exit_window(history->window);
        gui_window_history_destroy_window(history->window);
        gui_window_history_cache_remove(history);

        if(front == NULL)
        {
            gui_window_history_root = NULL;
            gui_window_history_top = NULL;
        }
        else
        {
            front->next = NULL;
            gui_window_history_top = front;
        }
        return 1;
    }
    return 0;
}


static void gui_window_history_remove_all_window()
{
    gui_window_history_struct* history = gui_window_history_top;
    while(history != NULL)
    {
        gui_window_history_exit_window(history->window);
        gui_window_history_destroy_window(history->window);

        history = history->front;
    }
    gui_window_history_cache_clear();
    gui_window_history_root = NULL;
    gui_window_history_top = NULL;
}


//删除到界面，把中间的全删除掉
static unsigned char gui_window_history_remove_to_window(const gui_window_struct* to_window)
{
    if(to_window == NULL)
        return 0;

    if(gui_window_history_is_top(to_window))
        return 0;

    // Taylor.Le, +
    if (gui_window_history_top == NULL) {
		gui_event_sent_by_id(GUI_EVENT_WINDOW_EXIT,NULL);
		
        const gui_window_struct* top_window = gui_window_history_get_top_window();
        if(g_window_history_main_window->window == top_window && g_window_history_main_window->window_inited)
            gui_window_history_exit_window(top_window);
    }
    //

    gui_window_history_struct* history = gui_window_history_find(to_window);
    if(history == NULL)
        return 0;

    history = gui_window_history_top;
    gui_window_history_struct* front = NULL;
    while(history != NULL)
    {
        if(history->window == to_window)
        {
            history->next = NULL;
            gui_window_history_top = history;
            return 1;
        }
        front = history->front;

        gui_window_history_exit_window(history->window);
        gui_window_history_destroy_window(history->window);

        gui_window_history_cache_remove(history);
        history = front;
    }
    gui_window_history_root = NULL;
    gui_window_history_top = NULL;
    return 0;
}

static unsigned char gui_window_history_remove_many_window(char count)
{
    if(gui_window_history_top == NULL)
        return 0;

    gui_window_history_struct* history = gui_window_history_top;
    gui_window_history_struct* front = NULL;
    char total = 0;
    while(history != NULL)
    {
        if(total++ == count)
        {
            history->next = NULL;
            gui_window_history_top = history;
            return 1;
        }
        front = history->front;

        gui_window_history_exit_window(history->window);
        gui_window_history_destroy_window(history->window);

        gui_window_history_cache_remove(history);
        history = front;
    }
    gui_window_history_root = NULL;
    gui_window_history_top = NULL;
    return 0;
}

static unsigned char gui_window_history_create(const gui_window_struct* window,GUI_WINDOW_TYPE type)
{
    gui_window_history_struct* history = gui_window_history_cache_get();
    history->window = window;
    history->type = type;

    if(gui_window_history_root == NULL)
    {
        gui_event_sent_by_id(GUI_EVENT_WINDOW_EXIT,NULL);
        gui_window_history_root = history;
        gui_window_history_top = history;
    }
    else
    {
        gui_window_history_exit_window(gui_window_history_top->window);
        history->front = gui_window_history_top;
        if(gui_window_history_top != NULL)
        {
            gui_window_history_top->next = history;
        }
        gui_window_history_top = history;
    }
    return 1;
}


void gui_window_history_set_main(gui_main_window_struct* window)
{
    g_window_history_main_window = window;
}


void gui_window_history_set_inited_window(const gui_window_struct* window)
{
    g_gui_window_inited_window = window;
}

void gui_window_history_set_loaded_window(const gui_window_struct* window)
{
    g_gui_window_loaded_window = window;
}

void gui_window_history_rentry_top_window(void)
{
	const gui_window_struct* window = gui_window_history_get_top_window();
    if (window != NULL && window->entry != NULL) {
        window->entry(NULL);
    }
}


const gui_window_struct* gui_window_history_get_main()
{
    return g_window_history_main_window->window;
}

const gui_window_struct* gui_window_history_get_top_window()
{
    if(gui_window_history_top != NULL)
        return gui_window_history_top->window;
    return g_window_history_main_window->window;
}

gui_window_history_struct* gui_window_history_get_top()
{
    return gui_window_history_top;
}

gui_window_history_struct* gui_window_history_get_root()
{
    return gui_window_history_root;
}

unsigned short gui_window_history_get_total()
{
    unsigned short count = 0;
    gui_window_history_struct* history_top = gui_window_history_top;
    while(history_top != NULL)
    {
        count++;
        history_top = history_top->front;
    }
    return count;
}

unsigned char gui_window_history_top_is_main()
{
    return gui_window_history_top == NULL;
}

unsigned char gui_window_history_is_main(const gui_window_struct* window)
{
    return window == (g_window_history_main_window->window);
}

unsigned char gui_window_history_is_top(const gui_window_struct* window)
{
    return gui_window_history_top != NULL && window == gui_window_history_top->window;
}

unsigned char gui_window_history_is_main_changed()
{
    return(g_window_history_main_window->window_changed
           && g_window_history_main_window->window != g_window_history_main_window->last_window);
}



//查找历史界面
//注 : 主界面无历史
gui_window_history_struct* gui_window_history_find(const gui_window_struct* window)
{
    if(window == NULL)
        return NULL;

    gui_window_history_struct* history = gui_window_history_top;
    while(history != NULL)
    {
        if(history->window == window)
            return history;

        history = history->front;
    }
    return NULL;
}

void gui_window_history_clear_last_main()
{
    if(gui_window_history_is_main_changed())
    {
        if(g_window_history_main_window->last_window != NULL)
        {
            if(gui_window_history_top == NULL)
            {
                gui_window_history_exit_window(g_window_history_main_window->last_window);
            }
            else
            {
                gui_event_sent_by_id(GUI_EVENT_WINDOW_EXIT,NULL);
            }
            gui_window_history_destroy_window(g_window_history_main_window->last_window);
        }
    }
}



unsigned char gui_window_history_push(const gui_window_struct* window,GUI_WINDOW_TYPE type,void *buf)
{
    if(window == NULL || gui_window_history_is_top(window))
        return 0;

    if(gui_window_history_is_main(window))
        return gui_window_history_goto_main();

    const gui_window_struct* top_window = gui_window_history_get_top_window();
    if(top_window != NULL)
    {
        const gui_window_config_struct* config = top_window->config;
        if(config && config->entry_back_to_destory)
        {
            gui_window_history_remove_back();
        }
    }

    unsigned char success = gui_window_history_remove_to_window(window);
    if(!success)
    {
        if(gui_window_history_create(window,type))
        {
            gui_window_history_top->window->init(buf);
        }
    }
    return 1;
}

unsigned char gui_window_history_replace(const gui_window_struct* window,GUI_WINDOW_TYPE type,void *buf)
{
	if(window == NULL || gui_window_history_is_top(window)) {
        //SYS_DEBUG("gui: window_his_rep 0");
		return 0;
    }

	if(gui_window_history_is_main(window)) {
        //SYS_DEBUG("gui: window_his_rep 1");
		return gui_window_history_goto_main();
    }

	if(gui_window_history_top == NULL)
	{
        //SYS_DEBUG("gui: window_his_rep 2");

        // Taylor.Le, +
        const gui_window_struct* top_window = gui_window_history_get_top_window();
        if(top_window != NULL)
            top_window->exit();
        //

        gui_window_history_create(window,type);
        if(g_gui_window_inited_window != gui_window_history_top->window)
        {
            gui_window_history_top->window->init(buf);
        }
        return 1;
    }

    gui_window_history_struct* history = gui_window_history_find(window);
    if(history == NULL)
    {
        //SYS_DEBUG("gui: window_his_rep 3");
        gui_window_history_remove_back();
        gui_window_history_create(window,type);
        if(g_gui_window_inited_window != gui_window_history_top->window)
        {
            gui_window_history_top->window->init(buf);
        }
    }
    else
    {
        //SYS_DEBUG("gui: window_his_rep 4");
        gui_window_history_remove_to_window(window);
    }
    return 1;
}

unsigned char gui_window_history_goto_main()
{
    gui_window_history_remove_all_window();
    gui_window_history_root = NULL;
    gui_window_history_top = NULL;
    if(gui_window_history_is_main_changed())
    {
        if(g_window_history_main_window->window && g_window_history_main_window->window->init)
        {
            if(g_gui_window_inited_window != g_window_history_main_window->window)
            {
                g_window_history_main_window->window->init(NULL);
            }
        }
    }
    g_window_history_main_window->window_changed = 0;
    g_window_history_main_window->last_window = NULL;
    g_window_history_main_window->window_inited = 1;
    return 1;
}

unsigned char gui_window_history_go_back()
{
    if(gui_window_history_top == NULL)
        return 0;

    if(gui_window_history_top == gui_window_history_root)
        return gui_window_history_goto_main();

    return gui_window_history_remove_back();
}

unsigned char gui_window_history_remove_many_back(char count)
{
    if(gui_window_history_top == NULL)
        return 0;

    if(count == 0)
        return 0;

    if(gui_window_history_top == gui_window_history_root)
        return gui_window_history_goto_main();

    return gui_window_history_remove_many_window(count);
}

//删除指定界面
void gui_window_history_remove_all_exclude_top()
{
    if(gui_window_history_top == NULL || gui_window_history_top->front == NULL)
        return;

    gui_window_history_struct* history = gui_window_history_top->front;
    gui_window_history_struct* front = NULL;
    while(history != NULL)
    {
        front = history->front;
        gui_window_history_exit_window(history->window);
        gui_window_history_destroy_window(history->window);
        gui_window_history_cache_remove(history);
        history = front;
    }

    gui_window_history_root = gui_window_history_top;
    gui_window_history_top->front = NULL;

}

// 回溯到指定window
void gui_window_history_goback_to_window(const gui_window_struct* window)
{
    if(gui_window_history_top == NULL || gui_window_history_top->window == window) {
        return;
    }

    gui_window_history_struct* history = gui_window_history_top;
    gui_window_history_struct* front;
    unsigned int  found = 0;
    
    while(history != NULL) {
        if (history->window == window) {
            found = 1;
            break;
        }
        history = history->front;
    }
    if (found == 0) {
        return;
    }

    history = gui_window_history_top;
    while(history != NULL) {
        if (history->window == window) {
            break;
        }
        front = history->front;
        gui_window_history_exit_window(history->window);
        gui_window_history_destroy_window(history->window);
        gui_window_history_cache_remove(history);
        history = front;
    }
    gui_window_history_top = history;
    if (gui_window_history_top == NULL) {
        gui_window_history_root = NULL;
        gui_window_goto_main();
    }
    else {
        gui_surface_clear_all_surface();
        gui_surface_create_main_surface(history->window);
        gui_window_history_entry(NULL);
        gui_surface_load_surface();
    }
}



// 跳转到home，如遇到有某个windo，它禁止跳转到home或者有拦截指定的event，则回溯到那个window。
void gui_window_history_goback_to_home(int event_id)
{
    //SYS_DEBUG("gui: window_history_goback_to_home");
    if(gui_window_history_top == NULL) {
        //SYS_DEBUG("gui: window_history_goback_to_home 0");
        return;
    }

    gui_window_history_struct* history = gui_window_history_top;
    gui_window_history_struct* front;
    while(history != NULL) {
        if (history->window->config && history->window->config->disable_go_home == 1) {
            break;
        }
        if (gui_wnidow_check_event(history->window, event_id)) {
            break;
        }

        front = history->front;
        gui_window_history_exit_window(history->window);
        gui_window_history_destroy_window(history->window);
        gui_window_history_cache_remove(history);
        history = front;
    }
    if (history == NULL) {
        gui_window_history_top  = NULL;
        gui_window_history_root = NULL;
        gui_window_goto_main();
        //SYS_DEBUG("gui: window_history_goback_to_home 1");
    }
    else {
        //SYS_DEBUG("gui: %x", (unsigned int)history->window);
        if (gui_window_history_top != history) {
            gui_window_history_top = history;
            gui_window_history_top->next = NULL;		// 20230513 Taylor.Le, UI bug-fixed

			gui_surface_clear_all_surface();
			gui_surface_create_main_surface(history->window);
			gui_window_history_entry(NULL);
			gui_surface_load_surface();

            //SYS_DEBUG("gui: window_history_goback_to_home 2");
        }
        else {
            //SYS_DEBUG("gui: window_history_goback_to_home 3");
        }
    }
}


//删除指定界面
unsigned char gui_window_history_remove_window(const gui_window_struct* window)
{
    if(gui_window_history_top == NULL || window == NULL)
        return 0;

    //不能删除正在使用的自己
    if(gui_window_history_is_top(window))
        return 0;

    gui_window_history_struct* history = gui_window_history_top;
    gui_window_history_struct* front = history->front;
    gui_window_history_struct* next = history->next;
    while(history != NULL)
    {
        front = history->front;
        next = history->next;
        if(history->window == window)
        {
            gui_window_history_exit_window(history->window);
            gui_window_history_destroy_window(history->window);
            gui_window_history_cache_remove(history);

            if(front == NULL)
            {
                gui_window_history_root = next;
                next->front = NULL;                         // 20230512 bug_fixed: 当删除第一个历史后，再进入其它界面死机问题!!!!!
            }
            else
            {
                front->next = next;
                next->front = front;
            }
            return 1;
        }
        history = history->front;
    }
    return 0;
}

void gui_window_history_change_switch_mode(GUI_WINDOW_SWITCH_MODE mode)
{
    gui_window_history_struct* top = gui_window_history_get_top();
    if(top != NULL)
    {
        top->switch_mode = (unsigned char)mode;
    }
}

void gui_window_history_entry(void *buf)
{
    if(gui_window_history_top != NULL)
    {
        if(g_gui_window_loaded_window != gui_window_history_top->window)
        {
            gui_window_history_top->window->load(buf);
        }
        gui_surface_layout_entry(gui_window_history_top->window);
        gui_window_history_top->window->entry(buf);
    }
    else if(g_window_history_main_window->window)
    {
        if(g_gui_window_loaded_window != g_window_history_main_window->window)
        {
            g_window_history_main_window->window->load(buf);
        }
        gui_surface_layout_entry(g_window_history_main_window->window);
        g_window_history_main_window->window->entry(buf);
    }
}






