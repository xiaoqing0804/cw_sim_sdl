#ifndef __FEATURE_DEFINE_H__
#define __FEATURE_DEFINE_H__

#ifndef NULL
#define NULL    0
#endif

#ifndef LIST_COUNT_PICTURE
#define LIST_COUNT_PICTURE(name)	  { &pic_##name##_01_info, \
										&pic_##name##_02_info, \
										&pic_##name##_03_info, \
										&pic_##name##_04_info, \
										&pic_##name##_05_info, \
										&pic_##name##_06_info, \
										&pic_##name##_07_info, \
										&pic_##name##_08_info, \
										&pic_##name##_09_info, \
										&pic_##name##_10_info,}
#endif


#ifndef LIST_NUMBER_PICTURE
#define LIST_NUMBER_PICTURE(name)	  { &pic_##name##_00_info, \
										&pic_##name##_01_info, \
										&pic_##name##_02_info, \
										&pic_##name##_03_info, \
										&pic_##name##_04_info, \
										&pic_##name##_05_info, \
										&pic_##name##_06_info, \
										&pic_##name##_07_info, \
										&pic_##name##_08_info, \
										&pic_##name##_09_info }
#endif

#ifndef LIST_SIZE_54_18_PICTURE
#define LIST_SIZE_54_18_PICTURE(name) { &pic_##name##_54_info, \
										&pic_##name##_50_info, \
										&pic_##name##_46_info, \
										&pic_##name##_42_info, \
										&pic_##name##_38_info, \
										&pic_##name##_34_info, \
										&pic_##name##_30_info, \
										&pic_##name##_26_info, \
										&pic_##name##_22_info, \
										&pic_##name##_18_info}
#endif

#ifndef LIST_SIZE_52_20_PICTURE
#define LIST_SIZE_52_20_PICTURE(name) { &pic_##name##_52_info, \
										&pic_##name##_48_info, \
										&pic_##name##_44_info, \
										&pic_##name##_40_info, \
										&pic_##name##_36_info, \
										&pic_##name##_32_info, \
										&pic_##name##_28_info, \
										&pic_##name##_24_info, \
										&pic_##name##_20_info}
#endif



#ifndef LIST_SIZE_65_20_PICTURE
#define LIST_SIZE_65_20_PICTURE(name) { &pic_##name##_88_info, \
										&pic_##name##_72_info, \
										&pic_##name##_66_info, \
										&pic_##name##_60_info, \
										&pic_##name##_52_info, \
										&pic_##name##_46_info, \
										&pic_##name##_30_info}

#endif

/*
{ &pic_##name##_88_info, \
										&pic_##name##_72_info, \
										&pic_##name##_66_info, \
										&pic_##name##_60_info, \
										&pic_##name##_52_info, \
										&pic_##name##_46_info, \
										&pic_##name##_30_info}

*/
#ifndef LIST_NUMBER_PICTURE_NULL
#define LIST_NUMBER_PICTURE_NULL	 { NULL }
#endif

#ifndef PICTURE_NAME
#define PICTURE_NAME(name)	 &pic_##name##_info
#endif


typedef enum
{
	ORIENTATION_TYPE_NONE,
	ORIENTATION_TYPE_HORIZONTAL,
	ORIENTATION_TYPE_VERTICAL,
	ORIENTATION_TYPE_ALL,
}ORIENTATION_TYPE;

typedef enum
{
	DIRECTION_TYPE_NONE,
	DIRECTION_TYPE_LEFT,
	DIRECTION_TYPE_RIGHT,
	DIRECTION_TYPE_UP,
	DIRECTION_TYPE_DOWN,
}DIRECTION_TYPE;


#endif

