
#include "font_convert.h"

#include "gui_display_draw_character.h"
#include "gui_display_draw_lib.h"


#pragma push
#pragma Otime
typedef struct {
    int x_s;
    int x_e;
    int y_s;
    int y_e;
    unsigned short x_pos;
    unsigned short y_pos;
}gui_drawable_info_struct;

SHARE_CACHE_RAM_FUNCTION static int gui_draw_char_drawable_init(gui_drawable_info_struct* drawable, font_char_bitmap_struct* char_bitmap, gui_render_struct* render, short y_start, short y_end)
{
    drawable->x_s = render->x + char_bitmap->xPos;
    drawable->x_e = drawable->x_s + char_bitmap->xSize;
    drawable->y_s = render->y + char_bitmap->yPos;
    drawable->y_e = drawable->y_s + char_bitmap->ySize;

    if((drawable->x_e < 0) || (drawable->x_s >= LCD_SIZE_WIDTH) || (drawable->y_e < 0) || (drawable->y_s >= LCD_SIZE_HEIGHT))
        return 1;

    if(drawable->x_s < 0)
    {
        drawable->x_pos = -drawable->x_s;
        drawable->x_s = 0;
    }
    else{
        drawable->x_pos = 0;
    }
    if(drawable->x_e > LCD_SIZE_WIDTH)
    {
        drawable->x_e = LCD_SIZE_WIDTH;
    }

    if(drawable->y_s < 0)
    {
        drawable->y_pos = -drawable->y_s;
        drawable->y_s = 0;
    }
    else{
        drawable->y_pos = 0;
    }
    if(drawable->y_e > LCD_SIZE_HEIGHT)
    {
        drawable->y_e = LCD_SIZE_HEIGHT;
    }
    /* if y_s & y_e over limit, so don't draw. */
    if ((drawable->y_s > y_end)&&(drawable->y_e < y_start))
    {
        return 1;
    }
    return 0;
}

SHARE_CACHE_RAM_FUNCTION static void gui_draw_char_bitmap(font_char_info_struct* char_info, font_char_bitmap_struct* char_bitmap, gui_render_struct* render, unsigned char* render_buf, short y_start, short y_end)
{
    static const unsigned char bitm[] = {0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01};
    const unsigned char* p_pic = char_bitmap->bitmap;
    gui_drawable_info_struct  drawable;

    unsigned short x_offset,y_offset;
    unsigned short x_align_size;
    unsigned int buf_offset;

    int x0,y0;
    GUI_COLOR color;
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    unsigned char color_h, color_l;
#else
    unsigned char color_r, color_g, color_b;
#endif

    if (gui_draw_char_drawable_init(&drawable, char_bitmap, render, y_start, y_end)) {
        return;
    }

    color = gui_get_color();
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    color_h = color >> 8;
    color_l = color & 0xFF;
#else
    color_r = (color >> 0)&0xFF;
    color_g = (color >> 8)&0xFF;
    color_b = (color >> 16)& 0xFF;
#endif

    x_align_size = ((char_bitmap->xSize+7)/8)*8;
    if (char_info->alinSize) x_align_size = (x_align_size + 31) & 0xFFE0;
    y_offset = drawable.y_pos * x_align_size;
    for(y0 = drawable.y_s;y0 < drawable.y_e;y0++)
    {
        if((y0 < y_start) || (y0 > y_end))
        {
            y_offset += x_align_size;
            continue ;
        }

        x_offset = drawable.x_pos;
        buf_offset = ((y0-y_start)*LCD_SIZE_WIDTH*COLOR_RGB_PIXEL + (drawable.x_s)*COLOR_RGB_PIXEL);
        for(x0 = drawable.x_s; x0 < drawable.x_e; x0++,x_offset++)
        {
            p_pic = &char_bitmap->bitmap[(y_offset + x_offset)/8];
            if(*p_pic & bitm[x_offset&0x07])
            {
            #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
                render_buf[buf_offset++] = color_h;
                render_buf[buf_offset++] = color_l;
            #else
                render_buf[buf_offset++] = color_b;
                render_buf[buf_offset++] = color_g;
                render_buf[buf_offset++] = color_r;
            #endif
            }
            else
            {
                buf_offset += COLOR_RGB_PIXEL;
                continue;
            }
        }
        y_offset += x_align_size;
    }
}

