#ifndef __APP_WINDOW_SPORT_DATA_H__
#define __APP_WINDOW_SPORT_DATA_H__

#include "data_common.h"
#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"


#define SPORT_WINDOW_NUM		4

extern MIX_SPORT_TYPE save_sport_type;
extern unsigned char m_window_sport_status;


typedef enum
{
	SPORT_STATUS_STOP = 0,
	SPORT_STATUS_START,
	SPORT_STATUS_PAUSE,
	SPORT_STATUS_CONTINUE,

	SPORT_STATUS_ALL
}SPORT_STATUS_TYPE;


extern void sport_info_init(void);
extern void sport_status_set(SPORT_STATUS_TYPE type);


extern const gui_window_struct app_window_sport_data;

#endif

