#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "arithmetic_sleep.h"
#include "data_common.h"

#include "system_util_math_geometry.h"

#include "gui_window.h"
#include "gui_surface_box.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "gui_surface_control_base.h"
#include "gui_surface_control_animation.h"
#include "application_titlebar.h"

#include "app_window_music.h"
#include "app_window_music_vol.h"
#include "app_window_music_layout.h"
#include "ams.h"

#include "app_widget/app_window_widget_delete.h"

// static unsigned char music_disp_volume_panel = 0;
static unsigned char music_volumn = 0;

/*-----------------------------ϵͳ�¼�--------------------------------------*/
// static int app_window_music_update_volume(void)
//{
//     gui_box_struct* box;
//
//     SYS_DEBUG("music: update, vol = %d", music_volumn);
//     box = gui_surface_get_box(&gui_screen_music, MUSIC_LAYOUT_ID_YL);
//     if (box != NULL) gui_surface_box_change_clip(box,0, 0, music_volumn, box->height);
//     return 0;
// }

// static int app_window_music_update_status(void)
// {
//     gui_box_struct *box;
//     {
//         box = gui_surface_get_box(&gui_screen_music, MUSIC_LAYOUT_ID_PLAY);
//         if (box != NULL)
//         {
//             gui_surface_box_image_change(box, &pic_music_pp_info);
//         }
//     }
//     return 1;
// }

static int app_window_music_update_name(void)
{
    remote_music_struct const *music_info = remote_music_info_get();
    gui_box_struct *box;

    SYS_DEBUG("test_music_name =%s", music_info->name);
    box = gui_surface_get_box(&gui_screen_music, MUSIC_LAYOUT_ID_MUSIC_NAME);
    if (box != NULL)
    {
        gui_surface_control_scrolltext_change_string(box, (unsigned char *)music_info->name);
    }
    return 1;
}

static void app_window_music_update_volume(void)
{
    gui_box_struct* box;
    short cw;

    box = gui_surface_get_box(&gui_screen_music, MUSIC_LAYOUT_ID_LOG_ICON);
    if (box != NULL) {
        cw = (pic_music_log_top_info.width * music_volumn) / 100;
        SYS_DEBUG("music_volumn=%d cw=%d",music_volumn,cw);
        gui_surface_box_change_clip(box, 0, 0, cw,box->height);
    }
}

// static int app_window_music_update_bt_status(void)
//{
//     gui_box_struct* box;
//
//     /* display ble connect. */
//     box = gui_surface_get_box(&gui_screen_music, MUSIC_LAYOUT_ID_BTSTA);
//     if (box != NULL) {
//         if (get_ble_connect_flag() > 0) {
//             box->visible = 0;
//         }
//         else {
//             gui_surface_box_image_change(box, &pic_main_ble_disconnect_info);
//             box->y = 5;
//         }
//
//     }
//     return 1;
// }

static void app_window_music_send_rmtaud_command(MUSIC_CMD_TYPE cmd)
{
    if (get_ble_connect_flag() == 0)
        return;

    Phone_music_control_handler(cmd);
}

