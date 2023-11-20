/***************************************************************************
** this file is all picture struct information source file, Color: RGB565
** by wpr
***************************************************************************/
#include "picture.h"
#include "picture_data.h"


const picture_info_struct pic_watchface_201_info = {
	.addr = (const unsigned char *)0x00000000,
	.width = 290,
	.height = 290,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)102259
};

const picture_info_struct pic_watch_201_roundDot_info = {
	.addr = (const unsigned char *)0x00018F74,
	.width = 16,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)669
};

const picture_info_struct pic_main_201_bg1_1_info = {
	.addr = (const unsigned char *)0x00019214,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)69065
};

const picture_info_struct pic_main_201_bg1_2_info = {
	.addr = (const unsigned char *)0x00029FE0,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)74001
};

const picture_info_struct pic_main_201_bg1_3_info = {
	.addr = (const unsigned char *)0x0003C0F4,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)49798
};

const picture_info_struct pic_main_201_bg1_4_info = {
	.addr = (const unsigned char *)0x0004837C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)47583
};

const picture_info_struct pic_main_201_gif_1_info = {
	.addr = (const unsigned char *)0x00053D5C,
	.width = 173,
	.height = 172,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)68298
};

const picture_info_struct pic_main_201_gif_5_info = {
	.addr = (const unsigned char *)0x00064828,
	.width = 173,
	.height = 172,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)64358
};

const picture_info_struct pic_main_201_gif_7_info = {
	.addr = (const unsigned char *)0x00074390,
	.width = 173,
	.height = 172,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)57553
};

const picture_info_struct pic_main_201_gif_8_info = {
	.addr = (const unsigned char *)0x00082464,
	.width = 173,
	.height = 171,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)63777
};

const picture_info_struct pic_main_202_hour_icon_1_info = {
	.addr = (const unsigned char *)0x00091D88,
	.width = 38,
	.height = 161,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12824
};

const picture_info_struct pic_main_202_min_icon_1_info = {
	.addr = (const unsigned char *)0x00094FA0,
	.width = 28,
	.height = 213,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)13185
};

const picture_info_struct pic_watchface_202_info = {
	.addr = (const unsigned char *)0x00098324,
	.width = 290,
	.height = 290,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)87427
};

const picture_info_struct pic_watch_202_roundDot_info = {
	.addr = (const unsigned char *)0x000AD8A8,
	.width = 18,
	.height = 18,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)648
};

const picture_info_struct pic_main_202_bg1_1_info = {
	.addr = (const unsigned char *)0x000ADB30,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)64442
};

const picture_info_struct pic_main_202_bg1_2_info = {
	.addr = (const unsigned char *)0x000BD6EC,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)57838
};

const picture_info_struct pic_main_202_bg1_3_info = {
	.addr = (const unsigned char *)0x000CB8DC,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)65839
};

const picture_info_struct pic_main_202_bg1_4_info = {
	.addr = (const unsigned char *)0x000DBA0C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)62756
};

