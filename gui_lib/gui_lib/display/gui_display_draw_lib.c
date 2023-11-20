
/***************************************************************************************/
//      date            auth            note
//--------------------------------------------------------------------------------------
//   2022-11-28       Taylor.Le         支持屏幕剪切区 （GUILIB_V2）
//
/***************************************************************************************/

#include "debug_info.h"
#include "math.h"

#include "gui_display_draw_lib.h"


#define MY_PI   (-3.1415926f)


static gdi_lib_ctx  _gui_lib_ctx;
gdi_lib_ctx*  gui_lib_ctx = &_gui_lib_ctx;


#pragma push
#pragma Otime
SHARE_CACHE_RAM_FUNCTION static void _drawHLineOpacity(int x0, int y, int x1, int opacity)
{
    RETURN_IF_Y_OUT();
    if (x0 > x1) {
        int tmp = x0;
        x0 = x1;
        x1 = tmp;
    }
    RETURN_IF_X_OUT_RANG();
    
    CLIP_X();

#if COLOR_RGB_MODE == COLOR_RGB_MODE_565
    unsigned short* frame_buff = (unsigned short*)(_gui_lib_ctx.frame_buffer + UI_CHARGE_XY(x0, y));
    unsigned int R = ((_gui_lib_ctx.color & 0x001F) << 3)*opacity;
    unsigned int G = ((_gui_lib_ctx.color & 0x07E0) >> 5)*opacity;
    unsigned int B = ((_gui_lib_ctx.color & 0xF800) >> 8)*opacity;
    unsigned int r, g, b;
    GUI_COLOR color;
    unsigned short tmp;
    
    opacity = 100 - opacity;
    for (; x0<=x1; x0++) {
        tmp = *frame_buff;
        color = (tmp >> 8) + (tmp << 8);
        r = R + ((color & 0x001F) << 3)*opacity;
        g = G + ((color & 0x07E0) >> 5)*opacity;
        b = B + ((color & 0xF800) >> 8)*opacity;
        r = ((r/100) >> 3)&0x001F;
        g = ((g/100) << 5)&0x07E0;
        b = ((b/100) << 8)&0xF800;
        tmp = r + g + b;
        color = (tmp >> 8) + (tmp << 8);
        *frame_buff ++ = color;
    }
#else
    unsigned char* frame_buff = _gui_lib_ctx.frame_buffer + UI_CHARGE_XY(x0, y);
    unsigned char color_r = ((_gui_lib_ctx.color >> 0)&0xFF)*opacity;
    unsigned char color_g = ((_gui_lib_ctx.color >> 8)&0xFF)*opacity;
    unsigned char color_b = ((_gui_lib_ctx.color >>16)&0xFF)*opacity;
    
    opacity = 100 - opacity;
    for (; x0<=x1; x0++, frame_buff+=COLOR_RGB_PIXEL) {
        frame_buff[0] = color_b + frame_buff[0]*opacity;
        frame_buff[1] = color_g + frame_buff[1]*opacity;
        frame_buff[2] = color_r + frame_buff[2]*opacity;
        frame_buff += 3;
    }
#endif
}

SHARE_CACHE_RAM_FUNCTION static void _drawHLine(int x0, int y, int x1)
{
    RETURN_IF_Y_OUT();
    if (x0 > x1) {
        int tmp = x0;
        x0 = x1;
        x1 = tmp;
    }
    RETURN_IF_X_OUT_RANG();
    CLIP_X();

#if COLOR_RGB_MODE == COLOR_RGB_MODE_565
    unsigned short* frame_buff = (unsigned short*)(_gui_lib_ctx.frame_buffer + UI_CHARGE_XY(x0, y));
    unsigned char color_h = (_gui_lib_ctx.color >> 8)&0xFF;
    unsigned char color_l = _gui_lib_ctx.color & 0xFF;
    unsigned short data = color_h + (color_l << 8);
    
    for (; x0<=x1; x0++) {
        *frame_buff ++ = data;
    }

#else
    unsigned char* frame_buff = _gui_lib_ctx.frame_buffer + UI_CHARGE_XY(x0, y);
    unsigned char color_r = (_gui_lib_ctx.color >> 0)&0xFF;
    unsigned char color_g = (_gui_lib_ctx.color >> 8)&0xFF;
    unsigned char color_b = (_gui_lib_ctx.color >>16)&0xFF;
    
    for (; x0<=x1; x0++, frame_buff+=COLOR_RGB_PIXEL) {
        frame_buff[0] = color_b;
        frame_buff[1] = color_g;
        frame_buff[2] = color_r;
    }
#endif
}

