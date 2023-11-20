#ifndef __APP_WINDOW_RECORD_LAYOUT_H__
#define __APP_WINDOW_RECORD_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	RECORD_ID_NONE,
	RECORD_ID_PIC,
	RECORD_ID_REC_START,
	RECORD_ID_REC_STOP,
	RECORD_ID_PLAY_START,
    RECORD_ID_PLAY_STOP,
	RECORD_ID_TIME,
}APP_WINDOW_RECORD_LAYOUT_ID;


extern const gui_screen_struct gui_screen_record;


#endif

