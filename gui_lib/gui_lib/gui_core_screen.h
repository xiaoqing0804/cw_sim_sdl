#ifndef __GUI_CORE_SCREEN_H__
#define __GUI_CORE_SCREEN_H__

#include "feature_all.h"
#include "gui_core_layout.h"

/*
**本文件是屏幕配置的静态结构
**screen是屏幕，也是排版，一个界面就是一个面
**widget是控件，它是一个控件数组，决定了屏幕内有多少控件
* gui_font_struct;
* gui_image_struct
* gui_pointer_struct;
* gui_canvas_struct;
**这些是基本元素，配置渲染的图形等
*/


/***********************************定义*******************************************/

#define NUMBER_IMAGE_LIST_CUSTOM   8

#define GUI_DRAW_HEADER \
	unsigned char type; /*TYPE_GUI_DRAW*/ \
	unsigned char id; \
	unsigned char align; /*GUI_ALIGN_MERGE*/ \
	unsigned char auto_wrap;                 \
	short anchor_x; /*锚点 - 使用宏 ANCHOR_VALUE */ \
	short anchor_y;	/*锚点 - 使用宏 ANCHOR_VALUE */ \
	float scale;

typedef enum
{
	GUI_FONT_VALUE_TYPE_STRING,     //文本
	GUI_FONT_VALUE_TYPE_STRING_ID,	//ID
	GUI_FONT_VALUE_TYPE_NUMBER,		//数字
}GUI_FONT_VALUE_TYPE;

typedef struct
{
	GUI_DRAW_HEADER; 	// TYPE_GUI_DRAW
}gui_draw_struct;

typedef struct
{
    short x;
    short y;
}gui_point_struct;  // see gdi_point.

//图片映射
typedef struct
{
	const picture_info_struct* number[10]; //0~9
	const picture_info_struct* dot;		//'.'     符号：点
	const picture_info_struct* colon; 	//':'    符号：冒号
	const picture_info_struct* dash; 	//'-'    符号：破折号
	const picture_info_struct* slash; 	//'/'    符号：斜杠
	const picture_info_struct* percent; //'%'    符号：百分号
	unsigned char custom_char[NUMBER_IMAGE_LIST_CUSTOM];
	const picture_info_struct* custom_picture[NUMBER_IMAGE_LIST_CUSTOM];
}gui_number_image_list_struct;


/***********************************基本元素*******************************************/
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_PICTURE
	
    const picture_info_struct* left_top;
    const picture_info_struct* top;
    const picture_info_struct* right_top;

    const picture_info_struct* left;
    const picture_info_struct* mid;
    const picture_info_struct* right;

    const picture_info_struct* left_bot;
    const picture_info_struct* bot;
    const picture_info_struct* right_bot;

    GUI_COLOR fill_color;
}gui_image_9slice_struct;


//图片
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_PICTURE
	short x;
	short y;
	short rotate;
	const void *data; // picture_info_struct
} gui_image_struct;

//文字
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_TEXT
	short x;
	short y;
	short max_width; //已废弃
	short width;
	short height;
	short rotate;
	short space_y;	//纵向间隔
	char auto_size;	//自适应变化大小
	char scroll;	//是否滚动

    unsigned char size;          // font size: SYS_FONT_SMALL, SYS_FONT_MEDIUM, SYS_FONT_LARGE .... 
    unsigned char name;          // font name: new-song ...
	GUI_COLOR color;
	GUI_FONT_VALUE_TYPE value_type;  //GUI_FONT_VALUE_TYPE_STRING  0,string   1,string_id   2,number  	
	unsigned char value_align;		/*GUI_ALIGN_MERGE*/
	union 
	{
		const void *string;
		int string_id;
		int number;
	}value;
}gui_font_struct;

//二维码
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_TEXT
	short rotate;
	short width;
	const void *string;
}gui_qr_code_struct;

//条形码
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_TEXT
	short rotate;
	const void *string;
}gui_bar_code_struct;

