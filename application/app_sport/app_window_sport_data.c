#include "debug_info.h"
#include "bsp_includes.h"

#include "data_common.h"
#include "arithmetic_common.h"
#include "arithmetic_mix_sport.h"
#include "sys_timer.h"

#include "gui_surface_box_label.h"

#include "application.h"

#include "app_window_sport_data.h"
#include "app_window_sport_data_layout.h"
#include "app_window_sport_data_exit.h"
#include "app_window_sport_data.h"
#include "app_window_sport_data_layout.h"

static unsigned int g_ready_timer_hd;

static void app_window_sport_data_update(void);

static const picture_info_struct *const sport_ready_count[] = {
    &pic_spor_ready_3_info,
    &pic_spor_ready_2_info,
    &pic_spor_ready_1_info,
    &pic_spor_ready_0_info,
};

static unsigned int m_sport_time = 0;
static unsigned int m_sport_time_base = 0;
static mix_sport_struct mix_sport_result = {0};
static unsigned int m_temp_time = 0;
static unsigned char m_window_sport_status = 0;
static unsigned char m_window_type;  // 0: walk;  1: football; 2: swim
static unsigned char logo_cnt = 0;   // 0-3
static unsigned char ready_flag = 0; // 0 锛歯o ready , 1 : ready

MIX_SPORT_TYPE save_sport_type;

static void app_window_sport_data_time_static_event_act(void *buf);

mix_sport_struct *get_mix_sport_result_info(void)
{
    return &mix_sport_result;
}

unsigned int sport_time_get(void)
{
    unsigned int value = 0;

    if (0 == m_sport_time)
    {
        value = m_sport_time_base;
        if ((SPORT_STATUS_START == m_window_sport_status) ||
            (SPORT_STATUS_CONTINUE == m_window_sport_status))
        {
            m_sport_time = HAL_GetTickMS();
        }
    }
    else
    {
        value = (HAL_GetTickMS() - m_sport_time) + m_sport_time_base;
    }

    return value;
}

void sport_status_set(SPORT_STATUS_TYPE type)
{
    if ((MIX_SPORT_WALK == save_sport_type) || (MIX_SPORT_RUN == save_sport_type) || (MIX_SPORT_CLIMBING == save_sport_type))
    {
        m_window_type = 0;
    }
    else if ((MIX_SPORT_FOOTBALL == save_sport_type) || (MIX_SPORT_BASKETBALL == save_sport_type) || (MIX_SPORT_BADMINTON == save_sport_type))
    {
        m_window_type = 1;
    }
    else if ((MIX_SPORT_SWIM == save_sport_type) || (MIX_SPORT_CYCLING == save_sport_type) || (MIX_SPORT_CYCLING_INDOOR == save_sport_type)|| (MIX_SPORT_YOGA == save_sport_type) || (MIX_SPORT_SKIP == save_sport_type) || (save_sport_type >= 30))
    {
        m_window_type = 2;
    }
    else//没有指定的类型均只显示 卡路里和心率
    {
        m_window_type = 2;
    }

    SYS_DEBUG("sport_status_set =%d", m_window_type);
    m_window_sport_status = type;

    if (SPORT_STATUS_START == type)
    {
        m_sport_time = HAL_GetTickMS();
        m_sport_time_base = 0;
        mix_sport_start(save_sport_type);
    }
    else if (SPORT_STATUS_PAUSE == type)
    {
        m_sport_time_base = sport_time_get();
        m_sport_time = 0;
        mix_sport_pause();
    }
    else if (SPORT_STATUS_CONTINUE == type)
    {
        m_sport_time_base = sport_time_get();
        m_sport_time = HAL_GetTickMS();
        mix_sport_continue();
    }
    else // if(SPORT_STATUS_STOP == type)
    {
        m_sport_time_base = sport_time_get();
        m_sport_time = 0;
        memcpy(get_mix_sport_result_info(), get_mix_sport_info(), sizeof(mix_sport_struct));
        mix_sport_stop();
    }
}
/*-----------------------------????-----------------------------------*/

static void app_window_sport_ready_init(void)
{
    gui_box_struct *box;
    unsigned int index = 0;
    while (1)
    {
        box = gui_surface_get_box_by_index(&gui_screen_sport_data, index);
        if (box == NULL)
        {
            break;
        }
        if (box->id < SPORT_DATA_LAYOUT_ID_READY_BASE)
        {
            gui_surface_box_change_visible(box, 0);
        }
        index++;
    }
}

