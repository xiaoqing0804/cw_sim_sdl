
#include "sys_timer.h"
#include "sys_timer_thread.h"
#include "debug_info.h"
#include "app_task_main.h"
#include "os_mem.h"

#include "gui_display_draw_lib.h"
#include "gui_surface_cache.h"
#include "gui_surface_node.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_chart.h"


typedef struct {
    short mMinX;
    short mMaxX;
    short mMinY;
    short mMaxY;
    gui_canvas_struct   canvas[1];
}gui_chart_info;

static const gui_font_struct gui_chart_label_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(130, 130, 130),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "0",
};

static void gui_chart_memfree_timer_handler(unsigned int timer_id, void* param)
{
    application_stop_user_timer(timer_id);
    if (param != NULL) {
        os_mem_free(param);
    }
}

//
static short gui_chart_dumy_fmtXAxis(gui_chart_struct* chart, short value, char* axis)
{
    if (axis != NULL) {
        sprintf(axis, "%d", value);
    }
    return value;
}

static short gui_chart_dumy_fmtYAxis(gui_chart_struct* chart, short value, char* axis)
{
    if (axis != NULL) {
        sprintf(axis, "%d", value);
    }
    return value;
}

static void gui_chart_calcRange(gui_box_struct* box)
{
    gui_chart_struct* chart = (gui_chart_struct*)box->widget->children;
    gui_chart_info* chart_info = (gui_chart_info*)box->data;

    if ((chart->mFlags & CHARTS_FLG_FIXED_AXIS) == CHARTS_FLG_FIXED_AXIS) {
        return;
    }

    unsigned int cnt = 0, idx;
    int val;
    if (0 == (chart->mFlags & CHARTS_FLG_FIXED_XAXIS)) {
        chart_info->mMinX = SHORT_MIN;
        chart_info->mMaxX = SHORT_MAX;
    }
    if (0 == (chart->mFlags & CHARTS_FLG_FIXED_YAXIS)) {
        chart_info->mMinY = SHORT_MAX;
        chart_info->mMaxY = SHORT_MIN;
    }

    cnt = chart->getCount(chart);
    for (idx=0; idx<cnt; idx++) {
        if (0 == (chart->mFlags & CHARTS_FLG_FIXED_YAXIS)) {
            val = chart->getYValue(chart, idx);
            if (chart_info->mMaxY < val) {
                chart_info->mMaxY = val;
            }
            if (chart_info->mMinY > val) {
                chart_info->mMinY = val;
            }
        }

        if (0 == (chart->mFlags & CHARTS_FLG_FIXED_XAXIS)) {
            val = chart->getXValue(chart, idx);
            if (chart_info->mMaxX < val) {
                chart_info->mMaxX = val;
            }
            if (chart_info->mMinX > val) {
                chart_info->mMinX = val;
            }
        }
    }

    if (cnt > 1) {
        if (0 == (chart->mFlags & CHARTS_FLG_FIXED_YAXIS)) {
            if (chart_info->mMaxY == 0) {
                chart_info->mMaxY = 100;
                chart_info->mMinY = 0;
            }
            else {
                chart_info->mMaxY += (10 - chart_info->mMaxY%10);
                if (chart_info->mMinY > 10) {
                    chart_info->mMinY -= (10 + chart_info->mMinY%10);
                }
                else {
                    chart_info->mMinY = 0;
                }
            }
        }
    }
    else {
        if (0 == (chart->mFlags & CHARTS_FLG_FIXED_YAXIS)) {
            chart_info->mMinY = 0;
            chart_info->mMaxY = 100;
        }
        if (0 == (chart->mFlags & CHARTS_FLG_FIXED_XAXIS)) {
            chart_info->mMinX = 0;
            chart_info->mMaxX = 100;
        }
    }
}