SHARE_CACHE_RAM_FUNCTION static void gui_draw_char_bitmap2(font_char_info_struct* char_info, font_char_bitmap_struct* char_bitmap, gui_render_struct* render, unsigned char* render_buf, short y_start, short y_end)
{
    const unsigned char *p_pic = char_bitmap->bitmap;
    gui_drawable_info_struct  drawable;

    unsigned short x_offset,y_offset;
    unsigned short x_align_size;
    unsigned int buf_offset;
    unsigned int r,g,b,b_r,b_g,b_b;
    int x0,y0;

    GUI_COLOR color;
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    unsigned char color_h, color_l;
#endif

    if (gui_draw_char_drawable_init(&drawable, char_bitmap, render, y_start, y_end)) {
        return;
    }

    color = gui_get_color();
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    // color: 16bit
    // r: AA, 0x00, 0x1F
    // g: AA, 0x07, 0xE0
    // b: AA, 0xF8, 0x00
    // RAM: B0: bbbb_bggg   B1: gggr_rrrr
    color_h = color >> 8;
    color_l = color & 0xFF;
    r = (color >> 0)&0x1F;
    g = (color >> 5)&0x3F;
    b = (color >> 11)&0x1F;
#else
    // color: 24bit
    // r:  AA, 0x00, 0x00, 0xFF
    // g:  AA, 0x00, 0xFF, 0x00
    // b:  AA, 0xFF, 0x00, 0x00
    // RAM: AA, bbbb_bbbb gggg_gggg rrrr_rrrr
    r = (color >> 0)&0xFF;
    g = (color >> 8)&0xFF;
    b = (color >> 16)&0xFF;
#endif

    x_align_size = ((char_bitmap->xSize*2+(8-2))/8)*8;
    if (char_info->alinSize) x_align_size = (x_align_size + 31) & 0xFFE0;
    y_offset = drawable.y_pos * x_align_size;
    for(y0 = drawable.y_s;y0 < drawable.y_e;y0++)
    {
        if((y0 < y_start) || (y0 > y_end))
        {
            y_offset += x_align_size;
            continue ;
        }

        x_offset = drawable.x_pos;
        buf_offset = ((y0-y_start)*LCD_SIZE_WIDTH*COLOR_RGB_PIXEL + (drawable.x_s)*COLOR_RGB_PIXEL);
        for(x0 = drawable.x_s; x0 < drawable.x_e; x0++,x_offset++)
        {
            p_pic = &char_bitmap->bitmap[(y_offset + x_offset*2)/8];
            unsigned char value = ((*p_pic) >> (6-2*(x_offset&0x03)))&0x03;    //    (*p_pic & (0x03 << (6-2*(x_offset%4))));
            if(value != 0)
            {
            #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
                if (value == 0x03) {
                    render_buf[buf_offset++] = color_h;
                    render_buf[buf_offset++] = color_l;
                }
                else {
                    GUI_COLOR pixel_color;
                    pixel_color = (render_buf[buf_offset+0] << 8)+render_buf[buf_offset+1];
                    if (pixel_color == 0) {
                        pixel_color = ((value*r/0x03)<<0) +
                                    ((value*g/0x03)<<5) +
                                    ((value*b/0x03)<<11);
                    }
                    else {
                        b_r = (pixel_color >> 0)&0x1F;
                        b_g = (pixel_color >> 5)&0x3F;
                        b_b = (pixel_color >> 11)&0x1F;
                        pixel_color = (((value*r/0x03)+((0x03-value)*b_r/0x03))<<0) +
                                    (((value*g/0x03)+((0x03-value)*b_g/0x03))<<5) +
                                    (((value*b/0x03)+((0x03-value)*b_b/0x03))<<11);
                    }
                    render_buf[buf_offset++] = pixel_color >> 8;
                    render_buf[buf_offset++] = pixel_color & 0xFF;
                }
            #else
                if (value == 0x03) {
                    render_buf[buf_offset++] = b;
                    render_buf[buf_offset++] = g;
                    render_buf[buf_offset++] = r;
                }
                else {
                    b_r = render_buf[buf_offset+2];
                    b_g = render_buf[buf_offset+1];
                    b_b = render_buf[buf_offset+0];
                    if ((b_r+b_g+b_b) == 0) {
                        render_buf[buf_offset++] = (value*b/0x03);
                        render_buf[buf_offset++] = (value*g/0x03);
                        render_buf[buf_offset++] = (value*r/0x03);
                    }
                    else {
                        render_buf[buf_offset++] = ((value*b/0x03)+((0x03-value)*b_b/0x03));
                        render_buf[buf_offset++] = ((value*g/0x03)+((0x03-value)*b_g/0x03));
                        render_buf[buf_offset++] = ((value*r/0x03)+((0x03-value)*b_r/0x03));
                    }
                }
            #endif
            }
            else
            {
                buf_offset += COLOR_RGB_PIXEL;
                continue;
            }
        }
        y_offset += x_align_size;
    }
}

