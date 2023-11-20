
#include "sys_init.h"
#include "bsp_includes.h"
#include "data_common.h"
#include "data_receive_package.h"
#include "os_mem.h"

#include "srv_alipay.h"

#include "gui_surface_box_label.h"
#include "gui_surface_box_image.h"

#if TCFG_PAY_ALIOS_ENABLE
#include "app_window_alipay_menu.h"
#include "app_window_alipay_bind.h"
#include "app_window_alipay_setting.h"
#include "app_window_alipay_common.h"

static const gui_font_struct gui_alipay_setting_title_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SETTING,
};

static const gui_font_struct gui_alipay_setting_nick_name_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    //.auto_wrap = 1,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "alipay",
};

static const gui_font_struct gui_alipay_setting_account_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    //.auto_wrap = 1,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(150, 150, 150),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "alipay",
};

static const gui_font_struct gui_alipay_setting_unbind_cfm_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .auto_wrap = 1,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_TOP),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_TOP),
    .space_y    = 10,
    .color = COLOR_RGB(150, 150, 150),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "unbind?",
};

static const gui_font_struct gui_alipay_setting_unbinded_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .auto_wrap = 1,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_TOP),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_TOP),
    .space_y    = 10,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "unbinded!",
};


static const gui_image_struct gui_alipay_bar1_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_zhifubao_op1_h_bg_info,
};

static const gui_font_struct gui_alipay_setting_unbind_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_UNBIND,
};



// ----------------------------------------------------------------------------------------------
static const gui_font_struct gui_alipay_op_cancel_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_CANCEL,
};

static const gui_font_struct gui_alipay_op_ok_text =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(0, 0, 0),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_ALIPAY_OK,
};

static const gui_image_struct gui_alipay_bar2_ok =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_zhifubao_op2_bg_info,
};

static const gui_image_struct gui_alipay_bar2_cancel =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .data = &pic_zhifubao_op2_h_bg_info,
};


enum
{
    ALIPAY_SETTING_TITLE_ID = 10,
    ALIPAY_SETTING_USER_ACC_ID,
    ALIPAY_SETTING_USER_NAME_ID,

    ALIPAY_SETTING_UNBIND_CFM_ID,
    ALIPAY_SETTING_INFO_TEXT_ID,

    ALIPAY_SETTING_BAR_IMG_ID,
    ALIPAY_SETTING_BAR_TXT_ID,

    ALIPAY_SETTING_OK_ID,
    ALIPAY_SETTING_CANCEL_ID,
    ALIPAY_SETTING_OK_TXT_ID,
    ALIPAY_SETTING_CANCEL_TXT_ID
};

