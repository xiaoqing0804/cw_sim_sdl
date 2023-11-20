#include "picture.h"
#include "application_config_app_info.h"
#include "app_window_moreinfo_apple_cellular_layout.h"

#define CELL_NORMAL_WIDTH (98)

#define CELL_PICS(name)           \
    {                             \
        &pic_app_##name##_88_info \
    }

#define DEF_CELL_PICS(u_name, l_name) static const picture_info_struct *const gui_cellular_##u_name[] = CELL_PICS(l_name)

#define ADD_CELL_ITEM(u_name, l_name)                                   \
    {                                                                   \
        .id = APP_INFO_ID_##u_name,                                     \
        .type = TYPE_GUI_CONTROL_LAYOUT_CELL,                           \
        .visible = 1,                                                   \
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER), \
        .width = CELL_NORMAL_WIDTH,                                     \
        .height = CELL_NORMAL_WIDTH,                                    \
        .anchor_x = ANCHOR_VALUE(0.5f),                                 \
        .anchor_y = ANCHOR_VALUE(0.5f),                                 \
        .child_num = countof(gui_cellular_##u_name),                    \
        .children = gui_cellular_##u_name,                              \
    }

DEF_CELL_PICS(AOD_DIAL, aod);
DEF_CELL_PICS(ADVANCED_SET, wake_timeout);
DEF_CELL_PICS(DISTURB, disturb);
DEF_CELL_PICS(WIDGET, add);
DEF_CELL_PICS(ALARM, clock);
DEF_CELL_PICS(SIRI, siri);
DEF_CELL_PICS(BREATHE, breath);
DEF_CELL_PICS(CLACULATOR, calc);
DEF_CELL_PICS(CALL, telephone);
DEF_CELL_PICS(COUNTER, counter);
DEF_CELL_PICS(CALENDAR, calendar);
DEF_CELL_PICS(FIND, findphone);
DEF_CELL_PICS(HR, hr);
DEF_CELL_PICS(CONTACTS, telephone);
DEF_CELL_PICS(MUSIC, music);
DEF_CELL_PICS(O2, O2);
DEF_CELL_PICS(CALL_LOG, telephone);
DEF_CELL_PICS(PHOTO, photograph);
DEF_CELL_PICS(MESSAGE, message);
DEF_CELL_PICS(SETTING, setting);
DEF_CELL_PICS(SLEEP, sleep);
DEF_CELL_PICS(SPORT, sport_outdoor);
DEF_CELL_PICS(STOPWATCH, stopwatch);
DEF_CELL_PICS(WEATHER, weather);
DEF_CELL_PICS(HOME, home);
DEF_CELL_PICS(STEP, steps);
DEF_CELL_PICS(WATCHFACE, watchface);
DEF_CELL_PICS(BRIGHTNESS, brightness);
DEF_CELL_PICS(LCDTIMEOUT, lcd_time);
DEF_CELL_PICS(QR_PUSH, qr_push);
DEF_CELL_PICS(QR, QR_code);
DEF_CELL_PICS(BLOOD, BP);
DEF_CELL_PICS(RESTORE, restore);
DEF_CELL_PICS(GAME, game);
DEF_CELL_PICS(LANGUAGE, language);
DEF_CELL_PICS(ABOUT, about);
DEF_CELL_PICS(SCREEN_SET, screen_set);
DEF_CELL_PICS(SCREEN_MENU, menu_set);
DEF_CELL_PICS(CONSTANT_LIGHTE, lcd_clock);
DEF_CELL_PICS(SHUTDOWN, shutdown);

static const gui_widget_struct gui_widget_cellular_list[] =
    {
        ADD_CELL_ITEM(HR, hr),          // 3
        ADD_CELL_ITEM(BREATHE, breath), // 4
        ADD_CELL_ITEM(SIRI, siri),      // 4
        ADD_CELL_ITEM(O2, O2),          // 3

        ADD_CELL_ITEM(CLACULATOR, calc),     // 1
        ADD_CELL_ITEM(SLEEP, sleep),         // 4
        ADD_CELL_ITEM(STOPWATCH, stopwatch), // 3
        ADD_CELL_ITEM(WIDGET, add),          // 2
        ADD_CELL_ITEM(CALL, telephone),      // 6

        ADD_CELL_ITEM(CONSTANT_LIGHTE, lcd_clock), // 3
        ADD_CELL_ITEM(LANGUAGE, language),         // 1
        ADD_CELL_ITEM(SETTING, setting),           // 1
        ADD_CELL_ITEM(STEP, steps),                // 2
        ADD_CELL_ITEM(WATCHFACE, watchface),       // 5
        ADD_CELL_ITEM(BLOOD, BP),                  // 1

        ADD_CELL_ITEM(MUSIC, music),           // 5
        ADD_CELL_ITEM(SPORT, sport_outdoor),   // 3
        ADD_CELL_ITEM(DISTURB, disturb),       // 2
        ADD_CELL_ITEM(HOME, home),             // 4
        ADD_CELL_ITEM(BRIGHTNESS, brightness), // 3
        ADD_CELL_ITEM(FIND, findphone),        // 4
        ADD_CELL_ITEM(ALARM, clock),           // 3

        ADD_CELL_ITEM(LCDTIMEOUT, lcd_time),   // 4
        ADD_CELL_ITEM(PHOTO, photograph),      // 1
        ADD_CELL_ITEM(QR_PUSH, qr_push),       // 3
        ADD_CELL_ITEM(SCREEN_SET, screen_set), // 1
        ADD_CELL_ITEM(COUNTER, counter),       // 3
        ADD_CELL_ITEM(CALENDAR, calendar),     // 2

        ADD_CELL_ITEM(QR, QR_code),      // 3
        ADD_CELL_ITEM(RESTORE, restore), // 6
        ADD_CELL_ITEM(MESSAGE, msg),     // 6
        ADD_CELL_ITEM(AOD_DIAL, aod),    // 1
        ADD_CELL_ITEM(WEATHER, weather), // 4

        ADD_CELL_ITEM(SCREEN_MENU, menu_set), // 1
        ADD_CELL_ITEM(GAME, game),            // 3
        ADD_CELL_ITEM(ABOUT, about),          // 4
        ADD_CELL_ITEM(SHUTDOWN, shutdown),

};

static const gui_layout_apple_cellular_struct gui_apple_cellular_layout_config =
    {
        /*-----自动计算-------*/
        .offset_x = 0, // 当前偏移的Y坐标
        .offset_y = 0, // 共有多少条

        .width = 0,
        .height = 0,
        .scale = 1.0f,

        .min_diameter = 55,  // 0.75  图标全部在屏幕内时的大小
        .mid_diameter = 103, // 1.00  图标的标准大小，中间状态
        .max_diameter = 153, // 1.33  图标放大状态时的大小
        .app_diameter = 170, // 1.60  图标进入打开App状态时的大小
        .icon_diameter = 98, // 图片大小

        .space = 6, // 条与条之间的间隙
};

const gui_screen_struct gui_screen_apple_cellular =
    {
        .type = TYPE_GUI_LAYOUT_APPLE_CELLULAR,
        .space_x = 0,
        .space_y = 0,
        .order = 0,
        .children = gui_widget_cellular_list,
        .child_num = countof(gui_widget_cellular_list),
        .layout_config = &gui_apple_cellular_layout_config,
};
