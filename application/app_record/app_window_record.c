
#include "bsp_includes.h"
#include "sys_timer_thread.h"
#include "data_common.h"
#include "key_event_deal.h"
#include "audio_dec_record.h"

#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_drivers_display.h"

#include "app_widget/app_window_widget_delete.h"

#include "app_window_record.h"
#include "app_window_record_layout.h"
#include "app_window_record_filelist.h"

extern u32 record_mic_get_time(void);
extern u32 record_mic_is_encoding(void);
extern u32 record_dec_is_playing(void);


extern void app_recmod_start_req(void);
extern void app_recmod_stop_req(void);
extern void app_recmod_record_req(void);               // recmod, record | pause
extern void app_recmod_play_req(void);                 // recmod, play | pause


#define APP_RECORD_ACT_TOUT 500

static unsigned char  g_record_status;  // 0: idle;  1: recording;  2: playing
static unsigned char  g_record_rentry_flag;

/*-----------------------------系统事件--------------------------------------*/
static void app_window_record_update_ctrl(void)
{
    gui_box_struct* box;

    SYS_DEBUG("app: record_update, stat=%d", g_record_status);
    if (g_record_status == 1) {
        // record
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_REC_START);
        if (box != NULL) box->visible = 0;
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_REC_STOP);
        if (box != NULL) box->visible = 1;

        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_PLAY_START);
        if (box != NULL) box->visible = 0;
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_PLAY_STOP);
        if (box != NULL) box->visible = 0;
    }
    else if (g_record_status == 2) {
        // play
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_REC_START);
        if (box != NULL) box->visible = 0;
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_REC_STOP);
        if (box != NULL) box->visible = 0;

        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_PLAY_START);
        if (box != NULL) box->visible = 0;
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_PLAY_STOP);
        if (box != NULL) box->visible = 1;
    }
    else {
        // idle
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_REC_START);
        if (box != NULL) box->visible = 1;
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_REC_STOP);
        if (box != NULL) box->visible = 0;

        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_PLAY_START);
        if (box != NULL) box->visible = 1;
        box = gui_surface_get_box(&gui_screen_record, RECORD_ID_PLAY_STOP);
        if (box != NULL) box->visible = 0;
    }
}

static void app_window_record_update_time(void)
{
    gui_box_struct* box;
    char time_str[16];
    u32 time = 0;

    box = gui_surface_get_box(&gui_screen_record, RECORD_ID_TIME);
    if (box != NULL) {
        if (g_record_status == 1) {
            time = record_mic_get_time();
        #if defined(FLASH_INSIDE_REC_ENABLE)&&FLASH_INSIDE_REC_ENABLE
			if(time >= 30)
			{
				app_recmod_record_req();
	            g_record_status = 0;
	            app_window_record_update_ctrl();
	            application_close_act_timer(APPLICATION_TIMER_ACT);
			}
        #endif
        }
        else if (g_record_status == 2) {
            u32 temp = record_file_dec_get_cur_time();
            time = record_file_get_total_time();
            if (time > temp) {
                time -= temp;
            }
            else {
                time = 0;
                //g_record_status = 0;
            }
        }
        SYS_DEBUG("app: record_update, time=%d", time);

        sprintf(time_str, "%02d:%02d", time/60, time%60);
        gui_surface_box_label_change_string(box, time_str);
    }
}


//----------------------------------------------------------------
static void app_window_record_init(void *buf)
{
    app_recmod_start_req();
    g_record_rentry_flag = 0;
}

static void app_window_record_load(void *buf)
{
	application_titlebar_create(&gui_screen_record, STRING_RECORD);

    app_window_record_update_ctrl();
    app_window_record_update_time();
}


static void app_window_record_entry(void *buf)
{
    if (!app_rec_running() && (g_record_rentry_flag != 0)) {
        application_send_event(EVENT_GO_HOME, NULL);
    }
    else {
        if (g_record_status != 0) {
            application_open_act_timer(APPLICATION_TIMER_ACT, APP_RECORD_ACT_TOUT);
        }
    }
    g_record_rentry_flag = 1;
}