static const gui_widget_struct gui_alipay_widget_setting[] =
{
    // title
	{
		.id = ALIPAY_SETTING_TITLE_ID,
		.type = TYPE_GUI_CONTROL_LABEL,
		.y = ALIPAY_TITLE_TEXT_Y_POS,
		.width = LCD_SIZE_WIDTH,
		.height = ALIPAY_TITLE_TEXT_H,
		.visible= 1,
        .child_num = 1,
        .children = &gui_alipay_setting_title_text,
	},

    // user
    {
        .id = ALIPAY_SETTING_USER_NAME_ID,
        .type = TYPE_GUI_CONTROL_SCROLL_TEXT,
        .y = LCD_SIZE_HALF_HEIGHT - (ALIPAY_TITLE_TEXT_H*3/2),
        .width = LCD_SIZE_WIDTH,
        .height = ALIPAY_TITLE_TEXT_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_setting_nick_name_text,
    },
    {
        .id = ALIPAY_SETTING_USER_ACC_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = LCD_SIZE_HALF_HEIGHT - 5,
        .width = LCD_SIZE_WIDTH,
        .height = ALIPAY_TITLE_TEXT_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_setting_account_text,
    },

    // unbind cfm?
    {
        .id = ALIPAY_SETTING_UNBIND_CFM_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = ALIPAY_INFO_TEXT_X_POS,
        .y = ALIPAY_INFO_TEXT_Y_POS,
        .width = LCD_SIZE_WIDTH - ALIPAY_INFO_TEXT_X_POS*2,
        .height = ALIPAY_INFO_TEXT_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_setting_unbind_cfm_text,
    },

    // unbinded!
    {
        .id = ALIPAY_SETTING_INFO_TEXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = ALIPAY_INFO_TEXT_X_POS,
        .y = ALIPAY_INFO_TEXT_Y_POS,
        .width = LCD_SIZE_WIDTH - ALIPAY_INFO_TEXT_X_POS*2,
        .height = ALIPAY_INFO_TEXT_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_setting_unbinded_text,
    },

    // bar1
    {
        .id = ALIPAY_SETTING_BAR_IMG_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = (LCD_SIZE_WIDTH-ALIPAY_OP1_BAR_W)/2,
        .y = ALIPAY_OP1_BAR_Y_POS,
        .width = ALIPAY_OP1_BAR_W,
        .height = ALIPAY_OP1_BAR_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_bar1_bg,
    },

    {
        .id = ALIPAY_SETTING_BAR_TXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = (LCD_SIZE_WIDTH-ALIPAY_OP1_BAR_W)/2,
        .y = ALIPAY_OP1_BAR_Y_POS,
        .width = ALIPAY_OP1_BAR_W,
        .height = ALIPAY_OP1_BAR_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_alipay_setting_unbind_text,
    },

    // bar2
    {
        .id = ALIPAY_SETTING_OK_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = LCD_SIZE_HALF_WIDTH - ALIPAY_OP2_BAR_W - ALIPAY_OP2_BAR_GAP/2,
        .y = ALIPAY_OP2_BAR_Y_POS,
        .width = ALIPAY_OP2_BAR_W,
        .height = ALIPAY_OP2_BAR_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_bar2_ok,
    },
    {
        .id = ALIPAY_SETTING_OK_TXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = LCD_SIZE_HALF_WIDTH - ALIPAY_OP2_BAR_W - ALIPAY_OP2_BAR_GAP/2,
        .y = ALIPAY_OP2_BAR_Y_POS,
        .width = ALIPAY_OP2_BAR_W,
        .height = ALIPAY_OP2_BAR_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_op_ok_text,
    },


    {
        .id = ALIPAY_SETTING_CANCEL_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = LCD_SIZE_HALF_WIDTH + ALIPAY_OP2_BAR_GAP/2,
        .y = ALIPAY_OP2_BAR_Y_POS,
        .width = ALIPAY_OP2_BAR_W,
        .height = ALIPAY_OP2_BAR_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_bar2_cancel,
    },
    {
        .id = ALIPAY_SETTING_CANCEL_TXT_ID,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = LCD_SIZE_HALF_WIDTH + ALIPAY_OP2_BAR_GAP/2,
        .y = ALIPAY_OP2_BAR_Y_POS,
        .width = ALIPAY_OP2_BAR_W,
        .height = ALIPAY_OP2_BAR_H,
        .visible= 0,
        .child_num = 1,
        .children = &gui_alipay_op_cancel_text,
    },
};

const gui_screen_struct gui_screen_alipay_setting =
{
	.children = gui_alipay_widget_setting,
	.child_num = countof(gui_alipay_widget_setting),
};

static void app_window_alipay_setting_exclude_str(char* pStr)
{
    char* pTemp = pStr;

    while(*pStr != 0) {
        if (*pStr == '\n' || *pStr == '\r') {
            pStr ++;
            continue;
        }

        if (pTemp != pStr) {
            *pTemp = *pStr;
        }
        pTemp ++;
        pStr ++;
    }
    *pTemp = 0;
}


