#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "app_task_main.h"

#include "application_titlebar.h"

#include "app_window_message_info.h"
#include "app_window_message_delete_all.h"

#include "app_window_message_list.h"
#include "app_window_message_list_ui.h"
#include "app_window_message_list_layout.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
static void app_window_message_list_init(void *buf)
{
    app_window_message_list_ui_init();
}

static void app_window_message_list_load(void *buf)
{
    app_window_message_list_ui_update();

    application_titlebar_create(&gui_screen_message_list, STRING_MESSAGE);
    application_titlebar_hide_bg_from_screen(&gui_screen_message_list);
}

static void app_window_message_list_entry(void *buf)
{
    application_titlebar_show_bg_from_screen(&gui_screen_message_list);
}

static void app_window_message_list_exit()
{
}

static void app_window_message_list_destroy()
{
}

/*-----------------------------响应事件--------------------------------------*/
static void app_window_message_list_event_handler(void *buf)
{
    app_window_message_list_ui_update();
    gui_surface_commit();
}

static void app_window_message_list_key_handler(void *buf)
{
    application_go_back();
}

static unsigned char app_window_message_list_event_touch(gui_touch_struct *envent)
{
    return app_window_message_list_ui_touch(envent);
}

static void app_window_message_list_delect_click(gui_click_struct *event)
{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_message_delete_all, (void *)25);
}

static void app_window_message_list_delect_one_click(gui_click_struct *event)
{
    app_window_message_list_ui_delect_one(event);
}

static void app_window_message_list_click_on_layout_item(gui_click_layout_struct *event)
{
    unsigned int msg_index = event->id - MSG_ITEM_BOX_BASE_ID;
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_message_info, (void *)msg_index);
}

static void app_window_message_list_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_message_list);

    if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
    {
        gui_surface_layout_scrollview_switch_to_direction(surface, DIRECTION_TYPE_UP);
    }
    else if (rolkey->rotate == ROTATE_TYPE_FORWARD)
    {
        gui_surface_layout_scrollview_switch_to_direction(surface, DIRECTION_TYPE_DOWN);
    }

    gui_surface_commit();
}

static void app_window_message_list_swipe_start_handler(void *buf)
{
    application_titlebar_hide_bg_from_screen(&gui_screen_message_list);
    gui_surface_commit();
}

static void app_window_message_list_swipe_end_handler(void *buf)
{
    application_titlebar_show_bg_from_screen(&gui_screen_message_list);
    gui_surface_commit();
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_message_list_event_map[] =
    {
        {
            .id = EVENT_MESSAGE,
            .handler = app_window_message_list_event_handler,
        },
        {
            .id = EVENT_KEY1_SHORT,
            .handler = app_window_message_list_key_handler,
        },
        {
            .id = EVENT_ROLKEY,
            .handler = app_window_message_list_rolkey_handler,
        },
        {
            .id = EVENT_SWIPE_START,
            .handler = app_window_message_list_swipe_start_handler,
        },
        {
            .id = EVENT_SWIPE_END,
            .handler = app_window_message_list_swipe_end_handler,
        },
};

static const gui_touch_event_struct app_window_message_list_touch_events[] =
    {
        {
            .id = APP_MESSAGE_CV_LIST_DELECT,
            .click = app_window_message_list_delect_click,
        },
        {
            .id = APP_MESSAGE_CV_LIST_DELECT_ONE,
            .click = app_window_message_list_delect_one_click,
        },
        {
            .id = 0xFFFF,
            .touch = app_window_message_list_event_touch,
        },
};

const gui_window_struct app_window_message_list =
    {
        .screen = &gui_screen_message_list,

        .init = app_window_message_list_init,
        .load = app_window_message_list_load,
        .entry = app_window_message_list_entry,
        .exit = app_window_message_list_exit,
        .destroy = app_window_message_list_destroy,

        .click_on_layout_item = app_window_message_list_click_on_layout_item,

        .touch_event_num = countof(app_window_message_list_touch_events),
        .touch_events = app_window_message_list_touch_events,

        .event_num = countof(app_window_message_list_event_map),
        .events = app_window_message_list_event_map,
};
