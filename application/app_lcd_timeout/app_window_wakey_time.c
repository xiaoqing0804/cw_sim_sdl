
#include "app_task_main.h"
#include "data_manager_user_info.h"

#include "application_titlebar.h"

#include "app_window_wakey_time.h"
#include "app_window_wakey_time_layout.h"
#include "gui_surface_box_image_progress.h"
#include "gui_surface_box_image_number.h"
#include "gui_surface_box_label.h"

static unsigned char m_wakey_time = 5;  //Ϣ���r�g ������λ
static void app_window_wakey_time_update(void)
{
    gui_box_struct* box;
    gui_node_struct* node;
    unsigned int index, count = 0, flags;
    char temp[40];
	if(m_wakey_time == 5)
	{
		snprintf(temp, sizeof(temp), "%02d",20);
		gui_box_struct*  hour_up = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_0);
		gui_surface_box_label_change_string(hour_up,(unsigned char *)temp);
	}
	else
	{
		snprintf(temp, sizeof(temp), "%02d",m_wakey_time -5);
		gui_box_struct*  hour_up = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_0);
		gui_surface_box_label_change_string(hour_up,(unsigned char *)temp);
	}

	snprintf(temp, sizeof(temp), "%02d",m_wakey_time);
	gui_box_struct*  hour = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_2);
	gui_surface_box_label_change_string(hour,(unsigned char *)temp);

	if(m_wakey_time == 20)
	{
		snprintf(temp, sizeof(temp), "%02d",5);
		gui_box_struct*  hour_down = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_1);
		gui_surface_box_label_change_string(hour_down,(unsigned char *)temp);
	}
	else
	{
		snprintf(temp, sizeof(temp), "%02d",m_wakey_time+5);
		gui_box_struct*  hour_down = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_1);
		gui_surface_box_label_change_string(hour_down,(unsigned char *)temp);
	}
}

/*-----------------------------ϵͳ�¼�--------------------------------------*/
static void app_window_wakey_time_init(void *buf)
{
	m_wakey_time = application_get_aod_timeout();
}

static void app_window_wakey_time_load(void *buf)
{
    app_window_wakey_time_update();

//    application_titlebar_create(&gui_screen_wakey_time, STRING_LCD_TIMEOUT);
}


static void app_window_wakey_time_entry(void *buf)
{

}


static void app_window_wakey_time_exit()
{
//	application_set_aod_timeout(m_wakey_time);
}

static void app_window_wakey_time_destroy()
{

}

