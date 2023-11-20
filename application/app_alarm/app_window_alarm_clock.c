#include "debug_info.h"
#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_transfer.h"
#include "gui_window.h"
#include "app_window_alarm_clock_set.h"


static gui_font_struct gui_text_clock_time =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 1,
    .x = 56,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_NUMBER_29,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "00:00",
};

static gui_image_struct g_gui_clock_onoff =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
	.id = 2,
	.x = 312,
	.y = 15,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_on_info,
};


static gui_image_struct g_gui_clock_bg =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_bg_info,
};

static gui_image_struct g_gui_clock_add =     // must with static!
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.data = &pic_timer_add_info,
};

static gui_font_struct gui_text_clock_add =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_CLOCK_ADD,
};



static gui_image_struct g_gui_clock_week_sun =     // must with static!
{

	    .type = TYPE_GUI_DRAW_PICTURE,
		.id = 3,
		.x = 56,
		.y = 50,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_clock_s_info,
};

static gui_image_struct g_gui_clock_week_mon =
{
	    .type = TYPE_GUI_DRAW_PICTURE,
		.id = 4,
		.x = 81,
		.y = 50,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_clock_m_info,
};

static gui_image_struct g_gui_clock_week_tue =
{
	    .type = TYPE_GUI_DRAW_PICTURE,
		.id = 5,
		.x = 106,
		.y = 50,
		.anchor_x = 0,
		.anchor_y = 0,
		.data = &pic_clock_t_info,
};

static gui_image_struct g_gui_clock_week_wed =
{
    .type = TYPE_GUI_DRAW_PICTURE,
	.id = 6,
	.x = 131,
	.y = 50,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_w_info,
};

static gui_image_struct g_gui_clock_week_thu =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 7,
	.x = 156,
	.y = 50,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_t_info,
};

static gui_image_struct g_gui_clock_week_fri =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 8,
	.x = 181,
	.y = 50,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_f_info,
};

static gui_image_struct g_gui_clock_week_sat =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 9,
	.x = 206,
	.y = 50,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_clock_s_info,
};


/*-----------------------------系统事件--------------------------------------*/
// static const char g_app_window_clock_time_indx[5] =
// {

// };
// static const int APP_WINDOW_CLOCK_NUM = (sizeof(g_app_window_clock_time_indx)/sizeof(g_app_window_clock_time_indx[0]));

static const gui_layout_list_struct g_app_window_clock_time_layout =
{
	.row_height = 70,

	.top = 75,
	.bottom = 110,
	.space = 30,


	.scroll = 1,
};

enum{
	CLOCK_BG=6,
	CLOCK_ADD,
	CLOCK_ADD_TEXT,
};


gui_widget_struct gui_widget_clock_time_list[] =
{
	{
    	.id = CLOCK_BG,
		.type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT-60,
        .visible= 1,
        .child_num = 1,
        .children = &g_gui_clock_bg
    },
    {
		.id = CLOCK_ADD,
		.y = 364,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.width = LCD_SIZE_WIDTH,
		.height = 102,
		.visible= 1,
		.order = 1,
		.child_num = 1,
		.children = &g_gui_clock_add
    },
	{
		.id = CLOCK_ADD_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 395,
        .width = LCD_SIZE_WIDTH,
        .height = 43,
		.order = 1,
        .rotate = 0,
        .visible= 1,
        .child_num = 1,
        .children = &gui_text_clock_add,
	},

};


static const gui_screen_struct gui_screen_clock_time_list =
{
	.type = TYPE_GUI_LAYOUT_LIST,
	.layout_config = &g_app_window_clock_time_layout,
	.child_num = countof(gui_widget_clock_time_list),
    .children = gui_widget_clock_time_list
};




static unsigned int app_window_clock_time_list_get_count(void)
{
	char number = 0;
	for (char i = 0; i < ALARM_CLOCK_MAX_TOTAL; i++)
	{
		if(g_alarm_clock[i].offon !=NULL)
		{
			number++;
		}
	}

    return number;
}

static unsigned int app_window_clock_time_list_get_set(void)
{
	unsigned int box_idx;
    unsigned int icon_num;
	unsigned int clock_set_num = 0;
	icon_num = app_window_clock_time_list_get_count();


	for(box_idx=0; box_idx<icon_num; box_idx++)
	{
		if(g_alarm_clock[box_idx].offon >= 2)
		{
			clock_set_num = 0;
		}
		else
		{
			clock_set_num++;
		}

	}
	if(clock_set_num == icon_num)
		return 1;
	else
		return 0;
}

static unsigned int app_window_clock_time_list_get_box_item(void)
{
	unsigned int box_idx;
    unsigned int icon_num;
	unsigned int clock_set_num = 0;
	icon_num = app_window_clock_time_list_get_count();


	for(box_idx=0; box_idx<icon_num; box_idx++)
	{
		if(g_alarm_clock[box_idx].offon >= 2)
		{
			clock_set_num++;
		}
	}

	return clock_set_num;
}

