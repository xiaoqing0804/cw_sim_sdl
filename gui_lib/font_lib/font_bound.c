#include "font_bound.h"
#include "stdio.h"
#include "string.h"
#include "feature_all.h"

//是否为拉丁文文字
unsigned char font_bound_is_latin(unsigned short unicode)
{
	return unicode <= 0x00FF;
}

//是否为拉丁文符号
unsigned char font_bound_is_latin_symbol(unsigned short unicode)
{
	return (unicode >= 0x20 && unicode <= 0x2F)
		|| (unicode >= 0x3A && unicode <= 0x40)
		|| (unicode >= 0x5B && unicode <= 0x60)
		|| (unicode >= 0x7B && unicode <= 0x7F);
}




//是否为阿拉伯文字
unsigned char font_bound_is_arabic(unsigned short unicode)
{
	return (unicode >= 0x0600 && unicode <= 0x06FF)
		 ||(unicode >= 0xFB50 && unicode <= 0xFDFF) //阿拉伯文表达形式A
		 ||(unicode >= 0xFE70 && unicode <= 0xFEFF);//阿拉伯文表达形式B
}

unsigned char font_bound_is_arabic_symbol(unsigned short unicode)
{
	return (unicode >= 0x0600 && unicode <= 0x0620)
		|| (unicode >= 0x066A && unicode <= 0x066D)
		|| (unicode >= 0x06D4 && unicode <= 0x06ED);
}




//是否为希伯来文文字
unsigned char font_bound_is_hebrew(unsigned short unicode)
{
	return (unicode >= 0x0590 && unicode <= 0x05FF);
}

unsigned char font_bound_is_hebrew_symbol(unsigned short unicode)
{
	return (unicode >= 0x0590 && unicode <= 0x05CF)
		|| (unicode >= 0x05F3 && unicode <= 0x05FF);
}




//是否为中文
unsigned char font_bound_is_chinese(unsigned short unicode)
{
	return (unicode >= 0x4E00 && unicode <= 0x9FA5); //汉字全部
}

//是否为日文
unsigned char font_bound_is_japanese(unsigned short unicode)
{
	return (unicode >= 0x3040 && unicode <= 0x309F)  //日文平假名
		||(unicode >= 0x30A0 && unicode <= 0x30FF)  //日文片假名
		||(unicode >= 0x31F0 && unicode <= 0x31FF);  //日文片假名拼音扩展
}

//是否为韩文
unsigned char font_bound_is_korean(unsigned short unicode)
{
	return (unicode >= 0xAC00 && unicode <= 0xD7AF)  //韩文拼音
		||(unicode >= 0x1100 && unicode <= 0x11FF)  //韩文字母
		||(unicode >= 0x3130 && unicode <= 0x318F); //韩文兼容字母
}




//是否为数字
unsigned char font_bound_is_number(unsigned short unicode)
{
	return (unicode >= 0x30 && unicode <= 0x39);
}

//是否为空格
unsigned char font_bound_is_space(unsigned short unicode)
{
	return unicode == 0x20;
}

unsigned char font_bound_is_dot(unsigned short unicode)
{
	return unicode == 0x2E;
}

//是否为字母文字的符号
unsigned char font_bound_is_alphabet_symbol(unsigned short unicode)
{
	return font_bound_is_latin_symbol(unicode)
		|| font_bound_is_arabic_symbol(unicode)
		|| font_bound_is_hebrew_symbol(unicode);
}


//是否为从右到左的字母文字
unsigned char font_bound_is_alphabet_right_to_left(unsigned short unicode)
{
	return font_bound_is_arabic(unicode)
		 ||font_bound_is_hebrew(unicode);
}


//是否为字母文字
unsigned char font_bound_is_alphabet(unsigned short unicode)
{
	return font_bound_is_latin(unicode)
		 ||font_bound_is_arabic(unicode)
		 ||font_bound_is_hebrew(unicode);
}

//是否为表意文字
unsigned char font_bound_is_ideogram(unsigned short unicode)
{
	return font_bound_is_chinese(unicode)
		||font_bound_is_japanese(unicode)
		||font_bound_is_korean(unicode);
}


