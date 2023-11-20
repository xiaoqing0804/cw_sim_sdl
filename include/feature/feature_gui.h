#ifndef __FEATURE_GUI_H__
#define __FEATURE_GUI_H__

#include "feature.h"
#include "feature_define.h"

/****************屏幕刷新***********************/
#define GUI_DISPLAY_SCREEN_PART					1    				//一屏需要刷新多次
#define GUI_DISPLAY_SCREEN_WHOLE				2					//整屏刷新
#define GUI_DISPLAY_SCREEN_G2D				    3					//整屏刷新
#if defined(__CW_JL_G2D_IMB__)||defined(__CW_JL_G2D_IMB_EXT__)
#define GUI_DISPLAY_SCREEN						GUI_DISPLAY_SCREEN_G2D
#elif defined(__CW_JL_PSRAM__)
#define GUI_DISPLAY_SCREEN						GUI_DISPLAY_SCREEN_WHOLE
#else
#define GUI_DISPLAY_SCREEN						GUI_DISPLAY_SCREEN_PART
#endif

#if defined(__CW_JL_G2D_IMB_EXT__)
#define GUI_SCREEN_PART_BUF_ROW					64
#elif defined( __CW_JL_VLT_MEM__)
#define GUI_SCREEN_PART_BUF_ROW					24   //8   // 9
#else
#define GUI_SCREEN_PART_BUF_ROW					8   //8   // 9
#endif
#define GUI_DISPLAY_RENDERING_TIME_INTERVAL     20  // 33      //每帧需要的时间: ms


/****************节点缓存***********************/
#define GUI_CACHE_BOX_TOTAL 				128
#define GUI_CACHE_NODE_TOTAL 				1024    // 512

#define GUI_CACHE_RENDER_TOTAL 				(256+128)
#define GUI_CACHE_WINDOW_HISTORY_TOTAL 		64


/****************触摸***********************/

#define TOUCH_MOVE_START_MIN 			2   	//最少要移动多少才算是移动
#if defined(__CW_JL_M31__)||defined(__CW_JL_M36__)||defined(__CW_JL_GW69T__)
#define TOUCH_GESTURE_START_MAX 		180   	//重新判断时，超过多少，就不算是手势移动
#elif defined(__CW_JL_M28__)
#define TOUCH_GESTURE_START_MAX 		180   	//重新判断时，超过多少，就不算是手势移动
#else
#define TOUCH_GESTURE_START_MAX 		180   	//重新判断时，超过多少，就不算是手势移动
#endif

#define TOUCH_AUTO_MOVE_TARGET_MIN 		6   	//自动移动到离目标距离多少内算是到达
#define TOUCH_AUTO_MOVE_GAP_MS 			15   	//自动移动间隔时间
#define TOUCH_AUTO_MOVE_MIN_SPEED 		(500)
#define TOUCH_AUTO_MOVE_NORMAL_SPEED 	(1000)
#define TOUCH_AUTO_MOVE_MAX_SPEED 		(2500)

#define TOUCH_EMPTY_PULL_SLOW_SPEED 	3   	//列表拉空时，速度降低的系数

#define TOUCH_SWITCH_X_MIN 				(LCD_SIZE_WIDTH/4)   //在X方向上，到达该数值，就可以进行切换
#define TOUCH_SWITCH_Y_MIN 				(LCD_SIZE_HEIGHT/4)   //在Y方向上，到达该数值，就可以进行切换
#define TOUCH_SWITCH_X_SPEED_MIN		(240)
#define TOUCH_SWITCH_Y_SPEED_MIN		(240)

#define TOUCH_LONGPRESS_TIMEOUT         (1000)   	   //长按的时长  1S  // Taylor.Le, +

#define TOUCH_REBOUND_MAX_OVER 			(40)  		//惯性移动时，最大超过多少就回弹
#define TOUCH_REBOUND_END_LEN 			(LCD_SIZE_WIDTH*0.1f)  		//滚动条移动时的，惯性长度
#define TOUCH_REBOUND_MAX_TIME 			(300)		//自动移动时的最大时间
#define TOUCH_REBOUND_MIN_TIME 			(150)		//自动移动时的最大时间

//当缩放发生后，特别是全屏缩放这类，如果这时候计算时还是原始坐标/大小，那么就需要用这个把坐标/大小放到缩放系统中去
#define GUI_VALUE_ORGIN_TO_SCALE(object, value) ((value) * (object)->scale)

//当缩放发生后，特别是全屏缩放这类，如果这时候计算，需要知道原始坐标/大小的位置时，那么就需要用这个把坐标/大小放到原始系统中去
#define GUI_VALUE_SCALE_TO_ORGIN(object, value) ((value) / (object)->scale)


/****************蜂窝界面UI的参数***********************/
#define APPLE_CELLULAR_MIN_COL_TOTAL (4)
#define APPLE_CELLULAR_MAX_COL_TOTAL (7)

