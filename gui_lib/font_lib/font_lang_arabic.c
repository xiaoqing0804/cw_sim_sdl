﻿#include "font_lang_arabic.h"
#include "stdio.h"
#include "string.h"
#include "feature_all.h"
#include "font_convert.h"

static const unsigned short g_arbic_position_list[][4]=  // first, last, middle, alone
{
	{ 0xfe80, 0xfe80, 0xfe80, 0xfe80},    // 0x621
	{ 0xfe82, 0xfe81, 0xfe82, 0xfe81},    // 0x622
	{ 0xfe84, 0xfe83, 0xfe84, 0xfe83},    // 0x623
	{ 0xfe86, 0xfe85, 0xfe86, 0xfe85},    // 0x624
	{ 0xfe88, 0xfe87, 0xfe88, 0xfe87},    // 0x625
	{ 0xfe8a, 0xfe8b, 0xfe8c, 0xfe89},    // 0x626
	{ 0xfe8e, 0xfe8d, 0xfe8e, 0xfe8d},    // 0x627
	{ 0xfe90, 0xfe91, 0xfe92, 0xfe8f},   // 0x628
	{ 0xfe94, 0xfe93, 0xfe94, 0xfe93},    // 0x629
	{ 0xfe96, 0xfe97, 0xfe98, 0xfe95},   // 0x62A
	{ 0xfe9a, 0xfe9b, 0xfe9c, 0xfe99},    // 0x62B
	{ 0xfe9e, 0xfe9f, 0xfea0, 0xfe9d},    // 0x62C
	{ 0xfea2, 0xfea3, 0xfea4, 0xfea1},    // 0x62D
	{ 0xfea6, 0xfea7, 0xfea8, 0xfea5},    // 0x62E
	{ 0xfeaa, 0xfea9, 0xfeaa, 0xfea9},    // 0x62F
	{ 0xfeac, 0xfeab, 0xfeac, 0xfeab},   // 0x630
	{ 0xfeae, 0xfead, 0xfeae, 0xfead},    // 0x631
	{ 0xfeb0, 0xfeaf, 0xfeb0, 0xfeaf},    // 0x632
	{ 0xfeb2, 0xfeb3, 0xfeb4, 0xfeb1},    // 0x633
	{ 0xfeb6, 0xfeb7, 0xfeb8, 0xfeb5},    // 0x634
	{ 0xfeba, 0xfebb, 0xfebc, 0xfeb9},    // 0x635
	{ 0xfebe, 0xfebf, 0xfec0, 0xfebd},    // 0x636
	{ 0xfec2, 0xfec3, 0xfec4, 0xfec1},    // 0x637
	{ 0xfec6, 0xfec7, 0xfec8, 0xfec5},  // 0x638
	{ 0xfeca, 0xfecb, 0xfecc, 0xfec9},    // 0x639
	{ 0xfece, 0xfecf, 0xfed0, 0xfecd},  //0x63A
	{ 0x63b, 0x63b, 0x63b, 0x63b},    // 0x63B
	{ 0x63c, 0x63c, 0x63c, 0x63c},    // 0x63C
	{ 0x63d, 0x63d, 0x63d, 0x63d},    // 0x63D
	{ 0x63e, 0x63e, 0x63e, 0x63e},    // 0x63E
	{ 0x63f, 0x63f, 0x63f, 0x63f},    // 0x63F
	{ 0x640, 0x640, 0x640, 0x640},   // 0x640
	{ 0xfed2, 0xfed3, 0xfed4, 0xfed1},    // 0x641
	{ 0xfed6, 0xfed7, 0xfed8, 0xfed5},    // 0x642
	{ 0xfeda, 0xfedb, 0xfedc, 0xfed9},    // 0x643
	{ 0xfede, 0xfedf, 0xfee0, 0xfedd},    // 0x644
	{ 0xfee2, 0xfee3, 0xfee4, 0xfee1},    // 0x645
	{ 0xfee6, 0xfee7, 0xfee8, 0xfee5},    // 0x646
	{ 0xfeea, 0xfeeb, 0xfeec, 0xfee9},    // 0x647
	{ 0xfeee, 0xfeed, 0xfeee, 0xfeed},   // 0x648
	{ 0xfef0, 0xfef3, 0xfef4, 0xfeef},    // 0x649
	{ 0xfef2, 0xfef3, 0xfef4, 0xfef1},   // 0x64A
};
static const unsigned short g_arbic_set_list_1[24]=
{
	0x62c,  0x62d,  0x62e,  0x647,  0x639,  0x63a,  0x641,  0x642,
	0x62b,  0x635,  0x636,  0x637,  0x643,  0x645,  0x646,  0x62a,
	0x644,  0x628,  0x64a,  0x633,  0x634,  0x638,  0x626,  0x640 // 0x640 新增
};
static const unsigned short g_arbic_set_list_2[36]=
{
	0x62c,  0x62d,  0x62e,  0x647,  0x639,  0x63a,  0x641,  0x642,
	0x62b,  0x635,  0x636,  0x637,  0x643,  0x645,  0x646,  0x62a,
	0x644,  0x628,  0x64a,  0x633,  0x634,  0x638,  0x626,
	0x627,  0x623,  0x625,  0x622,  0x62f,  0x630,  0x631,  0x632,
	0x648,  0x624,  0x629,  0x649,  0x640 // 0x640 新增
};
//0x644-> 0x622/0x623/0x625/0x627
static const unsigned short g_arabic_specs[][2]=
{
	{0xFEF5, 0xFEF6},
	{0xFEF7, 0xFEF8},
	{0xFEF9, 0xFEFA},
	{0xFEFB, 0xFEFC},
};


