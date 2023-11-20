

/***************************************************************************************/
//      date            auth            note
//--------------------------------------------------------------------------------------
//   2022-11-28       Taylor.Le         支持屏幕剪切区
//
/***************************************************************************************/

#include <math.h>

#include "picture.h"
#include "debug_info.h"

#include "gui_drivers_flash.h"
#include "gui_display_draw_lib.h"

#undef SHARE_CACHE_RAM_FUNCTION
#define SHARE_CACHE_RAM_FUNCTION    

#pragma push
#pragma Otime
typedef void (*point_map_func)(int cx, int cy, int* x, int* y);
SHARE_CACHE_RAM_FUNCTION static void ui_point8_map_0(int cx, int cy, int* x, int* y)
{
}
SHARE_CACHE_RAM_FUNCTION static void ui_point8_map_1(int cx, int cy, int* x, int* y)
{
    int tx = *x - cx;
    int ty = cy - *y;
    *x = cx + ty;
    *y = cy - tx;
}
SHARE_CACHE_RAM_FUNCTION static void ui_point8_map_2(int cx, int cy, int* x, int* y)
{
    int tx = *x - cx;
    int ty = cy - *y;
    *x = cx + ty;
    *y = cy + tx;
}
SHARE_CACHE_RAM_FUNCTION static void ui_point8_map_3(int cx, int cy, int* x, int* y)
{
    int ty = cy - *y;
    *y = cy + ty;
}
SHARE_CACHE_RAM_FUNCTION static void ui_point8_map_4(int cx, int cy, int* x, int* y)
{
    int tx = *x - cx;
    int ty = cy - *y;
    *x = cx - tx;    
    *y = cy + ty;
}
SHARE_CACHE_RAM_FUNCTION static void ui_point8_map_5(int cx, int cy, int* x, int* y)
{
    int tx = *x - cx;
    int ty = cy - *y;
    *x = cx - ty;
    *y = cy + tx;
}
SHARE_CACHE_RAM_FUNCTION static void ui_point8_map_6(int cx, int cy, int* x, int* y)
{
    int tx = *x - cx;
    int ty = cy - *y;
    *x = cx - ty;
    *y = cy - tx;
}
SHARE_CACHE_RAM_FUNCTION static void ui_point8_map_7(int cx, int cy, int* x, int* y)
{
    int tx = *x - cx;
    *x = cx - tx;
}
static point_map_func c_pointer8_map[] = 
{
    ui_point8_map_0, ui_point8_map_1, ui_point8_map_2, ui_point8_map_3,
    ui_point8_map_4, ui_point8_map_5, ui_point8_map_6, ui_point8_map_7
};
static unsigned char c_pointer8_area[] = 
{
    0, 0, 0, 0,  0, 0, 0, 0,        // [0 ~ 7]
    1, 1, 1, 1,  1, 1, 1, 1,        // [8 ~ 15]
    2, 2, 2, 2,  2, 2, 2,           // [16 ~ 22]
    3, 3, 3, 3,  3, 3, 3, 3,        // [23 ~ 30]
    4, 4, 4, 4,  4, 4, 4,           // [31 ~ 37]
    5, 5, 5, 5,  5, 5, 5,           // [38 ~ 44]
    6, 6, 6, 6,  6, 6, 6, 6,        // [45 ~ 52]
    7, 7, 7, 7,  7, 7, 7, 0         // [53 ~ 59]
};
static unsigned char c_pointer8_table[60] = {
	0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1,
	0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1,
	0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1,
	0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1,
};

static int g_pointer_draw_x_pos;

