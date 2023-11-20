#include "app_window_shake.h"
#include "app_window_shake_layout.h"
#include "application_titlebar.h"

void app_window_shake_ui_show()
{
	application_titlebar_create(&gui_screen_shake, STRING_SHAKE);
}
