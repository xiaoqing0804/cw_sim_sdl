#include "debug_info.h"
#include "app_window_sport_data.h"
#include "app_window_sport_data_exit.h"

#include "app_widget/app_window_widget_delete.h"
#include "app_window_sportlist_bg.h"

#include "application_titlebar.h"

#include "gui_surface_layout_listview.h"

#include "data_common.h"
#include "gui_surface_cache.h"
#include "gui_surface_box_layout_item.h"

#define SPORT_ITEM_ROW_WIDTH (482)
#define SPORT_ITEM_ROW_HEIGHT (190)

static const sport_window_item_struct g_sport_window_list_info[] =
    {
        {
            .string = STRING_SPORT_RUN,
            .id = MIX_SPORT_RUN,
            .bg = {
                &pic_sportlist_bg_1_001_info,
                &pic_sportlist_bg_1_002_info,
            },
            .ani = {
                &pic_detailed_run_1_info,
                &pic_detailed_run_2_info,
                &pic_detailed_run_3_info,
            },
        },
        {
            .string = STRING_SPORT_WALK,
            .id = MIX_SPORT_WALK,
            .bg = {
                &pic_sportlist_bg_2_001_info,
                &pic_sportlist_bg_2_002_info,
            },
            .ani = {
                &pic_detailed_walk_1_info,
                &pic_detailed_walk_2_info,
                &pic_detailed_walk_3_info,
            },
        },
        {
            .string = STRING_SPORT_CYCLING,
            .id = MIX_SPORT_CYCLING,
            .bg = {
                &pic_sportlist_bg_3_001_info,
                &pic_sportlist_bg_3_002_info,
            },
            .ani = {
                &pic_detailed_cycling_1_info,
                &pic_detailed_cycling_2_info,
                &pic_detailed_cycling_3_info,
            },
        },
        {
            .string = STRING_SPORT_CLIMB,
            .id = MIX_SPORT_CLIMBING,
            .bg = {
                &pic_sportlist_bg_4_001_info,
                &pic_sportlist_bg_4_002_info,
            },
            .ani = {
                &pic_detailed_climbing_1_info,
                &pic_detailed_climbing_2_info,
                &pic_detailed_climbing_3_info,
            },
        },
        {
            .string = STRING_TREADMILL,
            .id = MIX_SPORT_RUNNING_MACHINE,
            .bg = {
                &pic_sportlist_bg_5_001_info,
                &pic_sportlist_bg_5_002_info,
            },
            .ani = {
                &pic_detailed_running_machine_1_info,
                &pic_detailed_running_machine_2_info,
                &pic_detailed_running_machine_3_info,
            },
        },
        {
            .string = STRING_SPORT_BASKETBALL,
            .id = MIX_SPORT_BASKETBALL,
            .bg = {
                &pic_sportlist_bg_6_001_info,
                &pic_sportlist_bg_6_002_info,
            },
            .ani = {
                &pic_detailed_basketball_1_info,
                &pic_detailed_basketball_2_info,
                &pic_detailed_basketball_3_info,
            },
        },
        {
            .string = STRING_SPORT_FOOTBALL,
            .id = MIX_SPORT_FOOTBALL,
            .bg = {
                &pic_sportlist_bg_7_001_info,
                &pic_sportlist_bg_7_002_info,
            },
            .ani = {
                &pic_detailed_football_1_info,
                &pic_detailed_football_2_info,
                &pic_detailed_football_3_info,
            },
        },
        {
            .string = STRING_SPORT_BADMINTON,
            .id = MIX_SPORT_BADMINTON,
            .bg = {
                &pic_sportlist_bg_8_001_info,
                &pic_sportlist_bg_8_002_info,
            },
            .ani = {
                &pic_detailed_badminton_1_info,
                &pic_detailed_badminton_2_info,
                &pic_detailed_badminton_3_info,
            },
        },
        {
            .string = STRING_SPORT_SKIP,
            .id = MIX_SPORT_SKIP,
            .bg = {
                &pic_sportlist_bg_9_001_info,
                &pic_sportlist_bg_9_002_info,
            },
            .ani = {
                &pic_detailed_skip_1_info,
                &pic_detailed_skip_2_info,
                &pic_detailed_skip_3_info,
            },
        },
        {
            .string = STRING_CYCLING_INDOOR,
            .id = MIX_SPORT_CYCLING_INDOOR,
            .bg = {
                &pic_sportlist_bg_10_001_info,
                &pic_sportlist_bg_10_002_info,
            },
            .ani = {
                &pic_detailed_cycling_indoor_1_info,
                &pic_detailed_cycling_indoor_2_info,
                &pic_detailed_cycling_indoor_3_info,
            },
        },
};

static const int SPORT_LIST_NUM = sizeof(g_sport_window_list_info) / sizeof(g_sport_window_list_info[0]);

static unsigned int sport_list_get_count(void)
{
    return SPORT_LIST_NUM;
}