const picture_alpha_piont_fast_struct pic_main_202_min_01_config[] = {
	{.start_y = 65,	.end_y = 277,	.max_width = 28,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_01_info = {
	.addr = (const unsigned char *)0x000EAF30,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_01_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_02_config[] = {
	{.start_y = 65,	.end_y = 277,	.max_width = 30,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_02_info = {
	.addr = (const unsigned char *)0x000EF6C0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_02_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_03_config[] = {
	{.start_y = 68,	.end_y = 277,	.max_width = 30,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_03_info = {
	.addr = (const unsigned char *)0x000F434C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_03_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_04_config[] = {
	{.start_y = 72,	.end_y = 276,	.max_width = 31,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_04_info = {
	.addr = (const unsigned char *)0x000F8EC4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_04_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_05_config[] = {
	{.start_y = 78,	.end_y = 274,	.max_width = 33,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_05_info = {
	.addr = (const unsigned char *)0x000FDAD8,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_05_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_06_config[] = {
	{.start_y = 86,	.end_y = 272,	.max_width = 34,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_06_info = {
	.addr = (const unsigned char *)0x00102894,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_06_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_07_config[] = {
	{.start_y = 96,	.end_y = 270,	.max_width = 37,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_07_info = {
	.addr = (const unsigned char *)0x0010748C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_07_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_08_config[] = {
	{.start_y = 107,	.end_y = 267,	.max_width = 40,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_08_info = {
	.addr = (const unsigned char *)0x0010C1CC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_08_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_09_config[] = {
	{.start_y = 119,	.end_y = 266,	.max_width = 44,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_09_info = {
	.addr = (const unsigned char *)0x00110E88,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_09_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_10_config[] = {
	{.start_y = 133,	.end_y = 264,	.max_width = 50,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_10_info = {
	.addr = (const unsigned char *)0x00115C00,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_10_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_11_config[] = {
	{.start_y = 146,	.end_y = 261,	.max_width = 59,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_11_info = {
	.addr = (const unsigned char *)0x0011AA60,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_11_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_12_config[] = {
	{.start_y = 160,	.end_y = 259,	.max_width = 72,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_12_info = {
	.addr = (const unsigned char *)0x0011FB7C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_12_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_13_config[] = {
	{.start_y = 175,	.end_y = 256,	.max_width = 82,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_13_info = {
	.addr = (const unsigned char *)0x001250A4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_13_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_14_config[] = {
	{.start_y = 191,	.end_y = 253,	.max_width = 121,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_14_info = {
	.addr = (const unsigned char *)0x0012A014,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_14_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_15_config[] = {
	{.start_y = 206,	.end_y = 250,	.max_width = 196,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_15_info = {
	.addr = (const unsigned char *)0x0012F9E8,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_15_config,
};

const picture_alpha_piont_fast_struct pic_main_202_min_16_config[] = {
	{.start_y = 219,	.end_y = 246,	.max_width = 213,	.data_offset = 0},
};

const picture_info_struct pic_main_202_min_16_info = {
	.addr = (const unsigned char *)0x001361A0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_min_16_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_01_config[] = {
	{.start_y = 114,	.end_y = 274,	.max_width = 38,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_01_info = {
	.addr = (const unsigned char *)0x0013A7BC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_01_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_02_config[] = {
	{.start_y = 114,	.end_y = 275,	.max_width = 40,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_02_info = {
	.addr = (const unsigned char *)0x0013F0B0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_02_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_03_config[] = {
	{.start_y = 116,	.end_y = 274,	.max_width = 41,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_03_info = {
	.addr = (const unsigned char *)0x00143DE4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_03_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_04_config[] = {
	{.start_y = 119,	.end_y = 273,	.max_width = 42,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_04_info = {
	.addr = (const unsigned char *)0x00148B88,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_04_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_05_config[] = {
	{.start_y = 124,	.end_y = 272,	.max_width = 44,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_05_info = {
	.addr = (const unsigned char *)0x0014D908,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_05_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_06_config[] = {
	{.start_y = 129,	.end_y = 270,	.max_width = 46,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_06_info = {
	.addr = (const unsigned char *)0x00152708,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_06_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_07_config[] = {
	{.start_y = 136,	.end_y = 269,	.max_width = 49,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_07_info = {
	.addr = (const unsigned char *)0x001574B0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_07_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_08_config[] = {
	{.start_y = 144,	.end_y = 268,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_08_info = {
	.addr = (const unsigned char *)0x0015C2B0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_08_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_09_config[] = {
	{.start_y = 151,	.end_y = 267,	.max_width = 59,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_09_info = {
	.addr = (const unsigned char *)0x00161150,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_09_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_10_config[] = {
	{.start_y = 158,	.end_y = 266,	.max_width = 67,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_10_info = {
	.addr = (const unsigned char *)0x00166320,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_10_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_11_config[] = {
	{.start_y = 167,	.end_y = 265,	.max_width = 76,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_11_info = {
	.addr = (const unsigned char *)0x0016B990,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_11_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_12_config[] = {
	{.start_y = 176,	.end_y = 263,	.max_width = 89,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_12_info = {
	.addr = (const unsigned char *)0x00171284,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_12_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_13_config[] = {
	{.start_y = 185,	.end_y = 260,	.max_width = 117,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_13_info = {
	.addr = (const unsigned char *)0x00176EFC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_13_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_14_config[] = {
	{.start_y = 195,	.end_y = 258,	.max_width = 144,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_14_info = {
	.addr = (const unsigned char *)0x0017D7C8,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_14_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_15_config[] = {
	{.start_y = 206,	.end_y = 255,	.max_width = 154,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_15_info = {
	.addr = (const unsigned char *)0x00184448,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_15_config,
};

const picture_alpha_piont_fast_struct pic_main_202_hour_16_config[] = {
	{.start_y = 214,	.end_y = 251,	.max_width = 161,	.data_offset = 0},
};

const picture_info_struct pic_main_202_hour_16_info = {
	.addr = (const unsigned char *)0x00189EE8,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_202_hour_16_config,
};

const picture_info_struct pic_watchface_203_info = {
	.addr = (const unsigned char *)0x0018E6E8,
	.width = 290,
	.height = 290,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)91233
};

const picture_info_struct pic_watch_203_roundDot_info = {
	.addr = (const unsigned char *)0x001A4B4C,
	.width = 18,
	.height = 18,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)648
};

const picture_info_struct pic_main_203_bg1_1_info = {
	.addr = (const unsigned char *)0x001A4DD4,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)42325
};

const picture_info_struct pic_main_203_bg1_2_info = {
	.addr = (const unsigned char *)0x001AF32C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)41514
};

const picture_info_struct pic_main_203_bg1_3_info = {
	.addr = (const unsigned char *)0x001B9558,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)44651
};

const picture_info_struct pic_main_203_bg1_4_info = {
	.addr = (const unsigned char *)0x001C43C4,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)45227
};

const picture_info_struct pic_main_203_weekPic5_1_info = {
	.addr = (const unsigned char *)0x001CF470,
	.width = 94,
	.height = 94,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4895
};

const picture_info_struct pic_main_203_weekPic5_2_info = {
	.addr = (const unsigned char *)0x001D0790,
	.width = 94,
	.height = 94,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4876
};

const picture_info_struct pic_main_203_weekPic5_3_info = {
	.addr = (const unsigned char *)0x001D1A9C,
	.width = 94,
	.height = 94,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4677
};

const picture_info_struct pic_main_203_weekPic5_4_info = {
	.addr = (const unsigned char *)0x001D2CE4,
	.width = 94,
	.height = 94,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4980
};

const picture_info_struct pic_main_203_weekPic5_5_info = {
	.addr = (const unsigned char *)0x001D4058,
	.width = 94,
	.height = 94,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4961
};

const picture_info_struct pic_main_203_weekPic5_6_info = {
	.addr = (const unsigned char *)0x001D53BC,
	.width = 94,
	.height = 94,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4540
};

const picture_info_struct pic_main_203_weekPic5_7_info = {
	.addr = (const unsigned char *)0x001D6578,
	.width = 94,
	.height = 94,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4905
};

const picture_info_struct pic_main_203_step_bpm_0_info = {
	.addr = (const unsigned char *)0x001D78A4,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)522
};

const picture_info_struct pic_main_203_step_bpm_1_info = {
	.addr = (const unsigned char *)0x001D7AB0,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)419
};

const picture_info_struct pic_main_203_step_bpm_2_info = {
	.addr = (const unsigned char *)0x001D7C54,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)498
};

const picture_info_struct pic_main_203_step_bpm_3_info = {
	.addr = (const unsigned char *)0x001D7E48,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)535
};

const picture_info_struct pic_main_203_step_bpm_4_info = {
	.addr = (const unsigned char *)0x001D8060,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)502
};

const picture_info_struct pic_main_203_step_bpm_5_info = {
	.addr = (const unsigned char *)0x001D8258,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)485
};

const picture_info_struct pic_main_203_step_bpm_6_info = {
	.addr = (const unsigned char *)0x001D8440,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)585
};

const picture_info_struct pic_main_203_step_bpm_7_info = {
	.addr = (const unsigned char *)0x001D868C,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)389
};

const picture_info_struct pic_main_203_step_bpm_8_info = {
	.addr = (const unsigned char *)0x001D8814,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)583
};

const picture_info_struct pic_main_203_step_bpm_9_info = {
	.addr = (const unsigned char *)0x001D8A5C,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)601
};

const picture_info_struct pic_main_204_hour_icon_info = {
	.addr = (const unsigned char *)0x001D8CB8,
	.width = 52,
	.height = 190,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)14534
};

const picture_info_struct pic_main_204_min_icon_info = {
	.addr = (const unsigned char *)0x001DC580,
	.width = 44,
	.height = 242,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)19415
};

const picture_info_struct pic_watchface_204_info = {
	.addr = (const unsigned char *)0x001E1158,
	.width = 290,
	.height = 290,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)67769
};

const picture_info_struct pic_watch_204_roundDot_info = {
	.addr = (const unsigned char *)0x001F1A14,
	.width = 18,
	.height = 18,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)648
};

const picture_info_struct pic_main_204_bg1_1_info = {
	.addr = (const unsigned char *)0x001F1C9C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)29420
};

const picture_info_struct pic_main_204_bg1_2_info = {
	.addr = (const unsigned char *)0x001F8F88,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)33874
};

const picture_info_struct pic_main_204_bg1_3_info = {
	.addr = (const unsigned char *)0x002013DC,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)25598
};

const picture_info_struct pic_main_204_bg1_4_info = {
	.addr = (const unsigned char *)0x002077DC,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)27828
};

const picture_alpha_piont_fast_struct pic_main_204_min_01_config[] = {
	{.start_y = 71,	.end_y = 260,	.max_width = 52,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_01_info = {
	.addr = (const unsigned char *)0x0020E490,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_01_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_02_config[] = {
	{.start_y = 71,	.end_y = 261,	.max_width = 54,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_02_info = {
	.addr = (const unsigned char *)0x002159D4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_02_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_03_config[] = {
	{.start_y = 73,	.end_y = 261,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_03_info = {
	.addr = (const unsigned char *)0x0021D430,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_03_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_04_config[] = {
	{.start_y = 77,	.end_y = 261,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_04_info = {
	.addr = (const unsigned char *)0x00224B10,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_04_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_05_config[] = {
	{.start_y = 83,	.end_y = 260,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_05_info = {
	.addr = (const unsigned char *)0x0022BF6C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_05_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_06_config[] = {
	{.start_y = 91,	.end_y = 261,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_06_info = {
	.addr = (const unsigned char *)0x00232F60,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_06_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_07_config[] = {
	{.start_y = 100,	.end_y = 260,	.max_width = 54,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_07_info = {
	.addr = (const unsigned char *)0x00239AEC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_07_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_08_config[] = {
	{.start_y = 110,	.end_y = 260,	.max_width = 54,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_08_info = {
	.addr = (const unsigned char *)0x00240210,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_08_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_09_config[] = {
	{.start_y = 122,	.end_y = 260,	.max_width = 58,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_09_info = {
	.addr = (const unsigned char *)0x002462CC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_09_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_10_config[] = {
	{.start_y = 135,	.end_y = 260,	.max_width = 66,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_10_info = {
	.addr = (const unsigned char *)0x0024C25C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_10_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_11_config[] = {
	{.start_y = 148,	.end_y = 259,	.max_width = 78,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_11_info = {
	.addr = (const unsigned char *)0x002524CC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_11_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_12_config[] = {
	{.start_y = 162,	.end_y = 259,	.max_width = 96,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_12_info = {
	.addr = (const unsigned char *)0x00258C0C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_12_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_13_config[] = {
	{.start_y = 176,	.end_y = 259,	.max_width = 126,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_13_info = {
	.addr = (const unsigned char *)0x0025FB10,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_13_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_14_config[] = {
	{.start_y = 191,	.end_y = 259,	.max_width = 168,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_14_info = {
	.addr = (const unsigned char *)0x002677C0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_14_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_15_config[] = {
	{.start_y = 206,	.end_y = 259,	.max_width = 186,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_15_info = {
	.addr = (const unsigned char *)0x00270024,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_15_config,
};

const picture_alpha_piont_fast_struct pic_main_204_min_16_config[] = {
	{.start_y = 207,	.end_y = 258,	.max_width = 190,	.data_offset = 0},
};

const picture_info_struct pic_main_204_min_16_info = {
	.addr = (const unsigned char *)0x00277644,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_min_16_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_01_config[] = {
	{.start_y = 71,	.end_y = 260,	.max_width = 52,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_01_info = {
	.addr = (const unsigned char *)0x0027EA74,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_01_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_02_config[] = {
	{.start_y = 71,	.end_y = 261,	.max_width = 54,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_02_info = {
	.addr = (const unsigned char *)0x00285FB8,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_02_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_03_config[] = {
	{.start_y = 73,	.end_y = 261,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_03_info = {
	.addr = (const unsigned char *)0x0028DA14,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_03_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_04_config[] = {
	{.start_y = 77,	.end_y = 261,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_04_info = {
	.addr = (const unsigned char *)0x002950F4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_04_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_05_config[] = {
	{.start_y = 83,	.end_y = 260,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_05_info = {
	.addr = (const unsigned char *)0x0029C550,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_05_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_06_config[] = {
	{.start_y = 91,	.end_y = 261,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_06_info = {
	.addr = (const unsigned char *)0x002A3544,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_06_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_07_config[] = {
	{.start_y = 100,	.end_y = 260,	.max_width = 54,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_07_info = {
	.addr = (const unsigned char *)0x002AA0D0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_07_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_08_config[] = {
	{.start_y = 110,	.end_y = 260,	.max_width = 54,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_08_info = {
	.addr = (const unsigned char *)0x002B07F4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_08_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_09_config[] = {
	{.start_y = 122,	.end_y = 260,	.max_width = 58,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_09_info = {
	.addr = (const unsigned char *)0x002B68B0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_09_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_10_config[] = {
	{.start_y = 135,	.end_y = 260,	.max_width = 66,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_10_info = {
	.addr = (const unsigned char *)0x002BC840,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_10_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_11_config[] = {
	{.start_y = 148,	.end_y = 259,	.max_width = 78,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_11_info = {
	.addr = (const unsigned char *)0x002C2AB0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_11_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_12_config[] = {
	{.start_y = 162,	.end_y = 259,	.max_width = 96,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_12_info = {
	.addr = (const unsigned char *)0x002C91F0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_12_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_13_config[] = {
	{.start_y = 176,	.end_y = 259,	.max_width = 126,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_13_info = {
	.addr = (const unsigned char *)0x002D00F4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_13_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_14_config[] = {
	{.start_y = 191,	.end_y = 259,	.max_width = 168,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_14_info = {
	.addr = (const unsigned char *)0x002D7DA4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_14_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_15_config[] = {
	{.start_y = 206,	.end_y = 259,	.max_width = 186,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_15_info = {
	.addr = (const unsigned char *)0x002E0608,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_15_config,
};

const picture_alpha_piont_fast_struct pic_main_204_hour_16_config[] = {
	{.start_y = 207,	.end_y = 258,	.max_width = 190,	.data_offset = 0},
};

const picture_info_struct pic_main_204_hour_16_info = {
	.addr = (const unsigned char *)0x002E7C28,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_204_hour_16_config,
};

const picture_info_struct pic_main_204_step_bpm_0_info = {
	.addr = (const unsigned char *)0x002EF058,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)522
};

const picture_info_struct pic_main_204_step_bpm_1_info = {
	.addr = (const unsigned char *)0x002EF264,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)419
};

const picture_info_struct pic_main_204_step_bpm_2_info = {
	.addr = (const unsigned char *)0x002EF408,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)498
};

const picture_info_struct pic_main_204_step_bpm_3_info = {
	.addr = (const unsigned char *)0x002EF5FC,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)535
};

const picture_info_struct pic_main_204_step_bpm_4_info = {
	.addr = (const unsigned char *)0x002EF814,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)502
};

const picture_info_struct pic_main_204_step_bpm_5_info = {
	.addr = (const unsigned char *)0x002EFA0C,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)485
};

const picture_info_struct pic_main_204_step_bpm_6_info = {
	.addr = (const unsigned char *)0x002EFBF4,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)585
};

const picture_info_struct pic_main_204_step_bpm_7_info = {
	.addr = (const unsigned char *)0x002EFE40,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)389
};

const picture_info_struct pic_main_204_step_bpm_8_info = {
	.addr = (const unsigned char *)0x002EFFC8,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)583
};

const picture_info_struct pic_main_204_step_bpm_9_info = {
	.addr = (const unsigned char *)0x002F0210,
	.width = 17,
	.height = 16,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)601
};

const picture_info_struct pic_main_204_battery_level_0_info = {
	.addr = (const unsigned char *)0x002F046C,
	.width = 136,
	.height = 136,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6049
};

const picture_info_struct pic_main_204_battery_level_100_info = {
	.addr = (const unsigned char *)0x002F1C10,
	.width = 136,
	.height = 136,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6030
};

const picture_info_struct pic_main_204_battery_level_25_info = {
	.addr = (const unsigned char *)0x002F33A0,
	.width = 136,
	.height = 136,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4047
};

const picture_info_struct pic_main_204_battery_level_50_info = {
	.addr = (const unsigned char *)0x002F4370,
	.width = 136,
	.height = 136,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5912
};

const picture_info_struct pic_main_204_battery_level_75_info = {
	.addr = (const unsigned char *)0x002F5A88,
	.width = 136,
	.height = 136,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4047
};

const picture_info_struct pic_main_205_hour_icon_info = {
	.addr = (const unsigned char *)0x002F6A58,
	.width = 46,
	.height = 175,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)10609
};

const picture_info_struct pic_main_205_min_icon_info = {
	.addr = (const unsigned char *)0x002F93CC,
	.width = 38,
	.height = 212,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)14819
};

const picture_info_struct pic_watchface_205_info = {
	.addr = (const unsigned char *)0x002FCDB0,
	.width = 290,
	.height = 290,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)125734
};

const picture_info_struct pic_watch_205_roundDot_info = {
	.addr = (const unsigned char *)0x0031B8D8,
	.width = 18,
	.height = 18,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)648
};

const picture_info_struct pic_main_205_bg1_1_info = {
	.addr = (const unsigned char *)0x0031BB60,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)71268
};

const picture_info_struct pic_main_205_bg1_2_info = {
	.addr = (const unsigned char *)0x0032D1C4,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)83569
};

const picture_info_struct pic_main_205_bg1_3_info = {
	.addr = (const unsigned char *)0x00341838,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)84082
};

const picture_info_struct pic_main_205_bg1_4_info = {
	.addr = (const unsigned char *)0x003560AC,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)84516
};

const picture_alpha_piont_fast_struct pic_main_205_min_01_config[] = {
	{.start_y = 43,	.end_y = 254,	.max_width = 38,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_01_info = {
	.addr = (const unsigned char *)0x0036AAD0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_01_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_02_config[] = {
	{.start_y = 43,	.end_y = 255,	.max_width = 40,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_02_info = {
	.addr = (const unsigned char *)0x00370AE0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_02_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_03_config[] = {
	{.start_y = 46,	.end_y = 256,	.max_width = 40,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_03_info = {
	.addr = (const unsigned char *)0x00377064,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_03_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_04_config[] = {
	{.start_y = 51,	.end_y = 256,	.max_width = 41,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_04_info = {
	.addr = (const unsigned char *)0x0037D4F4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_04_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_05_config[] = {
	{.start_y = 58,	.end_y = 256,	.max_width = 42,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_05_info = {
	.addr = (const unsigned char *)0x0038398C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_05_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_06_config[] = {
	{.start_y = 67,	.end_y = 256,	.max_width = 42,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_06_info = {
	.addr = (const unsigned char *)0x00389D0C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_06_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_07_config[] = {
	{.start_y = 77,	.end_y = 255,	.max_width = 41,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_07_info = {
	.addr = (const unsigned char *)0x0038FC0C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_07_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_08_config[] = {
	{.start_y = 89,	.end_y = 255,	.max_width = 43,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_08_info = {
	.addr = (const unsigned char *)0x00395374,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_08_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_09_config[] = {
	{.start_y = 103,	.end_y = 254,	.max_width = 48,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_09_info = {
	.addr = (const unsigned char *)0x0039A8EC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_09_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_10_config[] = {
	{.start_y = 118,	.end_y = 254,	.max_width = 56,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_10_info = {
	.addr = (const unsigned char *)0x0039FF9C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_10_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_11_config[] = {
	{.start_y = 135,	.end_y = 254,	.max_width = 66,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_11_info = {
	.addr = (const unsigned char *)0x003A5A98,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_11_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_12_config[] = {
	{.start_y = 152,	.end_y = 254,	.max_width = 81,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_12_info = {
	.addr = (const unsigned char *)0x003AB858,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_12_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_13_config[] = {
	{.start_y = 170,	.end_y = 254,	.max_width = 106,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_13_info = {
	.addr = (const unsigned char *)0x003B1AEC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_13_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_14_config[] = {
	{.start_y = 189,	.end_y = 253,	.max_width = 135,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_14_info = {
	.addr = (const unsigned char *)0x003B852C,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_14_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_15_config[] = {
	{.start_y = 208,	.end_y = 253,	.max_width = 206,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_15_info = {
	.addr = (const unsigned char *)0x003BEC84,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_15_config,
};

const picture_alpha_piont_fast_struct pic_main_205_min_16_config[] = {
	{.start_y = 214,	.end_y = 251,	.max_width = 212,	.data_offset = 0},
};

const picture_info_struct pic_main_205_min_16_info = {
	.addr = (const unsigned char *)0x003C5BEC,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_min_16_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_01_config[] = {
	{.start_y = 83,	.end_y = 257,	.max_width = 45,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_01_info = {
	.addr = (const unsigned char *)0x003CBAA0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_01_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_02_config[] = {
	{.start_y = 83,	.end_y = 258,	.max_width = 47,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_02_info = {
	.addr = (const unsigned char *)0x003D1848,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_02_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_03_config[] = {
	{.start_y = 86,	.end_y = 258,	.max_width = 48,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_03_info = {
	.addr = (const unsigned char *)0x003D7A98,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_03_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_04_config[] = {
	{.start_y = 89,	.end_y = 258,	.max_width = 49,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_04_info = {
	.addr = (const unsigned char *)0x003DDD44,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_04_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_05_config[] = {
	{.start_y = 95,	.end_y = 258,	.max_width = 48,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_05_info = {
	.addr = (const unsigned char *)0x003E4038,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_05_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_06_config[] = {
	{.start_y = 102,	.end_y = 257,	.max_width = 48,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_06_info = {
	.addr = (const unsigned char *)0x003E9DC0,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_06_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_07_config[] = {
	{.start_y = 110,	.end_y = 257,	.max_width = 48,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_07_info = {
	.addr = (const unsigned char *)0x003EF6B8,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_07_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_08_config[] = {
	{.start_y = 120,	.end_y = 257,	.max_width = 49,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_08_info = {
	.addr = (const unsigned char *)0x003F4B20,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_08_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_09_config[] = {
	{.start_y = 131,	.end_y = 257,	.max_width = 53,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_09_info = {
	.addr = (const unsigned char *)0x003F9B74,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_09_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_10_config[] = {
	{.start_y = 143,	.end_y = 257,	.max_width = 60,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_10_info = {
	.addr = (const unsigned char *)0x003FEB54,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_10_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_11_config[] = {
	{.start_y = 155,	.end_y = 256,	.max_width = 71,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_11_info = {
	.addr = (const unsigned char *)0x00403D18,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_11_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_12_config[] = {
	{.start_y = 169,	.end_y = 256,	.max_width = 84,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_12_info = {
	.addr = (const unsigned char *)0x004092C4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_12_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_13_config[] = {
	{.start_y = 183,	.end_y = 256,	.max_width = 98,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_13_info = {
	.addr = (const unsigned char *)0x0040EA14,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_13_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_14_config[] = {
	{.start_y = 198,	.end_y = 256,	.max_width = 135,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_14_info = {
	.addr = (const unsigned char *)0x00413FA4,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_14_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_15_config[] = {
	{.start_y = 209,	.end_y = 255,	.max_width = 172,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_15_info = {
	.addr = (const unsigned char *)0x00419D74,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_15_config,
};

const picture_alpha_piont_fast_struct pic_main_205_hour_16_config[] = {
	{.start_y = 210,	.end_y = 254,	.max_width = 175,	.data_offset = 0},
};

const picture_info_struct pic_main_205_hour_16_info = {
	.addr = (const unsigned char *)0x0041FC90,
	.width = 466,
	.height = 466,
	.alpha = 9,
	.external_flag = 1,
	.zoom_count = 1,
	.config = (const void *)pic_main_205_hour_16_config,
};

const picture_info_struct pic_main_012_bg_info = {
	.addr = (const unsigned char *)0x00425934,
	.width = 466,
	.height = 466,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)48390
};

const picture_info_struct pic_main_012_data_0_info = {
	.addr = (const unsigned char *)0x0043163C,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)976
};

const picture_info_struct pic_main_012_data_1_info = {
	.addr = (const unsigned char *)0x00431A0C,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)616
};

const picture_info_struct pic_main_012_data_2_info = {
	.addr = (const unsigned char *)0x00431C74,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)899
};

const picture_info_struct pic_main_012_data_3_info = {
	.addr = (const unsigned char *)0x00431FF8,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)906
};

const picture_info_struct pic_main_012_data_4_info = {
	.addr = (const unsigned char *)0x00432384,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)959
};

const picture_info_struct pic_main_012_data_5_info = {
	.addr = (const unsigned char *)0x00432744,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)965
};

const picture_info_struct pic_main_012_data_6_info = {
	.addr = (const unsigned char *)0x00432B0C,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)907
};

const picture_info_struct pic_main_012_data_7_info = {
	.addr = (const unsigned char *)0x00432E98,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)768
};

const picture_info_struct pic_main_012_data_8_info = {
	.addr = (const unsigned char *)0x00433198,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1040
};

const picture_info_struct pic_main_012_data_9_info = {
	.addr = (const unsigned char *)0x004335A8,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)905
};

const picture_info_struct pic_main_012_data_dou_info = {
	.addr = (const unsigned char *)0x00433934,
	.width = 26,
	.height = 26,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)292
};

const picture_info_struct pic_main_012_min_0_info = {
	.addr = (const unsigned char *)0x00433A58,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4753
};

const picture_info_struct pic_main_012_min_1_info = {
	.addr = (const unsigned char *)0x00434CEC,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3189
};

const picture_info_struct pic_main_012_min_2_info = {
	.addr = (const unsigned char *)0x00435964,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4928
};

const picture_info_struct pic_main_012_min_3_info = {
	.addr = (const unsigned char *)0x00436CA4,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4764
};

const picture_info_struct pic_main_012_min_4_info = {
	.addr = (const unsigned char *)0x00437F40,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4803
};

const picture_info_struct pic_main_012_min_5_info = {
	.addr = (const unsigned char *)0x00439204,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5149
};

const picture_info_struct pic_main_012_min_6_info = {
	.addr = (const unsigned char *)0x0043A624,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4838
};

const picture_info_struct pic_main_012_min_7_info = {
	.addr = (const unsigned char *)0x0043B90C,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4183
};

const picture_info_struct pic_main_012_min_8_info = {
	.addr = (const unsigned char *)0x0043C964,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4761
};

const picture_info_struct pic_main_012_min_9_info = {
	.addr = (const unsigned char *)0x0043DC00,
	.width = 84,
	.height = 84,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4319
};

const picture_info_struct pic_main_012_hour_00_info = {
	.addr = (const unsigned char *)0x0043ECE0,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4196
};

const picture_info_struct pic_main_012_hour_01_info = {
	.addr = (const unsigned char *)0x0043FD44,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2906
};

const picture_info_struct pic_main_012_hour_02_info = {
	.addr = (const unsigned char *)0x004408A0,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4359
};

const picture_info_struct pic_main_012_hour_03_info = {
	.addr = (const unsigned char *)0x004419A8,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4200
};

const picture_info_struct pic_main_012_hour_04_info = {
	.addr = (const unsigned char *)0x00442A10,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4297
};

const picture_info_struct pic_main_012_hour_05_info = {
	.addr = (const unsigned char *)0x00443ADC,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4380
};

const picture_info_struct pic_main_012_hour_06_info = {
	.addr = (const unsigned char *)0x00444BF8,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4387
};

const picture_info_struct pic_main_012_hour_07_info = {
	.addr = (const unsigned char *)0x00445D1C,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3697
};

const picture_info_struct pic_main_012_hour_08_info = {
	.addr = (const unsigned char *)0x00446B90,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4355
};

const picture_info_struct pic_main_012_hour_09_info = {
	.addr = (const unsigned char *)0x00447C94,
	.width = 118,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3979
};

const picture_info_struct pic_main_012_week_Breathing_plate_1_info = {
	.addr = (const unsigned char *)0x00448C20,
	.width = 62,
	.height = 58,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2639
};

const picture_info_struct pic_main_012_week_Breathing_plate_2_info = {
	.addr = (const unsigned char *)0x00449670,
	.width = 62,
	.height = 58,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2212
};

const picture_info_struct pic_main_012_week_Breathing_plate_3_info = {
	.addr = (const unsigned char *)0x00449F14,
	.width = 62,
	.height = 58,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3052
};

const picture_info_struct pic_main_012_week_Breathing_plate_4_info = {
	.addr = (const unsigned char *)0x0044AB00,
	.width = 62,
	.height = 58,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2265
};

const picture_info_struct pic_main_012_week_Breathing_plate_5_info = {
	.addr = (const unsigned char *)0x0044B3DC,
	.width = 62,
	.height = 58,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1808
};

const picture_info_struct pic_main_012_week_Breathing_plate_6_info = {
	.addr = (const unsigned char *)0x0044BAEC,
	.width = 62,
	.height = 58,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2206
};

const picture_info_struct pic_main_012_week_Breathing_plate_7_info = {
	.addr = (const unsigned char *)0x0044C38C,
	.width = 62,
	.height = 58,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2318
};

const picture_info_struct pic_main_012_month_1_info = {
	.addr = (const unsigned char *)0x0044CC9C,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2072
};

const picture_info_struct pic_main_012_month_10_info = {
	.addr = (const unsigned char *)0x0044D4B4,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2183
};

const picture_info_struct pic_main_012_month_11_info = {
	.addr = (const unsigned char *)0x0044DD3C,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2289
};

const picture_info_struct pic_main_012_month_12_info = {
	.addr = (const unsigned char *)0x0044E630,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2407
};

const picture_info_struct pic_main_012_month_2_info = {
	.addr = (const unsigned char *)0x0044EF98,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2465
};

const picture_info_struct pic_main_012_month_3_info = {
	.addr = (const unsigned char *)0x0044F93C,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2450
};

const picture_info_struct pic_main_012_month_4_info = {
	.addr = (const unsigned char *)0x004502D0,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2247
};

const picture_info_struct pic_main_012_month_5_info = {
	.addr = (const unsigned char *)0x00450B98,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2668
};

const picture_info_struct pic_main_012_month_6_info = {
	.addr = (const unsigned char *)0x00451604,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2016
};

const picture_info_struct pic_main_012_month_7_info = {
	.addr = (const unsigned char *)0x00451DE4,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1847
};

const picture_info_struct pic_main_012_month_8_info = {
	.addr = (const unsigned char *)0x0045251C,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2522
};

const picture_info_struct pic_main_012_month_9_info = {
	.addr = (const unsigned char *)0x00452EF8,
	.width = 58,
	.height = 53,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2455
};

const picture_info_struct pic_main_010_point_info = {
	.addr = (const unsigned char *)0x00453890,
	.width = 14,
	.height = 14,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)624
};

const picture_info_struct pic_main_010_hour_01_info = {
	.addr = (const unsigned char *)0x00453B00,
	.width = 29,
	.height = 181,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5799
};

const picture_info_struct pic_main_010_min_01_info = {
	.addr = (const unsigned char *)0x004551A8,
	.width = 29,
	.height = 223,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)7094
};

const picture_info_struct pic_main_010_day_0_info = {
	.addr = (const unsigned char *)0x00456D60,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)816
};

const picture_info_struct pic_main_010_day_1_info = {
	.addr = (const unsigned char *)0x00457090,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)428
};

const picture_info_struct pic_main_010_day_2_info = {
	.addr = (const unsigned char *)0x0045723C,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)669
};

const picture_info_struct pic_main_010_day_3_info = {
	.addr = (const unsigned char *)0x004574DC,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)781
};

const picture_info_struct pic_main_010_day_4_info = {
	.addr = (const unsigned char *)0x004577EC,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)657
};

const picture_info_struct pic_main_010_day_5_info = {
	.addr = (const unsigned char *)0x00457A80,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)729
};

const picture_info_struct pic_main_010_day_6_info = {
	.addr = (const unsigned char *)0x00457D5C,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)848
};

const picture_info_struct pic_main_010_day_7_info = {
	.addr = (const unsigned char *)0x004580AC,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)529
};

const picture_info_struct pic_main_010_day_8_info = {
	.addr = (const unsigned char *)0x004582C0,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)830
};

const picture_info_struct pic_main_010_day_9_info = {
	.addr = (const unsigned char *)0x00458600,
	.width = 16,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)835
};

const picture_info_struct pic_main_010_week_1_a_info = {
	.addr = (const unsigned char *)0x00458944,
	.width = 62,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2491
};

const picture_info_struct pic_main_010_week_2_a_info = {
	.addr = (const unsigned char *)0x00459300,
	.width = 62,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1522
};

const picture_info_struct pic_main_010_week_3_a_info = {
	.addr = (const unsigned char *)0x004598F4,
	.width = 62,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2076
};

const picture_info_struct pic_main_010_week_4_a_info = {
	.addr = (const unsigned char *)0x0045A110,
	.width = 62,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1843
};

const picture_info_struct pic_main_010_week_5_a_info = {
	.addr = (const unsigned char *)0x0045A844,
	.width = 62,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1395
};

const picture_info_struct pic_main_010_week_6_a_info = {
	.addr = (const unsigned char *)0x0045ADB8,
	.width = 62,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1589
};

const picture_info_struct pic_main_010_week_7_a_info = {
	.addr = (const unsigned char *)0x0045B3F0,
	.width = 62,
	.height = 21,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2126
};

const picture_info_struct pic_main_setting_bg_info = {
	.addr = (const unsigned char *)0x0045BC40,
	.width = 466,
	.height = 466,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)96626
};

const picture_info_struct pic_main_setting_heart_info = {
	.addr = (const unsigned char *)0x004735B4,
	.width = 30,
	.height = 30,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1971
};

const picture_info_struct pic_main_setting_sleep_info = {
	.addr = (const unsigned char *)0x00473D68,
	.width = 24,
	.height = 23,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)964
};

const picture_info_struct pic_main_setting_step_info = {
	.addr = (const unsigned char *)0x0047412C,
	.width = 35,
	.height = 35,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2819
};

const picture_info_struct pic_watchface_setting_info = {
	.addr = (const unsigned char *)0x00474C30,
	.width = 291,
	.height = 291,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)52057
};

const picture_info_struct pic_watchface_user_define_info = {
	.addr = (const unsigned char *)0x0048178C,
	.width = 150,
	.height = 150,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5203
};

const picture_info_struct pic_watchface_background_info = {
	.addr = (const unsigned char *)0x00482BE0,
	.width = 8,
	.height = 140,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1052
};

const picture_info_struct pic_watchface_block_info = {
	.addr = (const unsigned char *)0x00482FFC,
	.width = 8,
	.height = 25,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)247
};

const picture_info_struct pic_Hello_bg_info = {
	.addr = (const unsigned char *)0x004830F4,
	.width = 212,
	.height = 83,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5536
};

const picture_info_struct pic_app_about_88_info = {
	.addr = (const unsigned char *)0x00484694,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)7573
};

const picture_info_struct pic_app_add_88_info = {
	.addr = (const unsigned char *)0x0048642C,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16049
};

const picture_info_struct pic_app_alipay_88_info = {
	.addr = (const unsigned char *)0x0048A2E0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15641
};

const picture_info_struct pic_app_aod_88_info = {
	.addr = (const unsigned char *)0x0048DFFC,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)10319
};

const picture_info_struct pic_app_BP_88_info = {
	.addr = (const unsigned char *)0x0049084C,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12472
};

const picture_info_struct pic_app_breath_88_info = {
	.addr = (const unsigned char *)0x00493904,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15049
};

const picture_info_struct pic_app_brightness_88_info = {
	.addr = (const unsigned char *)0x004973D0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16321
};

const picture_info_struct pic_app_calc_88_info = {
	.addr = (const unsigned char *)0x0049B394,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15016
};

const picture_info_struct pic_app_calendar_88_info = {
	.addr = (const unsigned char *)0x0049EE3C,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)9225
};

const picture_info_struct pic_app_clock_88_info = {
	.addr = (const unsigned char *)0x004A1248,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16509
};

const picture_info_struct pic_app_counter_88_info = {
	.addr = (const unsigned char *)0x004A52C8,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12686
};

const picture_info_struct pic_app_disturb_88_info = {
	.addr = (const unsigned char *)0x004A8458,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)7372
};

const picture_info_struct pic_app_findphone_88_info = {
	.addr = (const unsigned char *)0x004AA124,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)10379
};

const picture_info_struct pic_app_game_88_info = {
	.addr = (const unsigned char *)0x004AC9B0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)14940
};

const picture_info_struct pic_app_hfp_no_88_info = {
	.addr = (const unsigned char *)0x004B040C,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15190
};

const picture_info_struct pic_app_hfp_yes_88_info = {
	.addr = (const unsigned char *)0x004B3F64,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)17255
};

const picture_info_struct pic_app_home_88_info = {
	.addr = (const unsigned char *)0x004B82CC,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12250
};

const picture_info_struct pic_app_hr_88_info = {
	.addr = (const unsigned char *)0x004BB2A8,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)11371
};

const picture_info_struct pic_app_language_88_info = {
	.addr = (const unsigned char *)0x004BDF14,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15322
};

const picture_info_struct pic_app_lcd_clock_88_info = {
	.addr = (const unsigned char *)0x004C1AF0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12553
};

const picture_info_struct pic_app_lcd_time_88_info = {
	.addr = (const unsigned char *)0x004C4BFC,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16748
};

const picture_info_struct pic_app_lock_88_info = {
	.addr = (const unsigned char *)0x004C8D68,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)11158
};

const picture_info_struct pic_app_menu_set_88_info = {
	.addr = (const unsigned char *)0x004CB900,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16051
};

const picture_info_struct pic_app_message_88_info = {
	.addr = (const unsigned char *)0x004CF7B4,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)9828
};

const picture_info_struct pic_app_music_88_info = {
	.addr = (const unsigned char *)0x004D1E18,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12208
};

const picture_info_struct pic_app_nfc_88_info = {
	.addr = (const unsigned char *)0x004D4DC8,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12981
};

const picture_info_struct pic_app_O2_88_info = {
	.addr = (const unsigned char *)0x004D8080,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16574
};

const picture_info_struct pic_app_password_88_info = {
	.addr = (const unsigned char *)0x004DC140,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)10910
};

const picture_info_struct pic_app_photograph_88_info = {
	.addr = (const unsigned char *)0x004DEBE0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)9734
};

const picture_info_struct pic_app_QR_code_88_info = {
	.addr = (const unsigned char *)0x004E11E8,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)18522
};

const picture_info_struct pic_app_qr_push_88_info = {
	.addr = (const unsigned char *)0x004E5A44,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)18448
};

const picture_info_struct pic_app_reboot_88_info = {
	.addr = (const unsigned char *)0x004EA254,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)19773
};

const picture_info_struct pic_app_restore_88_info = {
	.addr = (const unsigned char *)0x004EEF94,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15035
};

const picture_info_struct pic_app_screen_set_88_info = {
	.addr = (const unsigned char *)0x004F2A50,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)18512
};

const picture_info_struct pic_app_setting_88_info = {
	.addr = (const unsigned char *)0x004F72A0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15401
};

const picture_info_struct pic_app_shutdown_88_info = {
	.addr = (const unsigned char *)0x004FAECC,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12480
};

const picture_info_struct pic_app_siri_88_info = {
	.addr = (const unsigned char *)0x004FDF8C,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12553
};

const picture_info_struct pic_app_sleep_88_info = {
	.addr = (const unsigned char *)0x00501098,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)13380
};

const picture_info_struct pic_app_sos_88_info = {
	.addr = (const unsigned char *)0x005044DC,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15076
};

const picture_info_struct pic_app_sport_outdoor_88_info = {
	.addr = (const unsigned char *)0x00507FC0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)18982
};

const picture_info_struct pic_app_sport_records_88_info = {
	.addr = (const unsigned char *)0x0050C9E8,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)10251
};

const picture_info_struct pic_app_steps_88_info = {
	.addr = (const unsigned char *)0x0050F1F4,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)13619
};

const picture_info_struct pic_app_stopwatch_88_info = {
	.addr = (const unsigned char *)0x00512728,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)15224
};

const picture_info_struct pic_app_style_88_info = {
	.addr = (const unsigned char *)0x005162A0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16665
};

const picture_info_struct pic_app_telephone_88_info = {
	.addr = (const unsigned char *)0x0051A3BC,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)9233
};

const picture_info_struct pic_app_wake_timeout_88_info = {
	.addr = (const unsigned char *)0x0051C7D0,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16838
};

const picture_info_struct pic_app_watchface_88_info = {
	.addr = (const unsigned char *)0x00520998,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12776
};

const picture_info_struct pic_app_weather_88_info = {
	.addr = (const unsigned char *)0x00523B80,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)8617
};

const picture_info_struct pic_app_woman_88_info = {
	.addr = (const unsigned char *)0x00525D2C,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)17999
};

const picture_info_struct pic_zhifubao_code_info = {
	.addr = (const unsigned char *)0x0052A37C,
	.width = 50,
	.height = 50,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2017
};

const picture_info_struct pic_zhifubao_helper_info = {
	.addr = (const unsigned char *)0x0052AB60,
	.width = 50,
	.height = 50,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2868
};

const picture_info_struct pic_zhifubao_icon_info = {
	.addr = (const unsigned char *)0x0052B694,
	.width = 60,
	.height = 60,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2028
};

const picture_info_struct pic_zhifubao_logo_info = {
	.addr = (const unsigned char *)0x0052BE80,
	.width = 48,
	.height = 48,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3420
};

const picture_info_struct pic_zhifubao_no_info = {
	.addr = (const unsigned char *)0x0052CBDC,
	.width = 164,
	.height = 164,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4447
};

const picture_info_struct pic_zhifubao_op1_bg_info = {
	.addr = (const unsigned char *)0x0052DD3C,
	.width = 217,
	.height = 75,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2392
};

const picture_info_struct pic_zhifubao_op1_h_bg_info = {
	.addr = (const unsigned char *)0x0052E694,
	.width = 217,
	.height = 75,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2177
};

const picture_info_struct pic_zhifubao_op2_bg_info = {
	.addr = (const unsigned char *)0x0052EF18,
	.width = 164,
	.height = 78,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7369
};

const picture_info_struct pic_zhifubao_op2_h_bg_info = {
	.addr = (const unsigned char *)0x00530BE4,
	.width = 164,
	.height = 78,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)8594
};

const picture_info_struct pic_zhifubao_round_l_bar_info = {
	.addr = (const unsigned char *)0x00532D78,
	.width = 398,
	.height = 113,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4391
};

const picture_info_struct pic_zhifubao_setting_info = {
	.addr = (const unsigned char *)0x00533EA0,
	.width = 50,
	.height = 50,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2114
};

const picture_info_struct pic_zhifubao_startup_info = {
	.addr = (const unsigned char *)0x005346E4,
	.width = 130,
	.height = 161,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7334
};

const picture_info_struct pic_zhifubao_yes_info = {
	.addr = (const unsigned char *)0x0053638C,
	.width = 164,
	.height = 164,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3992
};

const picture_info_struct pic_alipay_Gif_02_info = {
	.addr = (const unsigned char *)0x00537324,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2004
};

const picture_info_struct pic_alipay_Gif_03_info = {
	.addr = (const unsigned char *)0x00537AF8,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2246
};

const picture_info_struct pic_alipay_Gif_05_info = {
	.addr = (const unsigned char *)0x005383C0,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2767
};

const picture_info_struct pic_alipay_Gif_07_info = {
	.addr = (const unsigned char *)0x00538E90,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3405
};

const picture_info_struct pic_alipay_Gif_09_info = {
	.addr = (const unsigned char *)0x00539BE0,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3962
};

const picture_info_struct pic_alipay_Gif_11_info = {
	.addr = (const unsigned char *)0x0053AB5C,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4497
};

const picture_info_struct pic_alipay_Gif_13_info = {
	.addr = (const unsigned char *)0x0053BCF0,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5082
};

const picture_info_struct pic_alipay_Gif_15_info = {
	.addr = (const unsigned char *)0x0053D0CC,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5644
};

const picture_info_struct pic_alipay_Gif_17_info = {
	.addr = (const unsigned char *)0x0053E6D8,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)6098
};

const picture_info_struct pic_alipay_Gif_19_info = {
	.addr = (const unsigned char *)0x0053FEAC,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)6674
};

const picture_info_struct pic_alipay_Gif_21_info = {
	.addr = (const unsigned char *)0x005418C0,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7314
};

const picture_info_struct pic_alipay_Gif_23_info = {
	.addr = (const unsigned char *)0x00543554,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7928
};

const picture_info_struct pic_alipay_Gif_25_info = {
	.addr = (const unsigned char *)0x0054544C,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)8480
};

const picture_info_struct pic_alipay_Gif_27_info = {
	.addr = (const unsigned char *)0x0054756C,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9108
};

const picture_info_struct pic_alipay_Gif_29_info = {
	.addr = (const unsigned char *)0x00549900,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9746
};

const picture_info_struct pic_alipay_Gif_31_info = {
	.addr = (const unsigned char *)0x0054BF14,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9824
};

const picture_info_struct pic_alipay_Gif_33_info = {
	.addr = (const unsigned char *)0x0054E574,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9746
};

const picture_info_struct pic_alipay_Gif_35_info = {
	.addr = (const unsigned char *)0x00550B88,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9106
};

const picture_info_struct pic_alipay_Gif_37_info = {
	.addr = (const unsigned char *)0x00552F1C,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)8480
};

const picture_info_struct pic_alipay_Gif_39_info = {
	.addr = (const unsigned char *)0x0055503C,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7928
};

const picture_info_struct pic_alipay_Gif_41_info = {
	.addr = (const unsigned char *)0x00556F34,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7314
};

const picture_info_struct pic_alipay_Gif_43_info = {
	.addr = (const unsigned char *)0x00558BC8,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)6674
};

const picture_info_struct pic_alipay_Gif_45_info = {
	.addr = (const unsigned char *)0x0055A5DC,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)6098
};

const picture_info_struct pic_alipay_Gif_47_info = {
	.addr = (const unsigned char *)0x0055BDB0,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5637
};

const picture_info_struct pic_alipay_Gif_49_info = {
	.addr = (const unsigned char *)0x0055D3B8,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5075
};

const picture_info_struct pic_alipay_Gif_51_info = {
	.addr = (const unsigned char *)0x0055E78C,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4466
};

const picture_info_struct pic_alipay_Gif_53_info = {
	.addr = (const unsigned char *)0x0055F900,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3854
};

const picture_info_struct pic_alipay_Gif_55_info = {
	.addr = (const unsigned char *)0x00560810,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3321
};

const picture_info_struct pic_alipay_Gif_57_info = {
	.addr = (const unsigned char *)0x0056150C,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2767
};

const picture_info_struct pic_alipay_Gif_59_info = {
	.addr = (const unsigned char *)0x00561FDC,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2246
};

const picture_info_struct pic_alipay_Gif_60_info = {
	.addr = (const unsigned char *)0x005628A4,
	.width = 142,
	.height = 142,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2004
};

const picture_info_struct pic_QR_code_info = {
	.addr = (const unsigned char *)0x00563078,
	.width = 160,
	.height = 160,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)21249
};

const picture_info_struct pic_sidebar_date_00_info = {
	.addr = (const unsigned char *)0x0056837C,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)292
};

const picture_info_struct pic_sidebar_date_01_info = {
	.addr = (const unsigned char *)0x005684A0,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)210
};

const picture_info_struct pic_sidebar_date_02_info = {
	.addr = (const unsigned char *)0x00568574,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)257
};

const picture_info_struct pic_sidebar_date_03_info = {
	.addr = (const unsigned char *)0x00568678,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)281
};

const picture_info_struct pic_sidebar_date_04_info = {
	.addr = (const unsigned char *)0x00568794,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)264
};

const picture_info_struct pic_sidebar_date_05_info = {
	.addr = (const unsigned char *)0x0056889C,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)263
};

const picture_info_struct pic_sidebar_date_06_info = {
	.addr = (const unsigned char *)0x005689A4,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)297
};

const picture_info_struct pic_sidebar_date_07_info = {
	.addr = (const unsigned char *)0x00568AD0,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)214
};

const picture_info_struct pic_sidebar_date_08_info = {
	.addr = (const unsigned char *)0x00568BA8,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)301
};

const picture_info_struct pic_sidebar_date_09_info = {
	.addr = (const unsigned char *)0x00568CD8,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)295
};

const picture_info_struct pic_sidebar_date_line_info = {
	.addr = (const unsigned char *)0x00568E00,
	.width = 10,
	.height = 13,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)103
};

const picture_info_struct pic_sidebar_time_00_info = {
	.addr = (const unsigned char *)0x00568E68,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)870
};

const picture_info_struct pic_sidebar_time_01_info = {
	.addr = (const unsigned char *)0x005691D0,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)616
};

const picture_info_struct pic_sidebar_time_02_info = {
	.addr = (const unsigned char *)0x00569438,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)706
};

const picture_info_struct pic_sidebar_time_03_info = {
	.addr = (const unsigned char *)0x005696FC,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)766
};

const picture_info_struct pic_sidebar_time_04_info = {
	.addr = (const unsigned char *)0x005699FC,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)712
};

const picture_info_struct pic_sidebar_time_05_info = {
	.addr = (const unsigned char *)0x00569CC4,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)769
};

const picture_info_struct pic_sidebar_time_06_info = {
	.addr = (const unsigned char *)0x00569FC8,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)891
};

const picture_info_struct pic_sidebar_time_07_info = {
	.addr = (const unsigned char *)0x0056A344,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)567
};

const picture_info_struct pic_sidebar_time_08_info = {
	.addr = (const unsigned char *)0x0056A57C,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)908
};

const picture_info_struct pic_sidebar_time_09_info = {
	.addr = (const unsigned char *)0x0056A908,
	.width = 22,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)887
};

const picture_info_struct pic_sidebar_time_dot_info = {
	.addr = (const unsigned char *)0x0056AC80,
	.width = 6,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)304
};

const picture_info_struct pic_sidebar_week_fri_info = {
	.addr = (const unsigned char *)0x0056ADB0,
	.width = 40,
	.height = 15,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)623
};

const picture_info_struct pic_sidebar_week_mon_info = {
	.addr = (const unsigned char *)0x0056B020,
	.width = 40,
	.height = 15,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)983
};

const picture_info_struct pic_sidebar_week_sat_info = {
	.addr = (const unsigned char *)0x0056B3F8,
	.width = 40,
	.height = 15,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)709
};

const picture_info_struct pic_sidebar_week_sun_info = {
	.addr = (const unsigned char *)0x0056B6C0,
	.width = 40,
	.height = 15,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)919
};

const picture_info_struct pic_sidebar_week_thu_info = {
	.addr = (const unsigned char *)0x0056BA58,
	.width = 42,
	.height = 15,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)645
};

const picture_info_struct pic_sidebar_week_tue_info = {
	.addr = (const unsigned char *)0x0056BCE0,
	.width = 40,
	.height = 15,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)730
};

const picture_info_struct pic_sidebar_week_wed_info = {
	.addr = (const unsigned char *)0x0056BFBC,
	.width = 40,
	.height = 15,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)917
};

const picture_info_struct pic_sidebar_steps_info = {
	.addr = (const unsigned char *)0x0056C354,
	.width = 25,
	.height = 25,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)814
};

const picture_info_struct pic_quick_bg_info = {
	.addr = (const unsigned char *)0x0056C684,
	.width = 466,
	.height = 466,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)17781
};

const picture_info_struct pic_quick_power_10_info = {
	.addr = (const unsigned char *)0x00570BFC,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)904
};

const picture_info_struct pic_quick_power_100_info = {
	.addr = (const unsigned char *)0x00570F84,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)884
};

const picture_info_struct pic_quick_power_20_info = {
	.addr = (const unsigned char *)0x005712F8,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_quick_power_30_info = {
	.addr = (const unsigned char *)0x00571688,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_quick_power_40_info = {
	.addr = (const unsigned char *)0x00571A18,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_quick_power_50_info = {
	.addr = (const unsigned char *)0x00571DA8,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_quick_power_60_info = {
	.addr = (const unsigned char *)0x00572138,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_quick_power_70_info = {
	.addr = (const unsigned char *)0x005724C8,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_quick_power_80_info = {
	.addr = (const unsigned char *)0x00572858,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_quick_power_90_info = {
	.addr = (const unsigned char *)0x00572BE8,
	.width = 51,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_quick_all_no_info = {
	.addr = (const unsigned char *)0x00572F78,
	.width = 40,
	.height = 40,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1788
};

const picture_info_struct pic_quick_all_yes_info = {
	.addr = (const unsigned char *)0x00573674,
	.width = 40,
	.height = 40,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1412
};

const picture_info_struct pic_quick_ble_yes_info = {
	.addr = (const unsigned char *)0x00573BF8,
	.width = 40,
	.height = 40,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1412
};

const picture_info_struct pic_quick_bright_off_info = {
	.addr = (const unsigned char *)0x0057417C,
	.width = 100,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)7471
};

const picture_info_struct pic_quick_bright_on_info = {
	.addr = (const unsigned char *)0x00575EAC,
	.width = 100,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)7790
};

const picture_info_struct pic_quick_disturb_off_info = {
	.addr = (const unsigned char *)0x00577D1C,
	.width = 100,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4983
};

const picture_info_struct pic_quick_disturb_on_info = {
	.addr = (const unsigned char *)0x00579094,
	.width = 100,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5333
};

const picture_info_struct pic_quick_hfp_no_info = {
	.addr = (const unsigned char *)0x0057A56C,
	.width = 100,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4154
};

const picture_info_struct pic_quick_hfp_yes_info = {
	.addr = (const unsigned char *)0x0057B5A8,
	.width = 100,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4118
};

const picture_info_struct pic_quick_hfp_yes_1_info = {
	.addr = (const unsigned char *)0x0057C5C0,
	.width = 40,
	.height = 40,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1412
};

const picture_info_struct pic_quick_more_info = {
	.addr = (const unsigned char *)0x0057CB44,
	.width = 100,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5704
};

const picture_info_struct pic_quic_alarm_info = {
	.addr = (const unsigned char *)0x0057E18C,
	.width = 100,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6219
};

const picture_info_struct pic_delete_msg_info = {
	.addr = (const unsigned char *)0x0057F9D8,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4282
};

const picture_info_struct pic_mesg_no_info = {
	.addr = (const unsigned char *)0x00580A94,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3118
};

const picture_info_struct pic_message_bg_info = {
	.addr = (const unsigned char *)0x005816C4,
	.width = 392,
	.height = 215,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5298
};

const picture_info_struct pic_message_bg_l1_info = {
	.addr = (const unsigned char *)0x00582B78,
	.width = 392,
	.height = 110,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3198
};

const picture_info_struct pic_message_bg_l2_info = {
	.addr = (const unsigned char *)0x005837F8,
	.width = 392,
	.height = 158,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4158
};

const picture_info_struct pic_message_cancel_info = {
	.addr = (const unsigned char *)0x00584838,
	.width = 100,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3244
};

const picture_info_struct pic_message_delect_info = {
	.addr = (const unsigned char *)0x005854E4,
	.width = 466,
	.height = 88,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5679
};

const picture_info_struct pic_message_deletect_one_info = {
	.addr = (const unsigned char *)0x00586B14,
	.width = 88,
	.height = 214,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3884
};

const picture_info_struct pic_message_deletect_one_l1_info = {
	.addr = (const unsigned char *)0x00587A40,
	.width = 88,
	.height = 110,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3096
};

const picture_info_struct pic_message_deletect_one_l2_info = {
	.addr = (const unsigned char *)0x00588658,
	.width = 88,
	.height = 158,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3492
};

const picture_info_struct pic_message_info_back_info = {
	.addr = (const unsigned char *)0x005893FC,
	.width = 466,
	.height = 88,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5197
};

const picture_info_struct pic_message_info_bg_bot_info = {
	.addr = (const unsigned char *)0x0058A84C,
	.width = 392,
	.height = 39,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1279
};

const picture_info_struct pic_message_info_bg_top_info = {
	.addr = (const unsigned char *)0x0058AD4C,
	.width = 392,
	.height = 39,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1279
};

const picture_info_struct pic_message_ok_info = {
	.addr = (const unsigned char *)0x0058B24C,
	.width = 100,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2796
};

const picture_info_struct pic_msg_yes_info = {
	.addr = (const unsigned char *)0x0058BD38,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2920
};

const picture_info_struct pic_no_msg_info = {
	.addr = (const unsigned char *)0x0058C8A0,
	.width = 148,
	.height = 148,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4598
};

const picture_info_struct pic_operator2_cancel_info = {
	.addr = (const unsigned char *)0x0058DA98,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3118
};

const picture_info_struct pic_operator2_ok_info = {
	.addr = (const unsigned char *)0x0058E6C8,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2920
};

const picture_info_struct pic_msg_facebook_info = {
	.addr = (const unsigned char *)0x0058F230,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3048
};

const picture_info_struct pic_msg_Instagram_info = {
	.addr = (const unsigned char *)0x0058FE18,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)11287
};

const picture_info_struct pic_msg_kakaotalk_info = {
	.addr = (const unsigned char *)0x00592A30,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)7528
};

const picture_info_struct pic_msg_Line_info = {
	.addr = (const unsigned char *)0x00594798,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4159
};

const picture_info_struct pic_msg_Linkedin_info = {
	.addr = (const unsigned char *)0x005957D8,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)9447
};

const picture_info_struct pic_msg_mail_info = {
	.addr = (const unsigned char *)0x00597CC0,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4047
};

const picture_info_struct pic_msg_message_info = {
	.addr = (const unsigned char *)0x00598C90,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3043
};

const picture_info_struct pic_msg_other_info = {
	.addr = (const unsigned char *)0x00599874,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2674
};

const picture_info_struct pic_msg_qq_info = {
	.addr = (const unsigned char *)0x0059A2E8,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4813
};

const picture_info_struct pic_msg_Skype_info = {
	.addr = (const unsigned char *)0x0059B5B8,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3924
};

const picture_info_struct pic_msg_telegram_info = {
	.addr = (const unsigned char *)0x0059C50C,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5086
};

const picture_info_struct pic_msg_twitter_info = {
	.addr = (const unsigned char *)0x0059D8EC,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3309
};

const picture_info_struct pic_msg_wechat_info = {
	.addr = (const unsigned char *)0x0059E5DC,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3723
};

const picture_info_struct pic_msg_whatsapp_info = {
	.addr = (const unsigned char *)0x0059F468,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4621
};

const picture_info_struct pic_widget_btn_add_info = {
	.addr = (const unsigned char *)0x005A0678,
	.width = 123,
	.height = 123,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2951
};

const picture_info_struct pic_widget_btn_add_l_info = {
	.addr = (const unsigned char *)0x005A1200,
	.width = 44,
	.height = 44,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1540
};

const picture_info_struct pic_widget_btn_delete_info = {
	.addr = (const unsigned char *)0x005A1804,
	.width = 44,
	.height = 44,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1242
};

const picture_info_struct pic_widget_btn_top_info = {
	.addr = (const unsigned char *)0x005A1CE0,
	.width = 44,
	.height = 44,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1315
};

const picture_info_struct pic_widget_list_bg_info = {
	.addr = (const unsigned char *)0x005A2204,
	.width = 410,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2624
};

const picture_info_struct pic_power_off_reboot_info = {
	.addr = (const unsigned char *)0x005A2C44,
	.width = 76,
	.height = 76,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3570
};

const picture_info_struct pic_power_off_shutdown_info = {
	.addr = (const unsigned char *)0x005A3A38,
	.width = 76,
	.height = 76,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3990
};

const picture_info_struct pic_power_off_sos_info = {
	.addr = (const unsigned char *)0x005A49D0,
	.width = 76,
	.height = 76,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3967
};

const picture_info_struct pic_sos_no_info = {
	.addr = (const unsigned char *)0x005A5950,
	.width = 86,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3815
};

const picture_info_struct pic_charger_info = {
	.addr = (const unsigned char *)0x005A6838,
	.width = 73,
	.height = 73,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3111
};

const picture_info_struct pic_charger_bg_01_info = {
	.addr = (const unsigned char *)0x005A7460,
	.width = 248,
	.height = 248,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7680
};

const picture_info_struct pic_charger_bg_02_info = {
	.addr = (const unsigned char *)0x005A9260,
	.width = 248,
	.height = 248,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)8190
};

const picture_info_struct pic_charger_bg_03_info = {
	.addr = (const unsigned char *)0x005AB260,
	.width = 248,
	.height = 248,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)8512
};

const picture_info_struct pic_charger_bg_04_info = {
	.addr = (const unsigned char *)0x005AD3A0,
	.width = 248,
	.height = 248,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)8761
};

const picture_info_struct pic_charger_bg_05_info = {
	.addr = (const unsigned char *)0x005AF5DC,
	.width = 248,
	.height = 248,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)8822
};

const picture_info_struct pic_charger_logo_info = {
	.addr = (const unsigned char *)0x005B1854,
	.width = 48,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)926
};

const picture_info_struct pic_ota_info = {
	.addr = (const unsigned char *)pic_ota_data,
	.width = 138,
	.height = 157,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_0_info = {
	.addr = (const unsigned char *)pic_ota_num_0_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_010_info = {
	.addr = (const unsigned char *)pic_ota_num_010_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_1_info = {
	.addr = (const unsigned char *)pic_ota_num_1_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_2_info = {
	.addr = (const unsigned char *)pic_ota_num_2_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_3_info = {
	.addr = (const unsigned char *)pic_ota_num_3_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_4_info = {
	.addr = (const unsigned char *)pic_ota_num_4_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_5_info = {
	.addr = (const unsigned char *)pic_ota_num_5_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_6_info = {
	.addr = (const unsigned char *)pic_ota_num_6_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_7_info = {
	.addr = (const unsigned char *)pic_ota_num_7_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_8_info = {
	.addr = (const unsigned char *)pic_ota_num_8_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_9_info = {
	.addr = (const unsigned char *)pic_ota_num_9_data,
	.width = 18,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_col_info = {
	.addr = (const unsigned char *)pic_ota_num_col_data,
	.width = 8,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_ota_num_dot_info = {
	.addr = (const unsigned char *)pic_ota_num_dot_data,
	.width = 8,
	.height = 24,
	.alpha = 0,
	.external_flag = 0,
};

const picture_info_struct pic_lock_screen_icon_info = {
	.addr = (const unsigned char *)0x005B1BF4,
	.width = 103,
	.height = 135,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3697
};

const picture_info_struct pic_password_delect_info = {
	.addr = (const unsigned char *)0x005B2A68,
	.width = 58,
	.height = 40,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1243
};

const picture_info_struct pic_password_no_info = {
	.addr = (const unsigned char *)0x005B2F44,
	.width = 26,
	.height = 26,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)470
};

const picture_info_struct pic_password_yes_info = {
	.addr = (const unsigned char *)0x005B311C,
	.width = 26,
	.height = 26,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)490
};

const picture_info_struct pic_password_bg_0_info = {
	.addr = (const unsigned char *)0x005B3308,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2484
};

const picture_info_struct pic_password_bg_1_info = {
	.addr = (const unsigned char *)0x005B3CBC,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2132
};

const picture_info_struct pic_password_bg_2_info = {
	.addr = (const unsigned char *)0x005B4510,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2227
};

const picture_info_struct pic_password_bg_3_info = {
	.addr = (const unsigned char *)0x005B4DC4,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2317
};

const picture_info_struct pic_password_bg_4_info = {
	.addr = (const unsigned char *)0x005B56D4,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2262
};

const picture_info_struct pic_password_bg_5_info = {
	.addr = (const unsigned char *)0x005B5FAC,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2273
};

const picture_info_struct pic_password_bg_6_info = {
	.addr = (const unsigned char *)0x005B6890,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2341
};

const picture_info_struct pic_password_bg_7_info = {
	.addr = (const unsigned char *)0x005B71B8,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2166
};

const picture_info_struct pic_password_bg_8_info = {
	.addr = (const unsigned char *)0x005B7A30,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2482
};

const picture_info_struct pic_password_bg_9_info = {
	.addr = (const unsigned char *)0x005B83E4,
	.width = 126,
	.height = 86,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2302
};

const picture_info_struct pic_alarm_info = {
	.addr = (const unsigned char *)0x005B8CE4,
	.width = 132,
	.height = 114,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7082
};

const picture_info_struct pic_calendar_bg_info = {
	.addr = (const unsigned char *)0x005BA890,
	.width = 73,
	.height = 62,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)937
};

const picture_info_struct pic_drink_info = {
	.addr = (const unsigned char *)0x005BAC3C,
	.width = 234,
	.height = 266,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)33648
};

const picture_info_struct pic_find_device_info = {
	.addr = (const unsigned char *)0x005C2FAC,
	.width = 99,
	.height = 99,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3862
};

const picture_info_struct pic_low_power_info = {
	.addr = (const unsigned char *)0x005C3EC4,
	.width = 128,
	.height = 128,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4900
};

const picture_info_struct pic_pair_finish_info = {
	.addr = (const unsigned char *)0x005C51E8,
	.width = 331,
	.height = 153,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)24962
};

const picture_info_struct pic_sedentary_remind_info = {
	.addr = (const unsigned char *)0x005CB36C,
	.width = 234,
	.height = 280,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)40891
};

const picture_info_struct pic_target_finish_info = {
	.addr = (const unsigned char *)0x005D5328,
	.width = 320,
	.height = 136,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)17539
};

const picture_info_struct pic_bg_gif_1_001_info = {
	.addr = (const unsigned char *)0x005D97AC,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9965
};

const picture_info_struct pic_bg_gif_1_002_info = {
	.addr = (const unsigned char *)0x005DBE9C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)21967
};

const picture_info_struct pic_bg_gif_1_003_info = {
	.addr = (const unsigned char *)0x005E146C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)18330
};

const picture_info_struct pic_bg_gif_1_004_info = {
	.addr = (const unsigned char *)0x005E5C08,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)14764
};

const picture_info_struct pic_more_ring_bg_1_info = {
	.addr = (const unsigned char *)0x005E95B4,
	.width = 24,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)780
};

const picture_info_struct pic_more_ring_ind_info = {
	.addr = (const unsigned char *)0x005E98C0,
	.width = 37,
	.height = 54,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1166
};

const picture_info_struct pic_style_ring_home_info = {
	.addr = (const unsigned char *)0x005E9D50,
	.width = 98,
	.height = 98,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)10161
};

const picture_info_struct pic_Step_flag_bg_1_info = {
	.addr = (const unsigned char *)0x005EC504,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)19096
};

const picture_info_struct pic_Step_flag_bg_2_info = {
	.addr = (const unsigned char *)0x005F0F9C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)29473
};

const picture_info_struct pic_Step_flag_bg_3_info = {
	.addr = (const unsigned char *)0x005F82C0,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)26625
};

const picture_info_struct pic_Step_flag_bg_4_info = {
	.addr = (const unsigned char *)0x005FEAC4,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)28788
};

const picture_info_struct pic_step_calorie_info = {
	.addr = (const unsigned char *)0x00605B38,
	.width = 13,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)320
};

const picture_info_struct pic_step_distance_info = {
	.addr = (const unsigned char *)0x00605C78,
	.width = 16,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)314
};

const picture_info_struct pic_step_step_info = {
	.addr = (const unsigned char *)0x00605DB4,
	.width = 50,
	.height = 65,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1971
};

const picture_info_struct pic_today_kcal_info = {
	.addr = (const unsigned char *)0x00606568,
	.width = 12,
	.height = 15,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)315
};

const picture_info_struct pic_today_km_info = {
	.addr = (const unsigned char *)0x006066A4,
	.width = 11,
	.height = 14,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)312
};

const picture_info_struct pic_today_step_info = {
	.addr = (const unsigned char *)0x006067DC,
	.width = 35,
	.height = 35,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1683
};

const picture_info_struct pic_spor_ready_0_info = {
	.addr = (const unsigned char *)0x00606E70,
	.width = 32,
	.height = 67,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1505
};

const picture_info_struct pic_spor_ready_1_info = {
	.addr = (const unsigned char *)0x00607454,
	.width = 32,
	.height = 67,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1315
};

const picture_info_struct pic_spor_ready_2_info = {
	.addr = (const unsigned char *)0x00607978,
	.width = 32,
	.height = 67,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1365
};

const picture_info_struct pic_spor_ready_3_info = {
	.addr = (const unsigned char *)0x00607ED0,
	.width = 32,
	.height = 67,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1494
};

const picture_info_struct pic_sportlist_bg_10_001_info = {
	.addr = (const unsigned char *)0x006084A8,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)57589
};

const picture_info_struct pic_sportlist_bg_10_002_info = {
	.addr = (const unsigned char *)0x006165A0,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)65982
};

const picture_info_struct pic_sportlist_bg_1_001_info = {
	.addr = (const unsigned char *)0x00626760,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)56021
};

const picture_info_struct pic_sportlist_bg_1_002_info = {
	.addr = (const unsigned char *)0x00634238,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)47747
};

const picture_info_struct pic_sportlist_bg_2_001_info = {
	.addr = (const unsigned char *)0x0063FCBC,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)53042
};

const picture_info_struct pic_sportlist_bg_2_002_info = {
	.addr = (const unsigned char *)0x0064CBF0,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)65413
};

const picture_info_struct pic_sportlist_bg_3_001_info = {
	.addr = (const unsigned char *)0x0065CB78,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)48865
};

const picture_info_struct pic_sportlist_bg_3_002_info = {
	.addr = (const unsigned char *)0x00668A5C,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)45107
};

const picture_info_struct pic_sportlist_bg_4_001_info = {
	.addr = (const unsigned char *)0x00673A90,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)56424
};

const picture_info_struct pic_sportlist_bg_4_002_info = {
	.addr = (const unsigned char *)0x006816F8,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)51159
};

const picture_info_struct pic_sportlist_bg_5_001_info = {
	.addr = (const unsigned char *)0x0068DED0,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)54459
};

const picture_info_struct pic_sportlist_bg_5_002_info = {
	.addr = (const unsigned char *)0x0069B38C,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)47137
};

const picture_info_struct pic_sportlist_bg_6_001_info = {
	.addr = (const unsigned char *)0x006A6BB0,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)59634
};

const picture_info_struct pic_sportlist_bg_6_002_info = {
	.addr = (const unsigned char *)0x006B54A4,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)61935
};

const picture_info_struct pic_sportlist_bg_7_001_info = {
	.addr = (const unsigned char *)0x006C4694,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)74952
};

const picture_info_struct pic_sportlist_bg_7_002_info = {
	.addr = (const unsigned char *)0x006D6B5C,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)72102
};

const picture_info_struct pic_sportlist_bg_8_001_info = {
	.addr = (const unsigned char *)0x006E8504,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)80235
};

const picture_info_struct pic_sportlist_bg_8_002_info = {
	.addr = (const unsigned char *)0x006FBE70,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)80956
};

const picture_info_struct pic_sportlist_bg_9_001_info = {
	.addr = (const unsigned char *)0x0070FAAC,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)35831
};

const picture_info_struct pic_sportlist_bg_9_002_info = {
	.addr = (const unsigned char *)0x007186A4,
	.width = 241,
	.height = 190,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)56396
};

const picture_info_struct pic_detailed_run_1_info = {
	.addr = (const unsigned char *)0x007262F0,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)22218
};

const picture_info_struct pic_detailed_run_2_info = {
	.addr = (const unsigned char *)0x0072B9BC,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)22449
};

const picture_info_struct pic_detailed_run_3_info = {
	.addr = (const unsigned char *)0x00731170,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)22218
};

const picture_info_struct pic_detailed_cycling_indoor_1_info = {
	.addr = (const unsigned char *)0x0073683C,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20871
};

const picture_info_struct pic_detailed_cycling_indoor_2_info = {
	.addr = (const unsigned char *)0x0073B9C4,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20912
};

const picture_info_struct pic_detailed_cycling_indoor_3_info = {
	.addr = (const unsigned char *)0x00740B74,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20779
};

const picture_info_struct pic_detailed_walk_1_info = {
	.addr = (const unsigned char *)0x00745CA0,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)18958
};

const picture_info_struct pic_detailed_walk_2_info = {
	.addr = (const unsigned char *)0x0074A6B0,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)19318
};

const picture_info_struct pic_detailed_walk_3_info = {
	.addr = (const unsigned char *)0x0074F228,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)19018
};

const picture_info_struct pic_detailed_cycling_1_info = {
	.addr = (const unsigned char *)0x00753C74,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)18762
};

const picture_info_struct pic_detailed_cycling_2_info = {
	.addr = (const unsigned char *)0x007585C0,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)18736
};

const picture_info_struct pic_detailed_cycling_3_info = {
	.addr = (const unsigned char *)0x0075CEF0,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)18683
};

const picture_info_struct pic_detailed_climbing_1_info = {
	.addr = (const unsigned char *)0x007617EC,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20469
};

const picture_info_struct pic_detailed_climbing_2_info = {
	.addr = (const unsigned char *)0x007667E4,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20518
};

const picture_info_struct pic_detailed_climbing_3_info = {
	.addr = (const unsigned char *)0x0076B80C,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20471
};

const picture_info_struct pic_detailed_running_machine_1_info = {
	.addr = (const unsigned char *)0x00770804,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)19565
};

const picture_info_struct pic_detailed_running_machine_2_info = {
	.addr = (const unsigned char *)0x00775474,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)19641
};

const picture_info_struct pic_detailed_running_machine_3_info = {
	.addr = (const unsigned char *)0x0077A130,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)19665
};

const picture_info_struct pic_detailed_basketball_1_info = {
	.addr = (const unsigned char *)0x0077EE04,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20174
};

const picture_info_struct pic_detailed_basketball_2_info = {
	.addr = (const unsigned char *)0x00783CD4,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20110
};

const picture_info_struct pic_detailed_basketball_3_info = {
	.addr = (const unsigned char *)0x00788B64,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)20120
};

const picture_info_struct pic_detailed_football_1_info = {
	.addr = (const unsigned char *)0x0078D9FC,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)25250
};

const picture_info_struct pic_detailed_football_2_info = {
	.addr = (const unsigned char *)0x00793CA0,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)25857
};

const picture_info_struct pic_detailed_football_3_info = {
	.addr = (const unsigned char *)0x0079A1A4,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)25286
};

const picture_info_struct pic_detailed_badminton_1_info = {
	.addr = (const unsigned char *)0x007A046C,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)30040
};

const picture_info_struct pic_detailed_badminton_2_info = {
	.addr = (const unsigned char *)0x007A79C4,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)30685
};

const picture_info_struct pic_detailed_badminton_3_info = {
	.addr = (const unsigned char *)0x007AF1A4,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)30828
};

const picture_info_struct pic_detailed_skip_1_info = {
	.addr = (const unsigned char *)0x007B6A10,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)13170
};

const picture_info_struct pic_detailed_skip_2_info = {
	.addr = (const unsigned char *)0x007B9D84,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)13205
};

const picture_info_struct pic_detailed_skip_3_info = {
	.addr = (const unsigned char *)0x007BD11C,
	.width = 130,
	.height = 130,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)13178
};

const picture_info_struct pic_sport_bg_info = {
	.addr = (const unsigned char *)0x007C0498,
	.width = 466,
	.height = 466,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)21961
};

const picture_info_struct pic_sport_font_bpm_info = {
	.addr = (const unsigned char *)0x007C5A64,
	.width = 58,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1441
};

const picture_info_struct pic_sport_font_kcal_info = {
	.addr = (const unsigned char *)0x007C6008,
	.width = 72,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1692
};

const picture_info_struct pic_sport_font_km_info = {
	.addr = (const unsigned char *)0x007C66A4,
	.width = 42,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1314
};

const picture_info_struct pic_sport_font_mile_info = {
	.addr = (const unsigned char *)0x007C6BC8,
	.width = 62,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1514
};

const picture_info_struct pic_sport_font_steps_info = {
	.addr = (const unsigned char *)0x007C71B4,
	.width = 86,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1824
};

const picture_info_struct pic_sport_calories_set_bg_small_info = {
	.addr = (const unsigned char *)0x007C78D4,
	.width = 17,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)442
};

const picture_info_struct pic_sport_distance_set_bg_small_info = {
	.addr = (const unsigned char *)0x007C7A90,
	.width = 14,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)506
};

const picture_info_struct pic_sport_heart_info = {
	.addr = (const unsigned char *)0x007C7C8C,
	.width = 19,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)323
};

const picture_info_struct pic_sport_set_info = {
	.addr = (const unsigned char *)0x007C7DD0,
	.width = 23,
	.height = 6,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)238
};

const picture_info_struct pic_sport_steps_info = {
	.addr = (const unsigned char *)0x007C7EC0,
	.width = 21,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)408
};

const picture_info_struct pic_sport_tip_bg_info = {
	.addr = (const unsigned char *)0x007C8058,
	.width = 240,
	.height = 30,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)300
};

const picture_info_struct pic_continue_info = {
	.addr = (const unsigned char *)0x007C8184,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3118
};

const picture_info_struct pic_finish_info = {
	.addr = (const unsigned char *)0x007C8DB4,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2856
};

const picture_info_struct pic_hr_large_num_0_info = {
	.addr = (const unsigned char *)0x007C98DC,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)933
};

const picture_info_struct pic_hr_large_num_1_info = {
	.addr = (const unsigned char *)0x007C9C84,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)526
};

const picture_info_struct pic_hr_large_num_2_info = {
	.addr = (const unsigned char *)0x007C9E94,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)725
};

const picture_info_struct pic_hr_large_num_3_info = {
	.addr = (const unsigned char *)0x007CA16C,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)878
};

const picture_info_struct pic_hr_large_num_4_info = {
	.addr = (const unsigned char *)0x007CA4DC,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)798
};

const picture_info_struct pic_hr_large_num_5_info = {
	.addr = (const unsigned char *)0x007CA7FC,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)817
};

const picture_info_struct pic_hr_large_num_6_info = {
	.addr = (const unsigned char *)0x007CAB30,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)958
};

const picture_info_struct pic_hr_large_num_7_info = {
	.addr = (const unsigned char *)0x007CAEF0,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)578
};

const picture_info_struct pic_hr_large_num_8_info = {
	.addr = (const unsigned char *)0x007CB134,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)974
};

const picture_info_struct pic_hr_large_num_9_info = {
	.addr = (const unsigned char *)0x007CB504,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)953
};

const picture_info_struct pic_hr_large_num_baifen_info = {
	.addr = (const unsigned char *)0x007CB8C0,
	.width = 18,
	.height = 24,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)803
};

const picture_info_struct pic_hr_small_num_0_info = {
	.addr = (const unsigned char *)0x007CBBE4,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)368
};

const picture_info_struct pic_hr_small_num_1_info = {
	.addr = (const unsigned char *)0x007CBD54,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)255
};

const picture_info_struct pic_hr_small_num_2_info = {
	.addr = (const unsigned char *)0x007CBE54,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)316
};

const picture_info_struct pic_hr_small_num_3_info = {
	.addr = (const unsigned char *)0x007CBF90,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)352
};

const picture_info_struct pic_hr_small_num_4_info = {
	.addr = (const unsigned char *)0x007CC0F0,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)306
};

const picture_info_struct pic_hr_small_num_5_info = {
	.addr = (const unsigned char *)0x007CC224,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)328
};

const picture_info_struct pic_hr_small_num_6_info = {
	.addr = (const unsigned char *)0x007CC36C,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)382
};

const picture_info_struct pic_hr_small_num_7_info = {
	.addr = (const unsigned char *)0x007CC4EC,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)254
};

const picture_info_struct pic_hr_small_num_8_info = {
	.addr = (const unsigned char *)0x007CC5EC,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)378
};

const picture_info_struct pic_hr_small_num_9_info = {
	.addr = (const unsigned char *)0x007CC768,
	.width = 12,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)379
};

const picture_info_struct pic_hr_small_num_baifen_info = {
	.addr = (const unsigned char *)0x007CC8E4,
	.width = 17,
	.height = 16,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)467
};

const picture_info_struct pic_hr_bg_001_info = {
	.addr = (const unsigned char *)0x007CCAB8,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)39220
};

const picture_info_struct pic_hr_bg_002_info = {
	.addr = (const unsigned char *)0x007D63EC,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)36329
};

const picture_info_struct pic_hr_bg_003_info = {
	.addr = (const unsigned char *)0x007DF1D8,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)39046
};

const picture_info_struct pic_hr_bg_004_info = {
	.addr = (const unsigned char *)0x007E8A60,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)36638
};

const picture_info_struct pic_hr_item_line_1_info = {
	.addr = (const unsigned char *)0x007F1980,
	.width = 182,
	.height = 4,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)800
};

const picture_info_struct pic_hr_item_line_2_info = {
	.addr = (const unsigned char *)0x007F1CA0,
	.width = 182,
	.height = 4,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)806
};

const picture_info_struct pic_hr_gif_1_info = {
	.addr = (const unsigned char *)0x007F1FC8,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6810
};

const picture_info_struct pic_hr_gif_10_info = {
	.addr = (const unsigned char *)0x007F3A64,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6899
};

const picture_info_struct pic_hr_gif_2_info = {
	.addr = (const unsigned char *)0x007F5558,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6375
};

const picture_info_struct pic_hr_gif_3_info = {
	.addr = (const unsigned char *)0x007F6E40,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6199
};

const picture_info_struct pic_hr_gif_4_info = {
	.addr = (const unsigned char *)0x007F8678,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6069
};

const picture_info_struct pic_hr_gif_5_info = {
	.addr = (const unsigned char *)0x007F9E30,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6039
};

const picture_info_struct pic_hr_gif_6_info = {
	.addr = (const unsigned char *)0x007FB5C8,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5929
};

const picture_info_struct pic_hr_gif_7_info = {
	.addr = (const unsigned char *)0x007FCCF4,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5838
};

const picture_info_struct pic_hr_gif_8_info = {
	.addr = (const unsigned char *)0x007FE3C4,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5938
};

const picture_info_struct pic_hr_gif_9_info = {
	.addr = (const unsigned char *)0x007FFAF8,
	.width = 68,
	.height = 68,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6468
};

const picture_info_struct pic_no_sleep_data_info = {
	.addr = (const unsigned char *)0x0080143C,
	.width = 100,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2608
};

const picture_info_struct pic_sleep_deep_info = {
	.addr = (const unsigned char *)0x00801E6C,
	.width = 240,
	.height = 52,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2657
};

const picture_info_struct pic_sleep_Gif_1_001_info = {
	.addr = (const unsigned char *)0x008028D0,
	.width = 233,
	.height = 157,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2177
};

const picture_info_struct pic_sleep_Gif_1_002_info = {
	.addr = (const unsigned char *)0x00803154,
	.width = 233,
	.height = 157,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)10512
};

const picture_info_struct pic_sleep_Gif_1_003_info = {
	.addr = (const unsigned char *)0x00805A64,
	.width = 233,
	.height = 157,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2764
};

const picture_info_struct pic_sleep_Gif_1_004_info = {
	.addr = (const unsigned char *)0x00806530,
	.width = 233,
	.height = 157,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)11706
};

const picture_info_struct pic_sleep_Gif_2_001_info = {
	.addr = (const unsigned char *)0x008092EC,
	.width = 233,
	.height = 187,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)41049
};

const picture_info_struct pic_sleep_Gif_2_002_info = {
	.addr = (const unsigned char *)0x00813348,
	.width = 233,
	.height = 187,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)41522
};

const picture_info_struct pic_sleep_light_info = {
	.addr = (const unsigned char *)0x0081D57C,
	.width = 240,
	.height = 52,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2657
};

const picture_info_struct pic_o2_data_0_info = {
	.addr = (const unsigned char *)0x0081DFE0,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2666
};

const picture_info_struct pic_o2_data_1_info = {
	.addr = (const unsigned char *)0x0081EA4C,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1713
};

const picture_info_struct pic_o2_data_10_info = {
	.addr = (const unsigned char *)0x0081F100,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3095
};

const picture_info_struct pic_o2_data_2_info = {
	.addr = (const unsigned char *)0x0081FD18,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2036
};

const picture_info_struct pic_o2_data_3_info = {
	.addr = (const unsigned char *)0x0082050C,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2205
};

const picture_info_struct pic_o2_data_4_info = {
	.addr = (const unsigned char *)0x00820DAC,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1803
};

const picture_info_struct pic_o2_data_5_info = {
	.addr = (const unsigned char *)0x008214B8,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2106
};

const picture_info_struct pic_o2_data_6_info = {
	.addr = (const unsigned char *)0x00821CF4,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2269
};

const picture_info_struct pic_o2_data_7_info = {
	.addr = (const unsigned char *)0x008225D4,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1880
};

const picture_info_struct pic_o2_data_8_info = {
	.addr = (const unsigned char *)0x00822D2C,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2654
};

const picture_info_struct pic_o2_data_9_info = {
	.addr = (const unsigned char *)0x0082378C,
	.width = 42,
	.height = 66,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2216
};

const picture_info_struct pic_o2_no_arrow_info = {
	.addr = (const unsigned char *)0x00824034,
	.width = 29,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)398
};

const picture_info_struct pic_o2_no_bg_info = {
	.addr = (const unsigned char *)0x008241C4,
	.width = 254,
	.height = 97,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5974
};

const picture_info_struct pic_o2_no_round_info = {
	.addr = (const unsigned char *)0x0082591C,
	.width = 26,
	.height = 26,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)486
};

const picture_info_struct pic_o2_start_measurement_info = {
	.addr = (const unsigned char *)0x00825B04,
	.width = 254,
	.height = 97,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7019
};

const picture_info_struct pic_o2_result_bg_001_info = {
	.addr = (const unsigned char *)0x00827670,
	.width = 240,
	.height = 166,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2712
};

const picture_info_struct pic_o2_result_bg_002_info = {
	.addr = (const unsigned char *)0x00828108,
	.width = 113,
	.height = 166,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2260
};

const picture_info_struct pic_o2_result_retry_info = {
	.addr = (const unsigned char *)0x008289DC,
	.width = 104,
	.height = 104,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3038
};

const picture_info_struct pic_o2_start_bg_1_001_info = {
	.addr = (const unsigned char *)0x008295BC,
	.width = 170,
	.height = 170,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)11178
};

const picture_info_struct pic_o2_start_bg_1_002_info = {
	.addr = (const unsigned char *)0x0082C168,
	.width = 170,
	.height = 170,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)10429
};

const picture_info_struct pic_o2_start_bg_1_003_info = {
	.addr = (const unsigned char *)0x0082EA28,
	.width = 170,
	.height = 170,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)11231
};

const picture_info_struct pic_o2_start_bg_1_004_info = {
	.addr = (const unsigned char *)0x00831608,
	.width = 170,
	.height = 170,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)10437
};

const picture_info_struct pic_bp_remind_bg_info = {
	.addr = (const unsigned char *)0x00833ED0,
	.width = 240,
	.height = 82,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4617
};

const picture_info_struct pic_bp_remind_bg_1_info = {
	.addr = (const unsigned char *)0x008350DC,
	.width = 210,
	.height = 178,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2048
};

const picture_info_struct pic_bp_remind_bg_2_info = {
	.addr = (const unsigned char *)0x008358DC,
	.width = 210,
	.height = 178,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2048
};

const picture_info_struct pic_hr_reset_info = {
	.addr = (const unsigned char *)0x008360DC,
	.width = 100,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3707
};

const picture_info_struct pic_bp_gif_01_info = {
	.addr = (const unsigned char *)0x00836F58,
	.width = 100,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5197
};

const picture_info_struct pic_bp_gif_05_info = {
	.addr = (const unsigned char *)0x008383A8,
	.width = 100,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5798
};

const picture_info_struct pic_bp_gif_13_info = {
	.addr = (const unsigned char *)0x00839A50,
	.width = 100,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)6961
};

const picture_info_struct pic_bp_data_00_info = {
	.addr = (const unsigned char *)0x0083B584,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1206
};

const picture_info_struct pic_bp_data_01_info = {
	.addr = (const unsigned char *)0x0083BA3C,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)702
};

const picture_info_struct pic_bp_data_02_info = {
	.addr = (const unsigned char *)0x0083BCFC,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1000
};

const picture_info_struct pic_bp_data_03_info = {
	.addr = (const unsigned char *)0x0083C0E4,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1095
};

const picture_info_struct pic_bp_data_04_info = {
	.addr = (const unsigned char *)0x0083C52C,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)959
};

const picture_info_struct pic_bp_data_05_info = {
	.addr = (const unsigned char *)0x0083C8EC,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1036
};

const picture_info_struct pic_bp_data_06_info = {
	.addr = (const unsigned char *)0x0083CCF8,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1239
};

const picture_info_struct pic_bp_data_07_info = {
	.addr = (const unsigned char *)0x0083D1D0,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)788
};

const picture_info_struct pic_bp_data_08_info = {
	.addr = (const unsigned char *)0x0083D4E4,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1232
};

const picture_info_struct pic_bp_data_09_info = {
	.addr = (const unsigned char *)0x0083D9B4,
	.width = 30,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1241
};

const picture_info_struct pic_bp_data_10_info = {
	.addr = (const unsigned char *)0x0083DE90,
	.width = 23,
	.height = 46,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)890
};

const picture_info_struct pic_bp_data_11_info = {
	.addr = (const unsigned char *)0x0083E20C,
	.width = 30,
	.height = 58,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)406
};

const picture_info_struct pic_bp_bg2_001_info = {
	.addr = (const unsigned char *)0x0083E3A4,
	.width = 210,
	.height = 156,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3925
};

const picture_info_struct pic_bp_bg2_002_info = {
	.addr = (const unsigned char *)0x0083F2FC,
	.width = 210,
	.height = 155,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3438
};

const picture_info_struct pic_bp_bg2_003_info = {
	.addr = (const unsigned char *)0x0084006C,
	.width = 210,
	.height = 156,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2543
};

const picture_info_struct pic_bp_bg2_004_info = {
	.addr = (const unsigned char *)0x00840A5C,
	.width = 210,
	.height = 155,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3332
};

const picture_info_struct pic_o2_remind_ic_info = {
	.addr = (const unsigned char *)0x00841760,
	.width = 42,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1624
};

const picture_info_struct pic_bp_bg_16_001_info = {
	.addr = (const unsigned char *)0x00841DB8,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)96203
};

const picture_info_struct pic_bp_bg_16_002_info = {
	.addr = (const unsigned char *)0x00859584,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)101062
};

const picture_info_struct pic_bp_bg_16_003_info = {
	.addr = (const unsigned char *)0x0087204C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)98500
};

const picture_info_struct pic_bp_bg_16_004_info = {
	.addr = (const unsigned char *)0x0088A110,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)101445
};

const picture_info_struct pic_breath_button_info = {
	.addr = (const unsigned char *)0x008A2D58,
	.width = 264,
	.height = 90,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2236
};

const picture_info_struct pic_breath_gif_bg_info = {
	.addr = (const unsigned char *)0x008A3614,
	.width = 172,
	.height = 172,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)13216
};

const picture_info_struct pic_breath_speed_info = {
	.addr = (const unsigned char *)0x008A69B4,
	.width = 132,
	.height = 90,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3337
};

const picture_info_struct pic_breath_start_info = {
	.addr = (const unsigned char *)0x008A76C0,
	.width = 102,
	.height = 102,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3564
};

const picture_info_struct pic_breath_time_info = {
	.addr = (const unsigned char *)0x008A84AC,
	.width = 132,
	.height = 90,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3867
};

const picture_info_struct pic_break_ountdown_time_01_info = {
	.addr = (const unsigned char *)0x008A93C8,
	.width = 26,
	.height = 38,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)952
};

const picture_info_struct pic_break_ountdown_time_02_info = {
	.addr = (const unsigned char *)0x008A9780,
	.width = 26,
	.height = 38,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1083
};

const picture_info_struct pic_break_ountdown_time_03_info = {
	.addr = (const unsigned char *)0x008A9BBC,
	.width = 26,
	.height = 38,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1223
};

const picture_info_struct pic_calllog_in_info = {
	.addr = (const unsigned char *)0x008AA084,
	.width = 26,
	.height = 26,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)695
};

const picture_info_struct pic_calllog_miss_info = {
	.addr = (const unsigned char *)0x008AA33C,
	.width = 26,
	.height = 26,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)674
};

const picture_info_struct pic_calllog_out_info = {
	.addr = (const unsigned char *)0x008AA5E0,
	.width = 26,
	.height = 26,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)687
};

const picture_info_struct pic_call_bg_1_info = {
	.addr = (const unsigned char *)0x008AA890,
	.width = 466,
	.height = 466,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)35630
};

const picture_info_struct pic_call_bmp_info = {
	.addr = (const unsigned char *)0x008B33C0,
	.width = 68,
	.height = 69,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2515
};

const picture_info_struct pic_call_in_ind_info = {
	.addr = (const unsigned char *)0x008B3D94,
	.width = 52,
	.height = 52,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2149
};

const picture_info_struct pic_call_list_book_info = {
	.addr = (const unsigned char *)0x008B45FC,
	.width = 92,
	.height = 92,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)6222
};

const picture_info_struct pic_call_list_callong_info = {
	.addr = (const unsigned char *)0x008B5E4C,
	.width = 92,
	.height = 92,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)6115
};

const picture_info_struct pic_call_list_dail_info = {
	.addr = (const unsigned char *)0x008B7630,
	.width = 92,
	.height = 92,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)7867
};

const picture_info_struct pic_call_mic_off_info = {
	.addr = (const unsigned char *)0x008B94EC,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3732
};

const picture_info_struct pic_call_mic_on_info = {
	.addr = (const unsigned char *)0x008BA380,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3590
};

const picture_info_struct pic_call_out_watch_info = {
	.addr = (const unsigned char *)0x008BB188,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3634
};

const picture_info_struct pic_call_pb_dial_info = {
	.addr = (const unsigned char *)0x008BBFBC,
	.width = 23,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)455
};

const picture_info_struct pic_call_reply_info = {
	.addr = (const unsigned char *)0x008BC184,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4020
};

const picture_info_struct pic_call_vol_info = {
	.addr = (const unsigned char *)0x008BD138,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3654
};

const picture_info_struct pic_call_vol_bg_info = {
	.addr = (const unsigned char *)0x008BDF80,
	.width = 120,
	.height = 360,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4088
};

const picture_info_struct pic_call_vol_down_info = {
	.addr = (const unsigned char *)0x008BEF78,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1452
};

const picture_info_struct pic_call_vol_line_info = {
	.addr = (const unsigned char *)0x008BF524,
	.width = 279,
	.height = 6,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)130
};

const picture_info_struct pic_call_vol_line1_info = {
	.addr = (const unsigned char *)0x008BF5A8,
	.width = 279,
	.height = 6,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)130
};

const picture_info_struct pic_call_vol_top_info = {
	.addr = (const unsigned char *)0x008BF62C,
	.width = 120,
	.height = 360,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4088
};

const picture_info_struct pic_call_vol_up_info = {
	.addr = (const unsigned char *)0x008C0624,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2052
};

const picture_info_struct pic_head_portrait_info = {
	.addr = (const unsigned char *)0x008C0E28,
	.width = 100,
	.height = 100,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4164
};

const picture_info_struct pic_missed_call_info = {
	.addr = (const unsigned char *)0x008C1E6C,
	.width = 88,
	.height = 88,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2323
};

const picture_info_struct pic_no_call_record_info = {
	.addr = (const unsigned char *)0x008C2780,
	.width = 72,
	.height = 72,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2522
};

const picture_info_struct pic_no_contact_info = {
	.addr = (const unsigned char *)0x008C315C,
	.width = 106,
	.height = 106,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2917
};

const picture_info_struct pic_no_little_info = {
	.addr = (const unsigned char *)0x008C3CC4,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2726
};

const picture_info_struct pic_yes_little_info = {
	.addr = (const unsigned char *)0x008C476C,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2900
};

const picture_info_struct pic_music_bg_01_info = {
	.addr = (const unsigned char *)0x008C52C0,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)40495
};

const picture_info_struct pic_music_bg_02_info = {
	.addr = (const unsigned char *)0x008CF0F0,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)45063
};

const picture_info_struct pic_music_bg_03_info = {
	.addr = (const unsigned char *)0x008DA0F8,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)45052
};

const picture_info_struct pic_music_bg_04_info = {
	.addr = (const unsigned char *)0x008E50F4,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)53631
};

const picture_info_struct pic_music_log_bg_info = {
	.addr = (const unsigned char *)0x008F2274,
	.width = 186,
	.height = 12,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)336
};

const picture_info_struct pic_music_log_top_info = {
	.addr = (const unsigned char *)0x008F23C4,
	.width = 186,
	.height = 12,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)336
};

const picture_info_struct pic_music_start0_info = {
	.addr = (const unsigned char *)0x008F2514,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3187
};

const picture_info_struct pic_music_volh_info = {
	.addr = (const unsigned char *)0x008F3188,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3572
};

const picture_info_struct pic_music_voll_info = {
	.addr = (const unsigned char *)0x008F3F7C,
	.width = 80,
	.height = 80,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3022
};

const picture_info_struct pic_next_info = {
	.addr = (const unsigned char *)0x008F4B4C,
	.width = 59,
	.height = 64,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1398
};

const picture_info_struct pic_previous_song_info = {
	.addr = (const unsigned char *)0x008F50C4,
	.width = 59,
	.height = 64,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6802
};

const picture_info_struct pic_sound_icon_info = {
	.addr = (const unsigned char *)0x008F6B58,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2052
};

const picture_info_struct pic_weather_bg_1_info = {
	.addr = (const unsigned char *)0x008F735C,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)32099
};

const picture_info_struct pic_weather_bg_2_info = {
	.addr = (const unsigned char *)0x008FF0C0,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)82201
};

const picture_info_struct pic_weather_bg_3_info = {
	.addr = (const unsigned char *)0x009131DC,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)8758
};

const picture_info_struct pic_weather_bg_4_info = {
	.addr = (const unsigned char *)0x00915414,
	.width = 233,
	.height = 233,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)38807
};

const picture_info_struct pic_aeolian_sand_info = {
	.addr = (const unsigned char *)0x0091EBAC,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4395
};

const picture_info_struct pic_cloudy_info = {
	.addr = (const unsigned char *)0x0091FCD8,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2958
};

const picture_info_struct pic_cloudy_partly_info = {
	.addr = (const unsigned char *)0x00920868,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3476
};

const picture_info_struct pic_heavy_rain_info = {
	.addr = (const unsigned char *)0x009215FC,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4231
};

const picture_info_struct pic_heavy_snow_info = {
	.addr = (const unsigned char *)0x00922684,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4550
};

const picture_info_struct pic_little_rain_info = {
	.addr = (const unsigned char *)0x0092384C,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3201
};

const picture_info_struct pic_little_snow_info = {
	.addr = (const unsigned char *)0x009244D0,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3298
};

const picture_info_struct pic_medium_rain_info = {
	.addr = (const unsigned char *)0x009251B4,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3847
};

const picture_info_struct pic_medium_snow_info = {
	.addr = (const unsigned char *)0x009260BC,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4090
};

const picture_info_struct pic_no_weather_info = {
	.addr = (const unsigned char *)0x009270B8,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3771
};

const picture_info_struct pic_shower_info = {
	.addr = (const unsigned char *)0x00927F74,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3570
};

const picture_info_struct pic_sleet_info = {
	.addr = (const unsigned char *)0x00928D68,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3920
};

const picture_info_struct pic_smog_info = {
	.addr = (const unsigned char *)0x00929CB8,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3580
};

const picture_info_struct pic_sun_info = {
	.addr = (const unsigned char *)0x0092AAB4,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4735
};

const picture_info_struct pic_thunder_rain_info = {
	.addr = (const unsigned char *)0x0092BD34,
	.width = 130,
	.height = 130,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4338
};

const picture_info_struct pic_aeolian_sand_l_info = {
	.addr = (const unsigned char *)0x0092CE28,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1817
};

const picture_info_struct pic_cloudy_l_info = {
	.addr = (const unsigned char *)0x0092D544,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1232
};

const picture_info_struct pic_cloudy_partly_l_info = {
	.addr = (const unsigned char *)0x0092DA14,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1451
};

const picture_info_struct pic_heavy_rain_l_info = {
	.addr = (const unsigned char *)0x0092DFC0,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1742
};

const picture_info_struct pic_heavy_snow_l_info = {
	.addr = (const unsigned char *)0x0092E690,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1823
};

const picture_info_struct pic_little_rain_l_info = {
	.addr = (const unsigned char *)0x0092EDB0,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1349
};

const picture_info_struct pic_little_snow_l_info = {
	.addr = (const unsigned char *)0x0092F2F8,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1366
};

const picture_info_struct pic_medium_rain_l_info = {
	.addr = (const unsigned char *)0x0092F850,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1580
};

const picture_info_struct pic_medium_snow_l_info = {
	.addr = (const unsigned char *)0x0092FE7C,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1631
};

const picture_info_struct pic_no_weather_l_info = {
	.addr = (const unsigned char *)0x009304DC,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1597
};

const picture_info_struct pic_shower_l_info = {
	.addr = (const unsigned char *)0x00930B1C,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1505
};

const picture_info_struct pic_sleet_l_info = {
	.addr = (const unsigned char *)0x00931100,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1597
};

const picture_info_struct pic_smog_l_info = {
	.addr = (const unsigned char *)0x00931740,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1537
};

const picture_info_struct pic_sun_l_info = {
	.addr = (const unsigned char *)0x00931D44,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1866
};

const picture_info_struct pic_thunder_rain_l_info = {
	.addr = (const unsigned char *)0x00932490,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1819
};

const picture_info_struct pic_weather_num_0_info = {
	.addr = (const unsigned char *)0x00932BAC,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1740
};

const picture_info_struct pic_weather_num_1_info = {
	.addr = (const unsigned char *)0x00933278,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)942
};

const picture_info_struct pic_weather_num_10_info = {
	.addr = (const unsigned char *)0x00933628,
	.width = 45,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)939
};

const picture_info_struct pic_weather_num_11_info = {
	.addr = (const unsigned char *)0x009339D4,
	.width = 50,
	.height = 50,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2117
};

const picture_info_struct pic_weather_num_2_info = {
	.addr = (const unsigned char *)0x0093421C,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1431
};

const picture_info_struct pic_weather_num_3_info = {
	.addr = (const unsigned char *)0x009347B4,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1621
};

const picture_info_struct pic_weather_num_4_info = {
	.addr = (const unsigned char *)0x00934E0C,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1324
};

const picture_info_struct pic_weather_num_5_info = {
	.addr = (const unsigned char *)0x00935338,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1468
};

const picture_info_struct pic_weather_num_6_info = {
	.addr = (const unsigned char *)0x009358F4,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1797
};

const picture_info_struct pic_weather_num_7_info = {
	.addr = (const unsigned char *)0x00935FFC,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1071
};

const picture_info_struct pic_weather_num_8_info = {
	.addr = (const unsigned char *)0x0093642C,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1842
};

const picture_info_struct pic_weather_num_9_info = {
	.addr = (const unsigned char *)0x00936B60,
	.width = 32,
	.height = 42,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1777
};

const picture_info_struct pic_music_dis_info = {
	.addr = (const unsigned char *)0x00937254,
	.width = 22,
	.height = 22,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1029
};

const picture_info_struct pic_woman_anquan_info = {
	.addr = (const unsigned char *)0x0093765C,
	.width = 50,
	.height = 41,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2060
};

const picture_info_struct pic_woman_bg_info = {
	.addr = (const unsigned char *)0x00937E68,
	.width = 200,
	.height = 187,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)27669
};

const picture_info_struct pic_woman_pailuan_info = {
	.addr = (const unsigned char *)0x0093EA80,
	.width = 50,
	.height = 41,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2411
};

const picture_info_struct pic_woman_yuejin_info = {
	.addr = (const unsigned char *)0x0093F3EC,
	.width = 50,
	.height = 41,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1713
};

const picture_info_struct pic_clock_set_bg_info = {
	.addr = (const unsigned char *)0x0093FAA0,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)416
};

const picture_info_struct pic_main_breath_ok_info = {
	.addr = (const unsigned char *)0x0093FC40,
	.width = 250,
	.height = 60,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2024
};

const picture_info_struct pic_clock_bg_info = {
	.addr = (const unsigned char *)0x00940428,
	.width = 230,
	.height = 230,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5850
};

const picture_info_struct pic_clock_cancel_info = {
	.addr = (const unsigned char *)0x00941B04,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3118
};

const picture_info_struct pic_clock_off_info = {
	.addr = (const unsigned char *)0x00942734,
	.width = 96,
	.height = 62,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1918
};

const picture_info_struct pic_clock_on_info = {
	.addr = (const unsigned char *)0x00942EB4,
	.width = 96,
	.height = 62,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1946
};

const picture_info_struct pic_clock_snooze_info = {
	.addr = (const unsigned char *)0x00943650,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3822
};

const picture_info_struct pic_radio_selected_info = {
	.addr = (const unsigned char *)0x00944540,
	.width = 40,
	.height = 40,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1456
};

const picture_info_struct pic_radio_unselected_info = {
	.addr = (const unsigned char *)0x00944AF0,
	.width = 40,
	.height = 40,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1796
};

const picture_info_struct pic_timer_add_info = {
	.addr = (const unsigned char *)0x009451F4,
	.width = 466,
	.height = 102,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5103
};

const picture_info_struct pic_clock_f_info = {
	.addr = (const unsigned char *)0x009465E4,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)361
};

