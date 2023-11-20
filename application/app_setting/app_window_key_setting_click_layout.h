#ifndef __APP_WINDOW_KEY_SETTING_CLICK_LAYOUT_H__
#define __APP_WINDOW_KEY_SETTING_CLICK_LAYOUT_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef enum
{
    KEY_SETTING_CLICK_LAYOUT_ID_NONE = 100,
    KEY_SETTING_CLICK_LAYOUT_ID_ICON,
    KEY_SETTING_CLICK_LAYOUT_ID_CHECKED,
};

extern gui_image_struct gui_key_setting_click_item_icon;
extern gui_font_struct gui_key_setting_click_item_title;
extern const gui_widget_struct gui_widget_key_setting_click;
extern const gui_screen_struct app_screen_key_setting_click;

#endif