static void gui_chart_drawBar(gui_box_struct* box, geometry_rect* rect)
{
    gui_chart_struct* chart = (gui_chart_struct*)box->widget->children;
    gui_chart_info* chart_info = (gui_chart_info*)box->data;
    gui_canvas_struct* canvas = &chart_info->canvas[2+chart->mLabelNum*4];
    unsigned int idx;
    unsigned short cnt = chart->getCount(chart);
    SYS_DEBUG("gui_chart_drawBar");

    //SYS_DEBUG("gui: chart_drawBar, count=%d", cnt);

    if (cnt > 0) {
        for (idx=0; idx<cnt; idx++) {
            short x_val = chart->getXValue(chart, idx);
            short y_val = chart->getYValue(chart, idx);
            short y_bottom = chart->getYBottomValue(chart, idx);
            unsigned short x_pos = rect->x + (rect->width * (x_val-chart_info->mMinX)) / (chart_info->mMaxX - chart_info->mMinX);
            unsigned short y_pos = (rect->height * (y_val-chart_info->mMinY)) / (chart_info->mMaxY - chart_info->mMinY);
            unsigned short y_bottom_pos = (rect->height * (y_bottom-chart_info->mMinY)) / (chart_info->mMaxY - chart_info->mMinY);
            if(y_bottom == 0){
                y_bottom_pos = 0;
            }
            if (y_pos > 1) {
                y_pos = rect->y + rect->height - y_pos;
                y_bottom_pos = rect->y + rect->height - y_bottom_pos - 1;
                x_pos -= chart->mBarWidth/2;
                canvas->id = 0;
                canvas->type = TYPE_GUI_DRAW_SHAPE_RECT_FILL;
                canvas->AA = 0;
                canvas->fillColor = chart->mFillColor;
                canvas->penColor = chart->mFillColor;
                canvas->penSize = 1;
                canvas->penShape = GUI_PS_FLAT;
                canvas->opacity = 0;
                canvas->canvas.rect.x0 = x_pos;
                canvas->canvas.rect.y0 = y_pos;
                canvas->canvas.rect.x1 = x_pos+chart->mBarWidth-1;
                canvas->canvas.rect.y1 = y_bottom_pos;
                gui_node_struct* node = gui_surface_cache_add_node();
                if (node != NULL) {
                    node->type = TYPE_GUI_DRAW_SHAPE_RECT_FILL;
                    node->x = 0;
                    node->y = 0;
                    node->data = canvas;
                    gui_surface_box_canvas_init(node);
                    gui_surface_box_add_node(box, node);
                    canvas ++;
                }
            }
        }
    }
}

static void gui_chart_drawLine(gui_box_struct* box, geometry_rect* rect)
{
    gui_chart_struct* chart = (gui_chart_struct*)box->widget->children;
    gui_chart_info* chart_info = (gui_chart_info*)box->data;
    gui_canvas_struct* canvas = &chart_info->canvas[2+chart->mLabelNum*4];
    unsigned int idx;
    unsigned short pre_x;
    unsigned short pre_y;
    unsigned short cnt = chart->getCount(chart);
    SYS_DEBUG("gui_chart_drawLine");

    if (cnt > 0) {
        for (idx=0; idx<cnt; idx++) {
            short x_val = chart->getXValue(chart, idx);
            short y_val = chart->getYValue(chart, idx);

            unsigned short x_pos = rect->x + (rect->width * (x_val-chart_info->mMinX)) / (chart_info->mMaxX - chart_info->mMinX);
            unsigned short y_pos = (rect->height * (y_val-chart_info->mMinY)) / (chart_info->mMaxY - chart_info->mMinY);
            y_pos = rect->y + rect->height - y_pos;

            if (idx > 0) {
                canvas->AA = 0;
                canvas->fillColor = chart->mColor;
                canvas->penColor = chart->mColor;
                canvas->penSize = 1;
                canvas->penShape = GUI_PS_FLAT;
                canvas->opacity = 0;
                canvas->canvas.line.x0 = pre_x;
                canvas->canvas.line.y0 = pre_y;
                canvas->canvas.line.x1 = x_pos;
                canvas->canvas.line.y1 = y_pos;
                gui_node_struct* node = gui_surface_cache_add_node();
                if (node != NULL) {
                    node->type = TYPE_GUI_DRAW_SHAPE_LINE;
                    node->x = 0;
                    node->y = 0;
                    node->data = canvas;
                    gui_surface_box_canvas_init(node);
                    gui_surface_box_add_node(box, node);
                    canvas ++;
                }
                if (chart->mStyle == CHARTS_STYLE_LINE_AND_FILL) {
                    canvas->AA = 0;
                    canvas->fillColor = chart->mFillColor;
                    canvas->penColor = chart->mFillColor;
                    canvas->penSize = 1;
                    canvas->penShape = GUI_PS_FLAT;
                    canvas->opacity = 0;
                    canvas->canvas.rect.x0 = pre_x;
                    canvas->canvas.rect.y0 = pre_y+2;
                    canvas->canvas.rect.x1 = x_pos;
                    canvas->canvas.rect.y1 = rect->y + rect->height;
                    gui_node_struct* node = gui_surface_cache_add_node();
                    if (node != NULL) {
                        node->type = TYPE_GUI_DRAW_SHAPE_RECT_FILL;
                        node->x = 0;
                        node->y = 0;
                        node->data = canvas;
                        gui_surface_box_canvas_init(node);
                        gui_surface_box_add_node(box, node);
                        canvas ++;
                    }
                }
            }
            else {
                canvas->AA = 0;
                canvas->fillColor = chart->mColor;
                canvas->penColor = chart->mColor;
                canvas->penSize = chart->mBarWidth;
                canvas->penShape = GUI_PS_ROUND;
                canvas->opacity = 0;
                canvas->canvas.point.x = x_pos;
                canvas->canvas.point.y = y_pos;
                gui_node_struct* node = gui_surface_cache_add_node();
                if (node != NULL) {
                    node->type = TYPE_GUI_DRAW_SHAPE_POINT;
                    node->x = 0;
                    node->y = 0;
                    node->data = canvas;
                    gui_surface_box_canvas_init(node);
                    gui_surface_box_add_node(box, node);
                    canvas ++;
                }
            }
            pre_x = x_pos;
            pre_y = y_pos;
        }
    }
}

