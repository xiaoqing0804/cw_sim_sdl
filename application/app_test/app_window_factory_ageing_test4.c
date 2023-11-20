
#include "debug_info.h"
#include "picture.h"
#include "language.h"
#include "bsp_includes.h"
#include "app_task_main.h"
#include "data_common.h"

#include "gui_window.h"
#include "gui_surface_box_label.h"

#include "app_window_factory_ageing_test4.h"

static unsigned int g_fact_age4_start_ts;

static short x, y, z;
static unsigned factory_ageing_test_bg_flg = 0;
//
// static const gui_image_struct gui_factory_worker_bg_image =
//{
//	.type = TYPE_GUI_DRAW_PICTURE,
//    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
//	.data = &pic_imb_bg_info,
//};

static const gui_canvas_struct factory_ageing_red[] =
    {
        {
            .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
            .penSize = 5,
            .penColor = COLOR_RGB(255, 0, 0),
            .canvas.rect.x0 = 0,
            .canvas.rect.y0 = 0,
            .canvas.rect.x1 = LCD_SIZE_WIDTH,
            .canvas.rect.y1 = LCD_SIZE_HEIGHT,
        },
};

static const gui_canvas_struct factory_ageing_green[] =
    {
        {
            .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
            .penSize = 5,
            .penColor = COLOR_RGB(0, 255, 0),
            .canvas.rect.x0 = 0,
            .canvas.rect.y0 = 0,
            .canvas.rect.x1 = LCD_SIZE_WIDTH,
            .canvas.rect.y1 = LCD_SIZE_HEIGHT,
        },
};

static const gui_canvas_struct factory_ageing_blue[] =
    {
        {
            .type = TYPE_GUI_DRAW_SHAPE_RECT_FILL,
            .penSize = 5,
            .penColor = COLOR_RGB(0, 0, 255),
            .canvas.rect.x0 = 0,
            .canvas.rect.y0 = 0,
            .canvas.rect.x1 = LCD_SIZE_WIDTH,
            .canvas.rect.y1 = LCD_SIZE_HEIGHT,
        },

};

static const gui_font_struct factory_ageing_num =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_SMALL,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "x:0 y:0 z:0",
};

static const gui_font_struct factory_time_text =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_NUMBER_32,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .width = LCD_SIZE_WIDTH - 240,
        .value.string = "00:00",
};

enum
{
    FACTORY_AGEINE_TEST4_RED = 100,
    FACTORY_AGEINE_TEST4_GREEN,
    FACTORY_AGEINE_TEST4_BLUE,
    FACTORY_AGEINE_TEST4_HR_NUM,
    FACTORY_AGEINE_TEST4_XYZ_NUM,
    FACTORY_AGEINE_TEST4_TIME,
};
static const gui_widget_struct gui_factory_ageing_test_4_widgets[] =
    {
        //    {   // bg
        //        .type = TYPE_GUI_CONTROL_IMAGE,
        //        .width = LCD_SIZE_WIDTH,
        //        .height = LCD_SIZE_HEIGHT,
        //        .scale  = 1.608f,
        //        .visible= 1,
        //        .child_num = 1,
        //        .children = &gui_factory_worker_bg_image,
        //    },

        {
            // RED
            .id = FACTORY_AGEINE_TEST4_RED,
            .type = TYPE_GUI_CONTROL_CANVAS,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 1,
            .child_num = countof(factory_ageing_red),
            .children = &factory_ageing_red,
        },
        {
            // GREEN
            .id = FACTORY_AGEINE_TEST4_GREEN,
            .type = TYPE_GUI_CONTROL_CANVAS,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 0,
            .child_num = countof(factory_ageing_green),
            .children = &factory_ageing_green,
        },
        {
            // BLUE
            .id = FACTORY_AGEINE_TEST4_BLUE,
            .type = TYPE_GUI_CONTROL_CANVAS,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 0,
            .child_num = countof(factory_ageing_blue),
            .children = &factory_ageing_blue,
        },

        {
            // value
            .id = FACTORY_AGEINE_TEST4_HR_NUM,
            .type = TYPE_GUI_CONTROL_LABEL,
            .y = 80,
            .width = LCD_SIZE_WIDTH,
            .height = 30,
            .visible = 1,
            .child_num = 1,
            .children = &factory_ageing_num,
        },
        {
            // value
            .id = FACTORY_AGEINE_TEST4_XYZ_NUM,
            .type = TYPE_GUI_CONTROL_LABEL,
            .y = 130,
            .width = LCD_SIZE_WIDTH,
            .height = 30,
            .visible = 1,
            .child_num = 1,
            .children = &factory_ageing_num,
        },

        {
            // value
            .id = FACTORY_AGEINE_TEST4_TIME,
            .type = TYPE_GUI_CONTROL_LABEL,
            .y = LCD_SIZE_HALF_HEIGHT,
            .width = LCD_SIZE_WIDTH,
            .height = 50,
            .visible = 1,
            .child_num = 1,
            .children = &factory_time_text,
        },

};