static void app_window_record_exit()
{
    if (g_record_status == 2) {
        app_recmod_play_req();
    }
    else if (g_record_status == 1) {
        app_recmod_record_req();
    }
    else {
    }
    g_record_status = 0;

    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_record_destroy()
{
    g_record_rentry_flag = 0;
    app_recmod_stop_req();
}


//----------------------------------------------------------------
static void app_window_record_start(gui_click_struct *event)
{
    SYS_DEBUG("app: record_start, %d", g_record_status);
    if (g_record_status == 2)  return;

    app_recmod_record_req();

    if (g_record_status == 1) {
        g_record_status = 0;
        app_window_record_update_ctrl();
        app_window_record_update_time();
        gui_surface_commit();
        application_close_act_timer(APPLICATION_TIMER_ACT);
    }
    else {
        g_record_status = 1;
        app_window_record_update_ctrl();
        app_window_record_update_time();
        gui_surface_commit();
        application_open_act_timer(APPLICATION_TIMER_ACT, APP_RECORD_ACT_TOUT);
    }
}

static void app_window_record_play(gui_click_struct *event)
{
    SYS_DEBUG("app: record_play, %d", g_record_status);
    if (g_record_status == 1) return;

    app_recmod_play_req();
    if (g_record_status == 2) {
        g_record_status = 0;
        app_window_record_update_ctrl();
        app_window_record_update_time();
        gui_surface_commit();
        application_close_act_timer(APPLICATION_TIMER_ACT);
    }
    else {
        g_record_status = 2;
        app_window_record_update_ctrl();
        app_window_record_update_time();
        gui_surface_commit();
        application_open_act_timer(APPLICATION_TIMER_ACT, APP_RECORD_ACT_TOUT);
    }
}

static void app_window_record_onclick_filelist(gui_click_struct *event)
{
    if (app_rec_running()) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_record_filelist, NULL);
    }
}


//----------------------------------------------------------------
static void app_window_record_timer_handler(void* buf)
{
    app_window_record_update_time();
    if (g_record_status == 0) {
        app_window_record_update_ctrl();
        application_close_act_timer(APPLICATION_TIMER_ACT);
    }
    gui_surface_commit();
}

static void app_window_record_audply_end_handler(void* buf)
{
    SYS_DEBUG("app: record_audply, %d", g_record_status);
    if (g_record_status == 2) {
        g_record_status = 0;
        app_window_record_update_ctrl();
        app_window_record_update_time();
        gui_surface_commit();
    }
}

static void app_window_audenc_ind_handler(void* buf)
{
    int evt = *((int*)buf);
    SYS_DEBUG("app: audenc_ind, evt=%d", evt);
    if (evt == AUDREC_START_IND) {
    }
    else if (evt == AUDREC_STOP_IND) {
    }
}
static void app_window_auddec_ind_handler(void* buf)
{
    int evt = *((int*)buf);
    SYS_DEBUG("app: auddec_ind, evt=%d", evt);
    if (evt == AUDPLY_START_IND) {
    }
    else if (evt == AUDPLY_STOP_IND) {
    }
    else if (evt == AUDPLY_TRACK_IND) {
    }
}

static void app_window_appmod_ind_handler(void* buf)
{
    SYS_DEBUG("app: rec, app_window_appmod_ind_handler");
    application_goto_main();
}

/*-----------------------------响应事件--------------------------------------*/

static const gui_touch_event_struct app_window_record_touch_events[] =
{
    {.id = RECORD_ID_REC_START,  .click = app_window_record_start, .offset_right = 30, .offset_top = 30},
    {.id = RECORD_ID_REC_STOP,   .click = app_window_record_start},
    {.id = RECORD_ID_PLAY_START, .click = app_window_record_play, .offset_left = 30, .offset_top = 30},
    {.id = RECORD_ID_PLAY_STOP,  .click = app_window_record_play},
    {.id = RECORD_ID_PIC,        .click = app_window_record_onclick_filelist}
};

static const app_window_event_struct app_window_record_static_events[] =
{
    {.id = EVENT_ACT,            .handler = app_window_record_timer_handler},
    {.id = EVENT_AUDPLY_END,     .handler = app_window_record_audply_end_handler},
    {.id = EVENT_AUDENC_IND,     .handler = app_window_audenc_ind_handler},
    {.id = EVENT_AUDDEC_IND,     .handler = app_window_auddec_ind_handler},
    {.id = EVENT_APPMOD_IND,     .handler = app_window_appmod_ind_handler},
    {.id = EVENT_BL_TIMEOUT},
    //{.id = EVENT_ALL}
};

static const gui_window_config_struct app_window_localmusic_config =
{
	//.forbid_gesture_back = 1,
	//.forbid_key_back = 1,
	//.enable_touch = 1,
};

const gui_window_struct app_window_record =
{
	.screen = &gui_screen_record,

	.init = app_window_record_init,
	.load = app_window_record_load,
	.entry = app_window_record_entry,
	.exit = app_window_record_exit,
	.destroy = app_window_record_destroy,

	.touch_event_num = countof(app_window_record_touch_events),
	.touch_events = app_window_record_touch_events,

	.event_num = countof(app_window_record_static_events),
	.events = app_window_record_static_events,
};

