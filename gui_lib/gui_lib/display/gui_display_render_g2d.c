
#include "gui_display_render.h"
#include "gui_display_render_cache.h"
#include "gui_display_render_g2d.h"


#if (GUI_DISPLAY_SCREEN == GUI_DISPLAY_SCREEN_G2D) && GUI_SURFACE_ZOOM_SUPPORT

static int gui_display_render_adj_x(gui_surface_struct* surface, float scale, int x)
{
    if (surface->x < 0) {
        x = (surface->x + LCD_SIZE_WIDTH) - (int)((surface->x + LCD_SIZE_WIDTH - x) * scale);
    }
    else {
        x = (int)((x - surface->x) * scale) + surface->x;
    }
    return x;
}
static int gui_display_render_adj_y(gui_surface_struct* surface, float scale, int y)
{
    if (y > LCD_SIZE_HALF_HEIGHT) {
        y = LCD_SIZE_HALF_HEIGHT + (int)(scale*(y - LCD_SIZE_HALF_HEIGHT));
    }
    else if (y < LCD_SIZE_HALF_HEIGHT) {
        y = LCD_SIZE_HALF_HEIGHT - (int)(scale*(LCD_SIZE_HALF_HEIGHT - y));
    }
    return y;
}
static int gui_display_render_adj_v(float scale, int v)
{
    return (int)(v * scale);
}

void gui_display_render_pointer_coordinate_transormation_by_scale(gui_render_struct* render)
{
    if (render == NULL && render->data == NULL) {
        return;
    }
    gui_pointer_struct* pointer = (gui_pointer_struct*)render->data;
    int   surface_x = render->surface_x;
    float scale     = render->scale;

    if (pointer->type == TYPE_GUI_DRAW_POINTER_LINE_60 || pointer->type == TYPE_GUI_DRAW_POINTER_LINE_360) {
        short* line_pos = pointer->shape.line.position;
        if (line_pos != NULL) {
            line_pos[0] = gui_display_render_adj_v(scale, line_pos[0]);
            line_pos[1] = gui_display_render_adj_v(scale, line_pos[1]);
            line_pos[2] = gui_display_render_adj_v(scale, line_pos[2]);
            line_pos[3] = gui_display_render_adj_v(scale, line_pos[3]);
        }
    }
}

