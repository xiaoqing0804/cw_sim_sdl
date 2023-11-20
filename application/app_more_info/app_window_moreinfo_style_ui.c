#include "app_window_moreinfo_style_ui.h"
#include "app_window_moreinfo_style_layout.h"

void app_window_moreinfo_style_ui_set_checked(short id)
{
	gui_surface_struct *surface = gui_surface_get_surface(&app_screen_moreinfo_style);
	if (surface != NULL)
	{
		gui_box_struct *box = surface->child;
		gui_node_struct *node;
		while (box != NULL)
		{
			node = gui_surface_box_find_node(box, MOREINFO_STYLE_LAYOUT_ID_CHECKED);
			if (node != NULL)
			{
				node->visible = (box->id == id);
			}
			box = box->brother;
		}
	}
}

void app_window_moreinfo_style_ui_show()
{
	application_titlebar_create(&app_screen_moreinfo_style, STRING_APP_VIEW);
	app_window_moreinfo_style_ui_set_checked(application_get_moreinfo_tyep());
}