#ifndef __APP_WINDOW_DISTURB_LAYOUT_H__
#define __APP_WINDOW_DISTURB_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	DISTURB_LAYOUT_ID_NONE,
	DISTURB_LAYOUT_ID_PIC,
	DISTURB_LAYOUT_ID_TITLE,
	DISTURB_LAYOUT_ID_TIME,
	DISTURB_LAYOUT_ID_TETX,
	DISTURB_LAYOUT_ID_YES,
	DISTURB_LAYOUT_ID_NO,
};

extern const gui_screen_struct gui_screen_disturb;

#endif
