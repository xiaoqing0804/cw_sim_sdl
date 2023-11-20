
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"
#include "key_event_deal.h"
#include "os_mem.h"

#include "system_util_string.h"
#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_localmusic.h"
#include "app_window_localmusic_layout.h"
#include "app_window_localmusic_filelist.h"


extern const char* music_file_get_cur_name(int *len, int *is_unicode);
extern int  music_is_playing(void);

extern void app_music_start_req(void);            // start music mode
extern void app_music_stop_req(void);             // stop music mode
extern void app_music_player_start(void);
extern void app_music_player_stop(void);
extern void app_music_player_prev(void);
extern void app_music_player_next(void);
extern void app_volume_up(void);
extern void app_volume_down(void);
extern bool app_music_running(void);

static const geometry_rect c_prev_rect = {LOCALMUSIC_PREV_X, LOCALMUSIC_PREV_Y, 57, 57};
static const geometry_rect c_next_rect = {LOCALMUSIC_NEXT_X, LOCALMUSIC_NEXT_Y, 57, 57};

static unsigned char localmusic_volumn = 0;
static unsigned char g_localmusic_rentry_flag;

/*-----------------------------ϵͳ�¼�--------------------------------------*/
static int app_window_localmusic_update_volume(void)
{
    gui_box_struct* box;

    SYS_DEBUG("music: update, vol = %d", localmusic_volumn);
    box = gui_surface_get_box(&gui_screen_localmusic, LOCALMUSIC_LAYOUT_ID_YL);
    if (box != NULL) gui_surface_box_change_clip(box,0, 0, localmusic_volumn, box->height);
    return 0;
}

// static int app_window_localmusic_update_status(void)
// {
//     gui_box_struct* box;
//     {
//         box = gui_surface_get_box(&gui_screen_localmusic, LOCALMUSIC_LAYOUT_ID_PLAY);
//         if (box != NULL) {
//             gui_surface_box_image_change(box, &pic_music_pp_info);
//         }
//     }
//     return 1;
// }

static int app_window_localmusic_update_name(void)
{
    gui_box_struct* box;

    box = gui_surface_get_box(&gui_screen_localmusic, LOCALMUSIC_LAYOUT_ID_NAME);
    if (box != NULL) {
        int   len = 0;
        int   is_ucs = 0;
        char* name = music_file_get_cur_name(&len, &is_ucs);
        SYS_DEBUG("music: name, len=%d, is_ucs=%d", len, is_ucs);
        if (is_ucs) {
            unsigned char* temp_name = (unsigned char*)os_mem_alloc(RAM_TYPE_DATA_ON, 256);
            if (temp_name != NULL) {
                SYS_DEBUG("music: ..........");
                len = Unicode2UTF8(temp_name, (u16*)name, len);
                SYS_DEBUG("music: %d, name=%s", len, temp_name);
                gui_surface_control_scrolltext_change_string(box, temp_name);
                os_mem_free(temp_name);
            }
        }
        else {
            gui_surface_control_scrolltext_change_string(box, (unsigned char*)name);
        }
    }
    return 1;
}

static void app_window_localmusic_set_volume(unsigned int inc_vol)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_localmusic_init(void *buf)
{
    app_music_start_req();
    g_localmusic_rentry_flag = 0;
}

static void app_window_localmusic_load(void *buf)
{
    localmusic_volumn =	10;

    SYS_DEBUG("music: load, vol = %d", localmusic_volumn);
    app_window_localmusic_update_status();
    app_window_localmusic_update_name();
    app_window_localmusic_update_volume();
    gui_surface_control_animation_start(&gui_screen_localmusic, LOCALMUSIC_LAYOUT_ID_ANI);
    application_titlebar_create(&gui_screen_localmusic, STRING_MUSIC);
}


static void app_window_localmusic_entry(void *buf)
{
    if (!app_music_running() && (g_localmusic_rentry_flag != 0)) {
        application_send_event(EVENT_GO_HOME, NULL);
    }
    g_localmusic_rentry_flag = 1;
}


static void app_window_localmusic_exit()
{
}

static void app_window_localmusic_destroy()
{
    if (0 == music_is_playing()) {
        app_music_stop_req();
    }
    g_localmusic_rentry_flag = 0;
}


