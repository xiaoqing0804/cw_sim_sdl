#include "app_window_widget.h"
#include "app_window_widget_layout.h"
#include "app_window_widget_ui.h"
#include "config_widget_list.h"
#include "data_widget_list.h"

#include "app_window_widget_delete.h"

/*-----------------------------事件及触屏--------------------------------------*/

static void app_window_widget_click_handler(gui_click_struct *event)
{
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_widget_delete, NULL);
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_widget_init(void *buf)
{
}

static void app_window_widget_load(void *buf)
{
}

static void app_window_widget_entry(void *buf)
{
}

static void app_window_widget_exit()
{
}

static void app_window_widget_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_touch_event_struct app_window_widget_touch_events[] =
    {
        {
            .id = WIDGET_LAYOUT_ID_ADD,
            .click = app_window_widget_click_handler,
        },
};

static const gui_window_config_struct app_window_widget_config =
    {
        .entry_back_to_destory = 1,
};

const gui_window_struct app_window_widget =
    {
        .screen = &gui_widget_screen,
        .config = &app_window_widget_config,

        .init = app_window_widget_init,
        .load = app_window_widget_load,
        .entry = app_window_widget_entry,
        .exit = app_window_widget_exit,
        .destroy = app_window_widget_destroy,

        .touch_event_num = countof(app_window_widget_touch_events),
        .touch_events = app_window_widget_touch_events,
};