gui_mix_struct gui_clock_item[] =
{
    {
        .data = &gui_text_clock_time,
    },
    {
        .data = &g_gui_clock_onoff,
    },
    {
        .data = &g_gui_clock_week_sun,
    },
    {
        .data = &g_gui_clock_week_mon,
    },
    {
        .data = &g_gui_clock_week_tue,
    },
    {
        .data = &g_gui_clock_week_wed,
    },
    {
        .data = &g_gui_clock_week_thu,
    },
    {
        .data = &g_gui_clock_week_fri,
    },
    {
        .data = &g_gui_clock_week_sat,
    },
};

gui_widget_struct gui_clcok_info = {
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = 70,
        .visible= 1,
        .child_num = countof(gui_clock_item),
        .children = gui_clock_item
};

static void app_window_clock_time_list_init_box_data(gui_box_struct* box, unsigned int box_idx)
{
	char temp[20];
    if (box->id == 0)
    {
        gui_widget_struct* menu_info = &gui_clcok_info;

                box->id = box_idx+10;
                box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
                box->widget = &gui_clcok_info;
                box->x = gui_clcok_info.x;
                box->y = gui_clcok_info.y;
                box->width = gui_clcok_info.width;
                box->height = gui_clcok_info.height;
                box->visible = gui_clcok_info.visible;

				if(g_alarm_clock[box_idx].offon >= 2)
				{
					if(g_alarm_clock[box_idx].offon == 2)
						g_gui_clock_onoff.data = &pic_clock_off_info;
					else
						g_gui_clock_onoff.data = &pic_clock_on_info;

					SYS_DEBUG("g_alarm_clock[box_idx].repeat=%d, %02x",box_idx,g_alarm_clock[box_idx].repeat);
					if((g_alarm_clock[box_idx].repeat & 0X01) > 0)
						g_gui_clock_week_sun.data = &pic_clock_s1_info;
					else
						g_gui_clock_week_sun.data = &pic_clock_s_info;

					if((g_alarm_clock[box_idx].repeat & 0X40) > 0)
						g_gui_clock_week_sat.data = &pic_clock_s1_info;
					else
						g_gui_clock_week_sat.data = &pic_clock_s_info;

					if((g_alarm_clock[box_idx].repeat & 0X20) > 0)
						g_gui_clock_week_fri.data = &pic_clock_f1_info;
					else
						g_gui_clock_week_fri.data = &pic_clock_f_info;

					if((g_alarm_clock[box_idx].repeat & 0X10) > 0)
						g_gui_clock_week_thu.data = &pic_clock_t1_info;
					else
						g_gui_clock_week_thu.data = &pic_clock_t_info;

					if((g_alarm_clock[box_idx].repeat & 0X08) > 0)
						g_gui_clock_week_wed.data = &pic_clock_w1_info;
					else
						g_gui_clock_week_wed.data = &pic_clock_w_info;

					if((g_alarm_clock[box_idx].repeat & 0X04) > 0)
						g_gui_clock_week_tue.data = &pic_clock_t1_info;
					else
						g_gui_clock_week_tue.data = &pic_clock_t_info;

					if((g_alarm_clock[box_idx].repeat & 0X02) > 0)
						g_gui_clock_week_mon.data = &pic_clock_m1_info;
					else
						g_gui_clock_week_mon.data = &pic_clock_m_info;

					snprintf(temp, sizeof(temp), "%02d:%02d",g_alarm_clock[box_idx].hour,g_alarm_clock[box_idx].min );
					gui_text_clock_time.value.string = temp;

				}
				else
				{
					box->visible = 0;
				}
    }
}


static void app_window_clock_time_list_refresh()
{
	SYS_DEBUG("app_window_clock_time_list_refresh");
    gui_surface_struct* surface;
    gui_box_struct*     box;

    unsigned int box_idx;
    unsigned int icon_num;

    // geg box_number
    icon_num = app_window_clock_time_list_get_count();
	if(icon_num>=ALARM_CLOCK_MAX_TOTAL){
    	box = gui_surface_get_box(&gui_screen_clock_time_list, CLOCK_ADD);
		if (box != NULL) box->visible = 0;

		box = gui_surface_get_box(&gui_screen_clock_time_list, CLOCK_ADD_TEXT);
		if (box != NULL) box->visible = 0;
	}
	else{
		box = gui_surface_get_box(&gui_screen_clock_time_list, CLOCK_ADD);
		if (box != NULL) box->visible = 1;

		box = gui_surface_get_box(&gui_screen_clock_time_list, CLOCK_ADD_TEXT);
		if (box != NULL) box->visible = 1;
	}


    surface = gui_surface_get_surface(&gui_screen_clock_time_list);
    if (surface != NULL) {
        gui_surface_layout_listview_dynamic_init(surface);

        for (box_idx=0; box_idx<icon_num; box_idx++)
		{
            box = gui_surface_layout_listview_dynamic_get_box(surface, box_idx+10);// gui_surface_cache_add_box();
            if (box != NULL)
			{
				app_window_clock_time_list_init_box_data(box, box_idx);
                gui_surface_layout_listview_dynamic_add_item(surface,box);
            }
        }

		gui_surface_layout_listview_dynamic_finish(surface);
    }

    SYS_DEBUG("more: refresh exit\n");
}