static void app_window_sport_ready_run(void)
{
    char temp[40];
    unsigned int sec;
    gui_box_struct *box;

    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_READY_NUMBER);
    if (box == NULL)
        return;
    if (logo_cnt < 4)
        gui_surface_box_image_change(box, (const picture_info_struct *)sport_ready_count[logo_cnt]);

    logo_cnt++;
    if (logo_cnt >= 5)
    {
        ready_flag = 1;
        sport_status_set(SPORT_STATUS_START);
        app_window_sport_data_update();
        m_sport_time = 0;
        return;
    }
}

/*-----------------------------????-------------------------------------*/
static void app_window_sport_data_update(void)
{
    gui_box_struct *box;
    unsigned int index = 0;

    if (SPORT_STATUS_PAUSE == m_window_sport_status)
    {
        while (1)
        {
            box = gui_surface_get_box_by_index(&gui_screen_sport_data, index);
            if (box == NULL)
            {
                break;
            }
            if ((box->id < SPORT_DATA_LAYOUT_ID_PAUSE_BASE) || (box->id > SPORT_DATA_LAYOUT_ID_READY_BASE))
            {
                gui_surface_box_change_visible(box, 0);
            }
            else
            {
                gui_surface_box_change_visible(box, 1);
            }
            index++;
        }
    }
    else
    {
        SYS_DEBUG("app_window_sport_data_update m_window_type=%d", m_window_type);

        while (1)
        {
            box = gui_surface_get_box_by_index(&gui_screen_sport_data, index);
            if (box == NULL)
            {
                break;
            }
            if ((box->id < SPORT_DATA_LAYOUT_ID_PAUSE_BASE) || (box->id > SPORT_DATA_LAYOUT_ID_READY_BASE))
            {
                if (box->id == SPORT_DATA_LAYOUT_ID_TIME)
                {
                    gui_surface_box_change_visible(box, 1);
                }
                else if (m_window_type == 2)
                {
                    if (box->id < SPORT_DATA_LAYOUT_ID_FOOTBALL_BASE)
                    {
                        gui_surface_box_change_visible(box, 1);

                        gui_box_struct *hr_log = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_BPM);
                        gui_box_struct *hr_txt = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_BPM_TEXT);

                        gui_surface_box_change_x(hr_log, 290);
                        gui_surface_box_change_y(hr_log, 290);
                        gui_surface_box_change_x(hr_txt, 290);
                        gui_surface_box_change_y(hr_txt, 240);

                        gui_box_struct *kcal_log = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KCAL);
                        gui_box_struct *kcal_txt = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KCAL_TEXT);

                        gui_surface_box_change_x(kcal_log, 100);
                        gui_surface_box_change_y(kcal_log, 290);
                        gui_surface_box_change_x(kcal_txt, 100);
                        gui_surface_box_change_y(kcal_txt, 240);
                        gui_box_struct *swim_line = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_SWIM_LINE);
                        gui_box_struct *steps_line = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_STEPS_LINE);
                        swim_line->visible = 1;
                        steps_line->visible = 0;
                    }
                    else
                    {
                        gui_surface_box_change_visible(box, 0);
                    }
                }
                else if (m_window_type == 1)
                {
                    if (box->id < SPORT_DATA_LAYOUT_ID_SWIM_BASE)
                    {

                        gui_surface_box_change_visible(box, 1);

                        gui_box_struct *steps_log = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_STEPS);
                        gui_box_struct *steps_txt = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_STEPS_TEXT);

                        gui_surface_box_change_x(steps_log, 290);
                        gui_surface_box_change_y(steps_log, 280);
                        gui_surface_box_change_x(steps_txt, 300);
                        gui_surface_box_change_y(steps_txt, 235);

                        gui_box_struct *hr_log = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_BPM);
                        gui_box_struct *hr_txt = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_BPM_TEXT);

                        gui_surface_box_change_x(hr_log, 224);
                        gui_surface_box_change_y(hr_log, 370);
                        gui_surface_box_change_x(hr_txt, 224);
                        gui_surface_box_change_y(hr_txt, 324);

                        gui_box_struct *kcal_log = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KCAL);
                        gui_box_struct *kcal_txt = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KCAL_TEXT);

                        gui_surface_box_change_x(kcal_log, 100);
                        gui_surface_box_change_y(kcal_log, 280);
                        gui_surface_box_change_x(kcal_txt, 110);
                        gui_surface_box_change_y(kcal_txt, 235);

                        gui_box_struct *swim_line = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_SWIM_LINE);
                        gui_box_struct *steps_line = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_STEPS_LINE);
                        swim_line->visible = 0;
                        steps_line->visible = 1;
                    }
                    else
                    {
                        gui_surface_box_change_visible(box, 0);
                    }
                }
                else
                {
                    if (box->id < SPORT_DATA_LAYOUT_ID_PAUSE_BASE)
                    {
                        gui_surface_box_change_visible(box, 1);
                        gui_box_struct *swim_line = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_SWIM_LINE);
                        gui_box_struct *steps_line = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_STEPS_LINE);
                        swim_line->visible = 0;
                        steps_line->visible = 1;
                    }
                    else
                    {
                        gui_surface_box_change_visible(box, 0);
                    }
                }
            }
            else
            {
                gui_surface_box_change_visible(box, 0);
            }
            index++;
        }
    }
}