static void app_window_music_set_volume(unsigned int inc_vol)
{
    MUSIC_CMD_TYPE cmd = ((inc_vol) ? MUSIC_CMD_VOLUME_UP : MUSIC_CMD_VOLUME_DOWN);

    if (get_ble_connect_flag() == 0)
        return;
    Phone_music_control_handler(cmd);

    SYS_DEBUG("BT_MUSIC_TOUCH = %d", ext_btaud_status_get()->dev_status);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_music_init(void *buf)
{
#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_STATUS, NULL, 0);
#endif
}

static void app_window_music_load(void *buf)
{
    const remote_music_struct *music_info = remote_music_info_get();
    music_volumn = music_info->volume;

    SYS_DEBUG("music: load, vol = %d", music_volumn);
    // app_window_music_update_status();
    app_window_music_update_name();
    app_window_music_update_volume();

    // am_pm = sys_time_get_12h(&time,&sec);
    // if(am_pm){
    // 	box = gui_surface_get_box(&gui_screen_music,MUSIC_LAYOUT_ID_PLAY);
    // 	gui_surface_box_image_change(box,&pic_music_stop_info);
    // 	box = gui_surface_get_box(&gui_screen_music,MUSIC_LAYOUT_ID_ICON);
    // 	gui_surface_box_image_change(box,&pic_music_start0_info);
    // }
    // else
    // {
    //     box = gui_surface_get_box(&gui_screen_music,MUSIC_LAYOUT_ID_ICON);
    // 	gui_surface_box_image_change(box,&pic_music_start0_info);
    // 	box = gui_surface_get_box(&gui_screen_music,MUSIC_LAYOUT_ID_PLAY);
    // 	gui_surface_box_image_change(box,&pic_music_stop_info);
    // }

    //    app_window_music_update_volume();
    //    app_window_music_update_bt_status();
    //    gui_surface_control_animation_start(&gui_screen_music, MUSIC_LAYOUT_ID_ANI);
    //    application_titlebar_create(&gui_screen_music, STRING_MUSIC);
}

static void app_window_music_entry(void *buf)
{
    // application_open_act_timer(APPLICATION_TIMER_ACT, 500);
    app_window_music_update_volume();
}

static void app_window_music_exit()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_music_destroy()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

/*-----------------------------����--------------------------------------*/
/*
static const geometry_rect c_prev_rect = {MUSIC_PREV_X, MUSIC_PREV_Y, 57, 57};
static const geometry_rect c_next_rect = {MUSIC_NEXT_X, MUSIC_NEXT_Y, 57, 57};
static void app_window_music_navi_event_touch(gui_click_struct *click)
{
    MUSIC_CMD_TYPE cmd = MUSIC_CMD_NULL;

#if defined(__EXT_BT_AUDIO__)
    if ((0 == get_ble_connect_flag()) && (0 == ext_btaud_status_get()->dev_status)) return;
#else
    if (0 == get_ble_connect_flag()) return;
#endif

    if (check_rect_contain_point_xy((geometry_rect*)&c_prev_rect, click->x, click->y)) {
        cmd = MUSIC_CMD_BACKWARD;
        app_window_music_send_rmtaud_command(cmd);
    }
    else if (check_rect_contain_point_xy((geometry_rect*)&c_next_rect, click->x, click->y)) {
        cmd = MUSIC_CMD_FORWARD;
        app_window_music_send_rmtaud_command(cmd);
    }
    else {
        return;
    }

    send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
}
*/
static void app_window_music_next_event_touch(gui_click_struct *click)
{
    MUSIC_CMD_TYPE cmd = MUSIC_CMD_NULL;

    cmd = MUSIC_CMD_BACKWARD;
    app_window_music_send_rmtaud_command(cmd);
    if (get_ble_connect_flag() > 0)
    {
        send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
    }
}

static void app_window_music_vol_event_touch(gui_click_struct *click)
{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_music_vol, NULL);
}

static void app_window_music_previous_song_event_touch(gui_click_struct *click)
{
    MUSIC_CMD_TYPE cmd = MUSIC_CMD_NULL;

    cmd = MUSIC_CMD_FORWARD;
    app_window_music_send_rmtaud_command(cmd);

    if (get_ble_connect_flag() > 0)
    {
        send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
    }
}

static void app_window_music_play_event_touch(gui_click_struct *click)
{
    SYS_DEBUG("app_window_music_play_event_touch");
#if defined(__EXT_BT_AUDIO__)
    if ((0 == get_ble_connect_flag()) && (0 == ext_btaud_status_get()->dev_status))
        return;
#else
    if (0 == get_ble_connect_flag())
        return;
#endif
    send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
    app_window_music_send_rmtaud_command(MUSIC_CMD_PP);
}

static void app_window_music_volup_event_touch(gui_click_struct *click)
{
    app_window_music_set_volume(1);
    app_window_music_update_volume();
    if (get_ble_connect_flag() > 0)
    {
        send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
    }
    gui_surface_commit();
}

static void app_window_music_voldn_event_touch(gui_click_struct *click)
{
    app_window_music_set_volume(0);
    app_window_music_update_volume();
    if (get_ble_connect_flag() > 0)
    {
        send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
    }
    gui_surface_commit();
}

static void app_window_music_vol_event(gui_click_struct *click)
{
    if(click->x < LCD_SIZE_HALF_WIDTH)
    {
        app_window_music_voldn_event_touch(click);
    }
    else
    {
        app_window_music_volup_event_touch(click);
    }
}

