
#include "app_task_main.h"
#include "data_manager_user_info.h"

#include "application_titlebar.h"

#include "app_window_alarm_clock_set_time.h"
#include "gui_surface_box_image_progress.h"
#include "gui_surface_box_image_number.h"
#include "gui_surface_box_label.h"
#include "data_common.h"
#include "app_window_alarm_clock.h"


static unsigned char clock_time_hour = 0;
static unsigned char clock_time_min = 0;
static unsigned char touch_time_flag;		// 0: hour; 1: minute


#define ALARM_DRAW_LINE_X1    (LCD_SIZE_WIDTH/7)
#define ALARM_DRAW_LINE_X2    (LCD_SIZE_WIDTH*3/7)
#define ALARM_DRAW_LINE_W     (ALARM_DRAW_LINE_X2 - ALARM_DRAW_LINE_X1 + 1)

#define ALARM_DRAW_LINE_X3    (LCD_SIZE_WIDTH*4/7)
#define ALARM_DRAW_LINE_X4    (LCD_SIZE_WIDTH*6/7)

#define ALARM_DRAW_LINE_Y1    (LCD_SCALE_HEIGHT*191)
#define ALARM_DRAW_LINE_Y2    (LCD_SCALE_HEIGHT*280)
#define ALARM_DRAW_LINE_H     (ALARM_DRAW_LINE_Y2 - ALARM_DRAW_LINE_Y1 + 1)




static const gui_image_struct gui_pic_clock_time_ok =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_timer_add_info,
};


static const gui_font_struct gui_public_clock_time_ok =   //ʱ��
{
    .type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_YES,
};

static const gui_font_struct gui_public_clock_number_gray =   //ʱ��
{
    .type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(76, 76, 76),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .size = SYS_FONT_LARGE,
    .value_type = GUI_FONT_VALUE_TYPE_NUMBER,
    .value.number = 3,
};

static const gui_font_struct gui_public_clock_number_hilight =   //ʱ��
{
    .type = TYPE_GUI_DRAW_TEXT,
    .color = COLOR_RGB(255, 255, 255),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .size = SYS_FONT_XLARGE,
    .value_type = GUI_FONT_VALUE_TYPE_NUMBER,
    .value.number = 3,
};


static const gui_canvas_struct gui_clock_time_line_shapes[] =
{
    {
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(0, 114, 255),
        .canvas.line.x0 = ALARM_DRAW_LINE_X1,
        .canvas.line.y0 = ALARM_DRAW_LINE_Y1,
        .canvas.line.x1 = ALARM_DRAW_LINE_X2,
        .canvas.line.y1 = ALARM_DRAW_LINE_Y1,
    },

    {
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(0, 114, 255),
        .canvas.line.x0 = ALARM_DRAW_LINE_X1,
        .canvas.line.y0 = ALARM_DRAW_LINE_Y2,
        .canvas.line.x1 = ALARM_DRAW_LINE_X2,
        .canvas.line.y1 = ALARM_DRAW_LINE_Y2,
    },

	{
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(0, 114, 255),
        .canvas.line.x0 = ALARM_DRAW_LINE_X3,
        .canvas.line.y0 = ALARM_DRAW_LINE_Y1,
        .canvas.line.x1 = ALARM_DRAW_LINE_X4,
        .canvas.line.y1 = ALARM_DRAW_LINE_Y1,
    },

    {
        .type = TYPE_GUI_DRAW_SHAPE_LINE,     // TYPE_GUI_DRAW
        .penSize = 1,
        .penColor = COLOR_RGB(0, 114, 255),
        .canvas.line.x0 = ALARM_DRAW_LINE_X3,
        .canvas.line.y0 = ALARM_DRAW_LINE_Y2,
        .canvas.line.x1 = ALARM_DRAW_LINE_X4,
        .canvas.line.y1 = ALARM_DRAW_LINE_Y2,
    },

};

