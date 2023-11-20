
#include "debug_info.h"
#include "data_receive_package.h"

#include "application_config_app_info.h"

#include "gui_surface.h"
#include "gui_surface_cache.h"
#include "gui_surface_layout.h"
#include "gui_surface_box_layout_item.h"

#include "app_more_info/app_window_moreinfo.h"
#include "app_window_moreinfo_icon_list.h"
#include "gui_surface_layout_listview.h"

static const APP_INFO_ID g_menu_app_list[] =
{
	APP_INFO_ID_SPORT,
	APP_INFO_ID_SIRI,
	APP_INFO_ID_PHOTO,

	APP_INFO_ID_HR,
	APP_INFO_ID_O2,
	APP_INFO_ID_CALL,

	APP_INFO_ID_FIND,
	APP_INFO_ID_STOPWATCH,
	APP_INFO_ID_SETTING,

	APP_INFO_ID_BRIGHTNESS,
	APP_INFO_ID_LCDTIMEOUT,
	APP_INFO_ID_WATCHFACE,

	APP_INFO_ID_SLEEP,
	APP_INFO_ID_MUSIC,
    APP_INFO_ID_COUNTER,

    APP_INFO_ID_WEATHER,
    APP_INFO_ID_BREATHE,
	APP_INFO_ID_QR,
    APP_INFO_ID_WOMAN,
    APP_INFO_ID_GAME,
    APP_INFO_ID_ALIPAY,

	APP_INFO_ID_REBOOT,
	APP_INFO_ID_RESTORE,

	APP_INFO_ID_BLOOD,
	APP_INFO_ID_SHUTDOWN,
	APP_INFO_ID_ABOUT,

};
static const int WIDGET_LIST_NUM = (sizeof(g_menu_app_list)/sizeof(g_menu_app_list[0]));


#define WIDGET_ADD_GAP_LEFT 8
#define WIDGET_ADD_GAP_RIGHT 127
static app_info_struct* menu_list_get_info(int index)
{
    APP_INFO_ID  app_id = g_menu_app_list[index];
    if (app_id != APP_INFO_ID_NONE) {
        return get_app_info_by_id(app_id);
    }
    return NULL;
}


static unsigned int menu_list_get_count(void)
{
    return WIDGET_LIST_NUM;
}

static gui_layout_list_struct gui_window_menu_list_layout =
{
	.row_height = 66,

	.top = 10,
	.bottom = 5,    // 10,
	.space = 5,
	.scroll = 1,
};


static const gui_screen_struct gui_screen_menu_list =
{
	.type = TYPE_GUI_LAYOUT_LIST,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.layout_config = &gui_window_menu_list_layout,
};

/*-----------------------------ϵͳ�¼�--------------------------------------*/
static gui_image_struct gui_menu_list_icon1 = {
    .type = TYPE_GUI_DRAW_PICTURE,
};

static gui_image_struct gui_menu_list_icon2 = {
    .type = TYPE_GUI_DRAW_PICTURE,
};

static gui_image_struct gui_menu_list_icon3 = {
    .type = TYPE_GUI_DRAW_PICTURE,
};

static gui_mix_struct gui_menu_list_item[] = {
    { .data = &gui_menu_list_icon1,  },
    { .data = &gui_menu_list_icon2,  },
    { .data = &gui_menu_list_icon3,  },
};

static gui_widget_struct gui_menu_info = {
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = 60,
        .visible= 1,
        .child_num = 3,
        .children = gui_menu_list_item
};

static void app_window_moreinfo_icon_list_init_box(gui_box_struct* box, unsigned int box_idx, unsigned int icon_idx, icon_num)
{
  	app_info_struct* app_info1;
    app_info_struct* app_info2;
	app_info_struct* app_info3;

    if (box->id == 0) {
        box->id = box_idx+1;
        box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
        box->widget = &gui_menu_info;
        box->x = gui_menu_info.x;
        box->y = gui_menu_info.y;
        box->width = LCD_SIZE_WIDTH;
        box->height = gui_menu_info.height;
        box->visible = 1;

        // set icons
        app_info1 = menu_list_get_info(icon_idx);
        gui_menu_list_icon1.data = app_info1->icons[0];
        if ((icon_idx+1) < icon_num) {
            app_info2 = menu_list_get_info(icon_idx+1);
            gui_menu_list_icon2.data = app_info2->icons[0];
            if ((icon_idx+2) < icon_num) {
                app_info3 = menu_list_get_info(icon_idx+2);
                gui_menu_list_icon3.data = app_info3->icons[0];
                gui_menu_info.child_num = 3;
            }
            else {
                gui_menu_info.child_num = 2;
            }
        }
        else {
            gui_menu_info.child_num = 1;
        }
    }
}

