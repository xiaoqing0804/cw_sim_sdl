
#ifndef __APP_TITLEBAR_UI_H__
#define __APP_TITLEBAR_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

extern unsigned char application_titlebar_ui_is_exist(gui_surface_struct *surface);
extern void application_titlebar_ui_create_bg(gui_surface_struct *surface);
extern void application_titlebar_ui_create_name(gui_surface_struct *surface, unsigned int name_id);
extern void application_titlebar_ui_show_bg(gui_surface_struct *surface, unsigned char visible);
extern void application_titlebar_ui_set_fix(gui_surface_struct *surface, unsigned char fix);

#endif