enum
{
	CLOCK_TITLE_ID,
	CLOCK_HOUR_TIME_ID_LINE_0,
	CLOCK_HOUR_TIME_ID_LINE_2,
	CLOCK_HOUR_TIME_ID_LINE_1,
	CLOCK_HOUR_TIME_BG_ID,

	CLOCK_MIN_TIME_ID_LINE_0,
	CLOCK_MIN_TIME_ID_LINE_2,
	CLOCK_MIN_TIME_ID_LINE_1,
	CLOCK_MIN_TIME_BG_ID,
	CLOCK_OK_ID_PIC,
	CLOCK_OK_ID_PIC_TEXT,
};


static const gui_widget_struct gui_widget_clock_time[] =
{
    {
        .id = CLOCK_HOUR_TIME_ID_LINE_0,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = ALARM_DRAW_LINE_X1,
        .y = ALARM_DRAW_LINE_Y1 - ALARM_DRAW_LINE_H,
        .width = ALARM_DRAW_LINE_W,
        .height = ALARM_DRAW_LINE_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_clock_number_gray,
    },
    {
        .id = CLOCK_HOUR_TIME_ID_LINE_2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x =ALARM_DRAW_LINE_X1,
        .y =ALARM_DRAW_LINE_Y1,
        .width = ALARM_DRAW_LINE_W,
        .height = ALARM_DRAW_LINE_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_clock_number_hilight,
    },
    {
        .id = CLOCK_HOUR_TIME_ID_LINE_1,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = ALARM_DRAW_LINE_X1,
        .y = ALARM_DRAW_LINE_Y2,
        .width = ALARM_DRAW_LINE_W,
        .height = ALARM_DRAW_LINE_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_clock_number_gray,
    },

	{
        .id = CLOCK_MIN_TIME_ID_LINE_0,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = ALARM_DRAW_LINE_X3,
        .y = ALARM_DRAW_LINE_Y1-ALARM_DRAW_LINE_H,
        .width = ALARM_DRAW_LINE_W,
        .height = ALARM_DRAW_LINE_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_clock_number_gray,
    },
    {
        .id = CLOCK_MIN_TIME_ID_LINE_2,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = ALARM_DRAW_LINE_X3,
        .y = ALARM_DRAW_LINE_Y1,
        .width = ALARM_DRAW_LINE_W,
        .height = ALARM_DRAW_LINE_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_clock_number_hilight,
    },
    {
        .id = CLOCK_MIN_TIME_ID_LINE_1,
        .type = TYPE_GUI_CONTROL_LABEL,
        .x = ALARM_DRAW_LINE_X3,
        .y = ALARM_DRAW_LINE_Y2,
        .width = ALARM_DRAW_LINE_W,
        .height = ALARM_DRAW_LINE_H,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_clock_number_gray,
    },

    {   // line
        .type = TYPE_GUI_CONTROL_CANVAS,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = countof(gui_clock_time_line_shapes),
        .children = &gui_clock_time_line_shapes,
    },

	{
		.id = CLOCK_OK_ID_PIC,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = LCD_SIZE_HEIGHT - LCD_SCALE_HEIGHT*115,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SCALE_HEIGHT*115,
		.visible= 1,
		.child_num = 1,
		.children = &gui_pic_clock_time_ok,
	},
	{
		.id = CLOCK_OK_ID_PIC_TEXT,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = LCD_SIZE_HEIGHT - LCD_SCALE_HEIGHT*115,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SCALE_HEIGHT*115,
        .rotate = 0,
        .visible= 1,
        .child_num = 1,
        .children = &gui_public_clock_time_ok,
	},

};

const gui_screen_struct gui_screen_clock_set_time =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.children = gui_widget_clock_time,
	.child_num = countof(gui_widget_clock_time),
};



