
#include "debug_info.h"
#include "data_receive_package.h"
#include "application_config_app_info.h"

#include "gui_surface_layout_listview.h"

#include "app_window_moreinfo.h"
#include "app_window_moreinfo_list.h"
#include "app_window_moreinfo_list_layout.h"


static const APP_INFO_ID g_app_window_moreinfo_list_map[] =
{
    APP_INFO_ID_HR,
    APP_INFO_ID_SPORT,
    APP_INFO_ID_ALIPAY,

    APP_INFO_ID_BREATHE,
    APP_INFO_ID_O2,
    APP_INFO_ID_SLEEP,

    APP_INFO_ID_BLOOD,
    APP_INFO_ID_COUNTER,
    APP_INFO_ID_WOMAN,

    APP_INFO_ID_ALARM,
    APP_INFO_ID_STEP,
    APP_INFO_ID_MUSIC,

    APP_INFO_ID_STOPWATCH,
    APP_INFO_ID_MESSAGE,
    APP_INFO_ID_SIRI,

    APP_INFO_ID_WEATHER,
    APP_INFO_ID_WATCHFACE,
    APP_INFO_ID_FIND,

    APP_INFO_ID_CLACULATOR,
    APP_INFO_ID_CALL,
    APP_INFO_ID_GAME,

    APP_INFO_ID_CALENDAR,
	APP_INFO_ID_PHOTO,
	APP_INFO_ID_BRIGHTNESS,

    APP_INFO_ID_LCDTIMEOUT,
	APP_INFO_ID_SETTING,
    APP_INFO_ID_QR_PUSH,

    APP_INFO_ID_RESTORE,
	APP_INFO_ID_SOS,
    APP_INFO_ID_REBOOT,

    APP_INFO_ID_QR,
    APP_INFO_ID_ABOUT,
    APP_INFO_ID_SHUTDOWN,

};
static const int APP_WINDOW_MOREINFO_LIST_NUM = (sizeof(g_app_window_moreinfo_list_map)/sizeof(g_app_window_moreinfo_list_map[0]));



static const gui_image_struct gui_more_list_up_bg_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
  //  .data = &pic_more_list_bg_info,
};

static const gui_image_struct gui_more_list_down_bg_image =
{
	.type = TYPE_GUI_DRAW_PICTURE,
 //   .data = &pic_more_list_down_bg_info,
};

static const gui_widget_struct gui_more_list_bg_widget[] =
{
	{
		.type = TYPE_GUI_CONTROL_IMAGE,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
	},

};

static const gui_layout_list_struct g_app_window_moreinfo_list_layout =
{
	.row_height = 98,

    .top = 50,
	.bottom = 50,
	.space = 40,

	.scroll = 1,
	.can_swipe = 0,
    .auto_start = 1,
};

static const gui_screen_struct gui_screen_moreinfo_list =
{
	.type = TYPE_GUI_LAYOUT_LIST,
    .layout_config = &g_app_window_moreinfo_list_layout,
    .children = gui_more_list_bg_widget,
    .child_num = countof(gui_more_list_bg_widget),

};
/*-----------------------------ϵͳ�¼�--------------------------------------*/
static gui_image_struct g_gui_menu_item_pic =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .x = 86,
    .y = 0,
};

static gui_font_struct g_gui_menu_item_text =     // must with static!
{
    .type = TYPE_GUI_DRAW_TEXT,
    .x = 191,
    .y = 35,
    .width = LCD_SIZE_WIDTH - 191,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .scroll = 1,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
};
static const gui_mix_struct gui_menu_item[] =
    {
        {
            .data = &g_gui_menu_item_pic,
        },
        {
            .data = &g_gui_menu_item_text,
        },
};

static const gui_widget_struct gui_menu_info =
{
    .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
    .width = LCD_SIZE_WIDTH,
    .height = 98,
    .visible= 1,
    .child_num = 2,
    .clip =1,
    .children = gui_menu_item
};

static app_info_struct* app_window_moreinfo_list_get_info(int index)
{
    if (index < APP_WINDOW_MOREINFO_LIST_NUM) {
        APP_INFO_ID  app_id = g_app_window_moreinfo_list_map[index];
        if (app_id != APP_INFO_ID_NONE) {
            return get_app_info_by_id(app_id);
        }
    }
    return NULL;
}


static unsigned int app_window_moreinfo_list_get_count(void)
{
    return APP_WINDOW_MOREINFO_LIST_NUM;
}

static void app_window_moreinfo_list_init_box_data(gui_box_struct* box, app_info_struct* app_info)
{
    if (box->id == 0)
    {
        gui_widget_struct* menu_info = &gui_menu_info;

        box->id = app_info->id;
        box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
        box->widget = menu_info;
        box->x = menu_info->x;
        box->y = menu_info->y;
        box->width = menu_info->width;
        box->height = menu_info->height;
		box->visible = menu_info->visible;

        // set icons
        g_gui_menu_item_pic.data = app_info->icons[0];
        g_gui_menu_item_text.value.string_id = app_info->name;
    }
}

