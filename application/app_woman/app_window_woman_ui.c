#include "app_window_woman_ui.h"
#include "app_window_woman_layout.h"

#include "data_common.h"
#include "gui_surface.h"
#include "gui_surface_box_image.h"
#include "gui_surface_box_label.h"
#include "app_window_woman_info.h"


static unsigned char *app_window_woman_ui_get_period_string(unsigned char status)
{
	unsigned char *period_str = NULL;

	switch (status)
	{
	case WOMAN_STATUS_NULL:
		period_str = GUI_Get_ID_String(STRING_WOMAN_PHY_PERIOD);
		break;

	case WOMAN_STATUS_YUEJIN:
		period_str = GUI_Get_ID_String(STRING_WOMAN_YUEJIN);
		break;

	case WOMAN_STATUS_PAILUAN:
		period_str = GUI_Get_ID_String(STRING_WOMAN_PAILUAN);
		break;

	case WOMAN_STATUS_PAILUAN_DAY:
		period_str = GUI_Get_ID_String(STRING_WOMAN_PAILUAN_DAY);
		break;

	case WOMAN_STATUS_ANQUAN:
		period_str = GUI_Get_ID_String(STRING_WOMAN_ANQUAN);
		break;
	}
	return period_str;
}

void app_window_woman_ui_change_curr_period(unsigned char status)
{
	unsigned char *period_str = app_window_woman_ui_get_period_string(status);
	gui_box_struct *woman_text = gui_surface_get_box(&gui_screen_woman, (unsigned short)WOMAN_LAYOUT_ID_TEXT);
	gui_surface_box_label_change_string(woman_text, period_str);
}
