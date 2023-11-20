#include "application_titlebar.h"
#include "application_titlebar_ui.h"
#include "application_titlebar_layout.h"

#include "gui_surface_box_label.h"
#include "gui_surface_control.h"

void application_titlebar_create(const gui_screen_struct *screen, unsigned int name_id)
{
	if (screen == NULL || name_id == 0)
		return;

	gui_surface_struct *surface = gui_surface_get_surface(screen);
	if (surface == NULL)
		return;

	if (!application_titlebar_ui_is_exist(surface))
	{
		application_titlebar_ui_create_bg(surface);
		application_titlebar_ui_create_name(surface, name_id);
	}
}

void application_titlebar_show_bg(gui_surface_struct *surface)
{
	application_titlebar_ui_show_bg(surface, 1);
}

void application_titlebar_hide_bg(gui_surface_struct *surface)
{
	application_titlebar_ui_show_bg(surface, 0);
}

void application_titlebar_fix(gui_surface_struct *surface)
{
	application_titlebar_ui_set_fix(surface, 1);
}

void application_titlebar_unfix(gui_surface_struct *surface)
{
	application_titlebar_ui_set_fix(surface, 0);
}



void application_titlebar_show_bg_from_screen(const gui_screen_struct *screen)
{
	gui_surface_struct *surface = gui_surface_get_surface(screen);
	if (surface == NULL)
		return;
	application_titlebar_show_bg(surface);
}

void application_titlebar_hide_bg_from_screen(const gui_screen_struct *screen)
{
	gui_surface_struct *surface = gui_surface_get_surface(screen);
	if (surface == NULL)
		return;
	application_titlebar_hide_bg(surface);
}