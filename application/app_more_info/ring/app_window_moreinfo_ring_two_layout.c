#include "app_window_moreinfo_ring_two_layout.h"
#include "application_config_app_info.h"
#include "picture.h"

//
// #define APP_RING_PICS(name)    { \
//                       	&pic_app_##name##_60_info,&pic_app_##name##_60_info, &pic_app_##name##_60_info, &pic_app_##name##_60_info, \
//                        &pic_app_##name##_60_info,&pic_app_##name##_60_info, &pic_app_##name##_60_info}
//

#define DEF_CELL_PICS(u_name, l_name) static const picture_info_struct *const gui_cellular_##u_name[] = APP_PICS(l_name)

#define ADD_CELL_ITEM(u_name, l_name)                \
    {                                                \
        .id = APP_INFO_ID_##u_name,                  \
        .type = TYPE_GUI_CONTROL_LAYOUT_CELL,        \
        .anchor_x = ANCHOR_VALUE(0.5f),              \
        .anchor_y = ANCHOR_VALUE(0.5f),              \
        .visible = 1,                                \
        .child_num = countof(gui_cellular_##u_name), \
        .children = gui_cellular_##u_name,           \
        .scale = 1.05f,                               \
    }

DEF_CELL_PICS(MESSAGE, message);
DEF_CELL_PICS(WEATHER, weather);
DEF_CELL_PICS(HR, hr);
DEF_CELL_PICS(BREATHE, breath);
DEF_CELL_PICS(CALL, telephone);
DEF_CELL_PICS(SPORT, sport_outdoor);
DEF_CELL_PICS(CLACULATOR, calc);
DEF_CELL_PICS(SIRI, siri);
DEF_CELL_PICS(PHOTO, photograph);
DEF_CELL_PICS(O2, O2);
DEF_CELL_PICS(SETTING, setting);
DEF_CELL_PICS(STOPWATCH, stopwatch);
DEF_CELL_PICS(ALIPAY, alipay);
DEF_CELL_PICS(GAME, game);
DEF_CELL_PICS(SLEEP, sleep);
DEF_CELL_PICS(BLOOD, BP);
DEF_CELL_PICS(COUNTER, counter);
DEF_CELL_PICS(QR_PUSH, qr_push);

#define RT_ANI_TIME_GAP (200)

static const gui_image_struct gui_ani_ring_two[] =
    {
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 0,
            .y = 0,
            .data = &pic_bg_gif_1_001_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = LCD_SIZE_HALF_WIDTH,
            .y = 0,
            .data = &pic_bg_gif_1_003_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = 0,
            .y = LCD_SIZE_HALF_HEIGHT,
            .data = &pic_bg_gif_1_002_info,
        },
        {
            .type = TYPE_GUI_DRAW_PICTURE,
            .x = LCD_SIZE_HALF_WIDTH,
            .y = LCD_SIZE_HALF_HEIGHT,
            .data = &pic_bg_gif_1_004_info,
        },
};

static const gui_font_struct gui_text_more_info_ring =
    {
        .type = TYPE_GUI_DRAW_TEXT,
        .align = GUI_ALIGN_NONE,
        .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
        .color = COLOR_RGB(255, 255, 255),
        .size = SYS_FONT_MEDIUM,
        .value_type = GUI_FONT_VALUE_TYPE_STRING,
        .value.string = "",
};

static const gui_image_struct gui_more_info_ring_home =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .data = &pic_style_ring_home_info,
};

static const gui_image_struct gui_more_info_ring_ind =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .data = &pic_more_ring_ind_info,
};

#define MOREINFO_RING_RADIUS 180

static const gui_widget_struct gui_widget_more_info_ring_list[] =
    {
        {
            .id = RING_LAYOUT_ID_BG_ANI,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 0,
            .y = 0,
            .width = LCD_SIZE_WIDTH,
            .height = LCD_SIZE_HEIGHT,
            .visible = 1,
            .child_num = countof(gui_ani_ring_two),
            .children = gui_ani_ring_two,
        },

        ADD_CELL_ITEM(HR, hr),
        ADD_CELL_ITEM(BREATHE, breath),
        ADD_CELL_ITEM(SPORT, sport_outdoor),
        ADD_CELL_ITEM(SLEEP, sleep),
        ADD_CELL_ITEM(O2, O2),
        ADD_CELL_ITEM(BLOOD, BP),
        ADD_CELL_ITEM(COUNTER, counter),
        ADD_CELL_ITEM(STOPWATCH, stopwatch),
        ADD_CELL_ITEM(SIRI, siri),
        ADD_CELL_ITEM(MESSAGE, msg),

        ADD_CELL_ITEM(WEATHER, watchface),
        ADD_CELL_ITEM(CLACULATOR, calc),
        ADD_CELL_ITEM(CALL, telephone),
        ADD_CELL_ITEM(GAME, game),

        ADD_CELL_ITEM(PHOTO, photograph),
        ADD_CELL_ITEM(SETTING, setting),
        ADD_CELL_ITEM(ALIPAY, alipay),
        ADD_CELL_ITEM(QR_PUSH, qr_push),

        {
            .id = RING_LAYOUT_ID_TEXT,
            .type = TYPE_GUI_CONTROL_LABEL,
            .x = 102,
            .y = LCD_SIZE_HALF_HEIGHT - 20,
            .width = 240,
            .height = 40,
            .visible = 1,
            .clip = 1,
            .child_num = 1,
            .children = &gui_text_more_info_ring,
        },

        {
            .id = RING_LAYOUT_ID_HOMECELL,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = LCD_SIZE_HALF_WIDTH - MOREINFO_RING_RADIUS - 47,
            .y = LCD_SIZE_HALF_HEIGHT - 47,
            .width = 94,
            .height = 94,
            .visible = 1,
            .child_num = 1,
            .children = &gui_more_info_ring_home,
        },

        {
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 320,
            .y = 206,
            .width = 37,  // 22,
            .height = 54, // 24,
            .visible = 1,
            .child_num = 1,
            .children = &gui_more_info_ring_ind,
        },
};

static const gui_layout_ring_struct gui_more_info_ring_layout_config =
    {
        .mBaseAng = 0, // 焦点项所对应的角度 ...
        .mId = 0,      // 当前焦点的box-id
        .mIndex = 0,   // 当前焦点的序号
        .mPenDn = 0,   // Pen down handle flag.
        .mZoom = 0,    // zoom flag, 图标是否要进行缩放

        .mRadius = MOREINFO_RING_RADIUS, // 组件半径，图标中心点圆周
        .mAngGap = 36,                   //
        .mAngVal = 0,                    // current-ang
        .mSith = 0,                      //

        .c_x = LCD_SIZE_HALF_WIDTH,  // 圆心 x 坐标 ...
        .c_y = LCD_SIZE_HALF_HEIGHT, // 圆心 y 坐标 ...

        // for zoom
        .c_bias_x = 0, // 偏置圆心 x 距离....

        //.cfg_zoom_map   = gui_more_info_ring_cfg_zoom_map,
        //.cfg_pos_map    = gui_more_info_ring_cfg_pos_map,
        //.cfg_map_size   = countof(gui_more_info_ring_cfg_zoom_map),

        .auto_start = 1,
};

const gui_screen_struct gui_screen_moreinfo_ring_two =
    {
        .type = TYPE_GUI_LAYOUT_RING,
        .space_x = 0,
        .space_y = 0,
        .order = 0,
        .children = gui_widget_more_info_ring_list,
        .child_num = countof(gui_widget_more_info_ring_list),
        .layout_config = &gui_more_info_ring_layout_config,
};