const picture_info_struct pic_clock_f1_info = {
	.addr = (const unsigned char *)0x00946750,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)364
};

const picture_info_struct pic_clock_m_info = {
	.addr = (const unsigned char *)0x009468BC,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)704
};

const picture_info_struct pic_clock_m1_info = {
	.addr = (const unsigned char *)0x00946B7C,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)715
};

const picture_info_struct pic_clock_s_info = {
	.addr = (const unsigned char *)0x00946E48,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)448
};

const picture_info_struct pic_clock_s1_info = {
	.addr = (const unsigned char *)0x00947008,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)482
};

const picture_info_struct pic_clock_t_info = {
	.addr = (const unsigned char *)0x009471EC,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)370
};

const picture_info_struct pic_clock_t1_info = {
	.addr = (const unsigned char *)0x00947360,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)374
};

const picture_info_struct pic_clock_w_info = {
	.addr = (const unsigned char *)0x009474D8,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)763
};

const picture_info_struct pic_clock_w1_info = {
	.addr = (const unsigned char *)0x009477D4,
	.width = 22,
	.height = 20,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)781
};

const picture_info_struct pic_stopwatch_clear_info = {
	.addr = (const unsigned char *)0x00947AE4,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3270
};

const picture_info_struct pic_stopwatch_clear_no_info = {
	.addr = (const unsigned char *)0x009487AC,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3204
};

