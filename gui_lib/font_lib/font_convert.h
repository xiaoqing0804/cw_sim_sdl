#ifndef __GUI_CONVERT_H__
#define __GUI_CONVERT_H__

#include "feature_all.h"
#include "system_util_math_geometry.h"
#include "gui_core.h"
#include "font_cfont.h"


#if TCFG_PAY_ALIOS_ENABLE
#define UCS16_INVALID_CODE  0x25A1
#else
#define UCS16_INVALID_CODE  0x20
#endif

extern int utf8_get_size(unsigned char ch);

extern int utf8_nc_copy(unsigned char* pDes, unsigned char* pSrc, unsigned int char_count);
extern int utf8_n_copy_ext(unsigned char* pDes, unsigned char* pSrc, unsigned int des_len, unsigned int* utf8_num);
extern int utf8_n_copy(unsigned char* pDes, unsigned char* pSrc, unsigned int des_len);
extern int utf8_n_clip(unsigned char* pSrc, unsigned int des_len);
// 转换utf8编码到unicode， 返回当前字符的utf8编码长度
extern int utf8_to_unicode(const unsigned char* p_char, unsigned long *unicode);

// 测试utf8字符串的显示宽度和高度， 返回有多少个字符 ...
// lineFlag - [out] 如果字符串中有换行符,则此标志会置1 ...
extern unsigned int get_font_string_meastrue(unsigned char* utf8Str, unsigned int* width, unsigned int* height, unsigned int* lineFlag);


// 指定显示宽度,获取一行utf8字符串, 返回有多少个字符 这一行的utf8字符串长度 ...
// retWidth - [out] 返回当前行的实际显示宽度 ..
extern unsigned int get_font_chars_line_from_string(unsigned char* utf8Str, unsigned int dispWidth, unsigned int* retWidth);


// 从字符串中获取第一个字符, 返回字符后的字符串
// retFlag - [out] 成功时,此标志置1 ..
extern unsigned char* get_font_char_info_from_string(unsigned char* utf8Str, font_char_info_struct* char_info, unsigned int* retFlag);


// 获取给定字符的信息
extern int get_font_char_info_from_code(unsigned long unicode, font_char_info_struct* char_info);


// 获取字库中字符的高度 
extern unsigned int get_font_height(void);
extern unsigned int get_font_height_by_size(unsigned char fontSize);


extern unsigned char get_font_size(void);


// 设置系统字体大小 ..
extern unsigned char set_font_size(unsigned int szType);

extern int get_font_char_info_from_size_code(unsigned char size_type, unsigned long unicode, font_char_info_struct* char_info);

#endif


