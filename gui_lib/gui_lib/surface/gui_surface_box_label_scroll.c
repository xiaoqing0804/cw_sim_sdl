#include "gui_surface_box_label_scroll.h"

#include "debug_info.h"
#include "feature_all.h"
#include "font_lang.h"
#include "gui_surface_box_label.h"
#include "system_util_all.h"
#include "gui_event_core_list.h"
#include "gui_drivers_display.h"

#define LABEL_SCROLL_TIMER_DEALY (30)   // 定时器的延时启动时间     解决滚动时第一次滑动到此界面闪烁问题
#define LABEL_SCROLL_TIMER_INTERVAL (30) // 定时器的启动时间
#define LABEL_SCROLL_MOVE_GAP_X (2)      // 每次在X方向移动的间隔
#define LABEL_SCROLL_GAP_DIVIDE (4)      // 尾部到头部的距离是长度的多少等分

static unsigned int g_label_scroll_timer_id = 0;

static gui_node_struct *gui_surface_box_label_find_x_last(gui_node_struct *text_node)
{
    gui_node_struct *node = text_node->child;
    gui_node_struct *last_node = node;
    while (node != NULL)
    {
        if (font_lang_is_right_to_left())
        {
            if (last_node->x > node->x)
            {
                last_node = node;
            }
        }
        else
        {
            if (last_node->x < node->x)
            {
                last_node = node;
            }
        }
        node = node->child;
    }
    return last_node;
}

static unsigned char gui_surface_box_label_scroll_node(gui_box_struct *box, gui_node_struct *node)
{
    if (box == NULL || node == NULL)
        return 0;

    if (node->type == TYPE_GUI_DRAW_TEXT_BOX && node->is_scroll)
    {
        gui_node_struct *last_node = gui_surface_box_label_find_x_last(node);
        gui_node_struct *text_node = node->child;
        while (text_node != NULL)
        {
            //阿拉伯语等右到左书写的文字时，text_node->tag为负数
            if (font_lang_is_right_to_left())
            {
                text_node->x += LABEL_SCROLL_MOVE_GAP_X;
                if (text_node->x > node->clip_x + node->clip_width)
                {
                    text_node->x = last_node->x + text_node->tag;
                    last_node = text_node;
                }
            }
            else
            {
                text_node->x -= LABEL_SCROLL_MOVE_GAP_X;
                if (text_node->x + text_node->width < 0)
                {
                    text_node->x = last_node->x + text_node->tag;
                    last_node = text_node;
                }
            }
            text_node = text_node->child;
        }
        gui_surface_box_label_check_clip(box, node);
        return 1;
    }
    return 0;
}

// 检查BOX是否有需要滚动的
static unsigned char gui_surface_box_label_scroll_box(gui_box_struct *box)
{
    if (box == NULL)
        return 0;

    if (box->visible == 0)
        return 0;

    unsigned char result = 0;
    gui_node_struct *node = box->child;
    while (node != NULL)
    {
        if (gui_surface_box_label_scroll_node(box, node))
        {
            result = 1;
        }
        node = node->brother;
    }
    return result;
}

// 检查整个面是否有需要滚动的
static unsigned char gui_surface_box_label_scroll_surface()
{
    unsigned char result = 0;
    for (unsigned char i = 0; i < GUI_SURFACE_LIST_TOTAL; i++)
    {
        gui_surface_struct *surface = gui_surface_get_surface_by_index(i);
        if (surface != NULL)
        {
            gui_box_struct *box = surface->child;
            while (box != NULL)
            {
                if (gui_surface_box_label_scroll_box(box))
                {
                    result = 1;
                }
                box = box->brother;
            }
        }
    }
    gui_surface_commit();
    return result;
}