const picture_info_struct pic_stopwatch_record_info = {
	.addr = (const unsigned char *)0x00949430,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3556
};

const picture_info_struct pic_stopwatch_record_rect_info = {
	.addr = (const unsigned char *)0x0094A214,
	.width = 361,
	.height = 58,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1406
};

const picture_info_struct pic_stopwatch_start_info = {
	.addr = (const unsigned char *)0x0094A794,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2525
};

const picture_info_struct pic_stopwatch_suspend_info = {
	.addr = (const unsigned char *)0x0094B174,
	.width = 102,
	.height = 102,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2920
};

const picture_info_struct pic_counter_custom_info = {
	.addr = (const unsigned char *)0x0094BCDC,
	.width = 351,
	.height = 80,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2020
};

const picture_info_struct pic_counter_min_1_info = {
	.addr = (const unsigned char *)0x0094C4C0,
	.width = 160,
	.height = 160,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9510
};

const picture_info_struct pic_counter_min_10_info = {
	.addr = (const unsigned char *)0x0094E9E8,
	.width = 160,
	.height = 160,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)10446
};

const picture_info_struct pic_counter_min_3_info = {
	.addr = (const unsigned char *)0x009512B8,
	.width = 160,
	.height = 160,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9721
};

const picture_info_struct pic_counter_min_5_info = {
	.addr = (const unsigned char *)0x009538B4,
	.width = 160,
	.height = 160,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9686
};

