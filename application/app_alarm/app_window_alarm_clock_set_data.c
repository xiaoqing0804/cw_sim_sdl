#include "debug_info.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "arithmetic_steps.h"
#include "data_receive_package.h"

#include "gui_window.h"
#include "app_window_alarm_clock_set_data.h"
#include "application_config_app_info.h"
#include "app_window_alarm_clock.h"
#include "application_titlebar.h"
#include "gui_surface_layout_listview.h"

#define LIST_ITEM_H  70

/*-----------------------------系统事件--------------------------------------*/
static const unsigned char g_app_window_clock_data_map[] =
{
	STRING_SUNDAY,
	STRING_MONDAY,
	STRING_TUESDAY,
	STRING_WEDNESDAY,
	STRING_THURSDAY,
	STRING_FRIDAY,
	STRING_SATURDAY,

};
static const int APP_WINDOW_CLOCK_DATA_LIST_NUM = (sizeof(g_app_window_clock_data_map)/sizeof(g_app_window_clock_data_map[0]));

static gui_font_struct g_gui_clock_data_item_text =     // must with static!
{
    .type = TYPE_GUI_DRAW_TEXT,
    .x = 130,
    .y = 0,
	.height =LIST_ITEM_H,
	.value_align = GUI_ALIGN_VCENTER,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
};


static gui_image_struct g_gui_clock_data_item_pic =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
	.x = 50,
    .y = 15,
 	.data = &pic_radio_unselected_info,
};

static app_info_struct* app_window_clock_data_list_get_info(int index)
{
    if (index < APP_WINDOW_CLOCK_DATA_LIST_NUM) {
        APP_INFO_ID  app_id = g_app_window_clock_data_map[index];
        if (app_id != APP_INFO_ID_NONE) {
            return get_app_info_by_id(app_id);
        }
    }
    return NULL;
}

static unsigned int app_window_clock_data_list_get_count(void)
{
    return APP_WINDOW_CLOCK_DATA_LIST_NUM;
}



static const gui_image_struct g_gui_clock_data_add =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_timer_add_info,
};
static const gui_font_struct gui_clock_data_add_ok =   //ʱ��
{
    .type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_YES,
};


static const gui_layout_list_struct g_app_window_clock_data_layout =
{
	.row_height = LIST_ITEM_H,
	.top = GUI_CONTENT_GAP_TOP,
	.bottom = 115,
	.space = 28,
	.scroll = 1,
	.can_swipe =0,
};

enum{
	CLOCK_DATA_ADD= 10,
	CLOCK_DATA_ADD_TEXT,
};

static const gui_widget_struct gui_clock_data_widget[] = {

	{
		.id = CLOCK_DATA_ADD,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 364,
		.width = LCD_SIZE_WIDTH,
		.height = 102,
		.visible= 1,
		.order = 1,
		.child_num = 1,
		.children = &g_gui_clock_data_add,
    },
	{
		.id = CLOCK_DATA_ADD_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 395,
        .width = LCD_SIZE_WIDTH,
        .height = 43,
        .rotate = 0,
		.order = 1,
        .visible= 1,
        .child_num = 1,
        .children = &gui_clock_data_add_ok,
	},
};

static const gui_screen_struct gui_screen_clock_data_list =
{
	.type = TYPE_GUI_LAYOUT_LIST,
	.layout_config = &g_app_window_clock_data_layout,
	.child_num = countof(gui_clock_data_widget),
    .children = gui_clock_data_widget
};

static const gui_mix_struct gui_clock_data_item[] =
{
	{
		.data = &g_gui_clock_data_item_text,
	},
	{
		.data = &g_gui_clock_data_item_pic,
	},
};

static const gui_widget_struct gui_clock_data_info = {
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.width = LCD_SIZE_WIDTH,
		.height = LIST_ITEM_H,
		.visible= 1,
		.child_num = countof(gui_clock_data_item),
		.children = gui_clock_data_item
};


static void app_window_clock_data_list_init_box_data(gui_box_struct* box, unsigned int box_idx)
{
    if (box->id == 0)
    {
        gui_widget_struct* menu_info = &gui_clock_data_info;

		box->id = box_idx+10;
		box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
		box->widget = &gui_clock_data_info;
		box->x = gui_clock_data_info.x;
		box->y = gui_clock_data_info.y;
		box->width = gui_clock_data_info.width;
		box->height = gui_clock_data_info.height;
		box->visible = gui_clock_data_info.visible;

		g_gui_clock_data_item_text.value.string_id = g_app_window_clock_data_map[box->id-10];
		if((g_alarm_clock[g_clock_box_id-10].repeat & (1 << box_idx)) > 0)
			g_gui_clock_data_item_pic.data = &pic_radio_selected_info;
		else
			g_gui_clock_data_item_pic.data = &pic_radio_unselected_info;
    }
}

