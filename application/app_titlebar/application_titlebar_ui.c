#include "application_titlebar_ui.h"
#include "application_titlebar_layout.h"

unsigned char application_titlebar_ui_is_exist(gui_surface_struct *surface)
{
	gui_box_struct *box = gui_surface_get_box_by_id(surface, GUI_IDS_TITLE_NAME);
	return box != NULL;
}

void application_titlebar_ui_create_bg(gui_surface_struct *surface)
{
	gui_box_struct *box = gui_surface_box_create(surface, &gui_widget_titlebar_bg);
	if (box != NULL)
	{
		gui_surface_add_box(surface, box);
	}
}

void application_titlebar_ui_create_name(gui_surface_struct *surface, unsigned int name_id)
{
	gui_titlebar_name.value.string_id = name_id;
	gui_titlebar_name.color = COLOR_RGB(255, 255, 255);
	gui_box_struct *box = gui_surface_box_create(surface, &gui_widget_titlebar_name);
	if (box != NULL)
	{
		gui_surface_add_box(surface, box);
	}
}

void application_titlebar_ui_show_bg(gui_surface_struct *surface, unsigned char visible)
{
	gui_box_struct *box = gui_surface_get_box_by_id(surface, GUI_IDS_TITLE_BG);
	if (box != NULL)
	{
		box->visible = visible;
	}
}

void application_titlebar_ui_set_fix(gui_surface_struct *surface, unsigned char fix)
{
	gui_box_struct *box;

	box = gui_surface_get_box_by_id(surface, GUI_IDS_TITLE_BG);
	if (box != NULL)
		box->fix = fix;

	box = gui_surface_get_box_by_id(surface, GUI_IDS_TITLE_NAME);
	if (box != NULL)
		box->fix = fix;
}
