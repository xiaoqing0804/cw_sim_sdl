#include "debug_info.h"
#include "app_window_sport_data.h"
#include "app_window_sport_data_exit.h"

#include "application_titlebar.h"

#include "app_widget/app_window_widget_delete.h"
#include "app_window_sportlist.h"
#include "app_window_sportlist_layout.h"
#include "gui_surface_layout_listview.h"
#include "gui_surface_box_scale.h"
#include "gui_surface_node_scale.h"

static const struct
{
    unsigned int string;
    picture_info_struct *pic;
    unsigned int id;
} sport_window_list_info[] =
    {
        // 5
        {STRING_SPORT_RUN, &pic_run_info, MIX_SPORT_RUN},
        {STRING_SPORT_WALK, &pic_walk_info, MIX_SPORT_WALK},
        {STRING_SPORT_CYCLING, &pic_cycling_info, MIX_SPORT_CYCLING},
        {STRING_SPORT_CLIMB, &pic_climbing_info, MIX_SPORT_CLIMBING},
        {STRING_SPORT_YOGA, &pic_yoga_info, MIX_SPORT_YOGA},
        // 10
        {STRING_SPORT_BASKETBALL, &pic_basketball_info, MIX_SPORT_BASKETBALL},
        {STRING_SPORT_FOOTBALL, &pic_football_info, MIX_SPORT_FOOTBALL},
        {STRING_SPORT_BADMINTON, &pic_badminton_info, MIX_SPORT_BADMINTON},
        {STRING_SPORT_SKIP, &pic_skip_info, MIX_SPORT_SKIP},
        {STRING_SPORT_SWIM, &pic_swim_info, MIX_SPORT_SWIM}, // 15
        {STRING_CRICKET, &pic_cricket_info, MIX_SPORT_CRICKET},
        {STRING_VOLLEYBALL, &pic_volleyball_info, MIX_SPORT_VOLLEYBALL},
        {STRING_HOCKEY, &pic_hockey_info, MIX_SPORT_HOCKEY},
        {STRING_JUDO, &pic_judo_info, MIX_SPORT_JUDO},
        {STRING_ROCKCLIMBING, &pic_rockclimbing_info, MIX_SPORT_ROCKCLIMBING},
        // 15
        {STRING_AIR_WALKER, &pic_Air_Walker_info, MIX_SPORT_AIR_WALKER},
        {STRING_ARCHERY, &pic_archery_info, MIX_SPORT_ARCHERY},
        {STRING_BALLET, &pic_ballet_info, MIX_SPORT_BALLET},
        {STRING_BASEBALL, &pic_baseball_info, MIX_SPORT_BASEBALL},
        {STRING_BEACH_SOCCER, &pic_beach_football_info, MIX_SPORT_BEACH_FOOTBALL},
        // 20
        {STRING_BEACH_VOLLEYBALL, &pic_beach_volleyball_info, MIX_SPORT_BEACH_VOLLEYBALL},
        {STRING_BILLIARD, &pic_billiards_info, MIX_SPORT_BILLIARDS},
        {STRING_BOWLING, &pic_bowling_info, MIX_SPORT_BOWLING},
        {STRING_BREAL_DANCE, &pic_break_dance_info, MIX_SPORT_BREAK_DANCE},
        {STRING_CROSS_COUNTRY_SKIING, &pic_cross_country_skiing_info, MIX_SPORT_CROSSCOUNTRYSKIING},
        // 25
        {STRING_CURLING, &pic_curling_info, MIX_SPORT_CULING},
        {STRING_DARTS, &pic_darts_info, MIX_SPORT_DARTS},
        {STRING_DRIVE, &pic_drive_info, MIX_SPORT_DRIVE},
        {STRING_FOLK_DANCE, &pic_folk_dance_info, MIX_SPORT_FOLK_DANCE},
        {STRING_FRISBEE, &pic_frisbee_info, MIX_SPORT_FRISBEE},
        // 30
        {STRING_HULA_HOOP, &pic_hula_hoop_info, MIX_SPORT_HULAHOOP},
        {STRING_JUJITSU, &pic_jujitsu_info, MIX_SPORT_JUJITSU},
        {STRING_KITE_FLYING, &pic_kite_flying_info, MIX_SPORT_KITE_FLYING},
        {STRING_LINE_SKATING, &pic_line_skating_info, MIX_SPORT_LINE_SKATING},
        {STRING_MARTIAL_ARTS, &pic_martial_arts_info, MIX_SPORT_MARTIAL_ARTS},
        // 35
        {STRING_MOTOCROSS, &pic_Motocross_info, MIX_SPORT_MOTOCROSS},
        {STRING_MOUNTAIN_BIKING, &pic_mountain_biking_info, MIX_SPORT_MOUNTAIN_BIKING},
        {STRING_OUTDOOR_SKIING, &pic_Outdoor_Skiing_info, MIX_SPORT_OUTDOOR_SKATING},
        {STRING_POLE_DANCING, &pic_Pole_Dancing_info, MIX_SPORT_POLE_DANCE},
        {STRING_ROLLER_SKATING, &pic_roller_skating_info, MIX_SPORT_ROLLER_SKATING},
        // 40
        {STRING_ROWING_MACHINE, &pic_rowing_machine_info, MIX_SPORT_ROWING_MACHINE},
        {STRING_SNOWMOBILE, &pic_snowmobile_info, MIX_SPORT_SNOWMOBILE},
        {STRING_SOFTBALL, &pic_softball_info, MIX_SPORT_SOFTBALL},
        //{STRING_TREADMILL, &pic_treadmills_info, MIX_SPORT_RUNNING_MACHINE},
        {STRING_TAI_CHI, &pic_tai_cai_info, MIX_SPORT_TAI_CAI},
        // 45
        {STRING_TABLE_TENNIS, &pic_pingpong_info, MIX_SPORT_PINGPONG},
        {STRING_WATER_POLO1, &pic_water_polo_info, MIX_SPORT_WATER_POLO},
        {STRING_STREET_DANCE, &pic_street_dance_info, MIX_SPORT_STREET_DANCE},
        {STRING_SAILING, &pic_sailing_info, MIX_SPORT_SAILING},
        {STRING_PADDLE_BOARDING, &pic_paddle_boarding_info, MIX_SPORT_PADDLE_BOARDING},
        // 50
        {STRING_WATER_SKIING, &pic_water_skiing_info, MIX_SPORT_WATER_SKIING},
        {STRING_KAYAKING, &pic_kayaking_info, MIX_SPORT_KAYAKING},
        {STRING_RAFTING, &pic_rafting_info, MIX_SPORT_RAFTING},
        {STRING_POWERBOATING, &pic_powerboating_info, MIX_SPORT_POWERBOATING},
        {STRING_FINSWIMMING, &pic_finswimming_info, MIX_SPORT_FINSWIMMING},
        // 55
        {STRING_ARTISTIC_SWIMMING, &pic_artistic_swimming_info, MIX_SPORT_ARTISTIC_SWIMMING},
        {STRING_KITESURFNG, &pic_kitesurfng_info, MIX_SPORT_KITESURFNG},
        {STRING_OPEN_SWIM, &pic_open_swim_info, MIX_SPORT_OPEN_SWIM},
        //{STRING_SKATRBOARDING, &pic_long_jump_info, MIX_SPORT_SKATRBOARDING},
        {STRING_PARKOUT, &pic_parkout_info, MIX_SPORT_PARKOUT},
        // 60
        {STRING_ATV, &pic_atv_info, MIX_SPORT_ATV},
        {STRING_PARAGLIDING, &pic_paragliding_info, MIX_SPORT_PARAGLIDING},
        {STRING_OUTDOOR_RUNNING, &pic_marathon_info, MIX_SPORT_OUTDOOR_RUNNING},
        {STRING_KABADDI, &pic_kabaddi_info, MIX_SPORT_KABADDI},
        {STRING_STEPPER, &pic_treadmills_info, MIX_SPORT_TREADMILLS},
        // 65
        {STRING_FLEXIBILITY, &pic_flexibility_info, MIX_SPORT_FLEXIBILITY},
        {STRING_GYMNASTICS, &pic_gymnastics_info, MIX_SPORT_GYMNASTICS},
        {STRING_STRETCHING, &pic_stretching_info, MIX_SPORT_STRETCHING},
        {STRING_STRENGTH, &pic_strength_info, MIX_SPORT_STRENGTH},
        {STRING_PHYSICAL_TRAINING, &pic_physical_training_info, MIX_SPORT_PHYSICAL_TRAINING},
        // 70
        {STRING_DUMBBELLS, &pic_dumbbell_info, MIX_SPORT_DUMBBELL},
        {STRING_BARBELL, &pic_barbell_info, MIX_SPORT_BARBELL},
        {STRING_DEADLIFT, &pic_deadlift_info, MIX_SPORT_DEADLIFT},
        {STRING_SITUPS, &pic_situp_info, MIX_SPORT_SITUP},
        {STRING_BURPEE, &pic_Burpee_info, MIX_SPORT_BURPEE},
        // 75
        {STRING_BACK_EXERCISE, &pic_back_exercise_info, MIX_SPORT_BACK_EXERCISE},
        {STRING_ABS, &pic_abs_info, MIX_SPORT_ABS},
        {STRING_HIIT, &pic_hiit_info, MIX_SPORT_HIIT},
        {STRING_LNDOOR_WALKING, &pic_lndoor_walking_info, MIX_SPORT_LNDOOR_WALKING},
        {STRING_WEIGHLIFTING, &pic_weight_info, MIX_SPORT_WEIGHT},
        // 80
        {STRING_SQUARE_DANCING, &pic_square_dancing_info, MIX_SPORT_SQUARE_DANCING},
        {STRING_BELLY_DANCE, &pic_belly_dance_info, MIX_SPORT_BELLY_DANCE},
        {STRING_ZUMBA, &pic_zumba_info, MIX_SPORT_ZUMBA},
        {STRING_LATIN_DANCE, &pic_latin_dance_info, MIX_SPORT_LATIN_DANCE},
        {STRING_JAZZ_DANCE, &pic_jazz_dance_info, MIX_SPORT_JAZZ_DANCE},
        // 85
        {STRING_BOXING, &pic_boxing_info, MIX_SPORT_BOXING},
        {STRING_MUAY_THAI, &pic_Muay_Thai_info, MIX_SPORT_MUAY_THAI},
        {STRING_KARATE, &pic_karete_info, MIX_SPORT_KARETE},
        {STRING_HANDBALL, &pic_handball_info, MIX_SPORT_HANDBALL},
        {STRING_SHUTTLECOCK, &pic_shuttlecock_info, MIX_SPORT_SHUTTLECOCK},
        // 90
        {STRING_SPEAK_TAKRAW, &pic_speak_takraw_info, MIX_SPORT_SPEAK_TAKRAW},
        {STRING_LCE_HOCKEY, &pic_lce_hockey_info, MIX_SPORT_LCE_HOCKEY},
        {STRING_BOBSLEIGH, &pic_bobsleigh_info, MIX_SPORT_BOBSLEIGH},
        {STRING_SLEDDING, &pic_sled_info, MIX_SPORT_SLED},
        {STRING_TUG_OF_WAR, &pic_tug_of_war_info, MIX_SPORT_TUG_OF_WAR},
        // 95
        {STRING_HOUSE_RIDING, &pic_house_riding_info, MIX_SPORT_HOUSE_RIDING},
        {STRING_FISHING, &pic_fishing_info, MIX_SPORT_FISHING},
        {STRING_EQUESTRIAN_SPORTS, &pic_equestrian_info, MIX_SPORT_EQUESTRIAN},
        {STRING_ATHLETICS, &pic_athletics_info, MIX_SPORT_ATHLETICS},
        {STRING_AUTO_RACING, &pic_auto_racing_info, MIX_SPORT_AUTO_RACING},
        // 100
        {STRING_AEROBICS, &pic_aerobics_info, MIX_SPORT_AEROBICS},
        {STRING_ELLIPTICALMACHINE, &pic_ellipticalmachine_info, MIX_SPORT_ELLIPTICALMACHINE},
        {STRING_GOALBALL, &pic_goalball_info, MIX_SPORT_GOALBALL},
        {STRING_GOLF, &pic_golf_info, MIX_SPORT_GOLF},
        {STRING_HURDLE, &pic_hurdle_info, MIX_SPORT_HURDLE},
        // 105
        {STRING_CYCLING_INDOOR, &pic_cycling_indoor_info, MIX_SPORT_CYCLING_INDOOR},
        {STRING_RUNNING_MACHINE, &pic_running_machine_info, MIX_SPORT_RUNNING_MACHINE},
        {STRING_BIATHION, &pic_Biathlon_info, MIX_SPORT_BIATHION_WINTER},
        {STRING_PILATES, &pic_pilates_info, MIX_SPORT_PILATES},
        {STRING_SQUASH, &pic_squash_info, MIX_SPORT_SQUASH},
        // 110
        {STRING_STAIR_CLIMBER, &pic_climb_stairs_info, MIX_SPORT_CLIMB_STAIRS},
        {STRING_TENNIS, &pic_tennis_info, MIX_SPORT_TENNIS}, // ����
        {STRING_SKATRBOARDING, &pic_skatrboarding_info, MIX_SPORT_SKATRBOARDING},
        {STRING_KENDO, &pic_kendo_info, MIX_SPORT_KENDO},
        {STRING_TRIATHLON, &pic_triathlon_info, MIX_SPORT_TRIATHLON},
        // 115
        {STRING_RUGBY, &pic_rugby_info, MIX_SPORT_RUGBY}, // �����
        {STRING_ROWING, &pic_rowing_info, MIX_SPORT_ROWING},
        {STRING_FENCING, &pic_Fencing_info, MIX_SPORT_FENCING},             // Fencing
        {STRING_DRAGON_BOAT, &pic_dragon_boat_info, MIX_SPORT_DRAGON_BOAT}, // ����
        {STRING_DANCE, &pic_dance_info, MIX_SPORT_DANCE},
        // 120
};