unsigned char font_lang_arabic_check(unsigned short* unicode_str, unsigned int unicode_len)
{
	unsigned int n0 = 0;
	unsigned short unicode = 0;
	while(n0 < unicode_len)
	{
		unicode = unicode_str[n0];
		if((unicode >= 0x621) && (unicode <= 0x64A))
			return 1;
		n0++;
	}
	return 0;
}


//得到变形后的文字
unsigned int font_lang_arabic_letter_shape(unsigned short* unicode_str, unsigned int unicode_len)
{
	unsigned short *temp = unicode_str;
	unsigned short first_unicode;
	int n0 = 0, n1 = 0;
	unsigned long unicode = 0, unicode0 = 0, unicode1 = 0;
	unsigned char flag = 0;
	unsigned int index = 0;

	/* 1. get display string all len. */
	while(n0 < unicode_len)
	{
		/* 1.get unicode data. */
		if(n0 == 0)
			unicode0 = 0;
		else
			unicode0 = unicode_str[n0-1];
		
		unicode = unicode_str[n0];
		
		if((n0+1) >= unicode_len)
			unicode1 = 0;
		else
			unicode1 = unicode_str[n0+1];

		/* adjust char is change. */
		if((unicode >= 0x621)&&(unicode <= 0x64A))
		{
			flag = 0;
			/* 1. adjust before change. */
			for(unsigned char i = 0;i < countof(g_arbic_set_list_1);i++)
			{
				if(unicode0 == g_arbic_set_list_1[i])
				{
					flag |= 0x01;
					break;
				}
			}
			/* 2. adjust last change. */
			for(unsigned char i = 0;i < countof(g_arbic_set_list_2);i++)
			{
				if(unicode1 == g_arbic_set_list_2[i])
				{
					flag |= 0x02;
					break;
				}
			}
			/* 3. adjust middle change. */
			if(unicode == 0x644)
			{
				if((flag & 0x01) == 0)
					index = 0;
				else
					index = 1;

				switch(unicode1)
				{
					case 0x622:
						unicode = g_arabic_specs[0][index];
						flag = 0xFF;
						n0 += 1;
					break;

					case 0x623:
						unicode = g_arabic_specs[1][index];
						flag = 0xFF;
						n0 += 1;
					break;

					case 0x625:
						unicode = g_arabic_specs[2][index];
						flag = 0xFF;
						n0 += 1;
					break;

					case 0x627:
						unicode = g_arabic_specs[3][index];
						flag = 0xFF;
						n0 += 1;
					break;
				}
			}

			/* get change unicode. */
			if(flag < 4)
			{
				if(flag == 0)
					index = 3;
				else if(flag == 1)
					index = 0;
				else if(flag == 2)
					index = 1;
				else if(flag == 3)
					index = 2;

				unicode = g_arbic_position_list[unicode-0x621][index];
			}
		}

		if(0 == n1)
		{
			first_unicode = unicode;
		}
		else
		{
            temp[n1-1] = unicode;
		}

		/* point to next string char. */
		n0 += 1;
		n1 += 1;
	}

	/* switch data. */
	for(unsigned int i = n1-1;i >= 1;i--)
	{
		temp[i] = temp[i-1];
	}
	temp[0] = first_unicode;

	return n1;
}