SHARE_CACHE_RAM_FUNCTION static void _drawVLine(int x, int y0, int y1)
{
    RETURN_IF_X_OUT();
    if (y0 > y1) {
        int tmp = y0;
        y0 = y1;
        y1 = tmp;
    }
    RETURN_IF_Y_OUT_RANG();
    CLIP_Y();

#if COLOR_RGB_MODE == COLOR_RGB_MODE_565
    unsigned short* frame_buff = (unsigned short*)(_gui_lib_ctx.frame_buffer + UI_CHARGE_XY(x, y0));
    unsigned char color_h = (_gui_lib_ctx.color >> 8)&0xFF;
    unsigned char color_l = _gui_lib_ctx.color & 0xFF;
    unsigned short data = color_h + (color_l << 8);
    
    for (; y0<=y1; y0++, frame_buff+=LCD_SIZE_WIDTH) {
        *frame_buff = data;
    }
    
#else
    unsigned char* frame_buff = _gui_lib_ctx.frame_buffer + UI_CHARGE_XY(x, y0);
    unsigned char color_r = (_gui_lib_ctx.color >> 0)&0xFF;
    unsigned char color_g = (_gui_lib_ctx.color >> 8)&0xFF;
    unsigned char color_b = (_gui_lib_ctx.color >>16)&0xFF;
    for (; y0<=y1; y0++, frame_buff+=(LCD_SIZE_WIDTH*COLOR_RGB_PIXEL)) {
        frame_buff[0] = color_b;
        frame_buff[1] = color_g;
        frame_buff[2] = color_r;
    }
#endif
}

SHARE_CACHE_RAM_FUNCTION static GUI_COLOR _getPixel(int x, int y)
{
    if (IS_Y_OUT()) return _gui_lib_ctx.color;
    if (IS_X_OUT()) return _gui_lib_ctx.color;

    unsigned char* frame_buff = _gui_lib_ctx.frame_buffer + UI_CHARGE_XY(x, y);
    GUI_COLOR  color;

#if COLOR_RGB_MODE == COLOR_RGB_MODE_565
    color = (frame_buff[0] << 8) + frame_buff[1];
#else
    color = (frame_buff[0] << 16) + (frame_buff[1] << 8) + frame_buff[0];
#endif

    return color;
}

SHARE_CACHE_RAM_FUNCTION static void _setPixel(int x, int y, GUI_COLOR color)
{
    RETURN_IF_Y_OUT();
    RETURN_IF_X_OUT();

    unsigned char* frame_buff = _gui_lib_ctx.frame_buffer + UI_CHARGE_XY(x, y);
#if COLOR_RGB_MODE == COLOR_RGB_MODE_565
    frame_buff[0] = color >> 8;
    frame_buff[1] = color;
#else
    frame_buff[0] = color >> 16;
    frame_buff[1] = color >> 8;
    frame_buff[2] = color;
#endif
}
#pragma pop


////////////////////////////////////////////////////////////////////////////////
void gui_initContext(void)
{
    _gui_lib_ctx.clipRect_HL = &_gui_lib_ctx.clipRect;
    _gui_lib_ctx.drawHLine = _drawHLine;
    _gui_lib_ctx.drawVLine = _drawVLine;
    _gui_lib_ctx.getPixel  = _getPixel;
    _gui_lib_ctx.setPixel  = _setPixel;
    _gui_lib_ctx.clipRect.x0 = 0;
    _gui_lib_ctx.clipRect.y0 = 0;
    _gui_lib_ctx.clipRect.x1 = LCD_SIZE_WIDTH-1;
    _gui_lib_ctx.clipRect.y1 = LCD_SIZE_HEIGHT-1;
    _gui_lib_ctx.penSize = 1;
    _gui_lib_ctx.penShape = GUI_PS_ROUND;
    _gui_lib_ctx.scale = 1.0f;
}

