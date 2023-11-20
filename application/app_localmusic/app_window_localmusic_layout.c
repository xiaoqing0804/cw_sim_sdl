#include "picture.h"
#include "language.h"
#include "gui_surface_control_animation.h"
#include "gui_surface_control_base.h"

#include "app_window_localmusic_layout.h"


// bg
/*static const gui_image_struct gui_music_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_music_bg_info,
};*/

// music-name
static const gui_font_struct gui_music_name_txt =   //name
{
	.type = TYPE_GUI_DRAW_TEXT,
	.align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.value_align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.color = COLOR_RGB(255, 255, 255),
	.size = SYS_FONT_SMALL,
	.value_type = GUI_FONT_VALUE_TYPE_STRING,
	.value.string = "music",
};

// bt icon
/*static const gui_image_struct gui_music_btsta_img =
{
	.type = TYPE_GUI_DRAW_PICTURE,
    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
	.data = &pic_main_ble_disconnect_info,
};*/

// play|pause   80,99
// static const gui_image_struct gui_music_play_img =
// {
// 	.type = TYPE_GUI_DRAW_PICTURE,
// //    .align = GUI_ALIGN_MERGE(GUI_ALIGN_HCENTER , GUI_ALIGN_VCENTER),
// 	.data = &pic_music_pp_info,
// };

// ani
/*static const gui_animation_frame_struct gui_music_ani_frams[] = 
{
    PIC_ANIMATION_FRAME(300, 0, &pic_music_ani_1_info),
    PIC_ANIMATION_FRAME(300, 0, &pic_music_ani_2_info),
    PIC_ANIMATION_FRAME(300, 0, &pic_music_ani_3_info),
    PIC_ANIMATION_FRAME(300, 0, &pic_music_ani_2_info),
};

static const gui_animation_struct gui_music_ani = 
{
    .type = TYPE_GUI_DRAW_PICTURE,
    .id = 1,
    .frames_num = countof(gui_music_ani_frams),
    .frames = gui_music_ani_frams,
};*/

// vol
// static const gui_image_struct gui_music_volup_image = 
// {
//     .type = TYPE_GUI_DRAW_PICTURE,
//     .data = &pic_music_volh_info,
// };

// static const gui_image_struct gui_music_voldn_image = 
// {
//     .type = TYPE_GUI_DRAW_PICTURE,
//     .data = &pic_music_voll_info,
// };

/*static const gui_image_struct gui_music_yl_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_music_log_bg_info,
};
static const gui_image_struct gui_music_yy_bg =
{
	.type = TYPE_GUI_DRAW_PICTURE,
	.data = &pic_music_log_top_info,
};*/

/////////////////////////////////////////////////////////////////////////////////////////
static const gui_widget_struct gui_music_widget[] =
{
	/*{
		.id = LOCALMUSIC_LAYOUT_ID_BG,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.width = LCD_SIZE_WIDTH,
		.height = LCD_SIZE_HEIGHT,
		.visible= 1,
		.child_num =1,
		.children = &gui_music_bg,
	},*/

    {   // music-name
        .id = LOCALMUSIC_LAYOUT_ID_NAME,
        .type = TYPE_GUI_CONTROL_SCROLL_TEXT,
        .x = 0,
        .y = 45,
        .width = LCD_SIZE_WIDTH,
        .height = 24,
        .visible= 1,
        .child_num = 1,
        .children = &gui_music_name_txt,
    },
        
	/*{   // bt-icon
		.id = LOCALMUSIC_LAYOUT_ID_BTSTA,
		.type = TYPE_GUI_CONTROL_IMAGE,
		.y = 5,
		.width = LCD_SIZE_WIDTH,
		.height = 29,
		.visible= 1,
		.child_num = 1,
		.children = &gui_music_btsta_img,
	},*/
		
	// {   // play|pause
	// 	.id = LOCALMUSIC_LAYOUT_ID_PLAY,
	// 	.type = TYPE_GUI_CONTROL_IMAGE,
	// 	.x = 80,
	// 	.y = 74,
	// 	.width = 79,
	// 	.height = 79,
	// 	.visible= 1,
	// 	.child_num = 1,
	// 	.children = &gui_music_play_img,
	// },		

    /*{   // ani
        .id = LOCALMUSIC_LAYOUT_ID_ANI,
        .type = TYPE_GUI_CONTROL_ANIMATION,
        .x = 11,
        .y = 286-52,
        .width = 219,
        .height = 52, 
        .visible= 1,
        .child_num = 1,
        .children = &gui_music_ani,
    },*/      

    // {   // vol - up
    //     .id = LOCALMUSIC_LAYOUT_VOLUP_ID,
    //     .type = TYPE_GUI_CONTROL_IMAGE,
    //     .x = 175,
    //     .y = 175,
    //     .width = 70,
    //     .height = 50,
    //     .visible= 1,
    //     .child_num = 1,
    //     .children = &gui_music_volup_image,
    // },
    // {   // vol - dn
    //     .id = LOCALMUSIC_LAYOUT_VOLDN_ID,
    //     .type = TYPE_GUI_CONTROL_IMAGE,
    //     .x = 23,
    //     .y = 175,
    //     .width = 70,
    //     .height = 50,
    //     .visible= 1,
    //     .child_num = 1,
    //     .children = &gui_music_voldn_image,
    // },
};

const gui_screen_struct gui_screen_localmusic =
{
	.type = TYPE_GUI_LAYOUT_PANNEL,
	.order = 0,
	.children = gui_music_widget,
	.child_num = countof(gui_music_widget),
};