static void app_window_clock_data_list_refresh()
{
	SYS_DEBUG("app_window_clock_data_long_list_refresh");
    gui_surface_struct* surface;
    gui_box_struct*     box;

    unsigned int box_idx;
    unsigned int icon_num;
	// application_titlebar_create(&gui_screen_clock_data_list, STRING_CLOCK_DATE_SET);

    // geg box_number
    icon_num = app_window_clock_data_list_get_count();

    surface = gui_surface_get_surface(&gui_screen_clock_data_list);
    if (surface != NULL) {
		gui_surface_layout_listview_clear_item_box(surface);		// 20230923 Taylor.Le, 清除列表，否则点击状态不能改变..
		gui_surface_layout_listview_dynamic_init(surface);
        for (box_idx=0; box_idx<icon_num; box_idx++) {
            box = gui_surface_layout_listview_dynamic_get_box(surface, box_idx+10);	// gui_surface_cache_add_box();
            if ((box != NULL) ) {
				app_window_clock_data_list_init_box_data(box, box_idx);
                gui_surface_layout_listview_dynamic_add_item(surface,box);
            }
        }
		gui_surface_layout_listview_dynamic_finish(surface);
    }
}


static void app_window_clock_data_list_init(void *buf)
{

}

static void app_window_clock_data_list_load(void *buf)
{
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_clock_data_list);
	gui_surface_layout_listview_dynamic_create(surface,app_window_clock_data_list_refresh);

	application_titlebar_create(&gui_screen_clock_data_list,STRING_CLOCK_DATE_SET);

}


static void app_window_clock_data_list_entry(void *buf)
{
}


static void app_window_clock_data_list_exit()
{

}

static void app_window_clock_data_list_destroy()
{

}

static void app_window_clock_data_touch_event_click_on_layout_item(gui_click_layout_struct *event)
{
	SYS_DEBUG("app_window_clock_data_touch_event_click_on_layout_item =%d",event->id);
	if((g_alarm_clock[g_clock_box_id-10].repeat & (1 << (event->id -10))) > 0)
		g_alarm_clock[g_clock_box_id-10].repeat = (g_alarm_clock[g_clock_box_id-10].repeat - (1 << (event->id -10)));
	else
		g_alarm_clock[g_clock_box_id-10].repeat = (g_alarm_clock[g_clock_box_id-10].repeat | (1 << (event->id -10)));

	SYS_DEBUG("g_alarm_clock[g_clock_box_id-10].repeat =%x",g_alarm_clock[g_clock_box_id-10].repeat);

	app_window_clock_data_list_refresh();

	gui_surface_commit();
}



static void app_window_clock_set_date_ok(gui_click_struct *envent)
{

	block_save_user_info(&g_alarm_clock);
	application_go_back();
}

static const gui_touch_event_struct app_window_clock_set_date_touch_events[] =
{
	{
		.id = CLOCK_DATA_ADD,
		.click = app_window_clock_set_date_ok,
	},
};

static void app_window_alarm_clock_list_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_clock_data_list);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_DOWN);

	}else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_UP);
	}

	gui_surface_commit();

}


static const app_window_event_struct app_window_clock_long_list_events[] =
{
	 {
        .id = EVENT_ROLKEY,
        .handler = app_window_alarm_clock_list_rolkey_handler,
	 },
};

const gui_window_struct app_window_clock_data_list =
{
	.screen = &gui_screen_clock_data_list,
	.init = app_window_clock_data_list_init,
	.load = app_window_clock_data_list_load,
	.entry = app_window_clock_data_list_entry,
	.exit = app_window_clock_data_list_exit,
	.destroy = app_window_clock_data_list_destroy,

	.click_on_layout_item = app_window_clock_data_touch_event_click_on_layout_item,

	.touch_event_num = countof(app_window_clock_set_date_touch_events),
	.touch_events = app_window_clock_set_date_touch_events,

	.event_num = countof(app_window_clock_long_list_events),
    .events = app_window_clock_long_list_events,

};

