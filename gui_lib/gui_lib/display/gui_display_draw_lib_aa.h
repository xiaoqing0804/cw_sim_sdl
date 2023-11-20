#ifndef __GUI_DISPLAY_DRAW_LIB_AA_H__
#define __GUI_DISPLAY_DRAW_LIB_AA_H__

#include "gui_display_draw_lib.h"

GUI_COLOR gui_AA_mixColors(GUI_COLOR Color, GUI_COLOR BkColor, unsigned char Intens);

void GUI_AA_DrawLine(int x0, int y0, int x1, int y1);
void GUI_AA_DrawLineX10(int x0, int y0, int x1, int y1);
void GUI_AA_DrawArc(int x0, int y0, int rx, int ry, int a0, int a1);
void GUI_AA_DrawCircle(int x0, int y0, int r);
void GUI_AA_FillCircle(int x0, int y0, int r);
void GUI_AA_FillPolygon(gdi_point* paPoint, int NumPoints, int x, int y);
void GUI_AA_DrawPolyOutline(const gdi_point* pSrc, int NumPoints, int Thickness, int x, int y);

#endif