const gui_screen_struct gui_screen_factory_ageing_test_4 =
    {
        .children = gui_factory_ageing_test_4_widgets,
        .child_num = countof(gui_factory_ageing_test_4_widgets),
};

void factory_gsensor_xyz(short *data, unsigned int len)
{
    for (unsigned int i = 0; i < len; i += 3)
    {
        x = -data[i + 0];
        y = -data[i + 1];
        z = data[i + 2];
    }
}
static void factory_ageing_test4_bg(void)
{
    gui_box_struct *factory_ageine_test4_red = gui_surface_get_box(&gui_screen_factory_ageing_test_4, (unsigned short)FACTORY_AGEINE_TEST4_RED);
    gui_box_struct *factory_ageine_test4_green = gui_surface_get_box(&gui_screen_factory_ageing_test_4, (unsigned short)FACTORY_AGEINE_TEST4_GREEN);
    gui_box_struct *factory_ageine_test4_blue = gui_surface_get_box(&gui_screen_factory_ageing_test_4, (unsigned short)FACTORY_AGEINE_TEST4_BLUE);
    if (factory_ageing_test_bg_flg == 0)
    {
        factory_ageine_test4_red->visible = 1;
        factory_ageine_test4_green->visible = 0;
        factory_ageine_test4_blue->visible = 0;
    }
    else if (factory_ageing_test_bg_flg == 1)
    {
        factory_ageine_test4_red->visible = 0;
        factory_ageine_test4_green->visible = 1;
        factory_ageine_test4_blue->visible = 0;
    }
    else
    {
        factory_ageine_test4_red->visible = 0;
        factory_ageine_test4_green->visible = 0;
        factory_ageine_test4_blue->visible = 1;
    }
}

static void factory_ageing_test4_num_updata(void)
{
    char temp[20];

    snprintf(temp, sizeof(temp), "hr:%d ", last_hr_result.hr);
    gui_box_struct *HR_NUM = gui_surface_get_box(&gui_screen_factory_ageing_test_4, (unsigned short)FACTORY_AGEINE_TEST4_HR_NUM);
    gui_surface_box_label_change_string(HR_NUM, (unsigned char *)temp);
}

static void factory_ageing_test4_update_time(void)
{
    gui_box_struct *time;
    int h, m, s;
    char temp[32];

    h = g_fact_age4_start_ts / 3600;
    m = (g_fact_age4_start_ts / 60) % 60;
    s = g_fact_age4_start_ts % 60;
    sprintf(temp, "%02d:%02d:%02d", h, m, s);
    time = gui_surface_get_box(&gui_screen_factory_ageing_test_4, (unsigned short)FACTORY_AGEINE_TEST4_TIME);
    if (time != NULL)
        gui_surface_box_label_change_string(time, (unsigned char *)temp);
}

/*-----------------------------系统事件--------------------------------------*/
static void app_window_factory_ageing_test_4_init(void *buf)
{
    g_fact_age4_start_ts = 0;
    hr_set_24H_mode(true);
}

