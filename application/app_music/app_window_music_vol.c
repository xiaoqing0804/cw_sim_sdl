#include "ams.h"
#include "picture.h"
#include "language.h"

#include "gui_surface_control_base.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "arithmetic_sleep.h"
#include "data_common.h"


#include "system_util_math_geometry.h"
#include "gui_surface_control_animation.h"

#include "gui_window.h"
#include "gui_surface_box.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_box_canvas.h"
#include "application_titlebar.h"
#include "app_window_music.h"
#include "app_window_music_vol.h"
#include "app_window_music_layout.h"

#include "app_widget/app_window_widget_delete.h"

static unsigned char music_volumn = 0;

// vol
// static const gui_image_struct gui_music_volup_image =
// {
//     .type = TYPE_GUI_DRAW_PICTURE,
//     .data = &pic_music_volh_info,
// };

// static const gui_image_struct gui_music_voldn_image =
// {
//     .type = TYPE_GUI_DRAW_PICTURE,
//     .data = &pic_music_voll_info,
// };


// vol-bg
static const gui_image_struct gui_music_vol_bg_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_music_log_bg_info,
};

static const gui_image_struct gui_music_vol_ind_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_music_log_top_info,
};



static const gui_widget_struct gui_music_widget[] =
{

    // {   // vol - up
    //     .id = MUSIC_LAYOUT_VOLUP_ID,
    //     .type = TYPE_GUI_CONTROL_IMAGE,
    //     .x = 193,
    //     .y = 16,
    //     .width = 80,
    //     .height = 80,
    //     .visible= 1,
    //     .child_num = 1,
    //     .children = &gui_music_volup_image,
    // },

    // {   // vol - dn
    //     .id = MUSIC_LAYOUT_VOLDN_ID,
    //     .type = TYPE_GUI_CONTROL_IMAGE,
    //     .x = 193,
    //     .y = 370,
    //     .width = 80,
    //     .height = 80,
    //     .visible= 1,
    //     .child_num = 1,
    //     .children = &gui_music_voldn_image,
    // },

    // {   // vol - bg
    //     .id = MUSIC_LAYOUT_VOLBG_ID,
    //     .type = TYPE_GUI_CONTROL_IMAGE,
    //     .x = 227,
    //     .y = 113,
    //     .width = 12,
    //     .height = 240,
    //     .visible= 1,
    //     .child_num = 1,
    //     .children = &gui_music_vol_bg_image,
    // },

    // {   // vol - ind
    //     .id = MUSIC_LAYOUT_VOLIND_ID,
    //     .type = TYPE_GUI_CONTROL_IMAGE,
    //     .x = 227,    // 16+52,
    //     .y = 113,   // 326+22,
    //     .width = 12,
    //     .height = 240,
    //     .visible= 1,
    //     .child_num = 1,
    //     .children = &gui_music_vol_ind_image,
    // },





};

const gui_screen_struct gui_screen_music_vol =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.order = 0,
	.children = gui_music_widget,
	.child_num = countof(gui_music_widget),
};

static void app_window_music_set_volume(unsigned int inc_vol)
{
    MUSIC_CMD_TYPE cmd = ((inc_vol) ? MUSIC_CMD_VOLUME_UP : MUSIC_CMD_VOLUME_DOWN);

   if (get_ble_connect_flag() == 0)
        return;
    Phone_music_control_handler(cmd);
}

static int app_window_music_update_volume(void)
{
    gui_box_struct* box;
    short cw ,cy;

    box = gui_surface_get_box(&gui_screen_music_vol, MUSIC_LAYOUT_VOLIND_ID);
    if (box != NULL) {
        cw = (box->height * music_volumn) / 100;
        cy = box->height - cw;
        SYS_DEBUG("music_volumn=%d cw=%d",music_volumn,cw);
        gui_surface_box_change_clip(box, 0, cy, box->width, cw);
    }
    return 0;
}


static void app_window_music_vol_init(void *buf)
{
    music_volumn =	100;

}

static void app_window_music_vol_load(void *buf)
{
    const remote_music_struct* music_info = remote_music_info_get();
    music_volumn =	music_info->volume;

     app_window_music_update_volume();
}

static void app_window_music_ams_vol_ind(void *buf)
{
    // ...
    remote_music_struct const * music_info = remote_music_info_get();
    SYS_DEBUG("update: remote music status, music_volumn = %d, volume = %d", music_volumn, music_info->volume);

    if(music_volumn != music_info->volume) {
        music_volumn = music_info->volume;
        app_window_music_update_volume();
        gui_surface_commit();
    }
}

static void app_window_music_vol_track_ind(void *buf)
{
    // ....
    const remote_music_struct* rmt_music_info = remote_music_info_get();
    if (music_volumn != rmt_music_info->volume) {
        music_volumn = rmt_music_info->volume;
        app_window_music_update_volume();
    }

    gui_surface_commit();
}

static void app_window_music_vol_entry(void *buf)
{

}

static void app_window_music_vol_exit()
{

}

static void app_window_music_vol_destroy()
{

}

static void app_window_music_volup_event_touch(gui_click_struct *click)
{
    app_window_music_set_volume(1);
    app_window_music_update_volume();
}

static void app_window_music_voldn_event_touch(gui_click_struct *click)
{
    app_window_music_set_volume(0);
    app_window_music_update_volume();
}

static const gui_touch_event_struct app_window_music_vol_touch_events[] =
{
    {.id = MUSIC_LAYOUT_VOLUP_ID, .click = app_window_music_volup_event_touch,	.offset_right = 40, },
    {.id = MUSIC_LAYOUT_VOLDN_ID, .click = app_window_music_voldn_event_touch,	.offset_left = 40, },

};

static const app_window_event_struct app_window_music_vol_events[] =
{
    {EVENT_AMS_VOLUME_IND,  app_window_music_ams_vol_ind},
    {EVENT_AMS_CMD_IND,     app_window_music_vol_track_ind},
};


const gui_window_struct app_window_music_vol =
{
	.screen = &gui_screen_music_vol,

	.init = app_window_music_vol_init,
	.load = app_window_music_vol_load,
	.entry = app_window_music_vol_entry,
	.exit = app_window_music_vol_exit,
	.destroy = app_window_music_vol_destroy,

	.touch_event_num = countof(app_window_music_vol_touch_events),
	.touch_events = app_window_music_vol_touch_events,

    .event_num = countof(app_window_music_vol_events),
    .events = app_window_music_vol_events,
};
