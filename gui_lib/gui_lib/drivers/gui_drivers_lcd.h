#ifndef __GUI_DRIVERS_LCD_H__
#define __GUI_DRIVERS_LCD_H__

extern unsigned char gui_drivers_lcd_wait(unsigned int count);
extern void gui_drivers_lcd_display(unsigned char* render_buf,short y_start,short y_end);

extern void gui_driver_dbg_systick(char* infoFmt);

#endif

