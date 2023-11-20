#ifndef __GUI_DRIVERS_FLASH_H__
#define __GUI_DRIVERS_FLASH_H__

#include "gui_display_screen_part.h"

#if(GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_PART)
#define GUI_SCREEN_BUF_SIZE	(LCD_SIZE_WIDTH*GUI_SCREEN_PART_BUF_ROW*(COLOR_RGB_PIXEL+1))    //当带alpha时
#elif (GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_G2D)
#define GUI_SCREEN_BUF_SIZE	(LCD_SIZE_WIDTH*GUI_SCREEN_PART_BUF_ROW*(COLOR_RGB_PIXEL+1))
#else
#define GUI_SCREEN_BUF_SIZE	(LCD_SIZE_WIDTH*LCD_SIZE_HEIGHT*(COLOR_RGB_PIXEL+1))
#endif

extern unsigned char* gui_drivers_flash_read_image_to_buff(unsigned int addr, int len);
extern unsigned char* gui_drivers_flash_read_image_to(unsigned char* buff,unsigned int addr, int len);

#endif