const picture_info_struct pic_counter_up_number_0_info = {
	.addr = (const unsigned char *)0x00955E8C,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1358
};

const picture_info_struct pic_counter_up_number_1_info = {
	.addr = (const unsigned char *)0x009563DC,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)897
};

const picture_info_struct pic_counter_up_number_2_info = {
	.addr = (const unsigned char *)0x00956760,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1035
};

const picture_info_struct pic_counter_up_number_3_info = {
	.addr = (const unsigned char *)0x00956B6C,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1103
};

const picture_info_struct pic_counter_up_number_4_info = {
	.addr = (const unsigned char *)0x00956FBC,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1035
};

const picture_info_struct pic_counter_up_number_5_info = {
	.addr = (const unsigned char *)0x009573C8,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1063
};

const picture_info_struct pic_counter_up_number_6_info = {
	.addr = (const unsigned char *)0x009577F0,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1104
};

const picture_info_struct pic_counter_up_number_7_info = {
	.addr = (const unsigned char *)0x00957C40,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)963
};

const picture_info_struct pic_counter_up_number_8_info = {
	.addr = (const unsigned char *)0x00958004,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1330
};

const picture_info_struct pic_counter_up_number_9_info = {
	.addr = (const unsigned char *)0x00958538,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1118
};

const picture_info_struct pic_counter_dow_number_0_info = {
	.addr = (const unsigned char *)0x00958998,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1336
};

