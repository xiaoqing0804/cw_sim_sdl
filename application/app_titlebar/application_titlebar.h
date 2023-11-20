
#ifndef __APP_TITLEBAR_H__
#define __APP_TITLEBAR_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

extern void application_titlebar_create(const gui_screen_struct *screen, unsigned int name_id);
extern void application_titlebar_show_bg(gui_surface_struct *surface);
extern void application_titlebar_hide_bg(gui_surface_struct *surface);
extern void application_titlebar_fix(gui_surface_struct *surface);
extern void application_titlebar_unfix(gui_surface_struct *surface);

extern void application_titlebar_show_bg_from_screen(const gui_screen_struct *screen);
extern void application_titlebar_hide_bg_from_screen(const gui_screen_struct *screen);

#endif
