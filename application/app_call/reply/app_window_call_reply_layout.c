
#include "app_window_call_reply_layout.h"

#define SMS_REPLAY_TEXT_X  (LCD_SCALE_WIDTH*50)
#define SMS_REPLAY_ITME_Y  (GUI_TITLE_BAR_HEIGHT)
#define SMS_REPLAY_ITME_H  (LCD_SCALE_HEIGHT*77)
#define SMS_REPLAY_ITME_GAP (LCD_SCALE_HEIGHT*13)

//****************************************************call reply****************************************************//
/*static const gui_image_struct gui_widget_setting_personnal_bg =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .x = 0,
        .y = 0,
        .data = &pic_sys_replay_bg_info,
};*/

static const gui_font_struct gui_text_reply_1 =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.scroll = 1,
	.x = SMS_REPLAY_TEXT_X,
	.y = 0,
	.width = LCD_SIZE_WIDTH-2*SMS_REPLAY_TEXT_X,
	.height = SMS_REPLAY_ITME_H,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_REPLY_TYPE_1,
};

static const gui_mix_struct gui_widget_sys_replay_1[] =
    {
        /*{
            .data = &gui_widget_setting_personnal_bg,
        },*/
        {
            .data = &gui_text_reply_1,
        },
};

static const gui_font_struct gui_text_reply_2 =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.scroll = 1,
	.x = SMS_REPLAY_TEXT_X,
	.y = 0,
	.width = LCD_SIZE_WIDTH-2*SMS_REPLAY_TEXT_X,
	.height = SMS_REPLAY_ITME_H,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_REPLY_TYPE_2,
};

static const gui_mix_struct gui_widget_sys_replay_2[] =
    {
        /*{
            .data = &gui_widget_setting_personnal_bg,
        },*/
        {
            .data = &gui_text_reply_2,
        },
};

static const gui_font_struct gui_text_reply_3 =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.scroll = 1,
	.x = SMS_REPLAY_TEXT_X,
	.y = 0,
	.width = LCD_SIZE_WIDTH-2*SMS_REPLAY_TEXT_X,
	.height = SMS_REPLAY_ITME_H,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_REPLY_TYPE_3,
};

static const gui_mix_struct gui_widget_sys_replay_3[] =
    {
        /*{
            .data = &gui_widget_setting_personnal_bg,
        },*/
        {
            .data = &gui_text_reply_3,
        },
};

static const gui_font_struct gui_text_reply_4 =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.scroll = 1,
	.x = SMS_REPLAY_TEXT_X,
	.y = 0,
	.width = LCD_SIZE_WIDTH-2*SMS_REPLAY_TEXT_X,
	.height = SMS_REPLAY_ITME_H,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_REPLY_TYPE_4,
};

static const gui_mix_struct gui_widget_sys_replay_4[] =
    {
        /*{
            .data = &gui_widget_setting_personnal_bg,
        },*/
        {
            .data = &gui_text_reply_4,
        },
};

static const gui_font_struct gui_text_reply_5 =
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_LEFT , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.scroll = 1,
	.x = SMS_REPLAY_TEXT_X,
	.y = 0,
	.width = LCD_SIZE_WIDTH-2*SMS_REPLAY_TEXT_X,
	.height = SMS_REPLAY_ITME_H,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_REPLY_TYPE_5,
};

static const gui_mix_struct gui_widget_sys_replay_5[] =
    {
        /*{
            .data = &gui_widget_setting_personnal_bg,
        },*/
        {
            .data = &gui_text_reply_5,
        },
};



static const gui_widget_struct gui_call_reply_widget[] =
{
	{
		.id = REPLY_TYPE_ID_1,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.clip = 1,
		.x = 0,
		.y = SMS_REPLAY_ITME_Y,
		.width = LCD_SIZE_WIDTH,
		.height = SMS_REPLAY_ITME_H,
		.visible= 1,
		.child_num = countof(gui_widget_sys_replay_1),
		.children = gui_widget_sys_replay_1,
	},

	{
		.id = REPLY_TYPE_ID_2,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.clip = 1,
		.x = 0,
		.y = SMS_REPLAY_ITME_Y+(SMS_REPLAY_ITME_H+SMS_REPLAY_ITME_GAP),
		.width = LCD_SIZE_WIDTH,
		.height = SMS_REPLAY_ITME_H,
		.visible= 1,
		.child_num = countof(gui_widget_sys_replay_2),
		.children = gui_widget_sys_replay_2,
	},

	{
		.id = REPLY_TYPE_ID_3,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.clip = 1,
		.x = 0,
		.y = SMS_REPLAY_ITME_Y+(SMS_REPLAY_ITME_H+SMS_REPLAY_ITME_GAP)*2,
		.width = LCD_SIZE_WIDTH,
		.height = SMS_REPLAY_ITME_H,
		.visible= 1,
		.child_num = countof(gui_widget_sys_replay_3),
		.children = gui_widget_sys_replay_3,
	},
	{
		.id = REPLY_TYPE_ID_4,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.clip = 1,
		.x = 0,
		.y = SMS_REPLAY_ITME_Y+(SMS_REPLAY_ITME_H+SMS_REPLAY_ITME_GAP)*3,
		.width = LCD_SIZE_WIDTH,
		.height = SMS_REPLAY_ITME_H,
		.visible= 1,
		.child_num = countof(gui_widget_sys_replay_4),
		.children = gui_widget_sys_replay_4,
	},

	{
		.id = REPLY_TYPE_ID_5,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.clip = 1,
		.x = 0,
		.y = SMS_REPLAY_ITME_Y+(SMS_REPLAY_ITME_H+SMS_REPLAY_ITME_GAP)*4,
		.width = LCD_SIZE_WIDTH,
		.height = SMS_REPLAY_ITME_H,
		.visible= 1,
		.child_num = countof(gui_widget_sys_replay_5),
		.children = gui_widget_sys_replay_5,
	},
};

static const gui_layout_scroll_struct gui_layout_scroll_replay =
    {
        .height = SMS_REPLAY_ITME_Y+(SMS_REPLAY_ITME_H+SMS_REPLAY_ITME_GAP)*5+SMS_REPLAY_ITME_GAP,
        .scroll = 1,
};

const gui_screen_struct app_call_reply_screen =
{
	.type = TYPE_GUI_LAYOUT_SCROLL,
	.children = gui_call_reply_widget,
	.child_num = countof(gui_call_reply_widget),
	.layout_config = &gui_layout_scroll_replay,
};
//****************************************************call reply****************************************************//

