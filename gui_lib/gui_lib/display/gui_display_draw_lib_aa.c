
/***************************************************************************************/
//      date            auth            note
//--------------------------------------------------------------------------------------
//   2022-11-28       Taylor.Le         支持屏幕剪切区 （GUILIB_V2）
//
/***************************************************************************************/

#include "debug_info.h"
#include "math.h"

#include "gui_display_draw_lib_aa.h"


#define GUI_AAFACTOR    4
#define GUI_AA_LINEBUFFER_SIZE      LCD_SIZE_WIDTH

typedef struct 
{
    unsigned char   abAABuffer[GUI_AA_LINEBUFFER_SIZE];   /* This could be changed to dynamic memory ... */
    unsigned char*  pabAABuffer;
    int  _x0;
    int  _x1;
    int  _y;
    int  _x0_InUse;
    int  _x1_InUse;

    short   penSize;
    short   aaFactor;

    gdi_rect        clipRect;
    fp_DrawHLine    drawHLine;
    
}gui_aalib_ctx;


static gui_aalib_ctx    _aalib_ctx;

static void GUI_AA_Init(int x0, int x1);
static void GUI_AA_Exit(void);

#pragma push
#pragma Otime
SHARE_CACHE_RAM_FUNCTION GUI_COLOR gui_AA_mixColors(GUI_COLOR Color, GUI_COLOR BkColor, unsigned char Intens)
{
    GUI_COLOR Color2;
    
    //SYS_DEBUG("AA_mix=%d\n", Intens);
#if (COLOR_RGB_MODE == COLOR_RGB_MODE_565)
    unsigned int R = ((Color & 0x001F) << 3)*Intens;
    unsigned int G = ((Color & 0x07E0) >> 5)*Intens;
    unsigned int B = ((Color & 0xF800) >> 8)*Intens;

    Intens = 15 - Intens;
    R += ((BkColor & 0x001F) << 3)*Intens;
    G += ((BkColor & 0x07E0) >> 5)*Intens;
    B += ((BkColor & 0xF800) >> 8)*Intens;
    R = ((R/15) >> 3)&0x001F;
    G = ((G/15) << 5)&0x07E0;
    B = ((B/15) << 8)&0xF800;
    Color2 = R+G+B;
#else
    /* Calc Color seperations for FgColor first */
    unsigned int R = (Color&0xff)*Intens;
    unsigned int G = (Color&0xff00)*Intens;
    unsigned int B = (Color&0xff0000)*Intens;

    /* Add Color seperations for BkColor */
    Intens = 15-Intens;
    R += (BkColor&0xff)*Intens;
    G += (BkColor&0xff00)*Intens;
    B += (BkColor&0xff0000)*Intens;
    R = (R/15)&0xff;
    G = (G/15)&0xff00;
    B = (B/15)&0xff0000;
    Color2 = R+G+B;
#endif
    //SYS_DEBUG("AA_mix:%x, %x, %d, %x\n", Color, BkColor, Intens, Color2);
    return Color2;
}


/* Draw 1-pixel with Foreground color */
SHARE_CACHE_RAM_FUNCTION static void gui_setPixelAA(int x, int y, unsigned char Intens)
{
    //SYS_DEBUG("Intens=%d", Intens);
    if (Intens == 0)
        return;
    
    RETURN_IF_Y_OUT();
    RETURN_IF_X_OUT();
    if (Intens >= 15) {
        gui_lib_ctx->setPixel(x,y, gui_lib_ctx->color);
    }
    else {
        GUI_COLOR Color = gui_lib_ctx->color;
        GUI_COLOR BkColor =  gui_lib_ctx->getPixel(x,y);
        Color = gui_AA_mixColors(Color, BkColor, Intens);
        gui_lib_ctx->setPixel(x,y, Color);
    }
}