const picture_info_struct pic_counter_dow_number_1_info = {
	.addr = (const unsigned char *)0x00958ED0,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)845
};

const picture_info_struct pic_counter_dow_number_2_info = {
	.addr = (const unsigned char *)0x00959220,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)953
};

const picture_info_struct pic_counter_dow_number_3_info = {
	.addr = (const unsigned char *)0x009595DC,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1056
};

const picture_info_struct pic_counter_dow_number_4_info = {
	.addr = (const unsigned char *)0x009599FC,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)999
};

const picture_info_struct pic_counter_dow_number_5_info = {
	.addr = (const unsigned char *)0x00959DE4,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1092
};

const picture_info_struct pic_counter_dow_number_6_info = {
	.addr = (const unsigned char *)0x0095A228,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1122
};

const picture_info_struct pic_counter_dow_number_7_info = {
	.addr = (const unsigned char *)0x0095A68C,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)975
};

const picture_info_struct pic_counter_dow_number_8_info = {
	.addr = (const unsigned char *)0x0095AA5C,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1260
};

const picture_info_struct pic_counter_dow_number_9_info = {
	.addr = (const unsigned char *)0x0095AF48,
	.width = 32,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1060
};

const picture_info_struct pic_counter_number_0_info = {
	.addr = (const unsigned char *)0x0095B36C,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1998
};