void gui_setClip(short x0, short y0, short x1, short y1)
{
    _gui_lib_ctx.clipRect.x0 = ((x0 < 0) ? 0 : x0);     // Taylor.Le.
    _gui_lib_ctx.clipRect.y0 = y0;
    _gui_lib_ctx.clipRect.x1 = x1;
    _gui_lib_ctx.clipRect.y1 = y1;
}

void gui_setClipRect(gdi_rect* rect)
{
    _gui_lib_ctx.clipRect.x0 = ((rect->x0 < 0) ? 0 : rect->x0);     // Taylor.Le.
    _gui_lib_ctx.clipRect.y0 = rect->y0;
    _gui_lib_ctx.clipRect.x1 = rect->x1;
    _gui_lib_ctx.clipRect.y1 = rect->y1;
}

//#if GUILIB_V2
void gui_setFrameBufferRect(unsigned char* buff, short x, short y, short w, short h)
{
    short x1 = x+w-1;
    short y1 = y+h-1;

    //SYS_DEBUG("Frame: %d, %d, %d, %d", x, y, w, h);
    
    _gui_lib_ctx.frame_buffer = buff;
    
    _gui_lib_ctx.y0 = y;
    _gui_lib_ctx.y1 = y1;
    _gui_lib_ctx.clip_y0 = y;
    _gui_lib_ctx.clip_y1 = y1;
    _gui_lib_ctx.clipRect.y0 = y;
    _gui_lib_ctx.clipRect.y1 = y1;
    
    _gui_lib_ctx.x0 = x;
    _gui_lib_ctx.x1 = x1;
    _gui_lib_ctx.clip_x0 = x;
    _gui_lib_ctx.clip_x1 = x1;
    _gui_lib_ctx.clipRect.x0 = x;
    _gui_lib_ctx.clipRect.x1 = x1;

#if defined(__CW_JL__)
    _gui_lib_ctx.bw = ((w * COLOR_RGB_PIXEL + 3)/4) * 4;        // 4 bytes alin
#else
    _gui_lib_ctx.bw = (w * COLOR_RGB_PIXEL);    // byte alin
#endif
    _gui_lib_ctx.bh = h;
}
//#endif

void gui_setFrameBuffer(unsigned char* buff, short y0, short y1)
{
#if 1//GUILIB_V2
    gui_setFrameBufferRect(buff, 0, y0, LCD_SIZE_WIDTH, y1-y0+1);
#else
    //SYS_DEBUG("Frame: %d, %d", y0, y1);
    _gui_lib_ctx.frame_buffer = buff;

    _gui_lib_ctx.y0 = y0;
    _gui_lib_ctx.y1 = y1;
    _gui_lib_ctx.clip_y0 = y0;
    _gui_lib_ctx.clip_y1 = y1;
    _gui_lib_ctx.clipRect.y0 = y0;
    _gui_lib_ctx.clipRect.y1 = y1;
#endif
}

void gui_setScale(float scale)
{
    _gui_lib_ctx.scale = scale;
}

GUI_COLOR gui_setColor(GUI_COLOR color)
{
    GUI_COLOR cl = _gui_lib_ctx.color;
    _gui_lib_ctx.color = color;
    return cl;
}

unsigned char gui_setLineStyle(unsigned char lineStyle) {
    unsigned char ls = _gui_lib_ctx.lineStyle;
    _gui_lib_ctx.lineStyle = lineStyle;
    return ls;
}

unsigned char gui_setPenSize(unsigned char penSize) {
    unsigned char ps = _gui_lib_ctx.penSize;
    _gui_lib_ctx.penSize = penSize;
    return ps;
}

unsigned char gui_setPenShape(unsigned char penShape) {
    unsigned char ps = _gui_lib_ctx.penShape;
    _gui_lib_ctx.penShape = penShape;
    return ps;
}