static void gui_surface_control_chart_update(gui_box_struct* box)
{
    gui_chart_struct* chart = (gui_chart_struct*)box->widget->children;
    gui_chart_info* chart_info = (gui_chart_info*)box->data;
    gui_canvas_struct* canvas = &chart_info->canvas[0];
    short count = chart->getCount(chart);

    geometry_rect frame;

    char     temp[16];
    unsigned int idx, x, y, dlt_x=0, dlt_y=0;
    unsigned int tx, ty, tw, th, tl;

    //SYS_DEBUG("gui: chart_update, flags=%x", chart->mFlags);

    frame.x = 0;
    frame.y = 0;
    frame.width = box->width;
    frame.height = box->height;

    gui_chart_calcRange(box);

    set_font_size(SYS_FONT_SMALL);
    get_font_string_meastrue((unsigned char*)"0", &tw, &th, &tl);

    // draw axis
    if ((chart->mStyle == CHARTS_STYLE_BAR) || (chart->mStyle == CHARTS_STYLE_LINE) || (chart->mStyle == CHARTS_STYLE_LINE_AND_FILL)) {
        if (chart->mFlags & CHARTS_FLG_SHOW_XAXIS) {
            frame.height -= 2;
            if (chart->mFlags & CHARTS_FLG_TOP_XLABEL) {
                frame.y += 2;
                dlt_y += 2;
            }
        }
        if (chart->mFlags & CHARTS_FLG_SHOW_XLABEL) {
            frame.height -= th;
            if (chart->mFlags & CHARTS_FLG_TOP_XLABEL) {
                frame.y += th;
                dlt_y += th;
            }
        }
        if (chart->mFlags & CHARTS_FLG_SHOW_YAXIS) {
            frame.width -= 2;
            if (chart->mFlags & CHARTS_FLG_RIGHT_YLABEL) {
                // ...
            }
            else {
                frame.x += 2;
                dlt_x += 2;
            }
        }
        if (chart->mFlags & CHARTS_FLG_SHOW_YLABEL) {
            if (chart_info->mMaxY >= 1000) {
                tl = tw*4;
            }
            else if (chart_info->mMaxY >= 100) {
                tl = tw*3;
            }
            else if (chart_info->mMaxY >= 10) {
                tl = tw*2;
            }
            else {
                tl = tw;
            }
            frame.width -= tl;
            if (chart->mFlags & CHARTS_FLG_RIGHT_YLABEL) {
                //...
            }
            else {
                frame.x += tl;
                dlt_x += tl;
            }
        }
        //SYS_DEBUG("chart: frame={%d, %d, %d, %d}", frame.x, frame.y, frame.width, frame.height);

        // draw x-Axis
        x = frame.x-dlt_x;
        if (chart->mFlags & CHARTS_FLG_TOP_XLABEL) {
            y = frame.y-dlt_y;
        }
        else  {
            y = frame.y + frame.height;
        }
        if (chart->mFlags & CHARTS_FLG_SHOW_XAXIS) {
            canvas->AA = 0;
            canvas->fillColor = chart->mAxisColor;
            canvas->penColor = chart->mAxisColor;
            canvas->penSize = 2;
            canvas->penShape = GUI_PS_FLAT;
            canvas->opacity = 0;
            canvas->canvas.line.x0 = x;
            canvas->canvas.line.y0 = y;
            canvas->canvas.line.x1 = x+frame.width;
            canvas->canvas.line.y1 = y;
            gui_node_struct* node = gui_surface_cache_add_node();
            if (node != NULL) {
                node->type = TYPE_GUI_DRAW_SHAPE_LINE;
                node->x = 0;
                node->y = 0;
                node->data = canvas;
                gui_surface_box_canvas_init(node);
                gui_surface_box_add_node(box, node);
                canvas ++;
            }
        }
        if ((chart->mFlags & CHARTS_FLG_SHOW_XLABEL) && (chart->mLabelNum != 0)) {
            int val = chart_info->mMinX;
            int val_gap = (chart_info->mMaxX - chart_info->mMinX) / chart->mLabelNum;    // 4
            int rel_val;

            ty = y;
            for (idx=0; idx<chart->mLabelNum; idx++) {
                if (chart->fmtXAxis != NULL) {
                    rel_val = chart->fmtXAxis(chart, val, temp);
                }
                else {
                    rel_val = gui_chart_dumy_fmtXAxis(chart, val, temp);
                }
                SYS_DEBUG("chart: rel_val = %d", rel_val);
                get_font_string_meastrue((unsigned char*)temp, &tw, &th, &tl);

                short x_val = chart->getXValue(chart, rel_val);
                short y_val = chart->getYValue(chart, rel_val);
                short y_bottom = chart->getYBottomValue(chart, rel_val);
                unsigned short x_pos = frame.x + (frame.width * (x_val-chart_info->mMinX)) / (chart_info->mMaxX - chart_info->mMinX);
                unsigned short y_pos = (frame.height * (y_val-chart_info->mMinY)) / (chart_info->mMaxY - chart_info->mMinY);

                y_pos = frame.y + frame.height - y_pos;

                DATA_DEBUG("chart->mFlags & CHARTS_FLG_SHOW_XLABEL %d,%d",y_pos,y_bottom);
                // add text node
                const gui_font_struct* text = (chart->mLabelText == NULL) ? &gui_chart_label_text : chart->mLabelText;
                //gui_node_struct* node = gui_surface_box_label_text_arrange((unsigned char*)temp, text, x_pos-tw/2, ty);
				gui_node_struct* node = gui_surface_box_label_arrange_textbox(box,text,(unsigned char*)temp,x_pos-tw/2, ty,text->width,text->height);
                if (node != NULL) {
                    gui_surface_box_add_node(box, node);
                }

                if ((chart->mFlags & CHARTS_FLG_SHOW_XGRID) && (val < count)) {
                    // xGrid
                    canvas->AA = 0;
                    canvas->fillColor = chart->mGridColor;
                    canvas->penColor = chart->mGridColor;
                    canvas->penSize = 1;
                    canvas->penShape = GUI_PS_FLAT;
                    canvas->opacity = 0;
                    canvas->canvas.line.x0 = x_pos;
                    canvas->canvas.line.y0 = y_pos;
                    canvas->canvas.line.x1 = x_pos;
                    canvas->canvas.line.y1 = ty;
                    canvas->canvas.line.showPixel = 4;
                    canvas->canvas.line.skipPixel = 4;
                    gui_node_struct* node = gui_surface_cache_add_node();
                    if (node != NULL) {
                        node->type = TYPE_GUI_DRAW_SHAPE_LINE;
                        node->x = 0;
                        node->y = 0;
                        node->data = canvas;
                        gui_surface_box_canvas_init(node);
                        gui_surface_box_add_node(box, node);
                        canvas ++;
                    }
                }

                val += val_gap;
            }
        }

        // draw y-Axis
        if (chart->mFlags & CHARTS_FLG_RIGHT_YLABEL) {
            x = frame.x + frame.width;
        }
        else {
            x = frame.x - dlt_x;
        }
        y = frame.y - dlt_y;
        if (chart->mFlags & CHARTS_FLG_SHOW_YAXIS) {
            canvas->AA = 0;
            canvas->fillColor = chart->mAxisColor;
            canvas->penColor = chart->mAxisColor;
            canvas->penSize = 2;
            canvas->penShape = GUI_PS_FLAT;
            canvas->opacity = 0;
            canvas->canvas.line.x0 = x;
            canvas->canvas.line.y0 = frame.y;
            canvas->canvas.line.x1 = x;
            canvas->canvas.line.y1 = frame.y+frame.height;
            gui_node_struct* node = gui_surface_cache_add_node();
            if (node != NULL) {
                node->type = TYPE_GUI_DRAW_SHAPE_LINE;
                node->x = 0;
                node->y = 0;
                node->data = canvas;
                gui_surface_box_canvas_init(node);
                gui_surface_box_add_node(box, node);
                canvas ++;
            }
        }
        if ((chart->mFlags & CHARTS_FLG_SHOW_YLABEL) && (chart->mLabelNum != 0)) {
            int val = chart_info->mMinY;
            int gap = (chart_info->mMaxY - chart_info->mMinY) / (chart->mLabelNum-1);
            int gap_y = 0;
            int i=0;

            tx = x;
            ty = frame.y + frame.height;
            if (chart->mFlags & CHARTS_FLG_SHOW_XLABEL) {
                val += gap;
                i = 1;
                gap_y = (frame.height) / (chart->mLabelNum-1);
                ty -= gap_y;
            }
            else {
                gap_y = (frame.height) / (chart->mLabelNum-1);
                ty -= 4;
            }
            for (; i<chart->mLabelNum; i++) {

                if (chart->fmtYAxis != NULL) {
                    y = chart->fmtYAxis(chart, val, temp);
                }
                else {
                    y = gui_chart_dumy_fmtYAxis(chart, val, temp);
                }
                get_font_string_meastrue((unsigned char*)temp, &tw, &th, &tl);

                // add text node
                const gui_font_struct* text = (chart->mLabelText == NULL) ? &gui_chart_label_text : chart->mLabelText;
                //gui_node_struct* node = gui_surface_box_label_text_arrange((unsigned char*)temp, text, tx, ty-th/2);
				gui_node_struct* node = gui_surface_box_label_arrange_textbox(box,text,(unsigned char*)temp,tx, ty-th/2,text->width,text->height);
                if (node != NULL) {
                    gui_surface_box_add_node(box, node);
                }

                if (chart->mFlags & CHARTS_FLG_SHOW_YGRID) {
                    // ...
                    canvas->AA = 0;
                    canvas->fillColor = chart->mGridColor;
                    canvas->penColor = chart->mGridColor;
                    canvas->penSize = 1;
                    canvas->penShape = GUI_PS_FLAT;
                    canvas->opacity = 0;
                    canvas->canvas.line.x0 = frame.x;
                    canvas->canvas.line.y0 = ty;
                    canvas->canvas.line.x1 = frame.x + frame.width - 1;
                    canvas->canvas.line.y1 = ty;
                    canvas->canvas.line.showPixel = 4;
                    canvas->canvas.line.skipPixel = 4;
                    gui_node_struct* node = gui_surface_cache_add_node();
                    if (node != NULL) {
                        node->type = TYPE_GUI_DRAW_SHAPE_STYLE_LINE;
                        node->x = 0;
                        node->y = 0;
                        node->data = canvas;
                        gui_surface_box_canvas_init(node);
                        gui_surface_box_add_node(box, node);
                        canvas ++;
                    }
                }
                ty -= gap_y;
                val += gap;
            }
        }

        if (chart->mStyle == CHARTS_STYLE_BAR) {
            frame.x += chart->mBarWidth/2;
            frame.width -= chart->mBarWidth;
            gui_chart_drawBar(box, &frame);
        }
        else if ((chart->mStyle == CHARTS_STYLE_LINE) || (chart->mStyle == CHARTS_STYLE_LINE_AND_FILL)) {
            gui_chart_drawLine(box, &frame);
        }
    }
}