// static void app_window_music_long_touch_handler(gui_click_struct *event)
//{
//     SYS_DEBUG("window_music_touch longpress");
//     if (is_exist_widget_app(APP_INFO_ID_MUSIC)) {
//         application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void*)APP_INFO_ID_MUSIC);
//     }
// }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void app_window_music_suspend(void *buf)
{
}

static void app_window_music_swipe(void *buf)
{
    app_window_music_update_volume();
    gui_surface_commit();
}

static void app_window_music_resume(void *buf)
{
}

static void app_window_music_timer_handler(void *buf)
{
    app_window_music_update_name();
    gui_surface_commit();
}

// static void app_window_ble_status(void *buf)
//{
//     if (app_window_music_update_bt_status()) {
//         gui_surface_commit();
//     }
// }

static void app_window_music_btaud_status(void *buf)
{
}

static void app_window_music_ams_name_ind(void *buf)
{
    remote_music_struct const *music_info = remote_music_info_get();
    SYS_DEBUG("update: remote music status, music_volumn = %d, volume = %d", music_volumn, music_info->volume);

    app_window_music_update_name();
    gui_surface_commit();
}

static void app_window_music_ams_vol_ind(void *buf)
{
    // ...
    remote_music_struct const *music_info = remote_music_info_get();
    SYS_DEBUG("update: remote music status, music_volumn = %d, volume = %d", music_volumn, music_info->volume);

    if (music_volumn != music_info->volume)
    {
        music_volumn = music_info->volume;
    }
        app_window_music_update_volume();
        gui_surface_commit();
}

static void app_window_music_track_ind(void *buf)
{
    // ....
    const remote_music_struct *rmt_music_info = remote_music_info_get();
    if (music_volumn != rmt_music_info->volume)
    {
        music_volumn = rmt_music_info->volume;
    }
    app_window_music_update_name();
      app_window_music_update_volume();
    // app_window_music_update_status();
    gui_surface_commit();
}

static void app_window_music_long_touch_handler(gui_click_struct *event)
{
    if (is_exist_widget_app(APP_INFO_ID_MUSIC))
    {
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_MUSIC);
    }
}

static const gui_touch_event_struct app_window_music_touch_events[] =
    {

        {
            .id = MUSIC_LAYOUT_ID_PLAY,
            .click = app_window_music_play_event_touch,
        },
        {
            .id = MUSIC_LAYOUT_ID_LOG_ICON,
            .click = app_window_music_vol_event,
            .offset_right = 40,
            .offset_left = 40,
            .offset_top = 40,
            .offset_bottom = 40,
        },
        //{.id = MUSIC_LAYOUT_VOLDN_ID, .click = app_window_music_voldn_event_touch,	.offset_left = 40, },

        {
            .id = MUSIC_LAYOUT_ID_PREVIOUS_SONG,
            .click = app_window_music_previous_song_event_touch,
        },
        {
            .id = MUSIC_LAYOUT_ID_NEXT,
            .click = app_window_music_next_event_touch,
        },
        {
            .id = MUSIC_LAYOUT_ID_ICON,
            .click = app_window_music_vol_event_touch,
        },
        {
            .id = 0xFFFF,
            .long_touch = app_window_music_long_touch_handler,
        },

};

static const app_window_event_struct app_window_music_events[] =
    {

        {
            EVENT_GUI_SUSPENDED,
            app_window_music_suspend,
        },
        {
            EVENT_GUI_RESUMED,
            app_window_music_resume,
        },
        {
            EVENT_BTAUD_STATUS,
            app_window_music_btaud_status,
        },
        {
            EVENT_AMS_NAME_IND,
            app_window_music_ams_name_ind,
        },
        {
            EVENT_AMS_VOLUME_IND,
            app_window_music_ams_vol_ind,
        },
        {
            EVENT_AMS_CMD_IND,
            app_window_music_track_ind,
        },
        {
            EVENT_SWIPE_CANCEL,
            app_window_music_swipe,
        },
};

const gui_window_struct app_window_music =
    {
        .screen = &gui_screen_music,

        .init = app_window_music_init,
        .load = app_window_music_load,
        .entry = app_window_music_entry,
        .exit = app_window_music_exit,
        .destroy = app_window_music_destroy,

        .touch_event_num = countof(app_window_music_touch_events),
        .touch_events = app_window_music_touch_events,

        .event_num = countof(app_window_music_events),
        .events = app_window_music_events,
};
