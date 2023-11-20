#include "app_window_sos.h"
#include "app_window_sos_ui.h"
#include "app_window_sos_layout.h"

/*-----------------------------主流程--------------------------------------*/
static void app_window_sos_init(void *buf)
{
}

static void app_window_sos_load(void *buf)
{
    app_window_sos_ui_show();
}

static void app_window_sos_entry(void *buf)
{
}

static void app_window_sos_exit()
{
}

static void app_window_sos_destroy()
{
}

/*-----------------------------系统配置--------------------------------------*/

static const gui_window_config_struct app_window_sos_config =
    {
        .entry_back_to_destory = 1,
};

const gui_window_struct app_window_sos =
    {
        .screen = &gui_screen_sos,

        .config = &app_window_sos_config,

        .init = app_window_sos_init,
        .load = app_window_sos_load,
        .entry = app_window_sos_entry,
        .exit = app_window_sos_exit,
        .destroy = app_window_sos_destroy,
};