void gui_display_render_canvas_coordinate_transormation_by_scale(gui_render_struct* render)
{
    if (render == NULL && render->data == NULL) {
        return;
    }
    gui_canvas_struct* canvas = (gui_canvas_struct*)render->data;
    int   surface_x = render->surface_x;
    float scale     = render->scale;

    switch(canvas->type) {
		case TYPE_GUI_DRAW_SHAPE_POINT:
            canvas->canvas.point.x = gui_display_render_adj_v(scale, canvas->canvas.point.x);
            canvas->canvas.point.y = gui_display_render_adj_v(scale, canvas->canvas.point.y);
            break;

		case TYPE_GUI_DRAW_SHAPE_LINE:
		case TYPE_GUI_DRAW_SHAPE_STYLE_LINE:
            canvas->canvas.line.x0 = gui_display_render_adj_v(scale, canvas->canvas.line.x0);
            canvas->canvas.line.x1 = gui_display_render_adj_v(scale, canvas->canvas.line.x1);
            canvas->canvas.line.y0 = gui_display_render_adj_v(scale, canvas->canvas.line.y0);
            canvas->canvas.line.y1 = gui_display_render_adj_v(scale, canvas->canvas.line.y1);
            break;

		case TYPE_GUI_DRAW_SHAPE_RECT:
		case TYPE_GUI_DRAW_SHAPE_RECT_FILL:
            canvas->canvas.rect.x0 = gui_display_render_adj_v(scale, canvas->canvas.rect.x0);
            canvas->canvas.rect.x1 = gui_display_render_adj_v(scale, canvas->canvas.rect.x1);
            canvas->canvas.rect.y0 = gui_display_render_adj_v(scale, canvas->canvas.rect.y0);
            canvas->canvas.rect.y1 = gui_display_render_adj_v(scale, canvas->canvas.rect.y1);
            break;

		case TYPE_GUI_DRAW_SHAPE_CIRCLE:
		case TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL:
            canvas->canvas.circle.cx = gui_display_render_adj_v(scale, canvas->canvas.circle.cx);
            canvas->canvas.circle.cy = gui_display_render_adj_v(scale, canvas->canvas.circle.cy);
            canvas->canvas.circle.r  = gui_display_render_adj_v(scale, canvas->canvas.circle.r);
            break;

		case TYPE_GUI_DRAW_SHAPE_ARC:
		case TYPE_GUI_DRAW_SHAPE_ARC_FILL:
            canvas->canvas.arc.cx = gui_display_render_adj_v(scale, canvas->canvas.arc.cx);
            canvas->canvas.arc.cy = gui_display_render_adj_v(scale, canvas->canvas.arc.cy);
            canvas->canvas.arc.r  = gui_display_render_adj_v(scale, canvas->canvas.arc.r);
            break;

        case TYPE_GUI_DRAW_SHAPE_POLYGON:
        case TYPE_GUI_DRAW_SHAPE_POLYGON_FILL:
            if (canvas->canvas.polygon.point_num != 0) {
                gui_point_struct* point = canvas->canvas.polygon.points;
                unsigned int count;
                for (count=0; count<canvas->canvas.polygon.point_num; count++) {
                    point->x = gui_display_render_adj_v(scale, point->x);
                    point->y = gui_display_render_adj_v(scale, point->y);
                }

                canvas->canvas.polygon.bx = gui_display_render_adj_v(scale, canvas->canvas.polygon.bx);
                canvas->canvas.polygon.by = gui_display_render_adj_v(scale, canvas->canvas.polygon.by);
            }
            break;
        default:
            break;
    }
}

int gui_display_render_coordinate_transormation_by_scale(gui_surface_struct* surface, gui_render_struct* render) // coordinate transformation
{
    //SYS_DEBUG("gui: render_coordinate_transormation_by_scale, %f", surface->scale);
    if ((surface->scale == 1.0f) || (surface->scale == 0.0f)) return 0;
    float scale = surface->scale;

    //SYS_DEBUG("scal: loc0 = {x: %d, y: %d, w: %d, h: %d}", render->x, render->y, render->width, render->height);
    //SYS_DEBUG("scal: clp0 = {l: %d, t: %d, r: %d, b: %d}", render->clip_left, render->clip_top, render->clip_right, render->clip_bottom);
    //SYS_DEBUG("scal: surface_x=%d, scale0 = %f", surface->x, scale);

    render->x = gui_display_render_adj_x(surface, scale, render->x);
    render->width = gui_display_render_adj_v(scale, render->width);
    render->clip_left = gui_display_render_adj_x(surface, scale, render->clip_left);
    render->clip_right = gui_display_render_adj_x(surface, scale, render->clip_right);

    render->y = gui_display_render_adj_y(surface, scale, render->y);
    render->height = gui_display_render_adj_v(scale, render->height);
    render->clip_top = gui_display_render_adj_y(surface, scale, render->clip_top);
    render->clip_bottom = gui_display_render_adj_y(surface, scale, render->clip_bottom);

    render->scale = scale*render->scale;
    render->surface_x = surface->x;

    //SYS_DEBUG("scal: scale1 = %f", render->scale);
    //SYS_DEBUG("scal: loc1 = {x: %d, y: %d, w: %d, h: %d}", render->x, render->y, render->width, render->height);
    //SYS_DEBUG("scal: clp1 = {l: %d, t: %d, r: %d, b: %d}", render->clip_left, render->clip_top, render->clip_right, render->clip_bottom);

    return 1;
}
#endif