/*-----------------------------ϵͳ�¼�--------------------------------------*/
static void app_window_clock_update_time(void)
{
	char temp[40];
	if(clock_time_hour == 0)
	{
		snprintf(temp, sizeof(temp), "%02d",23);
		gui_box_struct*  hour_up = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_HOUR_TIME_ID_LINE_0);
		gui_surface_box_label_change_string(hour_up,(unsigned char *)temp);
	}
	else
	{
		snprintf(temp, sizeof(temp), "%02d",clock_time_hour -1);
		gui_box_struct*  hour_up = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_HOUR_TIME_ID_LINE_0);
		gui_surface_box_label_change_string(hour_up,(unsigned char *)temp);
	}

	snprintf(temp, sizeof(temp), "%02d",clock_time_hour);
	gui_box_struct*  hour = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_HOUR_TIME_ID_LINE_2);
	gui_surface_box_label_change_string(hour,(unsigned char *)temp);

	if(clock_time_hour == 23)
	{
		snprintf(temp, sizeof(temp), "%02d",0);
		gui_box_struct*  hour_down = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_HOUR_TIME_ID_LINE_1);
		gui_surface_box_label_change_string(hour_down,(unsigned char *)temp);
	}
	else
	{
		snprintf(temp, sizeof(temp), "%02d",clock_time_hour+1);
		gui_box_struct*  hour_down = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_HOUR_TIME_ID_LINE_1);
		gui_surface_box_label_change_string(hour_down,(unsigned char *)temp);
	}

	if(clock_time_min == 0)
	{
		snprintf(temp, sizeof(temp), "%02d",59);
		gui_box_struct*  min_up = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_MIN_TIME_ID_LINE_0);
		gui_surface_box_label_change_string(min_up,(unsigned char *)temp);
	}
	else
	{
		snprintf(temp, sizeof(temp), "%02d",clock_time_min -1);
		gui_box_struct*  min_up = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_MIN_TIME_ID_LINE_0);
		gui_surface_box_label_change_string(min_up,(unsigned char *)temp);
	}

	snprintf(temp, sizeof(temp), "%02d",clock_time_min);
	gui_box_struct*  min = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_MIN_TIME_ID_LINE_2);
	gui_surface_box_label_change_string(min,(unsigned char *)temp);

	if(clock_time_min == 59)
	{
		snprintf(temp, sizeof(temp), "%02d",0);
		gui_box_struct*  min_down = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_MIN_TIME_ID_LINE_1);
		gui_surface_box_label_change_string(min_down,(unsigned char *)temp);
	}
	else
	{
		snprintf(temp, sizeof(temp), "%02d",clock_time_min+1);
		gui_box_struct*  min_down = gui_surface_get_box(&gui_screen_clock_set_time, (unsigned short) CLOCK_MIN_TIME_ID_LINE_1);
		gui_surface_box_label_change_string(min_down,(unsigned char *)temp);
	}
}


static void app_window_clock_set_time_init(void *buf)
{
	clock_time_hour = g_alarm_clock[g_clock_box_id-10].hour;
	clock_time_min = g_alarm_clock[g_clock_box_id-10].min;
}

static void app_window_clock_set_time_load(void *buf)
{
    application_titlebar_create(&gui_screen_clock_set_time, STRING_CLOCK_TIME_SET);
	app_window_clock_update_time();
}


static void app_window_clock_set_time_entry(void *buf)
{
	//app_window_clock_update_time();
}


static void app_window_clock_set_time_exit()
{
}

static void app_window_clock_set_time_destroy()
{
	touch_time_flag = 0;
}


static void app_window_clock_set_hour(int add)
{
	if (add > 0) {
		clock_time_hour++;
		if(clock_time_hour > 23)
		{
			clock_time_hour = 0;
		}
	}
	else {
		clock_time_hour--;
		if(clock_time_hour <  0)
		{
			clock_time_hour = 23;
		}
		else if(clock_time_hour > 23)
		{
			clock_time_hour = 23;
		}
	}
	app_window_clock_update_time();
	gui_surface_commit();
}

static void app_window_clock_set_minute(int add)
{
	if (add > 0) {
		clock_time_min++;
		if(clock_time_min > 59)
		{
			clock_time_min = 0;
		}
	}
	else {
		clock_time_min--;
		if(clock_time_min <  0)
		{
			clock_time_min = 59;
		}
		else if(clock_time_min > 59)
		{
			clock_time_min = 59;
		}
	}
	app_window_clock_update_time();
	gui_surface_commit();
}