/*-----------------------------��Ӧ�¼�--------------------------------------*/
static unsigned char app_window_wakey_time_event_touch(gui_touch_struct *event)
{
    char temp[20];
	SYS_DEBUG("app_window_clock_set_hour_time");
	if(event->type == TOUCH_EVENT_TYPE_MOVE)
		{
			if(gui_run_time_lock())
				return 1;
            if(event->direction == DIRECTION_TYPE_LEFT)
            {
                application_go_back();
            }else if(event->direction == DIRECTION_TYPE_UP)
			{

				m_wakey_time-=5;

				if(m_wakey_time <  5)
				{
					m_wakey_time = 20;
				}
				else if(m_wakey_time > 20)
				{
					m_wakey_time = 20;
				}

				if(m_wakey_time == 5)
				{
					snprintf(temp, sizeof(temp), "%02d",20);
					gui_box_struct*  hour_up = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_0);
					gui_surface_box_label_change_string(hour_up,(unsigned char *)temp);
				}
				else
				{
					snprintf(temp, sizeof(temp), "%02d",m_wakey_time -5);
					gui_box_struct*  hour_up = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_0);
					gui_surface_box_label_change_string(hour_up,(unsigned char *)temp);
				}

				snprintf(temp, sizeof(temp), "%02d",m_wakey_time);
				gui_box_struct*  hour = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_2);
				gui_surface_box_label_change_string(hour,(unsigned char *)temp);

				if(m_wakey_time == 20)
				{
					snprintf(temp, sizeof(temp), "%02d",5);
					gui_box_struct*  hour_down = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_1);
					gui_surface_box_label_change_string(hour_down,(unsigned char *)temp);
				}
				else
				{
					snprintf(temp, sizeof(temp), "%02d",m_wakey_time+5);
					gui_box_struct*  hour_down = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_1);
					gui_surface_box_label_change_string(hour_down,(unsigned char *)temp);
				}

				gui_surface_commit();
			}
			else if(event->direction == DIRECTION_TYPE_DOWN)
			{
				m_wakey_time+=5;

				if(m_wakey_time > 20)
				{
					m_wakey_time = 5;
				}
				if(m_wakey_time == 5)
				{
					snprintf(temp, sizeof(temp), "%02d",20);
					gui_box_struct*  hour_up1 = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_0);
					gui_surface_box_label_change_string(hour_up1,(unsigned char *)temp);
				}
				else
				{
					snprintf(temp, sizeof(temp), "%02d",m_wakey_time -5);
					gui_box_struct*  hour_up1 = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_0);
					gui_surface_box_label_change_string(hour_up1,(unsigned char *)temp);
				}

				snprintf(temp, sizeof(temp), "%02d",m_wakey_time);
				gui_box_struct*  hour1 = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_2);
				gui_surface_box_label_change_string(hour1,(unsigned char *)temp);

				if(m_wakey_time == 20)
				{
					snprintf(temp, sizeof(temp), "%02d",5);
					gui_box_struct*  hour_down1 = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_1);
					gui_surface_box_label_change_string(hour_down1,(unsigned char *)temp);
				}
				else
				{
					snprintf(temp, sizeof(temp), "%02d",m_wakey_time+5);
					gui_box_struct*  hour_down1 = gui_surface_get_box(&gui_screen_wakey_time, (unsigned short) LCD_TIME_ID_LINE_1);
					gui_surface_box_label_change_string(hour_down1,(unsigned char *)temp);
				}

				gui_surface_commit();
			}
			return 1;
		}
		else if(event->type == TOUCH_EVENT_TYPE_DOWN)
		{
			return 1;
		}

	return 0;
}

static void app_window_wakey_time_ok(gui_click_struct *envent)
{
    application_set_aod_timeout(m_wakey_time);
	block_save_user_info(&forget_aod);

	application_reset_display_timeout(0);
    application_go_back();
}

static void app_window_wakey_time_key_andler(void* buf)
{
    app_window_wakey_time_ok(NULL);
}



static void app_window_lcd_time_rolkey_handler(void* buf)
{
    rolkey_event_struct* rolkey = (rolkey_event_struct*)buf;
    short dlt;

    if (rolkey->rotate == ROTATE_TYPE_BACKWARD) {
        dlt = -5;
    }
    else {
        dlt = 5;
    }

    m_wakey_time += dlt;
    if(m_wakey_time > 20) {
        m_wakey_time -= (20);
    }
    else {
        if(m_wakey_time < 5)
            m_wakey_time += (20);
    }
    app_window_wakey_time_update();
    gui_surface_commit();
}

/*-----------------------------����--------------------------------------*/

static const gui_touch_event_struct app_window_wakey_time_touch_events[] =
{
	{
		.id = LCD_TIME_ID_PIC,
		.click = app_window_wakey_time_ok,
        .offset_left = LCD_SIZE_HALF_WIDTH-1,
	},
    {
		.id = LCD_TIME_ID_BG,
		.touch = app_window_wakey_time_event_touch,
	},
};

static const app_window_event_struct app_window_wakey_time_events[] =
{
    {
        .id = EVENT_KEY2_SHORT,
        .handler = app_window_wakey_time_key_andler,
    },
	{
        .id = EVENT_ROLKEY,
        .handler = app_window_lcd_time_rolkey_handler,
    },
};



const gui_window_struct app_window_wakey_time =
{
    .screen = &gui_screen_wakey_time,
    .init = app_window_wakey_time_init,
    .load = app_window_wakey_time_load,
    .entry = app_window_wakey_time_entry,
    .exit = app_window_wakey_time_exit,
    .destroy = app_window_wakey_time_destroy,

    .touch_event_num = countof(app_window_wakey_time_touch_events),
    .touch_events = app_window_wakey_time_touch_events,

    .event_num = countof(app_window_wakey_time_events),
    .events = app_window_wakey_time_events,
};

