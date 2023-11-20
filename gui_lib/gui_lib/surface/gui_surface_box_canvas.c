
#include "math.h"
#include "debug_info.h"

#include "gui_display_draw_lib.h"

#include "gui_surface_box_canvas.h"
#include "gui_surface_cache.h"
#include "gui_surface_node.h"

static void gui_surface_box_canvas_point(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    node->clip_x = canvas->canvas.point.x - canvas->penSize/2;
    node->clip_y = canvas->canvas.point.y - canvas->penSize/2;
    node->clip_width = canvas->canvas.point.x + canvas->penSize/2 + 1;
    node->clip_height = canvas->canvas.point.y - canvas->penSize/2 + 1;
}

static void gui_surface_box_canvas_line(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    if (canvas->canvas.line.x0 > canvas->canvas.line.x1) {
        node->clip_x = canvas->canvas.line.x1 - canvas->penSize/2;
        node->clip_width = canvas->canvas.line.x0 - canvas->canvas.line.x1 + canvas->penSize + 1;
    }
    else {
        node->clip_x = canvas->canvas.line.x0 - canvas->penSize/2;
        node->clip_width = canvas->canvas.line.x1 - canvas->canvas.line.x0 + canvas->penSize + 1;
    }
    if (canvas->canvas.line.y0 > canvas->canvas.line.y1) {
        node->clip_y = canvas->canvas.line.y1 - canvas->penSize/2;
        node->clip_height = canvas->canvas.line.y0 - canvas->canvas.line.y1 + canvas->penSize + 1;
    }
    else {
        node->clip_y = canvas->canvas.line.y0 - canvas->penSize/2;
        node->clip_height = canvas->canvas.line.y1 - canvas->canvas.line.y0 + canvas->penSize + 1;
    }
}

static void gui_surface_box_canvas_rect(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    node->clip_x = canvas->canvas.rect.x0 - canvas->penSize/2;
    node->clip_y = canvas->canvas.rect.y0 - canvas->penSize/2;
    node->clip_width = canvas->canvas.rect.x1 - canvas->canvas.rect.x0 + canvas->penSize + 1;
    node->clip_height = canvas->canvas.rect.y1 - canvas->canvas.rect.y0 + canvas->penSize + 1;
}

static void gui_surface_box_canvas_fillRect(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    node->clip_x = canvas->canvas.rect.x0 - canvas->penSize/2;
    node->clip_y = canvas->canvas.rect.y0 - canvas->penSize/2;
    node->clip_width = canvas->canvas.rect.x1 - canvas->canvas.rect.x0 + canvas->penSize + 1;
    node->clip_height = canvas->canvas.rect.y1 - canvas->canvas.rect.y0 + canvas->penSize + 1;
}

static void gui_surface_box_canvas_circle(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    node->clip_x = canvas->canvas.circle.cx - canvas->canvas.circle.r - canvas->penSize/2;
    node->clip_y = canvas->canvas.circle.cy - canvas->canvas.circle.r - canvas->penSize/2;
    node->clip_width = 2*canvas->canvas.circle.r + canvas->penSize;
    node->clip_height = 2*canvas->canvas.circle.r + canvas->penSize;
}

static void gui_surface_box_canvas_fillCircle(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    node->clip_x = canvas->canvas.circle.cx - canvas->canvas.circle.r - canvas->penSize/2;
    node->clip_y = canvas->canvas.circle.cy - canvas->canvas.circle.r - canvas->penSize/2;
    node->clip_width = 2*canvas->canvas.circle.r + canvas->penSize;
    node->clip_height = 2*canvas->canvas.circle.r + canvas->penSize;
}

static void gui_surface_box_canvas_arc(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    node->clip_x = canvas->canvas.arc.cx - canvas->canvas.arc.r - canvas->penSize/2;
    node->clip_y = canvas->canvas.arc.cy - canvas->canvas.arc.r - canvas->penSize/2;
    node->clip_width = 2*canvas->canvas.arc.r + canvas->penSize;
    node->clip_height = 2*canvas->canvas.arc.r + canvas->penSize;
}

static void gui_surface_box_canvas_fillArc(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    node->clip_x = canvas->canvas.arc.cx - canvas->canvas.arc.r - canvas->penSize/2;
    node->clip_y = canvas->canvas.arc.cy - canvas->canvas.arc.r - canvas->penSize/2;
    node->clip_width = 2*canvas->canvas.arc.r + canvas->penSize;
    node->clip_height = 2*canvas->canvas.arc.r + canvas->penSize;
}

