
#include <math.h>

#include "picture.h"
#include "debug_info.h"
//#include "os/os_api.h"

#include "gui_drivers_flash.h"
#include "gui_display_draw_lib.h"

typedef struct
{
    int img_y0, dh, iy1;
    int img_x0, dw, ix1;
    int x0, y0, x1, y1;
}gui_drawable_info_struct;

#pragma push
#pragma Otime

SHARE_CACHE_RAM_FUNCTION static void ui_draw_picture_init(gui_drawable_info_struct* draw_info, picture_info_struct *picture_info, int x, int y)
{
    // y
    if (gui_lib_ctx->y0 < y) {
        if (gui_lib_ctx->clipRect.y0 > y) {
            draw_info->img_y0 = gui_lib_ctx->clipRect.y0 - y;
            draw_info->y0 = gui_lib_ctx->clipRect.y0;
        }
        else {
            draw_info->img_y0 = 0;
            draw_info->y0 = y;
        }
    }
    else {
        if (gui_lib_ctx->clipRect.y0 > gui_lib_ctx->y0) {
            draw_info->img_y0 = gui_lib_ctx->clipRect.y0 - y;
            draw_info->y0 = gui_lib_ctx->clipRect.y0;
        }
        else {
            draw_info->img_y0 = gui_lib_ctx->y0 - y;
            draw_info->y0 = gui_lib_ctx->y0;
        }
    }
    draw_info->iy1 = y + picture_info->height - 1;
    if (draw_info->iy1 > gui_lib_ctx->y1) {
        if (gui_lib_ctx->clipRect.y1 < gui_lib_ctx->y1) {
            draw_info->y1 = gui_lib_ctx->clipRect.y1;
        }
        else {
            draw_info->y1 = gui_lib_ctx->y1;
        }
    }
    else {
        if (gui_lib_ctx->clipRect.y1 < draw_info->iy1) {
            draw_info->y1 = gui_lib_ctx->clipRect.y1;
        }
        else {
            draw_info->y1 = draw_info->iy1;
        }
    }
    draw_info->dh = draw_info->y1 - draw_info->y0 + 1;

    // x
#if 1 //GUILIB_V2
    if (gui_lib_ctx->x0 < x) {
        if (gui_lib_ctx->clipRect.x0 > x) {
            draw_info->img_x0 = gui_lib_ctx->clipRect.x0 - x;
            draw_info->x0 = gui_lib_ctx->clipRect.x0;
        }
        else {
            draw_info->img_x0 = 0;
            draw_info->x0 = x;
        }
    }
    else {
        if (gui_lib_ctx->clipRect.x0 > gui_lib_ctx->x0) {
            draw_info->img_x0 = gui_lib_ctx->clipRect.x0 - x;
            draw_info->x0 = gui_lib_ctx->clipRect.x0;
        }
        else {
            draw_info->img_x0 = gui_lib_ctx->x0 - x;
            draw_info->x0 = gui_lib_ctx->x0;
        }
    }
    draw_info->ix1 = x + picture_info->width - 1;
    if (draw_info->ix1 > gui_lib_ctx->x1) {
        if (gui_lib_ctx->clipRect.x1 < gui_lib_ctx->x1) {
            draw_info->x1 = gui_lib_ctx->clipRect.x1;
        }
        else {
            draw_info->x1 = gui_lib_ctx->x1;
        }
    }
    else {
        if (gui_lib_ctx->clipRect.x1 < draw_info->ix1) {
            draw_info->x1 = gui_lib_ctx->clipRect.x1;
        }
        else {
            draw_info->x1 = draw_info->ix1;
        }
    }
    draw_info->dw = draw_info->x1 - draw_info->x0 + 1;

#else
    if (x > 0) {
        if (gui_lib_ctx->clipRect.x0 > x) {
            draw_info->img_x0 = gui_lib_ctx->clipRect.x0 - x;
            draw_info->x0 = gui_lib_ctx->clipRect.x0;
        }
        else {
            draw_info->img_x0 = 0;
            draw_info->x0 = x;
        }
    }
    else {
        if (gui_lib_ctx->clipRect.x0 > 0) {
            draw_info->img_x0 = gui_lib_ctx->clipRect.x0 - x;
            draw_info->x0 = gui_lib_ctx->clipRect.x0;
        }
        else {
            draw_info->img_x0 = - x;
            draw_info->x0 = 0;
        }
    }
    draw_info->ix1 = x + picture_info->width - 1;
    if (gui_lib_ctx->clipRect.x1 < draw_info->ix1) {
        draw_info->x1 = gui_lib_ctx->clipRect.x1;
    }
    else {
        draw_info->x1 = draw_info->ix1;
    }
    draw_info->dw = draw_info->x1 - draw_info->x0 + 1;
#endif
}

