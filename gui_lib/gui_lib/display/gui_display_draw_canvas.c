#include "gui_display_draw_canvas.h"

#include "gui_display_draw_lib.h"
#include "gui_display_draw_lib_aa.h"

void gui_display_draw_canvas_point(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->AA && canvas->penSize > 2) {
        GUI_AA_FillCircle(render->x+canvas->canvas.point.x, render->y+canvas->canvas.point.y, canvas->penSize/2);
    }
    else {
        GUI_DrawPoint(render->x+canvas->canvas.point.x, render->y+canvas->canvas.point.y);
    }
}

void gui_display_draw_canvas_line(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->AA) {
        GUI_AA_DrawLine(render->x+canvas->canvas.line.x0, render->y+canvas->canvas.line.y0, render->x+canvas->canvas.line.x1, render->y+canvas->canvas.line.y1);
    }
    else {
        GUI_DrawLine(render->x+canvas->canvas.line.x0, render->y+canvas->canvas.line.y0, render->x+canvas->canvas.line.x1, render->y+canvas->canvas.line.y1);
    }
}

void gui_display_draw_canvas_style_line(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->canvas.line.x0 == canvas->canvas.line.x1) {
        GUI_DrawStyleLineV(render->y+canvas->canvas.line.y0, render->y+canvas->canvas.line.y1, render->x+canvas->canvas.line.x0, canvas->canvas.line.showPixel, canvas->canvas.line.skipPixel);
    }
    else if (canvas->canvas.line.y0 == canvas->canvas.line.y1) {
        GUI_DrawStyleLineH(render->x+canvas->canvas.line.x0, render->x+canvas->canvas.line.x1, render->y+canvas->canvas.line.y0, canvas->canvas.line.showPixel, canvas->canvas.line.skipPixel);
    }
    else {  // only h-line or v-line supported style.
        GUI_AA_DrawLine(render->x+canvas->canvas.line.x0, render->y+canvas->canvas.line.y0, render->x+canvas->canvas.line.x1, render->y+canvas->canvas.line.y1);
    }
}


void gui_display_draw_canvas_rect(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    GUI_DrawRect(render->x+canvas->canvas.rect.x0, render->y+canvas->canvas.rect.y0, render->x+canvas->canvas.rect.x1, render->y+canvas->canvas.rect.y1);
}

void gui_display_draw_canvas_fill_rect(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->opacity != 0) {
        GUI_DrawFillRectOpacity(render->x+canvas->canvas.rect.x0, render->y+canvas->canvas.rect.y0, render->x+canvas->canvas.rect.x1, render->y+canvas->canvas.rect.y1, canvas->opacity);
    }
    else {
        GUI_DrawFillRect(render->x+canvas->canvas.rect.x0, render->y+canvas->canvas.rect.y0, render->x+canvas->canvas.rect.x1, render->y+canvas->canvas.rect.y1);
    }
}

void gui_display_draw_canvas_circle(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->AA) {
        GUI_AA_DrawCircle(render->x+canvas->canvas.circle.cx, render->y+canvas->canvas.circle.cy, canvas->canvas.circle.r);
    }
    else {
        GUI_DrawCircle(render->x+canvas->canvas.circle.cx, render->y+canvas->canvas.circle.cy, canvas->canvas.circle.r);
    }
}

void gui_display_draw_canvas_fill_circle(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->AA) {
        GUI_AA_FillCircle(render->x+canvas->canvas.circle.cx, render->y+canvas->canvas.circle.cy, canvas->canvas.circle.r);
    }
    else {
        GUI_FillCircle(render->x+canvas->canvas.circle.cx, render->y+canvas->canvas.circle.cy, canvas->canvas.circle.r);
    }
}

void gui_display_draw_canvas_arc(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->AA) {
        GUI_AA_DrawArc(render->x+canvas->canvas.arc.cx, render->y+canvas->canvas.arc.cy, canvas->canvas.arc.r, 0, canvas->canvas.arc.Angle0, canvas->canvas.arc.Angle1);
    }
    else {
        GUI_DrawArc(render->x+canvas->canvas.arc.cx, render->y+canvas->canvas.arc.cy, canvas->canvas.arc.r, 0, canvas->canvas.arc.Angle0, canvas->canvas.arc.Angle1);
    }
}

void gui_display_draw_canvas_fill_arc(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    unsigned char penSize = canvas->canvas.arc.r;
    gui_setColor(canvas->penColor);
    gui_setPenSize(penSize);
    if (canvas->AA) {
        GUI_AA_DrawArc(render->x+canvas->canvas.arc.cx, render->y+canvas->canvas.arc.cy, canvas->canvas.arc.r/2, 0, canvas->canvas.arc.Angle0, canvas->canvas.arc.Angle1);
    }
    else {
        GUI_DrawArc(render->x+canvas->canvas.arc.cx, render->y+canvas->canvas.arc.cy, canvas->canvas.arc.r/2, 0, canvas->canvas.arc.Angle0, canvas->canvas.arc.Angle1);
    }
}

void gui_display_draw_canvas_polygon(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->AA) {
        GUI_AA_DrawPolyOutline((gdi_point*)canvas->canvas.polygon.points, canvas->canvas.polygon.point_num, canvas->penSize, render->x+canvas->canvas.polygon.bx, render->y+canvas->canvas.polygon.by);
    }
    else {
        GUI_DrawPolygon((gdi_point*)canvas->canvas.polygon.points, canvas->canvas.polygon.point_num, render->x+canvas->canvas.polygon.bx, render->y+canvas->canvas.polygon.by);
    }
}

void gui_display_draw_canvas_fill_polygon(unsigned char* render_buf,gui_render_struct* render,short y_start,short y_end)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    gui_setColor(canvas->penColor);
    gui_setPenSize(canvas->penSize);
    if (canvas->AA) {
        GUI_AA_FillPolygon((gdi_point*)canvas->canvas.polygon.points, canvas->canvas.polygon.point_num, render->x+canvas->canvas.polygon.bx, render->y+canvas->canvas.polygon.by);
    }
    else {
        GUI_FillPolygon((gdi_point*)canvas->canvas.polygon.points, canvas->canvas.polygon.point_num, render->x+canvas->canvas.polygon.bx, render->y+canvas->canvas.polygon.by);
    }
}


