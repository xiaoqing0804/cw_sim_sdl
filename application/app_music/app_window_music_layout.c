#include "app_window_music_layout.h"
#include "gui_surface_control_base.h"
#include "picture.h"
#include "language.h"
#include "gui_surface_control_animation.h"



static const gui_image_struct gui_watch_music_bg_image[] =
{
    {
    	.type = TYPE_GUI_DRAW_PICTURE,
    	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
        .x = 0,
        .y = 0,
        .data = &pic_music_bg_01_info,
    },
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
        .x = LCD_SIZE_HALF_WIDTH,
        .y = 0,
        .data = &pic_music_bg_02_info,
    },
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
        .x = 0,
        .y = LCD_SIZE_HALF_HEIGHT,
        .data = &pic_music_bg_03_info,
    },
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
        .x = LCD_SIZE_HALF_WIDTH,
        .y = LCD_SIZE_HALF_HEIGHT,
        .data = &pic_music_bg_04_info,
    },
};


// static const gui_image_struct gui_watch_music_bg1_image[] =
// {
//     {
//     	.type = TYPE_GUI_DRAW_PICTURE,
//     	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
//         .x = 0,
//         .y = 0,
//         .data = &pic_music_bg1_01_info,
//     },
//     {
//         .type = TYPE_GUI_DRAW_PICTURE,
//         .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
//         .x = LCD_SIZE_HALF_WIDTH,
//         .y = 0,
//         .data = &pic_music_bg1_02_info,
//     },
//     {
//         .type = TYPE_GUI_DRAW_PICTURE,
//         .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
//         .x = 0,
//         .y = LCD_SIZE_HALF_HEIGHT,
//         .data = &pic_music_bg1_03_info,
//     },
//     {
//         .type = TYPE_GUI_DRAW_PICTURE,
//         .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
//         .x = LCD_SIZE_HALF_WIDTH,
//         .y = LCD_SIZE_HALF_HEIGHT,
//         .data = &pic_music_bg1_04_info,
//     },
// };


// music-name
static const gui_font_struct gui_music_name_txt =   //name
{
	.type = TYPE_GUI_DRAW_TEXT,
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_NONE),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_SMALL,
    .width = 100,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "music",
};



static const gui_font_struct gui_music_txt =   //������
{
	.type = TYPE_GUI_DRAW_TEXT,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_MEDIUM,
	.value_type = GUI_FONT_VALUE_TYPE_STRING_ID,
	.value.string_id = STRING_MUSIC,
};



// vol
static const gui_image_struct gui_music_start_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_music_start0_info,
};

// static const gui_image_struct gui_music_stop_image =
// {
//     .type = TYPE_GUI_DRAW_PICTURE,
//     .data = &pic_music_stop_info,
// };


static const gui_image_struct gui_music_next_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_next_info,
};


static const gui_image_struct gui_music_previous_song_image =
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .data = &pic_previous_song_info,
};

static const gui_image_struct gui_music_sound_bg_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .data = &pic_music_log_bg_info,
};

static const gui_image_struct gui_music_sound_long_image =
    {
        .type = TYPE_GUI_DRAW_PICTURE,
        .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER, GUI_ALIGN_NONE),
        .data = &pic_music_log_top_info,
};
static const gui_widget_struct gui_music_widget[] =
{
//bg

    {
        .id = MUSIC_LAYOUT_ID_MUSIC_BG,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .width = LCD_SIZE_WIDTH,
        .height = LCD_SIZE_HEIGHT,
        .visible= 1,
        .child_num = countof(gui_watch_music_bg_image),
        .children = gui_watch_music_bg_image,
    },


    // {
    //     .id = MUSIC_LAYOUT_ID_MUSIC_BG1,
    //     .type = TYPE_GUI_CONTROL_IMAGE,
    //     .width = LCD_SIZE_WIDTH,
    //     .height = LCD_SIZE_HEIGHT,
    //     .visible= 1,
    //     .child_num = countof(gui_watch_music_bg1_image),
    //     .children = gui_watch_music_bg1_image,
    // },


    {   // music-name
        .id = MUSIC_LAYOUT_ID_MUSIC_NAME,
        .type = TYPE_GUI_CONTROL_SCROLL_TEXT,
        .y = 80,
        .width = LCD_SIZE_WIDTH,
        .height = 30,
        .visible= 1,
        .child_num = 1,
        .children = &gui_music_name_txt,
    },

    {   // name
        .id = MUSIC_LAYOUT_ID_NAME,
        .type = TYPE_GUI_CONTROL_LABEL,
        .y = 30,
        .width = LCD_SIZE_WIDTH,
        .height = 30,
        .visible= 1,
        .child_num = 1,
        .children = &gui_music_txt,
    },

	{   // start
		.id = MUSIC_LAYOUT_ID_PLAY,
		.type = TYPE_GUI_CONTROL_IMAGE,
        .x = 195,
		.y = 195,
		.width = 80,
		.height = 80,
		.visible= 1,
		.child_num = 1,
		.children = &gui_music_start_image,
	},


    // {   // stop
    //     .id = MUSIC_LAYOUT_ID_ICON,
    //     .type = TYPE_GUI_CONTROL_IMAGE,
    //     .x = 213,
    //     .y = 204,
    //     .width = 56,
    //     .height = 56,
    //     .visible= 1,
    //     .child_num = 1,
    //     .children = &gui_music_stop_image,
    // },

    {   // sound_icon
        .id = MUSIC_LAYOUT_ID_PREVIOUS_SONG,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 380,
        .y = 213,
        .width = 70,
        .height = 70,
        .visible= 1,
        .child_num = 1,
        .children = &gui_music_previous_song_image,
    },

    {   // next
        .id = MUSIC_LAYOUT_ID_NEXT,
        .type = TYPE_GUI_CONTROL_IMAGE,
        .x = 30,
        .y = 213,
        .width = 70,
        .height = 70,
        .visible= 1,
        .child_num = 1,
        .children = &gui_music_next_image,
    },
    //sound
    {
            .id = MUSIC_LAYOUT_ID_LOG_BG,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 0,
            .y = 390,
            .width = LCD_SIZE_WIDTH,
            .height = 12,
            .visible= 1,
            .child_num = 1,
            .children = &gui_music_sound_bg_image,
    },
    {
        //SOUND ICON
            .id = MUSIC_LAYOUT_ID_LOG_ICON,
            .type = TYPE_GUI_CONTROL_IMAGE,
            .x = 0,
            .y = 390,
            .width = LCD_SIZE_WIDTH,
            .height = 12,
            .visible= 1,
            .child_num = 1,
            .children = &gui_music_sound_long_image,

    },
};

const gui_screen_struct gui_screen_music =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.order = 0,
	.children = gui_music_widget,
	.child_num = countof(gui_music_widget),
};



