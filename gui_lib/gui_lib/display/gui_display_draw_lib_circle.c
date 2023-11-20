
#include <math.h>
#include "gui_display_draw_lib.h"

extern void GL_DrawLine1(int x0, int y0, int x1, int y1);

#pragma push
#pragma Otime
SHARE_CACHE_RAM_FUNCTION static void Draw8Point(int x0,int y0, int xoff, int yoff)
{
    gui_lib_ctx->setPixel(x0+xoff, y0+yoff, gui_lib_ctx->color);
    gui_lib_ctx->setPixel(x0-xoff, y0+yoff, gui_lib_ctx->color);
    gui_lib_ctx->setPixel(x0+yoff, y0+xoff, gui_lib_ctx->color);
    gui_lib_ctx->setPixel(x0+yoff, y0-xoff, gui_lib_ctx->color);
    if (yoff) {
        gui_lib_ctx->setPixel(x0+xoff, y0-yoff, gui_lib_ctx->color);
        gui_lib_ctx->setPixel(x0-xoff, y0-yoff, gui_lib_ctx->color);
        gui_lib_ctx->setPixel(x0-yoff, y0+xoff, gui_lib_ctx->color);
        gui_lib_ctx->setPixel(x0-yoff, y0-xoff, gui_lib_ctx->color);
    }
}


SHARE_CACHE_RAM_FUNCTION static void GL_DrawCircle(int x0, int y0, int r)
{
    int i;
    int imax = ((r*707))/1000+1;
    int sqmax = r*r+r/2;
    int y=r;
    Draw8Point(x0,y0,r,0);
    for (i=1; i<= imax; i++) {
        if ((i*i+y*y) >sqmax) {
            Draw8Point(x0,y0,i,y);
            y--;
        }
        Draw8Point(x0,y0,i,y);
    }
}


SHARE_CACHE_RAM_FUNCTION static void GL_FillCircle(int x0, int y0, int r)
{
    int i;
    int imax = ((r*707))/1000+1;
    int sqmax = r*r+r/2;
    int x=r;

    gui_lib_ctx->drawHLine(x0-r,y0,x0+r);
    for (i=1; i<= imax; i++) {
        if ((i*i+x*x) >sqmax) {
            /* draw lines from outside */
            if (x>imax) {
                gui_lib_ctx->drawHLine (x0-i+1,y0+x, x0+i-1);
                gui_lib_ctx->drawHLine (x0-i+1,y0-x, x0+i-1);
            }
            x--;
        }

        /* draw lines from inside (center) */
        gui_lib_ctx->drawHLine(x0-x,y0+i, x0+x);
        gui_lib_ctx->drawHLine(x0-x,y0-i, x0+x);
    }
}

SHARE_CACHE_RAM_FUNCTION static void GL_FillEllipse(int x0, int y0, int rx, int ry)
{
    int OutConst, Sum, SumY;
    int x,y;
    unsigned int _rx = rx;
    unsigned int _ry = ry;

    OutConst = _rx*_rx*_ry*_ry  /* Constant as explaint above */
    +(_rx*_rx*_ry>>1); /* To compensate for rounding */
    x = rx;
    for (y=0; y<=ry; y++) {
        SumY =((rx*rx))*((y*y)); /* Does not change in loop */
        while (Sum = SumY + ((ry*ry))*((x*x)), (x>0) && (Sum>OutConst))
        {
            x--;
        }
        gui_lib_ctx->drawHLine(x0-x, y0+y, x0+x);
        if (y)
            gui_lib_ctx->drawHLine(x0-x, y0-y, x0+x);
    }
}

SHARE_CACHE_RAM_FUNCTION static void GL_DrawEllipse(int x0, int y0, int rx, int ry)
{
    int OutConst, Sum, SumY;
    int x,y;
    int xOld;
    unsigned int _rx = rx;
    unsigned int _ry = ry;
    OutConst = _rx*_rx*_ry*_ry  /* Constant as explaint above */
                +(_rx*_rx*_ry>>1); /* To compensate for rounding */
    xOld = x = rx;
    for (y=0; y<=ry; y++) {
        if (y==ry) {
            x=0;
        }
        else {
            SumY =((rx*rx))*((y*y)); /* Does not change in loop */
            while (Sum = SumY + ((ry*ry))*((x*x)), (x>0) && (Sum>OutConst))
                x--;
        }

        /* Since we draw lines, we can not draw on the first
        iteration
        */
        if (y) {
            GL_DrawLine1(x0-xOld,y0-y+1,x0-x,y0-y);
            GL_DrawLine1(x0-xOld,y0+y-1,x0-x,y0+y);
            GL_DrawLine1(x0+xOld,y0-y+1,x0+x,y0-y);
            GL_DrawLine1(x0+xOld,y0+y-1,x0+x,y0+y);
        }
        xOld = x;
    }
}
#pragma pop


void GUI_DrawCircle(int x0, int y0, int r)
{
    GL_DrawCircle( x0, y0, r);
}

void GUI_FillCircle(int x0, int y0, int r)
{
    GL_FillCircle(x0,y0,r);
}

void GUI_FillEllipse(int x0, int y0, int rx, int ry)
{
    GL_FillEllipse (x0,y0, rx, ry);
}

void GUI_DrawEllipse(int x0, int y0, int rx, int ry)
{
    GL_DrawEllipse(x0, y0, rx, ry);
}




