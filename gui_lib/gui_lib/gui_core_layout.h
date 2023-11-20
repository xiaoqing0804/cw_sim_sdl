#ifndef __GUI_CORE_LAYOUT_H__
#define __GUI_CORE_LAYOUT_H__

#include "feature_all.h"

#define GUI_LAYOUT_HEADER \
    short last_offset_x;  \
    short last_offset_y;  \
    short offset_x;       \
    short offset_y;       \
    short move_x;         \
    short move_y;         \
    short max_offset;     \
    short min_offset;     \
    short item_gap;       \
    short loop_flag;      \

struct _gui_box_struct;
typedef struct _gui_box_struct gui_box_struct;

typedef struct
{
    GUI_LAYOUT_HEADER;
} gui_layout_header_struct;

typedef struct
{
    GUI_LAYOUT_HEADER;
    unsigned char is_idle;
} gui_layout_watchface_struct;


typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;
    short total;		//共有多少条
    short height;
    short row_width;	//单个的宽度

    short row_height;	//单个的高度
    short row_column;	//一行有多少列

    short top;		//顶部的空缺
    short bottom;	//底部的空缺
    short left;		//左边的空缺
    short right;	//右边的空缺
    short space;  	//条与条之间的间隙

    unsigned char scroll;	//是否可以上下滚动
    unsigned char can_swipe;//列表界面也可以使用滑动切屏
} gui_layout_grid_struct;

typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;
    unsigned char scroll;//是否可以上下滚动
    unsigned char can_swipe;//列表界面也可以使用滑动切屏
    short height;
} gui_layout_flow_struct;


typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;
    unsigned char scroll;//是否可以上下滚动
    unsigned char can_swipe;//列表界面也可以使用滑动切屏
    unsigned char dynamic_height; //0 就是固定高度配置 1 就是动态高度
    unsigned char forbid_up_rebound;//禁止上方的回弹
    unsigned char forbid_down_rebound;//禁止下方的回弹
    short height;
    short top;		//顶部的空缺
    short bottom;	//底部的空缺
} gui_layout_scroll_struct;

typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;

    short total;		//共有多少条
    short height;		//高度

    short row_height;	//单条的最大高度
    short space;  	//条与条之间的间隙

    short top;		//顶部的空缺
    short bottom;	//底部的空缺

    unsigned char scroll : 1;//是否可以上下滚动
    unsigned char can_swipe : 1;//列表界面也可以使用滑动切屏
    unsigned char force_up : 1;//下方向滑动切屏
    unsigned char force_down : 1;//上方向滑动切屏
    unsigned char clip : 1;//在屏幕外的控件不加入树中

    unsigned char arc_flag : 1; //X方向的圆弧列表
    unsigned char zoom_flag : 1;    // Y方向上 是否要根据显示位置做缩放处理

    unsigned char auto_start : 1;//从屏幕下滚动上去

    short arc_radius;   // X方向 弧形列表的半径
    short zoom_radius;   // Y方向 弧形列表的半径
    float zoom_scale;   // Y方向 弧形列表的半径

	void (*dynamic_refresh)(void);

} gui_layout_list_struct;

typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;
    short total;	//共有多少页
    short curr_page;	//当前在第几页

    short page_width;
    short page_height;

    unsigned char orientation;//ORIENTATION_TYPE
    unsigned char can_swipe;//列表界面也可以使用滑动切屏
} gui_layout_page_struct;

typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;
    short width;
    short height;

    short max_diameter;		//单个的高度
    short diameter;		//单个的高度
    short min_column;	//最少的一行有多少列
    short max_column;	//最多的一行有多少列

    short margin;	//顶部的空缺
    short space;  	//条与条之间的间隙
    short default_center;

	gui_box_struct* center_box;
}gui_layout_cellular_struct;

typedef enum
{
    GUI_APPLE_CELLULAR_STEP_STATUS_BIG,   // 放大情况 --- 大模式
    GUI_APPLE_CELLULAR_STEP_STATUS_SAMLL, // 最小情况 --- 小模式
    GUI_APPLE_CELLULAR_STEP_STATUS_APP,   // 跳转APP --- 应用模式
} GUI_APPLE_CELLULAR_STEP_STATUS;

typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;

    short width;
    short height;
    short org_offset_x;
    short org_offset_y;
    short diameter; // 单个的高度
    short space;    // 条与条之间的间隙

    float scale;
    short step; // GUI_APPLE_CELLULAR_STEP_STATUS

    short min_diameter;  // 图标全部在屏幕内时的大小
    short mid_diameter;  // 图标的标准大小，中间状态
    short max_diameter;  // 图标放大状态时的大小
    short app_diameter;  // 图标进入打开App状态时的大小
    short icon_diameter; // 图片大小

    gui_box_struct *center_box;

} gui_layout_apple_cellular_struct;