SHARE_CACHE_RAM_FUNCTION static void _CleanLine(void)
{
    memset(_aalib_ctx.pabAABuffer, 0, _aalib_ctx._x1 - _aalib_ctx._x0 + 1);
    _aalib_ctx._y = -16383;  /* Invalidate */  
    _aalib_ctx._x0_InUse =  16383;
    _aalib_ctx._x1_InUse = -16383;
}

SHARE_CACHE_RAM_FUNCTION static void _FlushLine(void)
{
    int i;
    int iEnd = _aalib_ctx._x1_InUse - _aalib_ctx._x0;
    int IMax = _aalib_ctx.aaFactor * _aalib_ctx.aaFactor;
    for (i = _aalib_ctx._x0_InUse-_aalib_ctx._x0; i<=iEnd; i++) {
        int Intens = *(_aalib_ctx.pabAABuffer+i);
        if (Intens) {
            /* Check we can use line draw */
            if (Intens == IMax) {
                int j;
                for (j=i; j<iEnd; ) {
                    if (*(_aalib_ctx.pabAABuffer+j+1) != IMax) {
                        break;
                    }
                    j++;
                }
                /* Draw the full pixel(s) */
                if (j!=i) {
                    _aalib_ctx.drawHLine(_aalib_ctx._x0 + i, _aalib_ctx._y, _aalib_ctx._x0 + j);
                    i = j;  /*xxx*/
                }
                else {
                    gui_lib_ctx->setPixel(_aalib_ctx._x0 + i, _aalib_ctx._y, gui_lib_ctx->color);
                }
            }
            else {
                gui_setPixelAA(_aalib_ctx._x0 + i, _aalib_ctx._y, (15*Intens+IMax/2)/IMax);
            }
        }    
    }
    _CleanLine();
}


SHARE_CACHE_RAM_FUNCTION static void _DrawHLine  (int x0, int y,  int x1)
{
    int x0Real, x1Real;
    
    /* Make sure there is something to do */
    if (x1 < x0)
        return;
    
    /* Flush line if we are in an other pixel (real) line */
    if (y / _aalib_ctx.aaFactor != _aalib_ctx._y) {
        _FlushLine();
        _aalib_ctx._y = y / _aalib_ctx.aaFactor;
    }
    x0Real = x0 / _aalib_ctx.aaFactor;
    x1Real = x1 / _aalib_ctx.aaFactor;
    
    /* Handle used area (speed optimization for drawing) */
    if (x0Real < _aalib_ctx._x0_InUse)
        _aalib_ctx._x0_InUse = x0Real;
    if (x1Real > _aalib_ctx._x1_InUse)
        _aalib_ctx._x1_InUse = x1Real;
    
    /* Clip (should not be necessary ... Just to be on the safe side ! */
    if (x0Real < _aalib_ctx._x0) {
        x0 = _aalib_ctx._x0 * _aalib_ctx.aaFactor;
    }
    if (x1Real > _aalib_ctx._x1) {
        x1 = (_aalib_ctx._x1 + 1) * _aalib_ctx.aaFactor - 1;
    }
    
    /* Make sure there is still something to do (after clipping) */
    if (x1 < x0)
        return;
    
    /* Inc. hit counters in buffer */
    {
        int x0_Off = x0 / _aalib_ctx.aaFactor - _aalib_ctx._x0;
        int x1_Off = x1 / _aalib_ctx.aaFactor - _aalib_ctx._x0;
        int iRem = x1_Off - x0_Off + 1;
        unsigned char *pDest = _aalib_ctx.pabAABuffer + x0_Off;
        
        if (iRem == 1) {
            *(pDest) += (x1 - x0 + 1);
        }
        else {
            /* First Pixel */
            *pDest += ((x0_Off + _aalib_ctx._x0 + 1) * _aalib_ctx.aaFactor - x0);
            pDest ++;
            
            /* Middle Pixels */
            for (;--iRem>1; ) {
                *pDest += _aalib_ctx.aaFactor;
                pDest ++;
            }
            
            /* Last Pixel */
            *pDest += (1 + x1- (x1_Off + _aalib_ctx._x0) * _aalib_ctx.aaFactor);
        }
    }
}

