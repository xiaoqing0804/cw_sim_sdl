#include "picture.h"
#include "language.h"

#include "data_message.h"

#include "gui_window.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"

#include "app_window_message_list.h"
#include "app_window_message_list_layout.h"

#include "app_window_message_delete_all.h"
#include "app_window_message_delete_all_layout.h"

static unsigned char delete_messg_index = 0;

/*-----------------------------主流程--------------------------------------*/
static void app_window_message_delete_all_init(void *buf)
{
    unsigned int index = (unsigned int)buf;
    delete_messg_index = index;
}

static void app_window_message_delete_all_load(void *buf)
{
    gui_box_struct *box;
    box = gui_surface_get_box(&gui_message_delete_all_screen, 0);
    if (delete_messg_index > 4)
    {
        gui_surface_box_label_change_string_id(box, STRING_CLEAR_ALL);
    }
    else
    {
        gui_surface_box_label_change_string_id(box, STRING_DELETE_THIS_MSG);
    }
}

static void app_window_message_delete_all_entry(void *buf)
{
}

static void app_window_message_delete_all_exit()
{
}

static void app_window_message_delete_all_destroy()
{
}
/*-----------------------------响应事件--------------------------------------*/
static void app_window_message_delete_all_touch_event_click_cancel(gui_click_struct *event)
{
    //	application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_message_list, NULL);
    application_go_back();
}

static void app_window_message_delete_all_touch_event_click_ok(gui_click_struct *event)
{

    if (delete_messg_index > 4)
    {
        data_message_delete_all();
    }
    else
    {
        data_message_delete(delete_messg_index);
    }
    application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_message_list, NULL);
}

/*-----------------------------系统配置--------------------------------------*/
static const gui_touch_event_struct app_window_message_delete_all_touch_events[] =
    {
        {.id = APP_MESSAGE_DEL_CANCEL,       .click = app_window_message_delete_all_touch_event_click_cancel    },
        {.id = APP_MESSAGE_DEL_OK,           .click = app_window_message_delete_all_touch_event_click_ok        },
};

const gui_window_struct app_window_message_delete_all =
    {
        .screen = &gui_message_delete_all_screen,

        .init = app_window_message_delete_all_init,
        .load = app_window_message_delete_all_load,
        .entry = app_window_message_delete_all_entry,
        .exit = app_window_message_delete_all_exit,
        .destroy = app_window_message_delete_all_destroy,

        .touch_event_num = countof(app_window_message_delete_all_touch_events),
        .touch_events = app_window_message_delete_all_touch_events,
};
