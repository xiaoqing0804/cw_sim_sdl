#ifndef __APP_WINDOW_SETTING_UI_H__
#define __APP_WINDOW_SETTING_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef struct
{
	unsigned short id;
	const gui_window_struct *window;
} app_window_setting_list_item_struct;

extern const gui_window_struct *app_window_setting_ui_find_app(unsigned short id);
extern void app_window_setting_ui_show(void);
extern void app_window_setting_ui_show_content(void);

#endif

