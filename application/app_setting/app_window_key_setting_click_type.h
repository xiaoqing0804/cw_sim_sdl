#ifndef __APP_WINDOW_KEY_SETTING_CLICK_TYPE_H__
#define __APP_WINDOW_KEY_SETTING_CLICK_TYPE_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

extern void app_window_key_setting_click_type_set_type(unsigned short type);
extern unsigned char app_window_key_setting_click_type_get_type(void);
extern unsigned short app_window_key_setting_click_type_get_string_id(void);
extern unsigned char app_window_key_setting_click_type_is_selected(unsigned short id);
extern void app_window_key_setting_click_type_set_key(unsigned short id);

#endif