static void app_menu_list_refresh()
{
	app_info_struct* app_info1;
    unsigned int box_num, box_idx;
    unsigned int icon_idx, icon_num;
    unsigned int iw, ih, gap_x, gap_y;

    app_info1 = menu_list_get_info(0);
    iw = app_info1->icons[0]->width;
    ih = app_info1->icons[0]->height;

    gap_x = (LCD_SIZE_WIDTH - 3*iw)/3;
    gap_y = (LCD_SIZE_HEIGHT - 3*iw)/4;

    gui_menu_list_icon1.x = gap_x/2;
    gui_menu_list_icon2.x = LCD_SIZE_WIDTH/3 + gap_x/2;
    gui_menu_list_icon3.x = (2*LCD_SIZE_WIDTH)/3 + gap_x/2;
    gui_menu_info.height  = ih;

    // geg box_number
    icon_idx = 0;
    icon_num = menu_list_get_count();
    box_num = (icon_num + 2)/3;

    gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_menu_list);
	gui_surface_layout_listview_dynamic_init(surface);
    if (surface != NULL) {
        for (box_idx=0; box_idx<box_num; box_idx++) {
            gui_box_struct* box = gui_surface_layout_listview_dynamic_get_box(surface, box_idx+1);    // gui_surface_cache_add_box();
            if (box != NULL) {
                app_window_moreinfo_icon_list_init_box(box, box_idx, icon_idx, icon_num);
                gui_surface_layout_listview_dynamic_add_item(surface,box);
            }
            icon_idx += 3;
        }
		gui_surface_layout_listview_dynamic_finish(surface);
    }
}

static void app_window_menu_list_init(void *buf)
{

}

static void app_window_menu_list_load(void *buf)
{
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_menu_list);
	gui_surface_layout_listview_dynamic_create(surface,app_menu_list_refresh);
}

static void app_window_menu_list_entry(void *buf)
{

}


static void app_window_menu_list_exit()
{

}

 static void app_window_menu_list_destroy()
{

}



/*-----------------------------��Ӧ�¼�--------------------------------------*/
static void app_window_menu_list_touch_event_click_on_layout_item(gui_click_layout_struct *event)
{
	SYS_DEBUG("app_window_test1_touch_event_click_on_layout_item x=%d y=%d index=%d",event->x,event->y,event->index);
	unsigned int icon_num, icon_index = event->index * 3;

    icon_num = menu_list_get_count();

    if (event->x > (LCD_SIZE_WIDTH/3)) {
		if(event->x > ((LCD_SIZE_WIDTH/3)*2)){
			icon_index ++;
		}
		icon_index ++;
    }

    if (icon_index < icon_num) {
        // add
        app_info_struct* app_info = menu_list_get_info(icon_index);
        if (app_info != NULL) {
            entry_app_by_info(app_info);
       }
    }
}


/*-----------------------------����--------------------------------------*/
static void app_window_moreinfo_list_key1_handler(void* buf)
{
    app_window_moreinfo_change();
}

static void app_window_list_menu_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_menu_list);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_DOWN);

	}
    else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_UP);
	}
	gui_surface_commit();
}



static const app_window_event_struct app_window_moreinfo_events[] =
{
    {
        .id = EVENT_KEY1_DOUBLE,
        .handler = app_window_moreinfo_list_key1_handler,
    },
    {
       .id = EVENT_ROLKEY,
       .handler = app_window_list_menu_rolkey_handler,
    },
};


const gui_window_struct app_window_moreinfo_icon_list =
{
	.screen = &gui_screen_menu_list,

	.init = app_window_menu_list_init,
	.load = app_window_menu_list_load,
	.entry = app_window_menu_list_entry,
	.exit = app_window_menu_list_exit,
	.destroy = app_window_menu_list_destroy,

	/*�Ű��������Ӧ����¼�*/
	.click_on_layout_item = app_window_menu_list_touch_event_click_on_layout_item,

	.event_num = countof(app_window_moreinfo_events),
	.events = app_window_moreinfo_events,
};

