#ifndef __SYSTEM_UTIL_MATH_H__
#define __SYSTEM_UTIL_MATH_H__

#include "feature_all.h"

//Quake III中不可思议的求解平方根实现方法
//Lomont提出这个使用了更好的常数的函数
extern float math_sqrt_quake(float x);

//32位无符号整数开方得到16位无符号整数
extern unsigned short math_sqrt_16(unsigned int M);

extern int math_range(int value, int min, int max);

extern short math_get_average_data_short(short* data,short len);
extern int math_get_average_data_int(int* data,short len);

extern float lg3_interpolation(float x[], float y[], int n, float t);
extern float lgr_interpolation(float x[], float y[], int n, float t);

#endif