void gui_surface_control_chart_create(gui_box_struct* box)
{
    if (box == NULL || box->widget == NULL || (box->type != TYPE_GUI_CONTROL_CHART)) {
        SYS_DEBUG("gui: create_chart: create null");
        return;
    }

    gui_chart_struct* chart = (gui_chart_struct*)box->widget->children;

    //SYS_DEBUG("chart creat: chart=%x !!!!!!!!!!!!!!!!!!!!!!!!!!", (unsigned int)chart);
    if (chart == NULL || chart->getCount == NULL || chart->getXValue == NULL || chart->getYValue == NULL) {
        SYS_DEBUG("gui: create_chart: create error0");
        return;
    }

    SYS_DEBUG("gui: create_chart, %x", (unsigned int)chart);
    short count = chart->xMax+2;  // count = chart->getCount(chart);
    if (chart->mStyle == CHARTS_STYLE_LINE_AND_FILL) {
        count += count;
    }
    count += (2+chart->mLabelNum*4);        // +: x-Axis, y-Axis, x-Label(n), y-Label(n), x-Grid(n), y-Grid(n)

    gui_chart_info* chart_info = os_mem_alloc(RAM_TYPE_DATA_ON, sizeof(gui_chart_info)+sizeof(gui_canvas_struct)*count);
    if (chart_info != NULL) {
        chart_info->mMinX = chart->xMin;
        chart_info->mMaxX = chart->xMax;
        chart_info->mMinY = chart->yMin;
        chart_info->mMaxY = chart->yMax(chart);
        box->data = chart_info;
        gui_surface_control_chart_update(box);
    }
    else {
        SYS_DEBUG("gui: create_chart: create error2");
    }
}