STRING_ID_TYPE sport_list_get_string(MIX_SPORT_TYPE id)
{
    for (short i = 0; i < SPORT_LIST_NUM; i++)
    {
        if (id == g_sport_window_list_info[i].id)
        {
            return g_sport_window_list_info[i].string;
        }
    }
    return 0;
}

picture_info_struct *sport_list_get_detailed_pic(MIX_SPORT_TYPE id)
{
    for (short i = 0; i < SPORT_LIST_NUM; i++)
    {
        if (id == g_sport_window_list_info[i].id)
        {
            return g_sport_window_list_info[i].ani[0];
        }
    }
    return 0;
}

sport_window_item_struct *sport_list_get_item_by_index(short index)
{
    if (index < 0)
        index = 0;
    if (index >= SPORT_LIST_NUM)
        index = SPORT_LIST_NUM - 1;
    return &g_sport_window_list_info[index];
}

sport_window_item_struct *sport_list_get_item(MIX_SPORT_TYPE id)
{
    for (short i = 0; i < SPORT_LIST_NUM; i++)
    {
        if (id == g_sport_window_list_info[i].id)
        {
            return &g_sport_window_list_info[i];
        }
    }
    return 0;
}

static unsigned char g_sport_window_list_ani_count = 0;
typedef enum
{
    SPORT_BG_LAYOUT_ID_NONE = 0,
    SPORT_BG_LAYOUT_ID_ANI_PEOPLE,
};

static const gui_layout_list_struct gui_window_sport_list_layout =
    {
        .row_height = SPORT_ITEM_ROW_HEIGHT,

        .top = -60,
        .bottom = 138,
        .space = 4,
        .scroll = 1,
        .auto_start = 1,

        .zoom_flag = 1,
        .zoom_radius = LCD_SIZE_HEIGHT,
        .zoom_scale = 1.0f,
};

static const gui_screen_struct gui_screen_sportlist =
    {
        .type = TYPE_GUI_LAYOUT_LIST,
        .space_x = 0,
        .space_y = 0,
        .order = 0,
        .layout_config = &gui_window_sport_list_layout,
};

gui_image_struct gui_pic_sport_dance =
    {
        .id = SPORT_BG_LAYOUT_ID_ANI_PEOPLE,
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 58,
        .y = 10,
        //	.anchor_x = 0,
        //	.anchor_y = 0,
        //	.data = &pic_dance_info,
};

gui_image_struct gui_pic_sport_dance_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        //	.anchor_x = 0,
        //	.anchor_y = 0,
        .data = NULL,

};
gui_image_struct gui_pic_sport_dance_bg_1 =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = SPORT_ITEM_ROW_WIDTH / 2,
        //	.anchor_x = 0,
        //	.anchor_y = 0,
        .data = NULL,

};

static gui_font_struct gui_text_sport_dance =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = 75,
        .y = 128,
        .anchor_x = 0,
        .anchor_y = 0,
        .max_width = 0,
        .width = 300,
        .height = 22,
        // .align = GUI_ALIGN_VCENTER,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT, GUI_ALIGN_NONE),
        .auto_wrap = 0,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_SPORT_RUN,
};

static const gui_mix_struct gui_item_dance[] =
    {
        {
            .data = &gui_pic_sport_dance_bg,
        },
        {
            .data = &gui_pic_sport_dance_bg_1,
        },

        {
            .data = &gui_pic_sport_dance,
        },
        {
            .data = &gui_text_sport_dance,
        },

};

static gui_widget_struct gui_sport_info =
    {
        .id = 0,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = SPORT_ITEM_ROW_WIDTH,
        .height = SPORT_ITEM_ROW_HEIGHT,
        .anchor_x = ANCHOR_VALUE(0.5f),
        .anchor_y = ANCHOR_VALUE(0.5f),
        .x = -8,
        .visible = 1,
        .child_num = countof(gui_item_dance),
        .children = gui_item_dance,
};

static gui_font_struct gui_text_sport_title =
    {
        .id = STRING_SPORT,
        .type = TYPE_GUI_DRAW_TEXT,
        .x = 0,
        .y = 60,
        .width = LCD_SIZE_WIDTH,
        .height = SPORT_ITEM_ROW_HEIGHT - 60,
        .align = GUI_ALIGN_VCENTER,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_SPORT,
};
static const gui_mix_struct gui_item_title[] =
    {
        {
            .data = &gui_text_sport_title,
        },
};
static const gui_widget_struct gui_sport_title_info =
    {
        .id = STRING_SPORT,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = SPORT_ITEM_ROW_HEIGHT,
        .anchor_x = ANCHOR_VALUE(0.5f),
        .anchor_y = ANCHOR_VALUE(0.5f),
        .visible = 1,
        .child_num = 1,
        .children = gui_item_title,
};

/*-----------------------------系统事件--------------------------------------*/

