
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

#include "app_window_localmusic_filelist.h"

extern u16   music_file_get_count(void);
extern char *music_file_get_name(int index, char *nameBuff);
extern void  app_music_player_index(u16 index);

#define GUI_MUSIC_FILELIST_ITEM_H       50
#define GUI_MUSIC_FILELIST_BASE_ID      30

/////////////////////////////////////////////////////////////////////////////////////////////////////////
static const gui_layout_list_struct gui_window_localmusic_filelist_layout =
{
	.row_height = GUI_MUSIC_FILELIST_ITEM_H,
	.top = 10,
	.bottom = 1,
	.space = 4,
	.scroll = 1,
};


static const gui_screen_struct gui_screen_localmusic_filelist =
{
	.type = TYPE_GUI_LAYOUT_LIST,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.layout_config = &gui_window_localmusic_filelist_layout,
};

// list
static char g_filename_buff[192];
static const gui_font_struct gui_text_localmusic_filename =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.x = 10,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_SMALL,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = g_filename_buff,
};


static const gui_mix_struct gui_item_localmusic_filename[] =
{
	{
		.data = &gui_text_localmusic_filename,
	},
};

static const gui_widget_struct gui_widget_localmusic_filename = {
        .id = 0,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = GUI_MUSIC_FILELIST_ITEM_H,
        .visible= 1,
        .child_num = 1,
        .children = gui_item_localmusic_filename
};

static void app_window_localmusic_file_list_init_box_data(gui_box_struct* box, unsigned int box_idx)
{
    if (box->id == 0) {
        box->id = GUI_MUSIC_FILELIST_BASE_ID+box_idx;
        box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
        box->widget = &gui_widget_localmusic_filename;
        box->x = 0;
        box->y = 0;
        box->width = LCD_SIZE_WIDTH;
        box->height = GUI_MUSIC_FILELIST_ITEM_H;
        box->visible = 1;
    }
}

static void app_sport_list_refresh()
{
    unsigned int box_num, box_idx;

    // geg box_number
    box_num = music_file_get_count();
    
    gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_localmusic_filelist);
	gui_surface_layout_listview_dynamic_init(surface);
	
    if (surface != NULL) {
        for (box_idx=0; box_idx<box_num; box_idx++) {
            // get filename
            if (NULL != music_file_get_name(box_idx, g_filename_buff)) {
                gui_box_struct* box = gui_surface_layout_listview_dynamic_get_box(surface, GUI_MUSIC_FILELIST_BASE_ID+box_idx);    // gui_surface_cache_add_box();
                if (box != NULL) {
                    app_window_localmusic_file_list_init_box_data(box, box_idx);
                    gui_surface_layout_listview_dynamic_add_item(surface,box);
                }
            }
        }
		gui_surface_layout_listview_dynamic_finish(surface);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_localmusic_filelist_init(void *buf)
{
}

static void app_window_localmusic_filelist_load(void *buf)
{
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_localmusic_filelist);
	gui_surface_layout_listview_dynamic_create(surface,app_sport_list_refresh);	
}


static void app_window_localmusic_filelist_entry(void *buf)
{
    if (!app_music_running()) {
        application_send_event(EVENT_GO_HOME, NULL);
    }
}


static void app_window_localmusic_filelist_exit()
{
}

static void app_window_localmusic_filelist_destroy()
{
}


//
static void app_window_localmusic_filelist_click_on_layout_item(gui_click_layout_struct *event)
{
    int index = event->id - GUI_MUSIC_FILELIST_BASE_ID;
    SYS_DEBUG("app: music_filelist_onclick, index=%d", index);
    if (index > 0 && index < music_file_get_count()) {
        app_music_player_index(index);
        application_go_back();
    }
}


static void app_window_localmusic_filelist_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_localmusic_filelist);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD) 
	{	
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_DOWN);

	}
    else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_UP);
	}	
	gui_surface_commit();
}

static void app_window_appmod_ind_handler(void* buf)
{
    SYS_DEBUG("app: music_fl, app_window_appmod_ind_handler");
    application_goto_main();
}

// 
static const app_window_event_struct app_window_localmusic_filelist_events[] = 
{
    {.id = EVENT_ROLKEY,       .handler = app_window_localmusic_filelist_rolkey_handler},
    {.id = EVENT_APPMOD_IND,   .handler = app_window_appmod_ind_handler},
};

const gui_window_struct app_window_localmusic_filelist =
{
	.screen = &gui_screen_localmusic_filelist,

	.init = app_window_localmusic_filelist_init,
	.load = app_window_localmusic_filelist_load,
	.entry = app_window_localmusic_filelist_entry,
	.exit = app_window_localmusic_filelist_exit,
	.destroy = app_window_localmusic_filelist_destroy,

	.click_on_layout_item = app_window_localmusic_filelist_click_on_layout_item,

    .event_num = countof(app_window_localmusic_filelist_events),
    .events = app_window_localmusic_filelist_events,
};