SHARE_CACHE_RAM_FUNCTION static void _DrawCircle(int x0, int y0, int r)
{
    int i, x1, x2;
    int sqmax1, sqmax2, r1, r2;
    int yMin1,  yMax1, yMin2, yMax2;

    r1 = r-gui_lib_ctx->penSize/2;  // 
    r2 = r+gui_lib_ctx->penSize/2;
    sqmax1 = r1*r1 + r1/2;
    sqmax2 = r2*r2 + r2/2;

    yMin1 = y0 - r1;
    yMax1 = y0 + r1;
    yMin2 = y0 - r2;
    yMax2 = y0 + r2;

    /* Use Clipping rect to reduce calculation (if possible) */
    if (gui_lib_ctx->clipRect_HL != NULL) {
        if (yMax1 > gui_lib_ctx->clip_y1)
            yMax1 = gui_lib_ctx->clip_y1;
        if (yMin1 < gui_lib_ctx->clip_y0)
            yMin1 = gui_lib_ctx->clip_y0;
        if (yMax2 > gui_lib_ctx->clip_y1)
            yMax2 = gui_lib_ctx->clip_y1;
        if (yMin2 < gui_lib_ctx->clip_y0)
            yMin2 = gui_lib_ctx->clip_y0;
    }

    /* Draw top half */
    for (i=0, x2=r2, x1=r1; i<r2; i++) {
        int y = y0-i;
        if ((y >= yMin2) && (y <= yMax2)) {
            /* calc proper x-value */
            while ((i*i+x2*x2) >sqmax2) {
                --x2;
            }

            if ((y >= yMin1) && (y <= yMax1)) {
                /* calc proper x-value */
                while ((i*i+x1*x1) >sqmax1) {
                    --x1;
                }
                gui_lib_ctx->drawHLine (x0-x2, y, x0-x1);
                gui_lib_ctx->drawHLine (x0+x1, y, x0+x2);
            }
            else {
                gui_lib_ctx->drawHLine (x0-x2, y, x0+x2);
            }
        }
    }

    /* Draw bottom half */
    for (i=0, x2=r2, x1=r1; i<r2; i++) {
        int y = y0 + i;
        if ((y >= yMin2) && (y <= yMax2)) {
            /* calc proper x-value */
            while ((i*i+x2*x2) >sqmax2) {
                --x2;
            }

            if ((y >= yMin1) && (y <= yMax1)) {
                /* calc proper x-value */
                while ((i*i+x1*x1) >sqmax1) {
                    --x1;
                }
                gui_lib_ctx->drawHLine (x0-x2, y, x0-x1);
                gui_lib_ctx->drawHLine (x0+x1, y, x0+x2);
            }
            else {
                gui_lib_ctx->drawHLine (x0-x2, y, x0+x2);
            }
        }
    }
}


SHARE_CACHE_RAM_FUNCTION static void _FillCircle(int x0, int y0, int r)
{
    int i, x;
    int sqmax = r*r+r/2;
    int yMin, yMax;

    /* First step : find uppermost and lowermost coordinates */
    yMin = y0 - r;
    yMax = y0 + r;

    /* Use Clipping rect to reduce calculation (if possible) */
    if (gui_lib_ctx->clipRect_HL != NULL) {
        if (yMax > gui_lib_ctx->clip_y1)
            yMax = gui_lib_ctx->clip_y1;
        if (yMin < gui_lib_ctx->clip_y0)
            yMin = gui_lib_ctx->clip_y0;
    }

    /* Draw top half */
    for (i=0, x=r; i<r; i++) {
        int y = y0-i;
        if ((y >= yMin) && (y <= yMax)) {
            /* calc proper x-value */
            while ((i*i+x*x) >sqmax) {
                --x;
            }
            gui_lib_ctx->drawHLine (x0-x, y, x0+x);
        }
    }

    /* Draw bottom half */
    for (i=0, x=r; i<r; i++) {
        int y = y0 + i;
        if ((y >= yMin) && (y <= yMax)) {
            /* calc proper x-value */
            while ((i*i+x*x) >sqmax) {
                --x;
            }
            gui_lib_ctx->drawHLine (x0-x, y, x0+x);
        }
    }
}

