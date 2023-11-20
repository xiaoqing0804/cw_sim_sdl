#include "picture.h"
#include "application_config_app_info.h"
#include "app_window_moreinfo_matrix_layout.h"

#define MATRIX_NORMAL_WIDTH (98)

#define MATRIX_PICS(name)         \
    {                             \
        &pic_app_##name##_88_info \
    }

#define DEF_MATRIX_PICS(u_name, l_name) static const picture_info_struct *const gui_cellular_##u_name[] = MATRIX_PICS(l_name)

#define ADD_MATRIX_ITEM(u_name, l_name)                                 \
    {                                                                   \
        .id = APP_INFO_ID_##u_name,                                     \
        .type = TYPE_GUI_CONTROL_LAYOUT_CELL,                           \
        .visible = 1,                                                   \
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER), \
        .anchor_x = ANCHOR_VALUE(0.5f),                                 \
        .anchor_y = ANCHOR_VALUE(0.5f),                                 \
        .width = MATRIX_NORMAL_WIDTH,                                   \
        .height = MATRIX_NORMAL_WIDTH,                                  \
        .child_num = countof(gui_cellular_##u_name),                    \
        .children = gui_cellular_##u_name,                              \
    }

DEF_MATRIX_PICS(AOD_DIAL, aod);
DEF_MATRIX_PICS(ADVANCED_SET, wake_timeout);
DEF_MATRIX_PICS(DISTURB, disturb);
DEF_MATRIX_PICS(WIDGET, add);
DEF_MATRIX_PICS(ALARM, clock);
DEF_MATRIX_PICS(SIRI, siri);
DEF_MATRIX_PICS(BREATHE, breath);
DEF_MATRIX_PICS(CLACULATOR, calc);
DEF_MATRIX_PICS(CALL, telephone);
DEF_MATRIX_PICS(COUNTER, counter);
DEF_MATRIX_PICS(CALENDAR, calendar);
DEF_MATRIX_PICS(FIND, findphone);
DEF_MATRIX_PICS(HR, hr);
DEF_MATRIX_PICS(CONTACTS, telephone);
DEF_MATRIX_PICS(MUSIC, music);
DEF_MATRIX_PICS(O2, O2);
DEF_MATRIX_PICS(CALL_LOG, telephone);
DEF_MATRIX_PICS(PHOTO, photograph);
DEF_MATRIX_PICS(MESSAGE, message);
DEF_MATRIX_PICS(SETTING, setting);
DEF_MATRIX_PICS(SLEEP, sleep);
DEF_MATRIX_PICS(SPORT, sport_outdoor);
DEF_MATRIX_PICS(STOPWATCH, stopwatch);
DEF_MATRIX_PICS(WEATHER, weather);
DEF_MATRIX_PICS(HOME, home);
DEF_MATRIX_PICS(STEP, steps);
DEF_MATRIX_PICS(WATCHFACE, watchface);
DEF_MATRIX_PICS(BRIGHTNESS, brightness);
DEF_MATRIX_PICS(LCDTIMEOUT, lcd_time);
DEF_MATRIX_PICS(QR_PUSH, qr_push);
DEF_MATRIX_PICS(QR, QR_code);
DEF_MATRIX_PICS(BLOOD, BP);
DEF_MATRIX_PICS(RESTORE, restore);
DEF_MATRIX_PICS(GAME, game);
DEF_MATRIX_PICS(LANGUAGE, language);
DEF_MATRIX_PICS(ABOUT, about);
DEF_MATRIX_PICS(SCREEN_SET, screen_set);
DEF_MATRIX_PICS(SCREEN_MENU, menu_set);
DEF_MATRIX_PICS(CONSTANT_LIGHTE, lcd_clock);
DEF_MATRIX_PICS(SHUTDOWN, shutdown);

static const gui_widget_struct gui_widget_matrix_list[] =
    {
        ADD_MATRIX_ITEM(HR, hr),
        ADD_MATRIX_ITEM(BREATHE, breath),
        ADD_MATRIX_ITEM(SIRI, siri),
        ADD_MATRIX_ITEM(O2, O2),
        ADD_MATRIX_ITEM(CLACULATOR, calc),

        ADD_MATRIX_ITEM(SLEEP, sleep),
        ADD_MATRIX_ITEM(STOPWATCH, stopwatch),
        ADD_MATRIX_ITEM(ABOUT, about),
        ADD_MATRIX_ITEM(CALL, telephone),
        ADD_MATRIX_ITEM(CONSTANT_LIGHTE, lcd_clock),

        ADD_MATRIX_ITEM(LANGUAGE, language),
        ADD_MATRIX_ITEM(SETTING, setting),
        ADD_MATRIX_ITEM(GAME, game),
        ADD_MATRIX_ITEM(WATCHFACE, watchface),
        ADD_MATRIX_ITEM(BLOOD, BP),

        ADD_MATRIX_ITEM(MUSIC, music),
        ADD_MATRIX_ITEM(SPORT, sport_outdoor),
        ADD_MATRIX_ITEM(HOME, home),
        ADD_MATRIX_ITEM(DISTURB, disturb),
        ADD_MATRIX_ITEM(FIND, findphone),

        ADD_MATRIX_ITEM(BRIGHTNESS, brightness),
        ADD_MATRIX_ITEM(ALARM, clock),
        ADD_MATRIX_ITEM(LCDTIMEOUT, lcd_time),
        ADD_MATRIX_ITEM(PHOTO, photograph),
        ADD_MATRIX_ITEM(QR_PUSH, pr_phus),

        ADD_MATRIX_ITEM(MESSAGE, msg),
        ADD_MATRIX_ITEM(SCREEN_SET, screen_set),
        ADD_MATRIX_ITEM(CALENDAR, calendar),
        ADD_MATRIX_ITEM(QR, QR_code),
        ADD_MATRIX_ITEM(SHUTDOWN, shutdown),

        ADD_MATRIX_ITEM(COUNTER, counter),
        ADD_MATRIX_ITEM(AOD_DIAL, aod),
        ADD_MATRIX_ITEM(WEATHER, weather),
        ADD_MATRIX_ITEM(SCREEN_MENU, menu_set),
        ADD_MATRIX_ITEM(STEP, steps),
};

static const gui_layout_matrix_struct gui_matrix_layout_config =
    {
        /*-----自动计算-------*/
        .offset_x = 0, // 当前偏移的Y坐标
        .offset_y = 0, // 共有多少条

        .width = 0,
        .height = 0,
        .scale = 1.0f,

        .min_diameter = 50,  // 0.75  图标全部在屏幕内时的大小
        .mid_diameter = 98,  // 1.00  图标的标准大小，中间状态
        .max_diameter = 120, // 1.33  图标放大状态时的大小
        .app_diameter = 170, // 1.60  图标进入打开App状态时的大小
        .icon_diameter = 98, // 图片大小

        .space = 6, // 条与条之间的间隙
};

const gui_screen_struct gui_screen_matrix =
    {
        .type = TYPE_GUI_LAYOUT_MATRIX,
        .space_x = 0,
        .space_y = 0,
        .order = 0,
        .children = gui_widget_matrix_list,
        .child_num = countof(gui_widget_matrix_list),
        .layout_config = &gui_matrix_layout_config,
};