// 把文字间隔存储到tag中
static void gui_surface_box_label_scroll_save_gap(gui_node_struct *node)
{
    while (node != NULL)
    {
        if (node->type == TYPE_GUI_DRAW_TEXT_BOX && node->is_scroll && node->tag == 0)
        {
            node->tag = 1;

            gui_node_struct *frist_text_node = node->child;
            gui_node_struct *next_text_node = NULL;
            gui_node_struct *text_node = frist_text_node;
            while (text_node != NULL)
            {
                // 存入本node与前一个node的间隔
                next_text_node = text_node->child;
                if (next_text_node != NULL)
                {
                    next_text_node->tag = next_text_node->x - text_node->x;

                    GUI_DEBUG("gui_surface_box_label_scroll_init next_text_node->tag=%d", next_text_node->tag);
                }
                // 第一个node与前一个的间隔是最后一个node的宽度以及剪切区的1/LABEL_SCROLL_GAP_DIVIDE
                else if (frist_text_node != NULL)
                {
                    //阿拉伯文等其他右到左书写的文字，计算第一个字符滚动后与最后一个字符的间隔时，需计算为负数
                    if (font_lang_is_right_to_left())
                    {
                        frist_text_node->tag = -(frist_text_node->width + node->clip_width / LABEL_SCROLL_GAP_DIVIDE);
                    }
                    else
                    {
                        frist_text_node->tag = text_node->width + node->clip_width / LABEL_SCROLL_GAP_DIVIDE;
                    }
                    GUI_DEBUG("gui_surface_box_label_scroll_init frist_text_node->tag=%d", frist_text_node->tag);
                }
                text_node = text_node->child;
            }
        }
        node = node->brother;
    }
}

static void gui_surface_box_label_scroll_timer(unsigned int timer, void *param)
{
    gui_surface_box_label_scroll_end();
    if (gui_surface_box_label_scroll_surface() && !gui_display_isSuspended()) // 灭屏时，不启动scroll-text
    {
        g_label_scroll_timer_id = application_start_user_timer(LABEL_SCROLL_TIMER_INTERVAL, gui_surface_box_label_scroll_timer, NULL);
    }
}

unsigned char gui_surface_box_label_scroll_start(gui_node_struct *text_box)
{
    gui_surface_box_label_scroll_save_gap(text_box);
    if (g_label_scroll_timer_id == 0 && !gui_display_isSuspended()) // 灭屏时，不启动scroll-text
    {
        g_label_scroll_timer_id = application_start_user_timer(LABEL_SCROLL_TIMER_DEALY, gui_surface_box_label_scroll_timer, NULL);
    }
}

unsigned char gui_surface_box_label_scroll_restart()
{
    if (g_label_scroll_timer_id == 0 && !gui_display_isSuspended()) // 灭屏时，不启动scroll-text
    {
        g_label_scroll_timer_id = application_start_user_timer(LABEL_SCROLL_TIMER_DEALY, gui_surface_box_label_scroll_timer, NULL);
    }
}

unsigned char gui_surface_box_label_scroll_end()
{
    if (g_label_scroll_timer_id > 0)
    {
        application_stop_user_timer(g_label_scroll_timer_id);
    }
    g_label_scroll_timer_id = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////
// 灭屏时，停止scroll-text
static unsigned char gui_surface_box_label_scroll_event_enable(void)
{
    return gui_surface_box_label_scroll_surface();
}

static void gui_surface_box_label_scroll_event_suspend(void *buf)
{
    gui_surface_box_label_scroll_end();
}

static void gui_surface_box_label_scroll_event_resume(void *buf)
{
    gui_surface_box_label_scroll_start(NULL);
}

const gui_static_event_struct g_suface_scroll_text_suspend_event =
    {
        .id = EVENT_GUI_SUSPENDED,
        .enable = gui_surface_box_label_scroll_event_suspend,
        .handler = gui_surface_box_label_scroll_event_enable,
};
const gui_static_event_struct g_suface_scroll_text_resume_event =
    {
        .id = EVENT_GUI_RESUMED,
        .enable = gui_surface_box_label_scroll_event_resume,
        .handler = gui_surface_box_label_scroll_event_enable,
};