static void app_sport_list_refresh()
{
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_sportlist);
    if (surface != NULL)
    {
        unsigned int box_num = sport_list_get_count();
        gui_surface_layout_listview_dynamic_init(surface);

        gui_box_struct *box = gui_surface_layout_listview_dynamic_get_box(surface, STRING_SPORT); // gui_surface_cache_add_box();
        if (box != NULL)
        {
            box->id = STRING_SPORT;
            box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
            box->widget = &gui_sport_title_info;
            box->x = gui_sport_title_info.x;
            box->y = gui_sport_title_info.y;
            box->width = gui_sport_title_info.width;
            box->height = gui_sport_title_info.height;
            box->visible = 1;
            gui_surface_layout_listview_dynamic_add_item(surface, box);
        }

        sport_window_item_struct *item = NULL;
        for (short box_idx = 0; box_idx < box_num; box_idx++)
        {
            item = sport_list_get_item_by_index(box_idx);
            box = gui_surface_layout_listview_dynamic_get_box(surface, item->id);
            if (box != NULL)
            {
                box->id = item->id;
                box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
                box->widget = &gui_sport_info;
                box->visible = 1;
                box->x = gui_sport_info.x;
                box->y = gui_sport_info.y;
                box->width = gui_sport_info.width;
                box->height = gui_sport_info.height;
                // set icons
                gui_pic_sport_dance_bg.data = item->bg[0];
                gui_pic_sport_dance_bg_1.data = item->bg[1];
                gui_pic_sport_dance.data = item->ani[g_sport_window_list_ani_count];
                gui_text_sport_dance.value.string_id = item->string;

                gui_surface_box_layout_item_change_image(box, SPORT_BG_LAYOUT_ID_ANI_PEOPLE, item->ani[g_sport_window_list_ani_count]);
                gui_surface_layout_listview_dynamic_add_item(surface, box);
            }
        }
        gui_surface_layout_listview_dynamic_finish(surface);
    }
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_sport_list_init(void *buf)
{
}

static void app_window_sport_list_load(void *buf)
{
    // application_titlebar_create(&gui_screen_sportlist,STRING_SPORT);
    //  application_titlebar_create_color(&gui_screen_sportlist, STRING_SPORT, COLOR_RGB(0, 220, 128));
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_sportlist);
    gui_surface_layout_listview_dynamic_create(surface, app_sport_list_refresh);
}

static void app_window_sport_list_entry(void *buf)
{
    application_open_act_timer(APPLICATION_TIMER_ACT, 300);
}

static void app_window_sport_list_exit()
{
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_sport_list_destroy()
{
}

/*-----------------------------响应事件--------------------------------------*/

static void app_window_sport_list_acttimer_handler(void *buf)
{
    // application_close_act_timer(APPLICATION_TIMER_ACT);

    g_sport_window_list_ani_count++;
    if (g_sport_window_list_ani_count >= SPORT_ITEM_ANI_COUNT)
        g_sport_window_list_ani_count = 0;

    app_sport_list_refresh();
    gui_surface_force_update();

    // application_open_act_timer(APPLICATION_TIMER_ACT, 300);
}

static void app_window_sport_list_touch_event_click_on_layout_item(gui_click_layout_struct *event)
{
    save_sport_type = (MIX_SPORT_TYPE)event->id;
    //sport_status_set(SPORT_STATUS_START);
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_sport_data, NULL);
}

static void app_window_sport_list_view_rolkey_handler(void *buf)
{
    rolkey_event_struct *rolkey = (rolkey_event_struct *)buf;
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_sportlist);

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

static unsigned char app_window_sport_list_event_touch(gui_touch_struct *envent)
{
    if (envent->type == TOUCH_EVENT_TYPE_UP)
    {
        if (envent->direction == DIRECTION_TYPE_LEFT)
        {
            application_go_back();
        }
        return 1;
    }
    else if (envent->type == TOUCH_EVENT_TYPE_DOWN)
    {
        return 1;
    }
    else if (envent->type == TOUCH_EVENT_TYPE_MOVE)
    {
        return 1;
    }
    return 0;
}

/*-----------------------------配置--------------------------------------*/

static const app_window_event_struct app_window_sport_list_events[] =
    {
        {
            .id = EVENT_ACT,
            .handler = app_window_sport_list_acttimer_handler,
        },
        {
            .id = EVENT_ROLKEY,
            .handler = app_window_sport_list_view_rolkey_handler,
        },
};

static const gui_touch_event_struct app_window_sport_list_touch_events[] =
    {
        {
            .id = 0xFFFF,
            .touch = app_window_sport_list_event_touch,
        },
};

const gui_window_struct app_window_sport =
    {
        .screen = &gui_screen_sportlist,

        .init = app_window_sport_list_init,
        .load = app_window_sport_list_load,
        .entry = app_window_sport_list_entry,
        .exit = app_window_sport_list_exit,
        .destroy = app_window_sport_list_destroy,

        /*排版界面上响应点击事件*/
        .click_on_layout_item = app_window_sport_list_touch_event_click_on_layout_item,

        .touch_event_num = countof(app_window_sport_list_touch_events),
        .touch_events = app_window_sport_list_touch_events,

        .event_num = countof(app_window_sport_list_events),
        .events = app_window_sport_list_events,
};
