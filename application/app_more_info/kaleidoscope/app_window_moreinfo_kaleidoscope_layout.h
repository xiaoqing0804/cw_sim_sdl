#ifndef __APP_WINDOW_KALEIDOSCOPE_LAYOUT_H__
#define __APP_WINDOW_KALEIDOSCOPE_LAYOUT_H__

#include "feature_all.h"
#include "gui_core_all.h"
#include "picture.h"

#define KALEIDOSCOPE_APP_TOTAL (25)
#define KALEIDOSCOPE_RAY_TOTAL (16)

#define KALEIDOSCOPE_MAX_WIDTH (98)

typedef struct
{
	short id;
	const picture_info_struct *picture;
} gui_kaleidoscope_app_struct;

#define SIN_22_5 (0.3826834f)
#define SIN_45_0 (0.7071068f)
#define SIN_67_5 (0.9238795f)

#define COS_22_5 (0.9238795f)
#define COS_45_0 (0.7071068f)
#define COS_67_5 (0.3826834f)

extern const gui_screen_struct gui_screen_moreinfo_kaleidoscope;
extern const gui_kaleidoscope_app_struct g_kaleidoscope_app[KALEIDOSCOPE_APP_TOTAL];
extern const geometry_point gui_kaleidoscope_position_list[];

#endif
