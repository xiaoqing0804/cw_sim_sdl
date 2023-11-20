#ifndef __APP_WINDOW_COVER_BG_UI_H__
#define __APP_WINDOW_COVER_BG_UI_H__

#include "feature_all.h"
#include "gui_surface.h"
#include "application.h"
#include "gui_core_all.h"

extern unsigned char app_window_cover_bg_ui_is_exist(gui_surface_struct *surface);
extern void app_window_cover_bg_ui_create(gui_surface_struct *surface);
extern void app_window_cover_bg_ui_move(gui_surface_struct *surface, unsigned char direction);
extern void app_window_cover_bg_ui_end(gui_surface_struct *surface);

#endif
