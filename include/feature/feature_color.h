#ifndef __FEATURE_COLOR_H__
#define __FEATURE_COLOR_H__

#include "feature.h"

#define COLOR_RGB_32_to_16(rgb) (((((unsigned int)(rgb)) & 0xFF) >> 3) | ((((unsigned int)(rgb)) & 0xFC00) >> 5) | ((((unsigned int)(rgb)) & 0xF80000) >> 8))
#define COLOR_RGB_16_to_32(rgb) ((0xFF << 24) | ((((unsigned int)(rgb)) & 0x1F) << 3) | ((((unsigned int)(rgb)) & 0x7E0) << 5) | ((((unsigned int)(rgb)) & 0xF800) << 8))

//565-16λɫ
#if COLOR_RGB_MODE == COLOR_RGB_MODE_565
// color: 16bit
// r: AA, 0x00, 0x1F
// g: AA, 0x07, 0xE0
// b: AA, 0xF8, 0x00
// RAM: B0: bbbb_bggg   B1: gggr_rrrr

#define COLOR_BLACK	0x0000
#define COLOR_WHITE	0xFFFF
#define COLOR_RED	(0x1F<<0)
#define COLOR_GREEN	(0x3F<<5)
#define COLOR_BLUE	(0x1F<<11)

#define COLOR_ARGB24(a,r,g,b)	((((r) & 0xF8)>>3) | ((((g) & 0xFC))<<3) | ((((b) & 0xF8)<<8)) | (((a)&0xFF)<<24))

/*****************************************颜色转换--数据完整的8位*********************************************************/
#define COLOR_RGB_R(color)  ((color & 0x001F) << 3)  	//输入[0,0xFFFF] 返回[0,248] 处理成8位
#define COLOR_RGB_G(color)  ((color & 0x07E0) >> 3)		//输入[0,0xFFFF] 返回[0,252] 处理成8位
#define COLOR_RGB_B(color)  ((color & 0xF800) >> 8)		//输入[0,0xFFFF] 返回[0,248] 处理成8位
#define COLOR_RGB(r,g,b)	((((r) & 0xF8)>>3) | ((((g) & 0xFC))<<3) | ((((b) & 0xF8)<<8))) //输入 r [0,255],g [0,255],b [0,255]  输出[0, 0xFFFF] 

/*****************************************颜色转换--数据已经丢掉了冗余位****************************************************/
#define COLOR_RGB_R_5(color) 	((color >> 0) & 0x1F)		 //输入[0,0xFFFF] 返回[0,31] 数据已经丢掉了冗余位,处理成5位
#define COLOR_RGB_G_6(color) 	((color >> 5) & 0x3F)		 //输入[0,0xFFFF] 返回[0,63] 数据已经丢掉了冗余位,处理成6位
#define COLOR_RGB_B_5(color) 	((color >> 11) & 0x1F)      //输入[0,0xFFFF] 返回[0,31] 数据已经丢掉了冗余位,处理成5位
#define COLOR_RGB_565(r,g,b) 	((((r) & 0x1F) << 0) | (((g) & 0x3F) << 5) | (((b) & 0x1F) << 11)) //输入 r [0,31],g [0,63],b [0,31]  输出[0,0xFFFF]  每一个数据都丢掉了冗余位

#define COLOR_RGB_PIXEL		(2) 	// RGB565:2 , RGB888: 3.
#define COLOR_ARGB_PIXEL	(COLOR_RGB_PIXEL+1)

typedef unsigned short GUI_COLOR;

typedef union
{
	unsigned short value;
	struct
	{
		unsigned short R:5;
		unsigned short G:6;
		unsigned short B:5;
	}rgb;
}gui_color;


//888-24λɫ
#else
// color: 24bit
// r:  AA, 0x00, 0x00, 0xFF 
// g:  AA, 0x00, 0xFF, 0x00 
// b:  AA, 0xFF, 0x00, 0x00 
// RAM: B0: bbbb_bbbb  B1: gggg_gggg  B2: rrrr_rrrr

#define COLOR_BLACK	0x000000
#define COLOR_WHITE	0xFFFFFF
#define COLOR_RED	(0xFF<<0)
#define COLOR_GREEN	(0xFF<<8)
#define COLOR_BLUE	(0xFF<<16)

#define COLOR_ARGB24(a,r,g,b)	((((r)&0xFF)<<0)|(((g)&0xFF)<<8)|(((b)&0xFF)<<16)|(((a)&0xFF)<<24))
#define COLOR_RGB(r,g,b)	((((r)&0xFF)<<0)|(((g)&0xFF)<<8)|(((b)&0xFF)<<16))
#define COLOR_RGB_R(color)  ((color >> 0) & 0x0000FF)
#define COLOR_RGB_G(color)  ((color >> 8) & 0x0000FF)
#define COLOR_RGB_B(color)  ((color >>16) & 0x0000FF)

#define COLOR_RGB_PIXEL	(3) 	// RGB565:2 , RGB888: 3.
#define COLOR_ARGB_PIXEL	(COLOR_RGB_PIXEL+1)

typedef unsigned int GUI_COLOR;

typedef union
{
	unsigned int value;
	struct
	{
		unsigned short R:8;
		unsigned short G:8;
		unsigned short B:8;
	}rgb;
}gui_color;


#endif


#define FULL_SCREEN_PIXEL	 (LCD_SIZE_WIDTH * LCD_SIZE_HEIGHT * COLOR_RGB_PIXEL)


#endif