static void app_window_sport_data_update_walk(void)
{
    char temp[40];
    unsigned int value;
    unsigned int sec;
    gui_box_struct *box;
    gui_box_struct *box_img;
    box = gui_surface_get_box(&gui_screen_sport_data, (unsigned short)SPORT_DATA_LAYOUT_ID_TIME);
    if (box != NULL)
    {
        m_temp_time = sport_time_get() / 1000;
        sec = m_temp_time;

        /* display sport time. */
        snprintf(temp, sizeof(temp), "%02d:%02d:%02d", sec / 3600, (sec / 60) % 60, sec % 60);
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }

    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_STEPS_TEXT);
    if (box != NULL)
    {
        /* display step. */
        char_to_int(get_mix_sport_info()->type.info.step, &value, 4);
        snprintf(temp, sizeof(temp), "%d", value);
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }

    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_BPM_TEXT);
    if (box != NULL)
    {
        /* display heart. */
        if (get_mix_sport_info()->type.info.max_heartrate > 0)
        {
            value = last_hr_result.hr;
            snprintf(temp, sizeof(temp), "%03d", value);
        }
        else
        {
            snprintf(temp, sizeof(temp), "--");
        }
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }

    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KCAL_TEXT);
    if (box != NULL)
    {
        /* display calorie. */
        char_to_int(get_mix_sport_info()->type.info.calories, &value, 4);
        snprintf(temp, sizeof(temp), "%d", value / 1000);
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }

    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KM_TEXT);

    box_img = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KM);
    if (box != NULL)
    {
        /* display distance. */
        char_to_int(get_mix_sport_info()->type.info.distance, &value, 4);
        if (g_unit_setting.select.bit.distance)
        {
            // 1mile = 1609.3m , mile
            snprintf(temp, sizeof(temp), "%d.%d%d", value * 10 / 16093, (value * 10 * 10) / 16093 % 10, (value * 10 * 10 * 10) / 16093 % 10);
            gui_surface_box_image_change(box_img, (const picture_info_struct *)&pic_sport_font_mile_info);
        }
        else
        { // km
            snprintf(temp, sizeof(temp), "%d.%d%d", value / 1000, (value / 100) % 10, (value / 10) % 10);
            gui_surface_box_image_change(box_img, (const picture_info_struct *)&pic_sport_font_km_info);
        }
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }
}

