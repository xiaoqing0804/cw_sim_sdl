
/***************************************************************************************/
//      date            auth            note
//--------------------------------------------------------------------------------------
//   2022-11-28       Taylor.Le         支持屏幕剪切区 （GUILIB_V2）
//
/***************************************************************************************/

#ifndef __GUI_DISPLAY_DRAW_H__
#define __GUI_DISPLAY_DRAW_H__

#include "picture.h"
#include "feature_all.h"
#include "gui_display_render.h"


#define GUILIB_V2   1

/* Define minimum and maximum coordinates in x and y */
#define GUI_XMIN -4095
#define GUI_XMAX  4095
#define GUI_YMIN -4095
#define GUI_YMAX  4095

#define GUI_45DEG  512
#define GUI_90DEG  (2*GUI_45DEG)
#define GUI_180DEG (4*GUI_45DEG)
#define GUI_360DEG (8*GUI_45DEG)

#define GUI_DRAWMODE_NORMAL  0
#define GUI_DRAWMODE_XOR     1
#define GUI_DRAWMODE_TRANS   2
#define GUI_DRAWMODE_REV     4

/*********************************
 *
 *      Linestyles
 *
 *********************************/
#define GUI_LS_SOLID        (0)
#define GUI_LS_DASH         (1)
#define GUI_LS_DOT          (2)
#define GUI_LS_DASHDOT      (3)
#define GUI_LS_DASHDOTDOT   (4)

/**********************************
 *
 *      Pen shapes
 *
 **********************************/
#define GUI_PS_ROUND        (0)
#define GUI_PS_FLAT         (1)
#define GUI_PS_SQUARE       (2)

#define GUI_POLY_POINT_MAX  (10)

typedef void (*fp_DrawHLine)(int x0, int y, int x1);
typedef void (*fp_DrawVLine)(int x, int y0, int y1);

typedef GUI_COLOR (*fp_GetPixel)(int x, int y);
typedef void      (*fp_SetPixel)(int x, int y, GUI_COLOR color);

typedef struct 
{
    short x, y;
}gdi_point;

typedef struct
{
    short x0, y0;
    short x1, y1;
}gdi_rect;

typedef struct 
{
    char         lineStyle;
    char         penShape;
    char         penSize;
    char         drawMode;
    short        drawPosX;
    short        drawPosY;
    
    gdi_rect     clipRect;
    gdi_rect*    clipRect_HL;
    //#if GUILIB_V2
    short        clip_x0;
    short        clip_x1;
    //#endif
    short        clip_y0;
    short        clip_y1;
    
    fp_DrawHLine drawHLine;
    fp_DrawVLine drawVLine;
    fp_GetPixel  getPixel;
    fp_SetPixel  setPixel;

    unsigned char* frame_buffer;
    short          y0;
    short          y1;
    //#if GUILIB_V2
    short          x0;
    short          x1;
    unsigned short bw;      // line stride(bytes),  4byte alin
    unsigned short bh;
    float          scale;
    //#endif

    GUI_COLOR      color;
    GUI_COLOR      bg_color;
}gdi_lib_ctx;

typedef struct
{
	int img_x0;
	int x0;
	int x1;
	int dw;

    int img_y0;
	int y0;
	int y1;
	int dh;
}gui_display_draw_point_struct;


extern gdi_lib_ctx*  gui_lib_ctx;


extern void gui_initContext(void);
extern void gui_setClip(short x0, short y0, short x1, short y1);
extern void gui_setClipRect(gdi_rect* rect);
extern void gui_setFrameBuffer(unsigned char* buff, short y0, short y1);
//#if GUILIB_V2
extern void gui_setFrameBufferRect(unsigned char* buff, short x, short y, short w, short h);
extern void gui_setScale(float scale);
//#endif

extern unsigned char gui_setLineStyle(unsigned char lineStyle);
extern unsigned char gui_setPenSize(unsigned char penSize);
extern unsigned char gui_setPenShape(unsigned char penShape);
extern unsigned char gui_setDrawMode(unsigned char drawMode);

extern GUI_COLOR gui_setColor(GUI_COLOR color);

extern float gui_sqrt( float number );

extern void GUI_DrawLine(int x0, int y0, int x1, int y1);
extern void GUI_DrawPolygon(const gdi_point* pPoints, int NumPoints, int x0, int y0);

extern void GUI_DrawLineRel(int dx, int dy);
extern void GUI_DrawLineTo(int x, int y);
extern void GUI_MoveRel(int dx, int dy);
extern void GUI_MoveTo(int x, int y);

extern void GUI_DrawRect(int x0, int y0, int x1, int y1);
extern void GUI_DrawFillRect(int x0, int y0, int x1, int y1);
extern void GUI_DrawFillRectOpacity(int x0, int y0, int x1, int y1, int opacity);
extern void GUI_DrawPoint(int x, int y);

extern void GUI_DrawArc (int x0, int y0, int rx, int ry, int a0, int a1);


