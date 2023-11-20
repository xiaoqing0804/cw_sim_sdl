#include "app_window_breath_ui.h"
#include "app_window_breath_layout.h"
#include "app_window_breath_animate.h"

void app_window_breath_ui_init_animate()
{
	app_window_breath_animate_init(&gui_screen_breath, (unsigned short)BREATH_LAYOUT_ID_BG);
}

