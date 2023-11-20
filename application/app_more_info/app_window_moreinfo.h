#ifndef __APP_WINDOW_MOREINFO_H__
#define __APP_WINDOW_MOREINFO_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

#define APP_MOREINFO_DOUBLE_KEY 300

extern const gui_window_struct* app_window_moreinfo_get(void);
extern void app_window_moreinfo_enter(void* buf);
extern void app_window_moreinfo_change(void);
extern int application_get_moreinfo_tyep(void);
extern int application_add_moreinfo_tyep(void);
extern void app_window_moreinfo_set(unsigned char style);

#endif

