#ifndef __FEATURE_H__
#define __FEATURE_H__

// !!!!!!!释放正式版本时，必须要关闭debug，否则USB-IO漏电严重!!!!!!!
#define DEBUG_EN	    0

//
#define DEVELOP_VERSION  1

// !!!!!!!是否要给TP升级固件!!!!!!!
#define TP_UPDATE_CONFIG_EN    0

//当只有一个屏驱时默认选择该屏驱，不进行匹配
#define LCD_MATCH_BY_LOGO                   0 //通过屏驱logo来匹配
#define LCD_MATCH_BY_ID                     1 //通过屏幕id来匹配
#define TCFG_LCD_MATCH_MODE                 LCD_MATCH_BY_LOGO
#if (TCFG_LCD_MATCH_MODE == LCD_MATCH_BY_LOGO)
#define LCD_LOGO                            "gc9b71"
#else
#define LCD_LOGO                            "null"  //通过id匹配, 忽略logo参数
#endif

/****************屏幕尺寸***********************/
#define LCD_SIZE_WIDTH                  466
#define LCD_SIZE_HEIGHT                 466

#define LCD_SIZE_HALF_WIDTH 			(LCD_SIZE_WIDTH/2)
#define LCD_SIZE_HALF_HEIGHT 			(LCD_SIZE_HEIGHT/2)


/****************屏幕类型***********************/
#define LCD_CIRCLE 1
#define LCD_SQUARE 2
#define LCD_ROUND_CORNER 3   //圆角屏
#define LCD_SHAPE LCD_CIRCLE


/****************背光亮度**********************/
#define CUST_FULL_BACKLIGHT_LEVEL        100         // 全亮等级
#define CUST_HALF_BACKLIGHT_LEVEL        30          // 半亮等级
#define CUST_BACKLIGHT_TIMEOUT           10          // 默认亮屏时间(s)


/****************颜色***********************/
#define COLOR_RGB_MODE_565 					1  //565-16位
#define COLOR_RGB_MODE_888 					2  //888-24位
#define COLOR_RGB_MODE 					COLOR_RGB_MODE_565


/****************图片格式***********************/
#define PICTURE_ALPHA_POINT_FAST_SUPPORT 1

/****************屏幕驱动***********************/
#define LCD_USE_MULTIPLE 				0  //驱动兼容
//#define LCD_USE_GC9A01_BOE1_28IPS 		1
#define LCD_USE_7789_V2 				2
#define LCD_USE_7789_V3 				3
#define LCD_USE_DRIVER 				LCD_USE_MULTIPLE


/****************TP驱动***********************/
#define TP_USE_MULTIPLE 				0  //驱动兼容
#define TP_USE_816D 					1
#define TP_USE_716S 					2
#define TP_USE_DRIVER 				TP_USE_816D


/****************心率驱动***********************/
#define HR_USE_MULTIPLE 				0  //驱动兼容
#define HR_USE_8007 					1
#define HR_USE_LC11 					2
#define HR_USE_DRIVER 				HR_USE_8007

/****************心率24小时数据,设定每多少分钟一个数�?**********************/
#define HR_MIN_TIME                     15
#define USER_WEEK_DATA                    1    //心率 血氧、血压、睡眠记录一周的数据,每天记录一个数�?..

/****************电池驱动***********************/
#define BATTERY_USE_MULTIPLE 								0  //驱动兼容
#define BATTERY_USE_JINSANPU_481726_200MAH 					1
#define BATTERY_USE_M25_552221_100MA_30MA 					2
#define BATTERY_USE_M36_701728_140MA_30MA 					3
#define BATTERY_USE_DRIVER 								BATTERY_USE_M36_701728_140MA_30MA



/****************字节顺序***********************/
#define BYTE_ENDIAN_BIG 1
#define BYTE_ENDIAN_LITTLE 2
#define BYTE_ENDIAN BYTE_ENDIAN_LITTLE


/****************文字***********************/
#define FONT_UTF8_TO_UNICODE_SIZE 256


/****************床头钟功能***********************/
#define CHARGER_LAMP_SUPPORT 			0


/****************单按键设备***********************/
#define GUI_SINGLE_KEY_SUPPORT     1


/****************体感游戏***********************/
#define GUI_MOTION_GAME_SUPPORT     1


/****************二维码卡包***********************/
#define GUI_QR_INFO_SUPPORT     1
#define GUI_QR_OUSHU_LEN            400


//
#define BT_CALL_TEST 1
#define FACTORY_TEST_SUPPORT 1

/*******************************************/
#define GUI_SIDEBAR_SUPPORT             1
#define GUI_WIDGET_SUPPORT              1
#define GUI_SCREEN_LOCKER_SUPORT        1
#define GUI_PASSWORD_SUPPORT            1
#define GUI_LAYOUT_CELL_ZOOM_SUPPORT 	0
#define GUI_IDLE_CLOCK_SUPPORT          1

#define GUI_SURFACE_ZOOM_SUPPORT	1

#define GUI_RENDER_BUFFER_TOTAL_SUPPORT	3


#endif