SHARE_CACHE_RAM_FUNCTION static void _FillPolygon(gdi_point* paPoint, int NumPoints, int x, int y)
{
    int i;
    int x0,x1;

    /* Calc horizontal limits and init GUI_AA */
    x0 = x1 = paPoint[0].x;
    for (i=1; i< NumPoints; i++) {
        int x =  paPoint[i].x;
        if (x<x0)
            x0 = x;
        if (x>x1)
            x1 = x;
    }

    GUI_AA_Init((x0+x), (x1+x));

    /* Modify pointlist */
    for (i=0; i< NumPoints; i++) {
        paPoint[i].x *= _aalib_ctx.aaFactor;
        paPoint[i].y *= _aalib_ctx.aaFactor;
    }

    GUI_FillPolygon(paPoint, NumPoints, x * _aalib_ctx.aaFactor, y * _aalib_ctx.aaFactor);

    /* Restore pointlist */
    for (i=0; i< NumPoints; i++) {
        paPoint[i].x /= _aalib_ctx.aaFactor;
        paPoint[i].y /= _aalib_ctx.aaFactor;
    }

    /* Cleanup */
    GUI_AA_Exit();
}
#pragma pop


static void _CalcClipRect(void)
{
    _aalib_ctx.clipRect.x0 =  gui_lib_ctx->clipRect.x0    * _aalib_ctx.aaFactor;
    _aalib_ctx.clipRect.y0 =  gui_lib_ctx->clipRect.y0    * _aalib_ctx.aaFactor;
    _aalib_ctx.clipRect.x1 =  (gui_lib_ctx->clipRect.x1+1)* _aalib_ctx.aaFactor -1;
    _aalib_ctx.clipRect.y1 =  (gui_lib_ctx->clipRect.y1+1)* _aalib_ctx.aaFactor -1;
}


///////////////////////////////////////////////////////////////////////////////
void GUI_AA_Init(int x0, int x1)
{
    _aalib_ctx.aaFactor = GUI_AAFACTOR;

    if (x0 < 0)
        x0 = 0;

    if ((x1 - x0) > (GUI_AA_LINEBUFFER_SIZE-1))
        x1 = x0 + GUI_AA_LINEBUFFER_SIZE - 1;
    
    /* Is there anything to do at all ??? */
    if (x1 < x0) {
        x1 = x0;   /* Not really ... */
    }

    _aalib_ctx.drawHLine = gui_lib_ctx->drawHLine;
    _aalib_ctx.penSize = gui_lib_ctx->penSize;
    _aalib_ctx.pabAABuffer = _aalib_ctx.abAABuffer;
    _aalib_ctx._x0 = x0;
    _aalib_ctx._x1 = x1;
    
    _CleanLine();
    _CalcClipRect();

    gui_lib_ctx->clip_y0 = gui_lib_ctx->y0 * _aalib_ctx.aaFactor;
    gui_lib_ctx->clip_y1 = gui_lib_ctx->y1 * _aalib_ctx.aaFactor + _aalib_ctx.aaFactor - 1;
    gui_lib_ctx->clip_x0 = gui_lib_ctx->x0 * _aalib_ctx.aaFactor;                               // GUILIB_V2
    gui_lib_ctx->clip_x1 = gui_lib_ctx->x1 * _aalib_ctx.aaFactor + _aalib_ctx.aaFactor - 1;     // GUILIB_V2
    gui_lib_ctx->penSize *= _aalib_ctx.aaFactor;
    gui_lib_ctx->clipRect_HL = &_aalib_ctx.clipRect;
    gui_lib_ctx->drawHLine = _DrawHLine;
}


