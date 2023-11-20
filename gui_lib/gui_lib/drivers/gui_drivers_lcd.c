

#include "debug_info.h"
#include "bsp_includes.h"

#include "picture.h"
#include "data_manager.h"
#include "data_manager_flash.h"

#include "gui_core.h"
#include "gui_drivers_lcd.h"
#include "gui_drivers_display.h"


extern unsigned char teRequested;
extern void lcd_swap_pinstate(void);  // LCD_test

unsigned char gui_drivers_lcd_wait(unsigned int count)
{
    //lcd_swap_pinstate();  // LCD_test

    if (teRequested == BOOL_TRUE_FLAG) {
        //SYS_DEBUG("wait: TE\n");
        oled_wait_te();
        //putchar('[');
        teRequested = BOOL_FALSE_FLAG; // 只有在刷第一块时，才需要等待te信号....
        return 0;
    }

    if (count == 0) {
        SYS_DEBUG("wait: 0\n");
        return 0;
    }

    //SYS_DEBUG("wait: %d", count);
    lcd_wait_lcd_control_transfer(count);
    return 0;
}

void gui_drivers_lcd_display(unsigned char* render_buf,short y_start,short y_end)
{
    unsigned int sz = LCD_SIZE_WIDTH * (y_end-y_start+1) * COLOR_RGB_PIXEL;
    oled_set_XY_address(0, LCD_SIZE_WIDTH-1, y_start, y_end);
    lcd_dma_single_block_start((unsigned int)render_buf, sz, (y_end == (LCD_SIZE_HEIGHT-1)));
}


