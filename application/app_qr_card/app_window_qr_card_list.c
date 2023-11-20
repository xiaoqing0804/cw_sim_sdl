#include "debug_info.h"
#include "bsp_includes.h"
#include "os_mem.h"
#include "data_common.h"
#include "data_manager_qr_info.h"
#include "storage_qr_info.h"
#include "application_config_app_info.h"

#include "gui_window.h"

#include "app_window_qr_card_list.h"
#include "app_window_qr_card_list_ui.h"
#include "app_window_qr_card_list_layout.h"
#include "app_window_qr_card.h"


#if defined(GUI_QR_INFO_SUPPORT)&&GUI_QR_INFO_SUPPORT

static void app_window_qr_card_list_list_init(void *buf)
{
}

static void app_window_qr_card_list_list_load(void *buf)
{
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_qr_card_list);
	gui_surface_layout_listview_dynamic_create(surface,app_window_qr_card_list_list_refresh);
	//application_titlebar_create(&gui_screen_qr_card_list, STRING_CARD_HOLDER);
}


static void app_window_qr_card_list_list_entry(void *buf)
{
}


static void app_window_qr_card_list_list_exit()
{

}

static void app_window_qr_card_list_list_destroy()
{

}

static void app_window_qr_card_list_event_touch(gui_click_struct *event)
{
}


static void app_window_qr_card_list_touch_event_click_on_layout_item(gui_click_layout_struct *event)
{
	unsigned int qr_indx = event->id - QR_CARD_LIST_BASE_ID;
	application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_qr_card, &qr_indx);
}

static void app_window_qr_list_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_qr_card_list);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_DOWN);
	}
    else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_UP);
	}
	gui_surface_commit();
}


static const app_window_event_struct app_window_qr_list_events[] =
{
	{.id = EVENT_ROLKEY,   .handler = app_window_qr_list_rolkey_handler },
	{.id = EVENT_QR_CARD_REFLASH, .handler = app_window_qr_card_storage_reflash_handler}
};


const gui_window_struct app_window_qr_card_list =
{
	.screen = &gui_screen_qr_card_list,
	.init = app_window_qr_card_list_list_init,
	.load = app_window_qr_card_list_list_load,
	.entry = app_window_qr_card_list_list_entry,
	.exit = app_window_qr_card_list_list_exit,
	.destroy = app_window_qr_card_list_list_destroy,

	.click_on_layout_item = app_window_qr_card_list_touch_event_click_on_layout_item,

	.event_num = countof(app_window_qr_list_events),
    .events = app_window_qr_list_events,
};

#endif