void GUI_AA_Exit(void)
{
    _FlushLine();
    
    /* restore previous settings */
    gui_lib_ctx->clipRect_HL = &gui_lib_ctx->clipRect;
    gui_lib_ctx->drawHLine = _aalib_ctx.drawHLine;
    gui_lib_ctx->penSize = _aalib_ctx.penSize;
    gui_lib_ctx->clip_y0 = gui_lib_ctx->y0;
    gui_lib_ctx->clip_y1 = gui_lib_ctx->y1;
    gui_lib_ctx->clip_x0 = gui_lib_ctx->x0;     // GUILIB_V2
    gui_lib_ctx->clip_x1 = gui_lib_ctx->x1;     // GUILIB_V2
}


///////////////////////////////////////////////////////////////////////////////
void GUI_AA_DrawArc(int x0, int y0, int rx, int ry, int a0, int a1)
{
    // init
    GUI_AA_Init(x0 - rx - gui_lib_ctx->penSize, x0 + rx + gui_lib_ctx->penSize);

    /* Convert into Hires coordinates (if not already done) */
    x0 *= _aalib_ctx.aaFactor;
    y0 *= _aalib_ctx.aaFactor;
    rx *= _aalib_ctx.aaFactor;
    ry *= _aalib_ctx.aaFactor;
    GUI_DrawArc(x0, y0, rx, ry, a0, a1);

    /* Cleanup */
    GUI_AA_Exit();
}


///////////////////////////////////////////////////////////////////////////////
void GUI_AA_DrawCircle(int x0, int y0, int r)
{
    GUI_AA_Init(x0-r-_aalib_ctx.penSize/2, x0+r+_aalib_ctx.penSize/2);

    x0 *= _aalib_ctx.aaFactor;
    y0 *= _aalib_ctx.aaFactor;
    r  *= _aalib_ctx.aaFactor;

    _DrawCircle(x0, y0, r);

    GUI_AA_Exit();
}



///////////////////////////////////////////////////////////////////////////////
void GUI_AA_FillCircle(int x0, int y0, int r)
{
    GUI_AA_Init(x0-r, x0+r);

    x0 *= _aalib_ctx.aaFactor;
    y0 *= _aalib_ctx.aaFactor;
    r  *= _aalib_ctx.aaFactor;

    _FillCircle(x0, y0, r);

    GUI_AA_Exit();
}

///////////////////////////////////////////////////////////////////////////////
void GUI_AA_DrawLine(int x0, int y0, int x1, int y1)
{
    int xMin, xMax;
    unsigned char PenSizeOld = gui_lib_ctx->penSize;
    unsigned char PenSizeHR  = PenSizeOld * _aalib_ctx.aaFactor;
    unsigned char OldPenShape = gui_lib_ctx->penShape;

    gui_lib_ctx->penShape = GUI_PS_FLAT;

    /* Calculate left and right borders for AA module */
    if (x0 < x1) {
        xMin = x0;
        xMax = x1;
    }
    else {
        xMin = x1;
        xMax = x0;
    }

    xMin -= PenSizeOld;
    xMax += PenSizeOld;

    /* Do the actual drawing */
    GUI_AA_Init(xMin, xMax);

    gui_lib_ctx->penSize = PenSizeHR;

    x0 *= _aalib_ctx.aaFactor;
    x1 *= _aalib_ctx.aaFactor;
    y0 *= _aalib_ctx.aaFactor;
    y1 *= _aalib_ctx.aaFactor;
    GUI_DrawLine(x0 , y0 , x1 ,  y1 );

    GUI_AA_Exit();

    /* Draw end points (can be optimized away in future, TBD*/
    switch (OldPenShape) {
        case GUI_PS_ROUND:
        {
            //int r = PenSizeOld / 2;
            //GUI_AA_FillCircle(x0/_aalib_ctx.aaFactor, y0/_aalib_ctx.aaFactor, r);
            //GUI_AA_FillCircle(x1/_aalib_ctx.aaFactor, y1/_aalib_ctx.aaFactor, r);
        }
        break;
    }
    
    gui_lib_ctx->penSize = PenSizeOld;
    gui_lib_ctx->penShape = OldPenShape;
}

