#ifndef __APP_WINDOW_SPORTLIST_LAYOUT_H__
#define __APP_WINDOW_SPORTLIST_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"


typedef enum
{
	SPORT_LAYOUT_ID_NONE = 0,
	SPORT_LAYOUT_ID_RUN,
	SPORT_LAYOUT_ID_WALK,
	SPORT_LAYOUT_ID_CYCLING,
	SPORT_LAYOUT_ID_CLIMB,
	SPORT_LAYOUT_ID_YOGA,
	SPORT_LAYOUT_ID_BASKETBALL,
	SPORT_LAYOUT_ID_FOOTBALL,
	SPORT_LAYOUT_ID_BADMINTON,
	SPORT_LAYOUT_ID_SKIP,
	SPORT_LAYOUT_ID_SWIM,
	SPORT_LAYOUT_ID_TIP_BG,
	SPORT_LAYOUT_ID_TIP,
	SPORT_LAYOUT_ID_TIME,
}APP_WINDOW_SPORT_LIST_LAYOUT_ID;



extern const gui_screen_struct gui_screen_sportlist;


#endif