/*-----------------------------����--------------------------------------*/
static void app_window_localmusic_navi_event_touch(gui_click_struct *click)
{
    if (check_rect_contain_point_xy((geometry_rect*)&c_prev_rect, click->x, click->y)) {
        app_music_player_prev();
    }
    else if (check_rect_contain_point_xy((geometry_rect*)&c_next_rect, click->x, click->y)) {
        app_music_player_next();
    }
}

static void app_window_localmusic_play_event_touch(gui_click_struct *click)
{
    if (music_is_playing()) {
        app_music_player_stop();
    }
    else {
        app_music_player_start();
    }
}

static void app_window_localmusic_volup_event_touch(gui_click_struct *click)
{
    app_volume_up();
}

static void app_window_localmusic_voldn_event_touch(gui_click_struct *click)
{
    app_volume_down();
}

static void app_window_localmusic_filelist_event_touch(gui_click_struct *click)
{
    if (app_music_running()) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_localmusic_filelist, NULL);
    }
}

static void app_window_localmusic_long_touch_handler(gui_click_struct *event)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_localmusic_suspend(void *buf)
{
}

static void app_window_localmusic_resume(void *buf)
{
}

static void app_window_localmusic_audply_end_handler(void *buf)
{
    SYS_DEBUG("app: music, audply_end");
    application_go_back();
}

static void app_window_localmusic_audio_decode_handler(void *buf)
{
    int evt = *((int*)buf);
    SYS_DEBUG("app: music, auddec_ind, evt=%d", evt);
    if (evt == AUDPLY_START_IND) {
    }
    else if (evt == AUDPLY_STOP_IND) {
    }
    else if (evt == AUDPLY_TRACK_IND) {
        app_window_localmusic_update_name();
        gui_surface_commit();
    }
}

static void app_window_appmod_ind_handler(void* buf)
{
    SYS_DEBUG("app: music, app_window_appmod_ind_handler");
    application_goto_main();
}


static const gui_touch_event_struct app_window_localmusic_touch_events[] =
{
    {.id = LOCALMUSIC_LAYOUT_ID_PLAY,  .click = app_window_localmusic_play_event_touch },
    {.id = LOCALMUSIC_LAYOUT_VOLUP_ID, .click = app_window_localmusic_volup_event_touch,	.offset_right = 40, },
    {.id = LOCALMUSIC_LAYOUT_VOLDN_ID, .click = app_window_localmusic_voldn_event_touch,	.offset_left = 40, },
    {.id = LOCALMUSIC_LAYOUT_ID_NAME,  .click = app_window_localmusic_filelist_event_touch},
    {.id = LOCALMUSIC_LAYOUT_ID_BG,	  .click = app_window_localmusic_navi_event_touch },
    {.id = 0xFFFF,/*fullscreen*/  .long_touch = app_window_localmusic_long_touch_handler },
};


static const app_window_event_struct app_window_localmusic_events[] =
{
    {.id = EVENT_GUI_SUSPENDED, app_window_localmusic_suspend},
    {.id = EVENT_GUI_RESUMED,   app_window_localmusic_resume},
    {.id = EVENT_AUDPLY_END,    app_window_localmusic_audply_end_handler},
    {.id = EVENT_AUDDEC_IND,    app_window_localmusic_audio_decode_handler},
    {.id = EVENT_APPMOD_IND,    app_window_appmod_ind_handler},
    //{.id = EVENT_BL_TIMEOUT},
    //{.id = EVENT_ALL},
};

static const gui_window_config_struct app_window_localmusic_config =
{
	//.forbid_gesture_back = 1,
	//.forbid_key_back = 1,
	//.enable_touch = 1,
};

const gui_window_struct app_window_localmusic =
{
	.screen = &gui_screen_localmusic,
    .config = &app_window_localmusic_config,

	.init = app_window_localmusic_init,
	.load = app_window_localmusic_load,
	.entry = app_window_localmusic_entry,
	.exit = app_window_localmusic_exit,
	.destroy = app_window_localmusic_destroy,

	.touch_event_num = countof(app_window_localmusic_touch_events),
	.touch_events = app_window_localmusic_touch_events,

    .event_num = countof(app_window_localmusic_events),
    .events = app_window_localmusic_events,
};