static unsigned char app_window_clock_set_hour_time(gui_touch_struct *event)
{
	SYS_DEBUG("app_window_clock_set_hour_time");
	if(event->type == TOUCH_EVENT_TYPE_MOVE)
		{
			if(gui_run_time_lock())
				return 1;
			if(event->direction == DIRECTION_TYPE_LEFT)
            {
                application_go_back();
            }
			else if(event->direction == DIRECTION_TYPE_UP)
			{
				app_window_clock_set_hour(-1);
			}
			else if(event->direction == DIRECTION_TYPE_DOWN)
			{
				app_window_clock_set_hour(1);
			}
			return 1;
		}
		else if(event->type == TOUCH_EVENT_TYPE_DOWN)
		{
			return 1;
		}

	return 0;
}

static unsigned char app_window_clock_set_min_time(gui_touch_struct *event)
{
	SYS_DEBUG("app_window_clock_set_min_time");
	if(event->type == TOUCH_EVENT_TYPE_MOVE)
	{
		if(gui_run_time_lock())
			return 1;
		if(event->direction == DIRECTION_TYPE_LEFT)
		{
			application_go_back();
		}
		else if(event->direction == DIRECTION_TYPE_UP)
		{
			app_window_clock_set_minute(-1);
		}
		else if(event->direction == DIRECTION_TYPE_DOWN)
		{
			app_window_clock_set_minute(1);
		}
		return 1;
	}
	else if(event->type == TOUCH_EVENT_TYPE_DOWN)
	{
		return 1;
	}
	return 0;
}

static unsigned char app_window_clock_set_time_event_touch(gui_touch_struct *event)
{
	unsigned char ret = 0;
	if (event->type == TOUCH_EVENT_TYPE_DOWN) {
		if (event->x < LCD_SIZE_HALF_WIDTH) {
			touch_time_flag = 0;
		}
		else {
			touch_time_flag = 1;
		}
	}

	if (touch_time_flag) {
		ret = app_window_clock_set_min_time(event);
	}
	else {
		ret = app_window_clock_set_hour_time(event);
	}
	return ret;
}

static void app_window_clock_set_time_ok(gui_click_struct *envent)
{
	g_alarm_clock[g_clock_box_id-10].hour = clock_time_hour;
	g_alarm_clock[g_clock_box_id-10].min = clock_time_min;

	block_save_user_info(&g_alarm_clock);
	application_go_back();
}

static void app_window_alarm_clock_set_time_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_clock_set_time);
	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		if (touch_time_flag == 0)
		{
			app_window_clock_set_hour(1);
		}
		else
		{
			app_window_clock_set_minute(1);
		}
	}
	else if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
	{
		if (touch_time_flag == 0)
		{
			app_window_clock_set_hour(-1);
		}
		else
		{
			app_window_clock_set_minute(-1);
		}
	}
}

static const app_window_event_struct app_window_alarm_clock_set_time_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_alarm_clock_set_time_rolkey_handler,
		},
};

/*-----------------------------����--------------------------------------*/

static const gui_touch_event_struct app_window_clock_set_time_touch_events[] =
{
	{
		.id = 0xFFFF,
		.touch = app_window_clock_set_time_event_touch,
	},

	{
		.id = CLOCK_OK_ID_PIC,
		.click = app_window_clock_set_time_ok,
	},
};




const gui_window_struct app_window_clock_set_time =
{
	.screen = &gui_screen_clock_set_time,
	.init = app_window_clock_set_time_init,
	.load = app_window_clock_set_time_load,
	.entry = app_window_clock_set_time_entry,
	.exit = app_window_clock_set_time_exit,
	.destroy = app_window_clock_set_time_destroy,

	.touch_event_num = countof(app_window_clock_set_time_touch_events),
	.touch_events = app_window_clock_set_time_touch_events,

	.event_num = countof(app_window_alarm_clock_set_time_events),
	.events = app_window_alarm_clock_set_time_events,
};

