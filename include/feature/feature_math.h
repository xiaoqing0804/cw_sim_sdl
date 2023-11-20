#ifndef __FEATURE_MATH_H__
#define __FEATURE_MATH_H__

#include "feature.h"

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif


//左极限，也就是不能小于min
#ifndef LEFT_LIMIT
#define LEFT_LIMIT(value, min) ((value) < (min) ? (min) : (value))
#endif

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif

//右极限，也就是不能小于max
#ifndef RIGHT_LIMIT
#define RIGHT_LIMIT(value, max) ((value) > (max) ? (max) : (value))
#endif

#ifndef ABS
#define ABS(a)   ((a) > 0 ? (a) : -(a))
#endif

#ifndef SHORT_MIN
#define SHORT_MIN 	(-32768)
#endif

#ifndef SHORT_MAX
#define SHORT_MAX 	(0x7FFF)
#endif

#ifndef INT_MAX
#define INT_MAX     (0x7fffffff)
#endif

#ifndef INT_MIN
#define INT_MIN     (-2147483648)
#endif

#ifndef CHAR_MAX
#define CHAR_MAX    (0x7F)
#endif

#ifndef CHAR_MIN
#define CHAR_MIN    (-128)
#endif

#ifndef UCHAR_MAX
#define UCHAR_MAX 	(0xFF)
#endif

#ifndef EPSILON
#define EPSILON (0.0001f)
#endif

#ifndef MATH_PI
#define MATH_PI  3.1415926f
#endif

#ifndef PI
#define PI  3.1415926f
#endif

#ifndef WIDTH_ALGIN_BYTE
#define WIDTH_ALGIN_BYTE(bits) ((((bits) + 31) / 32) * 4)
#endif

#ifndef FLOAT_EQUAL
#define FLOAT_EQUAL(number1,number2) ((float)(number1) > (float)((number2) - EPSILON) && (float)(number1) < ((float)(number2) + EPSILON))
#endif

#ifndef FLOAT_EQUAL_ZERO
#define FLOAT_EQUAL_ZERO(x) (((x) >= -EPSILON) && ((x) <= EPSILON))
#endif

#ifndef FLOAT_EQUAL_ONE
#define FLOAT_EQUAL_ONE(x) (((x) >= (1.0f - EPSILON)) && ((x) <= (1.0f + EPSILON)))
#endif

#ifndef ROUND
#define ROUND(value) ((value) + 0.5f)
#endif

#ifndef ROUND_2
#define ROUND_2(value) ((int)(((value) >= 0) ? ((value) + 0.5f) : ((value) - 0.5f)))
#endif

#ifndef FLOAT_TO_INT
#define FLOAT_TO_INT(value) ((int)(((value) >= 0) ? ((value) + EPSILON) : ((value)-EPSILON)))
#endif

#ifndef ANGLE_2_RADIAN
#define ANGLE_2_RADIAN(angle) ((angle) * PI / 180.0f)
#endif

#ifndef RADIAN_2_ANGLE
#define RADIAN_2_ANGLE(radian) ((radian) * 180.0f / PI )
#endif


#ifndef ANCHOR_VALUE
///把浮点型的锚点值转化为整数，使用128是做除法速度快，可以使用移位
#define ANCHOR_VALUE(anchor_float) ((short)(((anchor_float) >= 0 ? ((anchor_float)+EPSILON) : ((anchor_float)-EPSILON)) * 128))
#endif

#ifndef ANCHOR_CONVERT
///把数值（一般是宽或高）根据整数型锚点值转化为锚点的距离 (除以128)
#define ANCHOR_CONVERT(value, anchor_short) (((value) * (anchor_short)) / 128)  
#endif

#ifndef countof
#define countof(arr) (sizeof(arr)/sizeof(arr[0]))
#endif


typedef struct
{
	short x;
	short y;
	short width;
	short height;
}geometry_rect;

typedef struct
{
	short x;
	short y;
}geometry_point;

#endif