const picture_info_struct pic_counter_number_1_info = {
	.addr = (const unsigned char *)0x0095BB3C,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1336
};

const picture_info_struct pic_counter_number_2_info = {
	.addr = (const unsigned char *)0x0095C074,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1530
};

const picture_info_struct pic_counter_number_3_info = {
	.addr = (const unsigned char *)0x0095C670,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1642
};

const picture_info_struct pic_counter_number_4_info = {
	.addr = (const unsigned char *)0x0095CCDC,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1385
};

const picture_info_struct pic_counter_number_5_info = {
	.addr = (const unsigned char *)0x0095D248,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1590
};

const picture_info_struct pic_counter_number_6_info = {
	.addr = (const unsigned char *)0x0095D880,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1693
};

const picture_info_struct pic_counter_number_7_info = {
	.addr = (const unsigned char *)0x0095DF20,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1426
};

const picture_info_struct pic_counter_number_8_info = {
	.addr = (const unsigned char *)0x0095E4B4,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1950
};

const picture_info_struct pic_counter_number_9_info = {
	.addr = (const unsigned char *)0x0095EC54,
	.width = 42,
	.height = 66,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1665
};

const picture_info_struct pic_link_ing_info = {
	.addr = (const unsigned char *)0x0095F2D8,
	.width = 59,
	.height = 70,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2026
};

const picture_info_struct pic_link_no_info = {
	.addr = (const unsigned char *)0x0095FAC4,
	.width = 59,
	.height = 70,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2001
};

const picture_info_struct pic_link_yes_info = {
	.addr = (const unsigned char *)0x00960298,
	.width = 59,
	.height = 70,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2033
};

const picture_info_struct pic_siri_bg_info = {
	.addr = (const unsigned char *)0x00960A8C,
	.width = 178,
	.height = 178,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)6021
};

const picture_info_struct pic_calculator_bg_info = {
	.addr = (const unsigned char *)0x00962214,
	.width = 466,
	.height = 466,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)42807
};

const picture_info_struct pic_ble_unlink_info = {
	.addr = (const unsigned char *)0x0096C94C,
	.width = 466,
	.height = 466,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)16592
};

const picture_info_struct pic_findphone_Gif_05_info = {
	.addr = (const unsigned char *)0x00970A1C,
	.width = 466,
	.height = 466,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)17578
};

const picture_info_struct pic_language_selected_info = {
	.addr = (const unsigned char *)0x00974EC8,
	.width = 400,
	.height = 110,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)4610
};

const picture_info_struct pic_language_set_yes_info = {
	.addr = (const unsigned char *)0x009760CC,
	.width = 466,
	.height = 88,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3692
};

const picture_info_struct pic_play_start_info = {
	.addr = (const unsigned char *)0x00976F38,
	.width = 69,
	.height = 69,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1889
};

const picture_info_struct pic_play_stop_info = {
	.addr = (const unsigned char *)0x0097769C,
	.width = 69,
	.height = 69,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1815
};

const picture_info_struct pic_record_bg_info = {
	.addr = (const unsigned char *)0x00977DB4,
	.width = 81,
	.height = 97,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3315
};

const picture_info_struct pic_record_start_info = {
	.addr = (const unsigned char *)0x00978AA8,
	.width = 70,
	.height = 70,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2848
};

const picture_info_struct pic_record_stop_info = {
	.addr = (const unsigned char *)0x009795C8,
	.width = 70,
	.height = 70,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2424
};

const picture_info_struct pic_battery_data_bg_info = {
	.addr = (const unsigned char *)0x00979F40,
	.width = 428,
	.height = 310,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)16329
};

const picture_info_struct pic_battery_schedule_0_info = {
	.addr = (const unsigned char *)0x0097DF0C,
	.width = 266,
	.height = 266,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9114
};

const picture_info_struct pic_battery_schedule_1_info = {
	.addr = (const unsigned char *)0x009802A8,
	.width = 266,
	.height = 266,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9448
};

const picture_info_struct pic_battery_schedule_2_info = {
	.addr = (const unsigned char *)0x00982790,
	.width = 266,
	.height = 266,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9534
};

const picture_info_struct pic_battery_schedule_3_info = {
	.addr = (const unsigned char *)0x00984CD0,
	.width = 266,
	.height = 266,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9562
};

const picture_info_struct pic_battery_schedule_4_info = {
	.addr = (const unsigned char *)0x0098722C,
	.width = 266,
	.height = 266,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)9342
};

const picture_info_struct pic_charger_txt_0_info = {
	.addr = (const unsigned char *)0x009896AC,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1476
};

const picture_info_struct pic_charger_txt_1_info = {
	.addr = (const unsigned char *)0x00989C70,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)972
};

const picture_info_struct pic_charger_txt_10_info = {
	.addr = (const unsigned char *)0x0098A03C,
	.width = 30,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1695
};

const picture_info_struct pic_charger_txt_2_info = {
	.addr = (const unsigned char *)0x0098A6DC,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1140
};

const picture_info_struct pic_charger_txt_3_info = {
	.addr = (const unsigned char *)0x0098AB50,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1248
};

const picture_info_struct pic_charger_txt_4_info = {
	.addr = (const unsigned char *)0x0098B030,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1092
};

const picture_info_struct pic_charger_txt_5_info = {
	.addr = (const unsigned char *)0x0098B474,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1199
};

const picture_info_struct pic_charger_txt_6_info = {
	.addr = (const unsigned char *)0x0098B924,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1284
};

const picture_info_struct pic_charger_txt_7_info = {
	.addr = (const unsigned char *)0x0098BE28,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1059
};

const picture_info_struct pic_charger_txt_8_info = {
	.addr = (const unsigned char *)0x0098C24C,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1456
};

const picture_info_struct pic_charger_txt_9_info = {
	.addr = (const unsigned char *)0x0098C7FC,
	.width = 32,
	.height = 50,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1209
};

const picture_info_struct pic_photograph_info = {
	.addr = (const unsigned char *)0x0098CCB8,
	.width = 107,
	.height = 92,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2448
};

const picture_info_struct pic_setting_app_icon_personal_info = {
	.addr = (const unsigned char *)0x0098D648,
	.width = 114,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4560
};

const picture_info_struct pic_setting_app_icon_personal_login_info = {
	.addr = (const unsigned char *)0x0098E818,
	.width = 114,
	.height = 114,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4723
};

const picture_info_struct pic_moreinfo_style_cell_info = {
	.addr = (const unsigned char *)0x0098FA8C,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5163
};

const picture_info_struct pic_moreinfo_style_kaleidoscope_info = {
	.addr = (const unsigned char *)0x00990EB8,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4266
};

const picture_info_struct pic_moreinfo_style_list_info = {
	.addr = (const unsigned char *)0x00991F64,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3244
};

const picture_info_struct pic_moreinfo_style_matrix_info = {
	.addr = (const unsigned char *)0x00992C10,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4940
};

const picture_info_struct pic_moreinfo_style_ring_info = {
	.addr = (const unsigned char *)0x00993F5C,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3760
};

const picture_info_struct pic_sound_touch_bg_big_info = {
	.addr = (const unsigned char *)0x00994E0C,
	.width = 63,
	.height = 48,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2386
};

const picture_info_struct pic_sound_touch_bg_small_info = {
	.addr = (const unsigned char *)0x00995760,
	.width = 31,
	.height = 46,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)694
};

const picture_info_struct pic_screen_brightness_high_info = {
	.addr = (const unsigned char *)0x00995A18,
	.width = 56,
	.height = 56,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2415
};

const picture_info_struct pic_screen_brightness_low_info = {
	.addr = (const unsigned char *)0x00996388,
	.width = 48,
	.height = 48,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2413
};

const picture_info_struct pic_setting_list_icon_app_view_info = {
	.addr = (const unsigned char *)0x00996CF8,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3376
};

const picture_info_struct pic_setting_list_icon_battry_info = {
	.addr = (const unsigned char *)0x00997A28,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2384
};

const picture_info_struct pic_setting_list_icon_disturb_info = {
	.addr = (const unsigned char *)0x00998378,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3171
};

const picture_info_struct pic_setting_list_icon_key_setting_info = {
	.addr = (const unsigned char *)0x00998FDC,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2717
};

const picture_info_struct pic_setting_list_icon_notice_info = {
	.addr = (const unsigned char *)0x00999A7C,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2387
};

const picture_info_struct pic_setting_list_icon_password_info = {
	.addr = (const unsigned char *)0x0099A3D0,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2536
};

const picture_info_struct pic_setting_list_icon_personal_info = {
	.addr = (const unsigned char *)0x0099ADB8,
	.width = 76,
	.height = 76,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5099
};

const picture_info_struct pic_setting_list_icon_personal_login_info = {
	.addr = (const unsigned char *)0x0099C1A4,
	.width = 76,
	.height = 76,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3113
};

const picture_info_struct pic_setting_list_icon_screen_info = {
	.addr = (const unsigned char *)0x0099CDD0,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2966
};

const picture_info_struct pic_setting_list_icon_setting_info = {
	.addr = (const unsigned char *)0x0099D968,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5768
};

const picture_info_struct pic_setting_list_icon_sleep_info = {
	.addr = (const unsigned char *)0x0099EFF0,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)6446
};

const picture_info_struct pic_setting_list_icon_sos_info = {
	.addr = (const unsigned char *)0x009A0920,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3239
};

const picture_info_struct pic_setting_list_icon_sound_and_touch_info = {
	.addr = (const unsigned char *)0x009A15C8,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2977
};

const picture_info_struct pic_setting_list_icon_sport_info = {
	.addr = (const unsigned char *)0x009A216C,
	.width = 62,
	.height = 62,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)5426
};

const picture_info_struct pic_black_point_1_info = {
	.addr = (const unsigned char *)0x009A36A0,
	.width = 8,
	.height = 8,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)166
};

const picture_info_struct pic_light_point_1_info = {
	.addr = (const unsigned char *)0x009A3748,
	.width = 8,
	.height = 8,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)166
};

const picture_info_struct pic_progress_bar_open_info = {
	.addr = (const unsigned char *)0x009A37F0,
	.width = 56,
	.height = 19,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)576
};

const picture_info_struct pic_progress_bar_shut_info = {
	.addr = (const unsigned char *)0x009A3A30,
	.width = 56,
	.height = 19,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)561
};