#define APPLE_CELLULAR_DISTANCE_Y_DOWN_UP_SCALE (0.002f)	   // 从中心向上下边缘偏时的X上产生衰减系数，当它增大，会导致图标行间距减小。
#define APPLE_CELLULAR_DISTANCE_X_CENTER_SCALE (0.3795f)	   // 同一行内，图标在中心时的衰减系数，越大，中心处间隔就越大
#define APPLE_CELLULAR_DISTANCE_X_LEFT_RIGHT_SCALE (0.000653f) // 同一行内，从中心向左右边缘的衰减系数，越大，间距减小。

#define APPLE_CELLULAR_DISTANCE_Y_CENTER_SCALE (0.54f)		// 在Y轴上，图标在中心时的衰减系数，越大，中心处间隔就越大
#define APPLE_CELLULAR_DISTANCE_Y_LEFT_RIGHT_SCALE (0.002f) //  在Y轴上，从中心向左右边缘的衰减系数，越大，间距减小。

#define APPLE_CELLULAR_DISTANCE_DISTANCER_SCALE (0.2f) //  在XY轴上，图标半径从中心向边缘的衰减系数。

//如果是圆角屏
#if LCD_SHAPE == LCD_ROUND_CORNER
#define APPLE_CELLULAR_ROUND_CORNER_ANGLE (90)
#endif

#define APPLE_CELLULAR_ROW_TOTAL ((APPLE_CELLULAR_MAX_COL_TOTAL - APPLE_CELLULAR_MIN_COL_TOTAL) * 2 + 1)
#define APPLE_CELLULAR_COL_TOTAL (APPLE_CELLULAR_MAX_COL_TOTAL)

#define APPLE_CELLULAR_NET_ROW_TOTAL (APPLE_CELLULAR_ROW_TOTAL)             // 网格的高度
#define APPLE_CELLULAR_NET_COL_TOTAL (APPLE_CELLULAR_MAX_COL_TOTAL * 2 - 1) // 网格的宽度
#define APPLE_CELLULAR_NET_FRIST_COL_TOTAL (APPLE_CELLULAR_MIN_COL_TOTAL * 2 - 1)
#define APPLE_CELLULAR_NET_FRIST_NODE ((APPLE_CELLULAR_NET_COL_TOTAL - APPLE_CELLULAR_NET_FRIST_COL_TOTAL)/2)
#define APPLE_CELLULAR_NET_STEP (2)

/****************矩阵界面UI的参数***********************/

#define MATRIX_ROW_TOTAL (7)
#define MATRIX_COL_TOTAL (5)

#define MATRIX_NET_ROW_TOTAL (MATRIX_ROW_TOTAL)             // 网格的高度
#define MATRIX_NET_COL_TOTAL (MATRIX_COL_TOTAL) // 网格的宽度



//通用状态栏
#define GUI_STATUS_BAR_HEIGHT        (99)
#define GUI_TITLE_BAR_HEIGHT         (99)
#define GUI_TITLE_BAR_LEFT         (100)
#define GUI_TITLE_BAR_WIDTH         (LCD_SIZE_WIDTH - GUI_TITLE_BAR_LEFT*2)

//通用内容
#define GUI_CONTENT_GAP_LEFT          (22)
#define GUI_CONTENT_GAP_RIGHT         (22)
#define GUI_CONTENT_GAP_TOP           (GUI_TITLE_BAR_HEIGHT + 1)
#define GUI_CONTENT_GAP_BOTTOM        (100)
#define GUI_CONTENT_WIDTH             (LCD_SIZE_WIDTH - GUI_CONTENT_GAP_LEFT -GUI_CONTENT_GAP_RIGHT)

//通用条目
#define GUI_ITEM_GAP_LEFT          (22)
#define GUI_ITEM_GAP_RIGHT         (22)
#define GUI_ITEM_SPACE             (14)
#define GUI_ITEM_WIDTH             (GUI_CONTENT_WIDTH - GUI_ITEM_GAP_LEFT - GUI_ITEM_GAP_RIGHT)
#define GUI_ITEM_HEIGHT            (106)
#define GUI_ITEM_HEIGHT_WITH_INFO  (120)  //显示更多信息时，特别是两行信息。
#define GUI_ITEM_HEIGHT_3          (256)  //三行信息。

//一行有前后两条信息。前面是标题，后面是值
#define GUI_ITEM_TITLE_AND_VALUE_FRIST_WIDTH  (240)
#define GUI_ITEM_TITLE_AND_VALUE_SECOND_WIDTH (GUI_ITEM_WIDTH - 240)


//一行中，标题有图标和文字时，前面是标题，后面是文字
#define GUI_ITEM_PIC_AND_TXT_FRIST_WIDTH  (22)
#define GUI_ITEM_PIC_AND_TXT_SECOND_WIDTH (103)

//一行中，有标题 和 解释文字，这两个文字分上下两行
#define GUI_ITEM_TWO_LINE_TXT_UP_HEIGHT    (70)
#define GUI_ITEM_TWO_LINE_TXT_DOWN_HEIGHT  (GUI_ITEM_HEIGHT - GUI_ITEM_TWO_LINE_TXT_UP_HEIGHT)


#define LCD_SCALE_WIDTH  (1.0f)
#define LCD_SCALE_HEIGHT (1.0f)

#endif