typedef enum
{
    GUI_MATRIX_STEP_STATUS_BIG,   // 放大情况 --- 大模式
    GUI_MATRIX_STEP_STATUS_SAMLL, // 最小情况 --- 小模式
    GUI_MATRIX_STEP_STATUS_APP,   // 跳转APP --- 应用模式
} GUI_MATRIX_STEP_STATUS;

typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;

    short width;
    short height;
    short org_offset_x;
    short org_offset_y;
    short diameter; // 单个的高度
    short space;    // 条与条之间的间隙

    float scale;
    short step; // GUI_APPLE_CELLULAR_STEP_STATUS

    short min_diameter;  // 图标全部在屏幕内时的大小
    short mid_diameter;  // 图标的标准大小，中间状态
    short max_diameter;  // 图标放大状态时的大小
    short app_diameter;  // 图标进入打开App状态时的大小
    short icon_diameter; // 图片大小

    gui_box_struct *center_box;
    
} gui_layout_matrix_struct;

typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;
    short column;
    short total;		//共有多少条
    short height;		//高度
    short row_height;	//单条的高度

    unsigned char scroll;//是否可以上下滚动
    unsigned char can_swipe;//列表界面也可以使用滑动切屏
    unsigned char force_up;//下方向滑动切屏
    unsigned char force_down;//上方向滑动切屏

    unsigned char zoom_flag;    // 是否要根据显示位置做缩放处理
    unsigned char arc_flag;
    short         arc_radius;
    unsigned char palace_grid;
    

    // 自定义游标、Y轴位置 和 缩放参数表....
    unsigned int map_size;
    float *cursor_map;
    float *x_pos_map;
    float *y_pos_map;
    float *y_pos_map2;
    float *scale_map;
} gui_layout_loop_struct;

////////////////////////////////////////////////////////////////////////////////
#if 0   // 废弃
typedef struct
{
    short x;
    short y;
    short angle;
    short zoom;
} gui_ring_position_struct;

typedef struct
{
    short x;
    short y;
    short angle;
    short zoom;
} gui_ring_center_position_struct;

typedef struct
{
    short x;
    float zoom;
} gui_ring_zoom_config_struct;
#endif

typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;

    /*
     *           90
     *           |
     *           |
     * 180 ------+------- 0
     *           |
     *           |
     *          270
     */
    // mBaseAng
    short    mBaseAng;  // 焦点项所对应的角度 ...
    short    mId;       // 当前焦点的box-id
    short    mIndex;    // 当前焦点的序号
    short    mCount;
    short    mPenDn;    // Pen down handle flag.
    short    mZoom;     // zoom flag, 图标是否要进行缩放

    float    mRadius;       // 组件半径，包括了旋转环在内 ...
    float    mAngGap;       // 360 / count
    float    mAngVal;       // current-ang
    float    mSith;

    float    c_x;       // 圆心 x 坐标 ...
    float    c_y;       // 圆心 y 坐标 ...

    // for zoom
    float    c_bias_x;  // 偏置圆心 x 坐标....
    float    c_bias_h;

    float*   cfg_zoom_map;
    float*   cfg_pos_map;
    short    cfg_map_size;
    short    mov_speed;

    unsigned char auto_start;
} gui_layout_ring_struct;

#if 0   // 废弃
typedef struct
{
    /*-----自动计算-------*/
    GUI_LAYOUT_HEADER;
    short index;	//当前在第几个
    short id;

    short diameter;	//单个的高度
    short touch_x;				//当前偏移的x坐标
    short touch_y;				//当前偏移的Y坐标
    short touch_width;
    short touch_height;

    const gui_ring_center_position_struct* postion_list;
    short postion_list_num;
    short step_angle;

} gui_layout_ring_center_struct;
#endif

///////////////////////////////////////////////////////////////////////////////
typedef struct
{
	GUI_LAYOUT_HEADER;
    short index;
    short id;

    //short item_gap;
    unsigned short total;
    unsigned short curr_index;      // current item index
    unsigned short curr_top_index;

    // y = func(dx) = a*dx*dx + b*dx
    float param_a;
    float param_b;

    // card 背景图片信息
    unsigned short bg_img_w;
    unsigned short bg_img_h;
}gui_layout_card_struct;


#endif