static void gui_surface_box_canvas_polygon(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    gui_point_struct* point = canvas->canvas.polygon.points;
    unsigned int i = 0;
    int yMin = GUI_YMIN, yMax = GUI_YMAX;
    int xMin = GUI_XMIN, xMax = GUI_XMAX;

    if (point != NULL && canvas->canvas.polygon.point_num != 0) {
        for (i=0; i<canvas->canvas.polygon.point_num; i++) {
            if (point->y < yMin)
                yMin = point->y;
            if (point->y > yMax)
                yMax = point->y;
            
            if (point->x < xMin)
                xMin = point->x;
            if (point->x > xMax)
                xMax = point->x;
        }
    }
    node->clip_x = canvas->canvas.polygon.bx + xMin - canvas->penSize/2;
    node->clip_y = canvas->canvas.polygon.by + yMin - canvas->penSize/2;
    node->clip_width = xMax - xMin + canvas->penSize + 1;
    node->clip_height = yMax - yMin + canvas->penSize + 1;
}

static void gui_surface_box_canvas_fillPolygon(gui_node_struct* node)
{
    gui_canvas_struct* canvas = (gui_canvas_struct*)node->data;
    gui_point_struct* point = canvas->canvas.polygon.points;
    unsigned int i = 0;
    int yMin = GUI_YMIN, yMax = GUI_YMAX;
    int xMin = GUI_XMIN, xMax = GUI_XMAX;

    if (point != NULL && canvas->canvas.polygon.point_num != 0) {
        for (i=0; i<canvas->canvas.polygon.point_num; i++) {
            if (point->y < yMin)
                yMin = point->y;
            if (point->y > yMax)
                yMax = point->y;

            if (point->x < xMin)
                xMin = point->x;
            if (point->x > xMax)
                xMax = point->x;
        }
    }
    node->clip_x = canvas->canvas.polygon.bx + xMin - canvas->penSize/2;
    node->clip_y = canvas->canvas.polygon.by + yMin - canvas->penSize/2;
    node->clip_width = xMax - xMin + canvas->penSize + 1;
    node->clip_height = yMax - yMin + canvas->penSize + 1;
}

gui_node_struct* gui_surface_box_canvas_init(gui_node_struct* node)
{
    switch(node->type) {
    case TYPE_GUI_DRAW_SHAPE_POINT:
        gui_surface_box_canvas_point(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_LINE:
    case TYPE_GUI_DRAW_SHAPE_STYLE_LINE:
        gui_surface_box_canvas_line(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_RECT:
        gui_surface_box_canvas_rect(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_RECT_FILL:
        gui_surface_box_canvas_fillRect(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_CIRCLE:
        gui_surface_box_canvas_circle(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_CIRCLE_FILL:
        gui_surface_box_canvas_fillCircle(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_ARC:
        gui_surface_box_canvas_arc(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_ARC_FILL:
        gui_surface_box_canvas_fillArc(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_POLYGON:
        gui_surface_box_canvas_polygon(node);
        break;
    case TYPE_GUI_DRAW_SHAPE_POLYGON_FILL:
        gui_surface_box_canvas_fillPolygon(node);
        break;
    default:
        gui_surface_cache_remove_node(node);
        node = NULL;
        break;
    }
    return node;
}


void gui_surface_box_canvas_create(gui_box_struct* box)
{
    gui_node_struct* end_node;
    gui_node_struct* node;
    gui_widget_struct* widget = box->widget;
    gui_canvas_struct* canvas = (gui_canvas_struct*)widget->children;
    unsigned int num = widget->child_num;
    
    box->child = NULL;
    
    while(num > 0)
    {
        node = gui_surface_cache_add_node();
        if (node != NULL) {
			node->id = canvas->id;
            node->data = canvas;
            node->draw = canvas;
            node->type = canvas->type;
            node->x = 0;
            node->y = 0;
			node->width = box->width;
			node->height = box->height;
            node->scale = GUI_INIT_SCALE(canvas->scale);
            node = gui_surface_box_canvas_init(node);
            if (node != NULL) {
                if (box->child == NULL) {
                    box->child = node;
                } 
                else {
                    end_node->brother = node;
                }
                end_node = node;
            }
        }
        canvas ++;
        num --;
    }
}

void gui_surface_box_canvas_change_color(gui_box_struct* box, unsigned short node_id, GUI_COLOR color)
{
}

void gui_surface_box_canvas_change(gui_box_struct* box, unsigned short node_id, gui_canvas_struct* canvas)
{
    if (box != NULL && canvas != NULL) {
        gui_node_struct* node = gui_surface_box_find_node(box, node_id);
        if (node != NULL) {
            node->data = canvas;
            node->type = canvas->type;
            node->x = 0;
            node->y = 0;
			node->width = box->width;
			node->height = box->height;
            gui_surface_box_canvas_init(node);
        }
    }
}

void gui_surface_box_canvas_flush(gui_box_struct* box, unsigned short node_id)
{
    if (box != NULL) {
        gui_node_struct* node = gui_surface_box_find_node(box, node_id);
        if (node != NULL) {
            gui_surface_box_canvas_init(node);
        }
    }
}

