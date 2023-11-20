#ifndef __GUI_CORE_SURFACE_H__
#define __GUI_CORE_SURFACE_H__

#include "feature_all.h"
#include "gui_core_screen.h"
#include "gui_core_screen_control.h"
#include "gui_core_layout.h"
#include "gui_core_window.h"

/*
**本文件是根据屏幕配置生成的动态结构，可以对其进行动态修改
**surface是面，一个界面就是一个面
**box是结合，也就是控件，它负责组织里面的元素，它会对元素进行排列
**node是节点，也就是元素，它们会决定渲染的样子，它还可以包含node子节点
*/

#define GUI_SURFACE_LIST_TOTAL (2)
#define GUI_INIT_SCALE(scale) (FLOAT_EQUAL_ZERO(scale) ? 1.0f : scale)

typedef struct _gui_element_struct gui_element_struct;
struct _gui_element_struct
{
	unsigned char type; // TYPE_GUI_DRAW

	short x;
	short y;

	short gap; // 与前一项的间隔，方便滚动用

	// 用于储存数据的属性
	short value;
	void *data;

	// 用于链表的结构
	gui_element_struct *brother;
};

typedef struct _gui_node_struct gui_node_struct;
struct _gui_node_struct
{
	unsigned short id;
	unsigned char type; // TYPE_GUI_DRAW
	unsigned char flags;

	unsigned char rotate;
	unsigned char cache : 1;
	unsigned char visible : 1;
	unsigned char is_scroll : 1;

	short x;
	short y;
	short width;
	short height;

	float scale;

	short clip_x;
	short clip_y;
	short clip_width;
	short clip_height;

	// 用于储存数据的属性
	int tag;
	int value;
	void *data;
	gui_draw_struct* draw;

	// 用于链表的结构
	gui_node_struct *brother;
	gui_node_struct *child; // 主要用于节点内的组合。
};

typedef struct _gui_box_struct gui_box_struct;
struct _gui_box_struct
{
	unsigned short id;	// Taylor.Le
	unsigned char type; // TYPE_GUI_CONTROL

	unsigned char cache : 1;
	unsigned char visible : 1;
	unsigned char update : 1;
	unsigned char fix : 1;
	unsigned char will_drop : 1;

	unsigned char alpha; // 0~255
	unsigned char flags;
	char order;

	unsigned short layout_index;
	short rotate;

	// 缩放时，要求是浮点型才不会闪烁
	short x;
	short y;
	short width;
	short height;
	float scale;

	// 用于储存数据的属性
	int value;
	void *data;

	// 用于链表的结构
	gui_widget_struct *widget;
	gui_box_struct *brother;
	gui_node_struct *child;
};

typedef struct
{
	short x;
	short y;

	float scale;

	short clip_x;
	short clip_y;
	short clip_width;
	short clip_height;

	unsigned char effect_type; // see: TYPE_SWIPE_EFFECT

	char order;
	gui_box_struct *child;
	gui_screen_struct *screen;
	gui_window_struct *window;
	union
	{
		gui_layout_header_struct header;
		gui_layout_flow_struct flow;
		gui_layout_grid_struct grid;
		gui_layout_scroll_struct scroll;
		gui_layout_list_struct list;
		gui_layout_page_struct page;
		gui_layout_cellular_struct cellular;
		gui_layout_loop_struct loop;
		gui_layout_ring_struct ring;
		// 废弃 gui_layout_ring_center_struct ring_center;
		gui_layout_card_struct card;
		gui_layout_matrix_struct matrix;
	} layout;
} gui_surface_struct;

typedef struct
{
	// 自身坐标
	short x;
	short y;
	short width;
	short height;

	// 相对自身坐标的剪切区
	short clip_x;
	short clip_y;
	short clip_width;
	short clip_height;

	// 全局坐标(渲染前用)
	short left;
	short top;
	short right;
	short bottom;

	// 全局的剪切区(渲染前用)
	short clip_left;
	short clip_top;
	short clip_right;
	short clip_bottom;

	float scale;
} gui_scale_item_struct;

typedef struct
{
	gui_surface_struct *surface;
	gui_box_struct *box;
	gui_node_struct *node;
	gui_node_struct *compose;

	gui_scale_item_struct surface_scale;
	gui_scale_item_struct box_scale;
	gui_scale_item_struct node_scale;
	gui_scale_item_struct compose_scale;
} gui_scale_struct;

#endif
