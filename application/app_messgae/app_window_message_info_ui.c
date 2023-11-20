
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "font_convert.h"
#include "os_mem.h"


#include "data_message.h"


#include "gui_surface_cache.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_node.h"
#include "gui_surface_box_layout_item.h"

#include "app_window_message_common.h"

#include "app_window_message_list.h"
#include "app_window_message_delete_all.h"


#include "app_window_message_info.h"
#include "app_window_message_info_ui.h"
#include "app_window_message_info_layout.h"

static unsigned short g_msg_num;

unsigned short g_curr_msg_index;
unsigned char  g_timer_exit;

// -----------------------------------------------------------------------------------------------------------------
void app_window_message_info_update(void)
{
    picture_info_struct *msg_icon;
    picture_info_struct *bg_img;

    gui_surface_struct *surface = gui_surface_get_surface(&gui_message_info_screen);
    gui_layout_scroll_struct *scroll = &surface->layout.scroll;
    gui_box_struct *box;

    data_message_ext_struct* msg_info;

    unsigned int   msg_items, title_ch_num=0, check_idx, dispHeight;
    unsigned char  attribute, attr_len;

    g_msg_num = data_message_count();
    if (g_curr_msg_index >= g_msg_num)
    {
        g_curr_msg_index = 0;
    }
    if (g_msg_num > DISP_MESSAGE_NUM)
    {
        g_msg_num = DISP_MESSAGE_NUM;
    }
    SYS_DEBUG("msg_info: num=%d, index=%d", g_msg_num, g_curr_msg_index);
    if (g_msg_num != 0)
    {
        msg_info = os_mem_alloc(RAM_TYPE_DATA_ON, sizeof(data_message_ext_struct) + DATA_MESSAGE_LEN);
        if (msg_info != NULL)
        {
            title_ch_num = data_message_get_ext(g_curr_msg_index, msg_info, (unsigned char*)(msg_info+1));
            msg_icon = app_message_get_picture_by_type(msg_info->type);
            SYS_DEBUG("msg[%d]: type=%d, title_ch_num=%d", g_curr_msg_index, msg_info->type, title_ch_num);

            box = gui_surface_get_box(&gui_message_info_screen, APP_MESSAGE_INFO_TIME);
            if (box != NULL) {
                box->y = (float)MSG_TIME_Y_POS;
                gui_surface_box_label_change_string(box, msg_info->time);
            }
            box = gui_surface_get_box(&gui_message_info_screen, APP_MESSAGE_INFO_ICON);
            if (box != NULL) {
                box->y = (float)MSG_ICON_Y_POS;
                gui_surface_box_image_change(box, msg_icon);
            }

            // info
            box = gui_surface_get_box(&gui_message_info_screen, APP_MESSAGE_INFO_TITLE);
            if (box != NULL) {
                box->y = (float)MSG_BODY_Y_POS;
                gui_node_struct* new_node = gui_surface_box_label_arrange_content(box, &gui_message_info_body_text, msg_info->message);
                if (new_node != NULL) {
                    // 改变title字符的颜色
                    gui_node_struct* title_node = new_node->child;
                    for (check_idx=0; ((check_idx<title_ch_num) && (title_node != NULL)); check_idx++) {
                        title_node->data = &gui_message_info_title_text;
                        title_node = title_node->child;
                    }
                    //SYS_DEBUG("set msg body!!!");
                    gui_surface_node_replace_brother(box,box->child,new_node);
                    box->height = (float)(new_node->value);
                    dispHeight = new_node->value;
                }
            }

            // 根据文字显示高度new_node->value，计算背景图高度，...
            box = gui_surface_get_box(&gui_message_info_screen, APP_MESSAGE_INFO_BG_TOP);
            if (box != NULL) {
                box->y = (float)MSG_BG_Y_POS;
            }
            box = gui_surface_get_box(&gui_message_info_screen, APP_MESSAGE_INFO_BG_MID);
            if (box != NULL) {
                box->y = (float)(MSG_BG_Y_POS + MSG_BG_TOP_H);
                box->height = (float)dispHeight;
                gui_message_info_bg_mid_rect.canvas.rect.y1 = dispHeight-1;
                gui_surface_box_canvas_flush(box, 1);
            }
            box = gui_surface_get_box(&gui_message_info_screen, APP_MESSAGE_INFO_BG_BOT);
            if (box != NULL) {
                box->y = (float)(MSG_BG_Y_POS + MSG_BG_TOP_H + dispHeight);
            }
            os_mem_free(msg_info);
        }
        scroll->scroll = 1;
        scroll->height = (short)(box->y + box->height + 20);
        scroll->offset_y = 0;
        scroll->min_offset = LCD_SIZE_HEIGHT - scroll->height - MSG_OP_BAR_H;
        scroll->max_offset = 0;
        if (scroll->min_offset > scroll->max_offset) {
            scroll->min_offset = scroll->max_offset;
        }
        scroll->item_gap   = LCD_SIZE_HALF_HEIGHT/4;
        SYS_DEBUG("scroll_height=%d, min=%d, max=%d", scroll->height, scroll->min_offset, scroll->max_offset);
    }
}

