#include "app_window_calculator_key.h"
#include "app_window_calculator_ui.h"
#include "app_window_calculator_layout.h"
#include "app_window_calculator_convert.h"

#include <math.h>
#include <string.h>

static calculator_operation_struct g_operation_1 = {0};
static calculator_operation_struct g_operation_2 = {0};
static unsigned char radix_point_flag = 0;
static unsigned char g_operation_sign = 0;
static unsigned char g_operation_status = 0;
static unsigned char g_show_data[9] = {0};
static const float EPSINON = 0.0000001;					   // 8λ
static const long long MAX_INT_DATA = (long long)99999999; // 8λ
static const long long MAX_FLOAT_DATA = 999999;			   // 8λ,һλС���͵��

unsigned char window_calculator_get_operation_sign()
{
	return g_operation_sign;
}

unsigned char *window_calculator_get_show_data()
{
	return g_show_data;
}

void window_calculator_clear()
{
	radix_point_flag = 0;
	g_operation_status = 0;
	g_operation_sign = 0;
	memset(&g_show_data, 0, sizeof(g_show_data));
	memset(&g_operation_1, 0, sizeof(calculator_operation_struct));
	memset(&g_operation_2, 0, sizeof(calculator_operation_struct));
}

static void window_calculator_add_key(unsigned char key)
{
	if (g_show_data[0] == '0' && g_show_data[1] == 0 && key != '.')
	{
		g_show_data[0] = key;
		return;
	}
	if (g_show_data[0] == '-' && g_show_data[1] == '0' && g_show_data[2] == 0 && key != '.')
	{
		g_show_data[1] = key;
		return;
	}

	for (short i = 0; i < (sizeof(g_show_data) / sizeof(g_show_data[0])) - 1; i++)
	{
		if (g_show_data[i] == '.')
			radix_point_flag = i;

		if (g_show_data[i] == 0)
		{
			if (radix_point_flag > 0 && key == '.')
				return;
			g_show_data[i] = key;
			SYS_DEBUG("g_show_data=%s", g_show_data);
			break;
		}
	}
}

static unsigned char window_calculator_is_float()
{
	for (short i = 0; i < sizeof(g_show_data) / sizeof(g_show_data[0]); i++)
	{
		if (g_show_data[i] == '.')
			return 1;
	}
	return 0;
}

static void window_calculator_float_trim_end()
{
	if (window_calculator_is_float())
	{
		for (short i = sizeof(g_show_data) / sizeof(g_show_data[0]) - 1; i >= 0; i--)
		{
			if (g_show_data[i] == 0)
				continue;
			if (g_show_data[i] != '0')
			{
				if (g_show_data[i] == '.')
					g_show_data[i] = 0;
				break;
			}

			g_show_data[i] = 0;
		}
	}
}

