#include "app_window_sportlist_layout.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_animation.h"
#include "app_window_sportlist_layout.h"
#include "data_common.h"

#if 0
static const gui_image_struct gui_pic_sport_TIP_BG =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_tip_bg_info,
};

/*static const gui_image_struct gui_pic_sport_set =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 0,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_set_info,
};*/

//RUN
static const gui_image_struct gui_pic_sport_run =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_running_info,
};

static const gui_font_struct gui_text_sport_run =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_RUN,
};


static const gui_mix_struct gui_item_run[] =
{
	{
		.data = &gui_pic_sport_run,
	},
	{
		.data = &gui_text_sport_run,
	},

};

//WALK
static const gui_image_struct gui_pic_sport_walk =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_walking_info,
};

static const gui_font_struct gui_text_sport_walk =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_WALK,
};


static const gui_mix_struct gui_item_wakl[] =
{
	{
		.data = &gui_pic_sport_walk,
	},
	{
		.data = &gui_text_sport_walk,
	},
};


//CYCING
static const gui_image_struct gui_pic_sport_cycling =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_cycling_info,
};

static const gui_font_struct gui_text_sport_cycling =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_CYCLING,
};


static const gui_mix_struct gui_item_cycing[] =
{
	{
		.data = &gui_pic_sport_cycling,
	},
	{
		.data = &gui_text_sport_cycling,
	},
};


//Climb
static const gui_image_struct gui_pic_sport_climb =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_Mountain_climbing_info,
};

static const gui_font_struct gui_text_sport_climb =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_CLIMB,
};


static const gui_mix_struct gui_item_climb[] =
{
	{
		.data = &gui_pic_sport_climb,
	},
	{
		.data = &gui_text_sport_climb,
	},
};


//YOGA
static const gui_image_struct gui_pic_sport_yoga =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_yoga_info,
};

static const gui_font_struct gui_text_sport_yoga =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_YOGA,
};


static const gui_mix_struct gui_item_yoga[] =
{
	{
		.data = &gui_pic_sport_yoga,
	},
	{
		.data = &gui_text_sport_yoga,
	},

};


//BASKETBALL
static const gui_image_struct gui_pic_sport_basketball =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_basketball_info,
};

static const gui_font_struct gui_text_sport_basketball =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_BASKETBALL,
};


static const gui_mix_struct gui_item_basketball[] =
{
	{
		.data = &gui_pic_sport_basketball,
	},
	{
		.data = &gui_text_sport_basketball,
	},
};


//football
static const gui_image_struct gui_pic_sport_football =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_football_info,
};

static const gui_font_struct gui_text_sport_football =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_FOOTBALL,
};


static const gui_mix_struct gui_item_football[] =
{
	{
		.data = &gui_pic_sport_football,
	},
	{
		.data = &gui_text_sport_football,
	},
};

//badminton
static const gui_image_struct gui_pic_sport_badminton =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_badminton_info,
};

static const gui_font_struct gui_text_sport_badminton =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_BADMINTON,
};


static const gui_mix_struct gui_item_badminton[] =
{
	{
		.data = &gui_pic_sport_badminton,
	},
	{
		.data = &gui_text_sport_badminton,
	},
};


//skip
static const gui_image_struct gui_pic_sport_skip =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_Jump_rope_info,
};

static const gui_font_struct gui_text_sport_skip =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_SKIP,
};


static const gui_mix_struct gui_item_skip[] =
{
	{
		.data = &gui_pic_sport_skip,
	},
	{
		.data = &gui_text_sport_skip,
	},
};



//swim
static const gui_image_struct gui_pic_sport_swim =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 20,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_sport_swimming_info,
};

static const gui_font_struct gui_text_sport_swim =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.id = 0,
	.x = 80,
    .y = 0,
    .anchor_x = 0,
    .anchor_y = 0,
    .max_width = 0,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
	.auto_wrap = 0,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_SPORT_SWIM,
};


static const gui_mix_struct gui_item_swim[] =
{
	{
		.data = &gui_pic_sport_swim,
	},
	{
		.data = &gui_text_sport_swim,
	},
};



static const gui_widget_struct gui_widget_sportlist[] =
{

	{
		.id = MIX_SPORT_RUN,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 0,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_run),
		.children = gui_item_run,
	},
	{
		.id = MIX_SPORT_WALK,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 0,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_wakl),
		.children = gui_item_wakl,

	},
	
	{
		.id = MIX_SPORT_CYCLING,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 32,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_cycing),
		.children = gui_item_cycing,
	},
	
	{
		.id = MIX_SPORT_CLIMBING,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 32,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_climb),
		.children = gui_item_climb,
	},
	
	{
		.id = MIX_SPORT_YOGA,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 32,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_yoga),
		.children = gui_item_yoga,
	},
	
	{
		.id = MIX_SPORT_BASKETBALL,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 32,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_basketball),
		.children = gui_item_basketball,
	},
	
	{
		.id = MIX_SPORT_FOOTBALL,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 32,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_football),
		.children = gui_item_football,
	},
	
	{
		.id = MIX_SPORT_BADMINTON,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 32,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_badminton),
		.children = gui_item_badminton,
	},
	
	
	{
		.id = MIX_SPORT_SKIP,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 32,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_skip),
		.children = gui_item_skip,
	},
	
	{
		.id = MIX_SPORT_SWIM,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.x = 0,
		.y = 32,
		.width = 240,
		.height = 51,
		.rotate = 0,
		.visible= 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = countof(gui_item_swim),
		.children = gui_item_swim,
	},
	{
		.id = SPORT_LAYOUT_ID_TIP_BG,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.x = 0,
		.y = 0,
		.width = 240,
		.height = 30,
		.rotate = 0,
		.visible = 1,
		.clip = 0,
		.space_x = 0,
		.space_y = 0,
		.child_num = 1,
		.children = &gui_pic_sport_TIP_BG,
	},
};


const gui_layout_list_struct gui_layout_list_sport =
{
	/*-----�Զ�����-------*/
	.total = 0,		//���ж�����
	.height = 0,		//�߶�

	.row_height = 51,	//�����ĸ߶�
	
	.top = 35,		//�����Ŀ�ȱ
	.bottom = 20,	//�ײ��Ŀ�ȱ
	.space = 20,  	//������֮��ļ�϶
	
	.scroll = 1,//�Ƿ�������¹���	
};


const gui_screen_struct gui_screen_sportlist =
{
	.type = TYPE_GUI_LAYOUT_LIST,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_sportlist,
	.child_num = countof(gui_widget_sportlist),
	.layout_config = &gui_layout_list_sport,
};
#endif

