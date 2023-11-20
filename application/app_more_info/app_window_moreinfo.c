
#include "data_common.h"

#include "gui_window_history.h"
#include "gui_window.h"
#include "gui_event_core.h"
#include "gui_surface_layout_matrix.h"

#include "application.h"
#include "application_config.h"
#include "application_touch.h"
#include "application_config_main_window.h"

#include "loop/app_window_moreinfo_loop.h"
#include "ring/app_window_moreinfo_ring.h"
#include "ring/app_window_moreinfo_ring_two.h"
#include "kaleidoscope/app_window_moreinfo_kaleidoscope.h"
#include "matrix/app_window_moreinfo_matrix.h"

extern const gui_window_struct app_window_moreinfo_list;
extern const gui_window_struct app_window_moreinfo_icon_list;
extern const gui_window_struct app_window_moreinfo_ring;
extern const gui_window_struct app_window_moreinfo_cellular;
extern const gui_window_struct app_window_moreinfo_apple_cellular;

static const unsigned char g_moreinfo_style_map[] =
    {
        MOREINFO_WINDOW_STYLE_RING_TWO,
        MOREINFO_WINDOW_STYLE_LIST,
        MOREINFO_WINDOW_STYLE_KALEIDOSCOPE,
        MOREINFO_WINDOW_STYLE_CELL,
        MOREINFO_WINDOW_STYLE_MATRIX,
};

#define C_MOREINFO_STYLE_MAX (sizeof(g_moreinfo_style_map) / sizeof(g_moreinfo_style_map[0]))

static unsigned int g_moreinfo_style_index = 0xFF;

static void app_window_moreinfo_checkinit(void)
{
    unsigned int index;
    if (g_moreinfo_style_index == 0xFF)
    {
        for (index = 0; index < C_MOREINFO_STYLE_MAX; index++)
        {
            if (g_moreinfo_window_style == g_moreinfo_style_map[index])
            {
                g_moreinfo_style_index = index;
                return;
            }
        }
        g_moreinfo_style_index = 0;
        g_moreinfo_window_style = g_moreinfo_style_map[0];
    }
}

const gui_window_struct *app_window_moreinfo_get(void)
{
    const gui_window_struct *window = NULL;

    app_window_moreinfo_checkinit();

    switch (g_moreinfo_window_style)
    {
    // case MOREINFO_WINDOW_STYLE_RING:
    //     window = &app_window_moreinfo_ring;
    //     break;
    case MOREINFO_WINDOW_STYLE_LOOP:
        window = &app_window_moreinfo_loop;
        break;
    case MOREINFO_WINDOW_STYLE_CELL:
        window = &app_window_moreinfo_apple_cellular;
        break;
    case MOREINFO_WINDOW_STYLE_RING_TWO:
        window = &app_window_moreinfo_ring_two;
        break;
    case MOREINFO_WINDOW_STYLE_KALEIDOSCOPE:
        window = &app_window_moreinfo_kaleidoscope;
        break;
    case MOREINFO_WINDOW_STYLE_MATRIX:
        window = &app_window_moreinfo_matrix;
        break;
    case MOREINFO_WINDOW_STYLE_LIST:
    default:
        g_moreinfo_window_style = MOREINFO_WINDOW_STYLE_LIST;
        window = &app_window_moreinfo_list;
        break;
    }

    return window;
}

void app_window_moreinfo_enter(void *buf)
{
    const gui_window_struct *window = app_window_moreinfo_get();
    if (window != NULL)
    {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, window, buf);
    }
}

void app_window_moreinfo_change(void)
{
    const gui_window_struct *window1 = app_window_moreinfo_get();
    if (window1 != gui_window_history_get_top_window())
    {
        GUI_DEBUG("app: change_moreinfo_window(NULL)");
        return;
    }

    application_add_moreinfo_tyep();
    GUI_DEBUG("app: change_moreinfo_window(%d)", g_moreinfo_window_style);

    const gui_window_struct *window2 = app_window_moreinfo_get();
    if (window2 != NULL)
    {
        application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, window2, NULL);
    }
}

int app_window_moreinfo_get_index(unsigned char style)
{
    for (short i = 0; i < countof(g_moreinfo_style_map); i++)
    {
        if (style == g_moreinfo_style_map[i])
            return i;
    }
    return 0;
}

unsigned char app_window_moreinfo_get_style(unsigned char index)
{
    index = math_range(index, 0, countof(g_moreinfo_style_map) - 1);
    return g_moreinfo_style_map[index];
}

void app_window_moreinfo_set(unsigned char style)
{
    const gui_window_struct *window = app_window_moreinfo_get();
    gui_window_history_remove_window(window);

    g_moreinfo_window_style = style;
    g_moreinfo_style_index = app_window_moreinfo_get_index(style);
}

int application_get_moreinfo_tyep(void)
{
    app_window_moreinfo_checkinit();
    return g_moreinfo_window_style;
}

int application_add_moreinfo_tyep(void)
{
    app_window_moreinfo_checkinit();

    g_moreinfo_style_index++;
    if (g_moreinfo_style_index >= C_MOREINFO_STYLE_MAX)
    {
        g_moreinfo_style_index = 0;
    }
    g_moreinfo_window_style = g_moreinfo_style_map[g_moreinfo_style_index];
    return g_moreinfo_window_style;
}
