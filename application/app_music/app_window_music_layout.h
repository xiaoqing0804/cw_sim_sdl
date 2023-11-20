#ifndef __APP_WINDOW_MUSIC_LAYOUT_H__
#define __APP_WINDOW_MUSIC_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

#define MUSIC_NAME_X    0
#define MUSIC_NAME_Y    45
#define MUSIC_NAME_H    24

#define MUSIC_PLAY_X    80
#define MUSIC_PLAY_Y    99
#define MUSIC_NEXT_X    171
#define MUSIC_NEXT_Y    85
#define MUSIC_PREV_X    10
#define MUSIC_PREV_Y    85
#define MUSIC_ANI_X     11
#define MUSIC_ANI_Y     210
#define MUSIC_ANI_H     56

enum
{
    MUSIC_LAYOUT_ID_BG = 100,
    MUSIC_LAYOUT_ID_MUSIC_BG,
    MUSIC_LAYOUT_ID_MUSIC_NAME ,
    MUSIC_LAYOUT_ID_PLAY,
    MUSIC_LAYOUT_ID_LOG_BG,
    MUSIC_LAYOUT_ID_LOG_ICON,
    MUSIC_LAYOUT_ID_PREVIOUS_SONG,
    MUSIC_LAYOUT_ID_ICON,
    MUSIC_LAYOUT_ID_NAME,
    MUSIC_LAYOUT_ID_NEXT,
    MUSIC_LAYOUT_ID_MUSIC_BG1,

};

extern gui_canvas_struct gui_music_vol_line_fg[];

extern const gui_screen_struct gui_screen_music;

#endif

