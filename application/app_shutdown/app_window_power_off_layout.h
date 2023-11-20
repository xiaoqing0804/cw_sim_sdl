#ifndef __APP_WINDOW_POWER_OFF_LAYOUT_H__
#define __APP_WINDOW_POWER_OFF_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum
{
    POWER_OFF_LAYOUT_ID_NONE = 0,

    //--------固定顺序：bg->icon->text
    POWER_OFF_LAYOUT_ID_SHUTDOWN_BG,
    POWER_OFF_LAYOUT_ID_SHUTDOWN_ICON,
    POWER_OFF_LAYOUT_ID_SHUTDOWN_TEXT,

    //--------固定顺序：bg->icon->text
    POWER_OFF_LAYOUT_ID_REBOOT_BG,
    POWER_OFF_LAYOUT_ID_REBOOT_ICON,
    POWER_OFF_LAYOUT_ID_REBOOT_TEXT,

    //--------固定顺序：bg->icon->text
    POWER_OFF_LAYOUT_ID_SOS_BG,
    POWER_OFF_LAYOUT_ID_SOS_ICON,
    POWER_OFF_LAYOUT_ID_SOS_TEXT,
};

#define POWER_OFF_CONTENT_LEFT (78)
#define POWER_OFF_CONTENT_TOP (64)

#define POWER_OFF_ITEM_WIDTH (310)
#define POWER_OFF_ITEM_HEIGHT (100)
#define POWER_OFF_ITEM_GAP (20)

#define POWER_OFF_ICON_LEFT (11)
#define POWER_OFF_ICON_TOP (11)
#define POWER_OFF_ICON_WIDTH (76)
#define POWER_OFF_ICON_HEIGHT (76)

#define POWER_OFF_TITLE_LEFT (100)
#define POWER_OFF_TITLE_TOP (0)
#define POWER_OFF_TITLE_WIDTH (200)
#define POWER_OFF_TITLE_HEIGHT (POWER_OFF_ITEM_HEIGHT)

#define POWER_OFF_ITEM_Y(index) (POWER_OFF_CONTENT_TOP + (index) * (POWER_OFF_ITEM_HEIGHT + POWER_OFF_ITEM_GAP))

extern const gui_screen_struct app_screen_power_off;

#endif