const picture_info_struct pic_setting_list_hint_arrow_info = {
	.addr = (const unsigned char *)0x009A3C64,
	.width = 23,
	.height = 46,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1234
};

const picture_info_struct pic_setting_list_icon_bg_1_info = {
	.addr = (const unsigned char *)0x009A4138,
	.width = 422,
	.height = 118,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4626
};

const picture_info_struct pic_setting_list_icon_bg_2_info = {
	.addr = (const unsigned char *)0x009A534C,
	.width = 422,
	.height = 106,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)4114
};

const picture_info_struct pic_setting_list_icon_bg_3_info = {
	.addr = (const unsigned char *)0x009A6360,
	.width = 422,
	.height = 256,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)7122
};

const picture_info_struct pic_setting_list_icon_bg_4_info = {
	.addr = (const unsigned char *)0x009A7F34,
	.width = 310,
	.height = 100,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)3472
};

const picture_info_struct pic_setting_list_icon_progress_bar_info = {
	.addr = (const unsigned char *)0x009A8CC4,
	.width = 246,
	.height = 18,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)512
};

const picture_info_struct pic_setting_list_icon_progress_bg_info = {
	.addr = (const unsigned char *)0x009A8EC4,
	.width = 246,
	.height = 18,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)512
};

const picture_info_struct pic_setting_list_status_checked_info = {
	.addr = (const unsigned char *)0x009A90C4,
	.width = 44,
	.height = 44,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1626
};

const picture_info_struct pic_setting_list_status_checked_unselect_info = {
	.addr = (const unsigned char *)0x009A9720,
	.width = 44,
	.height = 44,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)1626
};

const picture_info_struct pic_setting_list_status_close_info = {
	.addr = (const unsigned char *)0x009A9D7C,
	.width = 88,
	.height = 52,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2134
};

const picture_info_struct pic_setting_list_status_open_info = {
	.addr = (const unsigned char *)0x009AA5D4,
	.width = 88,
	.height = 52,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2110
};

const picture_info_struct pic_shake_open_info = {
	.addr = (const unsigned char *)0x009AAE14,
	.width = 55,
	.height = 25,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)743
};

const picture_info_struct pic_shake_shut_info = {
	.addr = (const unsigned char *)0x009AB0FC,
	.width = 55,
	.height = 25,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)695
};

const picture_info_struct pic_top_bg_info = {
	.addr = (const unsigned char *)0x009AB3B4,
	.width = 466,
	.height = 90,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1440
};

const picture_info_struct pic_game_2048_info = {
	.addr = (const unsigned char *)0x009AB954,
	.width = 48,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3147
};

const picture_info_struct pic_game_dadishu_info = {
	.addr = (const unsigned char *)0x009AC5A0,
	.width = 48,
	.height = 48,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)3538
};

const picture_info_struct pic_game_2048_0_info = {
	.addr = (const unsigned char *)0x009AD374,
	.width = 77,
	.height = 77,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2259
};

const picture_info_struct pic_game_2048_16_info = {
	.addr = (const unsigned char *)0x009ADC48,
	.width = 77,
	.height = 77,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2207
};

const picture_info_struct pic_game_2048_2_info = {
	.addr = (const unsigned char *)0x009AE4E8,
	.width = 77,
	.height = 77,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2227
};

const picture_info_struct pic_game_2048_32_info = {
	.addr = (const unsigned char *)0x009AED9C,
	.width = 77,
	.height = 77,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2200
};

const picture_info_struct pic_game_2048_4_info = {
	.addr = (const unsigned char *)0x009AF634,
	.width = 77,
	.height = 77,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2261
};

const picture_info_struct pic_game_2048_64_info = {
	.addr = (const unsigned char *)0x009AFF0C,
	.width = 77,
	.height = 77,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2072
};

const picture_info_struct pic_game_2048_8_info = {
	.addr = (const unsigned char *)0x009B0724,
	.width = 77,
	.height = 77,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)2221
};

const picture_info_struct pic_game_2048_back_info = {
	.addr = (const unsigned char *)0x009B0FD4,
	.width = 165,
	.height = 67,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5142
};

const picture_info_struct pic_game_2048_bg_info = {
	.addr = (const unsigned char *)0x009B23EC,
	.width = 466,
	.height = 398,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)72195
};

const picture_info_struct pic_game_2048_reset_info = {
	.addr = (const unsigned char *)0x009C3DF0,
	.width = 165,
	.height = 67,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)5734
};

const picture_info_struct pic_game_2048_result_info = {
	.addr = (const unsigned char *)0x009C5458,
	.width = 365,
	.height = 161,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)58296
};

const picture_info_struct pic_dadishu_bg_info = {
	.addr = (const unsigned char *)0x009D3810,
	.width = 466,
	.height = 466,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)36769
};

const picture_info_struct pic_dadishu_chuizi_1_info = {
	.addr = (const unsigned char *)0x009DC7B4,
	.width = 141,
	.height = 108,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)14238
};

const picture_info_struct pic_dadishu_chuizi_2_info = {
	.addr = (const unsigned char *)0x009DFF54,
	.width = 125,
	.height = 135,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)16465
};

const picture_info_struct pic_dadishu_close_info = {
	.addr = (const unsigned char *)0x009E3FA8,
	.width = 70,
	.height = 71,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)9019
};

const picture_info_struct pic_dadishu_guanka_info = {
	.addr = (const unsigned char *)0x009E62E4,
	.width = 28,
	.height = 25,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1086
};

const picture_info_struct pic_dadishu_jiesuan_info = {
	.addr = (const unsigned char *)0x009E6724,
	.width = 440,
	.height = 280,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)145503
};

const picture_info_struct pic_dadishu_kaishi_info = {
	.addr = (const unsigned char *)0x00A09F84,
	.width = 440,
	.height = 253,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)160677
};

const picture_info_struct pic_dadishu_score_info = {
	.addr = (const unsigned char *)0x00A3132C,
	.width = 28,
	.height = 25,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1113
};

const picture_info_struct pic_dadishu_shudong_1_info = {
	.addr = (const unsigned char *)0x00A31788,
	.width = 124,
	.height = 101,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)12698
};

const picture_info_struct pic_dadishu_shudong_2_info = {
	.addr = (const unsigned char *)0x00A34924,
	.width = 124,
	.height = 101,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)18375
};

const picture_info_struct pic_dadishu_shudong_3_info = {
	.addr = (const unsigned char *)0x00A390EC,
	.width = 124,
	.height = 101,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)19566
};

const picture_info_struct pic_dadishu_start_info = {
	.addr = (const unsigned char *)0x00A3DD5C,
	.width = 70,
	.height = 71,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)8910
};

const picture_info_struct pic_dadishu_time_info = {
	.addr = (const unsigned char *)0x00A4002C,
	.width = 28,
	.height = 25,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1397
};

const picture_info_struct pic_dadishu_xiaoguo_1_info = {
	.addr = (const unsigned char *)0x00A405A4,
	.width = 37,
	.height = 36,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2328
};

const picture_info_struct pic_dadishu_xiaoguo_2_info = {
	.addr = (const unsigned char *)0x00A40EBC,
	.width = 37,
	.height = 36,
	.alpha = 11,
	.external_flag = 1,
	.config = (const void*)2333
};

const picture_info_struct pic_12x17_0_info = {
	.addr = (const unsigned char *)0x00A417DC,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)397
};

const picture_info_struct pic_12x17_1_info = {
	.addr = (const unsigned char *)0x00A4196C,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)309
};

const picture_info_struct pic_12x17_2_info = {
	.addr = (const unsigned char *)0x00A41AA4,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)337
};

const picture_info_struct pic_12x17_3_info = {
	.addr = (const unsigned char *)0x00A41BF8,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)378
};

const picture_info_struct pic_12x17_4_info = {
	.addr = (const unsigned char *)0x00A41D74,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)362
};

const picture_info_struct pic_12x17_5_info = {
	.addr = (const unsigned char *)0x00A41EE0,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)353
};

const picture_info_struct pic_12x17_6_info = {
	.addr = (const unsigned char *)0x00A42044,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)409
};

const picture_info_struct pic_12x17_7_info = {
	.addr = (const unsigned char *)0x00A421E0,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)279
};

const picture_info_struct pic_12x17_8_info = {
	.addr = (const unsigned char *)0x00A422F8,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)409
};

const picture_info_struct pic_12x17_9_info = {
	.addr = (const unsigned char *)0x00A42494,
	.width = 12,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)403
};

const picture_info_struct pic_12x17_percent_info = {
	.addr = (const unsigned char *)0x00A42628,
	.width = 20,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)593
};

const picture_info_struct pic_12x17_point_info = {
	.addr = (const unsigned char *)0x00A4287C,
	.width = 4,
	.height = 17,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)137
};

const picture_info_struct pic_16x23_0_info = {
	.addr = (const unsigned char *)0x00A42908,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)593
};

const picture_info_struct pic_16x23_1_info = {
	.addr = (const unsigned char *)0x00A42B5C,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)463
};

const picture_info_struct pic_16x23_2_info = {
	.addr = (const unsigned char *)0x00A42D2C,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)496
};

const picture_info_struct pic_16x23_3_info = {
	.addr = (const unsigned char *)0x00A42F1C,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)544
};

const picture_info_struct pic_16x23_4_info = {
	.addr = (const unsigned char *)0x00A4313C,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)536
};

const picture_info_struct pic_16x23_5_info = {
	.addr = (const unsigned char *)0x00A43354,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)518
};

const picture_info_struct pic_16x23_6_info = {
	.addr = (const unsigned char *)0x00A4355C,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)609
};

const picture_info_struct pic_16x23_7_info = {
	.addr = (const unsigned char *)0x00A437C0,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)408
};

const picture_info_struct pic_16x23_8_info = {
	.addr = (const unsigned char *)0x00A43958,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)606
};

const picture_info_struct pic_16x23_9_info = {
	.addr = (const unsigned char *)0x00A43BB8,
	.width = 16,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)604
};

const picture_info_struct pic_16x23_percent_info = {
	.addr = (const unsigned char *)0x00A43E14,
	.width = 21,
	.height = 23,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)708
};

const picture_info_struct pic_34_0_info = {
	.addr = (const unsigned char *)0x00A440D8,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)798
};

const picture_info_struct pic_34_1_info = {
	.addr = (const unsigned char *)0x00A443F8,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)507
};

const picture_info_struct pic_34_2_info = {
	.addr = (const unsigned char *)0x00A445F4,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)657
};

const picture_info_struct pic_34_3_info = {
	.addr = (const unsigned char *)0x00A44888,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)743
};

const picture_info_struct pic_34_4_info = {
	.addr = (const unsigned char *)0x00A44B70,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)603
};

const picture_info_struct pic_34_5_info = {
	.addr = (const unsigned char *)0x00A44DCC,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)699
};

const picture_info_struct pic_34_6_info = {
	.addr = (const unsigned char *)0x00A45088,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)808
};

const picture_info_struct pic_34_7_info = {
	.addr = (const unsigned char *)0x00A453B0,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)522
};

const picture_info_struct pic_34_8_info = {
	.addr = (const unsigned char *)0x00A455BC,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)819
};

const picture_info_struct pic_34_9_info = {
	.addr = (const unsigned char *)0x00A458F0,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)749
};

const picture_info_struct pic_34_delete_info = {
	.addr = (const unsigned char *)0x00A45BE0,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)273
};

const picture_info_struct pic_34_line_info = {
	.addr = (const unsigned char *)0x00A45CF4,
	.width = 21,
	.height = 33,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)609
};

const picture_info_struct pic_36_color_0_info = {
	.addr = (const unsigned char *)0x00A45F58,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)824
};

const picture_info_struct pic_36_color_1_info = {
	.addr = (const unsigned char *)0x00A46290,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)596
};

const picture_info_struct pic_36_color_2_info = {
	.addr = (const unsigned char *)0x00A464E4,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)689
};

const picture_info_struct pic_36_color_3_info = {
	.addr = (const unsigned char *)0x00A46798,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)771
};

const picture_info_struct pic_36_color_4_info = {
	.addr = (const unsigned char *)0x00A46A9C,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)687
};

const picture_info_struct pic_36_color_5_info = {
	.addr = (const unsigned char *)0x00A46D4C,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)726
};

const picture_info_struct pic_36_color_6_info = {
	.addr = (const unsigned char *)0x00A47024,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)846
};

const picture_info_struct pic_36_color_7_info = {
	.addr = (const unsigned char *)0x00A47374,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)547
};

const picture_info_struct pic_36_color_8_info = {
	.addr = (const unsigned char *)0x00A47598,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)855
};

const picture_info_struct pic_36_color_9_info = {
	.addr = (const unsigned char *)0x00A478F0,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)844
};

const picture_info_struct pic_36_color_C_info = {
	.addr = (const unsigned char *)0x00A47C3C,
	.width = 9,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)361
};

const picture_info_struct pic_36_color_delete_info = {
	.addr = (const unsigned char *)0x00A47DA8,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)268
};

const picture_info_struct pic_36_color_line_info = {
	.addr = (const unsigned char *)0x00A47EB4,
	.width = 22,
	.height = 34,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)628
};

const picture_info_struct pic_90_1_info = {
	.addr = (const unsigned char *)0x00A48128,
	.width = 49,
	.height = 71,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1397
};

const picture_info_struct pic_90_2_info = {
	.addr = (const unsigned char *)0x00A486A0,
	.width = 49,
	.height = 71,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1567
};

const picture_info_struct pic_90_3_info = {
	.addr = (const unsigned char *)0x00A48CC0,
	.width = 49,
	.height = 71,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1786
};

const picture_info_struct pic_alarm_0_info = {
	.addr = (const unsigned char *)0x00A493BC,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1036
};

const picture_info_struct pic_alarm_1_info = {
	.addr = (const unsigned char *)0x00A497C8,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)912
};

const picture_info_struct pic_alarm_2_info = {
	.addr = (const unsigned char *)0x00A49B58,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)938
};

const picture_info_struct pic_alarm_3_info = {
	.addr = (const unsigned char *)0x00A49F04,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1008
};

const picture_info_struct pic_alarm_4_info = {
	.addr = (const unsigned char *)0x00A4A2F4,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)937
};

const picture_info_struct pic_alarm_5_info = {
	.addr = (const unsigned char *)0x00A4A6A0,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)968
};

const picture_info_struct pic_alarm_6_info = {
	.addr = (const unsigned char *)0x00A4AA68,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1039
};

const picture_info_struct pic_alarm_7_info = {
	.addr = (const unsigned char *)0x00A4AE78,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)813
};

const picture_info_struct pic_alarm_8_info = {
	.addr = (const unsigned char *)0x00A4B1A8,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1194
};

const picture_info_struct pic_alarm_9_info = {
	.addr = (const unsigned char *)0x00A4B654,
	.width = 27,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1068
};

const picture_info_struct pic_alarm_point_info = {
	.addr = (const unsigned char *)0x00A4BA80,
	.width = 10,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)378
};

const picture_info_struct pic_alarm_two_point_info = {
	.addr = (const unsigned char *)0x00A4BBFC,
	.width = 10,
	.height = 44,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)420
};

const picture_info_struct pic_sport_data_0_info = {
	.addr = (const unsigned char *)0x00A4BDA0,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)598
};

const picture_info_struct pic_sport_data_1_info = {
	.addr = (const unsigned char *)0x00A4BFF8,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)439
};

const picture_info_struct pic_sport_data_2_info = {
	.addr = (const unsigned char *)0x00A4C1B0,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)472
};

const picture_info_struct pic_sport_data_3_info = {
	.addr = (const unsigned char *)0x00A4C388,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)499
};

const picture_info_struct pic_sport_data_4_info = {
	.addr = (const unsigned char *)0x00A4C57C,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)444
};

const picture_info_struct pic_sport_data_5_info = {
	.addr = (const unsigned char *)0x00A4C738,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)490
};

const picture_info_struct pic_sport_data_6_info = {
	.addr = (const unsigned char *)0x00A4C924,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)510
};

const picture_info_struct pic_sport_data_7_info = {
	.addr = (const unsigned char *)0x00A4CB24,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)402
};

const picture_info_struct pic_sport_data_8_info = {
	.addr = (const unsigned char *)0x00A4CCB8,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)572
};

const picture_info_struct pic_sport_data_9_info = {
	.addr = (const unsigned char *)0x00A4CEF4,
	.width = 12,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)500
};

const picture_info_struct pic_sport_data_delete_info = {
	.addr = (const unsigned char *)0x00A4D0E8,
	.width = 8,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)178
};

const picture_info_struct pic_sport_data_point_info = {
	.addr = (const unsigned char *)0x00A4D19C,
	.width = 6,
	.height = 22,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)186
};

const picture_info_struct pic_sport_time_0_info = {
	.addr = (const unsigned char *)0x00A4D258,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1179
};

const picture_info_struct pic_sport_time_1_info = {
	.addr = (const unsigned char *)0x00A4D6F4,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)744
};

const picture_info_struct pic_sport_time_2_info = {
	.addr = (const unsigned char *)0x00A4D9DC,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)892
};

const picture_info_struct pic_sport_time_3_info = {
	.addr = (const unsigned char *)0x00A4DD58,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)991
};

const picture_info_struct pic_sport_time_4_info = {
	.addr = (const unsigned char *)0x00A4E138,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)872
};

const picture_info_struct pic_sport_time_5_info = {
	.addr = (const unsigned char *)0x00A4E4A0,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)957
};

const picture_info_struct pic_sport_time_6_info = {
	.addr = (const unsigned char *)0x00A4E860,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1024
};

const picture_info_struct pic_sport_time_7_info = {
	.addr = (const unsigned char *)0x00A4EC60,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)777
};

const picture_info_struct pic_sport_time_8_info = {
	.addr = (const unsigned char *)0x00A4EF6C,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1119
};

const picture_info_struct pic_sport_time_9_info = {
	.addr = (const unsigned char *)0x00A4F3CC,
	.width = 22,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)1027
};

const picture_info_struct pic_sport_time_point_info = {
	.addr = (const unsigned char *)0x00A4F7D0,
	.width = 14,
	.height = 43,
	.alpha = 10,
	.external_flag = 1,
	.config = (const void*)509
};

