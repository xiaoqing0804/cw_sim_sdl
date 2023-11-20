
#include <math.h>
#include "gui_display_draw_lib.h"


#define GUI_FP_MAXCOUNT 12

static int   GL_FP_Cnt;
static short _aX[GUI_FP_MAXCOUNT];

#pragma push
#pragma Otime
// 
SHARE_CACHE_RAM_FUNCTION static void _DrawHLine(int x0, int y, int x1)
{
    if (x0 < x1) {
        gui_lib_ctx->drawHLine(x0, y, x1);
    }
    else {
        gui_lib_ctx->drawHLine(x1, y, x0);
    }
}


/********************************************************
*
*        _CheckYInterSect

  This function returns the x-coordinate of the intersection
  of the given line at the given y-coordinate.
  If there is no intersection, GUI_XMAX is returned.
  This routine does not work for horizontal lines, as there
  would be more than a single point as intersection. This situation
  needs to be checked prior to calling the routine.
  Returns:
    0 if no intersection
    1 if we have an intersection
*/
SHARE_CACHE_RAM_FUNCTION static int _CheckYInterSect(int y, int* px, const gdi_point* paPoint0, const gdi_point* paPoint1)
{
    int x0, y0, x1, y1;
    if (paPoint0->y <= (paPoint1)->y) {
        y0 = paPoint0->y;
        if (y0 > y)      /* Check if there is an intersection ... (early out) */
            return 0;
        y1 = paPoint1->y;
        if (y1 < y)      /* Check if there is an intersection ... (early out) */
            return 0;
        x0 = paPoint0->x;
        x1 = paPoint1->x;
    }
    else {
        y0 = paPoint1->y;
        if (y0 > y)      /* Check if there is an intersection ... (early out) */
            return 0;
        y1 = paPoint0->y;
        if (y1 < y)      /* Check if there is an intersection ... (early out) */
            return 0;
        x0 = paPoint1->x;
        x1 = paPoint0->x;
    }

    /* Calculate intersection */
    {
        int Mul = (x1 - x0) * (y - y0);
        if (Mul > 0) {
            Mul += (y1 - y0) >> 1;	          /* for proper rounding */
        }
        else {
            Mul -= ((y1 - y0) >> 1) - 1;	    /* for proper rounding */
        }
        x0 += Mul / (y1 - y0);
    }
    *px = x0;
    return 1;
} 


/********************************************************
  This function adds a point into the sorted array
*/
SHARE_CACHE_RAM_FUNCTION static void _Add(int x)
{
    if (GL_FP_Cnt < GUI_FP_MAXCOUNT) {
        int i;
        /* Move all entries to the right (bigger x-value) */
        for (i=GL_FP_Cnt; i ; i--) {
            if (_aX[i-1] < x)
                break;
            _aX[i] = _aX[i-1];
        }
        /* Insert new entry */
        _aX[i]    = x;
        GL_FP_Cnt++;
    }
}


/********************************************************
  This function initialise the sorted array
*/
SHARE_CACHE_RAM_FUNCTION static void _Init(void)
{
    GL_FP_Cnt = 0;
}


/********************************************************
  This function draw lines between points in the array
*/
SHARE_CACHE_RAM_FUNCTION static void _Flush(int x0, int y)
{
    int i, x;
    char On=0;
    for (i=0; i<GL_FP_Cnt; i++) {
        int xNew = _aX[i];
        if (On) {
            gui_lib_ctx->drawHLine(x0 + x, y, x0 + xNew);
        }
        On ^= 1;
        x = xNew;
    }
}


/********************************************************
  This function decides either if there a V-point or a
  X-point. An X-point is added to the array, a V-point
  is drawn.
*/
SHARE_CACHE_RAM_FUNCTION static void _AddPoint(int x, int y, int y0, int y1, int xOff, int yOff)
{
    if ((y0 ^ y1) >= 0) {
        x += xOff;
        gui_lib_ctx->drawHLine(x, y + yOff, x);    // V-point, not crossing the polygon
    }
    else {
        _Add(x);
    }
}


/********************************************************
  Find previous point which is not on the same height
*/
SHARE_CACHE_RAM_FUNCTION static int _GetPrevPointDiffy(const gdi_point* paPoint, int i, const int NumPoints, const int y0)
{
    int j, y1;
    for (j = 0; j < (NumPoints - 1) ; j++) {
        i = (i != 0) ? i - 1 : NumPoints - 1;
        y1 = (paPoint + i)->y;
        if (y1 != y0) {
            return y1;
        }
    }
    return y0;
}