unsigned char gui_setDrawMode(unsigned char drawMode) {
    unsigned char dm = _gui_lib_ctx.drawMode;
    _gui_lib_ctx.drawMode = drawMode;
    return dm;
}

//牛顿法求开方
float gui_sqrt( float number )
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y   = number;
	i   = * ( long * ) &y;   // evil floating point bit level hacking
	i   = 0x5f3759df - ( i >> 1 ); // what the fuck?
	y   = * ( float * ) &i;
	y   = y * ( threehalfs - ( x2 * y * y ) ); // 1st iteration
	y   = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed
	y = 1/y;
	return y;
}

/////////////////////////////////////////////////////////////////////////////////////////
static void GL_SwapInt(int* pa, int* pb)
{
    int t = *pa;
    *pa = *pb;
    *pb = t;
}

static int Abs(int v)
{
    return ((v>0) ? v : -v);
}


/*
 *************************************************
 *                                               *
 *           Trigonometric functions             *
 *                                               *
 *************************************************
All trigonometric functions are for internal usage only and
use the following conventions:
      Angles: 4096 <==> 360?
*/

/*
 *********************************
 *                               *
 *      sin / cos (internal)     *
 *                               *
 *********************************
  Angle : 90/1024?
  Data  : 1/1024
*/
static const unsigned short aSin[] = {
    0,       /* 1/16 *90?  */
    100,     /* 1/16 *90?  */
    200,     /* 2/16 *90? */
    297,     /* 3/16 *90? */
    392,     /* 4/16 *90? */
    483,     /* 5/16 *90? */
    569,     /* 6/16 *90? */
    650,     /* 7/16 *90? */
    724,     /* 8/16 *90? */
    792,     /* 9/16 *90? */
    851,     /* 10/16 *90?*/
    903,     /* 11/16 *90?*/
    946,     /* 12/16 *90?*/
    980,     /* 13/16 *90?*/
    1004,    /* 14/16 *90?*/
    1019,    /* 15/16 *90?*/
    1024     /* 16/16 *90?*/
};


static int GUI_sin(int angle)
{
    char IsNeg =0;
    int i;
    unsigned short Faktor;
    unsigned int t;

    angle &= ((1<<12)-1);  /* reduce to 0-360 degrees */
    if (angle> 2* GUI_90DEG) {
        angle -= 2* GUI_90DEG;
        IsNeg =1;
    }
    if (angle> GUI_90DEG) {  /* between 90-180 */
        angle = 2*GUI_90DEG-angle;   /* use sine symetry */
    }
    /* Now angle is reduced to 0?<= <= 90?*/
    i = angle>>6;
    {
        Faktor = (unsigned short)((1<<6)-(angle&((1<<6)-1)));
        t = aSin[i]*(unsigned int)Faktor;
        if (Faktor !=(1<<6)) {
            t += aSin[i+1]*((1<<6)-Faktor);
        }
    }
    t = (t+(1<<5)) >>6;   /* divide,incl. rounding */
    return (IsNeg) ? 0-t : t;
}

static int GUI_cos(int angle)
{
    return GUI_sin(angle+GUI_90DEG);
}


/*
 *********************************
 *                               *
 *       atan()   (internal)     *
 *                               *
 *********************************
 * Angle : 360/4096?
*/
const short aTan[] = {
    0,       /* atan(0/16) */
    41,      /* atan(1/16) */
    81,      /* atan(2/16) */
    121,     /* atan(3/16) */
    160,     /* atan(4/16) */
    197,     /* atan(5/16) */
    234,     /* atan(6/16) */
    269,     /* atan(7/16) */
    302,     /* atan(8/16) */
    334,     /* atan(9/16) */
    364,     /* atan(10/16) */
    393,     /* atan(11/16) */
    419,     /* atan(12/16) */
    445,     /* atan(13/16) */
    469,     /* atan(14/16) */
    491,     /* atan(15/16) */
    512      /* atan(1) = 45?= 512/1024 */
};


