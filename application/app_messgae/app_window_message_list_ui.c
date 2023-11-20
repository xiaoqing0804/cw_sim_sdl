#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "font_convert.h"
#include "os_mem.h"


#include "data_message.h"

#include "gui_surface.h"
#include "gui_surface_cache.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_node.h"
#include "gui_surface_box_layout_item.h"

#include "app_window_message_common.h"
#include "app_window_message_list.h"
#include "app_window_message_list_ui.h"
#include "app_window_message_list_layout.h"


static const picture_info_struct *g_msg_del_images[] =
    {
        &pic_message_deletect_one_l1_info,
        &pic_message_deletect_one_l2_info,
        &pic_message_deletect_one_info,
};
static const picture_info_struct *g_msg_bg_images[] =
    {
        &pic_message_bg_l1_info,
        &pic_message_bg_l2_info,
        &pic_message_bg_info,
};
#define MSG_BG_IMAGES_NUM (sizeof(g_msg_bg_images) / sizeof(g_msg_bg_images[0]))

static gui_box_struct *g_msg_cv_delete_box;
static unsigned int g_msg_cv_num;


static void app_window_message_list_clear_item(gui_surface_struct *surface)
{
    gui_box_struct *box = gui_surface_get_box_by_type(surface, TYPE_GUI_CONTROL_LAYOUT_ITEM);
    while (box != NULL)
    {
        gui_surface_remove_box(surface, box);
        gui_surface_cache_remove_box_and_children(box);
        box = gui_surface_get_box_by_type(surface, TYPE_GUI_CONTROL_LAYOUT_ITEM);
    }
}

static int app_window_message_repace_char(gui_node_struct *node, int x_pos)
{
    static unsigned short txt_y_pos = 0;

    font_char_info_struct dot_char_info;
    unsigned short ch = 0x00B7; // MIDDLE DOT
    if (get_font_char_info_from_size_code(gui_message_item_subject_txt.size, ch, &dot_char_info))
    {
        if (x_pos > 0) {
            node->x = x_pos;
        }
        else {
            node->x += (node->clip_width - dot_char_info.xSize)/2;
            txt_y_pos = node->y + (node->clip_height - dot_char_info.ySize)/2;
        }
        node->y = txt_y_pos;//(node->clip_height - dot_char_info.ySize)/2;
        node->width = (float)dot_char_info.xDist;
        node->height= dot_char_info.ySize;

        //node->clip_x = dot_char_info.xPos;
        //node->clip_y = dot_char_info.yPos;
        node->clip_width = dot_char_info.xSize;
        node->clip_height = dot_char_info.ySize;
        node->value = ch;
        x_pos = node->x + node->width;
    }
    return x_pos;
}

static void app_window_message_check_text_length(gui_node_struct *text_box, unsigned int text_height)
{
    unsigned int flag = 0;
    gui_node_struct *node = text_box->child;

    SYS_DEBUG("app: message_check_text_length, %d", text_height);
    while (node != NULL)
    {
        if ((node->y + node->height) > text_height)
        {
            flag = 1;
            break;
        }
        node = node->child;
    }

    if (flag && node != NULL)
    {
        gui_node_struct *f_node0;
        gui_node_struct *f_node1;
        gui_node_struct *f_node2;
        int x_pos = -1;
        SYS_DEBUG("node: y=%f, h=%f, ch=%x, type=%d", node->y, node->height, node->value, node->type);
        f_node0 = gui_surface_cache_find_front_in_child(text_box, node);
        if (f_node0)
        {
            SYS_DEBUG("node0: ch=%x", f_node0->value);
            f_node1 = gui_surface_cache_find_front_in_child(text_box, f_node0);
            if (f_node1 != NULL)
            {
                SYS_DEBUG("node1: ch=%x", f_node1->value);
                f_node2 = gui_surface_cache_find_front_in_child(text_box, f_node1);
                if (f_node2 != NULL)
                {
                    SYS_DEBUG("node2: ch=%x", f_node2->value);
                    x_pos = app_window_message_repace_char(f_node2, x_pos); // f_node2->value = '.';
                }
                x_pos = app_window_message_repace_char(f_node1, x_pos); // f_node1->value = '.';
            }
            x_pos = app_window_message_repace_char(f_node0, x_pos); // f_node0->value = '.';
            f_node0->child = NULL;
        }

        // delect after
        gui_surface_cache_remove_node(node);
    }
}

static void app_window_message_list_ui_update_visable(unsigned int num)
{
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_message_list);
    gui_layout_scroll_struct *scroll = &surface->layout.scroll;
    gui_box_struct *box;

    if (num == 0) {
        scroll->scroll = 0;
        box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT);
        if (box != NULL)
            box->visible = 0;
        box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT_ONE);
        if (box != NULL)
            box->visible = 0;
        box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_EMPTY);
        if (box != NULL)
            box->visible = 1;

        scroll->scroll = 0;
    }
    else {
        box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT);
        if (box != NULL)
            box->visible = 1;
        box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT_ONE);
        if (box != NULL)
            box->visible = 0;
        box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_EMPTY);
        if (box != NULL)
            box->visible = 0;
    }
}


