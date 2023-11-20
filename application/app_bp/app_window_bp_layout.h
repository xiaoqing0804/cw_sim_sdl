#ifndef __APP_WINDOW_BP_LAYOUT_H__
#define __APP_WINDOW_BP_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"

typedef enum
{
	BP_LAYOUT_ID_NONE,
    BP_BOX_ANI_IMAGE_ID,
    BP_BOX_ANI_RESET_ID,
    BP_SBP_VALUE_ID,
    BP_DBP_VALUE_ID,
    BP_SBP_SMALL_VALUE_ID,
    BP_DBP_SMALL_VALUE_ID,
    BP_SBP_CHART,
    BP_DBP_CHART,
    BP_LAYOUT_ID_PUBLIC_TXT,

    BP_BG_ID,


}APP_WINDOW_BP_LAYOUT_ID;


extern const gui_screen_struct gui_screen_bp;

extern void ui_bp_value_start_updata(unsigned char spb_value,unsigned char dpb_value);
extern void ui_bp_value_ready_updata(void);
extern void ui_bp_value_messung_updata(unsigned char spb_value,unsigned char dpb_value);

#endif

