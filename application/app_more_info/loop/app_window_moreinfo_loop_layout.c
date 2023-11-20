#include "app_window_moreinfo_loop_layout.h"
#include "picture.h"
#include "application_config_app_info.h"

#define DEF_LOOP_PICS(u_name, l_name) static const picture_info_struct *const gui_loop_##u_name[] = APP_PICS(l_name)

#define ADD_LOOP_ITEM(u_name, l_name)            \
    {                                            \
        .id = APP_INFO_ID_##u_name,              \
        .type = TYPE_GUI_CONTROL_LAYOUT_CELL,    \
		.anchor_x = ANCHOR_VALUE(0.5),		     \
		.anchor_y = ANCHOR_VALUE(0.5),			 \
        .visible = 1,                            \
        .child_num = countof(gui_loop_##u_name), \
        .children = gui_loop_##u_name,           \
    }

DEF_LOOP_PICS(BREATHE, breath);
DEF_LOOP_PICS(FIND, findphone);
DEF_LOOP_PICS(HR, hr);

DEF_LOOP_PICS(MUSIC, music);
DEF_LOOP_PICS(O2, O2);
DEF_LOOP_PICS(PHOTO, photograph);

DEF_LOOP_PICS(SETTING, setting);
DEF_LOOP_PICS(SLEEP, sleep);
DEF_LOOP_PICS(STOPWATCH, stopwatch);

DEF_LOOP_PICS(COUNTER, counter);
DEF_LOOP_PICS(WEATHER, weather);
DEF_LOOP_PICS(SPORT, sport_outdoor);

DEF_LOOP_PICS(SIRI, siri);
DEF_LOOP_PICS(CALL, telephone);

DEF_LOOP_PICS(MESSAGE, message);
DEF_LOOP_PICS(CLACULATOR, calc);
DEF_LOOP_PICS(STEP, steps);

DEF_LOOP_PICS(WATCHFACE, watchface);
DEF_LOOP_PICS(QR_PUSH, qr_push);

DEF_LOOP_PICS(CALENDAR, calendar);
DEF_LOOP_PICS(BRIGHTNESS, brightness);
DEF_LOOP_PICS(LCDTIMEOUT, lcd_time);

DEF_LOOP_PICS(QR, QR_code);
DEF_LOOP_PICS(GAME, game);
DEF_LOOP_PICS(RESTORE, restore);
DEF_LOOP_PICS(BLOOD, BP);
DEF_LOOP_PICS(REBOOT, reboot);
DEF_LOOP_PICS(ALARM, clock);
DEF_LOOP_PICS(SHUTDOWN, shutdown);

static const gui_widget_struct gui_widget_loop_list[] =
{
    ADD_LOOP_ITEM(O2, O2),
    ADD_LOOP_ITEM(STEP, steps),
    ADD_LOOP_ITEM(PHOTO, photograph),
    ADD_LOOP_ITEM(SHUTDOWN, shutdown),

    ADD_LOOP_ITEM(WEATHER, weather),          // 1
    ADD_LOOP_ITEM(ALARM, clock),


    ADD_LOOP_ITEM(FIND, findphone),
    ADD_LOOP_ITEM(MESSAGE, message),
    ADD_LOOP_ITEM(CALENDAR, calendar),

    ADD_LOOP_ITEM(COUNTER, counter),
    ADD_LOOP_ITEM(MUSIC, music),
    ADD_LOOP_ITEM(QR, QR_code),                 // 3

    ADD_LOOP_ITEM(WATCHFACE, watchface),
    ADD_LOOP_ITEM(BREATHE, breath),
    ADD_LOOP_ITEM(HR, hr),

    ADD_LOOP_ITEM(STOPWATCH, stopwatch),
    ADD_LOOP_ITEM(CLACULATOR, calc),
    ADD_LOOP_ITEM(SIRI, siri),

    ADD_LOOP_ITEM(SLEEP, sleep),
    ADD_LOOP_ITEM(CALL, telephone),
    ADD_LOOP_ITEM(QR_PUSH, qr_push),


    ADD_LOOP_ITEM(LCDTIMEOUT, lcd_time),
    ADD_LOOP_ITEM(SPORT, sport_outdoor),
    ADD_LOOP_ITEM(RESTORE, restore),


    ADD_LOOP_ITEM(SETTING, setting),
    ADD_LOOP_ITEM(BLOOD, BP),
    ADD_LOOP_ITEM(GAME, game),
};


#define MID_SCALE   (1.234f)
static const float s_temp[] = {0, MID_SCALE/2.0f, MID_SCALE*3.0f/4.0f, MID_SCALE, MID_SCALE*3.0f/4.0f, MID_SCALE/2.0f, 0};

static const gui_layout_loop_struct gui_loop_layout_config =
{
    .column = 3,
    .row_height = 88,

    .scroll = 1,
    .can_swipe = 0,
    .arc_flag = 1,
    .zoom_flag = 1,
    .arc_radius = 400,
    .loop_flag = 1,

    .scale_map = s_temp,
};


const gui_screen_struct gui_screen_loop =
{
	.type = TYPE_GUI_LAYOUT_LOOP,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_loop_list,
	.child_num = countof(gui_widget_loop_list),
	.layout_config = &gui_loop_layout_config,
};