SHARE_CACHE_RAM_FUNCTION int gui_draw_pointer_check(unsigned char area, int x, int y)
{
    int ret = 0;
    switch(area) {
        case 0:
        case 7:
            if (y > gui_lib_ctx->y1) {
                ret = 1;
            }
            break;

        case 3:
        case 4:
            if (y < gui_lib_ctx->y0) {
                ret = 1;
            }
            break;

        case 1:
        case 2:
            if (g_pointer_draw_x_pos != -1 && x < (g_pointer_draw_x_pos-1)) {
                ret = 1;
            }
            break;

        case 6:
        case 5:
            if (g_pointer_draw_x_pos != -1 && x > (g_pointer_draw_x_pos+1)) {
                ret = 1;
            }
            break;
    }
    return ret;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// x, y, w, h  - 绘图区域(原点为中心点)
// cx, cy      - 图片中心点(旋转锚点)
SHARE_CACHE_RAM_FUNCTION void GUI_DrawPointer8(picture_info_struct* pics[], int x, int y, int w, int h, int cx, int cy, short value)
{
    picture_info_struct* p_bitmap = pics[c_pointer8_table[value]];
    point_map_func map_func = NULL;
    unsigned int pic_addr, pixel_count;
    unsigned int data_sz, read_sz;
    unsigned int alpha;
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
	unsigned int r,g,b, r_b,g_b,b_b;
    GUI_COLOR pic_color, bg_color;
#endif
    unsigned int buf_offset, area;
    unsigned char* pic_data;
    int x0, y0;

    if (p_bitmap->alpha != 4) {
        // not .pAA format.
        return;
    }

    g_pointer_draw_x_pos = -1;
    area = c_pointer8_area[value];
    map_func = c_pointer8_map[area];

    if (p_bitmap->width > 0x200) {      // 512
        #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
        read_sz = ((GUI_SCREEN_BUF_SIZE)/5)*5;
        #else
        read_sz = ((GUI_SCREEN_BUF_SIZE)/6)*6;
        #endif
        
        pic_addr = (unsigned int)p_bitmap->addr;
        data_sz = p_bitmap->height; // iw * ih * 5;
        
        // pixel array: 
        //  x: 1B; y: 1B; alpha: 1B; pixel: 2B
        while(data_sz != 0) {
            if (data_sz < read_sz) {
                read_sz = data_sz;
            }
            pic_data = gui_drivers_flash_read_image_to_buff(pic_addr, read_sz);
            pic_addr += read_sz;
            data_sz -= read_sz;
        #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
            pixel_count = read_sz / 5;
        #else
            pixel_count = read_sz / 6;
        #endif
            
            while(pixel_count) {
                pixel_count --;
                
                // map x,y
                x0 = pic_data[0];
                y0 = pic_data[1];
                map_func(cx, cy, &x0, &y0);
                x0 += x;
                y0 += y;
                //if ((x0 < 0) || (x0 >= LCD_SIZE_WIDTH) || (y0 < gui_lib_ctx->y0) || (y0 > gui_lib_ctx->y1)) {
                if ((y0 < gui_lib_ctx->y0) || (y0 > gui_lib_ctx->y1) || (x0 < gui_lib_ctx->x0) || (x0 > gui_lib_ctx->x1)) {
                    #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
                    pic_data += 5;
                    #else
                    pic_data += 6;
                    #endif

                    if (gui_draw_pointer_check(area, x0, y0)) {
                        return;
                    }
                    continue;
                }
                g_pointer_draw_x_pos = x0;
                
                // get pixel
                alpha = pic_data[2];
                
                // get bg
                buf_offset = UI_CHARGE_XY(x0, y0);  //((y0-gui_lib_ctx->y0)*LCD_SIZE_WIDTH + x0)*COLOR_RGB_PIXEL;
            #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
                if (alpha == 0xFF) {
                    gui_lib_ctx->frame_buffer[buf_offset] = pic_data[3];
                    gui_lib_ctx->frame_buffer[buf_offset+1] = pic_data[4];
                }
                else if (alpha != 0) {
                    bg_color = (gui_lib_ctx->frame_buffer[buf_offset] << 8)+gui_lib_ctx->frame_buffer[buf_offset+1];
                    r_b = (bg_color >> 0)&0x1F;
                    g_b = (bg_color >> 5)&0x3F;
                    b_b = (bg_color >> 11)&0x1F;

                    pic_color = (pic_data[3]<<8) + pic_data[4];
                    r = (pic_color >> 0)&0x1F;
                    g = (pic_color >> 5)&0x3F;
                    b = (pic_color >> 11)&0x1F;
                    r = (r*alpha + r_b*(0xFF-alpha))/0xFF;
                    g = (g*alpha + g_b*(0xFF-alpha))/0xFF;
                    b = (b*alpha + b_b*(0xFF-alpha))/0xFF;
                    if(r > 0x1F)r=0x1F;
                    if(g > 0x3F)g=0x3F;
                    if(b > 0x1F)b=0x1F;
                    pic_color = (r << 0)+(g << 5)+(b << 11);
                    
                    gui_lib_ctx->frame_buffer[buf_offset] = (pic_color >> 8)&0xFF;
                    gui_lib_ctx->frame_buffer[buf_offset+1] = pic_color & 0xFF;
                }
                pic_data += 5;
                
            #else
                if (alpha == 0xFF) {
                    gui_lib_ctx->frame_buffer[buf_offset] = pic_data[3];       // b
                    gui_lib_ctx->frame_buffer[buf_offset+1] = pic_data[4];     // g
                    gui_lib_ctx->frame_buffer[buf_offset+2] = pic_data[5];     // r
                }
                else if (alpha != 0) {
                    gui_lib_ctx->frame_buffer[buf_offset+0] = (pic_data[3]*alpha + gui_lib_ctx->frame_buffer[buf_offset+0]*(0xFF-alpha))/0xFF;    // b
                    gui_lib_ctx->frame_buffer[buf_offset+1] = (pic_data[4]*alpha + gui_lib_ctx->frame_buffer[buf_offset+1]*(0xFF-alpha))/0xFF;    // g
                    gui_lib_ctx->frame_buffer[buf_offset+2] = (pic_data[5]*alpha + gui_lib_ctx->frame_buffer[buf_offset+2]*(0xFF-alpha))/0xFF;    // r
                }
                pic_data += 6;
            #endif
            }
        }
    }
    else {
        #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
        read_sz = ((GUI_SCREEN_BUF_SIZE)/7)*7;
        #else
        read_sz = ((GUI_SCREEN_BUF_SIZE)/8)*8;
        #endif
        
        pic_addr  = (unsigned int)p_bitmap->addr;     // data_size: 4B + pixel-array[]
        pic_data  = gui_drivers_flash_read_image_to_buff(pic_addr, read_sz+4);   // read data size.
        pic_addr += (read_sz+4);
        data_sz   =   *((unsigned int*)pic_data); // iw * ih * 7;
        if (data_sz < read_sz) {
            read_sz = data_sz;
        }
        pic_data += 4;
        
        // pixel array: 
        //  x: 2B; y: 2B; alpha: 1B; pixel: 2B
        while(data_sz != 0) {
            #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
            pixel_count = read_sz / 7;
            #else
            pixel_count = read_sz / 8;
            #endif
            
            while(pixel_count) {
                pixel_count --;
                
                // map x,y
                x0 = pic_data[0] + (pic_data[1]<<8);
                y0 = pic_data[2] + (pic_data[3]<<8);
                map_func(cx, cy, &x0, &y0);
                x0 += x;
                y0 += y;
                //if ((y0 < gui_lib_ctx->y0) || (y0 > gui_lib_ctx->y1) || (x0 < 0) || (x0 >= LCD_SIZE_WIDTH)) {
                if ((y0 < gui_lib_ctx->y0) || (y0 > gui_lib_ctx->y1) || (x0 < gui_lib_ctx->x0) || (x0 > gui_lib_ctx->x1)) {
                    #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
                    pic_data += 7;
                    #else
                    pic_data += 8;
                    #endif

                    if (gui_draw_pointer_check(area, x0, y0)) {
                        return;
                    }
                    continue;
                }
                g_pointer_draw_x_pos = x0;

                buf_offset = UI_CHARGE_XY(x0, y0);  //((y0-gui_lib_ctx->y0)*LCD_SIZE_WIDTH + x0)*COLOR_RGB_PIXEL;
                alpha = pic_data[4];
            #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
                if (alpha == 0xFF) {
                    gui_lib_ctx->frame_buffer[buf_offset] = pic_data[5];
                    gui_lib_ctx->frame_buffer[buf_offset+1] = pic_data[6];
                }
                else if (alpha != 0) {
                    bg_color = (gui_lib_ctx->frame_buffer[buf_offset] << 8)+gui_lib_ctx->frame_buffer[buf_offset+1];
                    r_b = (bg_color >> 0)&0x1F;
                    g_b = (bg_color >> 5)&0x3F;
                    b_b = (bg_color >> 11)&0x1F;

                    pic_color = (pic_data[5]<<8) + pic_data[6];
                    r = (pic_color >> 0)&0x1F;
                    g = (pic_color >> 5)&0x3F;
                    b = (pic_color >> 11)&0x1F;
                    r = (r*alpha + r_b*(0xFF-alpha))/0xFF;
                    g = (g*alpha + g_b*(0xFF-alpha))/0xFF;
                    b = (b*alpha + b_b*(0xFF-alpha))/0xFF;
                    if(r > 0x1F)r=0x1F;
                    if(g > 0x3F)g=0x3F;
                    if(b > 0x1F)b=0x1F;
                    pic_color = (r << 0)+(g << 5)+(b << 11);
                    
                    gui_lib_ctx->frame_buffer[buf_offset] = (pic_color >> 8)&0xFF;
                    gui_lib_ctx->frame_buffer[buf_offset+1] = pic_color & 0xFF;
                }
                pic_data += 7;
                
            #else 
                if (alpha == 0xFF) {
                    gui_lib_ctx->frame_buffer[buf_offset] = pic_data[5];       // b
                    gui_lib_ctx->frame_buffer[buf_offset+1] = pic_data[6];     // g
                    gui_lib_ctx->frame_buffer[buf_offset+2] = pic_data[7];     // r
                }
                else if (alpha != 0) {
                    gui_lib_ctx->frame_buffer[buf_offset+0] = (pic_data[5]*alpha + gui_lib_ctx->frame_buffer[buf_offset+0]*(0xFF-alpha))/0xFF;    // b
                    gui_lib_ctx->frame_buffer[buf_offset+1] = (pic_data[6]*alpha + gui_lib_ctx->frame_buffer[buf_offset+1]*(0xFF-alpha))/0xFF;    // g
                    gui_lib_ctx->frame_buffer[buf_offset+2] = (pic_data[7]*alpha + gui_lib_ctx->frame_buffer[buf_offset+2]*(0xFF-alpha))/0xFF;    // r
                }
                pic_data += 8;
            #endif
            }

            data_sz -= read_sz;
            if (data_sz == 0) break;
            if (data_sz < read_sz) {
                read_sz = data_sz;
            }
            pic_data = gui_drivers_flash_read_image_to_buff(pic_addr, read_sz);
            pic_addr += read_sz;
        }
    }
}
#pragma pop

