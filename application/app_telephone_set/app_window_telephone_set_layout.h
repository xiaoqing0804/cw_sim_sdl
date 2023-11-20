#ifndef __APP_WINDOW_TELEPHONE_SET_LAYOUT_H__
#define __APP_WINDOW_TELEPHONE_SET_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	TELEPHONE_ID_NONE,
	TELEPHONE_ID_PIC,
	TELEPHONE_ID_TITLE,
	TELEPHONE_ID_TIME,
	TELEPHONE_ID_CALL,
	TELEPHONE_ID_CALL_PIC,
	TELEPHONE_ID_CALL_VIB,
	TELEPHONE_ID_CALL_VIB_PIC,
	TELEPHONE_ID_CALL_OUT_VIB,
	TELEPHONE_ID_CALL_OUT_VIB_PIC,

}APP_WINDOW_TELEPHONE_LAYOUT_ID;


extern const gui_screen_struct gui_screen_telephone;


#endif
