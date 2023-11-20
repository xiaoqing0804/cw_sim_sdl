#ifndef __APP_WINDOW_SPORTLIST_BG_H__
#define __APP_WINDOW_SPORTLIST_BG_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

#define SPORT_ITEM_BG_COUNT (2)
#define SPORT_ITEM_ANI_COUNT (3)

typedef struct
{
    unsigned int string;
    unsigned int id;
    picture_info_struct *ani[SPORT_ITEM_ANI_COUNT];
    picture_info_struct *bg[SPORT_ITEM_BG_COUNT];
} sport_window_item_struct;

extern const gui_window_struct app_window_sport;

extern STRING_ID_TYPE sport_list_get_string(MIX_SPORT_TYPE id);
extern picture_info_struct* sport_list_get_detailed_pic(MIX_SPORT_TYPE id);

#endif

