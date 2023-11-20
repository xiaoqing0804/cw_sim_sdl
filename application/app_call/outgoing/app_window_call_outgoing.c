
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "data_manager_message.h"

#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#include "data_manager_contact.h"
#endif

#include "srv_call.h"

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_control_base.h"

#include "application_config_main_window.h"

#include "app_call/app_window_call.h"
#include "app_window_call_outgoing_layout.h"
#include "app_window_call_outgoing_ui.h"
#include "app_window_call_outgoing.h"

extern void aec_input_clear_enable(u8 enable); //mic 0 静音  1：不静音

static unsigned char m_act_1_flag = 0;
static unsigned char m_call_stop_flag = 0;
static unsigned int  call_time_num = 0;
static unsigned char call_volumn = 0;
static unsigned char call_mic_flag = 0;//麦克风状态
static unsigned char call_phone_flag = 0; //接听状态
static unsigned char call_button_flg = 0;//模式切换保护
static unsigned char call_vol_time = 0;//音量显示时间

static void app_call_state_updata()
{
    gui_box_struct* box;
    //mic
    box = gui_surface_get_box(&app_call_outgoing_screen, CALL_OUTGOING_MIC_ID);
    if(call_mic_flag)
        gui_surface_box_image_change(box,&pic_call_mic_off_info);
    else
        gui_surface_box_image_change(box,&pic_call_mic_on_info);
    gui_surface_commit();
}
/*-------------------------------------------------------------------*/
static int app_window_call_update_volume(void *buf)
{
    gui_box_struct* box;
    short cw ,cy;

    // call_volumn = ext_btaud_status_get()->call_volume;

    call_volumn = app_adjust_call_volume(buf,call_volumn);

    box = gui_surface_get_box(&app_call_outgoing_screen, CALL_LAYOUT_VOLIND_ID);
    if (box != NULL) {
        cw = /*(box->width-pic_call_vol_line_info.width)/2 +*/ (pic_call_vol_line_info.width * call_volumn) / 15;
        gui_surface_box_change_clip(box, 0, 0, cw, box->height);
    }
    return 0;
}

static void app_window_call_outgoing_btaud_info(void *buf)
{
#if defined(__EXT_BT_AUDIO__)
    srv_call_info* call;
    gui_box_struct* box;
    unsigned int call_vol_num = ext_btaud_status_get()->call_volume;

    SYS_DEBUG("call: call_vol_num = %d", call_vol_num);

    call = srv_call_get_info(0);
    box = gui_surface_get_box(&app_call_outgoing_screen, CALL_OUTGOING_TEXT_ID);
    if (box != NULL && call != NULL) {
        SYS_DEBUG("call: name=%s, number=%s", call->name, call->number);
        if (call->name_flag && call->name_len != 0) {
            gui_surface_box_label_change_string(box, call->name);
        }
        else if (call->number_flag && call->number_len != 0) {
            gui_surface_box_label_change_string(box, call->number);
        }
    }
#endif
}


/*-----------------------------系统事件--------------------------------------*/

static void app_window_call_outgoing_init(void *buf)
{
    call_volumn = 15;
    call_phone_flag = bt_mod_get_eco_state();
    call_mic_flag = 0;
}

static void app_window_call_outgoing_load()
{
	call_time_num = srv_time_counter_create(0);
	app_window_call_outgoing_btaud_info(NULL);
    app_window_call_update_volume(0);
    app_call_state_updata();

}

static void app_window_call_outgoing_entry()
{
    m_act_1_flag = 0;
    m_call_stop_flag = 0;

    srv_call_info* call = srv_call_get_info(0);
    if (call == NULL) {
        application_send_event(EVENT_GO_BACK, NULL);
        return;
    }

    send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}

static void app_window_call_outgoing_exit(void *buf)
{
    m_act_1_flag = 0;
    m_call_stop_flag = 0;
    application_close_act_timer(APPLICATION_TIMER_ACT);

}

