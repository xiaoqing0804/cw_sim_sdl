#include "app_window_sound_touch.h"
#include "app_window_sound_touch_ui.h"
#include "app_window_sound_touch_layout.h"
#include "application_config_app_info.h"
#include "ams.h"
#include "bsp_includes.h"

/*-----------------------------本地逻辑处理--------------------------------------*/

static void app_window_set_volume(unsigned int inc_vol)
{
    if (get_ble_connect_flag() == 0)
        return;
    MUSIC_CMD_TYPE cmd = ((inc_vol) ? MUSIC_CMD_VOLUME_UP : MUSIC_CMD_VOLUME_DOWN);
    Phone_music_control_handler(cmd);
}

static void app_window_sound_touch_click_on_sound(short x, short y)
{
    if (app_window_sound_touch_ui_is_touch_on_sound_low(x, y))
    {
        app_window_set_volume(0);
    }
    else if (app_window_sound_touch_ui_is_touch_on_sound_high(x, y))
    {
        app_window_set_volume(1);
    }
    send_motor_msg(MOTOR_MSG_SLIGHT_VIBRATE);
    app_window_sound_touch_ui_show_sound();
    gui_surface_commit();
}

static void app_window_sound_touch_click_on_vibration(short x, short y)
{
    if (app_window_sound_touch_ui_is_touch_on_vibration_button(x, y))
    {
        bsp_set_touch_motor_msg(!bsp_get_touch_motor_onoff());
    }
    else if (app_window_sound_touch_ui_is_touch_on_vibration_check_1(x, y))
    {
        if (bsp_get_touch_motor_onoff())
        {
            bsp_set_touch_motor_grade_msg(0);
        }
    }
    else if (app_window_sound_touch_ui_is_touch_on_vibration_check_2(x, y))
    {
        if (bsp_get_touch_motor_onoff())
        {
            bsp_set_touch_motor_grade_msg(1);
        }
    }
    app_window_sound_touch_ui_show_touch();
    gui_surface_commit();
}

/*-----------------------------事件及触屏--------------------------------------*/
static void app_window_sound_touch_click_on_layout_item(gui_click_layout_struct *event)
{
    if (event->id == SOUND_TOUCH_LAYOUT_ID_SOUND)
    {
        if (get_ble_connect_flag() > 0)
        {
            app_window_sound_touch_click_on_sound(event->x_in_item, event->y_in_item);
        }
    }
    else if (event->id == SOUND_TOUCH_LAYOUT_ID_TOUCH)
    {
        app_window_sound_touch_click_on_vibration(event->x_in_item, event->y_in_item);
    }
}

static void app_window_update_vol(void *buf)
{
    app_window_sound_touch_ui_show_sound();
    gui_surface_commit();
}

static void app_window_sound_touch_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_sound_touch);

    if (rolkey->rotate == ROTATE_TYPE_FORWARD)
    {
        gui_surface_layout_listview_switch_to_item(surface, DIRECTION_TYPE_DOWN);
    }
    else if (rolkey->rotate == ROTATE_TYPE_BACKWARD)
    {
        gui_surface_layout_listview_switch_to_item(surface, DIRECTION_TYPE_UP);
    }
    gui_surface_commit();
}

/*-----------------------------主流程--------------------------------------*/

static void app_window_sound_touch_init(void *buf)
{
}

static void app_window_sound_touch_load(void *buf)
{
    app_window_sound_touch_ui_show();
}

static void app_window_sound_touch_entry(void *buf)
{
}

static void app_window_sound_touch_exit()
{
}

static void app_window_sound_touch_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/
static const app_window_event_struct app_window_sound_touch_events[] =
    {
        {
            .id = EVENT_ROLKEY,
            .handler = app_window_sound_touch_rolkey_handler,
        },
};

static const app_window_event_struct app_window_sound_events[] =
    {
        {
            EVENT_AMS_VOLUME_IND,
            app_window_update_vol,
        },
        {
            EVENT_AMS_CMD_IND,
            app_window_update_vol,
        },
};

const gui_window_struct app_window_sound_touch =
    {
        .screen = &gui_screen_sound_touch,

        .init = app_window_sound_touch_init,
        .load = app_window_sound_touch_load,
        .entry = app_window_sound_touch_entry,
        .exit = app_window_sound_touch_exit,
        .destroy = app_window_sound_touch_destroy,

        .click_on_layout_item = app_window_sound_touch_click_on_layout_item,

        .event_num = countof(app_window_sound_touch_events),
        .events = app_window_sound_touch_events,

        .event_num = countof(app_window_sound_events),
        .events = app_window_sound_events,
};
