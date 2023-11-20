#include "app_window_language.h"
#include "app_window_language_layout.h"
#include "debug_info.h"

#include "application_titlebar.h"
#include "data_common.h"
#include "language.h"

const language_strings_struct * language_string;

static unsigned char g_lang_bak = 0;
static unsigned char m_language_index = 0; // 
/*-----------------------------系统事件--------------------------------------*/

char get_langugae_id()
{
	return sys_language_type[m_language_index];
}

char get_langugae_string()
{
	return m_language_index;
}

static void app_window_language_update(void);

static void app_window_language_init(void *buf)
{
	language_string = GUI_Get_ID(STRING_LANGUAGE_NAME,NULL);
	for (char i = 0; i < sys_language_get_number(); i++)
	{
		if (g_language.num == sys_language_type[i])
		{
			m_language_index = i;
			break;
		}
	}
}

static void app_window_language_load(void *buf)
{
	app_window_language_update();
}

static void app_window_language_entry(void *buf)
{
}

static void app_window_language_exit()
{
}

static void app_window_language_destroy()
{
}

/*-----------------------------响应事件--------------------------------------*/

static void app_window_language_yes_click_handler()
{
	if (sys_language_type[m_language_index] != g_language.num)
	{
		g_language.num = sys_language_type[m_language_index];
		block_save_user_info(&g_language);
		LOG_DEBUG("222 %d", g_language.num);
	}

	g_language_list_flag = 1;
	block_save_user_info(&g_language_list_flag);
	application_goto_main();
}

static void app_window_language_update(void)
{
	short index[3];
	index[0] = m_language_index - 1;
	index[1] = m_language_index;
	index[2] = m_language_index + 1;

	if (m_language_index == 0)
	{
		index[0] = sys_language_get_number() - 1;
	}
	else if (m_language_index == sys_language_get_number() - 1)
	{
		index[2] = 0;
	}
	SYS_DEBUG("index %d,%d,%d", index[0], index[1], index[2]);

	for (short idx = 0; idx < 3; idx++)
	{
		gui_box_struct *box = gui_surface_get_box(&gui_screen_language_list, idx + LANGUAGE_ID_LINE_1);
		if (box != NULL)
		{
			gui_surface_box_label_change_string(box, (unsigned char *)language_string->string[index[idx]]);
		}
	}
}

static unsigned char app_window_language_event_touch(gui_touch_struct *event)
{
	static short pre_y = 0;
	static short rem_y = 0;
	short dlt_y, dlt;

	if (event->type == TOUCH_EVENT_TYPE_MOVE)
	{
		if (event->direction == DIRECTION_TYPE_LEFT && first_connection_flag == 1)
		{
			application_go_back();
		}
		else if (event->direction == DIRECTION_TYPE_UP || event->direction == DIRECTION_TYPE_DOWN)
		{
			dlt_y = pre_y - event->y;
			dlt_y += rem_y;
			dlt = dlt_y / LANGUAGE_LINE_H;
			if (dlt != 0)
			{
				m_language_index += dlt;
				if (m_language_index == 255)
				{
					m_language_index = sys_language_get_number() - 1;
				}
				else if (m_language_index > sys_language_get_number() - 1)
				{
					m_language_index = 0;
				}

				app_window_language_update();
				gui_surface_commit();

				pre_y = event->y;
				rem_y = dlt_y % LANGUAGE_LINE_H;
			}
		}
		return 1;
	}
	else if ((event->type == TOUCH_EVENT_TYPE_DOWN) || (event->type == TOUCH_EVENT_TYPE_CANCLE))
	{
		pre_y = event->y;
		rem_y = 0;
		return 1;
	}

	return 0;
}

static unsigned char app_window_language_event_click(gui_click_struct *event)
{
	app_window_language_yes_click_handler();
}

static const gui_touch_event_struct app_window_language_touch_events[] =
	{
		{
			.id = LANGUAGE_ID_YES_BG,
			.click = app_window_language_event_click,
		},
		{
			.id = 0xFFFF,
			.touch = app_window_language_event_touch,
		},
};

static void app_window_language_list_rolkey_handler(void *buf)
{
	rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
	gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_language_list);

	if (rolkey->rotate == ROTATE_TYPE_FORWARD)
	{
		m_language_index += 1;

		if(m_language_index > sys_language_get_number() - 1) {
            m_language_index = 0;
        }
        app_window_language_update();

	}
	else if(rolkey->rotate == ROTATE_TYPE_BACKWARD)
	{
		m_language_index -=1;
		if(m_language_index == 255) {
            m_language_index = sys_language_get_number() - 1;
        }
		app_window_language_update();
	}

	gui_surface_commit();
}

static void app_window_language_key1_short_handler(void *buf)
{
	if (first_connection_flag == 1)
		application_go_back();
}

static const app_window_event_struct app_window_language_events[] =
	{
		{
			.id = EVENT_ROLKEY,
			.handler = app_window_language_list_rolkey_handler,
		},

		// {
		// 	.id = EVENT_KEY1_SHORT,
		// 	.handler = app_window_language_key1_short_handler,
		// },
		{
			.id = EVENT_KEY2_SHORT,
			.handler = app_window_language_key1_short_handler,
		},

};

/*-----------------------------配置--------------------------------------*/

const gui_window_struct app_window_language_list =
	{
		.screen = &gui_screen_language_list,

		.init = app_window_language_init,
		.load = app_window_language_load,
		.entry = app_window_language_entry,
		.exit = app_window_language_exit,
		.destroy = app_window_language_destroy,

		/*排版界面上响应点击事件*/
		// .click_on_layout_item = app_window_more_list_touch_event_click_on_layout_item,

		.touch_event_num = countof(app_window_language_touch_events),
		.touch_events = app_window_language_touch_events,

		.event_num = countof(app_window_language_events),
		.events = app_window_language_events,
};
