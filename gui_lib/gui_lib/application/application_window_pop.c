#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "data_common.h"
#include "OTA.h"
#include "app_task_main.h"

#include "gui_window.h"

#include "application_window_pop.h"


#define POP_IMG_TXT_GAP         16

static const gui_image_struct gui_pop_image = 
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
};


static const gui_font_struct gui_pop_text =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .auto_wrap = 1,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
    .space_y = 10,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "Hello!",
};

enum
{
    WND_POP_IMAGE = 10,
    WND_POP_TEXT,
};

static const gui_widget_struct gui_pop_widget[] =
{
	{
		.id = WND_POP_IMAGE,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
        .child_num = 1,
        .children = &gui_pop_image,
	},

	{
		.id = WND_POP_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
		.visible= 1,
        .child_num = 1,
        .children = &gui_pop_text,
	},
};

static const gui_screen_struct gui_screen_pop =
{
	.children = gui_pop_widget,
	.child_num = countof(gui_pop_widget),
};


/*-----------------------------系统事件--------------------------------------*/
static void application_window_pop_init(void *buf)
{
    window_pop_info_struct* pop_info = application_get_pop_info();
    SYS_DEBUG("app: pop_init, str_id=%d, tout=%d", pop_info->str_id, pop_info->time_out);
}

static void application_window_pop_load(void *buf)
{
    window_pop_info_struct* pop_info = application_get_pop_info();
    picture_info_struct* pic = (picture_info_struct*)pop_info->param_p;
    gui_box_struct* ibox;
    gui_box_struct* tbox;
    unsigned int sh = 0, tw = 0, th = 0, tl = 0;
    unsigned int flags = 0;

    ibox = gui_surface_get_box(&gui_screen_pop, WND_POP_IMAGE);
    tbox = gui_surface_get_box(&gui_screen_pop, WND_POP_TEXT);
    if (ibox != NULL) {
        if (pic != NULL) {
            flags |= 0x01;
            ibox->visible = 1;
        }
        else {
            ibox->visible = 0;
        }
    }
    if (tbox != NULL) {
        if (pop_info->str_id != 0) {
            flags |= 0x02;
            tbox->visible = 1;
        }
        else {
            tbox->visible = 0;
        }
    }

    switch(flags) {
        case 3:
            // image & text
        	unsigned char* str = (unsigned char*)GUI_Get_ID_String((STRING_ID_TYPE)pop_info->str_id);
            unsigned char fs = set_font_size(gui_pop_text.size);
            get_font_string_meastrue(str, &tw, &th, &tl);

            sh = pic->height + th + POP_IMG_TXT_GAP;

            ibox->x = (LCD_SIZE_WIDTH - pic->width) / 2;
            ibox->y = (LCD_SIZE_HEIGHT - sh) / 2;
            ibox->width  = pic->width;
            ibox->height = pic->height;

            tbox->x = 0;
            tbox->y = ibox->y + pic->height + POP_IMG_TXT_GAP;
            tbox->width  = LCD_SIZE_WIDTH;
            tbox->height = th;
        
            gui_surface_box_image_change(ibox, pic);
            gui_surface_box_label_change_string_id(tbox, pop_info->str_id);
            break;
        case 2:
            // text only
            gui_surface_box_label_change_string_id(tbox, pop_info->str_id);
            break;
        case 1:
            // image only
            gui_surface_box_image_change(ibox, pic);
            break;
        default:
            application_send_event(EVENT_GO_BACK, NULL);
            break;
    }
}

static void application_window_pop_entry(void *buf)
{
    window_pop_info_struct* pop_info = application_get_pop_info();
    unsigned int tout = 3000;

    SYS_DEBUG("app: pop_entry");
    if (pop_info->time_out != 0) {
        tout = pop_info->time_out;
    }
    application_open_act_timer(APPLICATION_TIMER_ACT, tout);
    application_reset_display_timeout(0);
}


static void application_window_pop_exit()
{
    SYS_DEBUG("app: pop_exit");
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void application_window_pop_destroy()
{
    SYS_DEBUG("app: pop_destroy");
}


static void application_window_pop_acttimer_handler(void* buf)
{
    window_pop_info_struct* pop_info = application_get_pop_info();
    SYS_DEBUG("app: pop_acttimer_handler");
    application_close_act_timer(APPLICATION_TIMER_ACT);
    if (pop_info->onDestory != NULL) {
        application_send_event(EVENT_GUI_POP_CALLBACK, NULL);
    }
    else {
        application_go_back();
    }
}

static void application_window_pop_key_handler(void* buf)
{
    window_pop_info_struct* pop_info = application_get_pop_info();
    SYS_DEBUG("app: pop_key_handler");
    application_close_act_timer(APPLICATION_TIMER_ACT);
    if (pop_info->onDestory != NULL) {
        application_send_event(EVENT_GUI_POP_CALLBACK, NULL);
    }
    else {
        application_go_back();
    }
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct application_window_pop_static_events[] =
{
	{.id = EVENT_ACT,	.handler = application_window_pop_acttimer_handler	},
	{.id = EVENT_ALL,	.handler = application_window_pop_acttimer_handler	},
    {.id = EVENT_KEY2_SHORT,          .handler = application_window_pop_key_handler},
    {.id = EVENT_KEY1_SHORT,          .handler = application_window_pop_key_handler},
    {.id = EVENT_BL_TIMEOUT},       // 不允许灭屏 ...
};

static const gui_window_config_struct application_window_pop_config =
{
	.entry_back_to_destory = 1,
    .forbid_gesture_back = 1,
};


const gui_window_struct application_window_pop =
{
	.screen = &gui_screen_pop,
	.config = &application_window_pop_config,

	.init = application_window_pop_init,
	.load = application_window_pop_load,
	.entry = application_window_pop_entry,
	.exit = application_window_pop_exit,
	.destroy = application_window_pop_destroy,

	.event_num = countof(application_window_pop_static_events),
	.events = application_window_pop_static_events,
};

