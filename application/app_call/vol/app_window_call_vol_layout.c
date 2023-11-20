
#include "app_window_call_vol_layout.h"

//****************************************************call vol****************************************************//
static const gui_image_struct gui_call_volup_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_up_info,
};

static const gui_image_struct gui_call_voldn_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_down_info,
};


// vol-bg
static const gui_image_struct gui_call_vol_bg_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_bg_info,
};

static const gui_image_struct gui_call_vol_ind_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_call_vol_top_info,
};



static const gui_widget_struct gui_call_vol_widget[] =
{



    {   // vol - bg
        .id = CALL_LAYOUT_VOLBG_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 173,
        .y = 53,
        .width = 120,
        .height = 360,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_vol_bg_image,
    },

    {   // vol - ind
        .id = CALL_LAYOUT_VOLIND_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 173,    // 16+52,
        .y = 56,   // 326+22,
        .width = 120,
        .height = 360,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_vol_ind_image,
    },

    {   // vol - up
        .id = CALL_LAYOUT_VOLUP_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 205,
        .y = 73,
        .width = 56,
        .height = 56,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_volup_image,
    },

    {   // vol - dn
        .id = CALL_LAYOUT_VOLDN_ID,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 205,
        .y = 337,
        .width = 56,
        .height = 56,
        .visible= 1,
        .child_num = 1,
        .children = &gui_call_voldn_image,
    },
};

const gui_screen_struct gui_screen_call_vol =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.order = 0,
	.children = gui_call_vol_widget,
	.child_num = countof(gui_call_vol_widget),
};
//****************************************************call vol****************************************************//