void GUI_AA_DrawLineX10(int x0, int y0, int x1, int y1)
{
    int xMin, xMax;
    unsigned char PenSizeOld = gui_lib_ctx->penSize;
    unsigned char PenSizeHR  = PenSizeOld * _aalib_ctx.aaFactor;
    unsigned char OldPenShape = gui_lib_ctx->penShape;

    gui_lib_ctx->penShape = GUI_PS_FLAT;

    /* Calculate left and right borders for AA module */
    if (x0 < x1) {
        xMin = x0/10;
        xMax = x1/10;
    }
    else {
        xMin = x1/10;
        xMax = x0/10;
    }

    xMin -= PenSizeOld;
    xMax += PenSizeOld;

    /* Do the actual drawing */
    GUI_AA_Init(xMin, xMax);

    gui_lib_ctx->penSize = PenSizeHR;

    x0 = x0*_aalib_ctx.aaFactor/10;
    x1 = x1*_aalib_ctx.aaFactor/10;
    y0 = y0*_aalib_ctx.aaFactor/10;
    y1 = y1*_aalib_ctx.aaFactor/10;
    GUI_DrawLine(x0 , y0 , x1 ,  y1 );

    GUI_AA_Exit();

    /* Draw end points (can be optimized away in future, TBD*/
    switch (OldPenShape) {
        case GUI_PS_ROUND:
        {
            //int r = PenSizeOld / 2;
            //GUI_AA_FillCircle(x0/_aalib_ctx.aaFactor, y0/_aalib_ctx.aaFactor, r);
            //GUI_AA_FillCircle(x1/_aalib_ctx.aaFactor, y1/_aalib_ctx.aaFactor, r);
        }
        break;
    }
    
    gui_lib_ctx->penSize = PenSizeOld;
    gui_lib_ctx->penShape = OldPenShape;
}


///////////////////////////////////////////////////////////////////////////////
void GUI_AA_FillPolygon(gdi_point* paPoint, int NumPoints, int x, int y)
{
    gdi_point aiTemp[GUI_POLY_POINT_MAX];

    if (NumPoints > GUI_POLY_POINT_MAX) {
        return;
    }

    memcpy(aiTemp, paPoint, NumPoints*sizeof(gdi_point));
    _FillPolygon( aiTemp, NumPoints, x, y );
}

void GUI_AA_DrawPolyOutline(const gdi_point* pSrc, int NumPoints, int Thickness, int x, int y)
{
    unsigned int num;
    gdi_point aiTemp[2*GUI_POLY_POINT_MAX];

    if (NumPoints > (GUI_POLY_POINT_MAX-1)) {
        return;
    }

    GUI_EnlargePolygon(&aiTemp[0], pSrc, NumPoints, Thickness);
    for (num=0; num<NumPoints; num++) {
        aiTemp[NumPoints+num].x = pSrc[NumPoints-num-1].x;
        aiTemp[NumPoints+num].y = pSrc[NumPoints-num-1].y;
    }
    _FillPolygon(&aiTemp[0], 2*NumPoints, x, y);

    aiTemp[1].x = aiTemp[NumPoints-1].x;
    aiTemp[1].y = aiTemp[NumPoints-1].y;
    aiTemp[2].x = pSrc[NumPoints-1].x;
    aiTemp[2].y = pSrc[NumPoints-1].y;
    aiTemp[3].x = pSrc[0].x;
    aiTemp[3].y = pSrc[0].y;
    _FillPolygon(&aiTemp[0], 4, x, y);
}




