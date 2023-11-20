
#include "picture.h"
#include "application_config_app_info.h"
#include "app_window_moreinfo_cellular_layout.h"


#define DEF_CELL_PICS(u_name, l_name)  static const picture_info_struct* const gui_cellular_##u_name[] = APP_PICS(l_name)

#define ADD_CELL_ITEM(u_name, l_name) {   \
            .id = APP_INFO_ID_##u_name,   \
            .type = TYPE_GUI_CONTROL_LAYOUT_CELL, \
            .visible = 1, \
            .child_num = countof(gui_cellular_##u_name), \
            .children = gui_cellular_##u_name, \
        }

DEF_CELL_PICS(ALARM, clock);
DEF_CELL_PICS(SIRI, siri);
//DEF_CELL_PICS(BLOOD, BP);
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
DEF_CELL_PICS(QR, QR_code);
DEF_CELL_PICS(REBOOT, reboot);
DEF_CELL_PICS(RESTORE, restore);
DEF_CELL_PICS(SHUTDOWN, shutdown);
// DEF_CELL_PICS(ABOUT, about);




static const gui_widget_struct gui_widget_cellular_list[] =
{

   ADD_CELL_ITEM(ALARM, alarm),
    ADD_CELL_ITEM(SIRI, siri),
//    ADD_CELL_ITEM(BLOOD, BP),
    ADD_CELL_ITEM(BREATHE, breath),
    ADD_CELL_ITEM(MUSIC, music),
    ADD_CELL_ITEM(CALL, telephone),
    ADD_CELL_ITEM(COUNTER, counter),
    ADD_CELL_ITEM(CALENDAR, calendar),
    ADD_CELL_ITEM(FIND, findphone),
    ADD_CELL_ITEM(HR, hr),
//    ADD_CELL_ITEM(CONTACTS, contacts),

    ADD_CELL_ITEM(BRIGHTNESS, brightness),
    ADD_CELL_ITEM(LCDTIMEOUT, lcd_time),
    ADD_CELL_ITEM(QR, QR_code),
    ADD_CELL_ITEM(REBOOT, reboot),
    ADD_CELL_ITEM(RESTORE, restore),
    ADD_CELL_ITEM(SHUTDOWN, shutdown),
    ADD_CELL_ITEM(HOME, home),
    // ADD_CELL_ITEM(ABOUT, about),

    ADD_CELL_ITEM(CLACULATOR, calc),
    ADD_CELL_ITEM(O2, O2),
//    ADD_CELL_ITEM(CALL_LOG, call_log),
    ADD_CELL_ITEM(PHOTO, photograph),
    ADD_CELL_ITEM(MESSAGE, msg),
    ADD_CELL_ITEM(SETTING, setting),

    ADD_CELL_ITEM(SLEEP, sleep),
    ADD_CELL_ITEM(SPORT, sport_outdoor),

    ADD_CELL_ITEM(STOPWATCH, stopwatch),
    ADD_CELL_ITEM(WEATHER, weather),
    ADD_CELL_ITEM(STEP, steps),
    ADD_CELL_ITEM(WATCHFACE, watchface),





};

static const gui_layout_cellular_struct gui_cellular_layout_config =
{
	/*-----�Զ�����-------*/
	.offset_x = 0, 			//��ǰƫ�Ƶ�Y����
	.offset_y = 0, 			//���ж�����
	.width = 0,
	.height = 0,

	.diameter = 88,	//�����ĸ߶�
	.min_column = 3,
	.max_column = 6,

	.margin = 54,	//�����Ŀ�ȱ
	.space = 6,  	//������֮��ļ�϶
	.default_center = 15 ,
};


const gui_screen_struct gui_screen_cellular =
{
	.type = TYPE_GUI_LAYOUT_CELLULAR,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_cellular_list,
	.child_num = countof(gui_widget_cellular_list),
	.layout_config = &gui_cellular_layout_config,
};