/* Calculate arctan of q, where q is any where between 0 and 1024 */
static int _atan0_45(int q)
{
    int r;
    int i, Faktor;

    /* Now angle is reduced to 0?<= <= 90?==>  0 <= <= 256*/
    q >>=2;    /* make sure we do not exceed 16 bits in calculations */
    i = q>>4;
    Faktor = (1<<4)-(q&((1<<4)-1));
    r = aTan[i]*Faktor;
    if (Faktor !=(1<<4)) {
        r += aTan[i+1]*((1<<4)-Faktor);
    }
    r = (r+(1<<3))/(1<<4);   /* divide  incl. rounding */
    return r;
}

static int _atan2(int x, int y)
{
    unsigned char q =0;
    int angle;

    /* first make sure we are in angle between 0 and 45?*/
    if (x<0) {
        q=1;
        x=-x;
    }
    if (y<0) {
        q |= (1<<1);
        y=-y;
    }
    if (y>x) {
        int t = y;
        y=x;
        x=t;
        q |= (1<<2);  
    }
    y <<=10;
    y += (x/2);
    y /= x;
    angle = _atan0_45(y);
    if (q&(1<<2)) { /* y/x reverse ? */
        angle = GUI_90DEG-angle;
    }
    if (q&1) {  /* xreverse ? */
        angle = GUI_180DEG-angle;
    }
    if (q&(1<<1)) { /* y-reverse ? */
        angle = GUI_360DEG-angle;
    }
    return angle;
}

static int SetLineColor(int i)
{
    switch (_gui_lib_ctx.lineStyle) {
    case GUI_LS_DASH:
        i = (i+6)%16;
        return (i<12);

    case GUI_LS_DOT:
        i %= 4;
        return (i<2);

    case GUI_LS_DASHDOT:
        i %= 20;
        if (i<12)
            return 1;
        else if ((i>=16) && (i<18))
            return 1;
        return 0;

    case GUI_LS_DASHDOTDOT:
        i %= 24;
        if (i<12)
            return 1;
        else if ((i>=16) && (i<18))
            return 1;
        else if ((i>=20) && (i<22))
            return 1;
        else 
            return 0;
    }

    return 0;
}

static void CalcOrto(int xDiff, int yDiff, int r, int*px, int*py)
{
    int x,y;
    int Angle = _atan2(xDiff, yDiff);
    Angle+= GUI_90DEG;
    x = ( r*(int)GUI_cos(Angle));
    y = ( r*(int)GUI_sin(Angle));
    x = (x<0) ? -((-x+512)>>10) : ((x+512)>>10);
    y = (y<0) ? -((-y+512)>>10) : ((y+512)>>10);
    *px = x;
    *py = y;
}


static void GL_DrawPoint(int x, int y)
{
    if (_gui_lib_ctx.penSize == 1) {
        gui_lib_ctx->setPixel(x,y, _gui_lib_ctx.color);
    }
    else {
        GUI_FillCircle(x,y,(_gui_lib_ctx.penSize-1)/2);
    }
}


/*
 *************************************************
 *                                               *
 *             DrawLine, public                  *
 *                                               *
 *************************************************
Draw end points of the line.
In most cases, this is a circle.
*/
static void _DrawLineEnd(int x0, int y0)
{
    switch (_gui_lib_ctx.penShape) {
    case GUI_PS_ROUND:
        GL_DrawPoint(x0,y0);
        break;
    case GUI_PS_FLAT:
        break;
    }
}