void app_window_message_list_ui_update(void)
{
    picture_info_struct *msg_icon;
    picture_info_struct *bg_img;

    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_message_list);
    gui_layout_scroll_struct *scroll = &surface->layout.scroll;
    gui_box_struct *box;

    data_message_ext_struct* msg_info;

    int box_y = GUI_CONTENT_GAP_TOP, box_h;
    unsigned int index, title_ch_num = 0;

    // 删除items
    app_window_message_list_clear_item(surface);

    g_msg_cv_num = data_message_count();
    if (g_msg_cv_num > DISP_MESSAGE_NUM)
    {
        g_msg_cv_num = DISP_MESSAGE_NUM;
    }
    SYS_DEBUG("msg: num=%d", g_msg_cv_num);
    app_window_message_list_ui_update_visable(g_msg_cv_num);
    if (g_msg_cv_num > 0) {
        msg_info = os_mem_alloc(RAM_TYPE_DATA_ON, sizeof(data_message_ext_struct)+DATA_MESSAGE_LEN); // + title & body
        if (msg_info != NULL)  {
            for (index = 0; index < g_msg_cv_num; index++) {
                title_ch_num = data_message_get_ext(index, msg_info, (unsigned char*)(msg_info+1));
                msg_icon = app_message_get_picture_by_type(msg_info->type);
                SYS_DEBUG("msg[%d]: type=%d, title_ch_num=%d", index, msg_info->type, title_ch_num);

                box = gui_surface_box_create(surface, &gui_message_item_widget);
                if (box != NULL) {
                    unsigned int check_idx = 0, dispWidth = gui_message_item_subject_txt.width, dispHeight = 0, lines_flg = 0;
                    unsigned char fnt_sz;

                    bg_img = g_msg_bg_images[MSG_BG_IMAGES_NUM - 1];

                    gui_surface_box_layout_item_change_image(box, APP_MESSAGE_ITEM_CV_ICON_ID, msg_icon);
                    gui_surface_box_layout_item_change_string(box, APP_MESSAGE_ITEM_CV_TIME_ID, msg_info->time);

                    gui_node_struct *body_node = gui_surface_node_find_by_id(box, APP_MESSAGE_ITEM_CV_SUBJECT_ID);
                    if (body_node != NULL) {
                        gui_node_struct *new_node = gui_surface_box_label_arrange_content(box, &gui_message_item_subject_txt, msg_info->message);
                        if (new_node != NULL) {
                            // 改变title字符的颜色
                            gui_node_struct *title_node = new_node->child;
                            for (check_idx = 0; ((check_idx < title_ch_num) && (title_node != NULL)); check_idx++) {
                                title_node->data = &gui_message_item_title_txt;
                                title_node = title_node->child;
                            }
                            // SYS_DEBUG("set msg body!!!");
                            gui_surface_node_replace_brother(box, body_node, new_node);

                            // 根据文字显示高度new_node->value，计算背景图高度，选择背景图 & 改变 box 的高度...
                            dispHeight = new_node->value + gui_message_item_subject_txt.y - gui_message_item_bg_img.y;
                            for (check_idx = 0; check_idx < MSG_BG_IMAGES_NUM; check_idx++) {
                                if (g_msg_bg_images[check_idx]->height > dispHeight) {
                                    bg_img = g_msg_bg_images[check_idx];
                                    break;
                                }
                            }
                            if (check_idx >= MSG_BG_IMAGES_NUM)  {
                                // 将超出长度的文字删除
                                app_window_message_check_text_length(new_node, gui_message_item_bg_img.y + bg_img->height - gui_message_item_subject_txt.y);
                            }
                        }
                    }

                    box_h = gui_message_item_bg_img.y + bg_img->height + MSG_ITEM_GAP;
                    SYS_DEBUG("box_y=%d, box_h=%d", box_y, box_h);
                    box->y = (float)box_y;
                    box->height = (float)box_h;
                    SYS_DEBUG("box_y=%f, box_h=%f", box->y, box->height);
                    gui_surface_box_layout_item_change_image(box, APP_MESSAGE_ITEM_CV_BG_ID, bg_img);

                    box_y += box->height;
                    box->id = MSG_ITEM_BOX_BASE_ID + index;
                    gui_surface_add_box(surface, box);
                }
            }
            os_mem_free(msg_info);
        }
        SYS_DEBUG("app: window_message_list_load, ooo");

        // 改变 del-all 的位置
        box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT);
        if (box != NULL) {
            if(box_y + box->height < LCD_SIZE_HEIGHT)
            {
                box->y = LCD_SIZE_HEIGHT - box->height;
                box->fix = 1;
            }
            else
            {
                box->y = box_y;
                box->fix = 0;
            }
        }

        scroll->scroll = 1;
    #if (LCD_SHAPE == LCD_CIRCLE)
        scroll->height = box_y + box->height;
    #else
        scroll->height = box_y + box->height+32;       // +32
    #endif
        scroll->offset_y = 0;
        scroll->min_offset = LCD_SIZE_HEIGHT - scroll->height;
        scroll->max_offset = 0;
        if (scroll->min_offset > scroll->max_offset) {
            scroll->min_offset = scroll->max_offset;
        }
        scroll->item_gap = LCD_SIZE_HALF_HEIGHT / 4;
        SYS_DEBUG("scroll_height=%d", scroll->height);
        SYS_DEBUG("scroll->min_offset=%d", scroll->min_offset);
        SYS_DEBUG("scroll->max_offset=%d", scroll->max_offset);
    }
}


