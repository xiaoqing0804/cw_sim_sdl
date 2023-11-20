#ifndef __APP_WINDOW_CALCULATOR_UI_H__
#define __APP_WINDOW_CALCULATOR_UI_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef struct
{
	unsigned char value; // the char value.
	short x;
	short y;
	short w;
	short h;
} calculator_key_position_struct;

extern const calculator_key_position_struct g_calculator_key_list[];
extern unsigned char window_calculator_get_key(unsigned short x, unsigned short y);
extern void app_window_calculator_ui_show(unsigned char *show_data, unsigned char operation_sign);

#endif
