#ifndef __APP_WND_MESSAGE_LIST_UI_H__
#define __APP_WND_MESSAGE_LIST_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

extern void app_window_message_list_ui_init(void);

extern void app_window_message_list_ui_update(void);

extern unsigned char app_window_message_list_ui_touch(gui_touch_struct *envent);

extern void app_window_message_list_ui_delect_one(gui_click_struct *event);


#endif
