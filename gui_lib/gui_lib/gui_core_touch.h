#ifndef __GUI_CORE_TOUCH_H__
#define __GUI_CORE_TOUCH_H__

#include <stdint.h>
#include "feature_all.h"

#define FULL_SCREEN_TOUCH_FLAG         			(0xFFFF)
#ifndef IS_FULL_SCREEN_TOUCH
#define IS_FULL_SCREEN_TOUCH(touch_event)       (touch_event->id == 0xFFFF)
#endif

#define GUI_TOUCH_SPEED_TOTAL         			(3)

typedef enum
{
	GUI_GESTURE_TYPE_NONE,
	GUI_GESTURE_TYPE_SWIPE,
	GUI_GESTURE_TYPE_BACK,
}GUI_GESTURE_TYPE;

typedef enum
{
	TOUCH_EVENT_TYPE_NONE = 0,
	TOUCH_EVENT_TYPE_DOWN,
	TOUCH_EVENT_TYPE_MOVE,
	TOUCH_EVENT_TYPE_UP,
	TOUCH_EVENT_TYPE_CANCLE,
	TOUCH_EVENT_TYPE_LONGPRESS,  // Taylor.Le, +
}TOUCH_EVENT_TYPE;

typedef enum
{
	TOUCH_CLICK_TYPE_NONE = 0,
	TOUCH_CLICK_TYPE_CLICK,
	TOUCH_CLICK_TYPE_DOUBLE_CLICK,
	TOUCH_CLICK_TYPE_LONG_PRESS,
}TOUCH_CLICK_TYPE;

typedef enum
{
	TOUCH_TYPE_NONE = 0,
	TOUCH_TYPE_TOUCH,
	TOUCH_TYPE_CLICK,
	TOUCH_TYPE_LAYOUT,
	TOUCH_TYPE_LAYOUT_ITEM,
	TOUCH_TYPE_LAYOUT_FORBID,
}TOUCH_TYPE;

typedef struct
{
	short x;
	short y;
	
	short down_x;
	short down_y;

	short swipe_x;
	short swipe_y;
	short swipe_start_x;
	short swipe_start_y;

	short last_x;
	short last_y;

	int speed_x;
	int speed_y;
	
	uint32_t down_time;
	uint32_t last_time;
	uint32_t time;
	uint32_t time_ms;

	short record_x[GUI_TOUCH_SPEED_TOTAL];
	short record_y[GUI_TOUCH_SPEED_TOTAL];
	uint32_t record_time[GUI_TOUCH_SPEED_TOTAL];
	short record_index;

	char gesture_orientation; 	//0空，1横向 2纵向  ORIENTATION_TYPE
	char last_direction;		//DIRECTION_TYPE
	char curr_direction;		//DIRECTION_TYPE
	char direction;      		//DIRECTION_TYPE
	
}gui_touch_point_struct;

typedef struct
{
	unsigned char type;			//TOUCH_EVENT_TYPE.
	unsigned char direction;    //DIRECTION_TYPE
	unsigned short id;//控件ID. // Taylor.Le
	short x;
	short y;
	short down_x;
	short down_y;
	short speed_x;
	short speed_y;
}gui_touch_struct;

typedef struct
{
	unsigned char type;	//TOUCH_CLICK_TYPE.
	unsigned short id;//控件ID.     // Taylor.Le
	short x;
	short y;
}gui_click_struct;

typedef struct
{
	unsigned short id;//控件ID. // Taylor.Le
	short index;	//点击第几个
	short x_in_item;
	short y_in_item;
	short x;
	short y;
}gui_click_layout_struct;


typedef union
{
    struct
    {
    	short progress;//0-100
		short index;
		short total;
    }page; 
	struct
    {
    	short progress;//0-100
    }list; 
	struct
    {
		short index;
		short id;
    }ring; 
    struct
    {
		short progress;//0-100
		short x;
		short y;
    }scroll; 
	struct
    {
		short progress;//0-100
		short x;
		short y;
    }flow;
	struct
	{
		short index;
		short id;
    }ring_center; 
    struct
    {
        short index;
        short id;
    }card;
}gui_layout_value_struct;

typedef struct
{
	unsigned short id;	//控件ID.       // Taylor.Le
	unsigned char offset_left;
	unsigned char offset_top;
	unsigned char offset_right;
	unsigned char offset_bottom;
	void (*click)(gui_click_struct *event);
	void (*long_touch)(gui_click_struct *event);
	unsigned char (*touch)(gui_touch_struct *event);
}gui_touch_event_struct;


#endif

