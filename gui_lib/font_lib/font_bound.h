#ifndef __FONT_BOUND_H__
#define __FONT_BOUND_H__

#include "font_bound.h"
#include "stdio.h"
#include "string.h"
#include "feature_all.h"

//是否为拉丁文文字
extern unsigned char font_bound_is_latin(unsigned short unicode);

//是否为拉丁文符号
extern unsigned char font_bound_is_latin_symbol(unsigned short unicode);

//是否为阿拉伯文字
extern unsigned char font_bound_is_arabic(unsigned short unicode);

extern unsigned char font_bound_is_arabic_symbol(unsigned short unicode);

//是否为希伯来文文字
extern unsigned char font_bound_is_hebrew(unsigned short unicode);

extern unsigned char font_bound_is_hebrew_symbol(unsigned short unicode);

//是否为中文
extern unsigned char font_bound_is_chinese(unsigned short unicode);

//是否为日文
extern unsigned char font_bound_is_japanese(unsigned short unicode);

//是否为韩文
extern unsigned char font_bound_is_korean(unsigned short unicode);

//是否为数字
extern unsigned char font_bound_is_number(unsigned short unicode);

//是否为空格
extern unsigned char font_bound_is_space(unsigned short unicode);

//是否为句号
extern unsigned char font_bound_is_dot(unsigned short unicode);

//是否为字母文字的符号
extern unsigned char font_bound_is_alphabet_symbol(unsigned short unicode);

//是否为从右到左的字母文字
extern unsigned char font_bound_is_alphabet_right_to_left(unsigned short unicode);

//是否为字母文字
extern unsigned char font_bound_is_alphabet(unsigned short unicode);

//是否为表意文字
extern unsigned char font_bound_is_ideogram(unsigned short unicode);

#endif