static void app_window_sport_data_update_football(void)
{
    char temp[40];
    unsigned int value;
    unsigned int sec;
    gui_box_struct *box;

    box = gui_surface_get_box(&gui_screen_sport_data, (unsigned short)SPORT_DATA_LAYOUT_ID_TIME);
    if (box != NULL)
    {
        m_temp_time = sport_time_get() / 1000;
        sec = m_temp_time;

        /* display sport time. */
        snprintf(temp, sizeof(temp), "%02d:%02d:%02d", sec / 3600, (sec / 60) % 60, sec % 60);
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }

    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_STEPS_TEXT);
    if (box != NULL)
    {
        /* display step. */
        char_to_int(get_mix_sport_info()->type.info.step, &value, 4);
        snprintf(temp, sizeof(temp), "%d", value);
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }
    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KCAL_TEXT);
    if (box != NULL)
    {
        /* display calorie. */
        char_to_int(get_mix_sport_info()->type.info.calories, &value, 4);
        snprintf(temp, sizeof(temp), "%d", value / 1000);
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }
    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_BPM_TEXT);
    if (box != NULL)
    {
        /* display heart. */
        if (get_mix_sport_info()->type.info.max_heartrate > 0)
        {
            value = get_mix_sport_heart()->max_hr;
            snprintf(temp, sizeof(temp), "%03d", value);
        }
        else
        {
            snprintf(temp, sizeof(temp), "--");
        }
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }
}

static void app_window_sport_data_update_swim(void)
{
    char temp[40];
    unsigned int value;
    unsigned int sec;
    gui_box_struct *box;

    box = gui_surface_get_box(&gui_screen_sport_data, (unsigned short)SPORT_DATA_LAYOUT_ID_TIME);
    if (box != NULL)
    {
        m_temp_time = sport_time_get() / 1000;
        sec = m_temp_time;

        /* display sport time. */
        snprintf(temp, sizeof(temp), "%02d:%02d:%02d", sec / 3600, (sec / 60) % 60, sec % 60);
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }

    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_KCAL_TEXT);
    if (box != NULL)
    {
        /* display calorie. */
        char_to_int(get_mix_sport_info()->type.info.calories, &value, 4);
        snprintf(temp, sizeof(temp), "%d", value / 1000);
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }
    box = gui_surface_get_box(&gui_screen_sport_data, SPORT_DATA_LAYOUT_ID_BPM_TEXT);
    if (box != NULL)
    {
        /* display heart. */
        if (get_mix_sport_info()->type.info.max_heartrate > 0)
        {
            value = get_mix_sport_heart()->max_hr;
            snprintf(temp, sizeof(temp), "%03d", value);
        }
        else
        {
            snprintf(temp, sizeof(temp), "--");
        }
        gui_surface_box_label_change_string(box, (unsigned char *)temp);
    }
}

static void app_window_sport_ready_run_time(unsigned int timer_hd, void *param)
{

    app_window_sport_data_time_static_event_act(NULL);
}

/*-----------------------------系统事件--------------------------------------*/

static void app_window_sport_data_init(void *buf)
{
    // app_window_sport_ready_init();
    ready_flag = 0;
    logo_cnt = 0;
}

static void app_window_sport_data_load(void *buf)
{
    char temp[40];
    unsigned int sec;
    gui_box_struct *box;

    if (ready_flag)
    {
        box = gui_surface_get_box(&gui_screen_sport_data, (unsigned short)SPORT_DATA_LAYOUT_ID_TIME);
        if (box != NULL)
        {
            /* display sport time. */
            m_temp_time = sport_time_get() / 1000;
            sec = m_temp_time;
            snprintf(temp, sizeof(temp), "%02d:%02d:%02d", sec / 3600, (sec / 60) % 60, sec % 60);
            gui_surface_box_label_change_string(box, (unsigned char *)temp);
        }
        app_window_sport_data_update();
    }
    else
    {
        app_window_sport_ready_init();
        // logo_cnt = 0;
    }
    app_window_sport_data_time_static_event_act(buf);
}

static void app_window_sport_data_entry(void *buf)
{
    if ((SPORT_STATUS_START == m_window_sport_status) || (SPORT_STATUS_CONTINUE == m_window_sport_status))
    {
        /* open sport heart. */
        hr_set_sport_mode(1);
    }

    if (g_ready_timer_hd == 0)
    {
        g_ready_timer_hd = application_start_user_timer(1000, app_window_sport_ready_run_time, NULL);
    }

    application_reset_display_timeout(10);
}