extern void GUI_DrawCircle(int x0, int y0, int r);
extern void GUI_FillCircle(int x0, int y0, int r);
extern void GUI_DrawEllipse(int x0, int y0, int rx, int ry);
extern void GUI_FillEllipse(int x0, int y0, int rx, int ry);


extern void GUI_FillPolygon  (const gdi_point* pPoints, int NumPoints, int x0, int y0);
extern void GUI_EnlargePolygon(gdi_point* pDest, const gdi_point* pSrc, int NumPoints, int Len);
extern void GUI_MagnifyPolygon(gdi_point* pDest, const gdi_point* pSrc, int NumPoints, int Mag);
extern void GUI_RotatePolygon(gdi_point* pDest, const gdi_point* pSrc, int NumPoints, float Angle);

extern void GUI_DrawPicture(picture_info_struct* pic, int x, int y);
extern void GUI_DrawPointer8(picture_info_struct* pics[], int x, int y, int w, int h, int cx, int cy, short value);
#if PICTURE_ALPHA_POINT_FAST_SUPPORT
extern void GUI_DrawPointer16(picture_info_struct* pics[], int x, int y, int w, int h, int cx, int cy, short value);
#endif

extern void GUI_DrawStyleLineH(short x0, short x1, short y, short show_pixels, short skip_pixels);
extern void GUI_DrawStyleLineV(short y0, short y1, short x, short show_pixels, short skip_pixels);
extern void GUI_DrawStyleLine(int x0, int y0, int x1, int y1, short show_pixels, short skip_pixels);


#define RETURN_IF_Y_OUT() \
  if ((y < gui_lib_ctx->y0) || (y > gui_lib_ctx->y1)) return;

#define RETURN_IF_X_OUT() \
  if ((x < gui_lib_ctx->x0) || (x > gui_lib_ctx->x1)) return;

#define RETURN_IF_Y_OUT_RANG() \
    if ((y1 < gui_lib_ctx->y0) || (y0 > gui_lib_ctx->y1)) return;
  
#define RETURN_IF_X_OUT_RANG() \
    if ((x1 < gui_lib_ctx->x0) || (x0 > gui_lib_ctx->x1)) return;

#define IS_Y_OUT() \
  ((y < gui_lib_ctx->y0) || (y > gui_lib_ctx->y1))

#define IS_X_OUT() \
  ((x < gui_lib_ctx->x0) || (x > gui_lib_ctx->x1))


#if 1//GUILIB_V2
#define CLIP_X() \
  if (x0 < gui_lib_ctx->clipRect.x0) { x0 = gui_lib_ctx->clipRect.x0; } \
  if (x0 < gui_lib_ctx->x0)          { x0 = gui_lib_ctx->x0; } \
  if (x1 > gui_lib_ctx->clipRect.x1) { x1 = gui_lib_ctx->clipRect.x1; } \
  if (x1 > gui_lib_ctx->x1)          { x1 = gui_lib_ctx->x1; }


#define CLIP_Y() \
  if (y0 < gui_lib_ctx->clipRect.y0) { y0 = gui_lib_ctx->clipRect.y0; } \
  if (y0 < gui_lib_ctx->y0)          { y0 = gui_lib_ctx->y0; } \
  if (y1 > gui_lib_ctx->clipRect.y1) { y1 = gui_lib_ctx->clipRect.y1; } \
  if (y1 > gui_lib_ctx->y1)          { y1 = gui_lib_ctx->y1; }

#define UI_CHARGE_XY(x, y)		(((y) - gui_lib_ctx->y0)*(gui_lib_ctx->bw) + ((x)-gui_lib_ctx->x0)*COLOR_RGB_PIXEL)

#else
#define CLIP_X() \
  if (x0 < gui_lib_ctx->clipRect.x0) { x0 = gui_lib_ctx->clipRect.x0; } \
  if (x1 > gui_lib_ctx->clipRect.x1) { x1 = gui_lib_ctx->clipRect.x1; }


#define CLIP_Y() \
  if (y0 < gui_lib_ctx->clipRect.y0) { y0 = gui_lib_ctx->clipRect.y0; } \
  if (y1 > gui_lib_ctx->clipRect.y1) { y1 = gui_lib_ctx->clipRect.y1; }

#define UI_CHARGE_XY(x, y)		((((y) - gui_lib_ctx->y0)*LCD_SIZE_WIDTH + (x))*COLOR_RGB_PIXEL)
#endif

extern void gui_draw_picture_scale(unsigned char *picture_buff, int x, int y, int width, int height);

extern void gui_display_draw_box_scale_check(gui_box_struct*box, gui_render_struct* render);

extern void gui_display_draw_picture_scale_check(gui_render_struct* render);
extern void gui_display_draw_picture_scale_preload(void);
extern void gui_display_draw_picture_scale_clear(void);
extern void gui_display_draw_picture_scale_picture(gui_render_struct* render);
extern unsigned char gui_display_draw_picture_scale(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end);

#endif