static const int SPORT_LIST_NUM = (sizeof(sport_window_list_info) / sizeof(sport_window_list_info[0]));

static unsigned int sport_list_get_count(void)
{
    return SPORT_LIST_NUM;
}

static const gui_layout_list_struct gui_window_sport_list_layout =
    {
        .row_height = 76,

        .top = 43,
        .bottom = 43,
        .space = 10,

        .scroll = 1,
        .auto_start = 1,

        .arc_flag = 1,
        .zoom_flag = 1,
        .arc_radius = LCD_SIZE_WIDTH,
        .zoom_radius = LCD_SIZE_WIDTH,
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
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 40,
        .y = 0,
};

static gui_font_struct gui_text_sport_dance =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .x = 130,
        .y = 10,
        .align = GUI_ALIGN_VCENTER,
        .value_align = GUI_ALIGN_VCENTER,
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
        .value.string_id = STRING_DANCE,
};

static const gui_mix_struct gui_item_dance[] =
    {
        {
            .data = &gui_pic_sport_dance,
        },
        {
            .data = &gui_text_sport_dance,
        },
};

static const gui_widget_struct gui_sport_info =
    {
        .id = 0,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = 76,
        .visible = 1,
        .child_num = 2,
        .children = gui_item_dance,
};

/*-----------------------------ϵͳ�¼�--------------------------------------*/
static void app_sport_list_refresh()
{
    unsigned int box_num, box_idx;

    // geg box_number
    box_num = sport_list_get_count();

    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_sportlist);
    gui_surface_layout_listview_dynamic_init(surface);
    //gui_surface_layout_listview_clear_item_box(surface);

    if (surface != NULL)
    {
        for (box_idx = 0; box_idx < box_num; box_idx++)
        {
            unsigned int id = sport_window_list_info[box_idx].id;
            gui_box_struct *box = gui_surface_layout_listview_dynamic_get_box(surface, id); //gui_surface_cache_add_box();
            if (box != NULL)
            {
                box->id = id;
                box->type = TYPE_GUI_CONTROL_LAYOUT_ITEM;
                box->widget = &gui_sport_info;
                box->visible = 1;

                // set icons
                gui_pic_sport_dance.data = sport_window_list_info[box_idx].pic;
                gui_text_sport_dance.value.string_id = sport_window_list_info[box_idx].string;

                gui_surface_layout_listview_dynamic_add_item(surface, box);
            }
        }
        gui_surface_layout_listview_dynamic_finish(surface);
    }
}