/*
 *************************************************
 *                                               *
 *             DrawLine, internal, 1 pixel       *
 *                                               *
 *************************************************
*/
void GL_DrawLine1(int x0, int y0, int x1, int y1)
{
    int xdiff = x1-x0;
    int ydiff = y1-y0;
    int xdiffby2;
    int i;
    char Swapped =0;

    /* check if no line */
    if (!(xdiff|ydiff)) {
        GL_DrawPoint(x0,y0);
        return;
    }

    /* check if we swap x and y for calculation */
    if (Abs(xdiff) < Abs(ydiff)) {
        GL_SwapInt(&xdiff,&ydiff);
        GL_SwapInt(&x0,&y0);
        GL_SwapInt(&x1,&y1);
        Swapped =1;
    }

    /* make sure line direction is positive */
    if (xdiff!=Abs(xdiff)) {
        xdiff = -xdiff;
        ydiff = -ydiff;
        GL_SwapInt(&x0,&x1);
        GL_SwapInt(&y0,&y1);
    }
    xdiffby2 = xdiff/2;
    if (ydiff<0)
        xdiffby2 = -xdiffby2;

    /* Draw pixel by pixel solid*/
    if (_gui_lib_ctx.lineStyle == GUI_LS_SOLID) {
        for (i=0; i<=xdiff; i++) {
            int l = ydiff*i+xdiffby2;
            int y = (ABS(l)<32767) ? (y0 + l/xdiff) : (y0 + l/xdiff);
            if (!Swapped)
                gui_lib_ctx->setPixel(x0+i, y, _gui_lib_ctx.color);
            else
                gui_lib_ctx->setPixel(y, x0+i, _gui_lib_ctx.color);
        }
        /* Draw pixel by pixel with fill style */
    }
    else {
        for (i=0; i<=xdiff; i++) {
            long l = ((long)ydiff)*i+xdiffby2;
            int y = (ABS(l)<32767) ? (y0 + l/xdiff) : (y0 + l/xdiff);
            if (!SetLineColor(i)) {
                if (!Swapped)
                    gui_lib_ctx->setPixel(x0+i, y, _gui_lib_ctx.color);
                else
                    gui_lib_ctx->setPixel(y, x0+i, _gui_lib_ctx.color);
            }
        }
    }
}


/*
 *************************************************
 *                                               *
 *             DrawLine, public                  *
 *                                               *
 *************************************************
*/
static void GL_DrawLine(int x0, int y0, int x1, int y1)
{
    //SYS_DEBUG("DrawLine: %d, %d, %d, %d", x0, y0, x1, y1);

    if (_gui_lib_ctx.penSize == 1) {
        GL_DrawLine1(x0,y0,x1,y1);
    }
    else {
        int xdiff, ydiff;
        xdiff = x0-x1;
        ydiff = y0-y1;
        if (xdiff | ydiff) {    
            gdi_point Poly[4];
            int xOff, yOff;
            int xOffP, yOffP, xOffM, yOffM;

            CalcOrto(x0-x1,y0-y1, (int)(_gui_lib_ctx.penSize-1), &xOff, &yOff);

            /* Do rounding for offsets */
            if (xOff >0) {
                xOffP = (xOff+1)/2;
                xOffM =  xOff   /2;
            }
            else {
                xOffP =   xOff/2;
                xOffM =  (xOff-1)   /2;
            }
            if (yOff >0) {
                yOffP = (yOff+1)/2;
                yOffM =  yOff   /2;
            }
            else {
                yOffP =   yOff/2;
                yOffM =  (yOff-1)   /2;
            }
            Poly[0].x = x0+xOffP;
            Poly[0].y = y0+yOffP;
            Poly[1].x = x0-xOffM; 
            Poly[1].y = y0-yOffM; 
            Poly[2].x = x1-xOffM;
            Poly[2].y = y1-yOffM;
            Poly[3].x = x1+xOffP; 
            Poly[3].y = y1+yOffP;
            GUI_FillPolygon(&Poly[0], 4, 0,0);
            _DrawLineEnd(x0,y0);
            _DrawLineEnd(x1,y1);
        }
    }
}

void GL_MoveTo(int x, int y)
{
    _gui_lib_ctx.drawPosX = x;
    _gui_lib_ctx.drawPosY = y;
}


void GL_DrawLineTo(int x, int y)
{
    GL_DrawLine (_gui_lib_ctx.drawPosX, _gui_lib_ctx.drawPosY, x, y); 
    _gui_lib_ctx.drawPosX = x;
    _gui_lib_ctx.drawPosY = y;
}


static void GL_DrawLineToNM(int x, int y)
{
    GL_DrawLine(_gui_lib_ctx.drawPosX, _gui_lib_ctx.drawPosY, x, y); 
}


