

#include "sys_init.h"
#include "data_common.h"
#include "bsp_includes.h"

#include "gui_surface_box_label.h"
#include "data_receive_package.h"
#include "gui_surface_box_image.h"

#include "app_window_game_2048.h"
#include "app_window_game_dadishu.h"
#include "app_window_games_list.h"

enum {
    GAME_ITEM_2048 = 10,
    GAME_ITEM_DADISHU,
};


static const gui_image_struct gui_pic_game_2048_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 90,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_game_2048_info
};


static const gui_font_struct gui_text_game_2048_name =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .x = 150,
    .y = 45,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_GAME_2048,
};


static const gui_mix_struct gui_item_game_2048[] =
{
    { .data = &gui_pic_game_2048_icon },
    { .data = &gui_text_game_2048_name },
};

static const gui_image_struct gui_pic_game_dadishu_icon =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.id = 0,
	.x = 90,
	.y = 0,
	.anchor_x = 0,
	.anchor_y = 0,
	.data = &pic_game_dadishu_info
};


static const gui_font_struct gui_text_game_dadishu_name =
{
    .type = TYPE_GUI_DRAW_TEXT,
    .x = 150,
    .y = 60,
    .align = GUI_ALIGN_VCENTER,
    .value_align = GUI_ALIGN_VCENTER,
    .color = COLOR_RGB(255, 255, 255),
    .size = SYS_FONT_MEDIUM,
    .value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
    .value.string_id = STRING_GAME_DADISHU,
};


static const gui_mix_struct gui_item_game_dadishu[] =
{
    { .data = &gui_pic_game_dadishu_icon },
    { .data = &gui_text_game_dadishu_name },
};



static const gui_widget_struct gui_widget_games_list[] =
{
	{
		.id = GAME_ITEM_2048,
		.type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
		.width = LCD_SIZE_WIDTH,
		.height = 51,
		.visible= 1,
		.child_num = countof(gui_item_game_2048),
		.children = gui_item_game_2048,
	},
    {
        .id = GAME_ITEM_DADISHU,
        .type = TYPE_GUI_CONTROL_LAYOUT_ITEM,
        .width = LCD_SIZE_WIDTH,
        .height = 51,
        .visible= 1,
        .child_num = countof(gui_item_game_dadishu),
        .children = gui_item_game_dadishu,
    },
};


const gui_layout_list_struct gui_layout_games_list =
{
	.row_height = 80,	//单条的高度

	.top = 45,		//顶部的空缺
	.bottom = 20,	//底部的空缺
	.space = 50,  	//条与条之间的间隙

	.scroll = 0,//是否可以上下滚动
};


const gui_screen_struct gui_screen_games_list =
{
	.type = TYPE_GUI_LAYOUT_LIST,
	.space_x = 0,
	.space_y = 0,
	.order = 0,
	.children = gui_widget_games_list,
	.child_num = countof(gui_widget_games_list),
	.layout_config = &gui_layout_games_list,
};


/*-----------------------------系统事件--------------------------------------*/

static void app_window_games_list_init(void *buf)
{
}

static void app_window_games_list_load(void *buf)
{
}


static void app_window_games_list_entry(void *buf)
{

}


static void app_window_games_list_exit()
{
}

static void app_window_games_list_destroy()
{

}


static void app_window_games_list_click_on_layout_item(gui_click_layout_struct *event)
{
    if (event->id == GAME_ITEM_2048) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_game_2048, NULL);
    }
    else if (event->id == GAME_ITEM_DADISHU) {
        application_switch(GUI_WINDOW_SWITCH_TYPE_PUSH, &app_window_game_dadishu, NULL);
    }
}

/*-----------------------------响应事件--------------------------------------*/

/*-----------------------------配置--------------------------------------*/
const gui_window_struct app_window_games_list =
{
	.screen = &gui_screen_games_list,
	.init = app_window_games_list_init,
	.load = app_window_games_list_load,
	.entry = app_window_games_list_entry,
	.exit = app_window_games_list_exit,
	.destroy = app_window_games_list_destroy,

    .click_on_layout_item = app_window_games_list_click_on_layout_item,
};



