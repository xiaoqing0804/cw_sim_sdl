
#include "picture.h"
#include "gui_drivers_flash.h"

#include "gui_display_draw_lib.h"
#include "gui_display_draw_lib_aa.h"
#include "gui_display_draw_pointer.h"
#include "gui_display_draw_dlwf.h"

#include "debug_info.h"

void gui_display_draw_dlwf_picture(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    unsigned int width, height, alpha;

    //height = render->value & 0x0000FFFF;
    //width = (render->value >> 16) & 0x00007FFF;
    //alpha = (render->value & 0x80000000) ? 1 : 0;
    height = render->value & 0x00000FFF;
    width = (render->value >> 12) & 0x00000FFF;
    alpha = (render->value >> 24) & 0x000000FF;
    
    const picture_info_struct bitmap = {
        .addr = (unsigned char*)render->data,
        .width = width,
        .height = height,
        .alpha = alpha,
        .external_flag = 1,
    };
    
    //SYS_DEBUG("draw_dlwf_picture(d: %x, w:%d, h:%d)", render->data, width, height);
    GUI_DrawPicture((picture_info_struct*)&bitmap, render->x, render->y);
}

void gui_display_draw_dlwf_shape(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    // ... 
}

