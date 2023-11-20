#include "app_window_vib.h"
#include "app_window_vib_layout.h"
#include "app_window_vib_ui.h"

#include "application_titlebar.h"
#include "data_common.h"

/*-----------------------------ϵͳ�¼�--------------------------------------*/



void app_window_vib_ui_show()
{

	gui_box_struct *vib_onoff = gui_surface_get_box(&gui_screen_vib, VIB_ID_PIC);

	if(g_vib_mode.vib_onoff)
		gui_surface_box_image_change(vib_onoff,&pic_clock_on_info);
	else
		gui_surface_box_image_change(vib_onoff,&pic_clock_off_info);
}