static void app_window_sport_data_exit()
{

    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_sport_data_destroy()
{
    /* close sport heart. */
    hr_set_sport_mode(0);
    application_stop_user_timer(g_ready_timer_hd);
    g_ready_timer_hd = 0;

    application_close_act_timer(APPLICATION_TIMER_ACT);
}

static void app_window_sport_data_time_static_event_act(void *buf)
{
    if (ready_flag)
    {
        if (SPORT_STATUS_PAUSE != m_window_sport_status)
        {
            if (m_window_type == 2)
            {
                app_window_sport_data_update_swim();
            }
            else if (m_window_type == 1)
            {
                app_window_sport_data_update_football();
            }
            else
            {
                app_window_sport_data_update_walk();
            }
        }
    }
    else
    {
        app_window_sport_ready_run();
    }
    gui_surface_commit();
}

static void app_window_sport_data_time_static_event_key(void *buf)
{
    if ((SPORT_STATUS_START == m_window_sport_status) || (SPORT_STATUS_CONTINUE == m_window_sport_status))
    {
        sport_status_set(SPORT_STATUS_PAUSE);
    }
    else if (SPORT_STATUS_PAUSE == m_window_sport_status)
    {
        sport_status_set(SPORT_STATUS_CONTINUE);
    }
    app_window_sport_data_update();
    app_window_sport_data_time_static_event_act(buf);
}

static void app_window_sport_data_continue_click(gui_click_struct *event)
{
    if (SPORT_STATUS_PAUSE == m_window_sport_status)
    {
        sport_status_set(SPORT_STATUS_CONTINUE);
        app_window_sport_data_update();
        app_window_sport_data_time_static_event_act(NULL);
    }
}

static void app_window_sport_data_finish_click(gui_click_struct *event)
{
    if (SPORT_STATUS_PAUSE == m_window_sport_status)
    {
        sport_status_set(SPORT_STATUS_STOP);
        application_go_back();
    }
}

static void app_window_sptt_finish_click(gui_click_struct *event)
{

    if ((SPORT_STATUS_START == m_window_sport_status) || (SPORT_STATUS_CONTINUE == m_window_sport_status))
    {
        sport_status_set(SPORT_STATUS_PAUSE);
    }
    else if (SPORT_STATUS_PAUSE == m_window_sport_status)
    {
        sport_status_set(SPORT_STATUS_CONTINUE);
    }
    app_window_sport_data_update();
}

static void app_window_sport_finish_click(gui_click_struct *event)
{
    sport_status_set(SPORT_STATUS_STOP);
    ready_flag = 0;
    application_go_back();
}

/*-----------------------------????--------------------------------------*/
static const gui_touch_event_struct app_window_sport_data_touch_events[] =
    {
        {.id = SPORT_DATA_LAYOUT_ID_PAUSE_CONTINUE_PIC, .click = app_window_sport_data_continue_click},
        {.id = SPORT_DATA_LAYOUT_ID_PAUSE_EXIT_PIC, .click = app_window_sport_data_finish_click},

        //	{.id = SPORT_DATA_LAYOUT_ID_STOP,			.click = app_window_sptt_finish_click},
        //	{.id = SPORT_DATA_LAYOUT_ID_RESET,          .click = app_window_sport_finish_click},
};
static const app_window_event_struct app_window_sport_data_time_static_events[] =
    {
        {
            .id = EVENT_ACT, // 控件ID.
            .handler = app_window_sport_data_time_static_event_act,
        },

        {
            .id = EVENT_GUI_RESUMED, //??ID.
            .handler = app_window_sport_data_time_static_event_act,
        },
        {
            .id = EVENT_KEY1_SHORT, // 控件ID.
            .handler = app_window_sport_data_time_static_event_key,
        },
        {
            .id = EVENT_KEY1_LONG, // 控件ID.
            .handler = app_window_sport_data_time_static_event_key,
        },
        {
            .id = EVENT_KEY2_SHORT, // 控件ID.
            .handler = app_window_sport_data_time_static_event_key,
        },
};
static const gui_window_config_struct app_window_sport_data_config =
    {
        .forbid_gesture_back = 1,
        .disable_go_home = 1,
};

const gui_window_struct app_window_sport_data =
    {
        .screen = &gui_screen_sport_data,
        .config = &app_window_sport_data_config,

        .init = app_window_sport_data_init,
        .load = app_window_sport_data_load,
        .entry = app_window_sport_data_entry,
        .exit = app_window_sport_data_exit,
        .destroy = app_window_sport_data_destroy,

        .touch_event_num = countof(app_window_sport_data_touch_events),
        .touch_events = app_window_sport_data_touch_events,

        .event_num = countof(app_window_sport_data_time_static_events),
        .events = app_window_sport_data_time_static_events,

};