void app_window_message_list_ui_init(void)
{
    g_msg_cv_delete_box = NULL;
    g_msg_cv_num = 0;
}


unsigned char app_window_message_list_ui_touch(gui_touch_struct *envent)
{
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_message_list);
    gui_box_struct *box;

    SYS_DEBUG("app: message_list_event_touch, g_msg_cv_num = %d", g_msg_cv_num);
    if (g_msg_cv_num == 0) {
        return 0;
    }

    if (envent->type == TOUCH_EVENT_TYPE_UP)
    {
        if (envent->direction == DIRECTION_TYPE_LEFT)
        {
            gui_box_struct *del_box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT_ONE);
            if ((g_msg_cv_delete_box != NULL) && (del_box != NULL) && (del_box->visible))
            {
                g_msg_cv_delete_box->x = 0;
                g_msg_cv_delete_box = NULL;
                del_box->visible = 0;
                gui_surface_commit();
            }
            else
            {
                application_go_back();
            }
            return 1;
        }
        else if (envent->direction == DIRECTION_TYPE_RIGHT)
        {
            if (g_msg_cv_delete_box != NULL)
            {
                g_msg_cv_delete_box->x = -(pic_message_deletect_one_info.width + 20);
                box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT_ONE);
                if (box != NULL)
                {
                    unsigned int img_idx = 0;
                    if (g_msg_cv_delete_box->height > g_msg_bg_images[2]->height)
                    {
                        img_idx = 2;
                    }
                    else if (g_msg_cv_delete_box->height > g_msg_bg_images[1]->height)
                    {
                        img_idx = 1;
                    }
                    box->visible = 1;
                    box->y = g_msg_cv_delete_box->y + gui_message_item_bg_img.y;
                    box->height = g_msg_del_images[img_idx]->height;
                    gui_surface_box_image_change(box, g_msg_del_images[img_idx]);
                }
                gui_surface_commit();
            }
            return 1;
        }
        else
        {
            g_msg_cv_delete_box = NULL;
        }
    }
    else if (envent->type == TOUCH_EVENT_TYPE_DOWN)
    {
        box = gui_surface_get_by_position(surface, envent->x, envent->y);
        if (box != NULL && box->type == TYPE_GUI_CONTROL_LAYOUT_ITEM)
        {
            if ((g_msg_cv_delete_box != NULL) && (g_msg_cv_delete_box != box))
            {
                gui_box_struct *del_box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT_ONE);
                if ((del_box != NULL) && (del_box->visible))
                {
                    del_box->visible = 0;
                    g_msg_cv_delete_box->x = 0;
                    g_msg_cv_delete_box = NULL;
                    gui_surface_commit();
                }
            }
            g_msg_cv_delete_box = box;
            return 1;
        }
    }
    else if (envent->type == TOUCH_EVENT_TYPE_MOVE)
    {
        if (g_msg_cv_delete_box != NULL)
        {
            return 1;
        }
    }
    return 0;
}


void app_window_message_list_ui_delect_one(gui_click_struct *event)
{
    // gui_surface_struct*     surface = gui_surface_get_surface(&gui_screen_message_list);
    gui_box_struct *box;

    if (g_msg_cv_delete_box != NULL)
    {
        unsigned int idx = g_msg_cv_delete_box->id - MSG_ITEM_BOX_BASE_ID;
        SYS_DEBUG("app: message_list_delect_one, idx=%d, num=%d", idx, g_msg_cv_num);
        if (idx < g_msg_cv_num)
        {
            data_message_delete(idx);
            app_window_message_list_ui_update();
        }
        box = gui_surface_get_box(&gui_screen_message_list, APP_MESSAGE_CV_LIST_DELECT_ONE);
        if (box != NULL)
        {
            box->visible = 0;
        }
        g_msg_cv_delete_box = NULL;
        gui_surface_commit();
    }
}
