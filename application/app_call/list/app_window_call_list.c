
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"

#include "data_common.h"
#include "data_manager_user_info.h"
#include "data_receive_package.h"

#ifdef __PHONE_BOOK_SYNC_SUPPORTED__
#include "data_manager_contact.h"
#endif

#include "gui_drivers_display.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "gui_surface_control_base.h"

#include "application_config_main_window.h"

#include "app_widget/app_window_widget_delete.h"

#include "app_call/app_window_call.h"

#include "app_window_call_list_layout.h"
#include "app_window_call_list.h"


/*-----------------------------主流程--------------------------------------*/
static void app_window_call_list_init(void *buf)
{
    ext_btaud_onoff_set(1);
}

static void app_window_call_list_load(void *buf)
{
    application_titlebar_create(&app_call_list_screen, STRING_TELEPHONE);
    application_titlebar_hide_bg_from_screen(&app_call_list_screen);
}

static void app_window_call_list_entry(void *buf)
{
}

static void app_window_call_list_exit()
{
}

static void app_window_call_list_destroy(void)
{
}

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_call_book_click_handler(gui_click_struct *click)
{
#if defined(__EXT_BT_AUDIO__)
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_call_phonebook, NULL);
#endif
}
static void app_window_call_clog_click_handler(gui_click_struct *click)
{
#if defined(__EXT_BT_AUDIO__)
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_call_clog, NULL);
#endif
}

static void app_window_call_dial_click_handler(gui_click_struct *click)
{
#if defined(__EXT_BT_AUDIO__)
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_call_dial, NULL);
#endif
}
static void app_window_call_onoff_click_handler(gui_click_struct *click)
{
#if defined(__EXT_BT_AUDIO__)
    //application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_call_onoff, NULL);
#endif
}

static void app_window_call_list_long_touch_handler(gui_click_struct *event)
{
    if (is_exist_widget_app(APP_INFO_ID_CALL))
    {
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void *)APP_INFO_ID_CALL);
    }
}

/*-----------------------------系统配置--------------------------------------*/
static const gui_touch_event_struct app_window_call_list_touch_events[] =
    {

        {
            .id = CALL_BOOK_IND_ID,
            .click = app_window_call_book_click_handler,

        },
        {
            .id = CALL_CLOG_IND_ID,
            .click = app_window_call_clog_click_handler,

        },
        {
            .id = CALL_DAIL_IND_ID,
            .click = app_window_call_dial_click_handler,

        },
        {
            .id = 0xFFFF,
            .long_touch = app_window_call_list_long_touch_handler,
        },

};

const gui_window_struct app_window_call_list =
    {
        .screen = &app_call_list_screen,

        .init = app_window_call_list_init,
        .load = app_window_call_list_load,
        .entry = app_window_call_list_entry,
        .exit = app_window_call_list_exit,
        .destroy = app_window_call_list_destroy,

        .touch_event_num = countof(app_window_call_list_touch_events),
        .touch_events = app_window_call_list_touch_events,

};