SHARE_CACHE_RAM_FUNCTION static void ui_draw_picture_direct(picture_info_struct *picture_info, int x, int y)
{
    unsigned int   addr, buf_offset;
    int y0, img_y0, img_y1, dh;

    if (y > gui_lib_ctx->y0) {
        y0 = y;
        img_y0 = 0;
        dh = gui_lib_ctx->y1 - y0 + 1;
        if (dh > picture_info->height) {
            dh = picture_info->height;
        }
    }
    else {
        y0 = gui_lib_ctx->y0;
        img_y0 = gui_lib_ctx->y0 - y;
        img_y1 = y + picture_info->height - 1;
        if (img_y1 > gui_lib_ctx->y1) {
            dh = gui_lib_ctx->y1 - y0 + 1;
        }
        else {
            dh = img_y1 - y0 + 1;
        }
    }

    if (dh <= 0) {
        return;
    }

    buf_offset = (y0-gui_lib_ctx->y0)*LCD_SIZE_WIDTH*COLOR_RGB_PIXEL;
    addr = (unsigned int)picture_info->addr;
    addr += (img_y0*LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);

    if (picture_info->external_flag) {
        gui_drivers_flash_read_image_to(gui_lib_ctx->frame_buffer+buf_offset, addr, dh*LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
    }
    else {
        memcpy(gui_lib_ctx->frame_buffer+buf_offset, (unsigned char*)addr, dh*LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
    }
}

SHARE_CACHE_RAM_FUNCTION static void ui_draw_picture_normal(picture_info_struct *picture_info, int x, int y)
{
    gui_drawable_info_struct  draw_info;

    unsigned char* pic_buf;
    unsigned char* frame_buf;
    unsigned int   buf_offset;
    unsigned int   addr;

    ui_draw_picture_init(&draw_info, picture_info, x, y);
    if (draw_info.dw <= 0 || draw_info.dh <= 0) {
        return;
    }

    buf_offset = UI_CHARGE_XY(draw_info.x0, draw_info.y0);    // ((draw_info.y0-gui_lib_ctx->y0)*LCD_SIZE_WIDTH + draw_info.x0)*COLOR_RGB_PIXEL;
    frame_buf = gui_lib_ctx->frame_buffer + buf_offset;

    addr = (unsigned int)picture_info->addr;
    addr += (draw_info.img_y0*picture_info->width + draw_info.img_x0)*COLOR_RGB_PIXEL;
    if (picture_info->external_flag) {
        pic_buf = gui_drivers_flash_read_image_to_buff(addr, draw_info.dh*picture_info->width*COLOR_RGB_PIXEL);
    }
    else {
        pic_buf = (unsigned char*)addr;
    }
    while(draw_info.dh) {
        memcpy(frame_buf, pic_buf, draw_info.dw*COLOR_RGB_PIXEL);
        frame_buf += gui_lib_ctx->bw;    // (LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
        pic_buf += (picture_info->width*COLOR_RGB_PIXEL);
        draw_info.dh --;
    }
}

// alpha
SHARE_CACHE_RAM_FUNCTION static void ui_draw_picture_alpha(picture_info_struct *picture_info, int x, int y)
{
    gui_drawable_info_struct  draw_info;

    unsigned char* frame_buf;
    unsigned int   buf_offset;

    unsigned char* pic_buf;
    unsigned char* p_buf;
    unsigned char* d_buf;
    unsigned int   alpha;
    unsigned int   addr;

#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    unsigned int r,g,b,r_b,g_b,b_b;
    GUI_COLOR pic_color, bg_color;
#endif

    ui_draw_picture_init(&draw_info, picture_info, x, y);
    if (draw_info.dw <= 0 || draw_info.dh <= 0) {
        return;
    }

    buf_offset = UI_CHARGE_XY(draw_info.x0, draw_info.y0);  //((draw_info.y0-gui_lib_ctx->y0)*LCD_SIZE_WIDTH + draw_info.x0)*COLOR_RGB_PIXEL;
    frame_buf = gui_lib_ctx->frame_buffer + buf_offset;

    addr = (unsigned int)picture_info->addr;
    addr += (draw_info.img_y0*picture_info->width + draw_info.img_x0)*(COLOR_RGB_PIXEL+1);
    if (picture_info->external_flag) {
        pic_buf = gui_drivers_flash_read_image_to_buff(addr, draw_info.dh*picture_info->width*(COLOR_RGB_PIXEL+1));
    }
    else {
        pic_buf = (unsigned char*)addr;
    }

    while(draw_info.dh) {
        p_buf = pic_buf;
        d_buf = frame_buf;

        for (draw_info.x0=0; draw_info.x0<draw_info.dw; draw_info.x0++) {
            alpha = p_buf[0];

    #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
            if (alpha == 0xFF) {
                d_buf[0] = p_buf[1];
                d_buf[1] = p_buf[2];
            }
            else if (alpha != 0) {
                bg_color = (d_buf[0] << 8)+d_buf[1];
                if (bg_color == 0) {
                    pic_color = (p_buf[1]<<8) + p_buf[2];
                    r = (pic_color >> 0)&0x1F;
                    g = (pic_color >> 5)&0x3F;
                    b = (pic_color >> 11)&0x1F;
                    r = (r*alpha)/0xFF;
                    g = (g*alpha)/0xFF;
                    b = (b*alpha)/0xFF;
                    pic_color = (r << 0)+(g << 5)+(b << 11);
                }
                else {
                    r_b = (bg_color >> 0)&0x1F;
                    g_b = (bg_color >> 5)&0x3F;
                    b_b = (bg_color >> 11)&0x1F;

                    pic_color = (p_buf[1]<<8) + p_buf[2];
                    r = (pic_color >> 0)&0x1F;
                    g = (pic_color >> 5)&0x3F;
                    b = (pic_color >> 11)&0x1F;
                    r = (r*alpha + r_b*(0xFF-alpha))/0xFF;
                    g = (g*alpha + g_b*(0xFF-alpha))/0xFF;
                    b = (b*alpha + b_b*(0xFF-alpha))/0xFF;
                    pic_color = (r << 0)+(g << 5)+(b << 11);
                }
                d_buf[0] = (pic_color >> 8)&0xFF;
                d_buf[1] = pic_color & 0xFF;
            }
    #else
            if (alpha == 0xFF) {
                d_buf[0] = p_buf[1];        // b
                d_buf[1] = p_buf[2];        // g
                d_buf[2] = p_buf[3];        // r
            }
            else if (alpha != 0) {
                if ((d_buf[2]+d_buf[1]+d_buf[0]) == 0) {
                    d_buf[0] = (p_buf[1]*alpha)/0xFF;   // b
                    d_buf[1] = (p_buf[2]*alpha)/0xFF;   // g
                    d_buf[2] = (p_buf[3]*alpha)/0xFF;   // r
                }
                else {
                    d_buf[0] = (p_buf[1]*alpha + d_buf[0]*(0xFF-alpha))/0xFF;    // b
                    d_buf[1] = (p_buf[2]*alpha + d_buf[1]*(0xFF-alpha))/0xFF;    // g
                    d_buf[2] = (p_buf[3]*alpha + d_buf[2]*(0xFF-alpha))/0xFF;    // r
                }
            }
    #endif

            p_buf += (COLOR_RGB_PIXEL+1);
            d_buf += COLOR_RGB_PIXEL;
        }

        frame_buf += gui_lib_ctx->bw;    //(LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
        pic_buf += (picture_info->width*(COLOR_RGB_PIXEL+1));
        draw_info.dh --;
    }
}

SHARE_CACHE_RAM_FUNCTION static void ui_draw_picture_pat256(picture_info_struct *picture_info, int x, int y)
{   // 针对16位色，改为short指针操作，提高绘图效率!!!!
    gui_drawable_info_struct  draw_info;

    unsigned char* p_buf;
    unsigned char* pic_buf;
    unsigned char* frame_buf;
    unsigned int   buf_offset;

#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    unsigned short* d_buf;
    unsigned short* pat_buf;
    unsigned int pat_addr;
    unsigned int addr;

    ui_draw_picture_init(&draw_info, picture_info, x, y);
    if (draw_info.dw <= 0 || draw_info.dh <= 0) {
        return;
    }

    buf_offset = UI_CHARGE_XY(draw_info.x0, draw_info.y0);  //((draw_info.y0-gui_lib_ctx->y0)*LCD_SIZE_WIDTH + draw_info.x0)*COLOR_RGB_PIXEL;
    frame_buf = gui_lib_ctx->frame_buffer + buf_offset;

    addr = (unsigned int)picture_info->addr;
    pat_addr = addr + picture_info->width*picture_info->height + 2;
    addr += (draw_info.img_y0*picture_info->width + draw_info.img_x0);

    if (picture_info->external_flag) {
        pic_buf = gui_drivers_flash_read_image_to_buff(addr, draw_info.dh*picture_info->width);

        // read pattern
        pat_buf = (unsigned short*)(pic_buf + ((draw_info.dh*picture_info->width + 3) & 0xFFFFFFFC));
        gui_drivers_flash_read_image_to((unsigned char*)pat_buf, pat_addr, 256*COLOR_RGB_PIXEL);
    }
    else {
        pic_buf = (unsigned char*)addr;
        pat_buf = (unsigned short*)pat_addr;
    }

    while(draw_info.dh) {
        p_buf = pic_buf;
        d_buf = (unsigned short*)frame_buf;

        for (draw_info.x0=0; draw_info.x0<draw_info.dw; draw_info.x0++) {
            d_buf[0] = pat_buf[p_buf[0]];
            p_buf += 1;
            d_buf += 1;
        }

        frame_buf += gui_lib_ctx->bw;    //(LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
        pic_buf += picture_info->width;
        draw_info.dh --;
    }
#else
    unsigned char* d_buf;
    unsigned char* pat_buf;
    unsigned int pat_addr;
    unsigned int addr;

    ui_draw_picture_init(&draw_info, picture_info, x, y);
    if (draw_info.dw <= 0 || draw_info.dh <= 0) {
        return;
    }

    buf_offset = UI_CHARGE_XY(draw_info.x0, draw_info.y0);  //((draw_info.y0-gui_lib_ctx->y0)*LCD_SIZE_WIDTH + draw_info.x0)*COLOR_RGB_PIXEL;
    frame_buf = gui_lib_ctx->frame_buffer + buf_offset;

    addr = (unsigned int)picture_info->addr;
    pat_addr = addr + picture_info->width*picture_info->height + 2;
    addr += (draw_info.img_y0*picture_info->width + draw_info.img_x0);

    if (picture_info->external_flag) {
        pic_buf = gui_drivers_flash_read_image_to_buff(addr, draw_info.dh*picture_info->width);

        // read pattern
        pat_buf = pic_buf + ((draw_info.dh*picture_info->width + 3) & 0xFFFFFFFC);
        gui_drivers_flash_read_image_to(pat_buf, pat_addr, 256*COLOR_RGB_PIXEL);
    }
    else {
        pic_buf = (unsigned char*)addr;
        pat_buf = (unsigned char*)pat_addr;
    }

    while(draw_info.dh) {
        p_buf = pic_buf;
        d_buf = frame_buf;

        for (draw_info.x0=0; draw_info.x0<draw_info.dw; draw_info.x0++) {
            d_buf[0] = pat_buf[3*p_buf[0]+0];       // b
            d_buf[1] = pat_buf[3*p_buf[0]+1];       // g
            d_buf[2] = pat_buf[3*p_buf[0]+2];       // r
            p_buf += 1;
            d_buf += COLOR_RGB_PIXEL;
        }

        frame_buf += gui_lib_ctx.bw;    //(LCD_SIZE_WIDTH*COLOR_RGB_PIXEL);
        pic_buf += picture_info->width;
        draw_info.dh --;
    }
#endif
}

SHARE_CACHE_RAM_FUNCTION static void ui_draw_picture_alpha_pAA(picture_info_struct *picture_info, int x, int y)
{
    // ...
}

#pragma pop

void GUI_DrawPicture(picture_info_struct* picture_info, int x, int y)
{
    if (picture_info->alpha == 0) {
        if ((x == 0) && (picture_info->width == LCD_SIZE_WIDTH) && (gui_lib_ctx->x0 == 0) && (gui_lib_ctx->x1 == (LCD_SIZE_WIDTH-1))) {
            ui_draw_picture_direct(picture_info, x, y);
        }
        else {
            ui_draw_picture_normal(picture_info, x, y);
        }
    }
    else if (picture_info->alpha == 1) {
        ui_draw_picture_alpha(picture_info, x, y);
    }
    else if (picture_info->alpha == 3) {
        ui_draw_picture_pat256(picture_info, x, y);
    }
    else if (picture_info->alpha == 4) {
        ui_draw_picture_alpha_pAA(picture_info, x, y);
    }
}