static void window_calculator_compute()
{
	memset(g_show_data, 0, sizeof(g_show_data));

	if (g_operation_1.type == 2 || g_operation_2.type == 2)
	{
		if (g_operation_sign == '/' && (g_operation_2.value.f < -EPSINON && g_operation_2.value.f > EPSINON))
		{
			window_calculator_clear();
			g_show_data[0] = 'E';
			return;
		}
		double result = 0;
		double operation_1 = (double)g_operation_1.value.i;
		if (g_operation_1.type == 2)
		{
			operation_1 = (double)g_operation_1.value.f;
		}

		double operation_2 = (double)g_operation_2.value.i;
		if (g_operation_2.type == 2)
		{
			operation_2 = (double)g_operation_2.value.f;
		}

		if (g_operation_sign == '-')
			result = operation_1 - operation_2;
		else if (g_operation_sign == '*')
			result = operation_1 * operation_2;
		else if (g_operation_sign == '/')
			result = operation_1 / operation_2;
		else
			result = operation_1 + operation_2;

		if (result > MAX_FLOAT_DATA)
		{
			window_calculator_clear();
			g_show_data[0] = 'N';
			return;
		}

		g_operation_1.type = 2;
		g_operation_1.value.f = result;
		snprintf((char *)g_show_data, sizeof(g_show_data), "%f", result);
	}
	else
	{
		if (g_operation_sign == '+' || g_operation_sign == '-' || g_operation_sign == '*')
		{
			long long result = 0;
			if (g_operation_sign == '+')
				result = (long long)g_operation_1.value.i + (long long)g_operation_2.value.i;
			else if (g_operation_sign == '-')
				result = (long long)g_operation_1.value.i - (long long)g_operation_2.value.i;
			else if (g_operation_sign == '*')
				result = (long long)g_operation_1.value.i * (long long)g_operation_2.value.i;

			if (result > MAX_INT_DATA)
			{
				window_calculator_clear();
				g_show_data[0] = 'N';
				return;
			}

			g_operation_1.type = 1;
			g_operation_1.value.i = result;
			snprintf((char *)g_show_data, sizeof(g_show_data), "%lld", result);
		}
		else if (g_operation_sign == '/')
		{
			if (g_operation_2.value.i == 0)
			{
				window_calculator_clear();
				g_show_data[0] = 'E';
				return;
			}
			else if (g_operation_1.value.i % g_operation_2.value.i == 0)
			{
				long long result = g_operation_1.value.i / g_operation_2.value.i;

				g_operation_1.type = 1;
				g_operation_1.value.i = result;
				snprintf((char *)g_show_data, sizeof(g_show_data), "%lld", result);
			}
			else
			{
				float result = (float)g_operation_1.value.i / (float)g_operation_2.value.i;

				g_operation_1.type = 2;
				g_operation_1.value.f = result;
				snprintf((char *)g_show_data, sizeof(g_show_data), "%f", result);
			}
		}
	}
	window_calculator_float_trim_end();
}

void window_calculator_key_press(char key)
{
	if (key == 'C')
	{
		window_calculator_clear();
		return;
	}

	if (key == 'B')
	{
		application_go_back();
	}

	if (g_operation_status == 0) // ��ʼ����
	{
		if ((key >= '0' && key <= '9') || key == '-')
		{
			window_calculator_clear();
			window_calculator_add_key(key);
			g_operation_status = 1;
		}
	}
	else if (g_operation_status == 1) // �������뱻������
	{
		if ((key >= '0' && key <= '9') || key == '.')
		{
			window_calculator_add_key(key);
		}
		else if (key == '+' || key == '-' || key == '*' || key == '/')
		{
			if (window_calculator_is_float())
			{
				g_operation_1.type = 2;
				g_operation_1.value.f = atof((const char *)g_show_data);
			}
			else
			{
				g_operation_1.type = 1;
				g_operation_1.value.i = atol((const char *)g_show_data);
			}
			radix_point_flag = 0;
			g_operation_sign = key;
			g_operation_status = 2;
		}
	}
	else if (g_operation_status == 2) // �����������׼�����������
	{
		if ((key >= '0' && key <= '9') || key == '-')
		{
			memset(g_show_data, 0, sizeof(g_show_data));
			window_calculator_add_key(key);
			g_operation_status = 3;
		}
		else if (key == '+' || key == '-' || key == '*' || key == '/' || key == '=') // ������
		{
			g_operation_sign = key;
		}
	}
	else if (g_operation_status == 3) // �������������
	{
		if ((key >= '0' && key <= '9') || key == '.')
		{
			window_calculator_add_key(key);
		}
		else if (key == '+' || key == '-' || key == '*' || key == '/' || key == '=')
		{
			if (window_calculator_is_float())
			{
				g_operation_2.type = 2;
				g_operation_2.value.f = atof((const char *)g_show_data);
			}
			else
			{
				g_operation_2.type = 1;
				g_operation_2.value.i = atol((const char *)g_show_data);
			}
			radix_point_flag = 0;
			window_calculator_compute();
			if (g_operation_status == 0)
				return;

			if (key == '=')
			{
				g_operation_sign = key;
				g_operation_status = 1;
			}
			else
			{
				g_operation_sign = key;
				g_operation_status = 2;
			}
		}
	}
}