static void app_window_call_outgoing_destroy(void *buf)
{
	if (call_time_num != 0) {
        srv_time_counter_destory(call_time_num);
        call_time_num = 0;
    }
}

static void app_window_call_outgoing_handler(void* buf)
{
 	if(ext_btaud_status_get()->call_status == 0 )
	{
		application_go_back();
	}
	else if(ext_btaud_status_get()->call_status == 3 )
	{
		srv_time_counter_start(call_time_num);
	}
}

static void app_window_call_time_event_act()
{
	char temp[40];
	unsigned int value =srv_call_get_time(0);//srv_time_counter_get_value(call_time_num);

	SYS_DEBUG("gui: countdown_load, %d", value);
	snprintf(temp, sizeof(temp), "%02d:%02d:%02d",(value/60)/60,(value/60)%60, value%60);
	gui_box_struct*  box = gui_surface_get_box(&app_call_outgoing_screen, (unsigned short) CALL_OUTGOING_TIME_ID);
	gui_surface_box_label_change_string(box,(unsigned char *)temp);
	gui_surface_commit();

}


static void app_window_call_time_handler(void *buf)
{
	srv_time_counter_start(call_time_num);
}

static void app_window_call_outgoing_timer_handler(void *buf)
{
    unsigned int timer_index = *((unsigned int *)buf);
    GUI_DEBUG("in call_act ");

	app_window_call_time_event_act();

	if(call_button_flg>0) //切换模式保护标志位
    {
        call_button_flg--;
    }
	if(call_vol_time>0){
        call_vol_time --;
	}else{
        app_call_volind_box_visible(0);
	}



    GUI_DEBUG("call_act done");
}

static void app_window_call_outgoing_key_handler(void *buf)
{
    GUI_DEBUG("call hangup\r\n");
#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_CALL_HANG_UP, NULL, 0);
    ext_btaud_send_cmd(AU_CMD_CANCEL_DIAL, NULL, 0);
#endif
    application_go_back();
}

static void app_window_call_outgoing_hungup_click_handler(gui_click_struct* click)
{
    if(0 == m_call_stop_flag)
    {
        GUI_DEBUG("call hangup\r\n");
        m_call_stop_flag = 1;
    #if defined(__EXT_BT_AUDIO__)
        ext_btaud_send_cmd(AU_CMD_CALL_HANG_UP, NULL, 0);
        ext_btaud_send_cmd(AU_CMD_CANCEL_DIAL, NULL, 0);
    #endif
    }
		application_go_back();
}

static void app_window_call_outgoing_cmd_event_handler(void* buf)
{
	SYS_DEBUG("cw 8888 = %d",get_call_flag());
#if defined(__EXT_BT_AUDIO__)
	if(0 == ext_btaud_status_get()->call_status) {
    	application_go_back();
	}
#endif
}

static void app_window_call_vold_volup_click_handler(gui_click_struct* click)
{
#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_VOLUME_UP, NULL, 0);
    app_window_call_update_volume(2);
    gui_surface_commit();
#endif
}

static void app_window_call_vold_voldn_click_handler(gui_click_struct* click)
{
#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_VOLUME_DOWN, NULL, 0);
    app_window_call_update_volume(3);
    gui_surface_commit();
#endif
}
static void app_window_call_event_updata_handler(void* buf)
{
    call_phone_flag = bt_mod_get_eco_state();
    call_mic_flag = 0;
    app_call_state_updata();
}

static void app_window_call_mic_handler(gui_click_struct* click)
{
    if(call_button_flg>0)
        return;

    call_button_flg = 3;

    if(call_mic_flag){
        aec_input_clear_enable(0);
        call_mic_flag=0;
    }
    else{
        aec_input_clear_enable(1);
        call_mic_flag=1;
    }
    app_call_state_updata();

	gui_surface_commit();
}

