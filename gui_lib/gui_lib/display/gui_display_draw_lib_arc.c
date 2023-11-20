#include <math.h>
#include "gui_display_draw_lib.h"

#pragma push
#pragma Otime
SHARE_CACHE_RAM_FUNCTION static void _CalcX(int*px, int y, unsigned int r2)
{
    int x =*px;
    unsigned int y2 = (unsigned int)y*(unsigned int)y;
    unsigned int r2y2 = r2-y2;
    unsigned int x2;
    
    if (y2>=r2) {
        *px=0;
        return;
    }
    
    /* x2 = r2-y2 */
    do {
        x++;
        x2 =(unsigned int)x*(unsigned int)x;
    } while (x2 < r2y2);

    *px = x-1;
}

SHARE_CACHE_RAM_FUNCTION static float _CalcInterSectLin(float y, float y0, float y1, float x0, float x1)
{
    if (y1==y0) {
        return y0;
    }
    else {
        float Slope = (x1-x0)/(y1-y0);
        return (y-y0)*Slope+x0;
    }
}

SHARE_CACHE_RAM_FUNCTION static void _DrawArc(int x0, int y0, int rx, int ry, int Angle0, int Angle1, int xMul, int yMul)
{
    float afx[4];
    float afy[4];
    float ri = rx - (gui_lib_ctx->penSize+1.5f)/2.0f;
    float ro = rx + (gui_lib_ctx->penSize+1.5f)/2.0f;
    float fAngle0 = Angle0*3.1415926f/180.0f;
    float fAngle1 = Angle1*3.1415926f/180.0f;
    float sin0 = sinf(fAngle0); 
    float sin1 = sinf(fAngle1); 
    float cos0 = cosf(fAngle0); 
    float cos1 = cosf(fAngle1); 
    unsigned int   ri2 = ri*ri;
    unsigned int   ro2 = ro*ro;
    int y, yMax, yMin;
    
    afy[0] = ri*sin0;
    afy[1] = ro*sin0;
    afy[2] = ri*sin1;
    afy[3] = ro*sin1;
    afx[0] = ri*cos0;
    afx[1] = ro*cos0;
    afx[2] = ri*cos1;
    afx[3] = ro*cos1;
    yMin = ceilf(afy[0]);
    yMax = floorf(afy[3]);
    
    /* Use Clipping rect to reduce calculation (if possible) */
    if (gui_lib_ctx->clipRect_HL != NULL) {
        if (yMul ==1) {
            if (yMax > (gui_lib_ctx->clip_y1 -y0))
                yMax = (gui_lib_ctx->clip_y1 -y0);
            if (yMin < (gui_lib_ctx->clip_y0 -y0))
                yMin = (gui_lib_ctx->clip_y0 -y0);
        }
        if (yMul == -1) {
            if (yMin > (gui_lib_ctx->clip_y1 -y0))
                yMin = (gui_lib_ctx->clip_y1 -y0);
            if (yMax < (gui_lib_ctx->clip_y0 -y0))
                yMax = (gui_lib_ctx->clip_y0 -y0);
        }
    }
    
    /* Start drawing lines ... */
    {
        int xMinDisp, xMaxDisp, xMin=0,xMax=0;
        for (y=yMax; y>=yMin; y--) {
            _CalcX(&xMin, y, ri2);
            _CalcX(&xMax, y, ro2);
            if ((float)y< afy[1]) {
                xMaxDisp = _CalcInterSectLin(y,afy[0], afy[1], afx[0], afx[1]);
            }
            else {
                xMaxDisp = xMax;			
            }
            if ((float)y > afy[2]) {
                xMinDisp = _CalcInterSectLin(y,afy[2], afy[3], afx[2], afx[3]);
            }
            else {
                xMinDisp = xMin;			
            }
            if (xMul>0)
                gui_lib_ctx->drawHLine(xMinDisp+x0, yMul*y+y0, xMaxDisp+x0);
            else
                gui_lib_ctx->drawHLine(-xMaxDisp+x0, yMul*y+y0, -xMinDisp+x0);
        }
    }
}
#pragma pop

static void GL_DrawArc (int x0, int y0, int rx, int ry, int a0, int a1)
{
    int aEnd;
    
    a0+=360;
    a1+=360;
    while (a0>=360) {
        a0 -= 360;
        a1 -= 360;
    }
    
    /* Do first quadrant 0-90 degree */
DoFirst:
    if (a1<=0)
        return;
    if (a0<90) {
        if (a0<0)
            a0=0;
        aEnd = (a1<90) ? a1 : 90;
        _DrawArc(x0,y0,rx,ry,a0,aEnd, 1, -1);
    }
    a1-=90;
    a0-=90;
    
    /* Do second quadrant 90-180 degree */
    if (a1<=0)
        return;
    if (a0<90) {
        if (a0<0)
            a0=0;
        aEnd = (a1<90) ? a1 : 90;
        _DrawArc(x0,y0,rx,ry,90-aEnd, 90-a0,-1,-1);
    }
    a1-=90;
    a0-=90;
    
    /* Do third quadrant 180-270 degree */
    if (a1<=0)
        return;
    if (a0<90) {
        if (a0<0)
            a0=0;
        aEnd = (a1<90) ? a1 : 90;
        _DrawArc(x0,y0,rx,ry,a0,aEnd, -1, 1);
    }
    a1-=90;
    a0-=90;
    
    /* Do last quadrant 270-360 degree */
    if (a1<=0)
        return;
    if (a0<90) {
        if (a0<0)
            a0=0;
        aEnd = (a1<90) ? a1 : 90;
        _DrawArc(x0,y0,rx,ry,90-aEnd, 90-a0,1,1);
    }
    a1-=90;
    a0-=90;
    
    goto DoFirst;
}

void GUI_DrawArc (int x0, int y0, int rx, int ry, int a0, int a1)
{
    GL_DrawArc( x0, y0, rx, ry, a0, a1);
}

