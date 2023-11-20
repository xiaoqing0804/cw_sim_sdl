#ifndef __GUI_CORE_WINDOW_H__
#define __GUI_CORE_WINDOW_H__

#include "feature_all.h"
#include "gui_core_touch.h"
#include "gui_core_screen.h"
#include "gui_core_screen_control.h"
#include "gui_core_layout.h"
#include "app_task_main.h"

typedef enum
{
	GUI_WINDOW_SWITCH_TYPE_PUSH,
	GUI_WINDOW_SWITCH_TYPE_REPLACE,
}GUI_WINDOW_SWITCH_TYPE;

typedef enum
{
	GUI_WINDOW_SWITCH_MODE_JUMP = 0,
	GUI_WINDOW_SWITCH_MODE_SWIPE,
}GUI_WINDOW_SWITCH_MODE;

typedef enum
{
	WINDOW_SWIPE_TYPE_MOVE,     //平移
	WINDOW_SWIPE_TYPE_COVER,	//覆盖，一般是上下界面
	WINDOW_SWIPE_TYPE_FOLD,		//折叠，一般是左右界面
	WINDOW_SWIPE_TYPE_JUMP,		//跳转
}WINDOW_SWIPE_TYPE;

typedef enum
{
	GUI_WINDOW_TYPE_WINDOW,
	GUI_WINDOW_TYPE_DIALOG,
	GUI_WINDOW_TYPE_NOTICE,
}GUI_WINDOW_TYPE;


typedef enum
{
	GUI_STATUS_TYPE_NONE,
	GUI_STATUS_TYPE_IDLE,
	GUI_STATUS_TYPE_START,
	GUI_STATUS_TYPE_KEEP,
	GUI_STATUS_TYPE_END,
}GUI_STATUS_TYPE;



typedef struct
{
	unsigned char forbid_gesture_back;  //禁止左划手势返回
	unsigned char forbid_key_back;      //禁止按键返回
	unsigned char entry_back_to_destory;//进入后台后自动销毁
	unsigned char enable_touch;         // 有些window拦截了EVENT_ALL,但是又要响应TP的情况，设定这个标记
	unsigned char disable_go_home;      // 当window处于top或者history，响应go home事件时，不跳转到home。
	unsigned char disable_scale;        // 此window不可以进行缩放(diy|download watchface)
	unsigned char idle;
}gui_window_config_struct;

typedef struct
{
	const gui_screen_struct* screen;
	const gui_window_config_struct* config;

	void (*init)(void *buf);  	//初始化，分配内存等
	void (*load)();				//加载默认数据,显示默认界面,手势操作时，要显示的前期界面
	void (*entry)();			//进入界面，如开启定时器，点击事件等
	void (*exit)();
	void (*destroy)();

	/*排版界面上响应点击事件*/
	void (*click_on_layout_item)(gui_click_layout_struct *event);
	void (*layout_value_changed)(gui_layout_value_struct *event);
	void (*layout_moving)(gui_layout_header_struct *event);

	unsigned char touch_event_num;
	unsigned char event_num;

	const gui_touch_event_struct* touch_events;
	const app_window_event_struct* events;
}gui_window_struct;


typedef struct
{
	const gui_window_struct* last_window; //上一次切换的窗口
	const gui_window_struct* window;
	unsigned char window_index;  //默认值
	unsigned char idle_index;
	unsigned char window_changed;  //当前主界面是否有切换
	unsigned char window_inited;//当前主界面是否有实始化
}gui_main_window_struct;



//滑动切换界面用
typedef struct
{
	const gui_window_struct* window;
	unsigned char type;     //WINDOW_SWIPE_TYPE
	unsigned char dyamic;
	unsigned char dont_pull_empty;//不拉出空界面出来

	const gui_window_struct *left;
	const gui_window_struct *right;
	const gui_window_struct *up;
	const gui_window_struct *down;
}gui_window_swipe_struct;


typedef struct
{
	GUI_WINDOW_SWITCH_TYPE type;
	const gui_window_struct* window;
}gui_window_switch_struct;


typedef struct _gui_window_history_struct gui_window_history_struct;
struct _gui_window_history_struct
{
	const gui_window_struct *window;
	unsigned char type;  				//GUI_WINDOW_TYPE
	unsigned char cache;
	unsigned char switch_mode;  		//GUI_WINDOW_SWITCH_MODE

	unsigned char has_record;
	//保存界面现场,以便于恢复
	struct
	{
		short layout_offset_x; 		//当前偏移的X坐标
		short layout_offset_y; 		//当前偏移的Y坐标
	}record;

	gui_window_history_struct *front;
	gui_window_history_struct *next;
};



#endif