void gui_surface_control_chart_exit(gui_box_struct* box)
{
    //SYS_DEBUG("chart exit!!!!!!!!!!!!!!!!!!!!!!!");
    if ((box != NULL) && (box->data != NULL) && (box->type == TYPE_GUI_CONTROL_CHART)) {
        SYS_DEBUG("gui: exit_chart, %x", (unsigned int)box->widget->children);
        gui_surface_cache_remove_nodes(box->child);
        box->child = NULL;	// 20220830 Taylor.Le, bug
        application_start_user_timer(100, gui_chart_memfree_timer_handler, box->data);
        box->data = NULL;
    }
}

void gui_surface_control_chart_reload(gui_box_struct* box)
{
    gui_chart_info* chart_info;

    if (box == NULL) {
        SYS_DEBUG("gui: reload_chart: reload null");
        return;
    }

    if (box->widget == NULL || (box->type != TYPE_GUI_CONTROL_CHART)) {
        SYS_DEBUG("gui: reload_chart: reload null 2");
        return;
    }

    gui_chart_struct* chart = (gui_chart_struct*)box->widget->children;
    if (chart == NULL || chart->getCount == NULL || chart->getXValue == NULL || chart->getYValue == NULL) {
        SYS_DEBUG("gui: reload_chart: reload error0");
        return;
    }

    gui_surface_cache_remove_nodes(box->child);
    box->child = NULL;	// 20220830 Taylor.Le, bug

    chart_info = (gui_chart_info*)box->data;
    if ((chart_info == NULL) || ((chart_info != NULL) && (chart_info->mMaxX != chart->xMax))) {
        application_start_user_timer(100, gui_chart_memfree_timer_handler, box->data);
        box->data = NULL;

        short count = chart->xMax+2;  // count = chart->getCount(chart);
        if (chart->mStyle == CHARTS_STYLE_LINE_AND_FILL) {
            count += count;
        }
        count += (2+chart->mLabelNum*4);        // +: x-Axis, y-Axis, x-Label(n), y-Label(n), x-Grid(n), y-Grid(n)
        chart_info = os_mem_alloc(RAM_TYPE_DATA_ON, sizeof(gui_chart_info)+sizeof(gui_canvas_struct)*count);
        if (chart_info != NULL) {
            chart_info->mMinX = chart->xMin;
            chart_info->mMaxX = chart->xMax;
            chart_info->mMinY = chart->yMin;
            chart_info->mMaxY = chart->yMax(chart);
            box->data = chart_info;
            gui_surface_control_chart_update(box);
            SYS_DEBUG("gui: reload_chart 0, %x", (unsigned int)box->widget->children);
        }
        else {
            SYS_DEBUG("gui: reload_chart: reload error2");
        }
    }
    else {
        gui_surface_control_chart_update(box);
        SYS_DEBUG("gui: reload_chart 1, %x", (unsigned int)box->widget->children);
    }
}