//指针
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW
    unsigned short value;      // [0 ~ 60) or [0 ~ 3600)
	short center_x;           // 中心点
	short center_y;           // 中心点
	short hand_lenth;   // 指针长度
	short hilt_lenth;   // 指针尾巴长度
	short hand_width;
    union
    {
        struct {
            GUI_COLOR  color;
            short*     position;     // 此处保存计算出的画线起止点坐标，必须要指向 ram 空间 .
        }line;

        const void *pics[16+1];   // 8pics | 16pics, 20230921 Taylor.Le, +1, 增加一张附加图片，缩放时一律显示最后一张图片
    }shape;
}gui_pointer_struct;

//画布
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW
    unsigned char AA;       // antialiasing
    unsigned char penSize;
    unsigned char penShape; // GUI_PS_ROUND
    unsigned char opacity;  // 
    GUI_COLOR     penColor;
    GUI_COLOR     fillColor;
    
    union
    {
        struct {
            short x;
            short y;
        }point;
        
        struct {
            short x0;       // start point : x
            short y0;       // start point : y
            short x1;       // end point : x
            short y1;       // end point : y
            short showPixel;// for style line
            short skipPixel;// for style line
        }line;

        struct {
            short x0;       // left-top point : x
            short y0;       // left-top point : y
            short x1;       // right-bottom point : x
            short y1;       // right-bottom point : y
        }rect;

        struct {
            short cx;       // center of circle : x
            short cy;       // center of circle : y
            short r;        // radius
        }circle;

        struct {
            short cx;       // center of circle : y
            short cy;       // center of circle : x
            short r;        // radius
            short Angle0;   // start angle
            short Angle1;   // end   angle
        }arc;

        struct {
            short bx;       // base x
            short by;       // base y
            gui_point_struct* points;   // polygon's point array
            short point_num;            // array size
        }polygon;
    }canvas;
}gui_canvas_struct;



/***********************************组合元素*******************************************/

//混合元素
typedef struct
{
	const void *data;
}gui_mix_struct;

//数字图片
typedef struct
{
	GUI_DRAW_HEADER; // TYPE_GUI_DRAW_PICTURE
	short x;
	short y;
	const gui_number_image_list_struct* number_image_list;
    unsigned char number_digits;    // Taylor.Le, +
	unsigned char value_type;  //GUI_FONT_VALUE_TYPE_STRING  0,string   1,string_id   2,number  
	union 
	{
		const void *string;
		int string_id;
		int number;
	}value;

}gui_image_number_struct;

//图片进度条
typedef struct
{
	unsigned char progress;
	const gui_image_struct* bg;
	unsigned short child_num;
    const void *children;
}gui_image_progress_struct;


//图片进度条
typedef struct
{
	unsigned char progress;
	const gui_image_struct* bg;
	const gui_image_struct* bar;
	unsigned char orientation;//ORIENTATION_TYPE
}gui_progress_bar_struct;


/***********************************基础组织结构---控件*******************************************/

typedef struct
{
	/*type 决定了用那个控件来解析 children*/
	unsigned char type;     	// TYPE_GUI_CONTROL

	unsigned short id;
	char order;
	
	short x;
	short y;
	
	short width;
	short height;
	
	short rotate;
	unsigned char visible;
	
	unsigned char fix; //定住不动
	unsigned char clip;
	unsigned char align;		//在屏幕中的对齐  /*GUI_ALIGN_MERGE*/
	unsigned char alpha;
	
	short space_x;				//横向间隔
	short space_y;				//纵向间隔
	
	short anchor_x; //锚点 - 使用宏 ANCHOR_VALUE
	short anchor_y;	//锚点 - 使用宏 ANCHOR_VALUE
	
	unsigned short child_num;
	float scale;

	/*
	* gui_font_struct;
	* gui_image_struct
	* gui_pointer_struct;
	* gui_canvas_struct;
	*/
    const void *children;

}gui_widget_struct;


typedef struct
{
	unsigned char type;  		//TYPE_GUI_LAYOUT  排版方式
	unsigned char order;
	short space_x;				//横向间隔
	short space_y;				//纵向间隔
	short child_num;
	const gui_widget_struct *children;

	/*
	* gui_layout_grid_struct;
	* gui_layout_scroll_struct;
	* gui_layout_list_struct;
	* gui_layout_page_struct;
	* gui_layout_cellular_struct
	* gui_layout_ring_struct
	* gui_layout_watchface_struct
	*/
	const void* layout_config; //排版的配置表
}gui_screen_struct;

#endif