///////////////////////////////////////////////////////////////////////////////
static unsigned int g_alipay_setting_flag;      // 0: user-info; 1: unbind-cfm; 2: unbind-result
static void app_window_alipay_setting_update(void)
{
    gui_box_struct* box;

    SYS_DEBUG("app: alipay, setting_flag=%d", g_alipay_setting_flag);
    switch (g_alipay_setting_flag ) {
        case 0:     // 显示用户信息 & 【解绑】
            {
                unsigned int len;
                char* pBuff = os_mem_alloc(RAM_TYPE_DATA_ON, 256);
                if (pBuff != NULL) {
                    box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_USER_ACC_ID);
                    if (box != NULL) {
                        len = 255;
                        srv_alipay_get_logon_name(pBuff, &len);
                        pBuff[len] = 0;

                        SYS_DEBUG("app: alipay, acct_name=%s", pBuff);
                        gui_surface_box_label_change_string(box, pBuff);
                    }
                    box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_USER_NAME_ID);
                    if (box != NULL) {
                        len = 255;
                        srv_alipay_get_nick_name(pBuff, &len);
                        pBuff[len] = 0;
                        app_window_alipay_setting_exclude_str(pBuff);

                        SYS_DEBUG("app: alipay, nick_name=%s", pBuff);
                        gui_surface_control_scrolltext_change_string(box, pBuff);
                    }
                    os_mem_free(pBuff);
                }
            }
            break;

        case 1:     // 显示解绑用户确认界面， 【ok】 | 【cancel】
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_TITLE_ID);
            if (box != NULL) {
                gui_surface_box_label_change_string_id(box, STRING_ALIPAY_UNBIND);
            }
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_USER_ACC_ID);
            if (box != NULL) box->visible = 0;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_USER_NAME_ID);
            if (box != NULL) box->visible = 0;

            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_UNBIND_CFM_ID);
            if (box != NULL) {
                box->visible = 1;
                gui_surface_box_label_change_string_id(box, STRING_ALIPAY_UNBIND_INFO);
            }
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_INFO_TEXT_ID);
            if (box != NULL) box->visible = 0;

            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_BAR_IMG_ID);
            if (box != NULL) box->visible = 0;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_BAR_TXT_ID);
            if (box != NULL) box->visible = 0;

            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_OK_ID);
            if (box != NULL) box->visible = 1;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_OK_TXT_ID);
            if (box != NULL) box->visible = 1;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_CANCEL_ID);
            if (box != NULL) box->visible = 1;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_CANCEL_TXT_ID);
            if (box != NULL) box->visible = 1;
            break;

        case 2: // 显示解绑结果界面， 【OK】
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_TITLE_ID);
            if (box != NULL) box->visible = 0;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_USER_ACC_ID);
            if (box != NULL) box->visible = 0;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_USER_NAME_ID);
            if (box != NULL) box->visible = 0;

            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_UNBIND_CFM_ID);
            if (box != NULL) box->visible = 0;

            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_INFO_TEXT_ID);
            if (box != NULL) {
                box->visible = 1;
                gui_surface_box_label_change_string_id(box, STRING_ALIPAY_UNBIND_OK);
            }

            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_BAR_IMG_ID);
            if (box != NULL) box->visible = 1;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_BAR_TXT_ID);
            if (box != NULL) {
                box->visible = 1;
                gui_surface_box_label_change_string_id(box, STRING_ALIPAY_OK);
            }

            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_OK_ID);
            if (box != NULL) box->visible = 0;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_OK_TXT_ID);
            if (box != NULL) box->visible = 0;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_CANCEL_ID);
            if (box != NULL) box->visible = 0;
            box = gui_surface_get_box(&gui_screen_alipay_setting, ALIPAY_SETTING_CANCEL_TXT_ID);
            if (box != NULL) box->visible = 0;
            break;

        default:
            break;
    }
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_alipay_setting_init(void *buf)
{
    g_alipay_setting_flag = 0;
    SYS_DEBUG("app: alipay_setting_init()");
}

static void app_window_alipay_setting_load(void)
{
    SYS_DEBUG("app: alipay_setting_load()");
    app_window_alipay_setting_update();
}


static void app_window_alipay_setting_entry(void)
{
    SYS_DEBUG("app: alipay_setting_entry()");
}


static void app_window_alipay_setting_exit(void)
{

}

static void app_window_alipay_setting_destroy(void)
{

}



/*-----------------------------响应事件--------------------------------------*/
static void app_window_alipay_setting_click_handler(gui_click_struct *event)
{
    if (event->id == ALIPAY_SETTING_BAR_IMG_ID) {
        if (g_alipay_setting_flag == 0) {
            g_alipay_setting_flag = 1;
            app_window_alipay_setting_update();
        }
        else if (g_alipay_setting_flag == 2) {
            gui_window_history_remove_window(&app_window_alipay_menu);
            application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_alipay_bind, (void*)&app_window_alipay_setting);
            //application_go_back();
            return;
        }
        else {
            return;
        }
    }
    else if (event->id == ALIPAY_SETTING_OK_ID) {
        switch (srv_alipay_clear_bind()) {
            case 0:
            case 1:
                g_alipay_setting_flag = 2;
                app_window_alipay_setting_update();
                break;

            default:
                application_go_back();
                return;
        }
    }
    else if (event->id == ALIPAY_SETTING_CANCEL_ID) {
        application_go_back();
        return;
    }
    else {
        return;
    }
    gui_surface_commit();
}


/*-----------------------------配置--------------------------------------*/
static const gui_touch_event_struct app_window_alipay_setting_touch_events[] =
{
    {.id = ALIPAY_SETTING_BAR_IMG_ID,   .click = app_window_alipay_setting_click_handler},
    {.id = ALIPAY_SETTING_OK_ID,        .click = app_window_alipay_setting_click_handler},
    {.id = ALIPAY_SETTING_CANCEL_ID,    .click = app_window_alipay_setting_click_handler},
};


const gui_window_struct app_window_alipay_setting =
{
	.screen = &gui_screen_alipay_setting,
	.init = app_window_alipay_setting_init,
	.load = app_window_alipay_setting_load,
	.entry = app_window_alipay_setting_entry,
	.exit = app_window_alipay_setting_exit,
	.destroy = app_window_alipay_setting_destroy,

	.touch_event_num = countof(app_window_alipay_setting_touch_events),
	.touch_events = app_window_alipay_setting_touch_events,
};

#endif