static void app_window_call_phone_handler(gui_click_struct* click)
{
    if(call_button_flg>0)
        return;

    call_button_flg = 4;

    if(call_phone_flag)
        call_phone_flag = 0;
    else
        call_phone_flag = 1;

    call_mic_flag = 0;
    bt_mod_eco_open_and_close();
    app_call_state_updata();
	gui_surface_commit();
}
static void app_window_call_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;

	app_call_volind_box_visible(1);
	call_vol_time = 3;
	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
        #if defined(__EXT_BT_AUDIO__)
            ext_btaud_send_cmd(AU_CMD_VOLUME_UP, NULL, 0);
            app_window_call_update_volume(2);
        #endif

	}else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
        #if defined(__EXT_BT_AUDIO__)
        ext_btaud_send_cmd(AU_CMD_VOLUME_DOWN, NULL, 0);
        app_window_call_update_volume(3);
        #endif
	}

	gui_surface_commit();

}



/*-----------------------------配置--------------------------------------*/
static const gui_touch_event_struct app_window_call_outgoing_touch_events[] =
{
    {
        .id = CALL_OUTGOING_HUNGUP_ID,
        .click = app_window_call_outgoing_hungup_click_handler,
        .offset_top = 10,
    },
    {
        .id = CALL_OUTGOING_MIC_ID,
        .click = app_window_call_mic_handler,
         .offset_top = 10,
    },

    {
        .id = CALL_OUTGOING_PHONE_ID,
        .click = app_window_call_phone_handler,
         .offset_top = 10,
    },




};

static void app_window_call_outgoing_number_handler(void* buf)
{
	gui_box_struct* box = gui_surface_get_box(&app_call_outgoing_screen, CALL_OUTGOING_TEXT_ID);
    if (box != NULL) {
        gui_surface_box_label_change_string(box, (unsigned char*)AU_call_num);
    }
	gui_surface_commit();
}



static const app_window_event_struct app_window_call_outgoing_events[] =
{
    {.id = EVENT_BTAUD_STATUS,   .handler = app_window_call_outgoing_handler },
    {.id = EVENT_BTAUD_CALL,     .handler = app_window_call_outgoing_btaud_info },
    {.id = EVENT_BTAUD_CALL_ACTIVE,   .handler = app_window_call_time_handler },
    {.id = EVENT_ACT,            .handler = app_window_call_outgoing_timer_handler },
    {.id = EVENT_KEY1_SHORT,     .handler = app_window_call_outgoing_key_handler },
    {.id = EVENT_CALL_CMD,       .handler = app_window_call_outgoing_cmd_event_handler },
    {.id = EVENT_COUNTER_REPORT, .handler = app_window_call_outgoing_timer_handler},
    {.id = EVENT_ROLKEY,           .handler = app_window_call_rolkey_handler},
    {.id =EVENT_BT_STATUS_SCO_STATUS_CHANGE, .handler =app_window_call_event_updata_handler },



    {.id = EVENT_BL_TIMEOUT,     .handler = NULL },
    {.id = EVENT_MESSAGE,        .handler = NULL },
    {.id = EVENT_ALARM,        .handler = NULL },
    {.id = EVENT_FIND_DEVICE,        .handler = NULL },
    {.id = EVENT_DRINK_ALARM,        .handler = NULL },
    {.id = EVENT_SEDENTARY_REMINDER,        .handler = NULL },
};

static const gui_window_config_struct app_window_call_outgoing_config =
{
	.forbid_gesture_back = 1,
};

const gui_window_struct app_window_call_outgoing =
{
	.screen = &app_call_outgoing_screen,
	.config = &app_window_call_outgoing_config,
	.init = app_window_call_outgoing_init,
	.load = app_window_call_outgoing_load,
	.entry = app_window_call_outgoing_entry,
	.exit = app_window_call_outgoing_exit,
	.destroy = app_window_call_outgoing_destroy,

    .touch_event_num = countof(app_window_call_outgoing_touch_events),
    .touch_events = app_window_call_outgoing_touch_events,

	.event_num = countof(app_window_call_outgoing_events),
	.events = app_window_call_outgoing_events,
};