SHARE_CACHE_RAM_FUNCTION static void gui_draw_char_bitmap4(font_char_info_struct* char_info, font_char_bitmap_struct* char_bitmap, gui_render_struct* render, unsigned char* render_buf, short y_start, short y_end)
{
    const unsigned char *p_pic = char_bitmap->bitmap;
    gui_drawable_info_struct  drawable;

    unsigned short x_offset,y_offset;
    unsigned short x_align_size;
    unsigned int buf_offset;
    unsigned int r,g,b,b_r,b_g,b_b;
    int x0,y0;

    GUI_COLOR color;
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    unsigned char color_h, color_l;
#endif

    if (gui_draw_char_drawable_init(&drawable, char_bitmap, render, y_start, y_end)) {
        return;
    }

    color = gui_get_color();
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    // color: 16bit
    // r: AA, 0x00, 0x1F
    // g: AA, 0x07, 0xE0
    // b: AA, 0xF8, 0x00
    // RAM: B0: bbbb_bggg   B1: gggr_rrrr
    color_h = color >> 8;
    color_l = color & 0xFF;
    r = (color >> 0)&0x1F;
    g = (color >> 5)&0x3F;
    b = (color >> 11)&0x1F;
#else
    // color: 24bit
    // r:  AA, 0x00, 0x00, 0xFF
    // g:  AA, 0x00, 0xFF, 0x00
    // b:  AA, 0xFF, 0x00, 0x00
    // RAM: AA, bbbb_bbbb gggg_gggg rrrr_rrrr
    r = (color >> 0)&0xFF;
    g = (color >> 8)&0xFF;
    b = (color >> 16)&0xFF;
#endif
    x_align_size = ((char_bitmap->xSize*4+(8-4))/8)*8;
    if (char_info->alinSize) x_align_size = (x_align_size + 31) & 0xFFE0;
    y_offset = drawable.y_pos * x_align_size;
    for(y0 = drawable.y_s;y0 < drawable.y_e;y0++)
    {
        if((y0 < y_start) || (y0 > y_end))
        {
            y_offset += x_align_size;
            continue ;
        }

        x_offset = drawable.x_pos;
        buf_offset = ((y0-y_start)*LCD_SIZE_WIDTH*COLOR_RGB_PIXEL + (drawable.x_s)*COLOR_RGB_PIXEL);
        for(x0 = drawable.x_s; x0 < drawable.x_e; x0++,x_offset++)
        {
            p_pic = &char_bitmap->bitmap[(y_offset + x_offset*4)/8];
            unsigned char value = (x_offset&0x01) ? ((*p_pic)&0x0f) : (((*p_pic) >> 4)&0x0f);
            if(value != 0)
            {
            #if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
                if (value == 0x0F) {
                    render_buf[buf_offset++] = color_h;
                    render_buf[buf_offset++] = color_l;
                }
                else {
                    GUI_COLOR pixel_color;
                    pixel_color = (render_buf[buf_offset+0] << 8)+render_buf[buf_offset+1];
                    if (pixel_color == 0) {
                        pixel_color = ((value*r/0x0F)<<0) +
                                    ((value*g/0x0F)<<5) +
                                    ((value*b/0x0F)<<11);
                    }
                    else {
                        b_r = (pixel_color >> 0)&0x1F;
                        b_g = (pixel_color >> 5)&0x3F;
                        b_b = (pixel_color >> 11)&0x1F;
                        pixel_color = (((value*r/0x0F)+((0x0F-value)*b_r/0x0F))<<0) +
                                    (((value*g/0x0F)+((0x0F-value)*b_g/0x0F))<<5) +
                                    (((value*b/0x0F)+((0x0F-value)*b_b/0x0F))<<11);
                    }
                    render_buf[buf_offset++] = pixel_color >> 8;
                    render_buf[buf_offset++] = pixel_color & 0xFF;
                }
            #else
                if (value == 0x0F) {
                    render_buf[buf_offset++] = b;
                    render_buf[buf_offset++] = g;
                    render_buf[buf_offset++] = r;
                }
                else {
                    b_r = render_buf[buf_offset+2];
                    b_g = render_buf[buf_offset+1];
                    b_b = render_buf[buf_offset+0];
                    if ((b_r+b_g+b_b) == 0) {
                        render_buf[buf_offset++] = (value*b/0x0F);
                        render_buf[buf_offset++] = (value*g/0x0F);
                        render_buf[buf_offset++] = (value*r/0x0F);
                    }
                    else {
                        render_buf[buf_offset++] = ((value*b/0x0F)+((0x0F-value)*b_b/0x0F));
                        render_buf[buf_offset++] = ((value*g/0x0F)+((0x0F-value)*b_g/0x0F));
                        render_buf[buf_offset++] = ((value*r/0x0F)+((0x0F-value)*b_r/0x0F));
                    }
                }
            #endif
            }
            else
            {
                buf_offset += COLOR_RGB_PIXEL;
                continue;
            }
        }
        y_offset += x_align_size;
    }
}
#pragma pop


void gui_display_draw_character(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_font_struct* text = (gui_font_struct*)render->data;
    font_char_bitmap_struct* char_bitmap;
	font_char_info_struct char_info;
    int addr_val;
    GUI_COLOR color;

    color = gui_set_color(text->color);

    // get_font_char_info_from_code 改成独立接口，防止渲染线程与UI线程改变字体而产生竞争!!!!!!
    addr_val =  get_font_char_info_from_size_code(text->size, (unsigned long)render->value, &char_info);
    if (addr_val > 0) {
        char_bitmap = font_get_bitmap(&char_info);
        if (char_info.bitPoint == 1) {
            gui_draw_char_bitmap(&char_info, char_bitmap, render, render_buf,  y_start, y_end);
        }
        else if (char_info.bitPoint == 2) {
            gui_draw_char_bitmap2(&char_info, char_bitmap, render, render_buf,  y_start, y_end);
        }
        else if (char_info.bitPoint == 4) {
            gui_draw_char_bitmap4(&char_info, char_bitmap, render, render_buf,  y_start, y_end);
        }
    }

    gui_set_color(color);
}



