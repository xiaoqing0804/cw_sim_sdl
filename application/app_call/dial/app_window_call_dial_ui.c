
#include "bsp_includes.h"

#include "data_manager_message.h"
#include "srv_call.h"

#include "app_call/app_window_call.h"

#include "app_window_call_dial_layout.h"
#include "app_window_call_dial_ui.h"

//****************************************************call dial****************************************************//
/// @brief 是否显示输入号码
/// @param void
static int app_window_input_number_estimate(void)
{
    gui_box_struct *box;

#if defined(__EXT_BT_AUDIO__)
    /* display ble connect. */
    if (ext_btaud_status_get()->dev_status > 0)
    {
        box = gui_surface_get_box(&app_call_dial_screen, CALL_DIAL_NUMBER_ID);
        if (box != NULL)
        {
            gui_surface_box_change_visible(box, 1);
            gui_surface_box_label_change_string(box, (unsigned char *)AU_call_num);
        }
    }
    else
#endif
    {
        box = gui_surface_get_box(&app_call_dial_screen, CALL_DIAL_NUMBER_ID);
        if (box != NULL)
        {
            gui_surface_box_change_visible(box, 0);
        }
    }
}

void app_input_number_estimate(void)
{
    app_window_input_number_estimate();
}

/// @brief 点击拨号盘响应的区域
/// @param int x
/// @param int y
// 按照人的视觉习惯，将触控区域往下偏移一些...
static const geometry_rect c_call_dialpad_rect = {0, 99, 466, 300};
static const geometry_rect c_call_dialpad_callout = {0, 399, 466, 78};

static int call_dial_get_padpos(int x, int y)
{
    static const char pad_num[12] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '0', 0x14};
    int row, col;

    x -= (c_call_dialpad_rect.x + 1);
    y -= (c_call_dialpad_rect.y + 1);
    row = y * 4 / c_call_dialpad_rect.height;
    col = x * 3 / c_call_dialpad_rect.width;
    SYS_DEBUG("x = %d y=%d row= %d col =%d ", x, y, row, col);
    return pad_num[row * 3 + col];
}


static void app_window_call_dial_del_number(void)
{
    unsigned char len = strlen((const char *)AU_call_num);
    if (len > 0) {
        AU_call_num[len - 1] = 0;
    }
}

static void app_window_call_dial_callout(void)
{
    if (ext_btaud_status_get()->dev_status > 0) {
        if (AU_call_num[0] > 0) {
            unsigned char len = strlen((const char *)AU_call_num);

            #if defined(__EXT_BT_AUDIO__)
            ext_btaud_send_cmd(AU_CMD_CALL_DIAL, (unsigned char *)AU_call_num, len);
            #endif

            srv_call_info *call = srv_call_get_info(0);
            if (call != NULL) {
                application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_call_outgoing, NULL);
                memset(AU_call_num, 0, sizeof(AU_call_num));
            }
            return;
        }
    }
}

/// @brief 点击拨号盘响应的处理
/// @param char clickx
/// @param char clicky
void app_window_call_dial_pad_click_handler_function(int clickx, int clicky)
{
    unsigned char len = strlen((const char *)AU_call_num);
    if (check_rect_contain_point_xy((geometry_rect *)&c_call_dialpad_callout, clickx, clicky))  {
        app_window_call_dial_callout();
    }
    else if (check_rect_contain_point_xy((geometry_rect *)&c_call_dialpad_rect, clickx, clicky)) {
        int ret = call_dial_get_padpos(clickx, clicky);
        if (ret == 0x13) {
			app_window_call_dial_callout();
        }
		else if (ret == 0x14) {
			app_window_call_dial_del_number();
		}
        else {
            if (len < 0xF)  {
                AU_call_num[len] = ret;
            }
        }
    }
    else {
        return;
    }

    gui_box_struct *box = gui_surface_get_box(&app_call_dial_screen, CALL_DIAL_NUMBER_ID);
    if (box != NULL)
    {
        gui_surface_box_label_change_string(box, (unsigned char *)AU_call_num);
        gui_surface_commit();
    }
}


void app_window_call_dial_del_click_handler(void)
{
    gui_box_struct *box = gui_surface_get_box(&app_call_dial_screen, CALL_DIAL_NUMBER_ID);
    if (box != NULL)
    {
        app_window_call_dial_del_number();
        gui_surface_box_label_change_string(box, (unsigned char *)AU_call_num);
        gui_surface_commit();
    }
}


/// @brief 是否连接蓝牙
/// @param void
static void app_window_ble_status_function(void)
{
    gui_box_struct *box;

    if ((ext_btaud_status_get()->dev_status > 0))
    {
        box = gui_surface_get_box(&app_call_dial_screen, CALL_DIAL_NUMBER_ID);
        if (box != NULL)
        {
            gui_surface_box_change_visible(box, 1);
            gui_surface_box_label_change_string(box, (unsigned char *)AU_call_num);
        }
    }
}


void app_window_ble_status_function_invoking(void)
{
    app_window_ble_status_function();
}


//****************************************************call dial****************************************************//