unsigned char g_clock_box_id;

/*-----------------------------系统事件--------------------------------------*/

static void app_window_clock_init(void *buf)
{

}

static void app_window_clock_load(void *buf)
{
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_clock_time_list);
	gui_surface_layout_listview_dynamic_create(surface,app_window_clock_time_list_refresh);

	gui_box_struct *box = gui_surface_get_box(&gui_screen_clock_time_list,CLOCK_BG);
	if(app_window_clock_time_list_get_set())
	{
		box->visible = 1;
	}
	else
	{
		box->visible = 0;
	}
}


static void app_window_clock_entry(void *buf)
{
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_clock_time_list);
	gui_surface_layout_listview_offset(surface, 0, 0);
}


static void app_window_clock_exit()
{
	block_save_user_info(&g_alarm_clock);
}

static void app_window_clock_destroy()
{

}

static void app_window_clock_add_event_touch(gui_click_struct *event)
{
	if(event->id == CLOCK_ADD)
	{
		g_clock_box_id = app_window_clock_time_list_get_box_item() + 10;
		g_alarm_clock[g_clock_box_id-10].offon = 3;
		g_alarm_clock[g_clock_box_id-10].repeat = 0x7F;

		block_save_user_info(&g_alarm_clock);

		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_clock_set, NULL);
	}
}

/*-----------------------------配置--------------------------------------*/

static const gui_touch_event_struct app_window_clock_touch_events[] =
{
	{	.id = CLOCK_ADD,
		.click = app_window_clock_add_event_touch,
	},
};

static void app_window_clock_click_on_layout_item(gui_click_layout_struct *event)
{

	g_clock_box_id = event->id;

	gui_box_struct *box = gui_surface_get_box(&gui_screen_clock_time_list, event->id);

	SYS_DEBUG("app_window_clock_click_on_layout_item =%d",event->id);
	if(event->id == CLOCK_ADD)
	{
		g_clock_box_id = app_window_clock_time_list_get_box_item() + 10;
		g_alarm_clock[g_clock_box_id-10].offon = 2;
		g_alarm_clock[g_clock_box_id-10].repeat = 0x7F;

		block_save_user_info(&g_alarm_clock);

		application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_clock_set, NULL);
		return;

	}

	if (box != NULL)
	{
		if(event->x >220)
		{
			if(g_alarm_clock[g_clock_box_id-10].offon > 2)
			{
				g_alarm_clock[g_clock_box_id-10].offon = 2;

				gui_surface_box_layout_item_change_image(box,2,&pic_clock_off_info);
			}
			else
			{
				g_alarm_clock[g_clock_box_id-10].offon = 3;
				gui_surface_box_layout_item_change_image(box,2,&pic_clock_on_info);
			}

			block_save_user_info(&g_alarm_clock);

			gui_surface_commit();
		}
		else
		{
			application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_clock_set, NULL);
		}
	}

}

static void app_window_alarm_clock_list_rolkey_handler(void* buf)
{
	rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
	gui_surface_struct* surface = gui_surface_get_surface(&gui_screen_clock_time_list);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_DOWN);

	}else if(rolkey->rotate == ROTATE_TYPE_BACKWARD){
		gui_surface_layout_listview_switch_to_item(surface,DIRECTION_TYPE_UP);
	}

	gui_surface_commit();

}


static const app_window_event_struct app_window_alarm_clock_long_list_events[] =
{
	 {
        .id = EVENT_ROLKEY,
        .handler = app_window_alarm_clock_list_rolkey_handler,
	 },
};


const gui_window_struct app_window_clock =
{
	.screen = &gui_screen_clock_time_list,
	.init = app_window_clock_init,
	.load = app_window_clock_load,
	.entry = app_window_clock_entry,
	.exit = app_window_clock_exit,
	.destroy = app_window_clock_destroy,


	.click_on_layout_item = app_window_clock_click_on_layout_item,

	.touch_event_num = countof(app_window_clock_touch_events),
	.touch_events = app_window_clock_touch_events,


	.event_num = countof(app_window_alarm_clock_long_list_events),
    .events = app_window_alarm_clock_long_list_events,
};

