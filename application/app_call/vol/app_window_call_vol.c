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

#include "app_window_call_vol_layout.h"
#include "app_window_call_vol.h"

uint32_t outgoning_time = 0;
extern unsigned char call_volumn;


static int app_window_call_update_volume(void *buf)
{
    gui_box_struct* box;
    short cw ,cy;

    // call_volumn = ext_btaud_status_get()->call_volume;

    call_volumn = app_adjust_call_volume(buf,call_volumn);

    box = gui_surface_get_box(&gui_screen_call_vol, CALL_LAYOUT_VOLIND_ID);
    if (box != NULL) {
        cw = (box->width * call_volumn) / 15;
        gui_surface_box_change_clip(box, 0, 0, cw, box->height);
    }
    return 0;
}


static void app_window_call_vol_init(void *buf)
{
        call_volumn = 15;
}

static void app_window_call_vol_load(void *buf)
{;
     app_window_call_update_volume(1);
}

static void app_window_call_vol_entry(void *buf)
{

}

static void app_window_call_vol_exit()
{

}

static void app_window_call_vol_destroy()
{

}

static void app_window_call_vol_handler(void* buf)
{
 	if(ext_btaud_status_get()->call_status == 0 )
	{
		application_goto_main();
	}

}

static void app_window_call_outgoing_volup_click_handler(gui_click_struct* click)
{
#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_VOLUME_UP, NULL, 0);
    app_window_call_update_volume(2);
    gui_surface_commit();
#endif
}

static void app_window_call_outgoing_voldn_click_handler(gui_click_struct* click)
{
#if defined(__EXT_BT_AUDIO__)
    ext_btaud_send_cmd(AU_CMD_VOLUME_DOWN, NULL, 0);
    app_window_call_update_volume(3);
    gui_surface_commit();
#endif
}

static const gui_touch_event_struct app_window_call_vol_touch_events[] =
{
    {.id = CALL_LAYOUT_VOLUP_ID, .click = app_window_call_outgoing_volup_click_handler },
    {.id = CALL_LAYOUT_VOLDN_ID, .click = app_window_call_outgoing_voldn_click_handler},

};

static const app_window_event_struct app_window_call_vol_events[] =
{
    {.id = EVENT_BTAUD_STATUS,   .handler = app_window_call_vol_handler },
    {.id = EVENT_BL_TIMEOUT,     .handler = NULL },
    {.id = EVENT_MESSAGE,        .handler = NULL },
};


const gui_window_struct app_window_call_vol =
{
	.screen = &gui_screen_call_vol,

	.init = app_window_call_vol_init,
	.load = app_window_call_vol_load,
	.entry = app_window_call_vol_entry,
	.exit = app_window_call_vol_exit,
	.destroy = app_window_call_vol_destroy,

	.touch_event_num = countof(app_window_call_vol_touch_events),
	.touch_events = app_window_call_vol_touch_events,

    .event_num = countof(app_window_call_vol_events),
    .events = app_window_call_vol_events,
};