static void app_window_moreinfo_list_refresh()
{
    gui_surface_struct* surface;
    gui_box_struct*     box;
    app_info_struct*    app_info;

    unsigned int box_idx;
    unsigned int icon_num;

    // geg box_number
    icon_num = app_window_moreinfo_list_get_count();
    SYS_DEBUG("more: icon_num=%d\n", icon_num);

    surface = gui_surface_get_surface(&gui_screen_moreinfo_list);
    if (surface != NULL) {
        //gui_surface_layout_listview_clear_item_box(surface);
        gui_surface_layout_listview_dynamic_init(surface);

        for (box_idx=0; box_idx<icon_num; box_idx++) {
            app_info = app_window_moreinfo_list_get_info(box_idx);
            if ((app_info != NULL) && (app_info->icons != NULL)) {
                if(g_user.sex==0&&app_info->id==APP_INFO_ID_WOMAN)
                    continue;

                box = gui_surface_layout_listview_dynamic_get_box(surface, app_info->id);
                if ((box != NULL)) {
                    app_window_moreinfo_list_init_box_data(box, app_info);
                    gui_surface_layout_listview_dynamic_add_item(surface,box);
                }
            }
        }

		gui_surface_layout_listview_dynamic_finish(surface);
    }
    SYS_DEBUG("more: refresh exit\n");
}
/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_moreinfo_list_init(void *buf)
{

}

static void app_window_moreinfo_list_load(void *buf)
{
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_moreinfo_list);
	gui_surface_layout_listview_dynamic_create(surface,app_window_moreinfo_list_refresh);
}

static void app_window_moreinfo_list_entry(void *buf)
{

}

static void app_window_moreinfo_list_exit()
{

}

static void app_window_moreinfo_list_destroy()
{

}



/*-----------------------------��Ӧ�¼�--------------------------------------*/
static void app_window_moreinfo_list_touch_event_click_on_layout_item(gui_click_layout_struct *event)
{
	SYS_DEBUG("app_window_test1_touch_event_click_on_layout_item x=%d y=%d index=%d",event->x,event->y,event->index);
    app_info_struct* app_info = get_app_info_by_id((APP_INFO_ID)event->id);
    if (app_info != NULL) {
        entry_app_by_info(app_info);
    }
}
static unsigned char app_window_more_info_event_touch(gui_touch_struct *envent)
{
	if(envent->type == TOUCH_EVENT_TYPE_UP)
	{
		if(envent->direction == DIRECTION_TYPE_LEFT)
		{
			application_goto_main();
		}
		return 1;
	}
	else if(envent->type == TOUCH_EVENT_TYPE_DOWN)
	{
		return 1;
	}
	else if(envent->type == TOUCH_EVENT_TYPE_MOVE)
	{
		return 1;
	}

	return 0;
}

static void app_window_moreinfo_list_key1_handler(void* buf)
{
    app_window_moreinfo_change();
}

static void app_window_list_view_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_moreinfo_list);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_DOWN);

	}else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_UP);
	}

	gui_surface_commit();

}

static const app_window_event_struct app_window_moreinfo_events[] =
{
	 {
		#if GUI_SINGLE_KEY_SUPPORT
            .id = EVENT_KEY1_DOUBLE,
		#else
            .id = EVENT_KEY2_DOUBLE,
		#endif		
        .handler = app_window_moreinfo_list_key1_handler,
    },
    {
       .id = EVENT_ROLKEY,
       .handler = app_window_list_view_rolkey_handler,
    },
};

static const gui_touch_event_struct app_window_more_info_touch_events[] =
{
	{	.id = 0xFFFF,
		.touch = app_window_more_info_event_touch,
	},
};

static const gui_window_config_struct app_window_moreinfo_list_config =
{
    .disable_scale = 1,
};

/*-----------------------------����--------------------------------------*/
const gui_window_struct app_window_moreinfo_list =
{
	.screen = &gui_screen_moreinfo_list,
    .config = &app_window_moreinfo_list_config,

	.init = app_window_moreinfo_list_init,
	.load = app_window_moreinfo_list_load,
	.entry = app_window_moreinfo_list_entry,
	.exit = app_window_moreinfo_list_exit,
	.destroy = app_window_moreinfo_list_destroy,

	/*�Ű��������Ӧ����¼�*/
	.click_on_layout_item = app_window_moreinfo_list_touch_event_click_on_layout_item,

    .event_num = countof(app_window_moreinfo_events),
    .events = app_window_moreinfo_events,

  	.touch_event_num = countof(app_window_more_info_touch_events),
	.touch_events = app_window_more_info_touch_events,
};

