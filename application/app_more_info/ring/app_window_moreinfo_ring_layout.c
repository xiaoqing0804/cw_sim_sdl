#include "app_window_moreinfo_ring_layout.h"
#include "application_config_app_info.h"
#include "picture.h"


#define DEF_CELL_PICS(u_name, l_name)  static const picture_info_struct* const gui_cellular_##u_name[] = APP_PICS(l_name)

#define ADD_CELL_ITEM(u_name, l_name)                \
    {                                                \
        .id = APP_INFO_ID_##u_name,                  \
        .type = TYPE_GUI_CONTROL_LAYOUT_CELL,        \
        .anchor_x = ANCHOR_VALUE(0.5f),              \
        .anchor_y = ANCHOR_VALUE(0.5f),              \
        .visible = 1,                                \
        .child_num = countof(gui_cellular_##u_name), \
        .children = gui_cellular_##u_name,           \
    }

DEF_CELL_PICS(HR, hr);
DEF_CELL_PICS(O2, O2);
DEF_CELL_PICS(MESSAGE, message);
DEF_CELL_PICS(WEATHER, weather);
DEF_CELL_PICS(BREATHE, breath);
DEF_CELL_PICS(CALL, telephone);
DEF_CELL_PICS(SPORT, sport_outdoor);
DEF_CELL_PICS(CLACULATOR, calc);
DEF_CELL_PICS(SIRI, siri);
DEF_CELL_PICS(PHOTO, photograph);
DEF_CELL_PICS(SETTING, setting);
DEF_CELL_PICS(STOPWATCH, stopwatch);


static const gui_image_struct gui_more_info_ring_bg =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_NONE,
    .data = &pic_more_ring_bg_1_info,
};


static const gui_font_struct gui_text_more_info_ring =
{
	.type = TYPE_GUI_DRAW_TEXT,
    .value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_VCENTER),
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING,
    .value.string = "",
};


static const gui_widget_struct gui_widget_more_info_ring_list[] =
{
	//BG
  	{
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 130,
        .y = 190 + 30,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = 1,
        .children = &gui_more_info_ring_bg,
    },


    ADD_CELL_ITEM(HR, hr),
    ADD_CELL_ITEM(O2, O2),
    ADD_CELL_ITEM(MESSAGE, msg),
    ADD_CELL_ITEM(WEATHER, watchface),
    ADD_CELL_ITEM(BREATHE, breath),
    ADD_CELL_ITEM(CALL, telephone),
    ADD_CELL_ITEM(SPORT, sport_outdoor),
    ADD_CELL_ITEM(CLACULATOR, calc),
    ADD_CELL_ITEM(SIRI, siri),
    ADD_CELL_ITEM(PHOTO, photograph),
    ADD_CELL_ITEM(SETTING, setting),
    ADD_CELL_ITEM(STOPWATCH, stopwatch),
	{
		.id = RING_LAYOUT_ID_TEXT,
		.type = TYPE_GUI_CONTROL_LABEL,
		.x = 145,
		.y = 190 + 20,
		.width = 220,
		.height = 34,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_text_more_info_ring,
	},
};

/*
static const float gui_more_info_ring_cfg_zoom_map[] =
{
    1.1f,  1.0f,    0.9787f,   0.9362f,   0.8085f,   0.74468f,   0.6383f,   0.5106f,     0.5f
};

static const float gui_more_info_ring_cfg_pos_map[] = {
    0,      48,     82,         136,        228,        285,        338,        384,        LCD_SIZE_WIDTH+10
};
*/

static const gui_layout_ring_struct gui_more_info_ring_layout_config =
{
    .mBaseAng = 180,  // 焦点项所对应的角度 ...
    .mId = 0,       // 当前焦点的box-id
    .mIndex = 0,    // 当前焦点的序号
    .mPenDn = 0,    // Pen down handle flag.
    .mZoom  = 1,     // zoom flag, 图标是否要进行缩放

    .mRadius = 170,       // 组件半径，图标中心点圆周
    .mAngGap = 0,       //
    .mAngVal = 0,       // current-ang
    .mSith = 0,     //

    .c_x = LCD_SIZE_HALF_WIDTH,       // 圆心 x 坐标 ...
    .c_y = LCD_SIZE_HALF_HEIGHT,       // 圆心 y 坐标 ...

    // for zoom
    .c_bias_x = -70,    // 偏置圆心 x 距离....

    //.cfg_zoom_map   = gui_more_info_ring_cfg_zoom_map,
    //.cfg_pos_map    = gui_more_info_ring_cfg_pos_map,
    //.cfg_map_size   = countof(gui_more_info_ring_cfg_zoom_map),
};


const gui_screen_struct gui_screen_moreinfo_ring =
{
	.type = TYPE_GUI_LAYOUT_RING,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_more_info_ring_list,
	.child_num = countof(gui_widget_more_info_ring_list),
	.layout_config = &gui_more_info_ring_layout_config,
};



