#include "app_window_calculator_ui.h"
#include "app_window_calculator_layout.h"

const calculator_key_position_struct g_calculator_key_list[] =
	{
		{'0', 0, 125, 104, 79},
		{'1', 104, 125, 130, 79},
		{'2', 233, 125, 130, 79},
		{'3', 363, 125, 104, 79},

		{'4', 0, 205, 104, 79},
		{'5', 104, 205, 130, 79},
		{'6', 233, 205, 130, 79},
		{'7', 363, 205, 104, 79},

		{'8', 0, 284, 104, 79},
		{'9', 104, 284, 130, 79},
		{'.', 233, 284, 130, 79},
		{'=', 363, 284, 104, 79},

		{'+', 0, 364, 136, 136},
		{'-', 137, 364, 90, 96},
		{'*', 233, 364, 90, 96},
		{'/', 330, 364, 136, 136},

		{'C', 327, 0, 139, 113},

};

unsigned char window_calculator_get_key(unsigned short x, unsigned short y)
{
	for (short i = 0; i < sizeof(g_calculator_key_list) / sizeof(g_calculator_key_list[0]); i++)
	{
		const calculator_key_position_struct *key_list = &g_calculator_key_list[i];
		if (x >= key_list->x && y >= key_list->y && x <= key_list->x + key_list->w && y <= key_list->y + key_list->h)
		{
			return key_list->value;
		}
	}
	return 0;
}

static void app_window_calculator_ui_show_data(unsigned char *show_data)
{
	char temp[20];
	gui_box_struct *calculator = gui_surface_get_box(&app_calculator_screen, CALCULATOR_ID_TXET);
	snprintf(temp, sizeof(temp), "%s", show_data);
	gui_surface_box_label_change_string(calculator, temp);
}

static void app_window_calculator_ui_show_sign(unsigned char operation_sign)
{
	char temp[20];
	gui_box_struct *calculator_c = gui_surface_get_box(&app_calculator_screen, CALCULATOR_ID_C);
	if(calculator_c != NULL)
    {
        snprintf(temp, sizeof(temp), "%c", (operation_sign > 0) ? operation_sign : ' ');
	    gui_surface_box_label_change_string(calculator_c, temp);
    }

}

void app_window_calculator_ui_show(unsigned char *show_data, unsigned char operation_sign)
{
	app_window_calculator_ui_show_data(show_data);
	app_window_calculator_ui_show_sign(operation_sign);
}
