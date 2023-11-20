#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"
#include "data_manager_message.h"
#include "app_window_stopwatch.h"


#include "data_manager_contact.h"

#include "srv_call.h"

#include "gui_drivers_display.h"
#include "gui_surface.h"
#include "gui_surface_cache.h"
#include "gui_surface_layout.h"
#include "gui_surface_box_layout_item.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_base.h"

#include "application_config_main_window.h"
#include "gui_surface_layout_listview.h"


#define GUI_STOP_WATCH_ITEM_H    58





static const gui_layout_list_struct gui_stop_watch_record_layout =
{
	.total = 0,
	.height = 0,
	.row_height = GUI_STOP_WATCH_ITEM_H,

	.top = 40,
	.bottom = 40,
	.space = 10,
	.scroll = 1,
};

static const gui_screen_struct app_stop_watch_record_screen =
{
    .type = TYPE_GUI_LAYOUT_LIST,
    .layout_config = &gui_stop_watch_record_layout,
};

//////////////////////////////////////////////////////////////////////////////////////////////////////

static gui_font_struct gui_stop_watch_record_item_num =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_VCENTER),
	.x = 80,
	.y = 0,
    .width = 50,
    .height = GUI_STOP_WATCH_ITEM_H,
    .color = COLOR_RGB(0, 255, 0),
    .size = SYS_FONT_NUMBER_35,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "1",
};

static gui_font_struct gui_stop_watch_record_item_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_VCENTER),
	.x = 160,
	.y = 0,
    .width = 200,
    .height = GUI_STOP_WATCH_ITEM_H,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_35,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00:00:00",
};


static gui_mix_struct gui_stop_watch_record_item[] =
{
	{
		.data = &gui_stop_watch_record_item_num,
	},
    {
        .data = &gui_stop_watch_record_item_time,
    },
};

static const gui_widget_struct gui_stop_watch_record_widget_temp = {
        .id = 20,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = GUI_STOP_WATCH_ITEM_H,
        .visible= 1,
        .child_num = countof(gui_stop_watch_record_item),
        .children = gui_stop_watch_record_item
};

static void app_window_stop_watch_record_refresh(void)
{
    gui_box_struct* box;
    unsigned long time;
    char temp[40];
    char temp1[20];
    unsigned int idx, count = stop_watch_get_count();

    gui_surface_struct* surface = gui_surface_get_surface(&app_stop_watch_record_screen);

	gui_surface_layout_listview_dynamic_init(surface);
    if (surface != NULL) {
        for (idx=0; idx<count; idx++) {
            //box = gui_surface_cache_add_box();
            box = gui_surface_layout_listview_dynamic_get_box(surface, idx+1);
            if (box != NULL) {
                box->id = idx+1;
                box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
                box->widget = &gui_stop_watch_record_widget_temp;
                box->x = 0;
                box->y = 0;
                box->width = LCD_SIZE_WIDTH;
                box->height = GUI_STOP_WATCH_ITEM_H;
                box->visible = 1;

                snprintf(temp1, sizeof(temp1), "%02d",idx+1);
                gui_stop_watch_record_item_num.value.string = temp1;
                time= app_window_stopwatch_get_record_time(idx);
                snprintf(temp, sizeof(temp), "%02d:%02d:%02d", time/1000/60, (time/1000)%60, (time%1000)/10);
                gui_stop_watch_record_item_time.value.string = (unsigned char *)temp;

				gui_surface_layout_listview_dynamic_add_item(surface,box);
            }
        }

		gui_surface_layout_listview_dynamic_finish(surface);
    }

}




/*-----------------------------系统事件--------------------------------------*/
static void app_window_stop_watch_record_init(void *buf)
{
}

static void app_window_stop_watch_record_load(void *buf)
{
	gui_surface_struct* surface = gui_surface_get_surface(&app_stop_watch_record_screen);
	gui_surface_layout_listview_dynamic_create(surface,app_window_stop_watch_record_refresh);
}

static void app_window_stop_watch_record_entry(void *buf)
{
}

static void app_window_stop_watch_record_exit()
{
}

static void app_window_stop_watch_record_destroy(void)
{
}

static void app_window_stop_watch_record_item_click(gui_click_layout_struct *event)
{

}

static void app_window_clog_view_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&app_stop_watch_record_screen);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_DOWN);

	}else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_UP);
	}

	gui_surface_commit();

}


static const app_window_event_struct app_window_stop_watch_record_events[] =
{
    {
        .id = EVENT_ROLKEY,
        .handler = app_window_clog_view_rolkey_handler,
    },
};


const gui_window_struct app_window_stop_watch_record =
{
	.screen = &app_stop_watch_record_screen,

	.init = app_window_stop_watch_record_init,
	.load = app_window_stop_watch_record_load,
	.entry = app_window_stop_watch_record_entry,
	.exit = app_window_stop_watch_record_exit,
	.destroy = app_window_stop_watch_record_destroy,

	.click_on_layout_item = app_window_stop_watch_record_item_click,


	.event_num = countof(app_window_stop_watch_record_events),
	.events = app_window_stop_watch_record_events,
};