/********************************************************
  This function calculates the polygon
*/
SHARE_CACHE_RAM_FUNCTION static void GL_FillPolygon(const gdi_point* paPoint, int NumPoints, int xOff, int yOff)
{
    int i, y;
    int yMin = GUI_YMAX;
    int yMax = GUI_YMIN;

    /* First step : find uppermost and lowermost coordinates */
    for (i=0; i<NumPoints; i++) {
        y = (paPoint + i)->y;
        if (y < yMin)
            yMin = y;
        if (y > yMax)
            yMax = y;
    }

    /* Use Clipping rect to reduce calculation (if possible) */
    if (gui_lib_ctx->clipRect_HL != NULL) {
        if (yMax > (gui_lib_ctx->clip_y1 - yOff))
            yMax = (gui_lib_ctx->clip_y1 - yOff);
        if (yMin < (gui_lib_ctx->clip_y0 - yOff))
            yMin = (gui_lib_ctx->clip_y0 - yOff);
    }

    /* Second step: Calculate and draw horizontal lines */
    for (y=yMin; y<=yMax; y++) {
        _Init();

        /* find next intersection and count lines*/
        for (i=0; i<NumPoints; i++) {
            int i1 = (i < (NumPoints - 1)) ? i + 1 : 0;
            int y0 = (paPoint + i )->y;
            int y1 = (paPoint + i1)->y;
            /* Check if starting point is on line */
            if (y0 == y) {
                if (y1 == y) {  /* Add the entire line */
                    _DrawHLine((paPoint + i )->x + xOff , y + yOff, (paPoint + i1)->x + xOff);
                }
                else {        /* Add only one point */
                    int yPrev = _GetPrevPointDiffy(paPoint, i, NumPoints, y);
                    if (yPrev != y) {
                        _AddPoint((paPoint + i)->x, y, yPrev - y, y1 - y, xOff, yOff);
                    } 
                }
            }
            else if (y1 != y) {  /* Ignore if end-point is on the line */
                if (((y1 >= y) && (y0 <= y)) || ((y0 >= y) && (y1 <= y))) {
                    int xIntersect;
                    if (_CheckYInterSect(y, &xIntersect, paPoint + i, paPoint + i1)) {
                        _Add(xIntersect);
                    }
                }
            }
        }
        _Flush(xOff, y + yOff);
    }  
}
#pragma pop

/*******************************************************************
*
*                  GUI_EnlargePolygon
*
********************************************************************
*/
void GUI_FillPolygon  (const gdi_point* pPoints, int NumPoints, int x0, int y0)
{
    GL_FillPolygon (pPoints, NumPoints, x0, y0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    float x,y;
} tfPoint;

static int fround(float f)
{
    if (f>0)
        return f+0.5f;
    return f-0.5f;
}

static void Normalize(tfPoint* pfPoint)
{
    float fx = pfPoint->x;
    float fy = pfPoint->y;
    float r = gui_sqrt(fx*fx + fy*fy);   // sqrt(fx*fx + fy*fy);
    if (r > 0) {
        pfPoint->x = fx/r;
        pfPoint->y = fy/r;
    }
}

static void ReverseLen(tfPoint* pfPoint)
{
    float fx = pfPoint->x;
    float fy = pfPoint->y;
    float r = gui_sqrt(fx*fx/2 + fy*fy/2);   // sqrt(fx*fx/2 + fy*fy/2);
    if (r > 0) {
        pfPoint->x = fx/r/r;
        pfPoint->y = fy/r/r;
    }
}

static void GetVect(tfPoint* pfPoint, const gdi_point* pSrc, int NumPoints, int Index)
{
    int Off0 = (Index + NumPoints-1) % NumPoints;
    int Off1 = Index % NumPoints;
    pfPoint->x = pSrc[Off1].x - pSrc[Off0].x; 
    pfPoint->y = pSrc[Off1].y - pSrc[Off0].y; 
}


/*******************************************************************
*
*                  GUI_EnlargePolygon
*
********************************************************************
*/
void GUI_EnlargePolygon(gdi_point* pDest, const gdi_point* pSrc, int NumPoints, int Len)
{
    int j;

    /* Calc destination points */
    for (j=0; j<NumPoints; j++) {
        int x, y;
        tfPoint aVect[2];

        /* Get the vectors */
        GetVect(&aVect[0], pSrc, NumPoints, j);
        GetVect(&aVect[1], pSrc, NumPoints, j+1);

        /* Normalize the vectors and add vectors */
        Normalize(&aVect[0]);
        Normalize(&aVect[1]);
        aVect[0].x += aVect[1].x;
        aVect[0].y += aVect[1].y;

        /* Resulting vector needs to be normalized again */
        ReverseLen(&aVect[0]);
        x =  fround(aVect[0].y * Len);
        y = -fround(aVect[0].x * Len);

        /* Store destination */
        (pDest+j)->x = (pSrc+j)->x + x;
        (pDest+j)->y = (pSrc+j)->y + y;
    }
}

/*******************************************************************
*
*                  GUI_MagnifyPolygon
*
********************************************************************
*/

void GUI_MagnifyPolygon(gdi_point* pDest, const gdi_point* pSrc, int NumPoints, int Mag)
{
    int j;
    for (j=0; j<NumPoints; j++) {
        (pDest+j)->x = (pSrc+j)->x * Mag;
        (pDest+j)->y = (pSrc+j)->y * Mag;
    }
}

/*******************************************************************
*
*                  GUI_RotatePolygon
*
********************************************************************
*/
void GUI_RotatePolygon(gdi_point* pDest, const gdi_point* pSrc, int NumPoints, float Angle)
{
    int j;
    float fcos = cos(Angle);
    float fsin = sin(Angle);
    for (j=0; j<NumPoints; j++) {
        int x = (pSrc+j)->x;
        int y = (pSrc+j)->y;
        (pDest+j)->x =  x * fcos + y * fsin;
        (pDest+j)->y = -x * fsin + y * fcos;
    }
}