static void GL_DrawPolygon(const gdi_point* pPoints, int NumPoints, int x0, int y0)
{
    const gdi_point* pPoint = pPoints;
    GL_MoveTo(pPoint->x+x0, pPoint->y+y0);
    while (--NumPoints >0) {
        pPoint++;
        GL_DrawLineTo(pPoint->x+x0, pPoint->y+y0);
    }

    /* Now draw closing line unless it has already been closed */
    if ( (pPoint->x != pPoints->x)||(pPoint->y != pPoints->y))
    {
        GL_DrawLineTo(pPoints->x+x0, pPoints->y+y0);
    }
}

static void GL_DrawRect(int x0, int y0, int x1, int y1)
{
    char ps = _gui_lib_ctx.penShape;
    _gui_lib_ctx.penShape = GUI_PS_FLAT;
    GL_DrawLine(x0,y0,x1,y0);
    GL_DrawLine(x1,y0,x1,y1);
    GL_DrawLine(x1,y1,x0,y1);
    GL_DrawLine(x0,y1,x0,y0);
    _gui_lib_ctx.penShape = ps;
}

static void GL_DrawLineRelNM(int dx, int dy)
{
    GL_DrawLine(_gui_lib_ctx.drawPosX, _gui_lib_ctx.drawPosY, _gui_lib_ctx.drawPosX+dx, _gui_lib_ctx.drawPosY+dy);
}

void GUI_DrawPolygon(const gdi_point* pPoints, int NumPoints, int x0, int y0)
{
    GL_DrawPolygon (pPoints, NumPoints, x0, y0);
}

void GUI_DrawLineRel(int dx, int dy)
{
    GL_DrawLineRelNM(dx,dy);
    GUI_MoveRel(dx,dy);
}

void GUI_DrawLineTo(int x, int y)
{
    GL_DrawLineToNM(x,y);
    GL_MoveTo(x,y);
}

void GUI_MoveRel(int dx, int dy)
{
    _gui_lib_ctx.drawPosX += dx;
    _gui_lib_ctx.drawPosY += dy;
}

void GUI_MoveTo(int x, int y)
{
    GL_MoveTo(x,y);
}

void GUI_DrawLine(int x0, int y0, int x1, int y1)
{
    GL_DrawLine (x0, y0, x1, y1);
}

void GUI_DrawRect(int x0, int y0, int x1, int y1)
{
    GL_DrawRect(x0, y0, x1, y1);
}

void GUI_DrawPoint(int x, int y)
{
    GL_DrawPoint(x, y);
}

void GUI_DrawFillRect(int x0, int y0, int x1, int y1)
{
    for (; y0 <= y1; y0++) {
        _gui_lib_ctx.drawHLine(x0, y0, x1);
    }
}

void GUI_DrawFillRectOpacity(int x0, int y0, int x1, int y1, int opacity)
{
    for (; y0 <= y1; y0++) {
        _drawHLineOpacity(x0, y0, x1, opacity);
    }
}

void GUI_DrawStyleLineH(short x0, short x1, short y, short show_pixels, short skip_pixels)
{
    while((x0+show_pixels) < x1){
    	_gui_lib_ctx.drawHLine(x0, y, x0+show_pixels);
        x0 += show_pixels;
        x0 += skip_pixels;
    }

    if (x0 < x1) {
    	_gui_lib_ctx.drawHLine(x0, y, x1);
    }
}

void GUI_DrawStyleLineV(short y0, short y1, short x, short show_pixels, short skip_pixels)
{
    while((y0+show_pixels) < y1){
    	_gui_lib_ctx.drawVLine(x, y0, y0+show_pixels);
        y0 += show_pixels;
        y0 += skip_pixels;
    }

    if (y0 < y1) {
    	_gui_lib_ctx.drawVLine(x, y0, y1);
    }
}

void GUI_DrawStyleLine(int x0, int y0, int x1, int y1, short show_pixels, short skip_pixels)
{
    if (x0 == x1) {
        GUI_DrawStyleLineV(y0, y1, x0, show_pixels, skip_pixels);
    }
    else if (y0 == y1) {
        GUI_DrawStyleLineH(x0, x1, y0, show_pixels, skip_pixels);
    }
}



