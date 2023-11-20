#ifndef __APP_WINDOW_CALCULATOR_KEY_H__
#define __APP_WINDOW_CALCULATOR_KEY_H__

#include "feature_all.h"
#include "application.h"
#include "gui_core_all.h"

typedef struct
{
	char type; // 0�գ�1 int, 2 float
	union
	{
		long long i;
		double f;
	} value;
} calculator_operation_struct;

extern unsigned char window_calculator_get_operation_sign(void);
extern unsigned char *window_calculator_get_show_data(void);
extern void window_calculator_clear(void);
extern void window_calculator_key_press(char key);

#endif