/*-----------------------------ϵͳ�¼�--------------------------------------*/

static void app_window_sport_list_init(void *buf)
{
}

static void app_window_sport_list_load(void *buf)
{
    gui_surface_struct *surface = gui_surface_get_surface(&gui_screen_sportlist);
    gui_surface_layout_listview_dynamic_create(surface, app_sport_list_refresh);

    // application_titlebar_create(&app_window_sport_data, STRING_SPORT);
}

static void app_window_sport_list_entry(void *buf)
{
}

static void app_window_sport_list_exit()
{
}

static void app_window_sport_list_destroy()
{
}

/*-----------------------------��Ӧ�¼�--------------------------------------*/
static void app_window_sport_list_touch_event_click_on_layout_item(gui_click_layout_struct *event)
{
    SYS_DEBUG("app_window_test1_touch_event_click_on_layout_item x=%d y=%d index=%d", event->x, event->y, event->index);

    save_sport_type = (MIX_SPORT_TYPE)event->id;
    sport_status_set(SPORT_STATUS_START);
    application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_sport_data, NULL);
}

/*-----------------------------����--------------------------------------*/
static void app_window_sport_long_touch_handler(gui_click_struct *event)
{
    // SYS_DEBUG("window_sport_touch longpress");
    // if (is_exist_widget_app(APP_INFO_ID_SPO RT)) {
    //     application_switch(GUI_WINDOW_SWITCH_TYPE_REPLACE, &app_window_widget_delete, (void*)APP_INFO_ID_SPORT);
    // }
}

static void app_window_sportlist_view_rolkey_handler(void *buf)
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

static const gui_touch_event_struct app_window_sport_list_touch_events[] =
    {
        {
            .id = 0xFFFF, // fullscreen.
            .long_touch = app_window_sport_long_touch_handler,
        },
};

static const app_window_event_struct app_window_sportlist_events[] =
    {
        {
            .id = EVENT_ROLKEY,
            .handler = app_window_sportlist_view_rolkey_handler,
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

        /*�Ű��������Ӧ����¼�*/
        .click_on_layout_item = app_window_sport_list_touch_event_click_on_layout_item,

        .touch_event_num = countof(app_window_sport_list_touch_events),
        .touch_events = app_window_sport_list_touch_events,

        .event_num = countof(app_window_sportlist_events),
        .events = app_window_sportlist_events,
};