static void app_window_factory_ageing_test_4_load(void *buf)
{
    factory_ageing_test4_num_updata();
    factory_ageing_test4_update_time();
}

static void app_window_factory_ageing_test_4_entry(void *buf)
{
    application_open_act_timer(APPLICATION_TIMER_ACT, 1000);
}

static void app_window_factory_ageing_test_4_exit()
{
    close_motor_msg();
    hr_set_24H_mode(false);
    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_factory_ageing_test_4_destroy()
{
}

static void app_window_factory_ageing_test_4_acttimer_handler(void *buf)
{
    factory_ageing_test_bg_flg++;

    if (factory_ageing_test_bg_flg >= 3)
        factory_ageing_test_bg_flg = 0;

    factory_ageing_test4_bg();
    factory_ageing_test4_num_updata();

    g_fact_age4_start_ts++;
    factory_ageing_test4_update_time();
    gui_surface_commit();

    if (g_fact_age4_start_ts & 0x01)
    {
        send_motor_msg(MOTOR_MSG_MESSAGE);
    }
    else
    {
        close_motor_msg();
    }
}

static void app_window_heartrate_measure_handler(void *buf)
{
    factory_ageing_test4_num_updata();
    gui_surface_commit();
}

static void app_window_fatcory_key1_cancel(void *buf)
{
    application_goto_main();
}

static int ageing_test_4_check(void *param_p)
{
    char temp[20];
    short *xyz = (short *)param_p;

    snprintf(temp, sizeof(temp), "x:%d y:%d z:%d ", xyz[0], xyz[1], xyz[2]);
    gui_box_struct *XYZ_NUM = gui_surface_get_box(&gui_screen_factory_ageing_test_4, (unsigned short)FACTORY_AGEINE_TEST4_XYZ_NUM);
    gui_surface_box_label_change_string(XYZ_NUM, (unsigned char *)temp);

    gui_surface_commit();
}

static void app_window_ageing_test_4_g_sensor_handler(void *buf)
{
    short *xyz = (short *)buf;
    SYS_DEBUG("app: fact_test, gsensor, %d, %d, %d", xyz[0], xyz[1], xyz[2]);
    ageing_test_4_check(buf);
}

/*-----------------------------配置--------------------------------------*/
static const app_window_event_struct app_window_factory_ageing_test_4_static_events[] =
    {
        {.id = EVENT_ACT, .handler = app_window_factory_ageing_test_4_acttimer_handler},
        {.id = EVENT_KEY1_SHORT, .handler = app_window_fatcory_key1_cancel},
        {.id = EVENT_G_SENSOR_DATA, .handler = app_window_ageing_test_4_g_sensor_handler},
        {.id = EVENT_REAL_HEART},
        {.id = EVENT_BL_TIMEOUT},
        {.id = EVENT_GO_HOME},
        {.id = EVENT_ALL},
};

static const gui_touch_event_struct app_window_factory_ageing_test_4_touch_events[] =
    {

};

static const gui_window_config_struct app_window_factory_ageing_test_4_config =
    {
        .entry_back_to_destory = 1,
};

const gui_window_struct app_window_factory_ageing_test_4 =
    {
        .screen = &gui_screen_factory_ageing_test_4,
        .config = &app_window_factory_ageing_test_4_config,

        .init = app_window_factory_ageing_test_4_init,
        .load = app_window_factory_ageing_test_4_load,
        .entry = app_window_factory_ageing_test_4_entry,
        .exit = app_window_factory_ageing_test_4_exit,
        .destroy = app_window_factory_ageing_test_4_destroy,

        .touch_event_num = countof(app_window_factory_ageing_test_4_touch_events),
        .touch_events = app_window_factory_ageing_test_4_touch_events,

        .event_num = countof(app_window_factory_ageing_test_4_static_events),
        .events = app_window_factory_ageing_test_4_static_events,
};
